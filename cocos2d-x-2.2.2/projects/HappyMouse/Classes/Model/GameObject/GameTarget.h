//
//  GameTarget.h
//  HappyMouse
//
//  Created by xUanBing on 14-7-26.
//
//

#ifndef __HappyMouse__GameTarget__
#define __HappyMouse__GameTarget__

#include "cocos2d.h"
#include "GameObject.h"

class  GameTarget : public cocos2d::CCObject{
    
public:
    GameTarget();
	~GameTarget();
    bool init();
	CREATE_FUNC(GameTarget);
    CC_SYNTHESIZE_RETAIN(GameObject *, _role, Role);
    CC_SYNTHESIZE(float, _distance, Distance);
    static int compareDistance(const void * p1,const void * p2);
};

class  TargetsObject : public cocos2d::CCObject{
    
public:
	TargetsObject();
	~TargetsObject();
	bool init();
	CREATE_FUNC(TargetsObject);
	void addTargetsObject(GameTarget * obj);
    void removeGameTarget(GameObject * obj);
	CC_SYNTHESIZE_RETAIN(cocos2d::CCArray *, _targetsObject, TargetsObject);
    
};

#endif /* defined(__HappyMouse__GameTarget__) */
