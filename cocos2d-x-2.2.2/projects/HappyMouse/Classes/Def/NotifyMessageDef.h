//
//  NotifyMessageDef.h
//  motoGame
//
//  Created by xUanBing on 14-3-24.
//
//

#ifndef __motoGame__NotifyMessageDef__
#define __motoGame__NotifyMessageDef__

#define KNotifyApplicationDidEnterBackgroundMessage "application_did_enter_background_msg"  //程序切换后台时发送
#define KNotifyApplicationWillEnterForegroundMessage "application_will_enter_foreground_msg"  //程序从后台切换到前台发送
#define KNotifyApplicationResumeMessage "application_resume_msg"                              //程序从后台切换到前台发送

#define KNotifyLevelUpMessage         "notifyLevelUpMessage"
#define KNotifyStartBattleMessage     "notifyStartBattleMessage"
#define KNotifyPauseBattleMessage     "notifyPauseBattleMessage"


#define KNotifyMakeHeroJumpMessage       "notifyMakeHeroJumpMessage"
#define KNotifyMakeHeroFallFloorMessage  "notifyMakeHeroFallFloorMessage"
#define KNotifyMakeHeroDieMessage        "notifyMakeHeroDieMessage"

#define KNotifyEnergyChangeMessage    "notifyEnergyChangeMessage"
#define KNotifyEnergyFullMessage      "notifyEnergyFullMessage"
#define KNotifyEnergyEmptyMessage     "notifyEnergyEmptyMessage"

#define KNotifyGameScoreChangeMessage "notifyGameScoreChangeMessage"

//---
#define KNotifyMousePop               "notifyMousePop"

#endif /* defined(__motoGame__NotifyMessageDef__) */
