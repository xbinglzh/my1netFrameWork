//
//  GameController.cpp
//  HappyMouse
//
//  Created by xUanBing on 14-7-15.
//
//

#include "GameController.h"

static GameController* _sharedInstance = NULL;

GameController::GameController() : CCObject() {
    
}

GameController::~GameController() {
    
}

GameController* GameController::getInstance() {
    
    if (!_sharedInstance) {
        _sharedInstance = new GameController();
        _sharedInstance->init();
    }
    
    return _sharedInstance;
}

void GameController::purgeInstance() {
    CC_SAFE_RELEASE_NULL(_sharedInstance);
}

bool GameController::init() {
    return true;
}

void GameController::update(float dt) {
    //TODO: 处理业务逻辑
}

int GameController::genRandomMouseIndex() {
    
    return rand() % 9 ;
}
