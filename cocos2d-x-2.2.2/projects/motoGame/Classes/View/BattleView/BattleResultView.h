//
//  BattleResultView.h
//  motoGame
//
//  Created by xUanBing on 14-5-4.
//
//

#ifndef __motoGame__BattleResultView__
#define __motoGame__BattleResultView__

#include "cocos2d.h"
#include "RootUiLayer.h"
#include "battle.h"

class LabelView;

USING_NS_CC;

typedef boost::function<void (int32_t)> BattleResultCallback;

class BattleResultView : public RootUiLayer {
    
public:
    BattleResultView();
    ~BattleResultView();
    
    CREATE_FUNC(BattleResultView);
    
    static BattleResultView* show(const battle::Rewards& reward, const BattleResultCallback& callback = NULL);
    
protected:
    virtual bool initWithCustom();
    
protected:
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName,  CCNode * pNode);
    
private:
    static BattleResultView* createFromCCB();
    void   fillData(const battle::Rewards& rewards);
    void setCallback(const BattleResultCallback& callback){_callback = callback;}
    
private:
    void onRestartButtonCallBack();
    
private:
    BattleResultCallback  _callback;
    
    CCNode*      _scoreNode;
    CCMenuItem*  _restartButton;
    LabelView*   _score;
    
};

CREATE_NEW_INHERIT_CCLAYERLOADER_CLASS(BattleResultView);

#endif /* defined(__motoGame__BattleResultView__) */