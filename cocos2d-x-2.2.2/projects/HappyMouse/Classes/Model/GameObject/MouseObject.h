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

USING_NS_CC;

class MouseObject : public CCNodeRGBA {
    
public:
    
    MouseObject();
    ~MouseObject();
    static MouseObject* create();
    
protected:
    bool init();
    
private:
    
};


#endif /* defined(__HappyMouse__MouseObject__) */