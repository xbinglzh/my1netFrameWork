//
//  MovingState.cpp
//  HappyMouse
//
//  Created by xUanBing on 14-7-22.
//
//

#include "MovingUpState.h"
#include "GameEventParams.h"
#include "GameEventDef.h"
#include "GameObject.h"
#include "ConstansDef.h"

void MovingUpState::onEnterCallback(GameObject * obj) {
	runStateAnimation(obj,K_STATE_MOVING_UP);
    
    CCMoveBy* ation_moveTo = CCMoveBy::create(0.3f, CCPointMake(0, obj->getContentSize().height));
    CCCallFuncO* callfun = CCCallFuncO::create(this, callfuncO_selector(MovingUpState::changeToIdleState), obj);
    
    obj->getMidNode()->runAction(CCSequence::create(ation_moveTo, callfun, NULL));
}

void MovingUpState::onExitCallback(GameObject * obj) {
    obj->stopActionByTag(KSTATE_MOVING_ACTION_TAG);
}

void MovingUpState::updateCallback(GameObject * obj, const float dt) {

}

bool MovingUpState::onMessageCallback(GameObject * obj,const GameEventParams * params) {
    
    return false;
}
void MovingUpState::changeToIdleState(GameObject* obj) {
    obj->changeState(K_STATE_IDLE);
}