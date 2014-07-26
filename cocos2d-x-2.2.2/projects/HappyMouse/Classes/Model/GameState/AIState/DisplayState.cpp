//
//  DisplayState.cpp
//  HappyMouse
//
//  Created by xUanBing on 14-7-22.
//
//

#include "DisplayState.h"
#include "GameEventParams.h"
#include "GameEventDef.h"
#include "ConstansDef.h"
#include "GameObject.h"

void DisplayState::onEnterCallback(GameObject * obj){
	//播放动画
    runStateAnimation(obj, K_STATE_DISPLAY);
//    CCLOG("[%d]-[%d] DisplayState::onEnter", obj->getId(), ((int)this));
    
    CCDelayTime* delay = CCDelayTime::create(3);
    CCCallFuncO* callFun = CCCallFuncO::create(this, callfuncO_selector(DisplayState::changeToMoveUp), obj);
    obj->getMidNode()->runAction(CCSequence::create(delay, callFun, NULL));
}

bool DisplayState::onMessageCallback(GameObject * obj,const GameEventParams * params){
    
    return false;
}

void DisplayState::changeToMoveUp(GameObject *obj) {
    obj->changeState(K_STATE_MOVING_UP);
}