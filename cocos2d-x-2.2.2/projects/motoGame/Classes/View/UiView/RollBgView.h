//
//  RollBgView.h
//  motoGame
//
//  Created by xUanBing on 14-3-30.
//
//

#ifndef __motoGame__RollBgView__
#define __motoGame__RollBgView__

#include "cocos2d.h"

USING_NS_CC;

class b2World;
class LevelHelperLoader;
class LHSprite;
class LHContactInfo;

class RollBgView : public CCLayer {
public:
    RollBgView();
    ~RollBgView();
    
	virtual bool init();
    void initLhWorld();
    
	virtual void update(float t);
    void updateB2World(float dt);
    
    virtual void draw();
    
	CREATE_FUNC(RollBgView);
    
    void loadPhysicWorldWithLayer(const char* levelFile, CCLayer *layer);
    
private: /*碰撞处理*/
    void preCollisionBetweenHeroTreeAndCoin(LHContactInfo* contact);
    
private:
    b2World *_b2World;
    LevelHelperLoader *_levelHelper;
    LHSprite *_lhSprite;
};

#endif /* defined(__motoGame__RollBgView__) */
