//
//  AudioManager.h
//  MetalWar
//
//  Created by Ryan Yuan on 12-7-15.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef MetalWar_AudioManager_h
#define MetalWar_AudioManager_h

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

/*
 对音效进行包装，保证此处声音播放的引擎被替换
 */
class AudioManager:public CCObject {
    
protected:
    AudioManager();
	virtual ~AudioManager();
    bool init();
    
public:
    static AudioManager *sharedInstance();
    static void purgeInstance();
    
    /*
     加载需要使用到的音频资源
     */
    void loadAudioFile(CCArray* array);
    
    /*
     卸载使用不到的音效资源
     */
    void unloadAudioFile(CCArray* array);
    
    /*
     预加载一个音效文件
     */
	void preloadEffect(const char * file);
    
    /*
     卸载一个音效文件
     */
    void unloadEffect(const char * file);
    
    /*
     播放一个音效文件
     */
	unsigned int playEffect(const char* pszFilePath, bool bLoop = false);
    
    /*
     停止播放一个音效文件
     */
    void stopEffect(unsigned int nSoundId);
    
    /*
     停止播放所有音效文件
     */
    void stopAllEffect();

    /*
     开始播放背景音乐
     */
	void playBackgroundMusic(const char * file,bool bLoop = true);
    
    /*
     停止播放背景音乐
     */
    void stopBackgroundMusic(bool bReleaseData = false);//bReleaseData表示是否释放音乐文件
    
    /*
     暂停播放背景音乐
     */
    void pauseBackgroundMusic();
    

    /*
     设置当前的背景音乐和音效的音量大小
     */
    void setAudioVolume(float effect,float background);
    
    /*
     获取当前的背景音乐的音量大小
     */
    float getEffectsVolume();
    
    /*
     设置当前的背景音乐的音量大小
     */
    void setEffectsVolume(float volume);
    
    /*
     获取当前的音效的音量大小
     */
    float getBackgroundMusicVolume();
    
    /*
     设置当前的音效的音量大小
     */
    void setBackgroundMusicVolume(float volume);
    
    /*
     设置背景音乐打开
     */
    void openBackgroundMusic();
    
    /*
     设置背景音乐关闭
     */
    void closedBackgroundMusic();
    
    /*
     设置背景音效打开
     */
    void openEffectMusic();
    
    /*
     设置背景音效关闭
     */
    void closedEffectMusic();
    
    /*
     暂停背景音乐+音效
     */
    void pause();
    
    /*
     恢复背景音乐+音效
     */
    void resume();
    
    /*
     卸载背景音乐
     */
    void unloadBgMusicFile();
    
    void playAudioById(const int32_t id,const bool repeat = false/*= false*/);
    
private:
    /*
     预先加载背景音乐
     */
    void preloadBackGroundMusicFile(const char * file);
    
public:
    static void setDefaultBackgroundVolume(float vol);
    static void setDefaultEffectVolume(float vol);
    
protected:
    CocosDenshion::SimpleAudioEngine *_soundEngine;
	std::string _backgourndMusic;
    static float _defaultBackgroundVolume;
    static float _defaultEffectVolume;
    
};

#endif
