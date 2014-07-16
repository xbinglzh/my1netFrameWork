//
//  MouseObject.h
//  HappyMouse
//
//  Created by xUanBing on 14-7-15.
//
//

#ifndef __HappyMouse__MouseObject__
#define __HappyMouse__MouseObject__

#include "cocos2d.h"
#include "ConstansDef.h"

USING_NS_CC;

class AnimNode;
class CCSpriteExt;
class CCScale9ProgressBar;

class MouseObject : public CCNodeRGBA {
    
public:
    MouseObject();
    ~MouseObject();
    static MouseObject* create();
    
    MouseState  getCurrentState();
    void        changeMouseState(MouseState targetState);
    
protected:
    bool init();
    
private:
    AnimNode*             _animNode;
    CCSpriteExt*          _sprite;
    CCScale9ProgressBar*  _hpBar;
    
    MouseState            _curState;
};


#endif /* defined(__HappyMouse__MouseObject__) */
