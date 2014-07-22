//
//  GameEventParams.cpp
//  HappyMouse
//
//  Created by xUanBing on 14-7-22.
//
//

#include "GameEventParams.h"

GameEventParams::GameEventParams() : _data(NULL), _event(-1){
    
}

GameEventParams::~GameEventParams(){
    CC_SAFE_RELEASE_NULL(_data);
}

GameEventParams * GameEventParams::create(const int32_t event,CCObject * data){
    GameEventParams * params = new GameEventParams();
    params->autorelease();
    
    params->setEvent(event);
    params->setData(data);
    
    return params;
}

bool GameEventParams::init(){
    return true;
}
