//
//  GameModel.cpp
//  motoGame
//
//  Created by xUanBing on 14-5-3.
//
//

#include "GameModel.h"
#include "NotifyMessageDef.h"

static GameModel * _sharedInstance=NULL;

GameModel::GameModel() :CCObject(), _gameConfig(NULL) ,_currentEnergy(0),_saveEnergyRatio(0){
    
}

GameModel::~GameModel() {
    CCNotificationCenter::sharedNotificationCenter()->removeAllObservers(this);
    _currentEnergy = 0;
    _saveEnergyRatio = 0;
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

void GameModel::appendEnergyUnit() {
    _currentEnergy += Energy_Unit;
    genSaveEnergyRatio();
}

void GameModel::appendEnergy(float energyNum) {
    _currentEnergy += energyNum;
    genSaveEnergyRatio();
}

void GameModel::genSaveEnergyRatio() {
    float ratio = _currentEnergy / Energy_Max;
    if (ratio != _saveEnergyRatio) {
        _saveEnergyRatio = ratio;
        CCNotificationCenter::sharedNotificationCenter()->postNotification(KNotifyEnergyChangeMessage);
    }
}

float GameModel::getEnergyRatio() {
    return _saveEnergyRatio;
}
