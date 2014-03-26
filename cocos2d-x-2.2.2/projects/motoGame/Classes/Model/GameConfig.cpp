//
//  GameConfig.cpp
//  motoGame
//
//  Created by xUanBing on 14-3-24.
//
//

#include "GameConfig.h"



static GameConfig * _configSharedInstance=NULL;

GameConfig::GameConfig() {
    
}

GameConfig::~GameConfig() {
    
}

GameConfig * GameConfig::sharedInstance(){
	
	if (! _configSharedInstance)
    {
        _configSharedInstance = new GameConfig();
        _configSharedInstance->init();
    }
	
	return _configSharedInstance;
}

void GameConfig::purgeInstance() {
	CC_SAFE_RELEASE_NULL(_configSharedInstance);
}

bool GameConfig::init() {
    
    return true;
}

int GameConfig::getScreenSize() {
    return _screenSize;
}

void GameConfig::setScreenSize(int var) {
    this->_screenSize = var;
}