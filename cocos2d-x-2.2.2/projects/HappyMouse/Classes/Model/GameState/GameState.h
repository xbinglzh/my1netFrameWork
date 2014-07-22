//
//  GameState.h
//  HappyMouse
//
//  Created by xUanBing on 14-7-22.
//
//

#ifndef __HappyMouse__GameState__
#define __HappyMouse__GameState__

#include <string.h>
#include "State.h"
#include "GameEventParams.h"

class GameObject;

//-------------------------------
//角色（卡牌和兵）类的状态，默认GameState
//-------------------------------
class GameState : public State {
    
public:
    ~GameState();
    /**
     继承自 State,GameState的子类无需重载该系列函数
     */
    void onEnter(const void * t);
    void onExit(const void * t);
    void update(const void * t,const float dt);
    bool onMessage(const void * t,const void * tdata);
    
    virtual bool onSuperMessageCallback(GameObject * obj,const GameEventParams * params,bool & isprivate);
    virtual void superUpdateCallback(GameObject * obj,const float dt);
    virtual bool runStateAnimation(GameObject * obj,int stateId);
    virtual void runStateAnimWithCallback(GameObject * obj,int stateId,const char * durationKey);
    
public:
    /**
     进入该状态
     */
    virtual void onEnterCallback(GameObject * obj);
    /**
     离开该状态
     */
    virtual void onExitCallback(GameObject * obj);
    /**
     定时执行的操作
     */
    virtual void updateCallback(GameObject * obj,const float dt);
    /**
     收到外部消息进行处理,如果返回true,该消息不再被其它人处理,obj == NULL的时候表示是一个全面广播消息
     */
    virtual bool onMessageCallback(GameObject * obj,const GameEventParams * params);
    
};


#endif /* defined(__HappyMouse__GameState__) */
