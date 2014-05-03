//
//  GameBgRollView.h
//  motoGame
//
//  Created by xUanBing on 14-4-7.
//
//

#ifndef __motoGame__GameBgRollView__
#define __motoGame__GameBgRollView__

#include "cocos2d.h"

USING_NS_CC;

class GameBgRollView : public CCLayer {
    
public:
    GameBgRollView();
    ~GameBgRollView();
    
    bool init();
    virtual void update(float t);
    
    CREATE_FUNC(GameBgRollView);
    
    void setMoveSpeed(float speed);
    
private:
    float _moveSpeed;
    
};


#endif /* defined(__motoGame__GameBgRollView__) */
