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
    void notifyRandomMouses();
    
public:
    void  switchToBattleSence(const int32_t battleZoneId,
                              const int32_t stageId,
                              const int32_t chipId = -1);
    
private:
    bool    isIdInRandomVector(int currentId);
    int     genRandomMouseIndex();
    void    genRandomMouseIds();
    
private:
    std::vector<int> _randomVector;
};

#endif /* defined(__HappyMouse__GameController__) */
