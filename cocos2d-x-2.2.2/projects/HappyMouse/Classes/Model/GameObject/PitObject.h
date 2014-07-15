//
//  PitObject.h
//  HappyMouse
//
//  Created by xUanBing on 14-7-15.
//
//

#ifndef __HappyMouse__PitObject__
#define __HappyMouse__PitObject__

#include "cocos2d.h"

USING_NS_CC;

class CCSpriteExt;

class PitObject : public CCNodeRGBA {
    
public:
    PitObject();
    ~PitObject();
    static PitObject* create();
    
public:
     void addNodeToContent(CCNode* node);
    
protected:
    bool init();
   
private:
    CCSpriteExt* _pit;
    
};

#endif /* defined(__HappyMouse__PitObject__) */
