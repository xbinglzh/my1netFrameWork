//
//  IdleState.h
//  HappyMouse
//
//  Created by xUanBing on 14-7-26.
//
//

#ifndef __HappyMouse__IdleState__
#define __HappyMouse__IdleState__

#include "GameState.h"

class IdleState:public GameState {
    
public:
    virtual void onEnterCallback(GameObject * obj);
    virtual bool onMessageCallback(GameObject * obj,const GameEventParams * params);
    
};

#endif /* defined(__HappyMouse__IdleState__) */
