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



#endif
