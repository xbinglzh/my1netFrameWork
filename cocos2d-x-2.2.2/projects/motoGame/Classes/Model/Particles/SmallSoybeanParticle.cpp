//
//  SmallSoybeanParticle.cpp
//  motoGame
//
//  Created by xUanBing on 14-4-15.
//
//

#include "SmallSoybeanParticle.h"
#include "cocos2d.h"

USING_NS_CC;

bool SmallSoybeanParticle::initWithTotalParticles(unsigned int numberOfParticles)
{
    if( CCParticleSystemQuad::initWithTotalParticles(numberOfParticles) )
    {
        // duration
        m_fDuration = 0.3f;
        
        m_bIsAutoRemoveOnFinish = true;
        
        // Gravity Mode
        this->m_nEmitterMode = kCCParticleModeGravity;
        
        // Gravity Mode: gravity
        this->modeA.gravity = ccp(-7, 0.7);
        
        // Gravity Mode: radial acceleration
        this->modeA.radialAccel = -40;
        this->modeA.radialAccelVar = 0;
        
        this->modeA.tangentialAccel = 0;
        this->modeA.tangentialAccelVar = 0;
        
        // Gravity Mode: speed of particles
        this->modeA.speed = 60;
        this->modeA.speedVar = 10;
        
        // starting angle
        m_fAngle = 0;
        m_fAngleVar = 360;
        m_ePositionType = kCCPositionTypeFree;
        
        // emitter position
        //        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        this->setPosition(ccp(156,217));
        this->m_tPosVar = ccp(0, 0);
        
        // life of particles
        m_fLife = 0.4f;
        m_fLifeVar = 0.3f;
        
        
        // size, in pixels
        m_fStartSize = 37.0f;
        m_fStartSizeVar = 10.0f;
        m_fEndSize = 5;
        m_fEndSizeVar = 0;
        
        // emits per frame
        m_fEmissionRate = m_uTotalParticles/m_fLife;
        //        self.emissionRate = 30;
        
        // color of particles
        
        m_tStartColor.r = 0.5f;
		m_tStartColor.g = 0.44f;
		m_tStartColor.b = 0.12f;
		m_tStartColor.a = 1.0f;
        
		m_tStartColorVar.r = 0.4f;
		m_tStartColorVar.g = 0.4f;
		m_tStartColorVar.b = 0.4f;
		m_tStartColorVar.a = 1.0f;
		
		m_tEndColor.r = 0.5f;
		m_tEndColor.g = 0.5f;
		m_tEndColor.b = 0.5f;
		m_tEndColor.a = 1.0f;
		
		m_tEndColorVar.r = 0.4f;
		m_tEndColorVar.g = 0.4f;
		m_tEndColorVar.b = 0.4f;
		m_tEndColorVar.a = 1.0f;
        
        // additive
        this->setBlendAdditive(true);
        
        this->setTexture(CCTextureCache::sharedTextureCache()->addImage("fire.png"));
        //        ccBlendFunc blendFunc;
        //        this->setBlendFunc(ccBlendFunc::create())
        //        self.blendFunc = (ccBlendFunc){GL_SRC_ALPHA, GL_ONE};
        
        return true;
    }
    return false;
}
