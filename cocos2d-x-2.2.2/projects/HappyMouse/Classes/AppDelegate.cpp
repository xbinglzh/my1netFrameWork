#include "AppDelegate.h"

#include "SceneController.h"
#include "SPDataReaderHelper.h"
#include "SPArmatureDataManager.h"
#include "NotifyMessageDef.h"
#include <boost/bind.hpp>
#include "AppLauncher.h"
#include "ConstansDef.h"
#include "AudioManager.h"
#include "KeyConfigDef.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() {
    
    sp::ArmatureDataManager::sharedArmatureDataManager()->removeAll();
    AudioManager::sharedInstance()->purgeInstance();
}

bool AppDelegate::applicationDidFinishLaunching() {
    
    CCDirector *pDirector = CCDirector::sharedDirector();
    CCEGLView *glView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(glView);
    pDirector->setProjection(kCCDirectorProjection2D);
    pDirector->setAnimationInterval(GAME_INTERVAL);
    
    // 计算最接近的屏幕尺寸的设计分辨率
//    const CCSize &screenSize = glView->getFrameSize();
//    const float screenRatio = screenSize.width / screenSize.height;
//    const float offset_960_640 = fabsf(screenRatio - (960.0f / 640.0f));
//    const float offset_1066_640 = fabsf(screenRatio - (1066.0f / 640.0f));
//    const float offset_1138_640 = fabsf(screenRatio - (1138.0f / 640.0f));
//    const float miniOffset = fminf(offset_1138_640, fminf(offset_960_640, offset_1066_640));
    
    // 设置资源加载路径
    std::vector<std::string> ccfilePath;
    
    ccfilePath.push_back("audio");
    ccfilePath.push_back("anim");
    ccfilePath.push_back("map");
    ccfilePath.push_back("map/pit");
    ccfilePath.push_back("map/mouse");
    ccfilePath.push_back("particle");
    ccfilePath.push_back("ui_layout");
    ccfilePath.push_back("ui_layout/resources-iphonehd");
    ccfilePath.push_back("ui_layout/resources-normal");
    ccfilePath.push_back("plist");
    ccfilePath.push_back("fonts");
    
    CCFileUtils::sharedFileUtils()->setSearchPaths(ccfilePath);
    
    glView->setDesignResolutionSize(1138, 640, kResolutionFixedWidth);
//    pDirector->setContentScaleFactorFromSize();
    
    // 启动游戏
    _launcher.reset(new AppLauncher(boost::bind(&AppDelegate::didFinishedLauchApp, this)));
	_launcher->startup();
    
    pDirector->setDisplayStats(true);
    
    return true;
}

void AppDelegate::applicationDidEnterBackground() {
    
    CCDirector::sharedDirector()->stopAnimation();
    cocos2d::CCNotificationCenter::sharedNotificationCenter()->postNotification(KNotifyApplicationDidEnterBackgroundMessage, NULL);
    
    AudioManager::sharedInstance()->pause();
}

void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();
    cocos2d::CCNotificationCenter::sharedNotificationCenter()->postNotification(KNotifyApplicationWillEnterForegroundMessage, NULL);
    
    AudioManager::sharedInstance()->resume();
    initAudioManager();
}

void AppDelegate::applicationDidBecomeActive() {
	cocos2d::CCDirector::sharedDirector()->resume();
 	cocos2d::CCNotificationCenter::sharedNotificationCenter()->postNotification(KNotifyApplicationResumeMessage);
    
    AudioManager::sharedInstance()->resume();
    initAudioManager();
}

void AppDelegate::didFinishedLauchApp() {
    _launcher.reset();
}

void AppDelegate::initAudioManager() {
    AudioManager * audioManager = AudioManager::sharedInstance();
    CCUserDefault * gUserDefault = CCUserDefault::sharedUserDefault();
    const bool audioEffectStatusClosed = gUserDefault->getBoolForKey(KStrAudioEffectStatusClosed);
    const bool bgMusicStatusClosed = gUserDefault->getBoolForKey(KStrBgMusicStatusClosed);
    if (!bgMusicStatusClosed) {
        audioManager->openBackgroundMusic();
    } else {
        audioManager->closedBackgroundMusic();
    }
    if (!audioEffectStatusClosed) {
        audioManager->openEffectMusic();
    } else{
        audioManager->closedEffectMusic();
    }
}

