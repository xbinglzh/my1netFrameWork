//
//  RootUiLayer.cpp
//  iLostCity
//
//  Created by Ryan_Y on 13-4-22.
//
//

#include "RootUiLayer.h"
#include "ConstansDef.h"
#include "SPArmatureDataManager.h"
#include "UiUtils.h"

RootUiLayer::RootUiLayer() :
_isInit(false)
,_isScaleRootView(false)
,_nodeShowAll(NULL)
,_nodeExactFit(NULL)
,_contentScaleY(1.0f)
,_contentScaleX(1.0f){
    
}

RootUiLayer::~RootUiLayer() {

    CC_SAFE_RELEASE_NULL(_nodeShowAll);
    CC_SAFE_RELEASE_NULL(_nodeExactFit);
    removeAllChildrenWithCleanup(true);
    
    CCSpriteFrameCache * sharedSpriteFrameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
    for (std::set<std::string>::iterator iter = _singleSpriteFrame.begin();
         iter != _singleSpriteFrame.end(); iter++) {
        std::string fileName = (*iter);
        CCSpriteFrame* sf = sharedSpriteFrameCache->spriteFrameByName(fileName.c_str());
        CC_SAFE_RELEASE_NULL(sf);
    }
    _singleSpriteFrame.clear();
    
    releaseUiSprite();
    sp::ArmatureDataManager::sharedArmatureDataManager()->removeUnusedAnimations();
    CCTextureCache::sharedTextureCache()->dumpCachedTextureInfo();
}

void RootUiLayer::releaseUiSprite(){
    CCSpriteFrameCache * sharedSpriteFrameCache=CCSpriteFrameCache::sharedSpriteFrameCache();
    
    if(!_loadedSpriteSheet.empty()) {
        for (std::set<std::string>::iterator iter = _loadedSpriteSheet.begin();
             iter != _loadedSpriteSheet.end(); iter++) {
            std::string plist = (*iter);
            sharedSpriteFrameCache->removeSpriteFramesFromFile(plist.c_str());
        }
    }
    
    _loadedSpriteSheet.clear();
}

CCNode * RootUiLayer::loadClassFromCCBI(const char * pClassName,
                                   const char * pCCBIFileName,
                                   CCNodeLoader * pCCNodeLoader, ...) {
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    ccNodeLoaderLibrary->registerCCNodeLoader(pClassName, pCCNodeLoader);
    
    va_list loaders;
    va_start(loaders, pCCNodeLoader);
    const char *className = NULL;
    int count(0);
    while ((className = va_arg(loaders, const char *))) {
        count++;
        // 类名超过0~50个字符或者loader个数 < 10，可以防止调用函数的时候最后一个参数不传NULL
        assert(count < 10 && strlen(className) > 0 && strlen(className) < 50);
        ccNodeLoaderLibrary->registerCCNodeLoader(className,
                                                  va_arg(loaders, CCNodeLoader *));
    }
    va_end(loaders);
    
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    RootUiLayer * node = (RootUiLayer *)ccbReader->readNodeGraphFromFile(pCCBIFileName);
    if(!ccbReader->getLoadedSpriteSheet().empty()){
        node->_loadedSpriteSheet = ccbReader->getLoadedSpriteSheet();
    } 

    ccbReader->release();
    return node;
}

bool RootUiLayer::init(){
    if(CCLayer::init()){
        //todo
        CCSize screenSize = CCEGLView::sharedOpenGLView()->getFrameSize();  //屏幕大小
        const CCRect& rect = CCEGLView::sharedOpenGLView()->getViewPortRect();  //view大小
        _contentScaleX = screenSize.width/rect.size.width;
        _contentScaleY = screenSize.height/rect.size.height;
        return true;
    }
    return false;
}
void RootUiLayer::scaleBaseView() {
    
    UiUtils::scaleNodeToShowAll(_nodeShowAll);
    UiUtils::scaleNodeToExactFit(_nodeExactFit);
    
    if(_isScaleRootView) {
        UiUtils::scaleNodeToExactFit(this);
    }
}

