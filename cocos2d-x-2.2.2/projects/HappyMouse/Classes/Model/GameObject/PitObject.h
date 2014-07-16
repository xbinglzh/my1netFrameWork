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
class MouseObject;

class PitObject : public CCNodeRGBA {
    
public:
    PitObject();
    ~PitObject();
    static PitObject* create(int _pitId);
    
public:
    bool strikenMouse(CCTouch* pTouch);
    
protected:
    bool init(int _pitId);
    
private:
    void judgePopMouse(CCObject* pSender);
    
private:
    int          _pitId;
    
    CCSpriteExt* _pit;

    MouseObject* _mouse;
    
};

#endif /* defined(__HappyMouse__PitObject__) */
