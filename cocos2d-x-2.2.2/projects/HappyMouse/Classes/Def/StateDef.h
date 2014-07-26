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
 state ids
 */
enum EStateRealId {
    
	KDisactiveState                 = 10000,  //死亡状态
    
    KToDisactiveState               = 20000,  //将要死亡状态
    
    KDisplayState                   = 30000,  //显示状态
    
    KIdleState                      = 40000,  //闲置状态
    
    KMovingUpState                  = 50000,  //上移动状态
    
    KMovingDownState                = 60000,  //下移动状态
    
    KAttackingState                 = 70000,  //攻击状态
    
    KBeInjuredState                 = 80000,  //受伤状态
    
    KArrivedState                   = 90000,  //达到状态

};

/**
 游戏对象的运行状态
 */
enum EGameObjectStateId {
    
    K_STATE_DISACTIVE               = KDisactiveState / 10000,   //死亡
    
    K_STATE_TO_DISACTIVE            = KToDisactiveState / 10000, //死亡中
    
    K_STATE_DISPLAY                 = KDisplayState / 10000,     //显示
    
    K_STATE_IDLE                    = KIdleState / 10000,        //闲置
    
    K_STATE_MOVING_UP               = KMovingUpState / 10000,    //移动 - 上
    
    K_STATE_MOVING_DOWN             = KMovingDownState / 10000,  //移动 - 下
    
    K_STATE_ATTACKING               = KAttackingState / 10000,   //攻击CT中
    
        /* Attack */
           K_STATE_PREPARESKILL     = 41,                        //攻击准备中
           K_STATE_DO_SKILL         = 42,                        //攻击执行中
           K_STATE_DIE_SKILL        = 43,                        //死亡技能执行中
        /* Attack */
    
    K_STATE_BE_INJURED              = KBeInjuredState / 10000,   //受伤中

    K_STATE_ARRIVED                 = KArrivedState / 10000,     //到达目的
    
    
    
    
    K_STATE_AUTODISAPPEAR           = 8, //到达目的
    K_STATE_RELIVE                  = 9, //再生状态
    
};




#endif
