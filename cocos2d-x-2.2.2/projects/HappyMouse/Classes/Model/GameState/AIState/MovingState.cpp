//
//  MovingState.cpp
//  HappyMouse
//
//  Created by xUanBing on 14-7-22.
//
//

#include "MovingState.h"
#include "GameEventParams.h"
#include "GameEventDef.h"
#include "GameObject.h"
#include "ConstansDef.h"

void MovingState::onEnterCallback(GameObject * obj) {
	runStateAnimation(obj,K_STATE_MOVING);
}

void MovingState::onExitCallback(GameObject * obj) {
    obj->stopActionByTag(KSTATE_MOVING_ACTION_TAG);
}

void MovingState::updateCallback(GameObject * obj, const float dt) {

}

bool MovingState::onMessageCallback(GameObject * obj,const GameEventParams * params) {
    
    return false;
}
