//
//  Box2dUtil.cpp
//  motoGame
//
//  Created by xUanBing on 14-4-5.
//
//

#include "Box2dUtil.h"
#include "ConstansDef.h"
#include "GLES-Render.h"
#include "LevelHelperLoader.h"

void Box2dUtil::addBodyForSprite(b2World *b2World, LevelHelperLoader *levelHelp, cocos2d::CCSprite *sprite, b2FixtureDef fixtureDef, b2BodyDef bodyDef) {
    
    b2Body* spriteBody = b2World->CreateBody(&bodyDef);
    spriteBody->CreateFixture(&fixtureDef);
    
}

void Box2dUtil::addBodyForSprite(b2World *b2World, LevelHelperLoader *levelHelp,cocos2d::CCSprite *sprite, b2FixtureDef fixtureDef) {
    
    b2BodyDef bd;
    bd.type = b2_staticBody;
    bd.linearVelocity = b2Vec2(5, 10);
    bd.position = levelHelp->pointsToMeters(sprite->getPosition());
    
    bd.userData = sprite;
    
    addBodyForSprite(b2World, levelHelp, sprite, fixtureDef, bd);
}

void Box2dUtil::addBoxBodyForSprite(b2World *b2World,  LevelHelperLoader *levelHelp, cocos2d::CCSprite *sprite, b2FixtureDef fixtureDef) {
    b2PolygonShape polygon;
    
    b2Vec2 vec2 = levelHelp->pixelToMeters(ccp(sprite->getContentSize().width, sprite->getContentSize().height));
    polygon.SetAsBox(vec2.x, vec2.y);
    
    fixtureDef.shape = &polygon;
    
    addBodyForSprite(b2World, levelHelp, sprite, fixtureDef);
}

void Box2dUtil::createPhysicBoundaries(b2World *b2World, cocos2d::CCSize size) {
    
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0, 0); // bottom-left corner
    
    b2Body* groundBody = b2World->CreateBody(&groundBodyDef);
    
    b2EdgeShape groundBox;
    
    // bottom
    groundBox.Set(b2Vec2(0,0), b2Vec2(size.width,0));
    groundBody->CreateFixture(&groundBox,0);
    
    // top
    groundBox.Set(b2Vec2(0,size.height), b2Vec2(size.width, size.height));
    groundBody->CreateFixture(&groundBox,0);
    
    // left
    groundBox.Set(b2Vec2(0, size.height), b2Vec2(0,0));
    groundBody->CreateFixture(&groundBox,0);
    
    // right
    groundBox.Set(b2Vec2(size.width, size.height), b2Vec2(size.width,0));
    groundBody->CreateFixture(&groundBox,0);
}

void Box2dUtil::openDebugBox2dDraw(b2World *b2World) {
    GLESDebugDraw* _debugDraw = new GLESDebugDraw(PTM_RATIO);
	b2World->SetDebugDraw(_debugDraw);
    
	uint32 flags = 0;
	flags += b2Draw::e_shapeBit;//形状
    flags += b2Draw::e_jointBit;//关节
    //	flags += b2Draw::e_aabbBit;//AABB块
    //	flags += b2Draw::e_pairBit;
    //    flags += b2Draw::e_centerOfMassBit;//物体质心
	_debugDraw->SetFlags(flags);
}

void Box2dUtil::updateBox2dWorldInLevelHelp(b2World *b2World, LevelHelperLoader *levelHelp, float dt) {
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
        
        b2World->Step(UPDATE_INTERVAL, velocityIterations, positionIterations);
        
        for (b2Body* body = b2World->GetBodyList(); body; body = body->GetNext()) {
            if (body->GetUserData() != NULL) {
                CCSprite* sprite = (CCSprite*) body->GetUserData();
                sprite->setPosition(levelHelp->metersToPoints(body->GetPosition()));
                sprite->setRotation( -1 * CC_RADIANS_TO_DEGREES(body->GetAngle()));
            }
        }

    }

}

void Box2dUtil::destoryBody(b2World *b2World) {
    std::list<b2Body*>::iterator it = _toDestroyBodyList.begin();
    while(it != _toDestroyBodyList.end()) {
        b2World->DestroyBody(*it);
        it++;
    }
}

void Box2dUtil::appendDestoryBody(b2Body *body) {
    _toDestroyBodyList.push_back(body);
}
