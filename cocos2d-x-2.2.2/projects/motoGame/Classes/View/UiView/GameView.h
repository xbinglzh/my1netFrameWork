//
//  GameView.h
//  motoGame
//
//  Created by xUanBing on 14-4-6.
//
//

#ifndef __motoGame__GameView__
#define __motoGame__GameView__

#include "cocos2d.h"
#include "LevelHelperLoader.h"

USING_NS_CC;

class GameView : public CCLayer {
    
public:
    GameView();
    ~GameView();
    virtual bool init();
    void initPhysicalWorld();
    virtual void update(float dt);
    virtual void draw();
    
    CREATE_FUNC(GameView);
protected:
    virtual void registerWithTouchDispatcher(void);
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
private:
    b2World *_b2World;
    LevelHelperLoader *_levelHelper;
    LHSprite *_lhSprite;
};

#endif /* defined(__motoGame__GameView__) */
