//
//  AnimationDelegateExt.h
//  iLostCity
//
//  Created by Ryan_Y on 13-5-21.
//
//

#ifndef iLostCity_AnimationDelegateExt_h
#define iLostCity_AnimationDelegateExt_h

class AnimationDelegateExt{
public:
    virtual void onAnimationEvent(void * animation, const char * eventType, const char * movementID) = 0;
};
#endif
