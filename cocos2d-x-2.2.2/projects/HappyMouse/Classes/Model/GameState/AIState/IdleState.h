//
//  IdleState.h
//  HappyMouse
//
//  Created by xUanBing on 14-7-26.
//
//

#ifndef __HappyMouse__IdleState__
#define __HappyMouse__IdleState__

#include "cocos2d.h"
#include "GameState.h"


class IdleState : public GameState ,public cocos2d::CCObject {
    
public:
    virtual void onEnterCallback(GameObject * obj);
    virtual bool onMessageCallback(GameObject * obj,const GameEventParams * params);
    
private:
    void changeToMoveDown(GameObject* obj);
};

#endif /* defined(__HappyMouse__IdleState__) */
