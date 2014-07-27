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
#include "CharactarHandler.h"

MonsterObject::MonsterObject() : GameObject(), _isAddParent(false) {
    
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
    CCString* injureDuration = static_cast<CCString*>(dict->objectForKey(KKeyBeInjureDuration));
    
    _charactar._id = idStr->intValue();
    _charactar._hp = hpStr->intValue();
    _charactar._fullHp = hpStr->intValue();
    _charactar._hurt = hurtStr->intValue();
    _charactar._speed = speedStr->floatValue();
    _charactar._display = displayStr->getCString();
    _charactar._injureDuration = injureDuration->floatValue();
    
    this->initDisplay();
    
    CCString* stateGroupId = static_cast<CCString*>(dict->objectForKey(KKeyState));
    this->initStateMachine(stateGroupId->m_sString);
    
    this->scheduleUpdate();
    this->complete();
    
    makeMidNodeInClipNode();
    
    this->changeState(K_STATE_DISPLAY);
    
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
    
    LayoutUtil::layoutParentBottom(midNode, 0, -1 * (midNode->getContentSize().height + 10 ));
    
    this->addChild(cliper, 2, Mid_Node_Tag);
    LayoutUtil::layoutParentBottom(cliper);
}

CCNode* MonsterObject::getMoveNode() {
    return this->getChildByTag(Mid_Node_Tag);
}

void MonsterObject::setIsAddParent(bool isAdd) {
    this->_isAddParent = isAdd;
}

bool MonsterObject::isAddParent() {
    return _isAddParent;
}

void MonsterObject::changeStateToMove() {
    changeState(K_STATE_MOVING_UP);
}

bool MonsterObject::strikenMouse(cocos2d::CCTouch *pTouch) {
    
    if (_isAddParent && getCurrentState() == K_STATE_IDLE ) {
        CCNode* midNode = this->getChildByTag(Mid_Node_Tag);
        CCPoint pt = midNode->convertToNodeSpace(pTouch->getLocation());
        
        if (midNode->boundingBox().containsPoint(pt)) {
            
            CharactarHandler::GameSkillHurtInfo hurtinfo;
            hurtinfo._hurt = 10;
            CharactarHandler::doHurt(NULL, this, hurtinfo);
            
            return true;
        }
    }
    
    return false;
}


