//
//  BeInjuredState.cpp
//  HappyMouse
//
//  Created by xUanBing on 14-7-26.
//
//

#include "BeInjuredState.h"
#include "StateDef.h"
#include "GameEventDef.h"
#include "KeyConfigDef.h"
#include "GameObject.h"


void BeInjuredState::onEnterCallback(GameObject * obj){
    runStateAnimWithCallback(obj,K_STATE_BE_INJURED,KKeyBeInjureDuration);
}

bool BeInjuredState::onMessageCallback(GameObject* obj,const GameEventParams* params){
    if (params) {
        switch (params->getEvent()) {
            case K_EVENT_ANIMATION_FINISHED:
            {
                if(params->getData() == obj){
                    obj->removeAdditionState(K_STATE_BE_INJURED);
                    if(obj->getHp() == 0)
                        obj->changeState(K_STATE_TO_DISACTIVE);
                    runStateAnimation(obj,obj->getCurrentState());
                    return true;
                }
            }
                break;
            default:
                break;
        }
    }
    return false;
}