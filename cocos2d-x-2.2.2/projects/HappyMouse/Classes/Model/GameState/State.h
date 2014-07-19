//
//  State.h
//  HappyMouse
//
//  Created by xUanBing on 14-7-19.
//
//

#ifndef __HappyMouse__State__
#define __HappyMouse__State__

class State {
    
public:
    State():_stateId(-1){}
    virtual ~State(){}
    
	/*切换到该状态的时候调用*/
	virtual void onEnter(const void * t){}
    
	/*切出该状态的时候调用*/
	virtual void onExit(const void * t){}
    
    /*状态的循环调用*/
	virtual void update(const void * t,const float dt){}
    
	/*外部传入的消息*/
	virtual bool onMessage(const void * t,const void * tdata){return false;}
    
private:
    int _stateId;
    
public:
    void setStateId(const int value){ _stateId = value;}
    int getStateId()const{ return _stateId;}
    
};


#endif /* defined(__HappyMouse__State__) */
