//
//  GameResultView.h
//  HappyMouse
//
//  Created by xUanBing on 14-7-13.
//
//

#ifndef __HappyMouse__GameResultView__
#define __HappyMouse__GameResultView__

#include "cocos2d.h"
#include "RootUiLayer.h"
#include "ModelDialog.h"

USING_NS_CC;

class GameResultView : public RootUiLayer {
    
public:
    GameResultView();
    virtual ~GameResultView();
    CREATE_FUNC(GameResultView);
    static GameResultView * createFromCCB();
    
protected:
    virtual bool initWithCustom();
    
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName,  CCNode * pNode);
    
public:
    void show();
    void hide();
    
private:
    ModelDialog* _dialog;
    CCNode* _winResultNode;
    CCNode* _loseResultNode;
};

CREATE_NEW_INHERIT_CCLAYERLOADER_CLASS(GameResultView);

#endif /* defined(__HappyMouse__GameResultView__) */
