//
//  CCRGBSprite
//  iLostCity
//
//  Created by xUanBing on 13-10-24.
//
//

#include "CCRGBSprite.h"
#include "GameUtils.h"

CCRGBSprite* CCRGBSprite::createWithTexture(CCTexture2D *pTexture)
{
    CCRGBSprite *pobSprite = new CCRGBSprite();
    if (pobSprite && pobSprite->initWithTexture(pTexture))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

CCRGBSprite* CCRGBSprite::createWithTexture(CCTexture2D *pTexture, const CCRect& rect)
{
    CCRGBSprite *pobSprite = new CCRGBSprite();
    if (pobSprite && pobSprite->initWithTexture(pTexture, rect))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

CCRGBSprite* CCRGBSprite::create(const char *pszFileName)
{
    CCRGBSprite *pobSprite = new CCRGBSprite();
    if (pobSprite && pobSprite->initWithFile(pszFileName))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

CCRGBSprite* CCRGBSprite::create(const char *pszFileName, const CCRect& rect)
{
    CCRGBSprite *pobSprite = new CCRGBSprite();
    if (pobSprite && pobSprite->initWithFile(pszFileName, rect))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

CCRGBSprite* CCRGBSprite::createWithSpriteFrame(CCSpriteFrame *pSpriteFrame)
{
    CCRGBSprite *pobSprite = new CCRGBSprite();
    if (pSpriteFrame && pobSprite && pobSprite->initWithSpriteFrame(pSpriteFrame))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

CCRGBSprite* CCRGBSprite::createWithSpriteFrameName(const char *pszSpriteFrameName)
{
    CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pszSpriteFrameName);
    
#if COCOS2D_DEBUG > 0
    char msg[256] = {0};
    sprintf(msg, "Invalid spriteFrameName: %s", pszSpriteFrameName);
    CCAssert(pFrame != NULL, msg);
#endif
    
    return createWithSpriteFrame(pFrame);
}

CCRGBSprite* CCRGBSprite::create()
{
    CCRGBSprite *pSprite = new CCRGBSprite();
    if (pSprite && pSprite->init())
    {
        pSprite->autorelease();
        return pSprite;
    }
    CC_SAFE_DELETE(pSprite);
    return NULL;
}

//void CCRGBSprite::draw(){
//	ccGLEnableVertexAttribs(kCCVertexAttribFlag_PosColorTex );
//	ccGLBlendFunc( m_sBlendFunc.src, m_sBlendFunc.dst );
//    
//    if (this->getShaderProgram()) {
//        this->getShaderProgram()->use();
//        this->getShaderProgram()->setUniformsForBuiltins();
//    }
//    
//    ccGLBindTexture2D( this->getTexture()->getName() );
//    
//#define kQuadSize sizeof(m_sQuad.bl)
//	long offset = (long)&m_sQuad;
//    
//	// vertex
//	int diff = offsetof( ccV3F_C4B_T2F, vertices);
//	glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, kQuadSize, (void*) (offset + diff));
//    
//	// texCoods
//	diff = offsetof( ccV3F_C4B_T2F, texCoords);
//	glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, kQuadSize, (void*)(offset + diff));
//    
//	// color
//	diff = offsetof( ccV3F_C4B_T2F, colors);
//	glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (void*)(offset + diff));
//	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
//	CC_INCREMENT_GL_DRAWS(1);
//}

void CCRGBSprite::setColor(const ccColor3B& color3) {
    CCSprite::setColor(color3);
    
//    ccColor4F c4 = ccc4FFromccc3B(color3);
//    CCGLProgram *p = ShaderManager::sharedInstance()->getColorShaderProgramOrCompile(c4);
//    setShaderProgram(p);
}



