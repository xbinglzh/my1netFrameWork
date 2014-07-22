//
//  StateFactory.cpp
//  HappyMouse
//
//  Created by xUanBing on 14-7-22.
//
//

#include "StateFactory.h"
#include "MovingState.h"
#include "DisplayState.h"
#include "GameEventDef.h"

static StateFactory * _stateFactorySharedInstance = NULL;

StateFactory::StateFactory(){
	
}

StateFactory::~StateFactory(){
    std::map<int32_t,State*>::iterator iter =  _stateMap.begin();
    
    State * state = NULL;
    for (; iter != _stateMap.end(); iter++) {
        state = (*iter).second;
        if (state) {
            delete state;
        }
    }
	_stateMap.clear();
    
    std::map<int32_t,State*>::iterator siter =  _skillStateMap.begin();
    State * skillState = NULL;
    for (; siter != _skillStateMap.end(); siter++) {
        skillState = (*siter).second;
        if (skillState) {
            delete skillState;
        }
    }
    _skillStateMap.clear();
    
}

StateFactory * StateFactory::sharedInstance(){
    
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

State * StateFactory::getStateByTypeId(const int32_t id){
    State * state = NULL;
    
    std::map<int32_t,State * >::iterator iter = _stateMap.find(id);
    
    if (iter != _stateMap.end()) {
        
        state = (*iter).second;
        
    } else {
        
        switch (id) {
                //-----------------------------------
                //Normal State
                //-----------------------------------
            case KDisplayState:
                state = new DisplayState();
                break;
                
            case KMovingState:
                state = new MovingState();
                break;
                
            default:
                break;
        }
        
        if (state) {
            _stateMap[id] = state;
            _stateMap[id]->setStateId(id);
        }
        
    }
    
    return state;
}
