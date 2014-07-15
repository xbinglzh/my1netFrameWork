//
//  GameConfig.h
//  motoGame
//
//  Created by xUanBing on 14-3-24.
//
//

#ifndef __motoGame__GameConfig__
#define __motoGame__GameConfig__

#include "cocos2d.h"
#include "FontStyle.h"

USING_NS_CC;

class  GameConfig : public cocos2d::CCObject {
    
protected:
	GameConfig();
	virtual ~GameConfig();
	bool init();
    
public:
    static GameConfig *sharedInstance();
    static void purgeInstance();
    
public:
    /**
     * 当前屏幕尺寸
     */
    CC_PROPERTY(int, _screenSize, ScreenSize);
    
    /**
     当前版本号
     */
    const std::string & getVersion() const;
    
    /**
     当前版本Build号
     */
    const std::string & getBuild() const;
    
    /**
     当前版本所在运营平台号
     */
    const std::string & getPlatform() const;
    
    /**
     当前APPID
     */
    const std::string & getAppId() const;
    
    /**
     当前APPID
     */
    int getAppstoreAppId();
    
    /**
     当前APPID
     */
    const std::string & getAppTargetOSVersion() const;
    
public:
    /**
     获得对应Id的animation信息
     */
    cocos2d::CCDictionary * getAnimationById(const std::string & Id);
    /**
     获得对应Id的字体样式{颜色，字体名，大小}
     */
	const FontStyle getFontStyleById(const std::string & Id);
    
private:
    std::string 	_version;
	std::string 	_build;
	std::string 	_platform;
    std::string 	_appid;
    std::string 	_appTargetOSVersion;
	uint32_t		_simpleProperties;
    
    
private: // Dict
    cocos2d::CCDictionary*        _animationDict;
    cocos2d::CCDictionary*        _textFontStyleDict;
    
};

#endif /* defined(__motoGame__GameConfig__) */
