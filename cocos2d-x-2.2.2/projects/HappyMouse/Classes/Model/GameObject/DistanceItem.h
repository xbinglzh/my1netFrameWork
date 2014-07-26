//
//  DistanceItem.h
//  HappyMouse
//
//  Created by xUanBing on 14-7-26.
//
//

#ifndef __HappyMouse__DistanceItem__
#define __HappyMouse__DistanceItem__

#include "cocos2d.h"

class DistanceItem : public cocos2d::CCObject{
    
public:
    DistanceItem();
    virtual ~DistanceItem();
    virtual bool init();
    CREATE_FUNC(DistanceItem);
    
public:
    CC_SYNTHESIZE_RETAIN(cocos2d::CCObject *, _object, Object);
    CC_SYNTHESIZE(float, _distance, Distance);
    
};


#endif /* defined(__HappyMouse__DistanceItem__) */
