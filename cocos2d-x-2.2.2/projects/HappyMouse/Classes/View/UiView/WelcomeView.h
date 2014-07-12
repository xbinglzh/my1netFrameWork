//
//  WelcomeView.h
//  HappyMouse
//
//  Created by xUanBing on 14-7-13.
//
//

#ifndef __HappyMouse__WelcomeView__
#define __HappyMouse__WelcomeView__

#include "cocos2d.h"
#include "RootUiLayer.h"

class WelcomeView : public RootUiLayer {
    
public:
    WelcomeView();
    virtual ~WelcomeView();
    CREATE_FUNC(WelcomeView);
    static WelcomeView * createFromCCB();
    
protected:
    virtual bool initWithCustom();

    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName,  CCNode * pNode);
    
private:
    void onStartBtnClickCallBack();
    
private:
    CCMenuItem* _startBtn;
};

CREATE_NEW_INHERIT_CCLAYERLOADER_CLASS(WelcomeView);

#endif /* defined(__HappyMouse__WelcomeView__) */
