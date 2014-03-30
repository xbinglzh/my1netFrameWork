
#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "HelloView.h"
#include "SceneController.h"
#include "SPDataReaderHelper.h"
#include "SPArmatureDataManager.h"
#include "NotifyMessageDef.h"
#include <boost/bind.hpp>
#include "AppLauncher.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() {
     sp::ArmatureDataManager::sharedArmatureDataManager()->removeAll();
}

bool AppDelegate::applicationDidFinishLaunching() {

    CCDirector *pDirector = CCDirector::sharedDirector();
    CCEGLView *glView = CCEGLView::sharedOpenGLView();
    
    pDirector->setOpenGLView(glView);
    pDirector->setProjection(kCCDirectorProjection2D);
    pDirector->setAnimationInterval(1.0 / 60);
    
    // 计算最接近的屏幕尺寸的设计分辨率
    const CCSize &screenSize = glView->getFrameSize();
    const float screenRatio = screenSize.width / screenSize.height;
    const float offset_960_640 = fabsf(screenRatio - (960.0f / 640.0f));
    const float offset_1066_640 = fabsf(screenRatio - (1066.0f / 640.0f));
    const float offset_1138_640 = fabsf(screenRatio - (1138.0f / 640.0f));
    const float miniOffset = fminf(offset_1138_640, fminf(offset_960_640, offset_1066_640));
    
    // 设置资源加载路径
    std::vector<std::string> ccfilePath;

//    if (miniOffset == offset_960_640) {
//
//    } else if (miniOffset == offset_1066_640) {
//
//    } else {
//
//    }

    ccfilePath.push_back("anim");
    ccfilePath.push_back("xx_battle_ui");
    ccfilePath.push_back("ui_layout");
    ccfilePath.push_back("ui_layout/resources-iphonehd");
    
    // 启动游戏
    _launcher.reset(new AppLauncher(boost::bind(&AppDelegate::didFinishedLauchApp, this)));
	_launcher->startup();
    
//    CCFileUtils::sharedFileUtils()->setSearchPaths(ccfilePath);
//    CCScene *pScene = UiLoadingView::scene();
//
//    pDirector->runWithScene(pScene);

    return true;
}

void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();
    
    cocos2d::CCNotificationCenter::sharedNotificationCenter()->postNotification(KNotifyApplicationDidEnterBackgroundMessage, NULL);
}

void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
    cocos2d::CCNotificationCenter::sharedNotificationCenter()->postNotification(KNotifyApplicationWillEnterForegroundMessage, NULL);
}


void AppDelegate::applicationDidBecomeActive()
{
	cocos2d::CCDirector::sharedDirector()->resume();
 	cocos2d::CCNotificationCenter::sharedNotificationCenter()->postNotification(KNotifyApplicationResumeMessage);
}

void AppDelegate::didFinishedLauchApp() {
    CCLOG("launch finshed.");
    _launcher.reset();

}
