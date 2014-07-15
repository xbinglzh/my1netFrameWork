//
//  CCScale9ProgressBar.cpp
//  iLostCity
//
//  Created by xUanBing on 13-10-18.
//
//

#include "CCScale9ProgressBar.h"

enum positions
{
    pCentre = 0,
    pTop,
    pLeft,
    pRight,
    pBottom,
    pTopRight,
    pTopLeft,
    pBottomRight,
    pBottomLeft
};

CCScale9ProgressBar::CCScale9ProgressBar()
: m_insetLeft(0)
, m_insetTop(0)
, m_insetRight(0)
, m_insetBottom(0)
, m_cOpacity(0)
, m_bSpritesGenerated(false)
, m_bSpriteFrameRotated(false)
, m_positionsAreDirty(false)
, scale9Image(NULL)
, topLeft(NULL)
, top(NULL)
, topRight(NULL)
, left(NULL)
, centre(NULL)
, right(NULL)
, bottomLeft(NULL)
, bottom(NULL)
, bottomRight(NULL)
, m_bIsOpacityModifyRGB(false)
, m_fRatio(1)
, m_bIsProgressWithHead(false)
, m_percentIsDirty(false)
{
    
}

CCScale9ProgressBar::~CCScale9ProgressBar()
{
    CC_SAFE_RELEASE(scale9Image);
}

bool CCScale9ProgressBar::init()
{
    return this->initWithBatchNode(NULL, CCRectZero, CCRectZero);
}

bool CCScale9ProgressBar::initWithBatchNode(CCSpriteBatchNode* batchnode, CCRect rect, CCRect capInsets)
{
    return this->initWithBatchNode(batchnode, rect, false, capInsets);
}

bool CCScale9ProgressBar::initWithBatchNode(CCSpriteBatchNode* batchnode, CCRect rect, bool rotated, CCRect capInsets)
{
    if(batchnode)
    {
        this->updateWithBatchNode(batchnode, rect, rotated, capInsets);
        this->setAnchorPoint(ccp(0.5f, 0.5f));
    }
    this->m_positionsAreDirty = true;
    
    return true;
}

CCProgressTimer* CCScale9ProgressBar::createProgressTimer(CCSprite* sprite){
    CCProgressTimer* temp = CCProgressTimer::create(sprite);
    temp->setType(kCCProgressTimerTypeBar);
    temp->setMidpoint(CCPointZero);
    temp->setBarChangeRate(ccp(1, 0));
    temp->setReverseProgress(false);
    return temp;
}

