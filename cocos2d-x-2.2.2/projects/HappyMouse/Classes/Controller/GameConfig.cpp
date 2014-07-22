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
#include "GameEventDef.h"


static GameConfig * _configSharedInstance = NULL;

GameConfig::GameConfig() :
_animationDict(NULL),
_textFontStyleDict(NULL),
_audioDict(NULL),
_stateGroupDict(NULL),
_templateDict(NULL),
_pitNumCount(9) {
    
}

GameConfig::~GameConfig() {
    CC_SAFE_RELEASE_NULL(_animationDict);
    CC_SAFE_RELEASE_NULL(_textFontStyleDict);
    CC_SAFE_RELEASE_NULL(_audioDict);
    CC_SAFE_RELEASE_NULL(_stateGroupDict);
    CC_SAFE_RELEASE_NULL(_templateDict);
    
    _pitNumCount = 9;
}

GameConfig * GameConfig::getInstance(){
	
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
    
    CC_SAFE_RELEASE_NULL(_textFontStyleDict);
    _textFontStyleDict = CCDictionary::createWithContentsOfFile("x_fontstyle.plist");
    _textFontStyleDict->retain();
    
    CC_SAFE_RELEASE_NULL(_audioDict);
    _audioDict = CCDictionary::createWithContentsOfFile("x_audio.plist");
    _audioDict->retain();
    
    CC_SAFE_RELEASE_NULL(_templateDict);
    _templateDict = new CCDictionary;
    _templateDict->setObject(CCDictionary::createWithContentsOfFile("x_monster.plist"), K_TYPE_MONSTER);
    
    return true;
}

void GameConfig::loadDynamicResoure(){
    CC_SAFE_RELEASE_NULL(_animationDict);
    _animationDict = CCDictionary::createWithContentsOfFile("x_anim.plist");
    _animationDict->retain();
    
    CC_SAFE_RELEASE_NULL(_stateGroupDict);
    _stateGroupDict = CCDictionary::createWithContentsOfFile("x_state_group.plist");
    _stateGroupDict->retain();
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

cocos2d::CCDictionary * GameConfig::getStateGroupById(const std::string & key){
    if (_stateGroupDict) {
        return static_cast<CCDictionary * >(_stateGroupDict->objectForKey(key));
    }
    return NULL;
    
}

CCDictionary * GameConfig::getTemplateValue(const int32_t Id){
    if (_templateDict) {
        std::stringstream key;
        key << Id;

        CCDictionary * tmpDict = static_cast<CCDictionary * >(_templateDict->objectForKey(GameConfig::templateTypeOfId(Id)));
        
        if(tmpDict) {
            return static_cast<CCDictionary * >(tmpDict->objectForKey(key.str()));
        }
        
    }
    return NULL;
}

const uint32_t GameConfig::templateTypeOfId(const uint32_t id) {
    return (id / 100000);
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

/**
 获得对应id的音乐文件名
 */
const std::string  GameConfig::getMusicFileById(const std::string & id){
    if (_audioDict) {
        CCDictionary * audio = static_cast<CCDictionary * >(_audioDict->objectForKey(id));
        if (audio) {
            return static_cast<CCString * >(audio->objectForKey(KKeyAudio))->m_sString;
        }
    }
    return "";
}

cocos2d::CCDictionary * GameConfig::getMusicFileInfoById(const std::string & id){
    if (_audioDict) {
        return static_cast<CCDictionary * >(_audioDict->objectForKey(id));
    }
    return NULL;
}
