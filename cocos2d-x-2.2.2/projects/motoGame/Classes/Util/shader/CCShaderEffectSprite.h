//
//  CCShaderEffectSprite.h
//  iLostCity
//
//  Created by xUanBing on 13-10-24.
//
//

#ifndef __iLostCity__ShaderEffectSprite__
#define __iLostCity__ShaderEffectSprite__

#include "ShaderManager.h"
#include "cocos2d.h"
#include <string>

using namespace std;
USING_NS_CC;

class CCShaderEffectSprite : public CCSprite {
    
public:
	CCShaderEffectSprite();
	virtual ~CCShaderEffectSprite();
    
	static CCShaderEffectSprite* create(string shaderType);
	static CCShaderEffectSprite* create(const char* pszFileName,string shaderType);
    
	bool initWithTexture(CCTexture2D* pTexture, const CCRect& tRect);
    
    static CCShaderEffectSprite* createWithSpriteFrame(cocos2d::CCSpriteFrame *pSpriteFrame,string shaderType);
	virtual void draw();
    void changeShader(string shaderType);
    
private:
	void setShader(string shaderType);
    
private:
	static string shaderType;
};

#endif /* defined(__iLostCity__ShaderEffectSprite__) */
