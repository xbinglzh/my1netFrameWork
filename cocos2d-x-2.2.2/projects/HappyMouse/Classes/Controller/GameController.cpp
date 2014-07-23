//
//  GameController.cpp
//  HappyMouse
//
//  Created by xUanBing on 14-7-15.
//
//

#include "GameController.h"
#include "GameConfig.h"
#include "NotifyMessageDef.h"
#include "ConstansDef.h"
#include "SceneController.h"
#include "GameUtils.h"
#include "KeyConfigDef.h"


static GameController* _sharedInstance = NULL;

GameController::GameController() : CCObject() {
    
}

GameController::~GameController() {
    
    _randomVector.clear();
    
}

GameController* GameController::getInstance() {
    
    if (!_sharedInstance) {
        _sharedInstance = new GameController();
        _sharedInstance->init();
    }
    
    return _sharedInstance;
}

void GameController::purgeInstance() {
    CC_SAFE_RELEASE_NULL(_sharedInstance);
}

bool GameController::init() {
    
    return true;
}

void GameController::update(float dt) {
    //TODO: 处理业务逻辑
}

void GameController::notifyRandomMouses() {
    
    int randomId = genRandomMouseIndex();
    
    CCNotificationCenter::sharedNotificationCenter()->postNotification(KNotifyMousePop, CCInteger::create(randomId));
}

int GameController::genRandomMouseIndex() {
    
    if (_randomVector.size() == GameConfig::getInstance()->getPitNumCount()) {
        _randomVector.clear();
    }
    
    int randomId = rand() % GameConfig::getInstance()->getPitNumCount();
    
    if (isIdInRandomVector(randomId)) {
        return genRandomMouseIndex();
    } else {
        _randomVector.push_back(randomId);
        return randomId;
    }
    
}

bool GameController::isIdInRandomVector(int currentId) {
    for (int i = 0; i < _randomVector.size(); i++) {
        int id = _randomVector.at(i);
        if (currentId == id) {
            return true;
        }
    }
    return false;
}


void GameController::genRandomMouseIds() {
    
    _randomVector.clear();

    for (int i = 0; i < 4; i++) {
        _randomVector.push_back(genRandomMouseIndex());
    }
}

void GameController::switchToBattleSence(const int32_t battleZoneId,
                                         const int32_t stageId,
                                         const int32_t chipId) {
    
    CCDictionary * dict = CCDictionary::create();
    dict->setObject(GameUtils::GXCCStringMake(battleZoneId), KStrBattleZoneId);
    dict->setObject(GameUtils::GXCCStringMake(stageId), KStrBattleId);

    ESceneId currentScene = SceneController::getInstance()->getCurrentSceneId();
    
    SceneController::getInstance()->switchSence(K_SCENE_BATTLEVIEW, dict,
                currentScene != K_SCENE_BATTLEVIEW ? SceneController::SwitchOptionPush : SceneController::SwitchOptionReplace);
    
}
