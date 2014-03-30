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
    K_SCENE_SELECT_PHOTO            = 103,//头像选择
    K_SCENE_BASE                    = 104,//基地
    K_SCENE_TEAM                    = 105,//组队
    K_SCENE_SELECT_LEVEL            = 107,//选择关卡
    K_SCENE_BATTLE                  = 108,//战斗场景
    K_SCENE_HOME                    = 109,//主界面
    K_SCENE_ENERGY                  = 110,//能量
    K_SCENE_PHOTO                   = 111,//图鉴
    K_SCENE_TASK                    = 112,//任务
    K_SCENE_ACTIVITY                = 113,//活动
    K_SCENE_DUPLICATE               = 114,//副本
    K_SCENE_SOCIAL                  = 116,//社交
    K_SCENE_BATTLE_SETTING          = 117,//防御工事
    K_SCENE_WAREHOUSE               = 118,//仓库
    K_SCENE_ACHIEVEMENT             = 119,//成就
    K_SCENE_ARENA                   = 120,//竞技场
    K_SCENE_RANK                    = 121,//排行榜
    K_SCENE_TOWN_LIST               = 122,//城镇列表
    K_SCENE_ABOUT                   = 123,//关于
    K_SCENE_TEAM_INFO               = 124,//团队
    K_SCENE_HELP                    = 125,//帮助
    K_SCENE_SETTING                 = 126,//设置
    K_SCENE_ACHIEVEMENT_SCORE       = 127,//成就积分礼物
    K_SCENE_CHANGE_PASSWORD         = 128,//修改密码
    K_USER_SETTING                  = 129,//个人设置
    K_SCENE_STORY                   = 130,//故事剧情
    K_SCENE_ASSISTANT               = 131,//小助手
    K_SCENE_PUMPING_CARD            = 132, //抽卡
    K_SCENE_ASSEMBLE_MAP            = 133,//阵法
    K_SCENE_COMBAT_PREPARE          = 134,//战斗前准备
    K_SCENE_PLUNDER                 = 135,//掠夺
    K_SCENE_JXP                     = 136,//将星盘
    K_SCENE_ROLL_QIAN_SHU           = 1000,//摇钱树
};

#endif
