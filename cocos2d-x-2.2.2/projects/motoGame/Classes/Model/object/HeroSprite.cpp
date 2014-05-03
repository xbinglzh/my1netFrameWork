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
#include "LevelHelperLoader.h"
#include "Box2dUtil.h"
#include "NotifyMessageDef.h"

const std::string HERO_ANIM_ID = "100001#display";
const int         HERO_TAG_ID  =  100001;

HeroSprite::HeroSprite() : _curHeroState(HERO_NULL), _animNode(NULL) {
    
}

HeroSprite::~HeroSprite() {
    _curHeroState = HERO_NULL;
    CCNotificationCenter::sharedNotificationCenter()->removeAllObservers(this);
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
    
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(HeroSprite::onNotifyHeroJump), KNotifyMakeHeroJumpMessage, NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(HeroSprite::onNotifyHeroFallFloor), KNotifyMakeHeroFallFloorMessage, NULL);
    
    return true;
}

void HeroSprite::initPhysical(b2World* physicsWorld, LevelHelperLoader* levelHelperLoader) {
    this->setTag(LH_TAG_HERO);
    
    CCLOG("HeroSprite w :%f,h : %f", this->getContentSize().width, this->getContentSize().height);
    
    b2Filter filter;
    filter.maskBits = 46;
    filter.categoryBits = 16;
    filter.groupIndex = 0;
    
    b2FixtureDef fixtureDef;
    fixtureDef.density = 1000.0f;
    fixtureDef.isSensor = false;
    fixtureDef.friction = 0.0f;
    fixtureDef.restitution = 0.0f;
    fixtureDef.filter = filter;
    
    b2PolygonShape polygon;
    b2Vec2 vec2 = levelHelperLoader->pixelToMeters(ccp(this->getContentSize().width, this->getContentSize().height));
    polygon.SetAsBox(vec2.x, vec2.y);
    fixtureDef.shape = &polygon;
    
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.linearVelocity = b2Vec2(0, 0);
    bodyDef.position = levelHelperLoader->pointsToMeters(this->getPosition());
    bodyDef.userData = this;
    bodyDef.fixedRotation = true;
    bodyDef.allowSleep = false;
    
    if (physicsWorld && levelHelperLoader) {
        _heroBody = physicsWorld->CreateBody(&bodyDef);
        _heroBody->CreateFixture(&fixtureDef);
    }
    
}

void HeroSprite::appendLinearImpulse(b2Vec2 desiredVel) {
    b2Vec2 vel = _heroBody->GetLinearVelocity();
    float m = _heroBody->GetMass();
    b2Vec2 velChange = desiredVel - vel;
    b2Vec2 impluse = m * velChange;
    _heroBody->ApplyLinearImpulse(impluse, _heroBody->GetWorldCenter());
}

void HeroSprite::changeHeroState(HeroState state) {
    if (this->_curHeroState == state) {
        return;
    }
    
    switch (state) {
        case HERO_NULL:
            _animNode->stopAnimation();
            break;
        case HERO_RUN:
            _animNode->runAnimation("play");
            this->appendLinearImpulse(b2Vec2(0, 0));
            break;
        case HERO_JUMP:
            _animNode->runAnimation("play1");
            this->appendLinearImpulse(b2Vec2(0, 5));
            break;
        case HERO_BROKE_JUMP:
            _animNode->runAnimation("play2");
            this->appendLinearImpulse(b2Vec2(0, 8));
            break;
        case HERO_BROKE_RUN:
            break;
        case HERO_BROKE_RUN_JUMP:
            break;
    }
    
    this->_curHeroState = state;
    
}

void HeroSprite::runDefault() {
    changeHeroState(HERO_RUN);
}

void HeroSprite::onNotifyHeroJump(CCObject* pSender) {
    
    if (_curHeroState == HERO_RUN) {
        changeHeroState(HERO_JUMP);
    }else if (_curHeroState == HERO_JUMP) {
        changeHeroState(HERO_BROKE_JUMP);
    }
    
}

void HeroSprite::onNotifyHeroFallFloor(cocos2d::CCObject *pSender) {
    changeHeroState(HERO_RUN);
}

