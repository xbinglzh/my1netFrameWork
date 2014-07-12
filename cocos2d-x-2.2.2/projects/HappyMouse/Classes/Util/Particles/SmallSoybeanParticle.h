//
//  SmallSoybeanParticle.h
//  motoGame
//
//  Created by xUanBing on 14-4-15.
//
//

#ifndef __motoGame__SmallSoybeanParticle__
#define __motoGame__SmallSoybeanParticle__

#include "cocos2d.h"
#include "CCParticleSystemQuad.h"

USING_NS_CC;

class SmallSoybeanParticle : public CCParticleSystemQuad {
    
public:
    SmallSoybeanParticle(){}
    virtual ~SmallSoybeanParticle(){}
    
    bool init(){ return initWithTotalParticles(60); }
    virtual bool initWithTotalParticles(unsigned int numberOfParticles);
    
    static SmallSoybeanParticle * node() {
        return create();
    }
    
    static SmallSoybeanParticle * create() {
        SmallSoybeanParticle *pRet = new SmallSoybeanParticle();
        if (pRet->init())
        {
            pRet->autorelease();
            return pRet;
        }
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
    
};


#endif /* defined(__motoGame__SmallSoybeanParticle__) */
