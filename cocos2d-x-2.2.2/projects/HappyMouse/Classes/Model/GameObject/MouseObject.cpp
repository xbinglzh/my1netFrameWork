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

MouseObject::MouseObject() : _animNode(NULL), _sprite(NULL), _hpBar(NULL) {
    
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
    
    _sprite = CCSpriteExt::create("mouse1.png");
    this->setContentSize(_sprite->getContentSize());
    this->addChild(_sprite);
    LayoutUtil::layoutParentCenter(_sprite);
    
    
    return true;
}
