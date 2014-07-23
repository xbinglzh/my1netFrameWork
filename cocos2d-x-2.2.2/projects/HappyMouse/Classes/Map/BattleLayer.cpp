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
    
    return true;
}

void BattleLayer::onEnter() {
    
}

void BattleLayer::onExit() {
    
}

bool BattleLayer::updateGroundMap(BattleInfo& battleInfo) {
    updateMapBg(battleInfo);
    updateMapPit(battleInfo);
    
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
    CCLOG("w: %f, h: %f", gridWidth, gridHeight);
    
    CCDictionary* mapDataDict = battleInfo.getMapDataDict();
    CCDictElement * dataElement = NULL;
    
    int pitId = 0;
    
    CCDICT_FOREACH(mapDataDict, dataElement){
        std::string key = dataElement->getStrKey();
        CCString* value = static_cast<CCString*>(dataElement->getObject());
        size_t startPos = std::string::npos;
        
        CCLOG("key : %s, value %s",key.c_str(), value->getCString());
        
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

