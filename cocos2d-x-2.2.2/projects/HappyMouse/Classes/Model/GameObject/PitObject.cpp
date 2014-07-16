//
//  PitObject.cpp
//  HappyMouse
//
//  Created by xUanBing on 14-7-15.
//
//

#include "PitObject.h"
#include "CCScale9ProgressBar.h"
#include "CCSpriteExt.h"
#include "LayoutUtil.h"
#include "NotifyMessageDef.h"


#define TopPitOrder     1
#define MidNodeOrder    3
#define BottomPitOrder  5

#define TopPitTag       1
#define MidNodeTag      3
#define BottomPitTag    5

#define MouseTag        100


PitObject::PitObject() : _pit(NULL), _isArise(false){
    
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(PitObject::judgePopMouse), KNotifyMousePop, NULL);
}

PitObject::~PitObject() {
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, KNotifyMousePop);
}

PitObject* PitObject::create(int pitId) {
    PitObject* obj = new PitObject();
    
    if (obj && obj->init(pitId)) {
        obj->autorelease();
        return obj;
    } else {
        CC_SAFE_DELETE(obj);
        return NULL;
    }
    
}

bool PitObject::init(int pitId) {
    
    this->_pitId = pitId;
    
    _pit = CCSpriteExt::create("grass_pit.png");
    this->setContentSize(_pit->getContentSize());
    this->addChild(_pit);
    LayoutUtil::layoutParentBottom(_pit);
    
    return true;
}

void PitObject::addNodeToContent(cocos2d::CCNode *node) {
    
    //绘制裁剪区域
    CCDrawNode* shap = CCDrawNode::create();
    
    CCPoint point[4] = {ccp(0,0), ccp(node->getContentSize().width, 0), ccp(node->getContentSize().width, node->getContentSize().height), ccp(0, node->getContentSize().height)};
    
    shap->drawPolygon(point, 4, ccc4f(355, 255, 255, 255), 2, ccc4f(255, 255, 255, 255));
    
    CCClippingNode* cliper = CCClippingNode::create();
    cliper->setStencil(shap);
    cliper->setAnchorPoint(ccp(0, 0));
    cliper->setContentSize(node->getContentSize());
    
    cliper->addChild(node, 1, MouseTag);
    
    this->addChild(cliper, MidNodeOrder, MidNodeTag);

    LayoutUtil::layoutParentBottom(cliper, 0, 30);
    LayoutUtil::layoutParentBottom(node, 0 , -1 * node->getContentSize().height);
    
}

void PitObject::judgePopMouse(cocos2d::CCObject *pSender) {
    CCInteger* id = (CCInteger*)pSender;
    
    if (id->getValue() == _pitId) {
        ariseMouse();
    }
}

void PitObject::dropMouse() {
    if (!_isArise) {
        return;
    }
    
    CCNode* targetNode = this->getChildByTag(MidNodeTag)->getChildByTag(MouseTag);
    
    CCMoveBy* ation_moveTo = CCMoveBy::create(0.5f, CCPointMake(0, -1 * targetNode->getContentSize().height));
    CCCallFuncN* action_call = CCCallFuncN::create(this, callfuncN_selector(PitObject::resetAriseFlag));
    
    targetNode->runAction(CCSequence::create(ation_moveTo, action_call, NULL));
}

void PitObject::resetAriseFlag() {
    _isArise = false;
}

void PitObject::ariseMouse() {
    
    if (_isArise) {
        return;
    }
    
    CCNode* targetNode = this->getChildByTag(MidNodeTag)->getChildByTag(MouseTag);
    
    _isArise = true;
    
    CCMoveBy* ation_moveTo = CCMoveBy::create(0.3f, CCPointMake(0, targetNode->getContentSize().height));
    CCDelayTime* action_delay = CCDelayTime::create(0.5f);
    CCFiniteTimeAction *action_call = CCCallFuncN::create(this, callfuncN_selector(PitObject::dropMouse));
    
    targetNode->runAction(CCSequence::create(CCSequence::create(ation_moveTo,action_delay,action_call,NULL),NULL));
}

bool PitObject::isHitMouse(cocos2d::CCTouch *pTouch) {
    
    CCNode* midNode = this->getChildByTag(MidNodeTag);
    CCPoint pt = midNode->convertToNodeSpace(pTouch->getLocation());
    CCNode* mouse = midNode->getChildByTag(MouseTag);
    
    if (mouse && mouse->boundingBox().containsPoint(pt)) {
        return true;
    }
    
    return false;
}



