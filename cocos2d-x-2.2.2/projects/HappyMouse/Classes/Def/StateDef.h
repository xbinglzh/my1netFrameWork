//
//  StateDef.h
//  HappyMouse
//
//  Created by xUanBing on 14-7-19.
//
//

#ifndef HappyMouse_StateDef_h
#define HappyMouse_StateDef_h

/**
 游戏对象的运行状态
 */
enum EGameObjectStateId {
    
    K_STATE_DISPLAY                 = 0, //显示
    K_STATE_DISACTIVE               = 1, //死亡
    K_STATE_IDLE                    = 2, //闲置
    K_STATE_MOVING                  = 3, //移动中
    
    K_STATE_ATTACKING               = 4, //攻击CT中
    K_STATE_PREPARESKILL            = 41, //攻击准备中
    K_STATE_DO_SKILL                = 42, //攻击执行中
    K_STATE_DIE_SKILL               = 43, //死亡技能执行中
    K_STATE_BE_INJURED              = 5, //受伤中
    K_STATE_TO_DISACTIVE            = 6, //死亡中
    K_STATE_ARRIVED                 = 7, //到达目的
    K_STATE_AUTODISAPPEAR           = 8, //到达目的
    K_STATE_RELIVE                  = 9, //再生状态
    
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
