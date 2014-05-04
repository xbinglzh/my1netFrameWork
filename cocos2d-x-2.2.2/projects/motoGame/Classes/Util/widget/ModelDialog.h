//
//  ModelDialog.h
//  MetalWar
//
//  Created by user on 12-11-8.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef MetalWar_ModelDialog_h
#define MetalWar_ModelDialog_h

#include "cocos2d.h"

USING_NS_CC;

class ModelDialog : public cocos2d::CCLayerColor {
    
private:
    typedef cocos2d::CCLayerColor super;
    
public:
    ~ModelDialog();
    static ModelDialog* create(int touchPriority = -1024);
    
protected:
    ModelDialog();
    bool initWithTouchPriority(int touchPriority = -1024);
    
public:
    void show();
    void dismiss();
    virtual void addChild(cocos2d::CCNode * child);
    virtual void addChild(cocos2d::CCNode * child, int zOrder);
    virtual void addChild(cocos2d::CCNode * child, int zOrder, int tag);

protected:
    virtual void onEnter();
    virtual void onExit();
    
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
        
private:
    void updateTouchHandlerPriority(float dt);
    void traverseTouchHandler(cocos2d::CCNode* node, cocos2d::CCArray* handler);
    
private:
    int _minPriorityBeforeUpdated;
    
};


#endif
