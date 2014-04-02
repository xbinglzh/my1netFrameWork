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

const static int KTagBgOne = 1001;
const static int KTagBgTwo = 1002;

#define  X_MOVE_SPEED -0

RollBgView::RollBgView() : _b2World(NULL), _levelHelper(NULL), _lhSprite(NULL){
    
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
    
    AnimNode* anim = AnimNode::createFlashAnimNode("xx_m_204601d.png", "xx_m_204601d.plist", "xx_m_204601d.xml",
                                                   "walk", "xx_m_204601d");
    anim->setContentSize(CCSize(256, 256));
    anim->runAnimation("walk");
    anim->setAnchorPoint(CCPointZero);
    bg1->addChild(anim, 1001);
    LayoutUtil::layoutParentLeft(anim, 800, 0);
    
    CCSprite * bg2 = CCSprite::create("bg.jpg");
    bg2->setAnchorPoint(CCPointZero);
    this->addChild(bg2, 0, KTagBgTwo);
    LayoutUtil::layoutRight(bg2, bg1);

    this->scheduleUpdate();
    
    initLhWorld();
    
    this->configDebugBox2dDraw();
    
	return true;
}

void RollBgView::initLhWorld() {
    b2Vec2 gravity = b2Vec2(0.0f, 10.0f);
    bool doSleep = true;
    
    _b2World = new b2World(gravity);
    _b2World->SetAllowSleeping(doSleep);
    
    this->loadPhysicWorldWithLayer("kala_level.plhs", this);
    
//    _lhSprite = _levelHelper->createBatchSpriteWithUniqueName("kuwalio_stand");
    _lhSprite = _levelHelper->spriteWithUniqueName("kuwalio_stand");
//    _lhSprite->getBody()->SetLinearVelocity(b2Vec2(20.0f,0.0));
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
		//物理节点刷新
        static double UPDATE_INTERVAL = 1.0f/60.0f;
        static double MAX_CYCLES_PER_FRAME = 5;
        static double timeAccumulator = 0;
        timeAccumulator += dt;
        
        if (timeAccumulator > (MAX_CYCLES_PER_FRAME * UPDATE_INTERVAL)) {
            timeAccumulator = UPDATE_INTERVAL;
        }
        
		int velocityIterations = 1;
		int positionIterations = 1;
        
        while (timeAccumulator >= UPDATE_INTERVAL) {
            timeAccumulator -= UPDATE_INTERVAL;
            _b2World->Step(UPDATE_INTERVAL, velocityIterations, positionIterations);
            
            for (b2Body* body = _b2World->GetBodyList(); body; body = body->GetNext()) {
                if (body->GetUserData() != NULL) {
                    CCSprite* sprite = (CCSprite*) body->GetUserData();
                    sprite->setPosition(_levelHelper->metersToPoints(body->GetPosition()));
                    sprite->setRotation( -1 * CC_RADIANS_TO_DEGREES(body->GetAngle()));
                }
            }
        }
        
//        _lhSprite->setPosition(CCPointMake(_lhSprite->getBody()->GetPosition().x * PTM_RATIO,
//                                           _lhSprite->getBody()->GetPosition().y * PTM_RATIO));
    }
}

void RollBgView::loadPhysicWorldWithLayer(const char* levelFile, CCLayer *layer) {
    
    //加载带有物理属性的层
    _levelHelper = new LevelHelperLoader(levelFile);
    _levelHelper->addObjectsToWorld(_b2World, layer);
    _levelHelper->createPhysicBoundaries(_b2World);
    _levelHelper->createGravity(_b2World);
    
    //假如没有设置地面体
    if (!_levelHelper->hasPhysicBoundaries()) {
        
        CCSize s=_levelHelper->physicBoundariesRect().size;
        
        //创建一个地面体
        b2BodyDef groundBodyDef;
        groundBodyDef.position.Set(0, 0); // bottom-left corner
        
        b2Body* groundBody = _b2World->CreateBody(&groundBodyDef);
        
        // Define the ground box shape.
        b2EdgeShape groundBox;
        
        // bottom
        groundBox.Set(b2Vec2(0,0), b2Vec2(s.width,0));
        groundBody->CreateFixture(&groundBox,0);
        
        // top
        groundBox.Set(b2Vec2(0,s.height), b2Vec2(s.width,s.height));
        groundBody->CreateFixture(&groundBox,0);
        
        // left
        groundBox.Set(b2Vec2(0,s.height), b2Vec2(0,0));
        groundBody->CreateFixture(&groundBox,0);
        
        // right
        groundBox.Set(b2Vec2(s.width,s.height), b2Vec2(s.width,0));
        groundBody->CreateFixture(&groundBox,0);
    }
}

void RollBgView::configDebugBox2dDraw() {
	GLESDebugDraw* _debugDraw = new GLESDebugDraw(PT_RATIO);
	_b2World->SetDebugDraw(_debugDraw);
	uint32 flags = 0;
	flags += b2Draw::e_shapeBit;//形状
//	flags += b2Draw::e_jointBit;//关节
//	flags += b2Draw::e_aabbBit;//AABB块
//	flags += b2Draw::e_pairBit;
//    flags += b2Draw::e_centerOfMassBit;//物体质心
	_debugDraw->SetFlags(flags);
}


