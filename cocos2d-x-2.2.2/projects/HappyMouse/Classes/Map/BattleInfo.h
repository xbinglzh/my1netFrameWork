//
//  BattleInfo.h
//  HappyMouse
//
//  Created by xUanBing on 14-7-23.
//
//

#ifndef __HappyMouse__BattleInfo__
#define __HappyMouse__BattleInfo__

#include "cocos2d.h"
#include "GameObject.h"

class  BattleInfo{
    
public:
    BattleInfo();
	~BattleInfo();
    
    void reset();
    void initWithConfig(int32_t battleZoneId, int32_t stageId);
    
public:
    //Map Plist
    void setPveMapDict(cocos2d::CCDictionary* pveMapDict);
    cocos2d::CCString* getPveStateValueByKey(const std::string & key);
    
private:
    int32_t                       _battleZone;                      //关卡类型
    int32_t                       _stageId;                         //关卡ID
    float                         _battleTime;
    
    int32_t                       _totalWaves;                      //总波数
    int32_t                       _currentWaves;                    //当前波
    
    int32_t                       _currentTroopId;
    int32_t                       _currentMonsterId;
    
    cocos2d::CCDictionary*        _pveStageDict;
    
};

#endif /* defined(__HappyMouse__BattleInfo__) */
