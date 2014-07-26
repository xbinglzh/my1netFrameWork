//
//  AnimUtils.cpp
//  HappyMouse
//
//  Created by xUanBing on 14-7-22.
//
//

#include "AnimUtils.h"
#include "GameConfig.h"

AnimNode* AnimUtils::createAnimById(const char* animId, AnimNodeDelegate * delegate) {
    
    GameConfig* gConfig = GameConfig::getInstance();
    CCDictionary* dict = gConfig->getAnimationById(animId);
    AnimNode* anim = AnimNode::createAnim(dict, delegate);
    
    if (anim) {
        return anim;
    }
    
    return NULL;
    
}
