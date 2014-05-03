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
#include "ConstansDef.h"

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
    
    void appendEnergyUnit();
    void appendEnergy(float energy);
    float getEnergyRatio();
    
    void startUseEnergy();
    void stopUseEnergy();
private:
    void genSaveEnergyRatio();
    void decreaseEnergyUnit();
    void decreaseEnergy(float energy);
    void updateEnergy();
    
private:
    GameConfig* _gameConfig;
    float       _currentEnergy;
    float       _saveEnergyRatio;
};

#endif /* defined(__motoGame__GameModel__) */