bool RootUiLayer::initWithCustom() {
    //todo
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    scaleBaseView();
#endif
    return true;
}

void RootUiLayer::onEnter(){
    CCLayer::onEnter();
    if (!_isInit) {
        _isInit = initWithCustom();
    }
}

bool RootUiLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    return false;
}

void RootUiLayer::registerSingleSpriteFrame(const std::string & filename){
    _singleSpriteFrame.insert(filename);
    CCSpriteFrameCache * sharedSpriteFrameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
    CCSpriteFrame* spriteFrame = sharedSpriteFrameCache->spriteFrameByName(filename.c_str());
    CCAssert(spriteFrame != NULL, "RootUiLayer::registerSingleSpriteFrame");
    spriteFrame->retain();
}

void RootUiLayer::showToast(const char *text) {
//    XXUiToast::showToast(text);
}


RootUiLayerWithNetwork::RootUiLayerWithNetwork()
:RootUiLayer()
,_networkRequestId(-1)
,_networkWaitDlg(NULL) {

}

RootUiLayerWithNetwork::~RootUiLayerWithNetwork(){
    CCNotificationCenter * nc = CCNotificationCenter::sharedNotificationCenter();
    nc->removeAllObservers(this);
    dismissNetworkRequest();
}

void RootUiLayerWithNetwork::registerConnectionStatusObserver() {
    CCNotificationCenter * nc = CCNotificationCenter::sharedNotificationCenter();
//    nc->addObserver(this, callfuncO_selector(RootUiLayerWithNetwork::onConnectionStatusChanged),
//                                          KNotifyConnectionStatusChanged, NULL);
}

void RootUiLayerWithNetwork::unregisterConnectionStatusObserver() {
//    CCNotificationCenter * nc = CCNotificationCenter::sharedNotificationCenter();
//    nc->removeObserver(this, KNotifyConnectionStatusChanged);
}


void RootUiLayerWithNetwork::showWaitDlg() {
    if (!_networkWaitDlg) {
//        _networkWaitDlg = XXUiWaitingView::create();
//        _networkWaitDlg->run();
    }
}

void RootUiLayerWithNetwork::closeWaitDlg() {
    if(_networkWaitDlg) {
//        _networkWaitDlg->stop();
//        _networkWaitDlg = NULL;
    }
}


void RootUiLayerWithNetwork::dismissNetworkRequest() {
    if (_networkRequestId != -1) {
//        Online::instance().dismissCallWithToken(_networkRequestId);
//        _networkRequestId = -1;
    }
}



void RootUiLayerWithNetwork::showErrorDialog(const int error) {
    closeWaitDlg();
    if (error != 0) {
//        std::stringstream id;
//        id << error;
//        const CCString *str = GameConfig::sharedInstance()->getErrorById(id.str());
//        if(str) {
//            showToast(str->m_sString.c_str());
//        } else {
//            const std::string fromat = N2UiLocalizedString(RootUiLayerWithNetwork_unknow_error,
//                                                           "unkown error:%d");
//            showToast(CCString::createWithFormat(fromat.c_str(), error)->m_sString.c_str());
//        }
    }
}

void RootUiLayerWithNetwork::onConnectionStatusChanged(CCObject* param) {
    CCDictionary *params = (CCDictionary *)param;
//    int status = ((CCInteger *)params->objectForKey("msg"))->getValue();
//    if (status == K_CONNECTION_STATUS_KICK_OFF ||
//        status == K_CONNECTION_STATUS_RETRY_FAILED) {
//        closeWaitDlg();
//        dismissNetworkRequest();
//    }
}

void RootUiLayerWithNetwork::onMessageBoxClickedButton(int32_t type) {
//    if(type == XXUiMessageBox::EMessageBoxBtnOk) {
//
//    }
}