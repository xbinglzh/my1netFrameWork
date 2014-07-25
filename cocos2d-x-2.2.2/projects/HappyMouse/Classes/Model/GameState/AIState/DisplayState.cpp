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
    CCLOG("[%d]-[%d] DisplayState::onEnter", obj->getId(), ((int)this));
}

bool DisplayState::onMessageCallback(GameObject * obj,const GameEventParams * params){
    
    return false;
}