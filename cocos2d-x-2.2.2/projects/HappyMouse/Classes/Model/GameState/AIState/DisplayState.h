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
#include "cocos2d.h"

class DisplayState : public GameState, public cocos2d::CCObject {
    
public:
    virtual void onEnterCallback(GameObject * obj);
    virtual bool onMessageCallback(GameObject * obj,const GameEventParams * params);
    
private:
    void changeToMoveUp(GameObject* obj);
    
};

#endif /* defined(__HappyMouse__DisplayState__) */
