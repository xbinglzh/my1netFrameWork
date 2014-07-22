//
//  GameModel.cpp
//  HappyMouse
//
//  Created by xUanBing on 14-7-22.
//
//

#include "GameModel.h"
#include "ResourceLoader.h"

static GameModel * _sharedInstance=NULL;

GameModel::GameModel() : CCObject(),
_director(NULL),
_gameConfig(NULL),
_stateFactory(NULL),
_sharedAudioManager(NULL),
_gameObjectsDict(NULL) {
    
}

GameModel::~GameModel() {
    CCNotificationCenter::sharedNotificationCenter()->removeAllObservers(this);
    _stateFactory = NULL;
    StateFactory::purgeInstance();
    
    CC_SAFE_RELEASE_NULL(_gameObjectsDict);
}

GameModel * GameModel::sharedInstance(void) {
	
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
    
	_stateFactory = StateFactory::sharedInstance();
	_director = CCDirector::sharedDirector();
	_gameConfig = GameConfig::sharedInstance();
    _sharedAudioManager = AudioManager::sharedInstance();
    
    _gameObjectsDict = new CCDictionary();
    
    return true;
}

void GameModel::update(float dt) {
    //TODO:刷新战斗模块
    //TODO:对于状态已经是死亡或者到达目的地的状态角色对象压入清理队列
    
}

void GameModel::resetBattlelayer(cocos2d::CCLayer* battlelayer) {

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

void GameModel::clearGameObjects() {
    //清理所有的对象
	CCDictElement * pDictElement = NULL;
    
	CCDICT_FOREACH(_gameObjectsDict, pDictElement){
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
    
	_gameObjectsDict->removeAllObjects();
}

CCSet * GameModel::addGameObjectToBattle(GameObject * obj)
{
	CCSet * set = (CCSet*)_gameObjectsDict->objectForKey(obj->getId());
    
	if (!set) {
		set = new CCSet();
		_gameObjectsDict->setObject(set, obj->getId());
		CC_SAFE_RELEASE(set);
	}
    
	set->addObject(obj);
    
//    const int typeId = obj->getTypeId();
//    if (GameObjectExt::isBattleSyncObject(typeId)){
//        battle::BattleStartObjs startObj;
//        startObj.id = obj->getId();
//        startObj.hp = obj->getFullHp();
//        startObj.type = GameObjectExt::rtypeOfGameObject(obj);
//        _battleResultInfo.startObjInfo.push_back(startObj);
//    }
    
    return set;
}

cocos2d::CCSet * GameModel::findGameObjectsInBattle(const int32_t gid){
    CCSet * ret = (CCSet * )_gameObjectsDict->objectForKey(gid);
    return ret;
}

void GameModel::putGameObject(GameObject* batteObj) {

}


