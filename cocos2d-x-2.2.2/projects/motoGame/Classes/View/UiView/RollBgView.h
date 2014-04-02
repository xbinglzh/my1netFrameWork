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

class RollBgView : public CCLayer {
public:
    RollBgView();
    ~RollBgView();
    
	virtual bool init();
    void initLhWorld();
    void configDebugBox2dDraw();
    
	virtual void update(float t);
    void updateB2World(float dt);
    
	CREATE_FUNC(RollBgView);
    
    void loadPhysicWorldWithLayer(const char* levelFile, CCLayer *layer);
private:
    b2World *_b2World;
    LevelHelperLoader *_levelHelper;
    LHSprite *_lhSprite;
};

#endif /* defined(__motoGame__RollBgView__) */
