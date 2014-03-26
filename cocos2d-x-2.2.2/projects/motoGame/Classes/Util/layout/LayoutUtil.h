//
//  LayoutUtil.h
//  iLostCity
//
//  Created by xUanBing on 13-7-8.
//  
//

#ifndef __iLostCity__LayoutUtil__
#define __iLostCity__LayoutUtil__

#include "cocos2d.h"

namespace cocos2d {
    class CCNode;
}

namespace LayoutUtil {
    void layoutLeft(cocos2d::CCNode* view, cocos2d::CCNode* target, float offsetX = 0.0, float offsetY = 0.0);
    void layoutRight(cocos2d::CCNode* view, cocos2d::CCNode* target, float offsetX = 0.0, float offsetY = 0.0);
    void layoutTop(cocos2d::CCNode* view, cocos2d::CCNode* target, float offsetX = 0.0, float offsetY = 0.0);
    void layoutBottom(cocos2d::CCNode* view, cocos2d::CCNode* target, float offsetX = 0.0, float offsetY = 0.0);
    void layoutCenter(cocos2d::CCNode* view, cocos2d::CCNode* target, float offsetX = 0.0, float offsetY = 0.0);
    void layoutTopLeft(cocos2d::CCNode* view, cocos2d::CCNode* target, float offsetX = 0.0, float offsetY = 0.0);
    void layoutTopRight(cocos2d::CCNode* view, cocos2d::CCNode* target, float offsetX = 0.0, float offsetY = 0.0);
    void layoutBottomLeft(cocos2d::CCNode* view, cocos2d::CCNode* target, float offsetX = 0.0, float offsetY = 0.0);
    void layoutBottomRight(cocos2d::CCNode* view, cocos2d::CCNode* target, float offsetX = 0.0, float offsetY = 0.0);
    
    void layoutParentLeft(cocos2d::CCNode* view, float offsetX = 0.0, float offsetY = 0.0);
    void layoutParentRight(cocos2d::CCNode* view, float offsetX = 0.0, float offsetY = 0.0);
    void layoutParentTop(cocos2d::CCNode* view, float offsetX = 0.0, float offsetY = 0.0);
    void layoutParentBottom(cocos2d::CCNode* view, float offsetX = 0.0, float offsetY = 0.0);
    void layoutParentCenter(cocos2d::CCNode* view, float offsetX = 0.0, float offsetY = 0.0);
    void layoutParentTopLeft(cocos2d::CCNode* view, float offsetX = 0.0, float offsetY = 0.0);
    void layoutParentTopRight(cocos2d::CCNode* view, float offsetX = 0.0, float offsetY = 0.0);
    void layoutParentBottomLeft(cocos2d::CCNode* view, float offsetX = 0.0, float offsetY = 0.0);
    void layoutParentBottomRight(cocos2d::CCNode* view, float offsetX = 0.0, float offsetY = 0.0);
    
    
    void layout(cocos2d::CCNode* view, float viewAlignX, float viewAlignY, cocos2d::CCNode* target,
                float targetAlignX, float targetAlignY, bool targetIsParent = false, float offsetX = 0.0, float offsetY = 0.0);
}


#endif /* defined(__iLostCity__LayoutUtil__) */
