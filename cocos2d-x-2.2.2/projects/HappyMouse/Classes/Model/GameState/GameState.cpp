//
//  GameState.cpp
//  HappyMouse
//
//  Created by xUanBing on 14-7-22.
//
//

#include "GameState.h"
#include "GameEventParams.h"
#include "GameObject.h"
#include "ConstansDef.h"
#include "KeyConfigDef.h"
#include "GameEventDef.h"

//-------------------------------
//角色（卡牌和兵）类的状态
//-------------------------------
GameState::~GameState(){
    
}

/*切换到该状态的时候调用*/
void GameState::onEnter(const void * t){
    this->onEnterCallback((GameObject *)t);
}

/*切出该状态的时候调用*/
void GameState::onExit(const void * t){
    this->onExitCallback((GameObject *)t);
}

/*状态的循环调用*/
void GameState::update(const void * t,const float dt){
    this->superUpdateCallback((GameObject *)t,dt);
}

/*外部传入的消息*/
bool GameState::onMessage(const void * t,const void * tdata){
    bool isprivate = false;
    if(!this->onSuperMessageCallback((GameObject *)t,(const GameEventParams *)tdata,isprivate)){
        return this->onMessageCallback((GameObject *)t,(const GameEventParams *)tdata);
    }
    return isprivate;
}

void GameState::onEnterCallback(GameObject * obj){
    
}

void GameState::onExitCallback(GameObject * obj){
    obj->stopActionByTag(KSTATE_ANIMATION_ACTION_TAG);
}

void GameState::updateCallback(GameObject * obj,const float dt){
	
}

bool GameState::onSuperMessageCallback(GameObject * obj,const GameEventParams * params,bool & isprivate){
    return false;
}
void GameState::superUpdateCallback(GameObject * obj,const float dt){
    //执行状态
    this->updateCallback(obj,dt);
}

bool GameState::onMessageCallback(GameObject * obj,const GameEventParams * params){
    return false;
}

bool GameState::runStateAnimation(GameObject * obj,int stateId){
    return GameObject::runStateAnimation(obj,stateId);
}

void GameState::runStateAnimWithCallback(GameObject * obj,int stateId,const char * durationKey){
    
    float durationVal = 0.01f;
    
    if (strcmp(durationKey, KKeyBeInjureDuration) == 0) {
        durationVal = obj->getGameCharactar()._injureDuration;
    }

    if(!this->runStateAnimation(obj,stateId)){
        CCDictionary * dict = CCDictionary::create();
        dict->setObject(CCString::create(KKeyActOnMsg), KDoCallFuncActId);
        GameEventParams *  p = GameEventParams::create(K_EVENT_ANIMATION_FINISHED,obj);
        dict->setObject(p, KDoCallFuncParams);
        
        CCSequence * seq = CCSequence::create(CCDelayTime::create(durationVal),
                                              CCCallFuncO::create(obj,callfuncO_selector(GameObject::doCallFunc),dict), NULL);
        
        seq->setTag(KSTATE_ANIMATION_ACTION_TAG);
        obj->runAction(seq);
    }
}
