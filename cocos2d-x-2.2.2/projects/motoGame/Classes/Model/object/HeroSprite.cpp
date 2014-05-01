//
//  HeroSprite.cpp
//  motoGame
//
//  Created by xUanBing on 14-4-28.
//
//

#include "HeroSprite.h"
#include "GameConfig.h"
#include "LayoutUtil.h"

const std::string HERO_ANIM_ID = "100001#display";
const int         HERO_TAG_ID  =  100001;

HeroSprite::HeroSprite() : _curHeroState(HERO_NULL), _animNode(NULL) {
    
}

HeroSprite::~HeroSprite() {
    _curHeroState = HERO_NULL;
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
    
    _animNode = AnimNode::createAnim(GameConfig::sharedInstance()->getAnimationById(HERO_ANIM_ID.c_str()), NULL);
    this->addChild(_animNode, 0, HERO_TAG_ID);
    this->setContentSize(_animNode->getContentSize());
    LayoutUtil::layoutParentCenter(_animNode);
    
    return true;
}

void HeroSprite::changeHeroState(HeroState state) {
    if (_curHeroState == state) {
        return;
    }
    
    switch (state) {
        case HERO_NULL:
            _animNode->stopAnimation();
            break;
        case HERO_RUN:
            _animNode->runAnimation("play");
            break;
        case HERO_JUMP:
            _animNode->runAnimation("play1");
            break;
        case HERO_BROKE_JUMP:
            _animNode->runAnimation("play2");
            break;
        case HERO_BROKE_RUN:
            break;
        case HERO_BROKE_RUN_JUMP:
            break;
    }
    
    _curHeroState = state;
    
    
}

