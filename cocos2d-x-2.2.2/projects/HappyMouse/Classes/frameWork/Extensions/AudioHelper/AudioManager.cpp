//
//  AudioManager.cpp
//  MetalWar
//
//  Created by Ryan Yuan on 12-7-15.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "AudioManager.h"
#include "GameConfig.h"
#include "ConstansDef.h"
#include "KeyConfigDef.h"

#if 0

static AudioManager *_audioSharedInstance = NULL;
float AudioManager::_defaultBackgroundVolume  = 1.0f;
float AudioManager::_defaultEffectVolume  = 1.0f;

AudioManager* AudioManager::sharedInstance() {
    
    if (!_audioSharedInstance) {
		_audioSharedInstance = new AudioManager();
	}
    
	return _audioSharedInstance;
}

void AudioManager::purgeInstance() {
	CC_SAFE_DELETE(_audioSharedInstance);
}

void AudioManager::setDefaultBackgroundVolume(float vol) {
    AudioManager::_defaultBackgroundVolume = vol;
}

void AudioManager::setDefaultEffectVolume(float vol) {
    AudioManager::_defaultEffectVolume = vol;
}

AudioManager::AudioManager() {
    
}

AudioManager::~AudioManager() {
    
}

void AudioManager::loadAudioFile(CCArray* array) {
    
}

void AudioManager::unloadAudioFile(CCArray* array) {
    
}

void AudioManager::preloadEffect(const char * file) {
    
}

void AudioManager::preloadBackGroundMusicFile(const char * file) {
    
    if(file){
		_backgourndMusic=file;
	}
}

void AudioManager::unloadBgMusicFile() {
    
}

unsigned int AudioManager::playEffect(const char* file, bool bLoop) {
    
    return -1;
}

void AudioManager::stopEffect(unsigned int nSoundId) {
    
}

void AudioManager::stopAllEffect() {
    
}

void AudioManager::unloadEffect(const char * file) {
    
}

void AudioManager::playBackgroundMusic(const char * file, bool bLoop){
    
}

void AudioManager::stopBackgroundMusic(bool bReleaseData) {
    
}

void AudioManager::pauseBackgroundMusic() {
    
}

void AudioManager::setAudioVolume(float effect,float background) {
    
}
void AudioManager::setEffectsVolume(float volume) {
    
}
void AudioManager::setBackgroundMusicVolume(float volume) {
    
}

float AudioManager::getEffectsVolume() {
    return 0;
}
float AudioManager::getBackgroundMusicVolume() {
    return 0;
}

void AudioManager::openBackgroundMusic() {
    
}

void AudioManager::closedBackgroundMusic() {
    
}

void AudioManager::openEffectMusic() {
    
}

void AudioManager::closedEffectMusic() {
    
}

void AudioManager::pause() {
    
}

void AudioManager::resume() {
}

#else

static AudioManager * _audioSharedInstance=NULL;
float AudioManager::_defaultBackgroundVolume  = 1.0f;
float AudioManager::_defaultEffectVolume  = 1.0f;

AudioManager * AudioManager::sharedInstance() {
	
	if (! _audioSharedInstance) {
        _audioSharedInstance = new AudioManager();
        _audioSharedInstance->init();
    }
	
	return _audioSharedInstance;
}

void AudioManager::purgeInstance() {
	CC_SAFE_RELEASE_NULL(_audioSharedInstance);
}

AudioManager::AudioManager() {
    _soundEngine = CocosDenshion::SimpleAudioEngine::sharedEngine();
    this->setEffectsVolume(AudioManager::_defaultEffectVolume);
    this->setBackgroundMusicVolume(AudioManager::_defaultBackgroundVolume);
}

AudioManager::~AudioManager() {
    
	if (_soundEngine) {
		_soundEngine->end();
        _soundEngine = NULL;
	}
}

void AudioManager::setDefaultBackgroundVolume(float vol) {
    AudioManager::_defaultBackgroundVolume = vol;
}

void AudioManager::setDefaultEffectVolume(float vol) {
    AudioManager::_defaultEffectVolume = vol;
}

bool AudioManager::init() {
    return true;
}

void AudioManager::loadAudioFile(CCArray * array) {
    
	if (array) {
		for(int i = 0;i < array->count(); i++)
		{
			CCString* audio = (CCString*)array->objectAtIndex(i);
			this->preloadEffect(audio->getCString());
		}
	}
}

void AudioManager::unloadAudioFile(CCArray* array) {
    
	this->stopAllEffect();
	
	if (array) {
		for(int i=0;i<array->count();i++)
		{
			CCString* audio = (CCString*)array->objectAtIndex(i);
			this->unloadEffect(audio->getCString());
		}
	}
}

