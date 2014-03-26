//
//  HelloView.h
//  motoGame
//
//  Created by xUanBing on 14-3-24.
//
//

#ifndef __motoGame__HelloView__
#define __motoGame__HelloView__

#include "RootUiLayer.h"

class UiLoadingView : public RootUiLayerWithNetwork{
    
public:
    static cocos2d::CCScene* scene();
    
    UiLoadingView();
    virtual ~UiLoadingView();
    CREATE_FUNC(UiLoadingView);
    static UiLoadingView * createFromCCB();
    
public:
    virtual void onEnterTransitionDidFinish();
//    void onResourceUpdateMsg(CCObject *pSender);
protected:
    virtual bool initWithCustom();
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName,  CCNode * pNode);
    
private:
    CCSprite* _bgSprite;
};

CREATE_NEW_INHERIT_CCLAYERLOADER_CLASS(UiLoadingView);


#endif /* defined(__motoGame__HelloView__) */
