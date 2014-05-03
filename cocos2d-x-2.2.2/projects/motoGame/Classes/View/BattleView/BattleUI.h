//
//  BattleUI.h
//  motoGame
//
//  Created by xUanBing on 14-5-1.
//
//

#ifndef __motoGame__BattleUI__
#define __motoGame__BattleUI__

#include "cocos2d.h"
#include "RootUiLayer.h"
#include "cocos-ext.h"

class CCScale9ProgressBar;
class CCSpriteExt;

USING_NS_CC;
USING_NS_CC_EXT;

class BattleUI : public RootUiLayer {
    
public:
    BattleUI();
    virtual ~BattleUI();

    static BattleUI* createFromCCB();
    CREATE_FUNC(BattleUI);
    
public:
    void setPowerRatio();
    
protected:
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName,  CCNode * pNode);
    
protected:
    virtual bool initWithCustom();
    
protected:
    virtual void registerWithTouchDispatcher(void);
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
private:
    void onNotifyEnergyValueChangeMessage(CCObject* pSender);
    void onNotifyGameScoreChangeMessage(CCObject* pSender);
private:
    CCNode* _powerNode;
    CCNode* _scoreNode;
    
    CCScale9Sprite* _powerBg;
    CCScale9ProgressBar* _powerBar;
};

CREATE_NEW_INHERIT_CCLAYERLOADER_CLASS(BattleUI);

#endif /* defined(__motoGame__BattleUI__) */
