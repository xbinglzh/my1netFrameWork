//
//  StateFactory.cpp
//  HappyMouse
//
//  Created by xUanBing on 14-7-22.
//
//

#include "StateFactory.h"
#include "GameEventDef.h"
#include "StateDef.h"

#include "MovingUpState.h"
#include "DisplayState.h"
#include "IdleState.h"
#include "AttackingState.h"
#include "BeInjuredState.h"
#include "ToDisactiveState.h"

static StateFactory * _stateFactorySharedInstance = NULL;

StateFactory::StateFactory(){
	
}

StateFactory::~StateFactory(){
    std::map<int, State*>::iterator iter =  _stateMap.begin();
    
    State * state = NULL;
    for (; iter != _stateMap.end(); iter++) {
        state = (*iter).second;
        if (state) {
            delete state;
        }
    }
	_stateMap.clear();
    
    std::map<int, State*>::iterator siter =  _skillStateMap.begin();
    State * skillState = NULL;
    for (; siter != _skillStateMap.end(); siter++) {
        skillState = (*siter).second;
        if (skillState) {
            delete skillState;
        }
    }
    _skillStateMap.clear();
    
}

StateFactory * StateFactory::getInstance(){
    
	if (! _stateFactorySharedInstance) {
        _stateFactorySharedInstance = new StateFactory();
        _stateFactorySharedInstance->init();
    }
    
	return _stateFactorySharedInstance;
}

void StateFactory::purgeInstance(){
	if (_stateFactorySharedInstance) {
        delete _stateFactorySharedInstance;
        _stateFactorySharedInstance = NULL;
    }
}

bool StateFactory::init(){
    
	return true;
}

State * StateFactory::getStateByTypeId(const int stateType){
    
    CCLOG("StateFactory::getStateByTypeId %d .", stateType);
    
    State * state = NULL;
    
    std::map<int, State * >::iterator iter = _stateMap.find(stateType);
    
    if (iter != _stateMap.end()) {
        
        state = (*iter).second;
        
    } else {
        
        switch (stateType) {
                //-----------------------------------
                //Normal State
                //-----------------------------------
            case KDisplayState:
                state = new DisplayState();
                break;
                
            case KIdleState:
                state = new IdleState();
                break;
                
            case KMovingUpState:
                state = new MovingUpState();
                break;
                
            case KAttackingState:
                state = new AttackingState();
                break;
                
            case KBeInjuredState:
                state = new BeInjuredState();
                break;
                
            case KToDisactiveState:
                state = new ToDisactiveState();
                break;
                
            default:
                CCLOG("StateFactory::getStateByTypeId Un Find ID %d .", stateType);
                break;
        }
        
        if (state) {
            _stateMap[stateType] = state;
            _stateMap[stateType]->setStateId(stateType);
        }
        
    }
    
    return state;
}
