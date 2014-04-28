//
//  GameConfig.cpp
//  motoGame
//
//  Created by xUanBing on 14-3-24.
//
//

#include "GameConfig.h"



static GameConfig * _configSharedInstance=NULL;

GameConfig::GameConfig() : _animationDict(NULL) {
    
}

GameConfig::~GameConfig() {
    CC_SAFE_RELEASE_NULL(_animationDict);
}

GameConfig * GameConfig::sharedInstance(){
	
	if (!_configSharedInstance) {
        _configSharedInstance = new GameConfig();
        _configSharedInstance->init();
    }
	
	return _configSharedInstance;
}

void GameConfig::purgeInstance() {
	CC_SAFE_RELEASE_NULL(_configSharedInstance);
}

bool GameConfig::init() {
    
    CC_SAFE_RELEASE_NULL(_animationDict);
    _animationDict = CCDictionary::createWithContentsOfFile("x_anim.plist");
    _animationDict->retain();
    
    return true;
}

int GameConfig::getScreenSize() {
    return _screenSize;
}

void GameConfig::setScreenSize(int var) {
    this->_screenSize = var;
}

/**
 获得对应Id的animation信息
 */
cocos2d::CCDictionary * GameConfig::getAnimationById(const std::string & Id){
    if (_animationDict) {
        return static_cast<CCDictionary * >(_animationDict->objectForKey(Id));
    }
    return NULL;
}