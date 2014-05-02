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
#include "BattleUI.h"

#define IsOpenBox2dDebugDraw true

const int TagBgView = BASE_TAG + 1;
const int TagBg     = BASE_TAG + 2;
const int TagHero   = BASE_TAG + 3;

const float Gravity = -9.8f;

BattleView::BattleView(){
    
}

BattleView::~BattleView() {
    
}

bool BattleView::init() {
    if (!CCLayer::init()) {
        return false;
    }
    this->setTouchEnabled(true);
    
    initBattleUi();
    
    CCSpriteExt* bg = CCSpriteExt::create("back_1.png");
    bg->setScaleX(this->getContentSize().width / bg->getContentSize().width );
    bg->setScaleY(this->getContentSize().height / bg->getContentSize().height);
    this->addChild(bg, 0, TagBg);
    LayoutUtil::layoutParentTop(bg);
    
    GameBgRollView* bgView = GameBgRollView::create();
    this->addChild(bgView, 0, TagBgView);
    
    initPhysicalWorld();
    
    _hero = HeroSprite::create();
    _hero->runDefault();
    this->addChild(_hero, 10001, TagHero);
    _hero->setPosition(ccp(120, 500));
    _hero->initPhysical(_physicsWorld, _levelHelperLoader);
    
//    this->runAction(CCFollow::create(hero));
    
    if (IsOpenBox2dDebugDraw) {
        Box2dUtil::openDebugBox2dDraw(_physicsWorld);
        this->getChildByTag(TagBgView)->setVisible(!IsOpenBox2dDebugDraw);
        this->getChildByTag(TagBg)->setVisible(!IsOpenBox2dDebugDraw);
    }else {
        this->getChildByTag(TagBgView)->setVisible(!IsOpenBox2dDebugDraw);
    }
    
    this->scheduleUpdate();
    return true;
}

void BattleView::initBattleUi() {
    _battleUI = BattleUI::createFromCCB();
    this->addChild(_battleUI, BASE_TAG* 2);
}

void BattleView::initPhysicalWorld() {
    b2Vec2 gravity = b2Vec2(0, Gravity);
    
    _physicsWorld = new b2World(gravity);
    _physicsWorld->SetAllowSleeping(true);
    
    _levelHelperLoader = new LevelHelperLoader("battleLevel_1.plhs");
    _levelHelperLoader->addObjectsToWorld(_physicsWorld, this);
    _levelHelperLoader->createPhysicBoundaries(_physicsWorld);
    _levelHelperLoader->createGravity(_physicsWorld);

}


void BattleView::update(float dt) {
    CCLayer::update(dt);
    _levelHelperLoader->update(dt);
    
    if (_physicsWorld) {
        Box2dUtil::updateBox2dWorldInLevelHelp(_physicsWorld, _levelHelperLoader, dt);
    }
}

void BattleView::registerWithTouchDispatcher() {
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, getTouchPriority(), false);
}

bool BattleView::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
    
//    HeroSprite* hero = (HeroSprite*) this->getChildByTag(TagHero);
    _hero->jump();
    
    return true;
}

void BattleView::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
    
}

void BattleView::draw() {
    CCLayer::draw();
    ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );
    kmGLPushMatrix();
    _physicsWorld->DrawDebugData();
    kmGLPopMatrix();
    CHECK_GL_ERROR_DEBUG();
}