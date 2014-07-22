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
#include "GameEventDef.h"
#include "KeyConfigDef.h"

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

const uint32_t GameObject::getId()const{
	return _charactar._id;
}

const uint8_t GameObject::getType()const{
	return _charactar._type;
}

const uint8_t GameObject::getRace()const{
	return _charactar._race;
}

const int32_t GameObject::getLevel()const{
	return _charactar._level;
}

const int32_t  GameObject::getLastState() const {
    return _charactar._lastState;
}

const int8_t GameObject::getHurtType() const {
    return _charactar._hurtType;
}

const int32_t GameObject::getHurt() const {
    return _charactar._hurt;
}

const int32_t  GameObject::getHp() const {
    return _charactar._hp;
}

const int32_t  GameObject::getFullHp() const {
    return _charactar._fullHp;
}

const float GameObject::getSpeed() const {
    return _charactar._speed;
}

const std::string GameObject::getBufferTop() const {
    return _charactar._bufferTop;
}

const std::string GameObject::getBufferBottom() const {
    return _charactar._bufferBottom;
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
//-------------- 状态机 ---------------------

void GameObject::changeState(const int32_t value) {
	if (_stateMachine) {
		_stateMachine->changeState(this, value);
	}
}

void GameObject::onMessage(GameEventParams *params) {
    if(_stateMachine) {
        _stateMachine->onMessage(this, params);
    }
}
//--------------------------------------------

void GameObject::onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader){
	CCLOG("GameObject node onNodeLoaded~") ;
}

void GameObject::notifyCompletedAnimationSequenceNamed(const char *name, const bool loopCompleted){
    onMessage(GameEventParams::create(K_EVENT_ANIMATION_FINISHED,this));
}

void GameObject::animationSequenceFrameChanged(cocos2d::CCNode * animNode,
                                               const char *animName,
                                               const char *lastframeName,
                                               const char *newframeName){
    
    CCDictionary * dict = CCDictionary::create();
    dict->setObject(CCString::create(animName), "anim");
    dict->setObject(CCString::create(lastframeName), "lastframe");
    dict->setObject(CCString::create(newframeName), "newframe");
    onMessage(GameEventParams::create(K_EVENT_ANIMATION_FRAME_CHANGED,dict));
    
}

bool GameObject::runStateAnimation(GameObject * obj,int stateId){
    std::stringstream key;
    key << stateId;
    
//    CCDictionary * dict = static_cast<CCDictionary *>(obj->getValue(KKeyState));
//    if (dict) {
//        dict = static_cast<CCDictionary *>(dict->objectForKey(key.str()));
//        if (dict) {
//            CCString * anim = static_cast<CCString *>(dict->objectForKey(KKeyAnimation));
//            if (anim) {
//                bool ret = obj->runAnimation(anim->m_sString);
//                if (!ret) {
//                    CCLOG("Warnning:%d runStateAnimation %d : %s failed",obj->getId(),obj->getState(),anim->getCString());
//                }
//                return ret;
//            }
//        }
//    }
    
    return false;
}
