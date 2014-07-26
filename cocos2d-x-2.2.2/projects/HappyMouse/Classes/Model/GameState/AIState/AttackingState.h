//
//  AttackingState.h
//  HappyMouse
//
//  Created by xUanBing on 14-7-26.
//
//

#ifndef __HappyMouse__AttackingState__
#define __HappyMouse__AttackingState__

#include "GameState.h"

class AttackingState:public GameState {
    
public:
    virtual void onEnterCallback(GameObject * obj);
    virtual void onExitCallback(GameObject * obj);
    virtual void updateCallback(GameObject * obj,const float dt);
    virtual bool onMessageCallback(GameObject * obj,const GameEventParams * params);
    
};

#endif /* defined(__HappyMouse__AttackingState__) */
