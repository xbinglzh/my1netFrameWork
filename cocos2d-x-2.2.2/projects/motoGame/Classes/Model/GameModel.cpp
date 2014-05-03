//
//  GameModel.cpp
//  motoGame
//
//  Created by xUanBing on 14-5-3.
//
//

#include "GameModel.h"

static GameModel * _sharedInstance=NULL;

GameModel::GameModel() :CCObject(), _gameConfig(NULL) {
    
}

GameModel::~GameModel() {
    CCNotificationCenter::sharedNotificationCenter()->removeAllObservers(this);
}

GameModel * GameModel::sharedInstance(void) {
	
	if (!_sharedInstance)
    {
        _sharedInstance = new GameModel();
        _sharedInstance->init();
    }
	
	return _sharedInstance;
}

void GameModel::purgeInstance(void){
	CC_SAFE_RELEASE_NULL(_sharedInstance);
}

bool GameModel::init(void) {
    _gameConfig = GameConfig::sharedInstance();
    
    return true;
}

void GameModel::update(float dt) {
    
}

void GameModel::clearUserData() {
    
}



