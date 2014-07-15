//
//  PitObject.cpp
//  HappyMouse
//
//  Created by xUanBing on 14-7-15.
//
//

#include "PitObject.h"
#include "CCScale9ProgressBar.h"
#include "CCSpriteExt.h"

PitObject::PitObject() {
    
}

PitObject::~PitObject() {
    
}

PitObject* PitObject::create() {
    PitObject* obj = new PitObject();
    
    if (obj && obj->init()) {
        obj->autorelease();
        return obj;
    } else {
        CC_SAFE_DELETE(obj);
        return NULL;
    }
    
}

bool PitObject::init() {
    
    return true;
}

