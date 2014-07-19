//
//  GameObject.cpp
//  HappyMouse
//
//  Created by xUanBing on 14-7-19.
//
//

#include "GameObject.h"
#include "LayoutUtil.h"
#include "CCScale9ProgressBar.h"

GameObject::GameObject() :
_bgNode(NULL),
_fgNode(NULL),
_flashNode(NULL),
_stateMachine(NULL) {
    
    _charactar._id = 0;
    _charactar._type = 0;
    _charactar._race = 0;
    _charactar._level = 0;
    _charactar._hp = 0;
    _charactar._fullHp = 0;
    _charactar._hurt = 0;
    _charactar._lastState = 0;
    _charactar._bufferBottom = "-1";
    _charactar._bufferTop = "-1";
    
}

GameObject::~GameObject() {
     CC_SAFE_DELETE(_stateMachine);
}

GameObject* GameObject::create(const uint32_t id) {
    GameObject* pRet = new GameObject();
    if(pRet){
        pRet->setId(id);
        if (pRet->init())
        {
            pRet->autorelease();
            return pRet;
        }
        CC_SAFE_DELETE(pRet);
    }
	return NULL;
}

bool GameObject::init() {
    _stateMachine = new StateMachine();
    return true;
}

//---------------------- 设置基本属性信息 ------------------------/

void GameObject::setId(const uint32_t value) {
	_charactar._id = value;
}

void GameObject::setType(const uint8_t type) {
    _charactar._type = type;
}

void GameObject::setRace(const uint8_t race) {
    _charactar._race = race;
}

void GameObject::setLevel(const int32_t level) {
    _charactar._level = level;
}

void GameObject::setLastState(const uint32_t lastState) {
    _charactar._lastState = lastState;
}

void GameObject::setHurtType(const uint8_t hurtType) {
    _charactar._hurtType = hurtType;
}

void GameObject::setHP(const uint32_t hp) {
    _charactar._hp = hp;
}

void GameObject::setFullHp(const uint32_t fullHp) {
    _charactar._fullHp = fullHp;
}

void GameObject::setHurt(const uint32_t hurt) {
    _charactar._hurt = hurt;
}

void GameObject::setSpeed(const float speed) {
    _charactar._speed = speed;
}

void GameObject::setBufferTop(const std::string bufferTop) {
    _charactar._bufferTop = bufferTop;
}

void GameObject::setBufferBottom(const std::string bufferBottom) {
    _charactar._bufferBottom = bufferBottom;
}

//---------------- end Set Charactar Info-----------------------------

const bool GameObject::runAnimation(const std::string & name,const float delay){
	if (_flashNode) {
		return _flashNode->runAnimation(name,delay);
	}
    return false;
}


void GameObject::stopAnimation() {
	if (_flashNode) {
        _flashNode->stopAnimation();
	}
}

void GameObject::pauseAnimation() {
	if (_flashNode) {
        _flashNode->pauseAnimation();
	}
}

void GameObject::resumeAnimation() {
	if (_flashNode) {
        _flashNode->resumeAnimation();
	}
}

void GameObject::update(const float dt){
    if (_flashNode) {
        _flashNode->updateAnimFrame(dt);
    }
    
    if (_stateMachine) {
        _stateMachine->update(this, dt);
    }
}

