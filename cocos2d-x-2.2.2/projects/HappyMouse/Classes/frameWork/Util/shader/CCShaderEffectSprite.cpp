//
//  CCShaderEffectSprite.cpp
//  iLostCity
//
//  Created by xUanBing on 13-10-24.
//
//

#include "CCShaderEffectSprite.h"
#include <sstream>

string CCShaderEffectSprite::shaderType="";

CCShaderEffectSprite::CCShaderEffectSprite(){
    
}

CCShaderEffectSprite::~CCShaderEffectSprite(){
    
}

CCShaderEffectSprite* CCShaderEffectSprite::create(string shader){
	shaderType=shader;
	CCShaderEffectSprite* graySprite = new CCShaderEffectSprite;
	if (graySprite && graySprite->init()){
        graySprite->setShader(shaderType);
		graySprite->autorelease();
		return graySprite;
	}else{
		CC_SAFE_RELEASE(graySprite);
		return NULL;
	}
}

CCShaderEffectSprite* CCShaderEffectSprite::create( const char* pszFileName,string shader){
	shaderType=shader;
	CCShaderEffectSprite* graySprite = new CCShaderEffectSprite;
	if (graySprite && graySprite->initWithFile(pszFileName)){
        graySprite->setShader(shaderType);
		graySprite->autorelease();
		return graySprite;
	}else{
		CC_SAFE_RELEASE(graySprite);
		return NULL;
	}
}

CCShaderEffectSprite* CCShaderEffectSprite::createWithSpriteFrame(CCSpriteFrame *pSpriteFrame,string shader){
    shaderType=shader;
	CCShaderEffectSprite* graySprite = new CCShaderEffectSprite;
	if (graySprite && graySprite->initWithSpriteFrame(pSpriteFrame)){
        graySprite->setShader(shaderType);
		graySprite->autorelease();
		return graySprite;
	}else{
		CC_SAFE_RELEASE(graySprite);
		return NULL;
	}
}


bool CCShaderEffectSprite::initWithTexture(CCTexture2D* pTexture, const CCRect& tRect ){
    
	do{
		CC_BREAK_IF(!CCSprite::initWithTexture(pTexture, tRect));
		return true;
	} while (0);
    
	return false;
}

void CCShaderEffectSprite::changeShader(string shaderType){
	this->shaderType=shaderType;
	setShader(shaderType);
}

void CCShaderEffectSprite::setShader(string shaderType){
	CCGLProgram* pProgram = ShaderManager::sharedInstance()->getShaderProgram(shaderType);
	this->setShaderProgram(pProgram);
}

void CCShaderEffectSprite::draw(){
	ccGLEnableVertexAttribs(kCCVertexAttribFlag_PosColorTex );
	ccGLBlendFunc( m_sBlendFunc.src, m_sBlendFunc.dst );
    
    if (this->getShaderProgram()) {
        this->getShaderProgram()->use();
        this->getShaderProgram()->setUniformsForBuiltins();
    }
    
    ccGLBindTexture2D( this->getTexture()->getName() );
    
#define kQuadSize sizeof(m_sQuad.bl)
	long offset = (long)&m_sQuad;
    
	// vertex
	int diff = offsetof( ccV3F_C4B_T2F, vertices);
	glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, kQuadSize, (void*) (offset + diff));
    
	// texCoods
	diff = offsetof( ccV3F_C4B_T2F, texCoords);
	glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, kQuadSize, (void*)(offset + diff));
    
	// color
	diff = offsetof( ccV3F_C4B_T2F, colors);
	glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (void*)(offset + diff));
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	CC_INCREMENT_GL_DRAWS(1);
}




