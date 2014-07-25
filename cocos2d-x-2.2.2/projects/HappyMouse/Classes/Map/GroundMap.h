//
//  GroundMap.h
//  HappyMouse
//
//  Created by xUanBing on 14-7-22.
//
//

#ifndef __HappyMouse__GroundMap__
#define __HappyMouse__GroundMap__

#include "cocos2d.h"

USING_NS_CC;

class GroundMap : public cocos2d::CCNode {
    
public:
    GroundMap();
    virtual ~GroundMap();
    
public:
    static GroundMap* create();
    
public:
    bool initWithFile();
    
public:
    void pauseBattle();
    void resumeBattle();
    void changeLayerChildState(CCNode* parent,bool isPause);

public:
    void setMapId(int MapId);
    int  getMapId() const;
    CCLayerColor* getGroundMapLayerByTag(int tag);
    
private:
    CCLayerColor* genLayerColor(int zOrder, int layerTag);
    void topLayerTurnGray(bool isTurnGray);
    
private:
    CCLayerColor*  _baseLayer;         //  基础Layer, 存放最底层背景
    CCLayerColor*  _adornBottomLayer;  //  修饰层，背景修饰层面
    
    CCLayerColor*  _gameLayer;         //  游戏层
    CCLayerColor*  _dropsLayer;        //  掉落层
    CCLayerColor*  _npcLayer;          //  npc层
    
    CCLayerColor*  _adornTopLayer;     //  上层修饰
    CCLayerColor*  _guideLayer;        //  新手引导层
    CCLayerColor*  _grayLayer;         //  灰色遮罩
    
    int _mapId;
};


#endif /* defined(__HappyMouse__GroundMap__) */