bool CCScale9ProgressBar::updateWithBatchNode(CCSpriteBatchNode* batchnode, CCRect rect, bool rotated, CCRect capInsets)
{
    GLubyte opacity = m_cOpacity;
    ccColor3B color = m_tColor;
    
    // Release old sprites
    this->removeAllChildrenWithCleanup(true);
    
    if(this->scale9Image != batchnode)
    {
        CC_SAFE_RELEASE(this->scale9Image);
        scale9Image = batchnode;
        CC_SAFE_RETAIN(scale9Image);
    }
    
    scale9Image->removeAllChildrenWithCleanup(true);
    
    m_capInsets = capInsets;
    
    // If there is no given rect
    if ( rect.equals(CCRectZero)) {
        CCSize textureSize = scale9Image->getTextureAtlas()->getTexture()->getContentSize();
        rect = CCRectMake(0, 0, textureSize.width, textureSize.height);
    }
    
    // Set the given rect's size as original size
    m_spriteRect = rect;
    m_originalSize = rect.size;
    m_preferredSize = m_originalSize;
    m_capInsetsInternal = capInsets;
    
    // Get the image edges
    float l = rect.origin.x;
    float t = rect.origin.y;
    float h = rect.size.height;
    float w = rect.size.width;
    
    // If there is no specified center region
    if ( m_capInsetsInternal.equals(CCRectZero) )
    {
        // Apply the 3x3 grid format
        if (rotated) {
            m_capInsetsInternal = CCRectMake(l+h/3, t+w/3, w/3, h/3);
        }else {
            m_capInsetsInternal = CCRectMake(l+w/3, t+h/3, w/3, h/3);
        }
    }
    
    //
    // Set up the image
    //
    if (rotated)
    {
        // Sprite frame is rotated
        
        // Centre
        CCSprite* tempcentre      = CCSprite::create();
        tempcentre->initWithTexture(scale9Image->getTexture(), m_capInsetsInternal, true);
        centre = CCProgressTimer::create(tempcentre);
        addChild(centre, 0, pCentre);
        
        // Bottom
        CCSprite* tempbottom         =  CCSprite::create();
        tempbottom->initWithTexture(scale9Image->getTexture(), CCRectMake(l,
                                                                          m_capInsetsInternal.origin.y,
                                                                          m_capInsetsInternal.size.width,
                                                                          m_capInsetsInternal.origin.x - l),
                                    rotated
                                    );
        bottom = createProgressTimer(tempbottom);
        addChild(bottom, 1, pBottom);
        
        // Top
        CCSprite* temptop      = CCSprite::create();
        temptop->initWithTexture(scale9Image->getTexture(),CCRectMake(m_capInsetsInternal.origin.x + m_capInsetsInternal.size.height,
                                                                      m_capInsetsInternal.origin.y,
                                                                      m_capInsetsInternal.size.width,
                                                                      h - m_capInsetsInternal.size.height - (m_capInsetsInternal.origin.x - l)),
                                 rotated
                                 );
        top = createProgressTimer(temptop);
        addChild(top, 1, pTop);
        
        // Right
        CCSprite* tempRight        = CCSprite::create();
        tempRight->initWithTexture(scale9Image->getTexture(), CCRectMake(m_capInsetsInternal.origin.x,
                                                                         m_capInsetsInternal.origin.y+m_capInsetsInternal.size.width,
                                                                         w - (m_capInsetsInternal.origin.y-t)-m_capInsetsInternal.size.width,
                                                                         m_capInsetsInternal.size.height),
                                   rotated
                                   );
        
        right = createProgressTimer(tempRight);
        addChild(right, 1, pRight);
        
        // Left
        CCSprite* templeft       = CCSprite::create();
        templeft->initWithTexture(scale9Image->getTexture(), CCRectMake(m_capInsetsInternal.origin.x,
                                                                        t,
                                                                        m_capInsetsInternal.origin.y - t,
                                                                        m_capInsetsInternal.size.height),
                                  rotated
                                  );
        left = createProgressTimer(templeft);
        addChild(left ,1, pLeft);
        
        // Top right
        CCSprite* temptopRight     = CCSprite::create();
        temptopRight->initWithTexture(scale9Image->getTexture(), CCRectMake(m_capInsetsInternal.origin.x + m_capInsetsInternal.size.height,
                                                                            m_capInsetsInternal.origin.y + m_capInsetsInternal.size.width,
                                                                            w - (m_capInsetsInternal.origin.y-t)-m_capInsetsInternal.size.width,
                                                                            h - m_capInsetsInternal.size.height - (m_capInsetsInternal.origin.x - l)),
                                      rotated
                                      );
        topRight = createProgressTimer(temptopRight);
        addChild(topRight ,2 ,pTopRight);
        
        // Top left
        CCSprite* temptopLeft    = CCSprite::create();
        temptopLeft->initWithTexture(scale9Image->getTexture(), CCRectMake(m_capInsetsInternal.origin.x + m_capInsetsInternal.size.height,
                                                                           t,
                                                                           m_capInsetsInternal.origin.y - t,
                                                                           h - m_capInsetsInternal.size.height - (m_capInsetsInternal.origin.x - l)),
                                     rotated
                                     );
        topLeft = createProgressTimer(temptopLeft);
        addChild(topLeft, 2, pTopLeft);
        
        // Bottom right
        CCSprite* tempbottomRight  = CCSprite::create();
        tempbottomRight->initWithTexture(scale9Image->getTexture(),CCRectMake(l,
                                                                              m_capInsetsInternal.origin.y + m_capInsetsInternal.size.width,
                                                                              w - (m_capInsetsInternal.origin.y-t)-m_capInsetsInternal.size.width,
                                                                              m_capInsetsInternal.origin.x - l),
                                         rotated
                                         );
        bottomRight = createProgressTimer(tempbottomRight);
        addChild(bottomRight, 2, pBottomRight);
        
        // Bottom left
        CCSprite* tempbottomLeft     = CCSprite::create();
        tempbottomLeft->initWithTexture(scale9Image->getTexture(), CCRectMake(l,
                                                                              t,
                                                                              m_capInsetsInternal.origin.y - t,
                                                                              m_capInsetsInternal.origin.x - l),
                                        rotated
                                        );
        bottomLeft = createProgressTimer(tempbottomLeft);
        addChild(bottomLeft, 2, pBottomLeft);
    }
    else
    {
        // Sprite frame is not rotated
        // Centre
        CCSprite* tempcentre = CCSprite::create();
        tempcentre->initWithTexture(scale9Image->getTexture(), m_capInsetsInternal, rotated);
        centre = createProgressTimer(tempcentre);
        addChild(centre, 0, pCentre);
        
        // Top
        CCSprite* temptop = CCSprite::create();
        temptop->initWithTexture(scale9Image->getTexture(), CCRectMake(m_capInsetsInternal.origin.x,
                                                                       t,
                                                                       m_capInsetsInternal.size.width,
                                                                       m_capInsetsInternal.origin.y - t),
                                 rotated
                                 );
        top = createProgressTimer(temptop);
        addChild(top, 1, pTop);
        
        // Bottom
        CCSprite* tempbottom = CCSprite::create();
        tempbottom->initWithTexture(scale9Image->getTexture(), CCRectMake( m_capInsetsInternal.origin.x,
                                                                          m_capInsetsInternal.origin.y + m_capInsetsInternal.size.height,
                                                                          m_capInsetsInternal.size.width,
                                                                          h - (m_capInsetsInternal.origin.y - t + m_capInsetsInternal.size.height)),
                                    rotated);
        bottom = createProgressTimer(tempbottom);
        addChild(bottom, 1, pBottom);
        
        // Left
        CCSprite* templeft = CCSprite::create();
        templeft->initWithTexture(scale9Image->getTexture(), CCRectMake(
                                                                        l,
                                                                        m_capInsetsInternal.origin.y,
                                                                        m_capInsetsInternal.origin.x - l,
                                                                        m_capInsetsInternal.size.height),
                                  rotated);
        left = createProgressTimer(templeft);
        addChild(left, 1, pLeft);
        
        // Right
        CCSprite* tempright = CCSprite::create();
        tempright->initWithTexture(scale9Image->getTexture(), CCRectMake(
                                                                         m_capInsetsInternal.origin.x + m_capInsetsInternal.size.width,
                                                                         m_capInsetsInternal.origin.y,
                                                                         w - (m_capInsetsInternal.origin.x - l + m_capInsetsInternal.size.width),
                                                                         m_capInsetsInternal.size.height),
                                   rotated);
        right = createProgressTimer(tempright);
        addChild(right, 1, pRight);
        
        // Top left
        CCSprite* temptopLeft = CCSprite::create();
        temptopLeft->initWithTexture(scale9Image->getTexture(), CCRectMake(
                                                                           l,
                                                                           t,
                                                                           m_capInsetsInternal.origin.x - l,
                                                                           m_capInsetsInternal.origin.y - t),
                                     rotated);
        topLeft = createProgressTimer(temptopLeft);
        addChild(topLeft, 2, pTopLeft);
        
        // Top right
        CCSprite* temptopRight = CCSprite::create();
        temptopRight->initWithTexture(scale9Image->getTexture(), CCRectMake(
                                                                            m_capInsetsInternal.origin.x + m_capInsetsInternal.size.width,
                                                                            t,
                                                                            w - (m_capInsetsInternal.origin.x - l + m_capInsetsInternal.size.width),
                                                                            m_capInsetsInternal.origin.y - t),
                                      rotated);
        topRight = createProgressTimer(temptopRight);
        addChild(topRight, 2, pTopRight);
        
        // Bottom left
        CCSprite* tempbottomLeft = CCSprite::create();
        tempbottomLeft->initWithTexture(scale9Image->getTexture(), CCRectMake(
                                                                              l,
                                                                              m_capInsetsInternal.origin.y + m_capInsetsInternal.size.height,
                                                                              m_capInsetsInternal.origin.x - l,
                                                                              h - (m_capInsetsInternal.origin.y - t + m_capInsetsInternal.size.height)),
                                        rotated);
        bottomLeft = createProgressTimer(tempbottomLeft);
        addChild(bottomLeft, 2, pBottomLeft);
        
        // Bottom right
        CCSprite* tempbottomRight = CCSprite::create();
        tempbottomRight->initWithTexture(scale9Image->getTexture(), CCRectMake(
                                                                               m_capInsetsInternal.origin.x + m_capInsetsInternal.size.width,
                                                                               m_capInsetsInternal.origin.y + m_capInsetsInternal.size.height,
                                                                               w - (m_capInsetsInternal.origin.x - l + m_capInsetsInternal.size.width),
                                                                               h - (m_capInsetsInternal.origin.y - t + m_capInsetsInternal.size.height)),
                                         rotated);
        bottomRight = createProgressTimer(tempbottomRight);
        addChild(bottomRight, 2, pBottomRight);
    }
    
    this->setContentSize(rect.size);
    this->addChild(scale9Image);
    
    if (m_bSpritesGenerated)
    {
        // Restore color and opacity
        this->setOpacity(opacity);
        this->setColor(color);
    }
    m_bSpritesGenerated = true;
    
    return true;
}

