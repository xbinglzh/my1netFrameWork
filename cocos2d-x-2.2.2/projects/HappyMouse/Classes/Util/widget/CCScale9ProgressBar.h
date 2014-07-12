//
//  CCScale9ProgressBar.h
//  iLostCity
//
//  Created by xUanBing on 13-10-18.
//
//

#ifndef __iLostCity__CCScale9ProgressBar__
#define __iLostCity__CCScale9ProgressBar__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CCScale9ProgressBar : public CCNodeRGBA {
    
public:
    CCScale9ProgressBar();
    virtual ~CCScale9ProgressBar();
    
public:

    CC_SYNTHESIZE_READONLY(CCSize, m_originalSize, OriginalSize);
    
    CC_PROPERTY(CCSize, m_preferredSize, PreferredSize);
    CC_PROPERTY(CCRect, m_capInsets, CapInsets);
    CC_PROPERTY(float, m_insetLeft, InsetLeft);
    CC_PROPERTY(float, m_insetTop, InsetTop);
    CC_PROPERTY(float, m_insetRight, InsetRight);
    CC_PROPERTY(float, m_insetBottom, InsetBottom);
    CC_PROPERTY(bool, m_bIsProgressWithHead, IsProgressWithHead);
    CC_PROPERTY(float, ratio, VisibleRatio);
    CC_PROPERTY(GLubyte, m_cOpacity, Opacity);
    
    CC_PROPERTY_PASS_BY_REF(ccColor3B, m_tColor, Color);
    
protected:
    bool m_bSpritesGenerated;
    CCRect m_spriteRect;
    bool   m_bSpriteFrameRotated;
    CCRect m_capInsetsInternal;
    bool m_positionsAreDirty;
    bool m_percentIsDirty;
    
    void setLeftPercent(int per);
    void setCenterPercent(int per);
    void setRightPercent(int per);
    
    CCSpriteBatchNode* scale9Image;
    
    CCProgressTimer* createProgressTimer(CCSprite* sprite);
    
    float leftWidth, centerWidth, rightWidth;
    
    CCProgressTimer* top;
    CCProgressTimer* bottom;
    CCProgressTimer* centre;
    
    CCProgressTimer* topLeft;
    CCProgressTimer* bottomLeft;
    CCProgressTimer* left;
    
    CCProgressTimer* topRight;
    CCProgressTimer* bottomRight;
    CCProgressTimer* right;
    
    /** Conforms to CocosNodeRGBA protocol. */
    ccColor3B m_sColorUnmodified;
    bool m_bIsOpacityModifyRGB;
    
    void updateCapInset();
    void updatePositions();
    
    void updateVisiblePercent();
    
    void updatePercentWithHead();
    
    void updatePercent();
    
    // add by wenlong
    float m_fRatio;
    
public:
    
    virtual void setContentSize(const CCSize & size);
    virtual void visit();
    
    virtual bool init();
    
    virtual bool initWithBatchNode(CCSpriteBatchNode* batchnode, CCRect rect, bool rotated, CCRect capInsets);
    virtual bool initWithBatchNode(CCSpriteBatchNode* batchnode, CCRect rect, CCRect capInsets);

    virtual bool initWithFile(const char* file, CCRect rect,  CCRect capInsets);

    CC_DEPRECATED_ATTRIBUTE static CCScale9ProgressBar* spriteWithFile(const char* file, CCRect rect,  CCRect capInsets);
    
    static CCScale9ProgressBar* create(const char* file, CCRect rect,  CCRect capInsets);
    
    virtual bool initWithFile(const char* file, CCRect rect);
    
    CC_DEPRECATED_ATTRIBUTE static CCScale9ProgressBar* spriteWithFile(const char* file, CCRect rect);
    
    static CCScale9ProgressBar* create(const char* file, CCRect rect);

    virtual bool initWithFile(CCRect capInsets, const char* file);
    
    CC_DEPRECATED_ATTRIBUTE static CCScale9ProgressBar* spriteWithFile(CCRect capInsets, const char* file);

    static CCScale9ProgressBar* create(CCRect capInsets, const char* file);
    
    virtual bool initWithFile(const char* file);
    
    CC_DEPRECATED_ATTRIBUTE static CCScale9ProgressBar* spriteWithFile(const char* file);
    
    static CCScale9ProgressBar* create(const char* file);
    
    virtual bool initWithSpriteFrame(CCSpriteFrame* spriteFrame, CCRect capInsets);
    
    CC_DEPRECATED_ATTRIBUTE static CCScale9ProgressBar* spriteWithSpriteFrame(CCSpriteFrame* spriteFrame, CCRect capInsets);
    
    static CCScale9ProgressBar* createWithSpriteFrame(CCSpriteFrame* spriteFrame, CCRect capInsets);

    virtual bool initWithSpriteFrame(CCSpriteFrame* spriteFrame);
    
    CC_DEPRECATED_ATTRIBUTE static CCScale9ProgressBar* spriteWithSpriteFrame(CCSpriteFrame* spriteFrame);
    
    static CCScale9ProgressBar* createWithSpriteFrame(CCSpriteFrame* spriteFrame);
    
    virtual bool initWithSpriteFrameName(const char*spriteFrameName, CCRect capInsets);

    CC_DEPRECATED_ATTRIBUTE static CCScale9ProgressBar* spriteWithSpriteFrameName(const char*spriteFrameName, CCRect capInsets);
    
    static CCScale9ProgressBar* createWithSpriteFrameName(const char*spriteFrameName, CCRect capInsets);
    
    virtual bool initWithSpriteFrameName(const char*spriteFrameName);
    
    CC_DEPRECATED_ATTRIBUTE static CCScale9ProgressBar* spriteWithSpriteFrameName(const char*spriteFrameName);
    
    static CCScale9ProgressBar* createWithSpriteFrameName(const char*spriteFrameName);
    
    CCScale9ProgressBar* resizableSpriteWithCapInsets(CCRect capInsets);
    
    //@deprecated: This interface will be deprecated sooner or later.
    CC_DEPRECATED_ATTRIBUTE static CCScale9ProgressBar* node();
    
    static CCScale9ProgressBar* create();
    
    virtual void setOpacityModifyRGB(bool bValue);
    
    virtual bool isOpacityModifyRGB(void);
    
    virtual bool updateWithBatchNode(CCSpriteBatchNode* batchnode, CCRect rect, bool rotated, CCRect capInsets);
    
    virtual void setSpriteFrame(CCSpriteFrame * spriteFrame);
};


#endif /* defined(__iLostCity__CCScale9ProgressBar__) */
