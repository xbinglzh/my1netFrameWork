//
//  BattleInfo.cpp
//  HappyMouse
//
//  Created by xUanBing on 14-7-23.
//
//

#include "BattleInfo.h"
#include "GameConfig.h"
#include "ConstansDef.h"
#include "KeyConfigDef.h"

USING_NS_CC;

BattleInfo::BattleInfo() :
_battleZone(-1),
_stageId(-1),
_battleTime(-1),
_totalWaves(-1),
_currentWaves(-1),
_currentTroopId(-1),
_currentMonsterId(-1),
_pveStageDict(NULL) {
    
}

BattleInfo::~BattleInfo() {
    
}

void BattleInfo::reset() {
    _battleZone = -1;
    _stageId = -1;
    _battleTime = -1;
    _totalWaves = -1;
    _currentWaves = -1;
    _currentTroopId = -1;
    _currentMonsterId = -1;
}

void BattleInfo::initWithConfig(int32_t battleZoneId, int32_t stageId) {
    _pveStageDict = GameConfig::getInstance()->getStageConfig(battleZoneId, stageId);
}

CCString* BattleInfo::getPveStateValueByKey(const std::string &key) {
    CCString* mapId = static_cast<CCString*> (_pveStageDict ->objectForKey(KKeyMap));
    
    if (mapId) {
        CCDictionary* mapDict = GameConfig::getInstance()->getMapById(mapId->getCString());
        CCString* value = static_cast<CCString*> (mapDict->objectForKey(key));
        return value;
    }
    
    return NULL;
}




