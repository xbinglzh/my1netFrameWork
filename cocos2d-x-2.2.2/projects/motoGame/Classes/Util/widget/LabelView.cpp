//
//  LabelView.cpp
//  iLostCity
//
//  Created by user on 13-5-22.
//
//

#include "LabelView.h"

#include "UiUtils.h"
#include "GameConfig.h"
#include "FontStyle.h"
#include "ConstansDef.h"
#include "CCLabelTTFStroke.h"

LabelView::LabelView()
: _labelBMFont(NULL)
, _labelTTF(NULL)
, _labelTTFStroke(NULL) {
    
}

LabelView::~LabelView() {
    
}

LabelView* LabelView::create(const char *string, const char *fontName, float fontSize,
                             const CCSize& dimensions, CCTextAlignment hAlignment,
                             CCVerticalTextAlignment vAlignment) {
    LabelView *pRet = new LabelView();
    if(pRet && pRet->initWithString(string, fontName, fontSize, dimensions, hAlignment, vAlignment)) {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

LabelView *LabelView::createWithFontStyle(const char *string, const char * styleId,
                                const CCSize& dimensions, CCTextAlignment hAlignment,
                                CCVerticalTextAlignment vAlignment) {
    
    FontStyle style = GameConfig::sharedInstance()->getFontStyleById(styleId);
    
    LabelView *pRet = new LabelView();
    if(pRet && pRet->initWithFontType((string ? string :""), (style._font).c_str(), style._size, style._type, dimensions, hAlignment, vAlignment, style._stroke_color)) {
        if (style._type != K_FONT_LABEL_BM) {
             pRet->setColor(style._color);   
        }
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool LabelView::initWithFontType(const char *string, const char *fontName,
                          float fontSize, int type,
                          const CCSize& dimensions,
                          CCTextAlignment hAlignment, CCVerticalTextAlignment vAlignment,
                         const cocos2d::ccColor3B& colStroke) {
    if (type == K_FONT_LABEL_TTF) {
        _labelTTF = cocos2d::CCLabelTTF::create(string, fontName, fontSize, dimensions, hAlignment, vAlignment);
        _labelTTF->setAnchorPoint(CCPointZero);
        setContentSize(_labelTTF->getContentSize());
        _labelTTF->setPosition(CCPointZero);
        
        addChild(_labelTTF, 0);
        
    } else if (type == K_FONT_LABEL_BM) {
        _labelBMFont = cocos2d::CCLabelBMFont::create(string, fontName, fontSize, hAlignment);
        _labelBMFont->setAnchorPoint(CCPointZero);
        setContentSize(_labelBMFont->getContentSize());
        _labelBMFont->setPosition(CCPointZero);
        
        addChild(_labelBMFont, 0);
        
    } else if (type == K_FONT_LABEL_TTF_STROKE) {
        _labelTTFStroke = CCLabelTTFStroke::create(string, fontName, fontSize, 2, dimensions, colStroke, hAlignment, vAlignment);
        _labelTTFStroke->setAnchorPoint(CCPointZero);
        setContentSize(_labelTTFStroke->getContentSize());
        _labelTTFStroke->setPosition(CCPointZero);
        
        addChild(_labelTTFStroke, 0);
        
    } else {
        _labelTTF = cocos2d::CCLabelTTF::create(string, fontName, fontSize, dimensions, hAlignment, vAlignment);
        _labelTTF->setAnchorPoint(CCPointZero);
        setContentSize(_labelTTF->getContentSize());
        _labelTTF->setPosition(CCPointZero);
        
        addChild(_labelTTF, 0);
    } 
    return true;
}

bool LabelView::initWithString(const char *string, const char *fontName, float fontSize,
                                const CCSize& dimensions, CCTextAlignment hAlignment,
                               CCVerticalTextAlignment vAlignment) {
    int type = 1;
    std::string strCCBFileName(fontName);
    if (UiUtils::endsWith(strCCBFileName.c_str(), ".png")) {
        type = 3;
    } else if(UiUtils::endsWith(strCCBFileName.c_str(), ".fnt")){
        type = 2;
    } else {
        type = 1;
    }
    return initWithFontType(string, fontName, fontSize, type, dimensions, hAlignment, vAlignment);
}

void LabelView::setFontStyleWithId(const char *styleId) {
    FontStyle style = GameConfig::sharedInstance()->getFontStyleById(styleId);
    if (style._type != K_FONT_LABEL_BM) {
        setColor(style._color);
    }
    setFontSize(style._size);
}

void LabelView::setString(const char *label) {
    if (_labelBMFont) {
        _labelBMFont->setString(label);
        setContentSize(_labelBMFont->getContentSize());
    } else if(_labelTTF) {
        _labelTTF->setString(label);
        setContentSize(_labelTTF->getContentSize());
    } else if(_labelTTFStroke) {
        _labelTTFStroke->setString(label);
        setContentSize(_labelTTFStroke->getContentSize());
    }
}

const char* LabelView::getString() {
    if (_labelBMFont) {
        return _labelBMFont->getString();
    } else if(_labelTTF) {
        return _labelTTF->getString();
    } else if(_labelTTFStroke) {
        return _labelTTFStroke->getString();
    }
    return "";
}

void LabelView::setColor(const ccColor3B& color3) {
    if (_labelBMFont) {
        _labelBMFont->setColor(color3);
    } else if(_labelTTF) {
        _labelTTF->setColor(color3);
    } else if(_labelTTFStroke) {
        _labelTTFStroke->setColor(color3);
    }
}
const ccColor3B &LabelView::getColor() {
    if (_labelBMFont) {
        return _labelBMFont->getColor();
    } else if(_labelTTF) {
        return _labelTTF->getColor();
    } else if(_labelTTFStroke) {
        return _labelTTFStroke->getColor();
    }
    return ccWHITE;
}

CCTextAlignment LabelView::getHorizontalAlignment() {
    if (_labelBMFont) {
        return kCCTextAlignmentLeft;
    } else if(_labelTTF) {
        _labelTTF->getHorizontalAlignment();
    }
    return kCCTextAlignmentLeft;
}
void LabelView::setHorizontalAlignment(CCTextAlignment alignment) {
    if (_labelBMFont) {
        _labelBMFont->setAlignment(alignment);
        setContentSize(_labelBMFont->getContentSize());
    } else if(_labelTTF) {
        _labelTTF->setHorizontalAlignment(alignment);
        setContentSize(_labelTTF->getContentSize());
    }
}

CCVerticalTextAlignment LabelView::getVerticalAlignment() {
    if (_labelBMFont) {
        return kCCVerticalTextAlignmentTop;
    } else if(_labelTTF) {
        return _labelTTF->getVerticalAlignment();
    }
    return kCCVerticalTextAlignmentTop;
}
void LabelView::setVerticalAlignment(CCVerticalTextAlignment verticalAlignment) {
    if (_labelBMFont) {
        
    } else if(_labelTTF) {
        _labelTTF->setVerticalAlignment(verticalAlignment);
        setContentSize(_labelTTF->getContentSize());
    }
}

CCSize LabelView::getDimensions() {
    if (_labelBMFont) {
        return CCSizeZero;
    } else if(_labelTTF) {
        _labelTTF->getDimensions();
    }
    return CCSizeZero;
}
void LabelView::setDimensions(const CCSize &dim) {
    if (_labelBMFont) {
        
    } else if(_labelTTF) {
        _labelTTF->setDimensions(dim);
        setContentSize(_labelTTF->getContentSize());
    } else if(_labelTTFStroke) {
        _labelTTFStroke->setDimensions(dim);
    }
}

float LabelView::getFontSize() {
    if (_labelBMFont) {
        return -1;
    } else if(_labelTTF) {
        return _labelTTF->getFontSize();
    }
    return -1;
}
void LabelView::setFontSize(float fontSize) {
    if (_labelBMFont) {
        _labelBMFont->setWidth(fontSize);
        setContentSize(_labelBMFont->getContentSize());
    } else if(_labelTTF) {
        _labelTTF->setFontSize(fontSize);
        setContentSize(_labelTTF->getContentSize());
    }
}

const char* LabelView::getFontName() {
    if (_labelBMFont) {
        return _labelBMFont->getFntFile();
    } else if(_labelTTF) {
        return _labelTTF->getFontName();
    } else if(_labelTTFStroke) {
        return _labelTTFStroke->getFontName();
    }
    return "";
}

void LabelView::setFontName(const char *fontName) {
    if (_labelBMFont) {
        _labelBMFont->setFntFile(fontName);
        setContentSize(_labelBMFont->getContentSize());
    } else if(_labelTTF) {
        _labelTTF->setFontName(fontName);
        setContentSize(_labelTTF->getContentSize());
    }
}

LabelView* createLabelInParentCenter(CCNode * parent,
                              const char *string,
                              const char * styleId,
                              bool removeAllChildren) {
    CCSize size = parent->getContentSize();
    if (removeAllChildren) {
        parent->removeAllChildrenWithCleanup(true);
    }
    LabelView* ttf = LabelView::createWithFontStyle(string,styleId,size,kCCTextAlignmentCenter,
                                                    kCCVerticalTextAlignmentCenter);
    ttf->setAnchorPoint(ccp(0.5, 0.5));
    ttf->setPosition(ccp(size.width/2, size.height / 2));
    parent->addChild(ttf);
    return ttf;
}

LabelView* createLabelInParentLeftCenter(CCNode * parent,
                                  const char *string,
                                  const char * styleId,
                                  bool removeAllChildren) {
    LabelView* ttf = createLabelInParentCenter(parent, string, styleId,removeAllChildren);
    ttf->setAnchorPoint(ccp(0, 0.5));
    ttf->setPosition(ccp(0, parent->getContentSize().height / 2));
    
    return ttf;
}

LabelView* createLabelTTFItem(CCNode * parent,
                              const char *string,
                              const char * styleId,
                              const bool resetAll) {
    return createLabelInParentLeftCenter(parent, string, styleId,resetAll);
}