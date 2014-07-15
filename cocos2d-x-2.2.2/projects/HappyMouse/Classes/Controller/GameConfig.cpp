//
//  GameConfig.cpp
//  motoGame
//
//  Created by xUanBing on 14-3-24.
//
//

#include "GameConfig.h"
#include "KeyConfigDef.h"
#include "ConstansDef.h"
#include "UiUtils.h"

static GameConfig * _configSharedInstance=NULL;

GameConfig::GameConfig() : _animationDict(NULL), _textFontStyleDict(NULL), _pitNumCount(9){
    
}

GameConfig::~GameConfig() {
    CC_SAFE_RELEASE_NULL(_animationDict);
    CC_SAFE_RELEASE_NULL(_textFontStyleDict);
    _pitNumCount = 9;
}

GameConfig * GameConfig::sharedInstance(){
	
	if (!_configSharedInstance) {
        _configSharedInstance = new GameConfig();
        _configSharedInstance->init();
    }
	
	return _configSharedInstance;
}

void GameConfig::purgeInstance() {
	CC_SAFE_RELEASE_NULL(_configSharedInstance);
}

bool GameConfig::init() {
    
//    CC_SAFE_RELEASE_NULL(_animationDict);
//    _animationDict = CCDictionary::createWithContentsOfFile("x_anim.plist");
//    _animationDict->retain();
//    
//    CC_SAFE_RELEASE_NULL(_textFontStyleDict);
//    _textFontStyleDict = CCDictionary::createWithContentsOfFile("x_fontstyle.plist");
//    _textFontStyleDict->retain();
    
    return true;
}

int GameConfig::getScreenSize() {
    return _screenSize;
}

void GameConfig::setScreenSize(int var) {
    this->_screenSize = var;
}

/**
 获得对应Id的animation信息
 */
cocos2d::CCDictionary * GameConfig::getAnimationById(const std::string & Id){
    if (_animationDict) {
        return static_cast<CCDictionary * >(_animationDict->objectForKey(Id));
    }
    return NULL;
}

/**
 获得对应Id的字体样式{颜色，字体名，大小}
 */

const FontStyle GameConfig::getFontStyleById(const std::string & Id){
    FontStyle fontstyle;
    
    if (_textFontStyleDict) {
		CCDictionary * dict =  static_cast<CCDictionary * >(_textFontStyleDict->objectForKey(Id));
		fontstyle._font = static_cast<CCString * >(dict->objectForKey(KKeyFont))->m_sString;
		fontstyle._size = static_cast<CCString * >(dict->objectForKey(KKeySize))->intValue();
        
        const std::string &type = static_cast<CCString *>(dict->objectForKey(KKeyType))->m_sString;
        fontstyle._type = atoi(type.c_str());
        
        if (fontstyle._type != K_FONT_LABEL_BM) {
            const std::string & colorstring = static_cast<CCString * >(dict->objectForKey(KKeyColor))->m_sString;
            fontstyle._color.r = UiUtils::hexToR(colorstring);
            fontstyle._color.g = UiUtils::hexToG(colorstring);
            fontstyle._color.b = UiUtils::hexToB(colorstring);
        }
        if (fontstyle._type == K_FONT_LABEL_TTF_STROKE) {
            CCString *str = static_cast<CCString * >(dict->objectForKey(KKeyStrokeColor));
            if (str) {
                const std::string &strokeColorstring = str->getCString();
                fontstyle._stroke_color = ccc3(UiUtils::hexToR(strokeColorstring),
                                               UiUtils::hexToG(strokeColorstring),
                                               UiUtils::hexToB(strokeColorstring));
            }
        }
    }
    
    return fontstyle;
}

uint32_t GameConfig::getPitNumCount() {
    return _pitNumCount;
}
