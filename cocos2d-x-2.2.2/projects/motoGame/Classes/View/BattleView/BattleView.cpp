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
#include "GameController.h"
#include "NotifyMessageDef.h"

#define IsOpenBox2dDebugDraw false

const int TagBgView = BASE_TAG + 1;
const int TagBg     = BASE_TAG + 2;
const int TagHero   = BASE_TAG + 3;

const float Gravity = -10.0f;

BattleView::BattleView() :_battleUI(NULL), _gameController(NULL), _physicsWorld(NULL), _levelHelperLoader(NULL),_lhLayer(NULL),
_gameParallaxLayer(NULL),_curSceneState(nullScene) {
    
}

BattleView::~BattleView() {
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, KNotifyStartBattleMessage);
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, KNotifyPauseBattleMessage);
}

bool BattleView::init() {
    if (!CCLayer::init()) {
        return false;
    }
    
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this,callfuncO_selector(BattleView::onNotifyBattleStartMessage),KNotifyStartBattleMessage, NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(BattleView::onNotifyBattlePauseMessage), KNotifyPauseBattleMessage, NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(BattleView::onNotifyEnergyFullMessage), KNotifyEnergyFullMessage, NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(BattleView::onNotifyEnergyEmptyMessage), KNotifyEnergyEmptyMessage, NULL);
    
    this->setTouchEnabled(true);
    _gameController = GameController::sharedInstance();
    
    initBattleUi();
    
    CCSpriteExt* bg = CCSpriteExt::create("back_1.png");
    bg->setScaleX(this->getContentSize().width / bg->getContentSize().width );
    bg->setScaleY(this->getContentSize().height / bg->getContentSize().height);
    this->addChild(bg, 0, TagBg);
    LayoutUtil::layoutParentTop(bg);
    
    _rollView = GameBgRollView::create();
    this->addChild(_rollView, 0, TagBgView);
    
    initPhysicalWorld();
    
    HeroSprite* hero = HeroSprite::create();
    this->addChild(hero, 10001, TagHero);
    hero->setPosition(ccp(300, 500));
    hero->initPhysical(_physicsWorld, _levelHelperLoader);
    hero->runDefault();
    
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
    
    _gameParallaxLayer = _levelHelperLoader->parallaxNodeWithUniqueName("layer1");
    
    //碰撞检测
    _levelHelperLoader->useLevelHelperCollisionHandling();
    
    _levelHelperLoader->registerBeginOrEndCollisionCallbackBetweenTagA(LH_TAG_STAR, LH_TAG_HERO, this,callfuncO_selector(BattleView::postCollisionBetweenHeroAndCoin));
    _levelHelperLoader->registerPostCollisionCallbackBetweenTagA(LH_TAG_FLOOR, LH_TAG_HERO, this,callfuncO_selector(BattleView::postCollisionBetweenHeroAndFloor));
    _levelHelperLoader->registerPostCollisionCallbackBetweenTagA(LH_TAG_TREE, LH_TAG_HERO, this, callfuncO_selector(BattleView::postCollisionBetweenHeroAndTree));
    _levelHelperLoader->registerBeginOrEndCollisionCallbackBetweenTagA(LH_TAG_BOTTOMBORDER, LH_TAG_HERO, this, callfuncO_selector(BattleView::postCollisionBetweenHeroAndBottomBorder));

}


void BattleView::update(float dt) {
    CCLayer::update(dt);
    
    if (_curSceneState == nullScene ) {
        return;
    }
    
    _levelHelperLoader->update(dt);
    
    if (_physicsWorld) {
        Box2dUtil::updateBox2dWorldInLevelHelp(_physicsWorld, _levelHelperLoader, dt);
    }
}

void BattleView::registerWithTouchDispatcher() {
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, getTouchPriority(), false);
}

bool BattleView::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
    
    if (_curSceneState == nullScene || _curSceneState == pauseScene) {
        return true;
    }
    
    _gameController->makeHeroJump();
    
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

void BattleView::postCollisionBetweenHeroAndCoin(LHContactInfo *contact) {

    b2Body* starBody = contact->bodyA;
    LHSprite* star = (LHSprite*)starBody->GetUserData();
    
    if (star->isVisible()) {
        star->setVisible(false);
        star->removeFromParent(); //TODO:xUanBing 将刚体删除
        _gameController->makeHeroObtainStar();
    }
    
}

void BattleView::postCollisionBetweenHeroAndFloor(LHContactInfo *contact) {

    const b2ContactImpulse* impulse = contact->impulse;
    if (impulse && impulse->normalImpulses[0] > 1000) {
        _gameController->makeHeroFallFloor();
    }
}

void BattleView::postCollisionBetweenHeroAndTree(LHContactInfo *contact) {
    const b2ContactImpulse* impulse = contact->impulse;
    if (impulse && impulse->normalImpulses[0] > 1000) {
        _gameController->makeHeroFallFloor();
    }
}

void BattleView::postCollisionBetweenHeroAndBottomBorder(LHContactInfo *contact) {
    _gameController->makeHeroDie();
    
    changeSceneState(pauseScene);
}

void BattleView::changeSceneState(SceneState state) {
    
    if (_curSceneState == state) {
        return;
    }
    
    switch (state) {
        case nullScene:
            
            break;
        case startScene:
            _rollView->setMoveSpeed(2);
            _gameParallaxLayer->setSpeed(15);
            break;
        case accelerateScene:
            _rollView->setMoveSpeed(4);
            _gameParallaxLayer->setSpeed(30);
            break;
        case pauseScene:
            _rollView->setMoveSpeed(0);
            _gameParallaxLayer->setSpeed(0);
            break;
    }
    
    _curSceneState = state;
}

void BattleView::onNotifyBattleStartMessage(cocos2d::CCObject *pSender) {
    changeSceneState(startScene);
}

void BattleView::onNotifyBattlePauseMessage(cocos2d::CCObject *pSender) {
    changeSceneState(pauseScene);
}

void BattleView::onNotifyEnergyFullMessage(cocos2d::CCObject *pSender) {
    changeSceneState(accelerateScene);
}

void BattleView::onNotifyEnergyEmptyMessage(cocos2d::CCObject *pSender) {
    changeSceneState(startScene);
}
