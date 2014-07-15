//
//  AppLauncher.cpp
//  iLostCity
//
//  Created by huang.haiyang on 13-4-18.
//  Copyright (c) 2013年 __MyCompanyName__. All rights reserved.
//

#include "AppLauncher.h"
#include <boost/ref.hpp>
#include "ConstansDef.h"
#include "cocos2d.h"
#include "SceneController.h"

USING_NS_CC;

AppLauncher::AppLauncher(const boost::function<void ()> &finishCallback) {
    CCLOG("AppLauncher::AppLauncher()");
}

AppLauncher::~AppLauncher() {
    CCLOG("AppLauncher::~AppLauncher()");
}

#pragma mark -entrance
/**
 * 入口
 */
void AppLauncher::startup() {    
    displayWelcomeView();
}

/**
 * 显示欢迎页
 */
void AppLauncher::displayWelcomeView() {
    SceneController::sharedInstance()->switchSence(K_SCENE_GAMEVIEW);
}

