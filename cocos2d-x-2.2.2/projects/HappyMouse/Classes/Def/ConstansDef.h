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

#define GAME_INTERVAL  1.0f/60.f

#define Energy_Max            100.0f    //总能量
#define Energy_Unit           10.0f     //一颗星星的步长
#define Energy_Decrease_Unit  2.0f

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

/**
 游戏对象类型
 */
enum EGameObjectTypeId {
    
    K_TYPE_UNKNOWN                  = 0,
    K_TYPE_MONSTER                  = 1,//怪（军符中的兵）
    K_TYPE_CARD                     = 2,//卡片（即塔，或者是将领）
    K_TYPE_ROLE_CARD                = 3,//ROLE卡片（终点塔）
    K_TYPE_COMPONENT                = 5,//组件（武器,能量核心之类的）
    K_TYPE_OTHER                    = 6,//其它
    K_TYPE_PROP                     = 7,//道具（碎片，掉落物等）
    
    K_TYPE_OTHER_BULLET             = 600,//子弹
    K_TYPE_OTHER_TOWER_BULLET       = 620,//子弹
    K_TYPE_OTHER_DROP               = 610,//掉落
    
};

/**
 字体样式Id
 **/
enum EFontType {
    K_FONT_LABEL_TTF = 1,   //普通CCLabelTTF
    K_FONT_LABEL_BM,        //CCLabelBMFont
    K_FONT_LABEL_TTF_STROKE,    //描边字体
};

enum EUIAudioEffectId {
    
    K_AudioEffect_BackGroundMusic       = 950001,//	背景音乐
    K_AudioEffect_click                 = 950002,//	点击音效
    K_AudioEffect_eat                   = 950003,//	吃掉音效
    K_AudioEffect_GameOver              = 950004,//	游戏结束
    
};

//状态机状态设置

enum MouseState {
    
    MouseNormal,
    MouseArise,
    MouseDealy,
    MouseDrop,
    MouseStriken,
    MouseDead,
    
};

#define KSTATE_MOVING_ACTION_TAG (80001)
#define KSTATE_ANIMATION_ACTION_TAG (80002)
#define KSTATE_MOVE_TO_ACTION_TAG (80003)

#endif
