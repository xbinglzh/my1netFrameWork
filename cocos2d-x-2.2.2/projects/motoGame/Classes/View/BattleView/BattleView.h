//
//  BattleView.h
//  motoGame
//
//  Created by xUanBing on 14-4-24.
//
//

#ifndef __motoGame__BattleView__
#define __motoGame__BattleView__

#include "cocos2d.h"
#include "RootUiLayer.h"
#include "LevelHelperLoader.h"

class BattleUI;
class HeroSprite;
class GameController;

USING_NS_CC;

class BattleView : public CCLayer {
    
public:
    BattleView();
    ~BattleView();
    
    virtual bool init();
    virtual void initBattleUi();
    virtual void initPhysicalWorld();
    virtual void update(float dt);
    virtual void draw();
    
    CREATE_FUNC(BattleView);
    
protected:
    virtual void registerWithTouchDispatcher(void);
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
private:
    b2World* _physicsWorld;
    LevelHelperLoader* _levelHelperLoader;
    LHLayer* _lhLayer;
    
private:
    BattleUI* _battleUI;
    HeroSprite* _hero;
    
    GameController* _gameController;
};


#endif /* defined(__motoGame__BattleView__) */
