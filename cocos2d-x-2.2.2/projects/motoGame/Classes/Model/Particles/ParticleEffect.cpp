//
//  ParticleEffect.cpp
//  motoGame
//
//  Created by xUanBing on 14-4-15.
//
//

#include "ParticleEffect.h"
#include "ParticleEffect.h"

void BaseEffect::handleEffectAutoRemoveOnFinish()
{
	if(_effectDelegate){
		_effectDelegate->handleEffectAutoRemoveOnFinish(this);
	}
}

ParticleEffect * ParticleEffect::create(const char *plistFile)
{
	ParticleEffect *pRet = new ParticleEffect();
	if (pRet && pRet->initWithFile(plistFile))
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return pRet;
}

// ParticleSystem - MainLoop
void ParticleEffect::update(float dt)
{
    CC_PROFILER_START_CATEGORY(kCCProfilerCategoryParticles , "CCParticleSystem - update");
	
    if (m_bIsActive && m_fEmissionRate)
    {
        float rate = 1.0f / m_fEmissionRate;
        //issue #1201, prevent bursts of particles, due to too high emitCounter
        if (m_uParticleCount < m_uTotalParticles)
        {
            m_fEmitCounter += dt;
        }
        
        while (m_uParticleCount < m_uTotalParticles && m_fEmitCounter > rate)
        {
            this->addParticle();
            m_fEmitCounter -= rate;
        }
		
        m_fElapsed += dt;
        if (m_fDuration != -1 && m_fDuration < m_fElapsed)
        {
            this->stopSystem();
        }
    }
	
    m_uParticleIdx = 0;
	
    CCPoint currentPosition = CCPointZero;
    if (m_ePositionType == kCCPositionTypeFree)
    {
        currentPosition = this->convertToWorldSpace(CCPointZero);
    }
    else if (m_ePositionType == kCCPositionTypeRelative)
    {
        currentPosition = getPosition();
    }
	
    if (isVisible())
    {
        while (m_uParticleIdx < m_uParticleCount)
        {
            tCCParticle *p = &m_pParticles[m_uParticleIdx];
			
            // life
            p->timeToLive -= dt;
			
            if (p->timeToLive > 0)
            {
                // Mode A: gravity, direction, tangential accel & radial accel
                if (m_nEmitterMode == kCCParticleModeGravity)
                {
                    CCPoint tmp, radial, tangential;
					
                    radial = CCPointZero;
                    // radial acceleration
                    if (p->pos.x || p->pos.y)
                    {
                        radial = ccpNormalize(p->pos);
                    }
                    tangential = radial;
                    radial = ccpMult(radial, p->modeA.radialAccel);
					
                    // tangential acceleration
                    float newy = tangential.x;
                    tangential.x = -tangential.y;
                    tangential.y = newy;
                    tangential = ccpMult(tangential, p->modeA.tangentialAccel);
					
                    // (gravity + radial + tangential) * dt
                    tmp = ccpAdd( ccpAdd( radial, tangential), modeA.gravity);
                    tmp = ccpMult( tmp, dt);
                    p->modeA.dir = ccpAdd( p->modeA.dir, tmp);
                    tmp = ccpMult(p->modeA.dir, dt);
                    p->pos = ccpAdd( p->pos, tmp );
                }
				
                // Mode B: radius movement
                else
                {
                    // Update the angle and radius of the particle.
                    p->modeB.angle += p->modeB.degreesPerSecond * dt;
                    p->modeB.radius += p->modeB.deltaRadius * dt;
					
                    p->pos.x = - cosf(p->modeB.angle) * p->modeB.radius;
                    p->pos.y = - sinf(p->modeB.angle) * p->modeB.radius;
                }
				
                // color
                p->color.r += (p->deltaColor.r * dt);
                p->color.g += (p->deltaColor.g * dt);
                p->color.b += (p->deltaColor.b * dt);
                p->color.a += (p->deltaColor.a * dt);
				
                // size
                p->size += (p->deltaSize * dt);
                p->size = MAX( 0, p->size );
				
                // angle
                p->rotation += (p->deltaRotation * dt);
				
                //
                // update values in quad
                //
				
                CCPoint    newPos;
				
                if (m_ePositionType == kCCPositionTypeFree || m_ePositionType == kCCPositionTypeRelative)
                {
                    CCPoint diff = ccpSub( currentPosition, p->startPos );
                    newPos = ccpSub(p->pos, diff);
                }
                else
                {
                    newPos = p->pos;
                }
				
                // translate newPos to correct position, since matrix transform isn't performed in batchnode
                // don't update the particle with the new position information, it will interfere with the radius and tangential calculations
                if (m_pBatchNode)
                {
                    newPos.x += getPosition().x;
                    newPos.y += getPosition().y;
                }
				
                updateQuadWithParticle(p, newPos);
                //updateParticleImp(self, updateParticleSel, p, newPos);
				
                // update particle counter
                ++m_uParticleIdx;
            }
            else
            {
                // life < 0
                int currentIndex = p->atlasIndex;
                if( m_uParticleIdx != m_uParticleCount-1 )
                {
                    m_pParticles[m_uParticleIdx] = m_pParticles[m_uParticleCount-1];
                }
                if (m_pBatchNode)
                {
                    //disable the switched particle
                    m_pBatchNode->disableParticle(m_uAtlasIndex+currentIndex);
					
                    //switch indexes
                    m_pParticles[m_uParticleCount-1].atlasIndex = currentIndex;
                }
				
				
                --m_uParticleCount;
				
                if( m_uParticleCount == 0 && m_bIsAutoRemoveOnFinish )
                {
                    this->unscheduleUpdate();
					this->handleEffectAutoRemoveOnFinish();
                    removeFromParentAndCleanup(true);
                    return;
                }
            }
        } //while
        m_bTransformSystemDirty = false;
    }
    if (! m_pBatchNode)
    {
        postStep();
    }
	
    CC_PROFILER_STOP_CATEGORY(kCCProfilerCategoryParticles , "CCParticleSystem - update");
}