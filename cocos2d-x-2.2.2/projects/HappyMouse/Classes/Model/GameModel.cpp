//
//  GameModel.cpp
//  HappyMouse
//
//  Created by xUanBing on 14-7-22.
//
//

#include "GameModel.h"
#include "ResourceLoader.h"
#include "BattleLayer.h"

static GameModel * _sharedInstance = NULL;

GameModel::GameModel() : CCObject(),
_director(NULL),
_gameConfig(NULL),
_stateFactory(NULL),
_sharedAudioManager(NULL),
_battleLayer(NULL),
_troopMonsterDict(NULL) {
    
}

GameModel::~GameModel() {
    CCNotificationCenter::sharedNotificationCenter()->removeAllObservers(this);
    _stateFactory = NULL;
    StateFactory::purgeInstance();
    
    CC_SAFE_RELEASE_NULL(_troopMonsterDict);
}

GameModel * GameModel::getInstance(void) {
	
	if (!_sharedInstance) {
        _sharedInstance = new GameModel();
        _sharedInstance->init();
    }
	
	return _sharedInstance;
}

void GameModel::purgeInstance(void){
	CC_SAFE_RELEASE_NULL(_sharedInstance);
}

bool GameModel::init(void){
    
	_stateFactory = StateFactory::getInstance();
	_director = CCDirector::sharedDirector();
	_gameConfig = GameConfig::getInstance();
    _sharedAudioManager = AudioManager::sharedInstance();
    
    _troopMonsterDict = new CCDictionary();
    
    return true;
}

void GameModel::update(float dt) {
    //TODO:刷新战斗模块
    //TODO:对于状态已经是死亡或者到达目的地的状态角色对象压入清理队列
    
}

void GameModel::resetBattlelayer(BattleLayer* battlelayer) {
    _battleLayer = static_cast<BattleLayer *>(battlelayer);
    
}

void GameModel::addChildToGroundMap(CCNode *child, int zOrder, int tag){

}

void GameModel::loadResoure(const boost::function<void ()> &finishCallback) {

}

void GameModel::unloadResoure() {
    
}

void GameModel::didFinishedLoadingResources(const boost::function<void ()> &finishCallback){
    
    finishCallback();
}

GameObject * GameModel::generateById(const uint32_t pid){
    CCDictionary * gdict =_gameConfig->getTemplateValue(pid);
	return (gdict ? GameObject::create(gdict, pid) : NULL);
}

void GameModel::clearCache() {
    _battleInfo.reset();
    
}

void GameModel::clearGameObjects() {
    //清理所有的对象
	CCDictElement * pDictElement = NULL;
    
	CCDICT_FOREACH(_troopMonsterDict, pDictElement){
		CCSet * set = (CCSet*)pDictElement->getObject();
		CCSetIterator iter;
		for (iter = set->begin(); iter != set->end(); ++iter)
		{
			GameObject * tmp = (GameObject *)(*iter);
//            tmp->removeAllSkillObserver();
//            tmp->removeAllProperTies();
//            tmp->removeAtkTargets();
            tmp->removeFromParentAndCleanup(true);
		}
	}
    
	_troopMonsterDict->removeAllObjects();
}

CCSet * GameModel::addMonsterToTroop(GameObject * obj, int troopId) {
    
	CCSet * set = (CCSet*)_troopMonsterDict->objectForKey(troopId);
    
	if (!set) {
		set = new CCSet();
		_troopMonsterDict->setObject(set, troopId);
		CC_SAFE_RELEASE(set);
	}
    
	set->addObject(obj);

    
    return set;
}

cocos2d::CCSet * GameModel::findMonsterInTroop(const int troopId){
    CCSet * ret = (CCSet * )_troopMonsterDict->objectForKey(troopId);
    return ret;
}

void GameModel::putGameObject(GameObject* batteObj) {

}

void GameModel::loadMap(const std::string& mapId) {
    
    _battleLayer->updateGroundMap(GameModel::getInstance()->getBattleInfo());
}

BattleLayer* GameModel::getBattleLayer() {
    return _battleLayer;
}

BattleInfo& GameModel::getBattleInfo() {
    return _battleInfo;
}