void AudioManager::preloadEffect(const char * file) {
    if(file)
        _soundEngine->preloadEffect(file);
} 

void AudioManager::preloadBackGroundMusicFile(const char * file) {
    if(file && _backgourndMusic.compare(file) != 0){
		_backgourndMusic = file;
		_soundEngine->preloadBackgroundMusic(file);
	}
}

void AudioManager::unloadBgMusicFile() {
    if(_soundEngine->isBackgroundMusicPlaying()){
		_backgourndMusic.clear();
		this->stopBackgroundMusic(true);
	}
}

unsigned int AudioManager::playEffect(const char* file, bool bLoop) {
    
    int ret = -1;
    if(file){
        ret =  _soundEngine->playEffect(file,bLoop);
    }
    return ret;
}

void AudioManager::stopEffect(unsigned int nSoundId) {
    
    _soundEngine->stopEffect(nSoundId);
}

void AudioManager::stopAllEffect() {
    
    _soundEngine->stopAllEffects();
}

void AudioManager::unloadEffect(const char * file) {
    
    CCAssert( file != NULL&&file != "", "file must be non-nil");
    if(file)
        _soundEngine->unloadEffect(file);
}

void AudioManager::playBackgroundMusic(const char * file,bool bLoop){
    
    preloadBackGroundMusicFile(file);
    
	if (_backgourndMusic.length()>0) {
		_soundEngine->playBackgroundMusic(_backgourndMusic.c_str(),bLoop);
	}
}

void AudioManager::stopBackgroundMusic(bool bReleaseData) {
    
	if (_backgourndMusic.length()>0) {
		_backgourndMusic.clear();
		_soundEngine->stopBackgroundMusic(bReleaseData);
	}
}

void AudioManager::pauseBackgroundMusic() {
    
    _soundEngine->pauseBackgroundMusic();
}

void AudioManager::setAudioVolume(float effect,float background) {
    
    _soundEngine->setEffectsVolume(effect);
    _soundEngine->setBackgroundMusicVolume(background);
}

void AudioManager::setEffectsVolume(float volume) {
    
    _soundEngine->setEffectsVolume(volume);
}

void AudioManager::setBackgroundMusicVolume(float volume) {
    
    _soundEngine->setBackgroundMusicVolume(volume);
}

float AudioManager::getEffectsVolume() {
    
    return _soundEngine->getEffectsVolume();
}

float AudioManager::getBackgroundMusicVolume() {
    
    return _soundEngine->getBackgroundMusicVolume();
}

void AudioManager::openBackgroundMusic() {
    
    if(_soundEngine)
        _soundEngine->setBackgroundMusicVolume(AudioManager::_defaultBackgroundVolume);
}

void AudioManager::closedBackgroundMusic() {
    
    if(_soundEngine)
        _soundEngine->setBackgroundMusicVolume(0.0f);
}

void AudioManager::openEffectMusic() {
    
    if(_soundEngine)
        _soundEngine->setEffectsVolume(AudioManager::_defaultEffectVolume);
    
}

void AudioManager::closedEffectMusic() {
    
    if(_soundEngine)
        _soundEngine->setEffectsVolume(0.0f);
    
}

void AudioManager::pause() {
    
    if(_soundEngine){
        _soundEngine->pauseBackgroundMusic();
        _soundEngine->pauseAllEffects();
    }
    
}

void AudioManager::resume() {
    
    if(_soundEngine){
        _soundEngine->resumeBackgroundMusic();
        _soundEngine->resumeAllEffects();
    }
    
}

void AudioManager::playAudioById(const int32_t id,const bool repeat /*= false*/){
    if(id > 0){
        AudioManager * gAudioManager = AudioManager::sharedInstance();
        const float effectsVolume = gAudioManager->getEffectsVolume();
        CCLOG("effectsVolume = %f",effectsVolume);
        GameConfig *   gConfig = GameConfig::sharedInstance();
        std::stringstream audioString;
        audioString << id;
        
        CCDictionary * dict = gConfig->getMusicFileInfoById(audioString.str());
        
        if (dict) {
            CCString * type = (CCString *)dict->objectForKey(KKeyType);
            CCString * file = (CCString *)dict->objectForKey(KKeyAudio);
            if(file && type){
                if (type->intValue() == 2) {
                    gAudioManager->unloadBgMusicFile();
                    gAudioManager->playBackgroundMusic(file->getCString());
                }else{
                    int ret = gAudioManager->playEffect(file->getCString(),repeat);
                }
            }
        }
    }
}


#endif
