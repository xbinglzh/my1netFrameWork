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
#include "MouseObject.h"


#define TopPitOrder     1
#define MidNodeOrder    3
#define BottomPitOrder  5

#define TopPitTag       1
#define MidNodeTag      3
#define BottomPitTag    5

#define MouseTag        100


PitObject::PitObject() : _pit(NULL), _mouse(NULL){
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
    
    _mouse = MouseObject::create();
    this->addChild(_mouse, 1, MouseTag);
    
    LayoutUtil::layoutParentBottom(_mouse, 0, 30);
    
    return true;
}

void PitObject::judgePopMouse(cocos2d::CCObject *pSender) {
    CCInteger* id = (CCInteger*)pSender;
    
    if (id->getValue() == _pitId) {
        _mouse->changeMouseState(CCInteger::create(MouseArise));
    }
}

bool PitObject::strikenMouse(cocos2d::CCTouch *pTouch) {
    return _mouse->strikenMouse(pTouch);
}


