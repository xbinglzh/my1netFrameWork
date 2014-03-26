//
//  CCRGBSprite
//  iLostCity
//
//  Created by xUanBing on 13-10-24.
//
//

#ifndef __iLostCity__CCRGBSprite__
#define __iLostCity__CCRGBSprite__

#include "cocos2d.h"
#include "ShaderManager.h"

using namespace std;
USING_NS_CC;

class CCRGBSprite : public CCSprite {
    
public:
    static CCRGBSprite* create();
    static CCRGBSprite* create(const char *pszFileName);
    static CCRGBSprite* create(const char *pszFileName, const CCRect& rect);
    static CCRGBSprite* createWithTexture(CCTexture2D *pTexture);
    static CCRGBSprite* createWithTexture(CCTexture2D *pTexture, const CCRect& rect);
    static CCRGBSprite* createWithSpriteFrame(CCSpriteFrame *pSpriteFrame);
    static CCRGBSprite* createWithSpriteFrameName(const char *pszSpriteFrameName);
    
public:
//	virtual void draw();
    void setColor(const ccColor3B& color3);
};

#endif /* defined(__iLostCity__CCRGBSprite__) */
