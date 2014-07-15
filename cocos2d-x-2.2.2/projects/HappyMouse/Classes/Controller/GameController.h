//
//  GameController.h
//  HappyMouse
//
//  Created by xUanBing on 14-7-15.
//
//

#ifndef __HappyMouse__GameController__
#define __HappyMouse__GameController__

#include "cocos2d.h"

USING_NS_CC;

class GameController : public CCObject {
    
public:
    GameController();
    ~GameController();
    
    static GameController* getInstance(void);
    static void purgeInstance(void);
    
    bool init();
    
    /**
     * 逻辑主循环
     */
    void update(float dt);
    
protected:
    
private:
    int genRandomMouseIndex();
};

#endif /* defined(__HappyMouse__GameController__) */
