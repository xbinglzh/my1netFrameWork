//
//  GameView.cpp
//  motoGame
//
//  Created by xUanBing on 14-4-6.
//
//

#include "GameView.h"
#include "GLES-Render.h"
#include "Box2dUtil.h"
#include "GameBgRollView.h"
#include "ConstansDef.h"
#include "ParticleEffect.h"
#include "AnimNode.h"
#include "LayoutUtil.h"

#define IsOpenBox2dDebugDraw false

const int TagBgView = BASE_TAG + 1;

GameView::GameView() : _lhSprite(NULL), _levelHelper(NULL), _b2World(NULL) {
    
}

GameView::~GameView() {
    
}

bool GameView::init() {
    if(!CCLayer::init()){
		return false;
	}
    
    GameBgRollView* bgView = GameBgRollView::create();
    this->addChild(bgView, 0, TagBgView);
    
    initPhysicalWorld();
    return true;
}

void GameView::initPhysicalWorld() {
    b2Vec2 gravity = b2Vec2(0.0f, 10.0f);
    _b2World = new b2World(gravity);
    _b2World->SetAllowSleeping(true);
    
    _levelHelper = new LevelHelperLoader("level1.plhs");
    _levelHelper->addObjectsToWorld(_b2World, this);
    _levelHelper->createPhysicBoundaries(_b2World);
    _levelHelper->createGravity(_b2World);
    
    if (!_levelHelper->hasPhysicBoundaries()) {
        Box2dUtil::createPhysicBoundaries(_b2World, _levelHelper->physicBoundariesRect().size);
    }
    
//    _levelHelper->useLevelHelperCollisionHandling();//这个方法是必要的，否则碰撞将不会执行
    
    if (IsOpenBox2dDebugDraw) {
        Box2dUtil::openDebugBox2dDraw(_b2World);
        this->getChildByTag(TagBgView)->setVisible(!IsOpenBox2dDebugDraw);
    }else {
        this->getChildByTag(TagBgView)->setVisible(!IsOpenBox2dDebugDraw);
    }
    
    ParticleEffect* effect = ParticleEffect::create("fire.plist");
    CCLOG("effect w : %f, h : %f", effect->getContentSize().width, effect->getContentSize().height);
    this->addChild(effect, 10000, 10000);
    
    AnimNode* hero = AnimNode::createFlashAnimNode("hero_1_pao.png", "hero_1_pao.plist", "hero_1_pao.xml", "play", "hero_1_pao");
    
    
//    AnimNode* hero = AnimNode::createFlashAnimNode("xx_m_100041.png", "xx_m_100041.plist", "xx_m_100041.xml",
//                                                   "walk", "xx_m_100041");
    
    hero->runAnimation("play");
    hero->setContentSize(CCSizeMake(139, 264));
    this->addChild(hero, 10001, 0);
//    hero->setPosition(ccp(100, 100));
    
    LayoutUtil::layoutParentCenter(hero);
}

void GameView::update(float dt) {
    CCLayer::update(dt);
    _levelHelper->update(dt);
    
    if (_b2World) {
        Box2dUtil::updateBox2dWorldInLevelHelp(_b2World, _levelHelper, dt);
    }
}

void GameView::registerWithTouchDispatcher() {
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, getTouchPriority(), false);
}

bool GameView::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
    CCLayer::ccTouchBegan(pTouch, pEvent);
    return true;
}

void GameView::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
    CCLayer::ccTouchEnded(pTouch, pEvent);
    
}

void GameView::draw() {
    CCLayer::draw();
    ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );
    kmGLPushMatrix();
    _b2World->DrawDebugData();
    kmGLPopMatrix();
    CHECK_GL_ERROR_DEBUG();
}
