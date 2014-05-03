//
//  CCLabelTTFStroke.h
//  iLostCity
//
//  Created by user on 13-6-3.
//
//

#ifndef __iLostCity__CCLabelTTFStroke__
#define __iLostCity__CCLabelTTFStroke__

#include "cocos2d.h"

USING_NS_CC;

class CCLabelTTFStroke : public CCNode {
public:
    CCLabelTTFStroke();
    ~CCLabelTTFStroke();
    
public:
    static CCLabelTTFStroke* create(const char *string, const char *fontName, float fontSize, float strokeSize,
                                    const CCSize &dimensions = CCSizeZero,
                                    const cocos2d::ccColor3B& colStroke = ccc3(0, 0, 0),
                                    CCTextAlignment hAlignment = kCCTextAlignmentCenter,
                                    CCVerticalTextAlignment vAlignment = kCCVerticalTextAlignmentTop);
    
    bool initWithString(const char *label, const char *fontName, float fontSize, float fStrokeSize,
                        const CCSize &dimensions,
                        const cocos2d::ccColor3B& colStroke,
                        cocos2d::CCTextAlignment hAlignment, cocos2d::CCVerticalTextAlignment vAlignment);
    
public:
    void setColor(const cocos2d::ccColor3B& color3);
    const ccColor3B &getColor();
    
    void setString(const char *label);
    const char* getString(void) { return m_label->getString(); }
    
    const char* getFontName() { return m_label->getFontName(); }
    
    void setStrokeColor(cocos2d::ccColor3B col) { m_colStroke = col; updateStroke(); }
    void setStrokeSize(float StrokeSize){ m_fStrokeSize = StrokeSize; updateStroke();}
    
    CCSize getDimensions();
    void setDimensions(const CCSize &dim);
    
protected:
    void updateStroke();
    
private:
    float                   m_fStrokeSize;
    cocos2d::ccColor3B      m_colStroke;
    cocos2d::CCSprite*      m_sprite;
    cocos2d::CCLabelTTF*    m_label;
};

#endif /* defined(__iLostCity__CCLabelTTFStroke__) */
