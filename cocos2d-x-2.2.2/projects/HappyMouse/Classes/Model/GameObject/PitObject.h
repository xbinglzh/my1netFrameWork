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
    static PitObject* create(int pitId,const char* pitImg);
    
public:
    bool strikenMouse(CCTouch* pTouch);
    bool isAddMonster();
    void setIsAddMonster(bool isAddMonster);
    
protected:
    bool init(int pitId,const char* pitImg);
    
private:
    void judgePopMouse(CCObject* pSender);
    
private:
    int          _pitId;
    
    CCSpriteExt* _pit;

    MouseObject* _mouse;
    bool         _isAddMonster;
};

#endif /* defined(__HappyMouse__PitObject__) */
