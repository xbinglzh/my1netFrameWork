//
//  ToDisactiveState.cpp
//  HappyMouse
//
//  Created by xUanBing on 14-7-26.
//
//

#include "ToDisactiveState.h"
#include "StateDef.h"
#include "GameEventDef.h"
#include "KeyConfigDef.h"
#include "GameObject.h"

void ToDisactiveState::onEnterCallback(GameObject * obj){
    runStateAnimWithCallback(obj, K_STATE_TO_DISACTIVE, KKeyDestoryDuration);
    
//    CCNotificationCenter * nc = CCNotificationCenter::sharedNotificationCenter();
    
//    nc->postNotification(KNotifyGameObjectToDiactiveMessage, obj);
//	//播放动画
//    GameObjectExt::createCommonDeadAnim(obj);
    
//
//    CCString * destoryEffect = (CCString *)obj->getValue(KKeyDestoryEffect);
//    if(!destoryEffect){
//        destoryEffect = (CCString *)GameConfig::sharedInstance()->getTemplateSubValue(obj->getId(), KKeyDestoryEffect);
//    }
//    
//    EffectManager * gEffectManager = EffectManager::sharedInstance();
//    
//    //拆塔消失isDisappearByDead = false
//    CCBool* isDisappearByDead = (CCBool *)obj->getValue(KKeyIsDisappearByDead);
//    if(isDisappearByDead && !isDisappearByDead->getValue()) {
//        //        obj->setValue(KKeyIsDisappearByDead, CCBool::create(true));//重置,默认是死亡方式消失
//        gEffectManager->playAudioEffectById(K_AudioEffect_RemoveTower);
//    } else {
//        std::vector<int32_t>  effects = GameUtils::string2IntArray(destoryEffect->m_sString,"#");
//        const int32_t effectsSize = effects.size();
//        if (effectsSize == 1) {
//            gEffectManager->playAudioEffectById(effects[0]);
//        }else if (effectsSize > 1){
//            gEffectManager->playAudioEffectById(effects[(rand() % effectsSize)]);
//        }
//    }
}

bool ToDisactiveState::onMessageCallback(GameObject * obj,const GameEventParams * params){
    if (params) {
        switch (params->getEvent()) {
            case K_EVENT_ANIMATION_FINISHED:
            {
                if(params->getData() == obj && K_STATE_DISACTIVE != obj->getCurrentState()){
                    gotoNextState(obj,K_STATE_DISACTIVE);
                    return true;
                }
            }
                break;
            default:
                break;
        }
    }
    return false;
}

void ToDisactiveState::gotoNextState(GameObject * obj,const int state)
{
    
    CCInteger * nextState = CCInteger::create(K_STATE_DISACTIVE);
//    CCNotificationCenter * nc = CCNotificationCenter::sharedNotificationCenter();
 
//    CCDictionary * dict = CCDictionary::create();
//    dict->setObject(nextState,KKeyCurrentState);
//    dict->setObject(obj,KKeyTarget);
//    
//    GameSkillAction::SkillMsg * msg = GameSkillAction::SkillMsg::create(KNotifyGameCharactarDying, dict);
//    nc->postNotification(KNotifyGameCharactarDying,msg);
//    if (nextState->getValue() == K_STATE_RELIVE) { //如果是复活状态的话处理
//        doReliveAnimation(obj);
//    } else {
//        //发出消息
//        //获得掉落材料
//        const int32_t finalDropMaterial = GameObjectExt::finalDropMaterialWithAddition(obj);
//        if (finalDropMaterial > 0) {
//            CCBool* isDisappearByDead = (CCBool *)obj->getValue(KKeyIsDisappearByDead);
//            if(isDisappearByDead && !isDisappearByDead->getValue()) {
//            } else {
//                CharactarHandler::doCollectResource(obj, finalDropMaterial);
//                nc->postNotification(KNotifyMaterialChangeRefresh);
//            }
//        }
//        
        obj->changeState(nextState->getValue());
//    }
}

void ToDisactiveState::doReliveAnimation(GameObject* obj){
//    obj->setPropertyValue(K_GameObjet_Relive, true);
//    PlayAnimationAction* play = PlayAnimationAction::create("912081#skill", obj->getPosition(), "happening",
//                                                            9999, false, 1.0f);
//    play->setIsRemoveAnim(true);
//    play->setFinishedCallfunc(CCCallFuncO::create(obj->getParent(),
//                                                  callfuncO_selector(ToDisactiveState::animReliveEndCallBack),
//                                                  obj));
//    obj->getParent()->runAction(play);
//    
//    PlayAnimationAction* playTop = PlayAnimationAction::create("912080#skill", obj->getPosition(), "happening",
//                                                               9999, false, 1.0f);
//    playTop->setIsRemoveAnim(true);
//    obj->getParent()->runAction(playTop);
}

void ToDisactiveState::animReliveEndCallBack(cocos2d::CCObject* pSender){
//    GameObject* source = (GameObject *)pSender;
//    if (source == NULL) {
//        return;
//    }
//    source->changeState(K_STATE_IDLE);
//    CCNotificationCenter * nc = CCNotificationCenter::sharedNotificationCenter();
//    GameSkillAction::SkillMsg * msg = GameSkillAction::SkillMsg::create(KNotifyGameCharactarRelive, source);
//    nc->postNotification(KNotifyGameCharactarRelive,msg);
//    source->setPropertyValue(K_GameObjet_Relive, false);
}