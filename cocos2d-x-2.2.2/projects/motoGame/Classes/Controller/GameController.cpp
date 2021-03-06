//
//  GameController.cpp
//  motoGame
//
//  Created by xUanBing on 14-5-3.
//
//

#include "GameController.h"
#include "GameModel.h"
#include "KeyConfigDef.h"
#include "ConstansDef.h"
#include "NotifyMessageDef.h"
#include "SceneController.h"
#include "BattleResultView.h"
#include "battle.h"

static GameController * _sharedInstance=NULL;

GameController::GameController() : CCObject() ,_updateStoped(true), _gameModel(NULL), _director(NULL){
    
}

GameController::~GameController() {
    CCNotificationCenter::sharedNotificationCenter()->removeAllObservers(this);
}

GameController * GameController::sharedInstance(void){
	
	if (!_sharedInstance)
    {
        _sharedInstance = new GameController();
        _sharedInstance->init();
    }
	
	return _sharedInstance;
}

void GameController::purgeInstance(void){
	CC_SAFE_RELEASE_NULL(_sharedInstance);
}

bool GameController::init(void) {
    _gameModel = GameModel::sharedInstance();
    _director  = CCDirector::sharedDirector();
    _sceneController = SceneController::sharedInstance();
    
    return true;
}

void GameController::update(float dt){
	if (!_updateStoped) {
		_gameModel->update(dt);
    }
}

void GameController::startBattle(void){
    _sceneController->switchSence(K_SCENE_BATTLEVIEW);
    resumeBattle();
}

void GameController::pauseBattle(void){
	_updateStoped = true;
    _gameModel->pauseModel();
	_director->getScheduler()->unscheduleSelector(schedule_selector(GameController::update), this);
    CCNotificationCenter::sharedNotificationCenter()->postNotification(KNotifyPauseBattleMessage);
    
    battle::Rewards reward;
    reward.score = _gameModel->getGameScore();
    BattleResultView::show(reward);
}

void GameController::resumeBattle(void){
    _director->getScheduler()->scheduleSelector(schedule_selector(GameController::update), this, GAME_INTERVAL, false);
	_updateStoped = false;
    CCNotificationCenter::sharedNotificationCenter()->postNotification(KNotifyStartBattleMessage);
}

void GameController::quitFromBattle() {
    
//    const BattleSenceInfo & bsi = _gModel->battleSenceInfo();
//    if (bsi.getBattleZoneId() == K_BATTLE_ZONE_MULTI_PVE) {
//        _MIController->reportGameResult(false);
//    } else if (bsi.getBattleModeId() == K_BATTLE_LOOKON) {
//        _SIController->stopLookOnBattle();
//    } else if(bsi.getBattleModeId() == K_BATTLE_DEFENSE_SHOW) {  //刺探军情
//        _SIController->quitBattle();
//    } else {
//        _SIController->reportBattleResult(1);
//    }
    
    battle::Rewards reward;
    reward.score = _gameModel->getGameScore();
    BattleResultView::show(reward);
}

void GameController::reStartBattle() {
    _sceneController->switchSence(K_SCENE_UIHOME);
    _gameModel->clearUserData();
}

const bool GameController::isBattleRunning(){
    return !_updateStoped;
}

/*---------------hero control-------------------*/

void GameController::makeHeroJump() {
    CCNotificationCenter::sharedNotificationCenter()->postNotification(KNotifyMakeHeroJumpMessage);
}

void GameController::makeHeroObtainStar() {
    _gameModel->appendEnergyUnit();
}

void GameController::makeHeroFallFloor() {
    CCNotificationCenter::sharedNotificationCenter()->postNotification(KNotifyMakeHeroFallFloorMessage);
}

void GameController::makeHeroDie() {
    CCNotificationCenter::sharedNotificationCenter()->postNotification(KNotifyMakeHeroDieMessage);
    this->pauseBattle();
}

