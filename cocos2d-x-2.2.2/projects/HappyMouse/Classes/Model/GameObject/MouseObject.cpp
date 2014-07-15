//
//  MouseObject.cpp
//  HappyMouse
//
//  Created by xUanBing on 14-7-15.
//
//

#include "MouseObject.h"

MouseObject::MouseObject() {
    
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
    return true;
}
