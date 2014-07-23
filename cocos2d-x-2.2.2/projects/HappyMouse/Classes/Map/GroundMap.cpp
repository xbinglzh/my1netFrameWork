//
//  GroundMap.cpp
//  HappyMouse
//
//  Created by xUanBing on 14-7-22.
//
//

#include "GroundMap.h"
#include "LayoutUtil.h"
#include "NotifyMessageDef.h"
#include "ConstansDef.h"

enum LayerZOrder {
    
    BaseLayerZorder               =  0,
    AdornBottomLayerZorder,
    GameLayerZorder,
    DropsLayerZorder,
    NpcLayerZorder,
    AdornTopLayerZorder,
    GuideLayerZorder,
    GrayLayerZorder
    
};

GroundMap::GroundMap() :
_baseLayer(NULL),
_adornBottomLayer(NULL),
_gameLayer(NULL),
_dropsLayer(NULL),
_npcLayer(NULL),
_adornTopLayer(NULL),
_guideLayer(NULL),
_grayLayer(NULL),
_mapId(-1) {
    
    CCNotificationCenter * nc = CCNotificationCenter::sharedNotificationCenter();
    nc->addObserver(this, callfuncO_selector(GroundMap::pauseBattle), KNotifyPauseBattleMessage, NULL);
    nc->addObserver(this, callfuncO_selector(GroundMap::resumeBattle), KNotifyBattleResumeMessage, NULL);
    
}

GroundMap::~GroundMap() {
    
    CCNotificationCenter * nc = CCNotificationCenter::sharedNotificationCenter();
    nc->removeObserver(this, KNotifyPauseBattleMessage);
    nc->removeObserver(this, KNotifyBattleResumeMessage);
    
}

GroundMap* GroundMap::create() {
    
    GroundMap* self = new GroundMap();
    
    if (self && self->initWithFile()) {
        self->autorelease();
        return self;
    }
    
    CC_SAFE_DELETE(self);
    return NULL;
}

bool GroundMap::initWithFile() {
    this->setContentSize(CCSizeMake(CCDirector::sharedDirector()->getOpenGLView()->getDesignResolutionSize().width, CCDirector::sharedDirector()->getOpenGLView()->getDesignResolutionSize().height));
    this->setAnchorPoint(CCPointZero);
    
    _baseLayer = genLayerColor(BaseLayerZorder, GroundMap_Base_Layer_Tag);
    _adornBottomLayer = genLayerColor(AdornBottomLayerZorder, GroundMap_Adorn_Bottom_Layer_Tag);
    _gameLayer = genLayerColor(GameLayerZorder, GroundMap_Game_Layer_Tag);
    _dropsLayer = genLayerColor(DropsLayerZorder, GroundMap_Drops_Layer_Tag);
    _npcLayer = genLayerColor(NpcLayerZorder, GroundMap_Npc_Layer_Tag);
    _adornTopLayer = genLayerColor(AdornTopLayerZorder, GroundMap_Adorn_Top_Layer_Tag);
    _guideLayer = genLayerColor(GuideLayerZorder, GroundMap_Guide_Layer_Tag);
    _grayLayer = genLayerColor(GrayLayerZorder, GroundMap_Gray_Layer_Tag);
    
    return true;
}

void GroundMap::pauseBattle() {
    changeLayerChildState(_gameLayer, true);
    changeLayerChildState(_dropsLayer, true);
    changeLayerChildState(_npcLayer, true);
    changeLayerChildState(_guideLayer, true);
}

void GroundMap::resumeBattle() {
    changeLayerChildState(_gameLayer, false);
    changeLayerChildState(_dropsLayer, false);
    changeLayerChildState(_npcLayer, false);
    changeLayerChildState(_guideLayer, false);
}

CCLayerColor* GroundMap::genLayerColor(int zOrder, int layerTag) {
    CCLayerColor* layer = CCLayerColor::create(ccc4(0, 0, 0, 0));
    layer->setAnchorPoint(CCPointZero);
    layer->setContentSize(this->getContentSize());
    this->addChild(layer, zOrder, layerTag);
    LayoutUtil::layoutParentBottomLeft(layer);
    
    return layer;
}

void GroundMap::topLayerTurnGray(bool isTurnGray) {
    if (_grayLayer) {
        _grayLayer->setOpacity(isTurnGray ? 120 : 0);
    }
}

void GroundMap::changeLayerChildState(CCNode* parent,bool isPause) {
    CCArray* array = NULL;
    CCObject* object = NULL;
    CCNode* child = NULL;
    
    if(parent) {
        array = parent->getChildren();
        CCARRAY_FOREACH(array, object) {
            child = (CCNode*)object;
            if(isPause)
                child->pauseSchedulerAndActions();
            else
                child->resumeSchedulerAndActions();
        }
    }
}

void GroundMap::setMapId(int MapId) {
    _mapId = MapId;
}

int GroundMap::getMapId() const {
    return _mapId;
}

CCLayerColor* GroundMap::getGroundMapLayerByTag(int tag) {
    return (CCLayerColor*)this->getChildByTag(tag);
}

