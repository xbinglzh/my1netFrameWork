//
//  StateMachine.cpp
//  HappyMouse
//
//  Created by xUanBing on 14-7-19.
//
//

#include "StateMachine.h"
#include "State.h"
#include "StateDef.h"

StateMachine::StateMachine() : _currentState(-1) {
    
}

StateMachine::~StateMachine() {
    _states.clear();
    _additionStates.clear();
}

const State* StateMachine::getCurrentState() {
    if (_currentState >= 0 ) {
        StateMachineMap::iterator iter = _states.find(_currentState);
        if (iter != _states.end()) {
            return (*iter).second;
        }
    }
    return NULL;
}

const int32_t StateMachine::getCurrentStateId() {
    return _currentState;
}

void StateMachine::dumpStates() {
    //    StateMachineMap::iterator siter = _additionStates.begin();
    for (StateMachineMap::iterator siter = _additionStates.begin();
         siter != _additionStates.end(); siter++) {
        
        CCLOG("[0x%x]StateMachine dumpSkillStates[%d]=0x%x",this,siter->first,siter->second);
        
    }
    
    
    //    StateMachineMap::iterator iter = _states.begin();
    for (StateMachineMap::iterator iter = _states.begin();
         iter != _states.end(); iter++) {
        
        CCLOG("[0x%x]StateMachine dumpStates[%d]=0x%x",this,iter->first,iter->second);
        
    }
}

void StateMachine::addState(const int32_t id,
                            const State* t,
                            const bool isAdditionState,
                            const void* g /*= NULL*/) {
    if (isAdditionState) {
        _additionStates[id] = (State*)t;
        _additionStates[id]->onEnter(g);
    }
    else{
        _states[id] = (State*)t;
    }
}

void StateMachine::removeState(const int32_t id,
                               const bool isAdditionState,
                               const void* g) {
    
    CCLOG("[0x%x]removeState: state = %d", g, id);
    
    if (isAdditionState) {
        StateMachineMap::iterator iter = _additionStates.find(id);
        if (iter != _additionStates.end()) {
            State * currentState = _additionStates[id];
            if (currentState) {
                currentState->onExit(g);
            }
            _additionStates[id] = NULL;
        }
    }
    else{
        StateMachineMap::iterator iter = _states.find(id);
        if (iter != _states.end()) {
            _states[id] = NULL;
        }
    }
}


State* StateMachine::findAdditionState(const int32_t id) {
    
    StateMachineMap::iterator iter = _additionStates.find(id);
    if (iter != _additionStates.end()) {
        return (*iter).second;
    }
    
    return NULL;
}

State* StateMachine::findState(const int32_t id) {
    
    StateMachineMap::iterator iter = _states.find(id);
    if (iter != _states.end()) {
        return (*iter).second;
    }
    
    return NULL;
}


void StateMachine::changeState(const void* g, const int32_t id) {
    StateMachineMap::iterator iter = _states.find(id);
    
    if (iter != _states.end()) {
        State * currentState = NULL;
        if (_currentState >= 0) {
            currentState =  _states[_currentState];
            if(currentState){
                currentState->onExit(g);
            }
        }
        
        _currentState = id;
        
        if (_currentState >= 0) {
            currentState = _states[_currentState];
            if(currentState){
                currentState->onEnter(g);
            }
        }
    }
    else {
        CCLOG("Error [0x%x]change state: invalid state = %d",this, id);
    }
}

bool StateMachine::onMessage(const void* g, const void* d) {
    
    for (StateMachineMap::iterator iter = _additionStates.begin();
         iter != _additionStates.end();
         iter++) {
        State * currentState = (*iter).second;
        if(currentState && currentState->onMessage(g,d)){
            return true;
        }
    }
    
    if (_currentState >= 0) {
		State *  currentState = _states[_currentState];
        if(currentState && currentState->onMessage(g,d)){
            return true;
        }
    }
    
    return false;
}

void StateMachine::update(const void* g, float dt) {
    
    if (_currentState >= 0) {
		State * currentState = _states[_currentState];
        if (currentState) {
            currentState->update(g,dt);
        }
    }
    
    for (StateMachineMap::iterator iter = _additionStates.begin();
         iter != _additionStates.end();
         iter++) {
        State * currentState = (*iter).second;
        if(currentState){
            currentState->update(g,dt);
        }
    }
}

