//
//  MonsterObject.cpp
//  HappyMouse
//
//  Created by xUanBing on 14-7-24.
//
//

#include "MonsterObject.h"
#include "KeyConfigDef.h"
#include "ConstansDef.h"
#include "LayoutUtil.h"

MonsterObject::MonsterObject() : GameObject(), _isAddParent(false) {
    
    _monsterDetail._id = -1;
    _monsterDetail._hp = -1;
    _monsterDetail._hurt = -1;
    _monsterDetail._display = "-1";
    _monsterDetail._speed = -1;
    
}

MonsterObject::~MonsterObject() {
    _isAddParent = false;
}

MonsterObject* MonsterObject::create(cocos2d::CCDictionary *dict) {
    MonsterObject * pRet = new MonsterObject();
    if (pRet) {
        if ( pRet->init() && pRet->initWithDictionary(dict))
        {
            pRet->autorelease();
            return pRet;
        }
        CC_SAFE_DELETE(pRet);
    }
	return NULL;
}

bool MonsterObject::init() {
    GameObject::init();
    
    return true;
}

bool MonsterObject::initWithDictionary(cocos2d::CCDictionary *dict) {
    
    CCString* idStr = static_cast<CCString*>(dict->objectForKey(KKeyId));
    CCString* hpStr = static_cast<CCString*>(dict->objectForKey(KKeyHp));
    CCString* hurtStr = static_cast<CCString*>(dict->objectForKey(KKeyHurt));
    CCString* displayStr = static_cast<CCString*>(dict->objectForKey(KKeyDisplay));
    CCString* speedStr = static_cast<CCString*>(dict->objectForKey(KKeySpeed));
    
    _monsterDetail._id = idStr->intValue();
    _monsterDetail._hp = hpStr->intValue();
    _monsterDetail._hurt = hurtStr->intValue();
    _monsterDetail._display = displayStr->getCString();
    _monsterDetail._speed = speedStr->intValue();
    
    this->setId(_monsterDetail._id);
    this->initDisplay(_monsterDetail._display.c_str());
    
    CCString* stateGroupId = static_cast<CCString*>(dict->objectForKey(KKeyState));
    this->initStateMachine(stateGroupId->m_sString);
    
    this->scheduleUpdate();
    this->complete();
    
    makeMidNodeInClipNode();
    
    return true;
}

void MonsterObject::makeMidNodeInClipNode() {
    CCNode* midNode = this->getChildByTag(Mid_Node_Tag);
    midNode->removeFromParentAndCleanup(false);
    
    CCLOG("mid w: %f, h %f", midNode->getContentSize().width, midNode->getContentSize().height);
    
    CCDrawNode* shap = CCDrawNode::create();
    
    CCPoint point[4] = {
            ccp(0,0),
            ccp(midNode->getContentSize().width, 0),
            ccp(midNode->getContentSize().width, midNode->getContentSize().height + 50),
            ccp(0, midNode->getContentSize().height + 50)
    };
    
    shap->drawPolygon(point, 4, ccc4f(255, 255, 255, 255), 2, ccc4f(255, 255, 255, 255));
    
    CCClippingNode* cliper = CCClippingNode::create();
    cliper->setStencil(shap);
    cliper->setAnchorPoint(ccp(0, 0));
    cliper->setContentSize(midNode->getContentSize());
    
    cliper->addChild(midNode);
    LayoutUtil::layoutParentBottom(midNode);
    
    this->addChild(cliper, 2, Mid_Node_Tag);
    LayoutUtil::layoutParentCenter(cliper);
}

MonsterObject::MonsterDetail& MonsterObject::getMonsterDetail() {
    
    return _monsterDetail;
}

void MonsterObject::setIsAddParent(bool isAdd) {
    this->_isAddParent = isAdd;
}

bool MonsterObject::isAddParent() {
    return _isAddParent;
}

