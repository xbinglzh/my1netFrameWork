//
//  CharactarHandler.h
//  HappyMouse
//
//  Created by xUanBing on 14-7-26.
//
//

#ifndef __HappyMouse__CharactarHandler__
#define __HappyMouse__CharactarHandler__

#include "cocos2d.h"
#include "GameObject.h"

class TargetsObject;

class CharactarHandler {
    
public:
    class GameSkillHurtInfo {
        
    public:
        GameSkillHurtInfo() :
        _type(0),
        _hurt(0),
        _skill(false){
            
        }
        
    public:
        uint8_t          _type;      //类型(伤害类型)
        int              _hurt;      //伤害
        bool             _skill;
    };
    
public:
    static const std::set<int> getActiveCharactarStates(const int type);
    
    static bool doAddHP(GameObject * target,
                        const int hpAdd);
    
    /**
     进行伤害处理
     */
    static void doHurt(GameObject * source,
                       GameObject * target,
                       const GameSkillHurtInfo &hurtInfo);
    
    static void doHurt(GameObject * target,
                       const GameSkillHurtInfo &hurtInfo);
    
    /**
     查找所有在自己攻击范围内的目标对象
     */
    static cocos2d::CCSet  * findGameObjectInAtkRange(GameObject * self,
                                                      cocos2d::CCSet *targetSet,
                                                      const float rangeScale = 1.0);
    
    static cocos2d::CCSet  * findGameObjectInRange(GameObject * self,
                                                   cocos2d::CCSet *targetSet,
                                                   const float range,
                                                   const bool sort);
    
    
    static cocos2d::CCSet  * findGameObjectInRange(const cocos2d::CCPoint & p,
                                                   cocos2d::CCSet *targetSet,
                                                   const float range,
                                                   const bool sort = false
                                                   );
    /**
     source killed target
     */
    static void doKill(GameObject * source,GameObject * target);
    
    /**
     对一个角色对象进行重置状态
     */
    static void doReset(GameObject * source);
    
    
    static void doXPSkillToSelect(const int32_t skillId,const bool selected);
    
    static void doXPSkillStep(const int32_t skillId,
                              cocos2d::CCCallFuncO * call,
                              const int32_t effectType);
    
    static void doXPSkill(GameObject * target,
                          const int32_t skillId,
                          cocos2d::CCDictionary * paramDict = NULL);
    
    static bool doSkill(GameObject * source,
                        const int32_t skillType,
                        cocos2d::CCObject * params = NULL);
    
    static void doSKillEnergyEffect(GameObject * source, int pts, bool isLost);
    
    static void doCollectResource(GameObject *source, int resoucePts);
    
    static GameObject* getRandomGameObjectInBattleWithCard();
    static GameObject* getRandomGameObjectInBattle();
    
    
private:
    /**
     执行一个扣血特效
     */
    static void  doHPReduceEffect(GameObject * source,
                                  const int32_t hurtValue,
                                  const int32_t hitEffect);
    
    static void  doHPAddEffect(GameObject * source,
                               const int32_t hpValue,
                               const int32_t hitEffect);
    
    static void  doHPEffect(GameObject * source,
                            const int32_t hpValue,
                            const bool reduce,
                            const int32_t hitEffect);
    
    static TargetsObject  * createTargetsObject(cocos2d::CCSet * contactsObject,GameObject * item);
    
    static void doCollectResourceEffect(GameObject *source, int resourcePts);
};


#endif /* defined(__HappyMouse__CharactarHandler__) */
