//
//  ConstansDef.h
//  motoGame
//
//  Created by xUanBing on 14-3-24.
//
//

#ifndef motoGame_ConstansDef_h
#define motoGame_ConstansDef_h

enum EUserState {
    K_User_State_Disable = -1,  //停用
    K_User_State_Normal = 0,    //正常
    K_User_State_Quick  = 1,    //快速注册
};

/**
 场景ID
 */
enum ESceneId {
    K_SCENE_UNKNOW                  = 0,
    K_SCENE_WELCOME                 = 101,//欢迎
    K_SCENE_LOGIN                   = 102,//登录
    K_SCENE_ROLLVIEW                = 103,//测试
};

#endif
