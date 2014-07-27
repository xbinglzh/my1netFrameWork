//
//  CharactarHandler.cpp
//  HappyMouse
//
//  Created by xUanBing on 14-7-26.
//
//

#include "CharactarHandler.h"
#include "DistanceItem.h"
#include "AudioManager.h"
#include "ConstansDef.h"

const std::set<int> CharactarHandler::getActiveCharactarStates(const int type) {
    
}


bool CharactarHandler::doAddHP(GameObject * target, const int hpAdd) {
    
}

void CharactarHandler::doHurt(GameObject * source, GameObject * target,
                              const GameSkillHurtInfo &hurtInfo) {
    
    if (target->getHp() > 0) {
        
        int32_t hurtVal = hurtInfo._hurt;
        target->setHP(((target->getHp() > hurtVal) ? target->getHp() - hurtVal : 0));
        
    }
    
    target->addAdditionState(K_STATE_BE_INJURED);
    
//判定死亡
//    if(target->getHP() <= 0){
//        CCBool * intercept = CCBool::create(false);
//        dict->setObject(intercept, KKeyKillIntercept);
//        nc->postNotification(KNotifyGameCharactarKillToDie,
//                             GameSkillAction::SkillMsg::create(KNotifyGameCharactarKillToDie, dict));
//        if (!intercept->getValue()) {
//            doKill(source,target);
//        }
//        
//    }else{
//        nc->postNotification(KNotifyGameCharactarHPReduced,
//                             GameSkillAction::SkillMsg::create(KNotifyGameCharactarHPReduced, dict));
//    }
    
    AudioManager::sharedInstance()->playAudioById(K_AudioEffect_click, false);
    
}

void CharactarHandler::doHurt(GameObject * target,
                              const GameSkillHurtInfo &hurtInfo) {
    doHurt(NULL, target, hurtInfo);
}

cocos2d::CCSet* CharactarHandler::findGameObjectInAtkRange(GameObject * self, cocos2d::CCSet *targetSet,
                                                             const float rangeScale) {
    
}

cocos2d::CCSet* CharactarHandler::findGameObjectInRange(GameObject * self, cocos2d::CCSet *targetSet,
                                        const float range, const bool sort) {
    
}

cocos2d::CCSet* CharactarHandler::findGameObjectInRange(const cocos2d::CCPoint & p,
                                        cocos2d::CCSet *targetSet,
                                        const float range,
                                        const bool sort) {
    
    
}

void CharactarHandler::doKill(GameObject * source,GameObject * target) {
    
}

void CharactarHandler::doReset(GameObject * source) {
    
}

void CharactarHandler::doXPSkillToSelect(const int32_t skillId,const bool selected) {
    
}

void CharactarHandler::doXPSkillStep(const int32_t skillId, cocos2d::CCCallFuncO * call, const int32_t effectType) {
    
}

void CharactarHandler::doXPSkill(GameObject * target, const int32_t skillId,
               cocos2d::CCDictionary * paramDict) {
    
}

bool CharactarHandler::doSkill(GameObject * source, const int32_t skillType,
                               cocos2d::CCObject * params) {
    
}

void CharactarHandler::doSKillEnergyEffect(GameObject * source, int pts, bool isLost) {
    
}

void CharactarHandler::doCollectResource(GameObject *source, int resoucePts) {
    
}

GameObject* CharactarHandler::getRandomGameObjectInBattleWithCard() {
    
}

GameObject* CharactarHandler::getRandomGameObjectInBattle() {
    
}

void  CharactarHandler::doHPReduceEffect(GameObject * source,
                              const int32_t hurtValue,
                                         const int32_t hitEffect) {
    
}

void  CharactarHandler::doHPAddEffect(GameObject * source, const int32_t hpValue,
                                      const int32_t hitEffect) {
    
}

void  CharactarHandler::doHPEffect(GameObject * source, const int32_t hpValue,
                        const bool reduce, const int32_t hitEffect) {
    
}

TargetsObject* CharactarHandler::createTargetsObject(cocos2d::CCSet * contactsObject,GameObject * item) {
    
}

void CharactarHandler::doCollectResourceEffect(GameObject *source, int resourcePts) {
    
}

