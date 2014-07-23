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
    virtual void onEnter();
    virtual void onExit();
    
public:
    bool updateGroundMap(const char* mapBg,const char* mapPic);
	inline GroundMap* getGroundMap(){return _groundMap;}
//	const cocos2d::CCPoint& getPositionFromGroundMap( const std::list<int>::iterator & posIndex);
    
private:
    CCLayerColor* genLayerColor(int zOrder, int layerTag);

private:
    
    GameController *        _gameController;
//    GameModel*              _gameModel;
    GroundMap*              _groundMap;
    
    CCLayerColor*           _bottomLayer;             //底层贴图
    CCLayerColor*           _mapLayer;                //groundMap层
    CCLayerColor*           _topLayer;                //游戏上层
    CCLayerColor*           _xpEffectLayer;           //xp动画层
    CCLayerColor*           _battleUiLayer;           //UI控制层
    
//    XXBattleUI* _battleUI;
    
};

#endif /* defined(__HappyMouse__BattleLayer__) */
