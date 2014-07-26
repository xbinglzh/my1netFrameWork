//
//  MovingDownState.cpp
//  HappyMouse
//
//  Created by xUanBing on 14-7-26.
//
//

#include "MovingDownState.h"
#include "GameEventParams.h"
#include "GameEventDef.h"
#include "GameObject.h"
#include "ConstansDef.h"

void MovingDownState::onEnterCallback(GameObject * obj) {
	runStateAnimation(obj, K_STATE_MOVING_DOWN);
    
    CCMoveBy* ation_moveTo = CCMoveBy::create(0.3f, CCPointMake(0, -1 * obj->getContentSize().height));
    CCDelayTime* time = CCDelayTime::create(3.0f);
    CCCallFuncO* callfun = CCCallFuncO::create(this, callfuncO_selector(MovingDownState::changeToDisplay), obj);
    
    obj->getMidNode()->runAction(CCSequence::create(ation_moveTo, time, callfun, NULL));
}

void MovingDownState::onExitCallback(GameObject * obj) {
    obj->stopActionByTag(KSTATE_MOVING_ACTION_TAG);
}

void MovingDownState::updateCallback(GameObject * obj, const float dt) {
    
}

bool MovingDownState::onMessageCallback(GameObject * obj,const GameEventParams * params) {
    
    return false;
}

void MovingDownState::changeToDisplay(GameObject* obj) {
    obj->changeState(K_STATE_DISPLAY);
}