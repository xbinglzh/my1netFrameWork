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

_pveStageDict(NULL),
_mapDataDict(NULL),
_mapDict(NULL),
_attackTeamDict(NULL) {
    
}

BattleInfo::~BattleInfo() {
    CC_SAFE_RELEASE_NULL(_pveStageDict);
    CC_SAFE_RELEASE_NULL(_mapDataDict);
    CC_SAFE_RELEASE_NULL(_mapDict);
    CC_SAFE_RELEASE_NULL(_attackTeamDict);
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
    
    CCString* mapId = static_cast<CCString*> (_pveStageDict ->objectForKey(KKeyMap));
    _mapDict = GameConfig::getInstance()->getMapById(mapId->getCString());
    
    CCString* mapDataId = static_cast<CCString*>(_mapDict->objectForKey(KKeyMapData));
    _mapDataDict = GameConfig::getInstance()->getMapDataById(mapDataId->getCString());
    
    CCString* attackTeam = static_cast<CCString*>(_pveStageDict->objectForKey(KKeyAttackTeam));
    _attackTeamDict = GameConfig::getInstance()->getAttackTeamById(attackTeam->getCString());
    
}

CCDictionary* BattleInfo::getMapDict() {
    return _mapDict;
}

CCDictionary* BattleInfo::getMapDataDict() {
    return _mapDataDict;
}

CCDictionary* BattleInfo::getAttackTeamDict() {
    return _attackTeamDict;
}




