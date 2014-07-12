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
class GameBgRollView;

USING_NS_CC;

class BattleView : public CCLayer {
    
public:
    enum SceneState {
        nullScene,
        startScene,
        accelerateScene,
        pauseScene,
    };
    
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
    void postCollisionBetweenHeroAndCoin(LHContactInfo* contact);
    void postCollisionBetweenHeroAndFloor(LHContactInfo* contact);
    void postCollisionBetweenHeroAndTree(LHContactInfo* contact);
    void postCollisionBetweenHeroAndBottomBorder(LHContactInfo* contact);
    
private:
    void onNotifyBattleStartMessage(CCObject* pSender);
    void onNotifyBattlePauseMessage(CCObject* pSender);
    void onNotifyEnergyFullMessage(CCObject* pSender);
    void onNotifyEnergyEmptyMessage(CCObject* pSender);
    
private:
    void changeSceneState(SceneState state);
    
private:
    b2World* _physicsWorld;
    LevelHelperLoader* _levelHelperLoader;
    LHLayer* _lhLayer;
    LHParallaxNode*  _gameParallaxLayer;
    
private:
    BattleUI*        _battleUI;
    GameController*  _gameController;
    GameBgRollView*  _rollView;
private:
    SceneState       _curSceneState;
};


#endif /* defined(__motoGame__BattleView__) */
