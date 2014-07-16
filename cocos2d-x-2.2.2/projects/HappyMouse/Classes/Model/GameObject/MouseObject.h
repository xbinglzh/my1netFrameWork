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
    
    int     getCurrentState();
    void    changeMouseState(CCInteger* targetState);
    bool    strikenMouse(cocos2d::CCTouch *pTouch);
    
protected:
    bool init();
    
private:
    void ariseMouse();
    void delayMouse();
    void dropMouse();
    
private:
    CCNode*               _contentNode;
    AnimNode*             _animNode;
    CCSpriteExt*          _sprite;
    CCScale9ProgressBar*  _hpBar;
    
    int            _curState;
    bool                  _isArise;
    
};


#endif /* defined(__HappyMouse__MouseObject__) */
