//
//  LabelView.h
//  iLostCity
//
//  Created by user on 13-5-22.
//
//

#ifndef iLostCity_LabelView_h
#define iLostCity_LabelView_h

#include <list>

#include "cocos2d.h"

USING_NS_CC;

class CCLabelTTFStroke;

class LabelView : public CCNodeRGBA {
public:
    LabelView();
    ~LabelView();

    static LabelView *createWithFontStyle(const char *string, const char * styleId,
                                    const CCSize& dimensions = CCSizeZero,
                                    CCTextAlignment hAlignment = kCCTextAlignmentLeft,
                                    CCVerticalTextAlignment vAlignment = kCCVerticalTextAlignmentTop);

    bool initWithString(const char *string, const char *fontName,
                        float fontSize,
                        const CCSize& dimensions,
                        CCTextAlignment hAlignment,
                        CCVerticalTextAlignment vAlignment);

    bool initWithFontType(const char *string, const char *fontName,
                        float fontSize, int type,
                        const CCSize& dimensions,
                        CCTextAlignment hAlignment,
                        CCVerticalTextAlignment vAlignment,
                        const cocos2d::ccColor3B& colStroke = ccc3(0, 0, 0));
private:
    static LabelView *create(const char *string, const char *fontName,
                             float fontSize = -1,
                             const CCSize& dimensions = CCSizeZero,
                             CCTextAlignment hAlignment = kCCTextAlignmentLeft,
                             CCVerticalTextAlignment vAlignment = kCCVerticalTextAlignmentTop);
    
private:
    CCRenderTexture *createStroke(CCLabelTTF *labelTTF, const int size, ccColor3B sideColor);
    
public:
    void setFontStyleWithId(const char *styleId);
    
    void setString(const char *label);
    const char* getString(void);

    void setColor(const ccColor3B& color3);
    const ccColor3B &getColor();

    CCTextAlignment getHorizontalAlignment();
    void setHorizontalAlignment(CCTextAlignment alignment);

    CCVerticalTextAlignment getVerticalAlignment();
    void setVerticalAlignment(CCVerticalTextAlignment verticalAlignment);

    CCSize getDimensions();
    void setDimensions(const CCSize &dim);

    float getFontSize();
    void setFontSize(float fontSize);

    const char* getFontName();
    void setFontName(const char *fontName);
    
private:
    CCLabelTTF *_labelTTF;      //type = 1
    CCLabelBMFont *_labelBMFont;   //type = 2
    CCLabelTTFStroke *_labelTTFStroke; //type = 3;
};

LabelView* createLabelInParentCenter(CCNode * parent,
                              const char *string,
                              const char * styleId,
                              bool removeAllChildren = false);

LabelView* createLabelInParentLeftCenter(CCNode * parent,
                                  const char *string,
                                  const char * styleId,
                                  bool removeAllChildren = false);

LabelView* createLabelTTFItem(CCNode * parent,
                              const char *string,
                              const char * styleId,
                              const bool resetAll = false);

#endif
