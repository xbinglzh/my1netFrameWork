//
//  AnimUtils.cpp
//  HappyMouse
//
//  Created by xUanBing on 14-7-22.
//
//

#include "AnimUtils.h"
#include "GameConfig.h"

AnimNode* AnimUtils::createAnimById(const char* animId) {
    
    GameConfig* gConfig = GameConfig::sharedInstance();
    CCDictionary* dict = gConfig->getAnimationById(animId);
    AnimNode* anim = AnimNode::createAnim(dict, NULL);
    
    if (anim) {
        return anim;
    }
    
    return NULL;
    
}
