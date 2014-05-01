//
//  BattleView.cpp
//  motoGame
//
//  Created by xUanBing on 14-4-24.
//
//

#include "BattleView.h"
#include "LayoutUtil.h"
#include "ConstansDef.h"
#include "GameBgRollView.h"
#include "CCSpriteExt.h"
#include "AnimNode.h"
#include "Box2dUtil.h"
#include "HeroSprite.h"

#define IsOpenBox2dDebugDraw false
const int TagBgView = BASE_TAG + 1;
const int TagBg     = BASE_TAG + 2;

BattleView::BattleView(){
    
}

BattleView::~BattleView() {
    
}

bool BattleView::init() {
    if (!CCLayer::init()) {
        return false;
    }
    
    CCSpriteExt* bg = CCSpriteExt::create("back_1.png");
    bg->setScaleX(this->getContentSize().width / bg->getContentSize().width );
    bg->setScaleY(this->getContentSize().height / bg->getContentSize().height);
    this->addChild(bg, 0, TagBg);
    LayoutUtil::layoutParentTop(bg);
    
    GameBgRollView* bgView = GameBgRollView::create();
    this->addChild(bgView, 0, TagBgView);
    
    initPhysicalWorld();
    
    HeroSprite* hero = HeroSprite::create();
    hero->changeHeroState(HeroSprite::HERO_BROKE_JUMP);
    this->addChild(hero, 10001, 0);
    hero->setPosition(ccp(100, 100));
    
    if (IsOpenBox2dDebugDraw) {
        Box2dUtil::openDebugBox2dDraw(_physicsWorld);
        this->getChildByTag(TagBgView)->setVisible(!IsOpenBox2dDebugDraw);
        this->getChildByTag(TagBg)->setVisible(!IsOpenBox2dDebugDraw);
    }else {
        this->getChildByTag(TagBgView)->setVisible(!IsOpenBox2dDebugDraw);
    }
    
    return true;
}

void BattleView::initPhysicalWorld() {
    b2Vec2 gravity = b2Vec2(0, 9.8f);
    _physicsWorld = new b2World(gravity);
    _physicsWorld->SetAllowSleeping(true);
    
    _levelHelperLoader = new LevelHelperLoader("battleLevel_1.plhs");
    _levelHelperLoader->addObjectsToWorld(_physicsWorld, this);
    _levelHelperLoader->createPhysicBoundaries(_physicsWorld);
    _levelHelperLoader->createGravity(_physicsWorld);
    
}


void BattleView::update(float dt) {
    CCLayer::update(dt);
    
}

void BattleView::registerWithTouchDispatcher() {
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, getTouchPriority(), false);
}

bool BattleView::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
    CCLayer::ccTouchBegan(pTouch, pEvent);
    return true;
}

void BattleView::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
    CCLayer::ccTouchEnded(pTouch, pEvent);
    
}

void BattleView::draw() {
    CCLayer::draw();
    ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );
    kmGLPushMatrix();
    _physicsWorld->DrawDebugData();
    kmGLPopMatrix();
    CHECK_GL_ERROR_DEBUG();
}