void CCScale9ProgressBar::setContentSize(const CCSize &size)
{
    CCNode::setContentSize(size);
    this->m_positionsAreDirty = true;
}

void CCScale9ProgressBar::setIsProgressWithHead(bool var){
    m_bIsProgressWithHead = var;
}

bool CCScale9ProgressBar::getIsProgressWithHead(){
    return m_bIsProgressWithHead;
}

void CCScale9ProgressBar::setVisibleRatio(float ratio){
    if(ratio < 0){
        ratio = 0;
    }else if(ratio > 1){
        ratio = 1;
    }
    m_fRatio = ratio;
    
    this->updateVisiblePercent();
    this->updatePositions();
    
    m_percentIsDirty = true;
}

float CCScale9ProgressBar::getVisibleRatio(){
    return m_fRatio;
}

void CCScale9ProgressBar::setLeftPercent(int percent){
    left->setPercentage(percent);
    topLeft->setPercentage(percent);
    bottomLeft->setPercentage(percent);
}

void CCScale9ProgressBar::setCenterPercent(int percent){
    centre->setPercentage(percent);
    top->setPercentage(percent);
    bottom->setPercentage(percent);
}

void CCScale9ProgressBar::setRightPercent(int percent){
    right->setPercentage(percent);
    topRight->setPercentage(percent);
    bottomRight->setPercentage(percent);
}

