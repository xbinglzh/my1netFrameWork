//
//  ParticleEffect.h
//  motoGame
//
//  Created by xUanBing on 14-4-15.
//
//

#ifndef __motoGame__ParticleEffect__
#define __motoGame__ParticleEffect__

#include "cocos2d.h"
#include "CCParticleSystemQuad.h"

USING_NS_CC;

class BaseEffect;

class EffectAutoRemoveOnFinishDelegate {
    
public:
	virtual void handleEffectAutoRemoveOnFinish(BaseEffect * effect) = 0;
    
};

class BaseEffect{
    
public:
	BaseEffect(){_effectDelegate = NULL;_effectCallAction = NULL;}
	virtual ~BaseEffect(){CC_SAFE_RELEASE_NULL(_effectCallAction);}
    
	CC_SYNTHESIZE(EffectAutoRemoveOnFinishDelegate *, _effectDelegate, EffectDelegate);
	CC_SYNTHESIZE_RETAIN(CCString *, _effectCallAction, EffectCallAction);
    
public:
	virtual void handleEffectAutoRemoveOnFinish();
    
};

class ParticleEffect : public CCParticleSystemQuad, public BaseEffect {
    
public:
    ParticleEffect():CCParticleSystemQuad(),BaseEffect(){}
    virtual ~ParticleEffect(){}
	virtual void update(float dt);
	static ParticleEffect * create(const char *plistFile);
    
};



#endif /* defined(__motoGame__ParticleEffect__) */
