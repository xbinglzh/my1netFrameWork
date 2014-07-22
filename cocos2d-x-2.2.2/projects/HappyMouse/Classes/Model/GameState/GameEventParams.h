//
//  GameEventParams.h
//  HappyMouse
//
//  Created by xUanBing on 14-7-22.
//
//

#ifndef __HappyMouse__GameEventParams__
#define __HappyMouse__GameEventParams__

#include "cocos2d.h"

USING_NS_CC;

class  GameEventParams : public CCObject {
    
public:
    GameEventParams();
    ~GameEventParams();
    bool init();
    CREATE_FUNC(GameEventParams);
    static GameEventParams * create(const int32_t event,CCObject * data = NULL);
    
public:
    CC_SYNTHESIZE_RETAIN(CCObject * ,_data, Data);
    CC_SYNTHESIZE(int32_t ,_event, Event);
    
};


#endif /* defined(__HappyMouse__GameEventParams__) */
