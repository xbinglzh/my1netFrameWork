//
//  BattleLayer.h
//  HappyMouse
//
//  Created by xUanBing on 14-7-23.
//
//

#ifndef __HappyMouse__BattleLayer__
#define __HappyMouse__BattleLayer__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "GroundMap.h"
#include "GameModel.h"

USING_NS_CC;
USING_NS_CC_EXT;

class GameController;
class MonsterObject;
class PitObject;
class AnimNode;
class BattleUiView;

class BattleLayer : public CCLayer {
    
public:
    BattleLayer();
    virtual ~BattleLayer();
    virtual bool init();
    CREATE_FUNC(BattleLayer);
    virtual void onEnter();
    virtual void onExit();
    virtual void update(float dt);

    
public:
    bool updateGroundMap(BattleInfo& battleInfo);
	inline GroundMap* getGroundMap(){return _groundMap;}
//	const cocos2d::CCPoint& getPositionFromGroundMap( const std::list<int>::iterator & posIndex);
    
    void startBattleSendTroop(const int trropId);
    
    CCSet*  getCurInBattleTroop();
    
private:
    void updateGameMonster();
    
private:
    CCLayerColor* genLayerColor(int zOrder, int layerTag);
    
    void initMapBg(BattleInfo& battleInfo);
    void initMapPit(BattleInfo& battleInfo);
    
    MonsterObject* genRandomMonster(CCSet* monsterSet);
    PitObject*     genRandomPit();
    
private:  //*Touch*//
    
    virtual void registerWithTouchDispatcher(void);
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    

private:
    
    GameController*        _gameController;
    GroundMap*              _groundMap;
    BattleUiView*          _battleUiView;
    
    CCLayerColor*           _bottomLayer;             //底层贴图
    CCLayerColor*           _mapLayer;                //groundMap层
    CCLayerColor*           _topLayer;                //游戏上层
    CCLayerColor*           _xpEffectLayer;           //xp动画层
    CCLayerColor*           _battleUiLayer;           //UI控制层

    CCSet*                _curTrropMonsterInBattle;
    
};

#endif /* defined(__HappyMouse__BattleLayer__) */
