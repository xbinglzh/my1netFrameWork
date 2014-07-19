//
//  StateMachine.h
//  HappyMouse
//
//  Created by xUanBing on 14-7-19.
//
//

#ifndef __HappyMouse__StateMachine__
#define __HappyMouse__StateMachine__

#include <map>
#include <set>

#include "cocos2d.h"

class State;


class StateMachine {
    
public:
    typedef std::map<int32_t, State*> StateMachineMap;
    
public:
    StateMachine();
    ~StateMachine();
    /**
     获得当前状态
     */
    virtual const State* getCurrentState();
    
    /**
     获得当前状态的id 取值范围:EGameObjectStateId
     */
    virtual const int32_t getCurrentStateId();
    
    void dumpStates();
    /**
     添加一个状态:State* t
     对应的状态类型是id
     */
    virtual void addState(const int32_t id,
                          const State* t,
                          const bool isAdditionState = false,
                          const void* g = NULL);
    
    /**
     去除掉一个状态
     */
    virtual void removeState(const int32_t id,
                             const bool isAdditionState = false,
                             const void* g = NULL);
    
    /**
     更改到某个状态
     g 为状态作用到的实体
     */
	virtual void changeState(const void* g, const int32_t id);
    
    /**
     处理收到的消息
     g 为消息作用到的实体
     d 为消息体
     */
	virtual bool onMessage(const void* g, const void* d);
    
    /**
     刷新状态机
     */
    virtual void update(const void* g, float dt);
    
    State* findAdditionState(const int32_t id);
    State* findState(const int32_t id);
    
private:
    StateMachineMap _states; //State* 不被_states持有
    int32_t         _currentState;
    StateMachineMap _additionStates;
    
};


#endif /* defined(__HappyMouse__StateMachine__) */