void CCScale9ProgressBar::updatePercent(){
    float width = m_fRatio * this->getContentSize().width;
    if (width >= 0 && width < leftWidth) {
        int percent = 100.0 * (width)/leftWidth;
        setLeftPercent(percent);
        setCenterPercent(0);
        setRightPercent(0);
    }else if (width > leftWidth && width < leftWidth + centerWidth) {
        int percent = 100.0 * (width - leftWidth)/centerWidth;
        setLeftPercent(100);
        setCenterPercent(percent);
        setRightPercent(0);
    }else if (width > leftWidth + centerWidth) {
        int percent = 100.0 * (width - leftWidth - centerWidth)/rightWidth;
        setLeftPercent(100);
        setCenterPercent(100);
        setRightPercent(percent);
    }
}

void CCScale9ProgressBar::updatePercentWithHead(){
    setLeftPercent(100);
    setCenterPercent(100);
    setRightPercent(100);
    float width = (m_preferredSize.width - m_originalSize.width)*m_fRatio + m_originalSize.width;
    //    CCLOG("new width %.2f", width);
    setContentSize(CCSize(width, m_preferredSize.height));
}

void CCScale9ProgressBar::updateVisiblePercent(){
    if(m_bIsProgressWithHead){
        updatePercentWithHead();
    }else{
        this->updatePositions();
        updatePercent();
    }
}

