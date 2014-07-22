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
#include "GameController.h"

USING_NS_CC;
USING_NS_CC_EXT;

class BattleLayer : public cocos2d::extension::CCScrollView {
    
public:
    BattleLayer();
    virtual ~BattleLayer();
    virtual bool init();
    CREATE_FUNC(BattleLayer);
    
public:
    bool updateGroundMap(const char* fileName,const char* bgfileName);
	inline GroundMap* getGroundMap(){return _groundMap;}
	const cocos2d::CCPoint& getPositionFromGroundMap( const std::list<int>::iterator & posIndex);
	virtual void onEnter();
    virtual void onExit();

private:
    
    GameController *        _gameController;
    GameModel *             _gameModel;
    GroundMap*              _groundMap;

    cocos2d::CCLayerColor*  _topLayer;
    cocos2d::CCLayer*       _xpEffectLayer;
    
//    XXBattleUI* _battleUI;
};

#endif /* defined(__HappyMouse__BattleLayer__) */
