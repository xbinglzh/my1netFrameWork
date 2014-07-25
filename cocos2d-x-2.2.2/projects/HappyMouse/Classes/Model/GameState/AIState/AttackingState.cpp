//
//  AttackingState.cpp
//  HappyMouse
//
//  Created by xUanBing on 14-7-26.
//
//

#include "AttackingState.h"
#include "StateDef.h"
#include "GameEventDef.h"

void AttackingState::onEnterCallback(GameObject * obj){
	runStateAnimation(obj,K_STATE_ATTACKING);
}

void AttackingState::onExitCallback(GameObject * obj){
    MovingState::onExitCallback(obj);
}

void AttackingState::updateCallback(GameObject * obj,const float dt){
    //移动
    MovingState::updateCallback(obj, dt);
}

bool AttackingState::onMessageCallback(GameObject * obj,const GameEventParams * params){
    
    return false;
}
