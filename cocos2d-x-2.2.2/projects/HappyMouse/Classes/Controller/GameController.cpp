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
#include "GameModel.h"
#include "MonsterObject.h"

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
    GameModel::getInstance()->update(dt);
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

void GameController::resetBattleLayer(BattleLayer *battleLayer, cocos2d::CCDictionary *dict) {
    CCString * battleZoneId = static_cast<CCString *>(dict->objectForKey(KStrBattleZoneId));
    CCString * stageId = static_cast<CCString *>(dict->objectForKey(KStrBattleId));
    
    GameModel::getInstance()->clearCache();
    GameModel::getInstance()->resetBattlelayer(battleLayer);
    
    updateBattleInfo(battleZoneId->intValue(), stageId->intValue());
    
    battleLayer->updateGroundMap(GameModel::getInstance()->getBattleInfo());
    
    updateAttackTeam();
}

void GameController::updateBattleInfo(const int32_t battleZoneId,const int32_t stageId){
    BattleInfo& battleInfo = GameModel::getInstance()->getBattleInfo();
    battleInfo.initWithConfig(battleZoneId, stageId);
}

void GameController::updateAttackTeam() {
    BattleInfo& battleInfo = GameModel::getInstance()->getBattleInfo();
    
    CCDictionary* attackTeam = battleInfo.getAttackTeamDict();
    CCString* troopMaxSize = static_cast<CCString*>(attackTeam->objectForKey(KKeyTroop_max_size));
    
    std::stringstream sstmTroop;
    std::stringstream sstmTroopDifficulty;
    
    
    for (int i = 0; i < troopMaxSize->intValue(); i++) {
        sstmTroop << "troop_" << i + 1;
        sstmTroopDifficulty << "troop_" << i + 1 <<"_difficulty" ;
        
        std::string keyTroop = sstmTroop.str();
        std::string keyTroopDifficulty = sstmTroopDifficulty.str();
        
        CCString* troopId = static_cast<CCString*>(attackTeam->objectForKey(keyTroop));
        //        CCString* troopDifficulty = static_cast<CCString*>(attackTeam->objectForKey(keyTroopDifficulty));//难度系数
        
        CCDictionary* troop = GameConfig::getInstance()->getTroopById(troopId->getCString());
        updateMonsterTroop(troop);
    }
    
}

void GameController::updateMonsterTroop(cocos2d::CCDictionary *troopDict) {
    std::stringstream sstmMonsterId;
    std::stringstream sstmMonsterNum;
    
    CCString* monsterCount = static_cast<CCString*>(troopDict->objectForKey(KKeyMonsterCount));
    CCString* troopId = static_cast<CCString*>(troopDict->objectForKey(KKeyId));
    
    for (int j = 0; j < monsterCount->intValue(); j++) {
        sstmMonsterId << "monster_" << j + 1 << "_id";
        sstmMonsterNum<<"monster_" << j + 1 << "_num";
        
        std::string monsterId = sstmMonsterId.str();
        std::string monsterNum = sstmMonsterNum.str();
        
        CCString* monsterValue = static_cast<CCString*>(troopDict->objectForKey(monsterId.c_str()));
        CCString* monsterNumValue = static_cast<CCString*>(troopDict->objectForKey(monsterNum.c_str()));
        
        CCLOG("monsterId : %s, monsterNum : %s", monsterValue->getCString(), monsterNumValue->getCString());
        CCDictionary* monsterDict = GameConfig::getInstance()->getTemplateValue(monsterValue->intValue());
        
        for (int k = 0; k < monsterNumValue->intValue(); k++) {
            MonsterObject* monsterObj = MonsterObject::create(monsterDict);
            GameModel::getInstance()->addMonsterToTroop(monsterObj, troopId->intValue());
        }
        
    }

}



