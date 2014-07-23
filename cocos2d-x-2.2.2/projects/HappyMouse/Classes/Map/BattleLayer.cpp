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
    
    
    return true;
}

void BattleLayer::onEnter() {
    
}

void BattleLayer::onExit() {
    
}

bool BattleLayer::updateGroundMap(const char* mapBg,const char* mapPic) {
    
    
    return true;
}

CCLayerColor* BattleLayer::genLayerColor(int zOrder, int layerTag) {
    CCLayerColor* layer = CCLayerColor::create(ccc4(0, 0, 0, 0));
    layer->setAnchorPoint(CCPointZero);
    layer->setContentSize(this->getContentSize());
    this->addChild(layer, zOrder, layerTag);
    LayoutUtil::layoutParentBottomLeft(layer);
    
    return layer;
}

