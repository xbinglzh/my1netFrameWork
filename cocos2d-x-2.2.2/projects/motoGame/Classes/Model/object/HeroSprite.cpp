//
//  HeroSprite.cpp
//  motoGame
//
//  Created by xUanBing on 14-4-28.
//
//

#include "HeroSprite.h"


HeroSprite::HeroSprite() : _curHeroState(HERO_NULL), _animNode(NULL) {
    
}

HeroSprite::~HeroSprite() {
    
}

HeroSprite* HeroSprite::create() {
    HeroSprite* pRet = new HeroSprite();
    if (pRet) {
        if (pRet->init()) {
            pRet->autorelease();
            return pRet;
        }
        CC_SAFE_DELETE(pRet);
    }
    return NULL;
}


bool HeroSprite::init() {
    if (!CCSprite::init()) {
        return false;
    }
    
    
    
    return true;
}

void HeroSprite::changeHeroState(HeroState state) {
    if (_curHeroState == state) {
        return;
    }
    
    switch (state) {
        case HERO_NULL:
            break;
        case HERO_RUN:
            break;
        case HERO_JUMP:
            break;
        case HERO_BROKE_JUMP:
            break;
        case HERO_BROKE_RUN:
            break;
        case HERO_BROKE_RUN_JUMP:
            break;
    }
    
    _curHeroState = state;
    
    
}

