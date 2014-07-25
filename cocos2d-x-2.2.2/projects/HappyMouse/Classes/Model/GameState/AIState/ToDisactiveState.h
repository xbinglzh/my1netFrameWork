//
//  ToDisactiveState.h
//  HappyMouse
//
//  Created by xUanBing on 14-7-26.
//
//

#ifndef __HappyMouse__ToDisactiveState__
#define __HappyMouse__ToDisactiveState__

#include "GameState.h"

class ToDisactiveState:public GameState {
    
public:
    virtual void onEnterCallback(GameObject * obj);
    virtual bool onMessageCallback(GameObject * obj,const GameEventParams * params);
    void gotoNextState(GameObject * obj,const int state);
    
private:
    void doReliveAnimation(GameObject* obj);
    void animReliveEndCallBack(cocos2d::CCObject* pSender);
};

#endif /* defined(__HappyMouse__ToDisactiveState__) */
