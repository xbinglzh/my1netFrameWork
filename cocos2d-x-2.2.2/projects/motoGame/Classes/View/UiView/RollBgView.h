//
//  RollBgView.h
//  motoGame
//
//  Created by xUanBing on 14-3-30.
//
//

#ifndef __motoGame__RollBgView__
#define __motoGame__RollBgView__

#include "cocos2d.h"

USING_NS_CC;

class RollBgView : public CCLayer {
public:
    RollBgView();
    ~RollBgView();
    
	virtual bool init();
    
	virtual void update(float t);
    
	CREATE_FUNC(RollBgView);
};

#endif /* defined(__motoGame__RollBgView__) */