void CCScale9ProgressBar::updatePositions()
{
    CCSize size = this->getContentSize();
    
    float sizableWidth = size.width - topLeft->getContentSize().width - topRight->getContentSize().width;
    centerWidth = sizableWidth;
    float sizableHeight = size.height - topLeft->getContentSize().height - bottomRight->getContentSize().height;
    
    float horizontalScale = sizableWidth/centre->getContentSize().width;
    float verticalScale = sizableHeight/centre->getContentSize().height;
    centre->setScaleX(horizontalScale);
    centre->setScaleY(verticalScale);
    
    float rescaledWidth = centre->getContentSize().width * horizontalScale;
    float rescaledHeight = centre->getContentSize().height * verticalScale;
    
    leftWidth = bottomLeft->getContentSize().width;
    rightWidth = right->getContentSize().width;
    float bottomHeight = bottomLeft->getContentSize().height;
    
    bottomLeft->setAnchorPoint(ccp(0,0));
    bottomRight->setAnchorPoint(ccp(0,0));
    topLeft->setAnchorPoint(ccp(0,0));
    topRight->setAnchorPoint(ccp(0,0));
    left->setAnchorPoint(ccp(0,0));
    right->setAnchorPoint(ccp(0,0));
    top->setAnchorPoint(ccp(0,0));
    bottom->setAnchorPoint(ccp(0,0));
    centre->setAnchorPoint(ccp(0,0));
    
    // Position corners
    bottomLeft->setPosition(ccp(0,0));
    bottomRight->setPosition(ccp(leftWidth+rescaledWidth,0));
    topLeft->setPosition(ccp(0, bottomHeight+rescaledHeight));
    topRight->setPosition(ccp(leftWidth+rescaledWidth, bottomHeight+rescaledHeight));
    
    // Scale and position borders
    left->setPosition(ccp(0, bottomHeight));
    left->setScaleY(verticalScale);
    right->setPosition(ccp(leftWidth+rescaledWidth,bottomHeight));
    right->setScaleY(verticalScale);
    bottom->setPosition(ccp(leftWidth,0));
    bottom->setScaleX(horizontalScale);
    top->setPosition(ccp(leftWidth,bottomHeight+rescaledHeight));
    top->setScaleX(horizontalScale);
    
    // Position centre
    centre->setPosition(ccp(leftWidth, bottomHeight));
    
}

bool CCScale9ProgressBar::initWithFile(const char* file, CCRect rect,  CCRect capInsets)
{
    CCAssert(file != NULL, "Invalid file for sprite");
    
    CCSpriteBatchNode *batchnode = CCSpriteBatchNode::create(file, 9);
    bool pReturn = this->initWithBatchNode(batchnode, rect, capInsets);
    return pReturn;
}

CCScale9ProgressBar* CCScale9ProgressBar::spriteWithFile(const char* file, CCRect rect,  CCRect capInsets)
{
    return CCScale9ProgressBar::create(file, rect, capInsets);
}

CCScale9ProgressBar* CCScale9ProgressBar::create(const char* file, CCRect rect,  CCRect capInsets)
{
    CCScale9ProgressBar* pReturn = new CCScale9ProgressBar();
    if ( pReturn && pReturn->initWithFile(file, rect, capInsets) )
    {
        pReturn->autorelease();
        return pReturn;
    }
    CC_SAFE_DELETE(pReturn);
    return NULL;
}

CCScale9ProgressBar* CCScale9ProgressBar::create(CCRect capInsets, const char* file)
{
    CCScale9ProgressBar* pReturn = new CCScale9ProgressBar();
    if ( pReturn && pReturn->initWithFile(file, CCRectZero, capInsets) )
    {
        pReturn->autorelease();
        return pReturn;
    }
    CC_SAFE_DELETE(pReturn);
    return NULL;
}

bool CCScale9ProgressBar::initWithFile(const char* file, CCRect rect)
{
    CCAssert(file != NULL, "Invalid file for sprite");
    bool pReturn = this->initWithFile(file, rect, CCRectZero);
    return pReturn;
}

