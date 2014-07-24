//
//  BattleLayer.cpp
//  HappyMouse
//
//  Created by xUanBing on 14-7-23.
//
//

#include "BattleLayer.h"
#include "SPArmatureDataManager.h"
#include "LayoutUtil.h"
#include "CCSpriteExt.h"
#include "GameController.h"
#include "PitObject.h"
#include "ConstansDef.h"
#include "GameController.h"
#include "GameUtils.h"
#include "MonsterObject.h"

#define Bottom_Layer_Tag          100001
#define Map_Layer_Tag             100002
#define Top_Layer_Tag             100003
#define XpEffect_Layer_Tag        100004
#define BattleUi_Layer_Tag        100005

enum LayerZOrder {
    
    BottomLayerZorder               =  0,
    MapLayerZorder,
    TopLayerZorder,
    XpEffectLayerZorder,
    BattleUiLayerZorder
    
};

BattleLayer::BattleLayer() :
_gameController(NULL),
_bottomLayer(NULL),
_battleUiLayer(NULL),
_xpEffectLayer(NULL),
_topLayer(NULL),
_groundMap(NULL),
_mapLayer(NULL) {
    
}

BattleLayer::~BattleLayer() {
    removeAllChildrenWithCleanup(true);
    sp::ArmatureDataManager::sharedArmatureDataManager()->removeUnusedAnimations();
    
//    for (int i = 0; i < _monsterVector.size(); i++) {
//        MonsterObject* obj = _monsterVector.at(i);
//        
//    }
    
    _monsterVector.clear();
    
}

bool BattleLayer::init() {
    this->setContentSize(CCSizeMake(CCDirector::sharedDirector()->getOpenGLView()->getDesignResolutionSize().width, CCDirector::sharedDirector()->getOpenGLView()->getDesignResolutionSize().height));
    this->setAnchorPoint(CCPointZero);
    
    _gameController = GameController::getInstance();
    
    _bottomLayer = genLayerColor(BottomLayerZorder, Bottom_Layer_Tag);
    _mapLayer = genLayerColor(MapLayerZorder, Map_Layer_Tag);
    _topLayer = genLayerColor(TopLayerZorder, Top_Layer_Tag);
    _xpEffectLayer = genLayerColor(XpEffectLayerZorder, XpEffect_Layer_Tag);
    _battleUiLayer = genLayerColor(BattleUiLayerZorder, BattleUi_Layer_Tag);
    
    _groundMap = GroundMap::create();
    _mapLayer ->addChild(_groundMap);
    LayoutUtil::layoutParentBottom(_groundMap);
    
    CCDirector::sharedDirector()->getScheduler()->scheduleUpdateForTarget(this, 0, false);
    CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(BattleLayer::updateGameMonster),this, 0.5,kCCRepeatForever, 5.0f, false);
    
    return true;
}

void BattleLayer::onEnter() {
    
}

void BattleLayer::onExit() {
    
}

void BattleLayer::update(float dt) {
    
    GameController::getInstance()->update(dt);
    
}

bool BattleLayer::updateGroundMap(BattleInfo& battleInfo) {
    //Map ---
    updateMapBg(battleInfo);
    updateMapPit(battleInfo);
    //Attack Team --
    updateAttackTeam(battleInfo);
    
    
    return true;
}

void BattleLayer::updateMapBg(BattleInfo &battleInfo) {
    CCLayer* groundMap_baseLayer = _groundMap->getGroundMapLayerByTag(GroundMap_Base_Layer_Tag);
    
    const char* mapBg = static_cast<CCString*>(battleInfo.getMapDict()->objectForKey(KKeyMapBg))->getCString();
    
    CCSpriteExt* bgSprite = CCSpriteExt::create(mapBg);
    bgSprite->setScaleX(groundMap_baseLayer->getContentSize().width / bgSprite->getContentSize().width);
    bgSprite->setScaleY(groundMap_baseLayer->getContentSize().height / bgSprite->getContentSize().height);
    groundMap_baseLayer->addChild(bgSprite);
    LayoutUtil::layoutParentBottom(bgSprite);
}

void BattleLayer::updateMapPit(BattleInfo &battleInfo) {
    CCLayer* groundMap_gameLayer = _groundMap->getGroundMapLayerByTag(GroundMap_Game_Layer_Tag);
    float gridWidth = groundMap_gameLayer->getContentSize().width / MapXGridNum;
    float gridHeight = groundMap_gameLayer->getContentSize().height / MapYGridNum;
    
    CCDictionary* mapDataDict = battleInfo.getMapDataDict();
    CCDictElement * dataElement = NULL;
    
    int pitId = 0;
    
    CCDICT_FOREACH(mapDataDict, dataElement){
        std::string key = dataElement->getStrKey();
        CCString* value = static_cast<CCString*>(dataElement->getObject());
        size_t startPos = std::string::npos;
        
//        CCLOG("key : %s, value %s",key.c_str(), value->getCString());
        
        std::string srcString = key;
        srcString = srcString.substr(1,(srcString.length() - 1));
        startPos = srcString.find_first_of(",");
        int x = atoi(srcString.substr(0,startPos).c_str()) - 1;
        srcString = srcString.substr(startPos + 1,(srcString.length() - startPos));
        int y = atoi(srcString.substr(0,(srcString.length() - 1)).c_str()) - 1;
        
        CCLOG("x :%d, y : %d", x, y);
        
        CCString* pitImg = static_cast<CCString*>(GameConfig::getInstance()->getMapPitById(value->getCString())->objectForKey(KKeyPitImg));
        
        PitObject* pit = PitObject::create(pitId, pitImg->getCString());
        pitId ++;
        
        groundMap_gameLayer->addChild(pit, 10, pitId);
        LayoutUtil::layoutParentTopLeft(pit, x * gridWidth, -1 * y * gridHeight);
        
    }
    
}

CCLayerColor* BattleLayer::genLayerColor(int zOrder, int layerTag) {
    CCLayerColor* layer = CCLayerColor::create(ccc4(0, 0, 0, 0));
    layer->setAnchorPoint(CCPointZero);
    layer->setContentSize(this->getContentSize());
    this->addChild(layer, zOrder, layerTag);
    LayoutUtil::layoutParentBottomLeft(layer);
    
    return layer;
}

void BattleLayer::updateAttackTeam(BattleInfo &battleInfo) {
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

void BattleLayer::updateMonsterTroop(cocos2d::CCDictionary *troopDict) {
    
    std::stringstream sstmMonsterId;
    std::stringstream sstmMonsterNum;
    
    CCString* monsterCount = static_cast<CCString*>(troopDict->objectForKey(KKeyMonsterCount));
    
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
            _monsterVector.push_back(monsterObj);
            
        }
    }

}

MonsterObject* BattleLayer::genRandomMonster() {
    MonsterObject* monsterObj = _monsterVector.at(rand() % _monsterVector.size());
    return monsterObj;
}

PitObject* BattleLayer::genRandomPit() {
    CCLayer* groundMap_gameLayer = _groundMap->getGroundMapLayerByTag(GroundMap_Game_Layer_Tag);
    int randomTag = rand() % groundMap_gameLayer->getChildrenCount();
    PitObject* pitObj = (PitObject*)groundMap_gameLayer->getChildByTag(randomTag);
    return pitObj;
}

void BattleLayer::updateGameMonster() {
    PitObject* pit = genRandomPit();
    pit->removeChildByTag(MouseTag);
    
    MonsterObject* monster = genRandomMonster();
    
    pit->addChild(monster, 1, MouseTag);
//    LayoutUtil::layoutParentCenter(monster);
}




