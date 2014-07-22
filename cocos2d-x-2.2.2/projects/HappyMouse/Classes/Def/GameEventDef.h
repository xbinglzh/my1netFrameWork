//
//  GameEventDef.h
//  HappyMouse
//
//  Created by xUanBing on 14-7-22.
//
//

#ifndef HappyMouse_GameEventDef_h
#define HappyMouse_GameEventDef_h

enum EGameStateEvent {
    
    K_EVENT_ANIMATION_FINISHED          = 0,
    K_EVENT_ANIMATION_FRAME_CHANGED,
    
    K_EVENT_ENTER_ATK_RANGE,                                     //进入攻击范围
    K_EVENT_OUT_ATK_RANGE,                                       //出攻击范围
    
    K_EVENT_ON_GAMEOBJECT_TO_DISACTIVE,                          // GameObject未激活
    K_EVENT_ON_ARRIVED_TARGET,                                   // 到达目标
    K_EVENT_ON_GAME_PAUSE,
    K_EVENT_ON_MOVE_SPEED_UPDATED,
    K_EVENT_ON_TROOPS_CLEAN,
    K_EVENT_ON_MOVE_TO_TARGET_FINISHED,
    K_EVENT_ON_SWITCH_TO_NEXT_ANIM,
    
};

/**
 state ids
 */
enum EStateRealId {
	KDisactiveState                 = 10001,
    KDisactiveStateTroop            = 10003,
    KDisactiveStateBullet           = 10004,
    KDisactiveStateTower            = 10005,
    
    KDisplayState                   = 11000,
    
    KIdleState                      = 20000,
    KIdleStateBase                  = 20001,
    KIdleStateTower                 = 20002,
    KIdleStateDrop                  = 20003,
    
    KMovingState                    = 30000,
    KMovingStateBullet              = 30001,
    KMovingStateDrop                = 30002,
    KMovingBezierStateBullet        = 30004,
    KMovingStateBulletStormSkill    = 30005,
    KMovingStateBulletStormRange    = 30006,
    
    KAttackingState                 = 40000,
    KAttackingStateTower            = 40001,
    KAttackingStateBullet           = 40002,
    KAttackingStateSkillBullet      = 40003,
    KPrepareSkillState              = 41001,
    KDoSkillState                   = 42001,
    KDoSkillStateTower              = 42002,
    KDieSkillState                  = 43001,
    KDieSkillTroopArrivedState      = 43002,
    
    KBeInjuredState                 = 50000,
    
    KToDisactiveState               = 60000,
    KToDisactiveStateBullet         = 60001,
    KToDisactiveStateSkillChip      = 60002,
    KToDisactiveStateBulletSingleSkill   = 60003,
    KToDisactiveStateBulletRangeSkill    = 60004,
    KToDisactiveStateLightningBullet     = 60005,
    KToDisactiveStateBulletStorm         = 60006,
    
    KArrivedState                   = 70000,
    KArrivedStateTroop              = 70001,
    KAutoDisappearState             = 80000,
};


#endif
