//
//  UiUtils.h
//  iLostCity
//
//  Created by Ryan_Y on 13-4-22.
//
//

#ifndef iLostCity_UiUtils_h
#define iLostCity_UiUtils_h

#include "cocos2d.h"
#include "cocos-ext.h"

class UiUtils {
    
public:
    /*
     UI:创建一个可以滚动的文本框
     */
    static cocos2d::CCNode * createTextScrollNode(const cocos2d::CCSize & viewSize,
                                         const std::string & text,
                                         const cocos2d::ccColor3B& color3,
                                         const std::string & textFont,
                                         const int fontSize,
                                         const cocos2d::CCVerticalTextAlignment vertical = cocos2d::kCCVerticalTextAlignmentTop,
                                         const cocos2d::CCTextAlignment horizontal = cocos2d::kCCTextAlignmentLeft);
    
    /*
     UI:计算一个矩形放入到另外一个矩形中应该缩放多少的比例
     */
	static float scaleTofit(const cocos2d::CCSize & containerSize,
                            const cocos2d::CCSize & tgsize);
    
    /**
     * 对Node进行长款缩放
     */
    static cocos2d::CCNode* nodeScaleTofit(cocos2d::CCNode * containerNode,
                                           const cocos2d::CCSize & tgsiz);
    
    static cocos2d::CCNode* scale9Sprite(const std::string& fileName,
                                        const cocos2d::CCSize& size);
    
    /**
     * 获取配置中。对于的CCSize， CCPoint
     */
    static cocos2d::CCSize getUIConstantSizeById(const std::string & Id);
    static cocos2d::CCPoint getUIConstantPointById(const std::string & Id);
    
    static void createBackgroundWhitPlist(const std::string &plist, cocos2d::CCNode *node);
        
    /*
     *一代的正则表达式判断用户名密码是否合法
     */
//    static bool isNameCurrect(const std::string str);
//    static bool isPasswordCurrect(const std::string psw);
    
    /**
     *  1个中文2个长度
     *  1个英文字符一个长度
     */
    static const int stringLength(const std::string &str);
    
	/*
     UI:hex color value 转 R,G,B
     */
	static const uint8_t hexToR(const std::string & h);
	static const uint8_t hexToG(const std::string & h);
	static const uint8_t hexToB(const std::string & h);
    
    /**
      * 判断文件后坠名
    */
    static bool endsWith(const char* pString, const char* pEnding);
    
    /*
     UI:采用CCRenderTexture 方式实现为一个精灵生成遮罩
     */
    static cocos2d::CCSprite* maskedSprite(cocos2d::CCSprite* textureSprite,
                                                     cocos2d::CCSprite* maskSprite);
    
    static cocos2d::CCRect scaleNodeToExactFit(cocos2d::CCNode* node);
    static cocos2d::CCRect  scaleNodeToShowAll(cocos2d::CCNode* node);
    static cocos2d::CCRect scaleNodeByScaleFactor(cocos2d::CCNode* node,const float scale);
    static void revertScaleShowAllNode(cocos2d::CCNode* node);
protected:
	static std::string  cutHex(const std::string & h);
	
};

#endif
