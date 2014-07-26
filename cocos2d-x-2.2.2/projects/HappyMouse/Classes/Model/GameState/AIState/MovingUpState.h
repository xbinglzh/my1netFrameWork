//
//  MovingUpState.h
//  HappyMouse
//
//  Created by xUanBing on 14-7-22.
//
//

#ifndef __HappyMouse__MovingUpState__
#define __HappyMouse__MovingUpState__

#include "cocos2d.h"
#include "GameState.h"
#include "GameEventParams.h"

class GameObject;

class MovingUpState:public GameState , public CCObject {
    
public:
    virtual void onEnterCallback(GameObject* obj);
    virtual void onExitCallback(GameObject* obj);
    virtual void updateCallback(GameObject* obj,const float dt);
    virtual bool onMessageCallback(GameObject* obj,const GameEventParams* params);
    
private:
    void changeToIdleState(GameObject* obj);
    
};

#endif /* defined(__HappyMouse__MovingUpState__) */
