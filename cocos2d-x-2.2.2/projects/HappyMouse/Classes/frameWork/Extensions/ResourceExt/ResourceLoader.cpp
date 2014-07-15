//
//  ResourceLoader.cpp
//  iLostCity
//
//  Created by huang.haiyang on 13-4-19.
//  Copyright (c) 2013年 __MyCompanyName__. All rights reserved.
//

#include <boost/shared_ptr.hpp>
#include "ResourceLoader.h"
#include "AudioManager.h"
#include "KeyConfigDef.h"

static boost::shared_ptr<ResourceLoader> loader;

void ResourceLoader::loadNow(cocos2d::CCDictionary * resourceInfo,const boost::function<void ()> &finishedCallback) {
    loader.reset(new ResourceLoader(finishedCallback));
    
    loader->load(resourceInfo);
}

void ResourceLoader::unloadNow(cocos2d::CCDictionary * resourceInfo) {
    loader.reset(new ResourceLoader());
    
    loader->unload(resourceInfo);
}

void ResourceLoader::load(cocos2d::CCDictionary * resourceInfo) {
    
    //加载音效文件
    if (resourceInfo) {
        cocos2d::CCArray * array =  static_cast<cocos2d::CCArray *>(resourceInfo->objectForKey(KKeyAudio));
        AudioManager::sharedInstance()->loadAudioFile(array);
        
        //加载image文件
        array =  static_cast<cocos2d::CCArray *>(resourceInfo->objectForKey(KKeyImage));
        if(array){
            CCTextureCache * sharedTextureCache = CCTextureCache::sharedTextureCache();
            CCSpriteFrameCache * sharedSpriteFrameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
            CCObject * object = NULL;
            CCARRAY_FOREACH(array, object){
                CCDictionary * dict = static_cast<CCDictionary *>(object);
                CCString * texture =  static_cast<CCString *>(dict->objectForKey(KKeyImage));
                CCString * plist =  static_cast<CCString *>(dict->objectForKey(KKeyPlist));
                sharedTextureCache->addImage(texture->getCString());
                sharedSpriteFrameCache->addSpriteFramesWithFile(plist->getCString());
            }
        }
    }
    
    didFinished();
}

void ResourceLoader::unload(cocos2d::CCDictionary * resourceInfo) {
    //卸载音效文件
    if (resourceInfo) {
        cocos2d::CCArray * array =  static_cast<cocos2d::CCArray *>(resourceInfo->objectForKey(KKeyAudio));
        AudioManager::sharedInstance()->unloadAudioFile(array);
        
        //卸载image文件
        array =  static_cast<cocos2d::CCArray *>(resourceInfo->objectForKey(KKeyImage));
        if (array) {
            CCTextureCache * sharedTextureCache = CCTextureCache::sharedTextureCache();
            CCSpriteFrameCache * sharedSpriteFrameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
            CCObject * object = NULL;
            CCARRAY_FOREACH(array, object){
                CCDictionary * dict = static_cast<CCDictionary *>(object);
                CCString * texture = static_cast<CCString *>(dict->objectForKey(KKeyImage));
                CCString * plist = static_cast<CCString *>(dict->objectForKey(KKeyPlist));
                sharedSpriteFrameCache->removeSpriteFramesFromFile(plist->getCString());
                sharedTextureCache->removeTextureForKey(texture->getCString());
            }
        }
    }

    didFinished();
}

void ResourceLoader::didFinished() {
    if (finishedCallback_) {
        finishedCallback_();
    }
    loader.reset();
}

void ResourceLoader::loadClassResources(const std::string & className){
    CCSpriteFrameCache * sharedSpriteFrameCache=CCSpriteFrameCache::sharedSpriteFrameCache();
    CCTextureCache * sharedTextureCache = CCTextureCache::sharedTextureCache();
	std::string plist_name =  className +".plist";
	std::string image_name =  className +".png";
    sharedTextureCache->addImage(image_name.c_str());
    sharedSpriteFrameCache->addSpriteFramesWithFile(plist_name.c_str());
}

void ResourceLoader::unloadClassResources(const std::string & className){
    CCSpriteFrameCache * sharedSpriteFrameCache=CCSpriteFrameCache::sharedSpriteFrameCache();
    CCTextureCache * sharedTextureCache = CCTextureCache::sharedTextureCache();
    std::string plist_name =  className +".plist";
	std::string image_name =  className +".png";
    sharedSpriteFrameCache->removeSpriteFramesFromFile(plist_name.c_str());
    sharedTextureCache->removeTextureForKey(image_name.c_str());
}