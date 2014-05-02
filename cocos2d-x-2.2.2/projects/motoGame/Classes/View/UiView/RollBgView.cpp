//
//  RollBgView.cpp
//  motoGame
//
//  Created by xUanBing on 14-3-30.
//
//

#include "RollBgView.h"
#include "LayoutUtil.h"
#include "AnimNode.h"
#include "ConstansDef.h"
#include "LevelHelperLoader.h"
#include "b2World.h"
#include "GLES-Render.h"
#include "Box2dUtil.h"

const static int KTagBgOne = 1001;
const static int KTagBgTwo = 1002;

#define  X_MOVE_SPEED     -0
#define  X_Acceleration   0.1f

RollBgView::RollBgView() : _b2World(NULL), _levelHelper(NULL), _lhSprite(NULL),_isNeedAcceleration(false){
    
}

RollBgView::~RollBgView() {
    
}


bool RollBgView::init() {
    if(!CCLayer::init()){
		return false;
	}

    CCSprite * bg1 = CCSprite::create("bg.jpg");
    bg1->setAnchorPoint(CCPointZero);
    this->addChild(bg1, 0, KTagBgOne);
    LayoutUtil::layoutParentLeft(bg1);
    
    CCSprite * bg2 = CCSprite::create("bg.jpg");
    bg2->setAnchorPoint(CCPointZero);
    this->addChild(bg2, 0, KTagBgTwo);
    LayoutUtil::layoutRight(bg2, bg1);
    
    bg1->setVisible(false);
    bg2->setVisible(false);
    
    AnimNode* anim = AnimNode::createFlashAnimNode("xx_m_204601d.png", "xx_m_204601d.plist", "xx_m_204601d.xml",
                                                   "walk", "xx_m_204601d");
    anim->setContentSize(CCSize(256, 256));
    anim->runAnimation("walk");
    anim->setAnchorPoint(CCPointZero);
    bg1->addChild(anim, 1001);
    LayoutUtil::layoutParentLeft(anim, 800, 0);
    anim->setVisible(false);
    
    initLhWorld();
    
    CCSprite* coinSprite = CCSprite::create("res_crystal.png");
    this->addChild(coinSprite, 1000);
    LayoutUtil::layoutParentLeft(coinSprite, 100, 0);
    
    coinSprite->setTag(LH_TAG_STAR);
    
    b2Filter filter;
    filter.maskBits = 3;
    filter.categoryBits = 32;
    filter.groupIndex = 0;
    
    b2FixtureDef def;
    def.density = 0.0f;
    def.isSensor = false;
    def.filter = filter;

    Box2dUtil::addBoxBodyForSprite(_b2World, _levelHelper, coinSprite, def);
    
    this->scheduleUpdate();
    
    Box2dUtil::openDebugBox2dDraw(_b2World);
    this->setTouchEnabled(true);
    
	return true;
}

void RollBgView::initLhWorld() {
    b2Vec2 gravity = b2Vec2(0.0f, 10.0f);
    
    _b2World = new b2World(gravity);
    _b2World->SetAllowSleeping(true);
    
    this->loadPhysicWorldWithLayer("kala_level.plhs", this);
    _lhSprite = _levelHelper->spriteWithUniqueName("kuwalio_stand");
}

void RollBgView::update(float t) {
    
    CCSprite * bg1 = (CCSprite *)this->getChildByTag(KTagBgOne);
    CCSprite * bg2 = (CCSprite *)this->getChildByTag(KTagBgTwo);
    
    if (bg1->getPositionX() <= -1 * bg1->getContentSize().width) {
        LayoutUtil::layoutRight(bg1, bg2, X_MOVE_SPEED);
    } else {
        bg1->setPosition(ccpAdd(bg1->getPosition(), ccp(X_MOVE_SPEED, 0)));
    }

    if (bg2->getPositionX() <= -1 * bg2->getContentSize().width) {
        LayoutUtil::layoutRight(bg2, bg1);
    } else {
        bg2->setPosition(ccpAdd(bg2->getPosition(), ccp(X_MOVE_SPEED, 0)));
    }
    
    _levelHelper->update(t);
    this->updateB2World(t);
}

void RollBgView::updateB2World(float dt) {
    if (_b2World) {
        Box2dUtil::updateBox2dWorldInLevelHelp(_b2World, _levelHelper, dt);
    }
    
    
    
}

void RollBgView::loadPhysicWorldWithLayer(const char* levelFile, CCLayer *layer) {
    
    _levelHelper = new LevelHelperLoader(levelFile);
    _levelHelper->addObjectsToWorld(_b2World, layer);
    _levelHelper->createPhysicBoundaries(_b2World);
    _levelHelper->createGravity(_b2World);
    
    if (!_levelHelper->hasPhysicBoundaries()) {
        Box2dUtil::createPhysicBoundaries(_b2World, _levelHelper->physicBoundariesRect().size);
    }
    
    _levelHelper->useLevelHelperCollisionHandling();//这个方法是必要的，否则碰撞将不会执行
    _levelHelper->registerPreCollisionCallbackBetweenTagA(LH_TAG_STAR, LH_TAG_HERO, this,
                    callfuncO_selector(RollBgView::preCollisionBetweenHeroTreeAndCoin));
}


void RollBgView::preCollisionBetweenHeroTreeAndCoin(LHContactInfo *contact) {
    
    CCLOG("%s", "coin hero collision");
}


void RollBgView::draw() {
    CCLayer::draw();
    
    ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );
    
    kmGLPushMatrix();
    
    _b2World->DrawDebugData();
    
    kmGLPopMatrix();
    
    CHECK_GL_ERROR_DEBUG();
}

//control

void RollBgView::registerWithTouchDispatcher() {
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, getTouchPriority(), false);
}

bool RollBgView::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
    if (!_isNeedAcceleration) {
        
        if (_lhSprite) {
            
            if (_lhSprite->getBody()->GetLinearVelocity().x < 10) {
                b2Vec2 linearVec  = _lhSprite->getBody()->GetLinearVelocity();
                linearVec.x = 10;
                _lhSprite->getBody()->SetLinearVelocity(linearVec);
            } else {
                b2Vec2 linearVec  = _lhSprite->getBody()->GetLinearVelocity();
                linearVec.x = 1 * X_Acceleration;
                _lhSprite->getBody()->SetLinearVelocity(linearVec);
            }
            
        }

        _isNeedAcceleration = true;
    }
    
    return true;
}

void RollBgView::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
    if (_isNeedAcceleration) {
        
        _isNeedAcceleration = false;
    }
}



