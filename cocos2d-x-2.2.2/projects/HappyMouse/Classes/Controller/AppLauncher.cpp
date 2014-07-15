//
//  AppLauncher.cpp
//  iLostCity
//
//  Created by huang.haiyang on 13-4-18.
//  Copyright (c) 2013年 __MyCompanyName__. All rights reserved.
//

#include "AppLauncher.h"
#include <boost/ref.hpp>
#include <boost/bind.hpp>
#include "ConstansDef.h"
#include "cocos2d.h"
#include "SceneController.h"
#include "ResourceLoader.h"

USING_NS_CC;

AppLauncher::AppLauncher(const boost::function<void ()> &finishCallback) : _isResourceReady(false) {
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
    startLoadResources();
    displayWelcomeView();
}

/**
 * 显示欢迎页
 */
void AppLauncher::displayWelcomeView() {
    SceneController::sharedInstance()->switchSence(K_SCENE_GAMEVIEW);
}

void AppLauncher::startLoadResources() {
    
    if (_isResourceReady) {
        return;
    }
    
    CCDictionary* resourceDict = CCDictionary::createWithContentsOfFile("x_startup.plist");
    ResourceLoader::loadNow(resourceDict, boost::bind(&AppLauncher::didFinishedLoadResources, this));
}

void AppLauncher::didFinishedLoadResources() {
    _isResourceReady = true;
}

