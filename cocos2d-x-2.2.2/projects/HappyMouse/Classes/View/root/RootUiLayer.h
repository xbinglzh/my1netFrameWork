//
//  RootUiLayer.h
//  iLostCity
//
//  Created by Ryan_Y on 13-4-22.
//
//

#ifndef iLostCity_RootUiLayer_h
#define iLostCity_RootUiLayer_h

#include <map>

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

/**
 CCB编辑的界面对应的基类
 */

class  RootUiLayer : public CCLayer, 
public CCBSelectorResolver, 
public CCBMemberVariableAssigner
{
public:
	RootUiLayer();
	virtual ~RootUiLayer();
    static CCNode *loadClassFromCCBI(const char * pClassName,
                                     const char * pCCBIFileName,
                                     CCNodeLoader * pCCNodeLoader, ...);
	virtual bool init();
    virtual bool initWithCustom();
    inline  bool isInit() { return _isInit; }
    virtual void onEnter();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    void releaseUiSprite();
    void registerSingleSpriteFrame(const std::string & filename);
    
    void showToast(const char *text);
    
    void scaleBaseView();
    CCNode * _nodeShowAll;
    CCNode * _nodeExactFit;
    float getContentScaleX() {return _contentScaleX; }
    float getContentScaleY() {return _contentScaleY; }
    bool _isScaleRootView;
    float _contentScaleX;
    float _contentScaleY;
private:
    std::set<std::string>  _loadedSpriteSheet;
    std::set<std::string>  _singleSpriteFrame;
    bool _isInit;
};

class XXUiWaitingView;

class  RootUiLayerWithNetwork : public RootUiLayer{
public:
    RootUiLayerWithNetwork();
    virtual ~RootUiLayerWithNetwork();
    
    void showWaitDlg();
    void closeWaitDlg();
    
    void showErrorDialog(const int error);
        
    void onConnectionStatusChanged(cocos2d::CCObject* param);
    
    void registerConnectionStatusObserver();
    void unregisterConnectionStatusObserver();
    
    void onMessageBoxClickedButton(int32_t type);
    
    void dismissNetworkRequest();
    
protected:
    int32_t         _networkRequestId;
    XXUiWaitingView * _networkWaitDlg;
};

#endif
