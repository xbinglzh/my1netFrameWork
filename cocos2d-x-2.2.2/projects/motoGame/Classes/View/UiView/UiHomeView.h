//
//  UiHomeView.h
//  motoGame
//
//  Created by xUanBing on 14-4-20.
//
//

#ifndef __motoGame__UiHomeView__
#define __motoGame__UiHomeView__

#include "cocos2d.h"
#include "RootUiLayer.h"

class UiHomeView : public RootUiLayerWithNetwork {
    
public:
    UiHomeView();
    ~UiHomeView();
    
    CREATE_FUNC(UiHomeView);
    static UiHomeView* createFromCCB();
    
protected:
    virtual bool initWithCustom();
//    void onEnterTransitionDidFinish();
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName);
    
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName);
    
    virtual bool onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName,  CCNode * pNode);
    
private:
    void onNewGameCallBack();
    
};

CREATE_NEW_INHERIT_CCLAYERLOADER_CLASS(UiHomeView);

#endif /* defined(__motoGame__UiHomeView__) */
