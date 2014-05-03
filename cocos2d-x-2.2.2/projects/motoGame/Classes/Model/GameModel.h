//
//  GameModel.h
//  motoGame
//
//  Created by xUanBing on 14-5-3.
//
//

#ifndef __motoGame__GameModel__
#define __motoGame__GameModel__

#include "cocos2d.h"
#include "GameConfig.h"

USING_NS_CC;

class GameModel : public CCObject {
    
public:
    GameModel();
    virtual ~GameModel();
    bool init(void);
    
public:
    static GameModel *sharedInstance(void);
    static void purgeInstance(void);
    /**
     战斗场景业务逻辑循环
     */
	void update(float dt);
    void clearUserData();
    
private:
    GameConfig* _gameConfig;
};

#endif /* defined(__motoGame__GameModel__) */
