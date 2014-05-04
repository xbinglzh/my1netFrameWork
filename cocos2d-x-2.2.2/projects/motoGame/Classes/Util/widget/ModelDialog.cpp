//
//  ModelDialog.cpp
//  MetalWar
//
//  Created by user on 12-11-8.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "ModelDialog.h"
#include <algorithm>

static bool compareTouchHandler(const void* pA, const void* pB) {
    CCTouchHandler* handerA = (CCTouchHandler*)pA;
    CCTouchHandler* handerB = (CCTouchHandler*)pB;
    return handerA->getPriority() <= handerB->getPriority();
}

ModelDialog::ModelDialog() : _minPriorityBeforeUpdated(0) {
    
}

ModelDialog::~ModelDialog() {

}

bool ModelDialog::initWithTouchPriority(int touchPriority) {
    if (super::init()) {
        setTouchPriority(touchPriority);
        setTouchMode(kCCTouchesOneByOne);
        setTouchEnabled(true);
        return true;
    }
    return false;
}

ModelDialog* ModelDialog::create(int touchPriority) {
    ModelDialog *pLayer = new ModelDialog(); 
    if (pLayer && pLayer->initWithTouchPriority(touchPriority))  {
        pLayer->autorelease();
        return pLayer;
    } 
    CC_SAFE_RELEASE_NULL(pLayer);
    return pLayer;
}

void ModelDialog::show() {
    CCScene* scene = CCDirector::sharedDirector()->getRunningScene();
    CCArray* children = scene->getChildren();
    int maxPriority = 0;
    if (children) {
        CCObject* obj = NULL;
        CCARRAY_FOREACH(children, obj) {
            ModelDialog* dlg = dynamic_cast<ModelDialog*>(obj);
            if (dlg) {
                dlg->getTouchPriority() < maxPriority ? maxPriority = dlg->getTouchPriority() : 0;
            }
        }
    }
    setTouchPriority(getTouchPriority() + maxPriority);
    scene->addChild(this, 65535);
}

void ModelDialog::dismiss() {
    removeFromParentAndCleanup(true);
}
    
void ModelDialog::onEnter() {
    super::onEnter();
    setTouchEnabled(true);
    scheduleOnce(SEL_SCHEDULE(&ModelDialog::updateTouchHandlerPriority), 0.0f);
}

void ModelDialog::onExit() {
    super::onExit();
    _minPriorityBeforeUpdated = 0;
}

void ModelDialog::updateTouchHandlerPriority(float dt) {
    CC_UNUSED_PARAM(dt);
    
    CCArray* touchHandlers = CCArray::create();
    traverseTouchHandler(this, touchHandlers);
    
    if (touchHandlers->count() == 0) {
        return;
    }
    
    ccArray* data = touchHandlers->data;
    std::sort(data->arr, data->arr + data->num, compareTouchHandler);
    int minPriority = ((CCTouchHandler*)data->arr[0])->getPriority();
    minPriority = minPriority > 0 ? getTouchPriority() - minPriority : getTouchPriority()  - 1;
    if (minPriority > getTouchPriority() - 1) {
        minPriority = INT_MIN;
    }
    
    _minPriorityBeforeUpdated = minPriority;
    
    CCTouchDispatcher* touchDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
    CCObject* obj = NULL;
    CCARRAY_FOREACH(touchHandlers, obj) {
        CCTouchHandler* handler = (CCTouchHandler*)obj;
        touchDispatcher->setPriority(handler->getPriority() + minPriority, handler->getDelegate());
    }
}

void ModelDialog::traverseTouchHandler(CCNode* node, CCArray* handlers) {
    CCAssert(handlers != NULL, "touchHandler container not be NULL.");
    
    if (!node) {
        return;
    }
    
    CCArray *children = node->getChildren();
    if (!children) {
        return;
    }
    
    CCTouchDispatcher *touchDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
    CCObject* child = NULL;
    CCARRAY_FOREACH(children, child) {
        traverseTouchHandler((CCNode*)child, handlers);
        CCTouchDelegate* touchDelgate = dynamic_cast<CCTouchDelegate*>(child);
        if (!touchDelgate) {
            continue;
        }
        
        CCTouchHandler *touchHandler = touchDispatcher->findHandler(touchDelgate);
        if (touchHandler) {
            handlers->addObject(touchHandler);
        }
    }
}

bool ModelDialog::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    return isVisible();
}

void ModelDialog::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    CC_UNUSED_PARAM(pTouch);
    CC_UNUSED_PARAM(pEvent);  
}

void ModelDialog::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    CC_UNUSED_PARAM(pTouch);
    CC_UNUSED_PARAM(pEvent);  
}

void ModelDialog::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    CC_UNUSED_PARAM(pTouch);
    CC_UNUSED_PARAM(pEvent);
}

void ModelDialog::addChild(cocos2d::CCNode * child) {
    super::addChild(child);
}

void ModelDialog::addChild(cocos2d::CCNode * child, int zOrder) {
    super::addChild(child, zOrder);
}

void ModelDialog::addChild(CCNode * child, int zOrder, int tag) {
    CCArray* touchHandlers = CCArray::create();
    traverseTouchHandler(this, touchHandlers);
    
    CCObject* obj = NULL;
    CCARRAY_FOREACH(touchHandlers, obj) {
        CCTouchHandler* handler = (CCTouchHandler*)obj;
        handler->setPriority(handler->getPriority() - _minPriorityBeforeUpdated);
    }
    _minPriorityBeforeUpdated = 0;
    
    super::addChild(child, zOrder, tag);
    
    if (m_bRunning) {
        scheduleOnce(SEL_SCHEDULE(&ModelDialog::updateTouchHandlerPriority), 0.0f);
    }
}
