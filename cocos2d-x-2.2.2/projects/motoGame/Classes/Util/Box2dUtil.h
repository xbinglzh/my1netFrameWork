//
//  Box2dUtil.h
//  motoGame
//
//  Created by xUanBing on 14-4-5.
//
//

#ifndef __motoGame__Box2dUtil__
#define __motoGame__Box2dUtil__

#include "cocos2d.h"
#include "Box2D.h"

USING_NS_CC;

class LevelHelperLoader;

class Box2dUtil {
    
public:
    
    static void addBodyForSprite(b2World *b2World, LevelHelperLoader *levelHelp, cocos2d::CCSprite* sprite, b2FixtureDef fixtureDef, b2BodyDef bodyDef);
    
    static void addBodyForSprite(b2World *b2World, LevelHelperLoader *levelHelp, cocos2d::CCSprite* sprite, b2FixtureDef fixtureDef);
    
    static void addBoxBodyForSprite(b2World *b2World, LevelHelperLoader *levelHelp, cocos2d::CCSprite* sprite, b2FixtureDef fixtureDef);
    
    static void createPhysicBoundaries(b2World *b2World, CCSize size);
    static void openDebugBox2dDraw(b2World *b2World);
    
    static void updateBox2dWorldInLevelHelp(b2World *b2World, LevelHelperLoader *levelHelp, float dt);
    
};

#endif /* defined(__motoGame__Box2dUtil__) */
