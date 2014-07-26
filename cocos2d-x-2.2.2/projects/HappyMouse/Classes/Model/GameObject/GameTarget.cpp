//
//  GameTarget.cpp
//  HappyMouse
//
//  Created by xUanBing on 14-7-26.
//
//

#include "GameTarget.h"

GameTarget::GameTarget():_role(NULL),_distance(0){
    
}

GameTarget::~GameTarget(){
	CC_SAFE_RELEASE_NULL(_role);
}

bool GameTarget::init(){
	return true;
}

int GameTarget::compareDistance(const void * p1,const void * p2){
    GameTarget * item1 = *((GameTarget**)p1);
    GameTarget * item2 = *((GameTarget**)p2);
    if(item1->_distance > item2->_distance){
        return 1;
    }
    else if(item1->_distance < item2->_distance){
        return -1;
    }
    return 0 ;
}



TargetsObject::TargetsObject():_targetsObject(NULL){
    
}

TargetsObject::~TargetsObject(){
	CC_SAFE_RELEASE_NULL(_targetsObject);
}

bool TargetsObject::init(){
	return true;
}

void TargetsObject::addTargetsObject(GameTarget * obj){
    
	if(!_targetsObject){
		_targetsObject = new cocos2d::CCArray();
	}
    
    bool inserted = false;
	for (int i = 0 ; i < _targetsObject->count(); i++ ) {
        GameTarget * tmp =  (GameTarget *)_targetsObject->objectAtIndex(i);
        if (tmp->getDistance() > obj->getDistance()) {
            _targetsObject->insertObject(obj, i);
            inserted = true;
            break;
        }
    }
    
    if (!inserted) {
        _targetsObject->addObject(obj);
    }
}

void TargetsObject::removeGameTarget(GameObject * obj){
    if(_targetsObject){
        for (int i = 0 ; i < _targetsObject->count(); i++ ) {
            GameTarget * tmp =  (GameTarget *)_targetsObject->objectAtIndex(i);
            if (tmp->getRole() == obj) {
                _targetsObject->removeObject(tmp);
                break;
            }
        }
	}
}

