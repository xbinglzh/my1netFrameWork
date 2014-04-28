//
//  HeroSprite.h
//  motoGame
//
//  Created by xUanBing on 14-4-28.
//
//

#ifndef __motoGame__HeroSprite__
#define __motoGame__HeroSprite__

#include "cocos2d.h"
#include "LHSprite.h"
#include "Box2D.h"
#include "AnimNode.h"

USING_NS_CC;

class HeroSprite : public CCSprite {
    
public:
    enum HeroState {
        HERO_NULL,
        HERO_RUN,
        HERO_JUMP,
        
        HERO_BROKE_JUMP,
        HERO_BROKE_RUN,
        HERO_BROKE_RUN_JUMP
    };
    
public:
    HeroSprite();
    ~HeroSprite();
    virtual bool init();
    static HeroSprite* create();
    
    void changeHeroState(HeroState state);
    
private:
    HeroState   _curHeroState;
    AnimNode*   _animNode;
    
    
    
};

#endif /* defined(__motoGame__HeroSprite__) */
