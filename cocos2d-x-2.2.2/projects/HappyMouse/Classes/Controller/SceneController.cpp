//
//  SceneController.cpp
//  motoGame
//
//  Created by xUanBing on 14-3-30.
//
//

#include "SceneController.h"

static SceneController* _sharedInstance=NULL;

SceneController::SceneController() : _director(NULL), _currentSceneId(K_SCENE_UNKNOW) , _currentRunningSceneId(K_SCENE_UNKNOW){
    
}

SceneController::~SceneController() {
    
}

SceneController* SceneController::sharedInstance(void){
	
	if (!_sharedInstance)
    {
        _sharedInstance = new SceneController();
        _sharedInstance->init();
    }
	
	return _sharedInstance;
}

void SceneController::purgeInstance(void){
	CC_SAFE_RELEASE_NULL(_sharedInstance);
}

bool SceneController::init(void) {
    _director = CCDirector::sharedDirector();
    CCDirector::sharedDirector()->setDelegate(this);
    
    return true;
}

void SceneController::updateProjection() {
    
}

void SceneController::updateScene(cocos2d::CCScene *scene) {
    _currentRunningSceneId = (ESceneId)CCDirector::sharedDirector()->getRunningScene()->getTag();
    
}

void SceneController::switchSence(const ESceneId sceneId, cocos2d::CCObject* param, const SwitchOption option) {
    CCLayer *layer = NULL;
    CCLOGINFO("switchSence:%d", sceneId);
    _currentSceneId = sceneId;
    
    if (option == SwitchOptionPush) {
        _sceneQueue.push_front(sceneId);
    } else if (option == SwitchOptionRoot) {
        while (_sceneQueue.size() > 1) {
            _sceneQueue.pop_front();
            _director->popScene();
        }
        
        if (!_sceneQueue.empty()) {
            _sceneQueue.pop_front();
        }
        _sceneQueue.push_front(sceneId);
    } else if (option == SwitchOptionReplace) {
        if (!_sceneQueue.empty()) {
            _sceneQueue.pop_front();
        }
        _sceneQueue.push_front(sceneId);
    } else {
        CCAssert(false, "Unknown SwitchOption");
    }
	
	switch (sceneId) {
            
        case K_SCENE_WELCOME: {
//            layer = HelloWorld::create();
            break;
		}
            
        default:
            CCAssert(false, "GameController::switchSence sceneId is invalid..");
			break;
	}
    
	if (layer) {
        CCScene * pScene = CCScene::create();
        pScene->setTag(sceneId);
        pScene->addChild(layer);
        //bool isR = pScene->isRunning();
        if (_director->getRunningScene()) {
            if (option == SwitchOptionPush) {
                _director->pushScene(pScene);
            }
            else {
                _director->replaceScene(pScene);
            }
        }
        else{
            _director->runWithScene(pScene);
        }
        
        CCLOG("sceneID : %d", sceneId);
	}
}

const bool SceneController::backToScene() {
    if (!_sceneQueue.empty()) {
        _sceneQueue.pop_front();

        if (!_sceneQueue.empty()) {
            _currentSceneId = (ESceneId)_sceneQueue.front();
        } else {
            _currentSceneId = K_SCENE_UNKNOW;
        }
        _director->popScene();
        
        return true;
    }
    return false;
}

void SceneController::backToRootScene() {
    if (_sceneQueue.size() > 1) {
        _currentSceneId = (ESceneId)(*_sceneQueue.end());
        _sceneQueue.clear();
        _director->popToRootScene();
    }
}