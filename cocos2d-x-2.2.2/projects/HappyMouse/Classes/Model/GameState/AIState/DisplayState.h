//
//  DisplayState.h
//  HappyMouse
//
//  Created by xUanBing on 14-7-22.
//
//

#ifndef __HappyMouse__DisplayState__
#define __HappyMouse__DisplayState__

#include "GameState.h"

class DisplayState : public GameState {
    
public:
    virtual void onEnterCallback(GameObject * obj);
    virtual bool onMessageCallback(GameObject * obj,const GameEventParams * params);
    
};

#endif /* defined(__HappyMouse__DisplayState__) */
