//
//  BattleLayer.cpp
//  HappyMouse
//
//  Created by xUanBing on 14-7-23.
//
//

#include "BattleLayer.h"
#include "SPArmatureDataManager.h"

BattleLayer::BattleLayer() :
_gameController(NULL),
_gameModel(NULL),
_groundMap(NULL),
_topLayer(NULL),
_xpEffectLayer(NULL) {
    
}

BattleLayer::~BattleLayer() {
    removeAllChildrenWithCleanup(true);
    sp::ArmatureDataManager::sharedArmatureDataManager()->removeUnusedAnimations();
}

bool BattleLayer::init() {
    _gameController = GameController::getInstance();
    _gameModel = GameModel::getInstance();
    return true;
}
