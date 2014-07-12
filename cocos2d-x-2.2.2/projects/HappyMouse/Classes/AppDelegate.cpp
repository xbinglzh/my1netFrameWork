#include "AppDelegate.h"
#include <boost/bind.hpp>
#include "AppLauncher.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
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
    
    ccfilePath.push_back("hm_anim");
    ccfilePath.push_back("hm_layout");
    ccfilePath.push_back("ui_layout/resources-iphonehd");
    ccfilePath.push_back("ui_layout/resources-normal");
    ccfilePath.push_back("ui_layout/resources-release");
    ccfilePath.push_back("hm_map");
    ccfilePath.push_back("hm_map/pit");
    ccfilePath.push_back("hm_particle");
    
    CCFileUtils::sharedFileUtils()->setSearchPaths(ccfilePath);
    
    // 启动游戏
    _launcher.reset(new AppLauncher(boost::bind(&AppDelegate::didFinishedLauchApp, this)));
	_launcher->startup();
    
    pDirector->setDisplayStats(true);
    
    return true;

}

void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();
}

void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();
}

void AppDelegate::didFinishedLauchApp() {
    _launcher.reset();
}
