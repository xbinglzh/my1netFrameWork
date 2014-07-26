//
//  IdleState.cpp
//  HappyMouse
//
//  Created by xUanBing on 14-7-26.
//
//

#include "IdleState.h"
#include "GameObject.h"
#include "StateDef.h"
#include "GameEventDef.h"


void IdleState::onEnterCallback(GameObject * obj){
	//播放动画
    runStateAnimation(obj,K_STATE_IDLE);
    CCLOG("[%d]-[%d] IdleState::onEnter", obj->getId(), ((int)this));
}

bool IdleState::onMessageCallback(GameObject * obj,const GameEventParams * params){
    if (obj && params) {
		switch (params->getEvent()) {
            case K_EVENT_ENTER_ATK_RANGE:
            {
                
//                cocos2d::CCSet  * set = static_cast<cocos2d::CCSet *>(params->getData());
//                CharactarHandler::doDetectedEnemies(obj,set,true);
//                if (obj->getState() != K_STATE_ATTACKING && !obj->isTargetsEmpty()) {
//                    obj->changeState(K_STATE_ATTACKING);
//                }
                
                return true;
            }
				break;
			default:
				break;
		}
	}
    return false;
}
