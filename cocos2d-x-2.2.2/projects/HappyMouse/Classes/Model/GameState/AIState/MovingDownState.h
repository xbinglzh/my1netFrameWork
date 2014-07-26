//
//  MovingDownState.h
//  HappyMouse
//
//  Created by xUanBing on 14-7-26.
//
//

#ifndef __HappyMouse__MovingDownState__
#define __HappyMouse__MovingDownState__

#include "cocos2d.h"
#include "GameState.h"
#include "GameEventParams.h"

class GameObject;

class MovingDownState:public GameState {
    
public:
    virtual void onEnterCallback(GameObject* obj);
    virtual void onExitCallback(GameObject* obj);
    virtual void updateCallback(GameObject* obj,const float dt);
    virtual bool onMessageCallback(GameObject* obj,const GameEventParams* params);
    
};

#endif /* defined(__HappyMouse__MovingDownState__) */