CCScale9ProgressBar* CCScale9ProgressBar::spriteWithFile(const char* file, CCRect rect)
{
    return CCScale9ProgressBar::create(file, rect);
}

CCScale9ProgressBar* CCScale9ProgressBar::create(const char* file, CCRect rect)
{
    CCScale9ProgressBar* pReturn = new CCScale9ProgressBar();
    if ( pReturn && pReturn->initWithFile(file, rect) )
    {
        pReturn->autorelease();
        return pReturn;
    }
    CC_SAFE_DELETE(pReturn);
    return NULL;
}


bool CCScale9ProgressBar::initWithFile(CCRect capInsets, const char* file)
{
    bool pReturn = this->initWithFile(file, CCRectZero, capInsets);
    return pReturn;
}

CCScale9ProgressBar* CCScale9ProgressBar::spriteWithFile(CCRect capInsets, const char* file)
{
    return CCScale9ProgressBar::create(capInsets, file);
}

bool CCScale9ProgressBar::initWithFile(const char* file)
{
    bool pReturn = this->initWithFile(file, CCRectZero);
    return pReturn;
    
}

CCScale9ProgressBar* CCScale9ProgressBar::spriteWithFile(const char* file)
{
    return CCScale9ProgressBar::create(file);
}

CCScale9ProgressBar* CCScale9ProgressBar::create(const char* file)
{
    CCScale9ProgressBar* pReturn = new CCScale9ProgressBar();
    if ( pReturn && pReturn->initWithFile(file) )
    {
        pReturn->autorelease();
        return pReturn;
    }
    CC_SAFE_DELETE(pReturn);
    return NULL;
}

bool CCScale9ProgressBar::initWithSpriteFrame(CCSpriteFrame* spriteFrame, CCRect capInsets)
{
    CCAssert(spriteFrame != NULL, "Sprite frame must be not nil");
    
    CCSpriteBatchNode *batchnode = CCSpriteBatchNode::createWithTexture(spriteFrame->getTexture(), 9);
    bool pReturn = this->initWithBatchNode(batchnode, spriteFrame->getRect(), spriteFrame->isRotated(), capInsets);
    return pReturn;
}

CCScale9ProgressBar* CCScale9ProgressBar::spriteWithSpriteFrame(CCSpriteFrame* spriteFrame, CCRect capInsets)
{
    return CCScale9ProgressBar::createWithSpriteFrame(spriteFrame, capInsets);
}

CCScale9ProgressBar* CCScale9ProgressBar::createWithSpriteFrame(CCSpriteFrame* spriteFrame, CCRect capInsets)
{
    CCScale9ProgressBar* pReturn = new CCScale9ProgressBar();
    if ( pReturn && pReturn->initWithSpriteFrame(spriteFrame, capInsets) )
    {
        pReturn->autorelease();
        return pReturn;
    }
    CC_SAFE_DELETE(pReturn);
    return NULL;
}
bool CCScale9ProgressBar::initWithSpriteFrame(CCSpriteFrame* spriteFrame)
{
    CCAssert(spriteFrame != NULL, "Invalid spriteFrame for sprite");
    bool pReturn = this->initWithSpriteFrame(spriteFrame, CCRectZero);
    return pReturn;
}


CCScale9ProgressBar* CCScale9ProgressBar::spriteWithSpriteFrame(CCSpriteFrame* spriteFrame)
{
    return CCScale9ProgressBar::createWithSpriteFrame(spriteFrame);
}

CCScale9ProgressBar* CCScale9ProgressBar::createWithSpriteFrame(CCSpriteFrame* spriteFrame)
{
    CCScale9ProgressBar* pReturn = new CCScale9ProgressBar();
    if ( pReturn && pReturn->initWithSpriteFrame(spriteFrame) )
    {
        pReturn->autorelease();
        return pReturn;
    }
    CC_SAFE_DELETE(pReturn);
    return NULL;
}

bool CCScale9ProgressBar::initWithSpriteFrameName(const char* spriteFrameName, CCRect capInsets)
{
    CCAssert(spriteFrameName != NULL, "Invalid spriteFrameName for sprite");
    
    CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(spriteFrameName);
    bool pReturn = this->initWithSpriteFrame(frame, capInsets);
    return pReturn;
}

