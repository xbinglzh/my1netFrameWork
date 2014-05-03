//
//  GameController.h
//  motoGame
//
//  Created by xUanBing on 14-5-3.
//
//

#ifndef __motoGame__GameController__
#define __motoGame__GameController__

#include "cocos2d.h"

class GameModel;

USING_NS_CC;

class GameController : public CCObject {
public:
    GameController();
    virtual ~GameController();
    
public:
    static GameController *sharedInstance(void);
    static void purgeInstance(void);
	bool init(void);

    /**
     业务逻辑主循环
     */
	void update(float dt);
    /**
     开始战斗场景
     */
	void startBattle();
    /**
     暂停战斗场景
     */
    void pauseBattle();
    /**
     继续战斗场景
     */
    void resumeBattle();
    /**
     * 退出战斗
     */
    void quitFromBattle();
    
    const bool isBattleRunning();
    
private:
    bool                   _updateStoped;
    GameModel*             _gameModel;
    CCDirector*            _director;
};

#endif /* defined(__motoGame__GameController__) */
