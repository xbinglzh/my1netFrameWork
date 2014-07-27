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
#include "ConstansDef.h"
#include "MonsterObject.h"


#define TopPitOrder     1
#define MidNodeOrder    3
#define BottomPitOrder  5

#define TopPitTag       1
#define MidNodeTag      3
#define BottomPitTag    5


PitObject::PitObject() : _pit(NULL), _isAddMonster(false) {
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(PitObject::judgePopMouse), KNotifyMousePop, NULL);
}

PitObject::~PitObject() {
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, KNotifyMousePop);
    _isAddMonster = false;
}

PitObject* PitObject::create(int pitId,const char* pitImg) {
    PitObject* obj = new PitObject();
    
    if (obj && obj->init(pitId, pitImg)) {
        obj->autorelease();
        return obj;
    } else {
        CC_SAFE_DELETE(obj);
        return NULL;
    }
    
}

bool PitObject::init(int pitId,const char* pitImg) {

    this->_pitId = pitId;
    
    _pit = CCSpriteExt::create(pitImg);
    this->setContentSize(_pit->getContentSize());
    this->addChild(_pit);
    LayoutUtil::layoutParentBottom(_pit);
    
    return true;
}

void PitObject::judgePopMouse(cocos2d::CCObject *pSender) {
    
}

bool PitObject::strikenMouse(cocos2d::CCTouch *pTouch) {
    MonsterObject* mObj =(MonsterObject*) this->getChildByTag(MouseTag);
    
    if (!mObj) {
        return false;
    }
    
    return mObj->strikenMouse(pTouch);
}

bool PitObject::isAddMonster() {
    return _isAddMonster;
}

void PitObject::setIsAddMonster(bool isAddMonster) {
    this->_isAddMonster = isAddMonster;
}


