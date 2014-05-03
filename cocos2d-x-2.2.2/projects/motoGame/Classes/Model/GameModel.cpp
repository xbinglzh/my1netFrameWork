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

GameModel::GameModel() :CCObject(), _gameConfig(NULL) ,_currentEnergy(0),_saveEnergyRatio(0), _currentGameScore(0), _isUseEnergy(false),_saveGameScore(0){
    
}

GameModel::~GameModel() {
    CCNotificationCenter::sharedNotificationCenter()->removeAllObservers(this);
    _currentEnergy = 0;
    _saveEnergyRatio = 0;
    _currentGameScore = 0;
    _saveGameScore = 0;
    _isUseEnergy = false;
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
    
    if (_isUseEnergy) {
        _currentGameScore += 0.5f;
    } else {
        _currentGameScore += 0.1f;
    }
    
    genScore();
    
}

void GameModel::pauseModel() {
    stopUseEnergy();
}

void GameModel::clearUserData() {
    _currentGameScore = 0;
    _saveGameScore = 0;
}

void GameModel::appendEnergyUnit() {
    _currentEnergy += Energy_Unit;
    genSaveEnergyRatio();
}

void GameModel::appendEnergy(float energy) {
    _currentEnergy += energy;
    genSaveEnergyRatio();
}

void GameModel::genSaveEnergyRatio() {
    if (_currentEnergy <= 0) {
        _currentEnergy = 0;
    }
    
    float ratio = _currentEnergy / Energy_Max;
    
    if (ratio != _saveEnergyRatio) {
        _saveEnergyRatio = ratio;
        CCNotificationCenter::sharedNotificationCenter()->postNotification(KNotifyEnergyChangeMessage);
    }
    
    if (ratio == 1) {
        CCNotificationCenter::sharedNotificationCenter()->postNotification(KNotifyEnergyFullMessage);
        startUseEnergy();
    }else if (ratio == 0) {
        CCNotificationCenter::sharedNotificationCenter()->postNotification(KNotifyEnergyEmptyMessage);
        stopUseEnergy();
    }
}

float GameModel::getEnergyRatio() {
    return _saveEnergyRatio;
}

void GameModel::decreaseEnergyUnit() {
    _currentEnergy -= Energy_Decrease_Unit;
    genSaveEnergyRatio();
}

void GameModel::decreaseEnergy(float energy) {
    _currentEnergy -= energy;
    genSaveEnergyRatio();
}

void GameModel::startUseEnergy() {
    _isUseEnergy = true;
    CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(GameModel::updateEnergy), this, 0.1, false);
}
void GameModel::stopUseEnergy(){
    _isUseEnergy = false;
    CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(GameModel::updateEnergy), this);
}

void GameModel::updateEnergy() {
    decreaseEnergyUnit();
}

int GameModel::getGameScore() {
    return (int)_saveGameScore;
}

void GameModel::genScore() {
    if (_currentGameScore == _saveGameScore) {
        return;
    }
    
    this->_saveGameScore = _currentGameScore;
    CCNotificationCenter::sharedNotificationCenter()->postNotification(KNotifyGameScoreChangeMessage);
}


