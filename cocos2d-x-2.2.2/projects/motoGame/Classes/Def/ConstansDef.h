//
//  ConstansDef.h
//  motoGame
//
//  Created by xUanBing on 14-3-24.
//
//

#ifndef motoGame_ConstansDef_h
#define motoGame_ConstansDef_h

#define PTM_RATIO 32.0f
#define BASE_TAG  1000

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
    K_SCENE_GAMEVIEW                = 201,//游戏场景
    K_SCENE_UIHOME                  = 104,// 开始
    K_SCENE_BATTLEVIEW              = 105,
};

enum BodyTag {
    K_BodyTag_Default     = 0,
    K_BodyTag_Hero        = 1,
    K_BodyTag_Tree        = 2,
};

#endif
