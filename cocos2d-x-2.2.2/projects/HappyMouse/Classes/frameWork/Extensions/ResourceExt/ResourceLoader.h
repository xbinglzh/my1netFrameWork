//
//  ResourceLoader.h
//  iLostCity
//
//  Created by huang.haiyang on 13-4-19.
//  Copyright (c) 2013年 __MyCompanyName__. All rights reserved.
//

#ifndef iLostCity_ResourceLoader_h
#define iLostCity_ResourceLoader_h

#include <boost/function.hpp>

#include "cocos2d.h"

/**
 * 资源加载器
 * 从文件系统预先加载到内存
 */
class ResourceLoader {
public:
    static void loadNow(cocos2d::CCDictionary * resourceInfo,const boost::function<void ()> &finishedCallback);
    static void unloadNow(cocos2d::CCDictionary * resourceInfo);
    
    static void loadClassResources(const std::string & className);
    static void unloadClassResources(const std::string & className);
private:
    void load(cocos2d::CCDictionary * resourceInfo);
    void unload(cocos2d::CCDictionary * resourceInfo);
    void didFinished();
    
private:
    ResourceLoader(const boost::function<void ()> &finishedCallback) 
    : finishedCallback_(finishedCallback) {}
    
    ResourceLoader()
    : finishedCallback_(0) {}
    
    const boost::function<void ()> finishedCallback_;
};

#endif
