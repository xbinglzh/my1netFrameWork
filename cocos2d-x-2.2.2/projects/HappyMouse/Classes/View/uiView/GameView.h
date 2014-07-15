//
//  GameView.h
//  HappyMouse
//
//  Created by xUanBing on 14-7-15.
//
//

#ifndef __HappyMouse__GameView__
#define __HappyMouse__GameView__

#include "cocos2d.h"

USING_NS_CC;

class CCSpriteExt;

class GameView : public CCLayer {
    
public:
    GameView();
    ~GameView();
    
    static GameView* create();
    virtual bool init();
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    
    void update(float dt);
    
private:
    void initPitData();
    void initMouseData();
    
private:
    CCSpriteExt* _bg;
    CCNode*      _pitNode;
    CCNode*      _mouseNode;
    
};

#endif /* defined(__HappyMouse__GameView__) */
