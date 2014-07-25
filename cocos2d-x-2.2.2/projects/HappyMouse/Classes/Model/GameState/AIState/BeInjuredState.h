//
//  BeInjuredState.h
//  HappyMouse
//
//  Created by xUanBing on 14-7-26.
//
//

#ifndef __HappyMouse__BeInjuredState__
#define __HappyMouse__BeInjuredState__

#include "GameState.h"

class BeInjuredState:public GameState {
    
public:
    virtual void onEnterCallback(GameObject * obj);
    virtual bool onMessageCallback(GameObject * obj,const GameEventParams * params);
    
};

#endif /* defined(__HappyMouse__BeInjuredState__) */
