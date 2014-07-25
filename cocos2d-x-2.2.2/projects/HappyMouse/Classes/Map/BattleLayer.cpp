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
#include "AnimUtils.h"

#define Bottom_Layer_Tag          1001
#define Map_Layer_Tag             1002
#define Top_Layer_Tag             1003
#define XpEffect_Layer_Tag        1004
#define BattleUi_Layer_Tag        1005

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
_mapLayer(NULL) ,
_monsterArray(NULL) {
    
}

BattleLayer::~BattleLayer() {
    removeAllChildrenWithCleanup(true);
    sp::ArmatureDataManager::sharedArmatureDataManager()->removeUnusedAnimations();

    CCObject * obj = NULL;
    
    CCARRAY_FOREACH(_monsterArray, obj){
        CC_SAFE_RELEASE_NULL(obj);
    }
    
    _monsterArray->release() ;
}

bool BattleLayer::init() {
    this->setContentSize(CCSizeMake(CCDirector::sharedDirector()->getOpenGLView()->getDesignResolutionSize().width, CCDirector::sharedDirector()->getOpenGLView()->getDesignResolutionSize().height));
    this->setAnchorPoint(CCPointZero);
    
    _gameController = GameController::getInstance();
    
    _monsterArray = CCArray::create();
    _monsterArray->retain();
    
    _bottomLayer = genLayerColor(BottomLayerZorder, Bottom_Layer_Tag);
    _mapLayer = genLayerColor(MapLayerZorder, Map_Layer_Tag);
    _topLayer = genLayerColor(TopLayerZorder, Top_Layer_Tag);
    _xpEffectLayer = genLayerColor(XpEffectLayerZorder, XpEffect_Layer_Tag);
    _battleUiLayer = genLayerColor(BattleUiLayerZorder, BattleUi_Layer_Tag);
    
    _groundMap = GroundMap::create();
    _mapLayer ->addChild(_groundMap);
    LayoutUtil::layoutParentBottom(_groundMap);
    
    this->scheduleUpdate();
    
    CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(BattleLayer::updateGameMonster),this, 0.5,kCCRepeatForever, 5.0f, false);
    
    return true;
}

void BattleLayer::onEnter() {
    CCLayer::onEnter();
}

void BattleLayer::onExit() {
    CCLayer::onEnter();
}

void BattleLayer::update(float dt) {
    
    GameController::getInstance()->update(dt);
}

bool BattleLayer::updateGroundMap(BattleInfo& battleInfo) {
    //Map ---
    initMapBg(battleInfo);
    initMapPit(battleInfo);
    
    return true;
}

void BattleLayer::initMapBg(BattleInfo &battleInfo) {
    CCLayer* groundMap_baseLayer = _groundMap->getGroundMapLayerByTag(GroundMap_Base_Layer_Tag);
    
    const char* mapBg = static_cast<CCString*>(battleInfo.getMapDict()->objectForKey(KKeyMapBg))->getCString();
    
    CCSpriteExt* bgSprite = CCSpriteExt::create(mapBg);
    bgSprite->setScaleX(groundMap_baseLayer->getContentSize().width / bgSprite->getContentSize().width);
    bgSprite->setScaleY(groundMap_baseLayer->getContentSize().height / bgSprite->getContentSize().height);
    groundMap_baseLayer->addChild(bgSprite);
    LayoutUtil::layoutParentBottom(bgSprite);
}

void BattleLayer::initMapPit(BattleInfo &battleInfo) {
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

//------------------------ start Troop -------------------------
void BattleLayer::startTroop(const int trropId) {
    CCSet* trropMonster = GameModel::getInstance()->findMonsterInTroop(trropId);
    
}

MonsterObject* BattleLayer::genRandomMonster(CCSet* monsterSet) {
    
    MonsterObject* randomMObj = NULL;
    
    int randomIndex = rand() % monsterSet->count();
    
    CCSetIterator iter; int j = 0;
    
    for (iter = monsterSet->begin(); iter != monsterSet->end(); ++iter) {
        MonsterObject* mObj = (MonsterObject *)(*iter);
        
        if (j == randomIndex) {
            randomMObj = mObj;
        }
        
        j++;
    }
    
    if ( !randomMObj || randomMObj->getMonsterDetail()._hp == 0 || randomMObj->isAddParent()) {
        return genRandomMonster(monsterSet);
    }
    
    return randomMObj;
}


int randomCount;

PitObject* BattleLayer::genRandomPit() {
    CCLayer* groundMap_gameLayer = _groundMap->getGroundMapLayerByTag(GroundMap_Game_Layer_Tag);
    int randomTag = rand() % groundMap_gameLayer->getChildrenCount();
    PitObject* pitObj = (PitObject*)groundMap_gameLayer->getChildByTag(randomTag);
    
    if (randomCount <= 0) {
        return NULL;
    }
    
    if (pitObj && pitObj->isAddMonster()) {
        randomCount--;
        return genRandomPit();
    }
    
    return pitObj;
}

void BattleLayer::updateGameMonster() {
    randomCount = 3;
    PitObject* pit = genRandomPit();
    
    if (pit) {
        MonsterObject* addMonster =(MonsterObject*) pit->getChildByTag(MouseTag);
        
        if(addMonster)
            addMonster->setIsAddParent(false);
        
        pit->removeChildByTag(MouseTag, false);
        
        CCSet* trropMonster = GameModel::getInstance()->findMonsterInTroop(950001);
        
        MonsterObject* monster = genRandomMonster(trropMonster);
        
        if (monster) {
            pit->addChild(monster, 1, MouseTag);
            monster->setIsAddParent(true);
            LayoutUtil::layoutParentCenter(monster);
        }
    }

}




