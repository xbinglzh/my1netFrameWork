//
//  AppLauncher.h
//  iLostCity
//
//  Created by huang.haiyang on 13-4-18.
//  Copyright (c) 2013年 __MyCompanyName__. All rights reserved.
//

#ifndef iLostCity_AppLauncher_h
#define iLostCity_AppLauncher_h

#include <boost/function.hpp>

struct GameServerDescriptor;

/**
 * AppLauncher
 * 托管整个游戏启动过程，包括检查版本更新、资源更新、登陆、加载游戏资源
 * 为了让加载过程保持清晰，把检查更新和加载资源这类的相对独立的工作划分
 * 成tasks.
 */
class AppLauncher {
public:
    AppLauncher(const boost::function<void ()> &finishCallback);
    virtual ~AppLauncher();
    void startup();
    
private:
    void displayWelcomeView();
    
 
private:
    const boost::function<void ()> finishedCallback_;

};

#endif