CCScale9ProgressBar* CCScale9ProgressBar::spriteWithSpriteFrameName(const char* spriteFrameName, CCRect capInsets)
{
    return CCScale9ProgressBar::createWithSpriteFrameName(spriteFrameName, capInsets);
}

CCScale9ProgressBar* CCScale9ProgressBar::createWithSpriteFrameName(const char* spriteFrameName, CCRect capInsets)
{
    CCScale9ProgressBar* pReturn = new CCScale9ProgressBar();
    if ( pReturn && pReturn->initWithSpriteFrameName(spriteFrameName, capInsets) )
    {
        pReturn->autorelease();
        return pReturn;
    }
    CC_SAFE_DELETE(pReturn);
    return NULL;
}

bool CCScale9ProgressBar::initWithSpriteFrameName(const char* spriteFrameName)
{
    bool pReturn = this->initWithSpriteFrameName(spriteFrameName, CCRectZero);
    return pReturn;
}

CCScale9ProgressBar* CCScale9ProgressBar::spriteWithSpriteFrameName(const char* spriteFrameName)
{
    return CCScale9ProgressBar::createWithSpriteFrameName(spriteFrameName);
}

CCScale9ProgressBar* CCScale9ProgressBar::createWithSpriteFrameName(const char* spriteFrameName)
{
    CCScale9ProgressBar* pReturn = new CCScale9ProgressBar();
    if ( pReturn && pReturn->initWithSpriteFrameName(spriteFrameName) )
    {
        pReturn->autorelease();
        return pReturn;
    }
    CC_SAFE_DELETE(pReturn);
    return NULL;
    
}

CCScale9ProgressBar* CCScale9ProgressBar::resizableSpriteWithCapInsets(CCRect capInsets)
{
    CCScale9ProgressBar* pReturn = new CCScale9ProgressBar();
    if ( pReturn && pReturn->initWithBatchNode(scale9Image, m_spriteRect, capInsets) )
    {
        pReturn->autorelease();
        return pReturn;
    }
    CC_SAFE_DELETE(pReturn);
    return NULL;
}

CCScale9ProgressBar* CCScale9ProgressBar::node()
{
    return CCScale9ProgressBar::create();
}

CCScale9ProgressBar* CCScale9ProgressBar::create()
{
    CCScale9ProgressBar *pReturn = new CCScale9ProgressBar();
    if (pReturn)
    {
        pReturn->autorelease();
        return pReturn;
    }
    CC_SAFE_DELETE(pReturn);
    return NULL;
}


//LabelBMFont - CCRGBAProtocol protocol
void CCScale9ProgressBar::setColor(const ccColor3B& color3)
{
    m_tColor = color3;
    if (scale9Image->getChildren() && scale9Image->getChildren()->count() != 0)
    {
        CCObject* child;
        CCARRAY_FOREACH(scale9Image->getChildren(), child)
        {
            CCRGBAProtocol* pNode = dynamic_cast<CCRGBAProtocol*>(child);
            if (pNode)
            {
                pNode->setColor(m_tColor);
            }
        }
    }
}
const ccColor3B& CCScale9ProgressBar::getColor(void)
{
    return m_tColor;
}

void CCScale9ProgressBar::setOpacity(GLubyte var)
{
    m_cOpacity = var;
    
    if (scale9Image->getChildren() && scale9Image->getChildren()->count() != 0)
    {
        CCObject* child;
        CCARRAY_FOREACH(scale9Image->getChildren(), child)
        {
            CCRGBAProtocol* pNode = dynamic_cast<CCRGBAProtocol*>(child);
            if (pNode)
            {
                pNode->setOpacity(m_cOpacity);
            }
        }
    }
}

/** sets the opacity.
 @warning If the the texture has premultiplied alpha then, the R, G and B channels will be modifed.
 Values goes from 0 to 255, where 255 means fully opaque.
 */
GLubyte CCScale9ProgressBar::getOpacity()
{
    return m_cOpacity;
}

void CCScale9ProgressBar::setPreferredSize(CCSize preferedSize)
{
    this->setContentSize(preferedSize);
    this->m_preferredSize = preferedSize;
}

