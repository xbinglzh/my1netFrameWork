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
#include "GameConfig.h"
#include "StateFactory.h"
#include "AnimUtils.h"

#define Bg_Node_Tag        100001
#define Mid_Node_Tag       100002
#define Fg_Node_Tag        100003
#define Flash_Node_Tag     100004

GameObject::GameObject() :
_bgNode(NULL),
_fgNode(NULL),
_midNode(NULL),
_flashNode(NULL),
_stateMachine(NULL),
_properties(NULL) {
    
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
    CC_SAFE_RELEASE_NULL(_properties);
    
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
    _properties = new CCDictionary();
    
    _bgNode = CCNode::create();
    _midNode = CCNode::create();
    _fgNode = CCNode::create();
    
    _bgNode->setAnchorPoint(CCPointZero);
    _midNode->setAnchorPoint(CCPointZero);
    _fgNode->setAnchorPoint(CCPointZero);
    
    this->addChild(_bgNode, 1, Bg_Node_Tag);
    this->addChild(_midNode, 2, Mid_Node_Tag);
    this->addChild(_fgNode, 3, Fg_Node_Tag);
    
    return true;
}

GameObject * GameObject::create(CCDictionary * dict,const uint32_t id) {
	GameObject * pRet = new GameObject();
    if (pRet) {
        pRet->setId(id);
        if (pRet->init() && pRet->initWithDictionary(dict))
        {
            pRet->autorelease();
            return pRet;
        }
        CC_SAFE_DELETE(pRet);
    }
	return NULL;
}

bool GameObject::initWithDictionary(CCDictionary * dict){
    
    return true;
}

void GameObject::complete(){
//    this->initActions();
//    this->initDisplay();
//    this->initSkills();
    
    setObjContentSize();
}

CCNode* GameObject::getBgNode() {
    return _bgNode;
}

CCNode* GameObject::getMidNode() {
    return _midNode;
}

CCNode* GameObject::getFgNode() {
    return _fgNode;
}

void GameObject::setObjContentSize() {
    CCSize flashSize = _flashNode->getContentSize();
    
    _fgNode->setContentSize(flashSize);
    _midNode->setContentSize(flashSize);
    _bgNode->setContentSize(flashSize);
    this->setContentSize(flashSize);
    
    LayoutUtil::layoutParentCenter(_flashNode);
    
    LayoutUtil::layoutParentCenter(_fgNode);
    LayoutUtil::layoutParentCenter(_midNode);
    LayoutUtil::layoutParentCenter(_bgNode);
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

void GameObject::setValue(const std::string & key,CCObject * value){
	CCAssert(value != NULL, "GameObject::setValue-->value is invalid!!!");
    _properties->setObject(value, key);
}

CCObject * GameObject::getValue(const std::string & key){
    if(_properties)
        return _properties->objectForKey(key);
	return NULL;
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

void GameObject::setFrameITScale(const float value){
    if (_flashNode) {
        _flashNode->setFrameITScale(value);
    }
}

//-------------- display ------------------

void GameObject::initDisplay(const char* animId) {
    
    if (_flashNode) {
        _flashNode->removeFromParentAndCleanup(true);
    }
    
    _flashNode = AnimUtils::createAnimById(animId);
    
    if (_flashNode) {
        _midNode->addChild(_flashNode);
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

void GameObject::initStateMachine(std::string& stateGroupId){
    
    CCDictionary * states = dynamic_cast<CCDictionary *>(GameConfig::getInstance()->getStateGroupById(stateGroupId));
    CCAssert(states != NULL, "GameObject::initStateMachine");
    
    this->setValue(KKeyState, states);

    StateFactory * stateFactory = StateFactory::getInstance();

    if (states) {
        
        CCDictElement * pDictElement = NULL;
        CCDICT_FOREACH(states, pDictElement){
            
            std::string key = pDictElement->getStrKey();
            CCDictionary * callbackDict = static_cast<CCDictionary *>(pDictElement->getObject());
            
            if (callbackDict) {
                CCString * idStr = (CCString *)callbackDict->objectForKey(KKeyId);
                State * state = stateFactory->getStateByTypeId(idStr->intValue());
                
                if(state){
                    _stateMachine->addState(atoi(key.c_str()),state);
                }
            }
        }
    }
}

void GameObject::addState(const int32_t stateTypeId ,const int32_t stateId){
    State * state = StateFactory::getInstance()->getStateByTypeId(stateId);
    
    if(state){
        _stateMachine->addState(stateTypeId,state);
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

//-----------------------------

void GameObject::doCallFunc(cocos2d::CCObject * data){
    CCDictionary * dict = static_cast<CCDictionary *>(data);
    CCString * eventId = static_cast<CCString *>(dict->objectForKey(KDoCallFuncActId));
//    this->doAction(eventId->m_sString,dict);
}

void GameObject::doAutoremoveCallFunc(cocos2d::CCObject * node){
    CCNode * pNode = static_cast<CCNode *>(node);
    pNode->removeFromParentAndCleanup(true);
}
