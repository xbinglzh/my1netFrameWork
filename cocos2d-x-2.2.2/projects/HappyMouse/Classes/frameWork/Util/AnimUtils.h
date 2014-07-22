//
//  AnimUtils.h
//  HappyMouse
//
//  Created by xUanBing on 14-7-22.
//
//

#ifndef __HappyMouse__AnimUtils__
#define __HappyMouse__AnimUtils__

#include "cocos2d.h"
#include "AnimNode.h"

USING_NS_CC;

class AnimUtils {
    
public:
    static AnimNode* createAnimById(const char* animId);
    
};


#endif /* defined(__HappyMouse__AnimUtils__) */