CCSize CCScale9ProgressBar::getPreferredSize()
{
    return this->m_preferredSize;
}

void CCScale9ProgressBar::setCapInsets(CCRect capInsets)
{
    CCSize contentSize = this->getContentSize();
    this->updateWithBatchNode(this->scale9Image, this->m_spriteRect, m_bSpriteFrameRotated, capInsets);
    this->setContentSize(contentSize);
}

CCRect CCScale9ProgressBar::getCapInsets()
{
    return m_capInsets;
}

void CCScale9ProgressBar::updateCapInset()
{
    CCRect insets;
    if (this->m_insetLeft == 0 && this->m_insetTop == 0 && this->m_insetRight == 0 && this->m_insetBottom == 0)
    {
        insets = CCRectZero;
    }
    else
    {
        if (m_bSpriteFrameRotated)
        {
            insets = CCRectMake(m_spriteRect.origin.x + m_insetBottom,
                                m_spriteRect.origin.y + m_insetLeft,
                                m_spriteRect.size.width-m_insetRight-m_insetLeft,
                                m_spriteRect.size.height-m_insetTop-m_insetBottom);
        }
        else
        {
            insets = CCRectMake(m_spriteRect.origin.x + m_insetLeft,
                                m_spriteRect.origin.y + m_insetTop,
                                m_spriteRect.size.width-m_insetLeft-m_insetRight,
                                m_spriteRect.size.height-m_insetTop-m_insetBottom);
        }
    }
    this->setCapInsets(insets);
}

void CCScale9ProgressBar::setOpacityModifyRGB(bool var)
{
    m_bIsOpacityModifyRGB = var;
    if (scale9Image->getChildren() && scale9Image->getChildren()->count() != 0)
    {
        CCObject* child;
        CCARRAY_FOREACH(scale9Image->getChildren(), child)
        {
            CCRGBAProtocol* pNode = dynamic_cast<CCRGBAProtocol*>(child);
            if (pNode)
            {
                pNode->setOpacityModifyRGB(m_bIsOpacityModifyRGB);
            }
        }
    }
}
bool CCScale9ProgressBar::isOpacityModifyRGB()
{
    return m_bIsOpacityModifyRGB;
}

void CCScale9ProgressBar::setSpriteFrame(CCSpriteFrame * spriteFrame)
{
    CCSpriteBatchNode * batchnode = CCSpriteBatchNode::createWithTexture(spriteFrame->getTexture(), 9);
    this->updateWithBatchNode(batchnode, spriteFrame->getRect(), spriteFrame->isRotated(), CCRectZero);
    
    // Reset insets
    this->m_insetLeft = 0;
    this->m_insetTop = 0;
    this->m_insetRight = 0;
    this->m_insetBottom = 0;
}

float CCScale9ProgressBar::getInsetLeft()
{
    return this->m_insetLeft;
}

float CCScale9ProgressBar::getInsetTop()
{
    return this->m_insetTop;
}

float CCScale9ProgressBar::getInsetRight()
{
    return this->m_insetRight;
}

float CCScale9ProgressBar::getInsetBottom()
{
    return this->m_insetBottom;
}

void CCScale9ProgressBar::setInsetLeft(float insetLeft)
{
    this->m_insetLeft = insetLeft;
    this->updateCapInset();
}

void CCScale9ProgressBar::setInsetTop(float insetTop)
{
    this->m_insetTop = insetTop;
    this->updateCapInset();
}

void CCScale9ProgressBar::setInsetRight(float insetRight)
{
    this->m_insetRight = insetRight;
    this->updateCapInset();
}

void CCScale9ProgressBar::setInsetBottom(float insetBottom)
{
    this->m_insetBottom = insetBottom;
    this->updateCapInset();
}

void CCScale9ProgressBar::visit()
{
    if(this->m_percentIsDirty) {
        this->updateVisiblePercent();
        this->m_percentIsDirty = false;
    }
    
    if(this->m_positionsAreDirty) {
        this->updatePositions();
        this->m_positionsAreDirty = false;
    }
    
    CCNode::visit();
}