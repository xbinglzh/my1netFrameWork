//
//  CCLabelTTFStroke.cpp
//  iLostCity
//
//  Created by user on 13-6-3.
//
//

#include "CCLabelTTFStroke.h"

CCLabelTTFStroke::CCLabelTTFStroke()
:m_colStroke(ccc3(0,0,0))
,m_fStrokeSize(1.0f)
,m_sprite(NULL)
,m_label(NULL) {
    
}

CCLabelTTFStroke::~CCLabelTTFStroke() {
    CC_SAFE_RELEASE_NULL(m_label);
}

bool CCLabelTTFStroke::initWithString(const char *string, const char *fontName, float fontSize, float strokeSize,
                                      const CCSize &dimensions,
                                      const cocos2d::ccColor3B& colStroke,
                                      CCTextAlignment hAlignment,CCVerticalTextAlignment vAlignment) {
    m_fStrokeSize = strokeSize;
    m_colStroke = colStroke;
    m_label = CCLabelTTF::create(string, fontName, fontSize, dimensions, hAlignment,vAlignment);
    m_label->retain();
    
    updateStroke();
    
    return true;
}

CCLabelTTFStroke* CCLabelTTFStroke::create(const char *string, const char *fontName, float fontSize, float fStrokeSize,
                                           const CCSize &dimensions,
                                           const cocos2d::ccColor3B& colStroke,
                                           CCTextAlignment hAlignment,CCVerticalTextAlignment vAlignment) {
    CCLabelTTFStroke *pRet = new CCLabelTTFStroke();
    if(pRet && pRet->initWithString(string, fontName, fontSize, fStrokeSize, dimensions, colStroke, hAlignment, vAlignment)) {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

void CCLabelTTFStroke::updateStroke() {
    if (m_sprite) {
        removeChild(m_sprite, true);
    }
    
    CCSize textureSize = m_label->getContentSize();
    textureSize.width += 2 * m_fStrokeSize;
    textureSize.height += 2 * m_fStrokeSize;
        //call to clear error
    glGetError();
    CCRenderTexture *rt = CCRenderTexture::create(textureSize.width, textureSize.height);
    if(!rt) {
        CCLOG("create render texture failed !!!!");
        addChild(m_label);
        return;
    }
    
    setContentSize(rt->getContentSize());
    
    ccColor3B col = m_label->getColor();
    m_label->setColor(m_colStroke);
    
    ccBlendFunc originalBlend = m_label->getBlendFunc();
    ccBlendFunc func = { GL_SRC_ALPHA, GL_ONE};
    m_label->setBlendFunc(func);
    
    m_label->setAnchorPoint(ccp(0.5, 0.5));
    
    rt->begin();
    for(int i = 0; i < 360; i += 15) {
        float r = CC_DEGREES_TO_RADIANS(i);
        m_label->setPosition(ccp(textureSize.width/2 + sin(r) * m_fStrokeSize,
                                 textureSize.height/2 + cos(r) * m_fStrokeSize));
        m_label->visit();
    }
    
    m_label->setColor(col);
    m_label->setBlendFunc(originalBlend);
    m_label->setPosition(ccp(textureSize.width/2, textureSize.height/2));
    m_label->visit();
    rt->end();
    
    CCTexture2D *texture = rt->getSprite()->getTexture();
    texture->setAliasTexParameters();
    m_sprite = CCSprite::createWithTexture(rt->getSprite()->getTexture());
    setContentSize(m_sprite->getContentSize());
    m_sprite->setAnchorPoint(ccp(0, 0));
    m_sprite->setPosition(ccp(0, 0));
    ((CCSprite *)m_sprite)->setFlipY(true);
    
    addChild(m_sprite);
}

void CCLabelTTFStroke::setString(const char *label) {
    if (m_label) {
        if(0 != strcmp(label, m_label->getString())) {
            m_label->setString(label);
            updateStroke();
        }
    } else {
        CCLOG("ERROR:CCLabelTTFStroke::setString m_label=NULL");
    }
}

void CCLabelTTFStroke::setColor(const ccColor3B& color3) {
    if (m_label) {
        ccColor3B col = m_label->getColor();
        if(!ccc3BEqual(color3, col)) {
            m_label->setColor(color3);
            updateStroke();
        }
    } else {
        CCLOG("ERROR:CCLabelTTFStroke::setColor m_label=NULL");
    }
}

const ccColor3B &CCLabelTTFStroke::getColor() {
    if (m_label) {
        return m_label->getColor();
    } else {
        CCLOG("ERROR:CCLabelTTFStroke::setColor m_label=NULL");
    }
    return ccWHITE;
}

CCSize CCLabelTTFStroke::getDimensions() {
    if (m_label) {
        return m_label->getDimensions();
    } else {
        CCLOG("ERROR:CCLabelTTFStroke::setColor m_label=NULL");
    }
    return CCSizeZero;
}
void CCLabelTTFStroke::setDimensions(const CCSize &dim) {
    if (m_label) {
        m_label->setDimensions(dim);
        updateStroke();
    } else {
        CCLOG("ERROR:CCLabelTTFStroke::setColor m_label=NULL");
    }
}