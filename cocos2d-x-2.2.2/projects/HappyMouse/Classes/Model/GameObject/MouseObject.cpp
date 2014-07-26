//
//  MouseObject.cpp
//  HappyMouse
//
//  Created by xUanBing on 14-7-15.
//
//

#include "MouseObject.h"
#include "AnimNode.h"
#include "CCSpriteExt.h"
#include "CCScale9ProgressBar.h"
#include "LayoutUtil.h"
#include "AudioManager.h"
#include "AnimUtils.h"

MouseObject::MouseObject() :
_dizzyAnim(NULL),
_sprite(NULL),
_hpBar(NULL) ,
_curState(MouseNormal),
_contentNode(NULL),
_hp(100) {
    
}

MouseObject::~MouseObject() {
    
}

MouseObject* MouseObject::create() {
    MouseObject* obj = new MouseObject();
    
    if (obj && obj->init()) {
        obj->autorelease();
        return obj;
    } else {
        CC_SAFE_DELETE(obj);
        return NULL;
    }
    
}

bool MouseObject::init() {
    _contentNode = CCNode::create();
    _sprite = CCSpriteExt::create("mouse1.png");
    
    _dizzyAnim = AnimUtils::createAnimById("100002#skill",NULL);
    _dizzyAnim->runAnimation("happening");
    
    
    _contentNode->setContentSize(_sprite->getContentSize());
    this->setContentSize(_contentNode->getContentSize());
    
    CCDrawNode* shap = CCDrawNode::create();
    
    CCPoint point[4] = {
        ccp(0,0),
        ccp(_contentNode->getContentSize().width, 0),
        ccp(_contentNode->getContentSize().width, _contentNode->getContentSize().height + 50),
        ccp(0, _contentNode->getContentSize().height + 50)
    };
    
    shap->drawPolygon(point, 4, ccc4f(255, 255, 255, 255), 2, ccc4f(255, 255, 255, 255));
    
    CCClippingNode* cliper = CCClippingNode::create();
    cliper->setStencil(shap);
    cliper->setAnchorPoint(ccp(0, 0));
    cliper->setContentSize(_contentNode->getContentSize());
    
    _contentNode->addChild(_sprite);
    LayoutUtil::layoutParentBottom(_sprite);
    
    _contentNode->addChild(_dizzyAnim);
    LayoutUtil::layoutTop(_dizzyAnim, _sprite, 0, -130);
    _dizzyAnim->setVisible(false);
    
    cliper->addChild(_contentNode);
    LayoutUtil::layoutParentBottom(_contentNode, 0, -1 * _contentNode->getContentSize().height);
    
    this->addChild(cliper);
    LayoutUtil::layoutParentBottom(cliper);
    
    return true;
}

void MouseObject::changeMouseState(CCInteger* targetState) {
    
    if (_curState == targetState->getValue()) {
        return;
    }
    
    CCLOG("changeState : current : %d -> target : %d", _curState, targetState->getValue());
    
    switch (targetState->getValue()) {
            
        case MouseNormal:
            
            break;
        case MouseArise:
            ariseMouse();
            break;
        case MouseDealy:
            _dizzyAnim->setVisible(false);
            delayMouse();
            break;
        case MouseDrop:
            dropMouse();
            break;
        case MouseDead:
            
            break;
        case MouseStriken:
            AudioManager::sharedInstance()->playAudioById(K_AudioEffect_click, false);
            dizzyMouse();
            break;
    }
    
    this->_curState = targetState->getValue();
}

int MouseObject::getCurrentState() {
    return _curState;
}

void MouseObject::ariseMouse() {
    
    if (_curState != MouseNormal) {
        return;
    }
    
    CCMoveBy* ation_moveTo = CCMoveBy::create(0.3f, CCPointMake(0, _contentNode->getContentSize().height));
    CCCallFuncO* action_call = CCCallFuncO::create(this, callfuncO_selector(MouseObject::changeMouseState), CCInteger::create(MouseDealy));
    
    _contentNode->runAction(CCSequence::create(ation_moveTo, action_call, NULL));
    
}

void MouseObject::delayMouse() {
    
    CCDelayTime* action_delay = CCDelayTime::create(0.5f);
    CCCallFuncO* action_call = CCCallFuncO::create(this, callfuncO_selector(MouseObject::changeMouseState), CCInteger::create(MouseDrop));
    _contentNode->runAction(CCSequence::create(action_delay, action_call, NULL));
}

void MouseObject::dropMouse() {
    
    if (_curState == MouseStriken) {
        return;
    }
    
    CCMoveBy* ation_moveTo = CCMoveBy::create(0.3f, CCPointMake(0, -1 * _contentNode->getContentSize().height));
    CCCallFuncO* action_call = CCCallFuncO::create(this, callfuncO_selector(MouseObject::changeMouseState), CCInteger::create(MouseNormal));
        
    _contentNode->runAction(CCSequence::create(ation_moveTo, action_call, NULL));
    
}

void MouseObject::dizzyMouse() {
    _dizzyAnim->setVisible(true);
    
    CCDelayTime* action_delay = CCDelayTime::create(1.0f);
    CCCallFuncO* action_call = CCCallFuncO::create(this, callfuncO_selector(MouseObject::changeMouseState), CCInteger::create(MouseDealy));
    
    _contentNode->runAction(CCSequence::create(action_delay, action_call, NULL));
}

bool MouseObject::strikenMouse(cocos2d::CCTouch *pTouch) {
    
    if (_curState != MouseDealy) {
        return false;
    }
    
    CCPoint pt = _contentNode->convertToNodeSpace(pTouch->getLocation());
    
    if (_contentNode && _contentNode->boundingBox().containsPoint(pt)) {
        
        this->changeMouseState(CCInteger::create(MouseStriken));
        return true;
    }
    
    return false;
}


