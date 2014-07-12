/*
 * Copyright (c) 2012 Chukong Technologies, Inc.
 *
 * http://www.sweetpome.com
 * http://tools.cocoachina.com
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to permit
 * persons to whom the Software is furnished to do so, subject to the
 * following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
 * NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "SPDataReaderHelper.h"
#include "SPArmatureDataManager.h"
#include "SPTransformHelp.h"
#include "../SPArmature.h"
#include "tinyxml.h"
#include "../datas/SPTextureData.h"
#include "../datas/SPAnimationData.h"
#include "../datas/SPArmatureData.h"

using namespace cocos2d;

namespace sp{
    
ArmatureDataManager *ArmatureDataManager::m_sSharedArmatureDataManager = NULL;
ArmatureDataManager *ArmatureDataManager::sharedArmatureDataManager()
{
    if (m_sSharedArmatureDataManager == NULL)
    {
        m_sSharedArmatureDataManager = new ArmatureDataManager();
        if (!(m_sSharedArmatureDataManager && m_sSharedArmatureDataManager->init()))
        {
            CC_SAFE_DELETE(m_sSharedArmatureDataManager);
            m_sSharedArmatureDataManager = NULL;
        }
    }
    return m_sSharedArmatureDataManager;
}

ArmatureDataManager::ArmatureDataManager(void):
m_pAnimationDatas(NULL),
m_pArmarureDatas(NULL),
m_pTextureDatas(NULL),
m_pArmatureFileInfoDic(NULL){

}


ArmatureDataManager::~ArmatureDataManager(void){
    CC_SAFE_RELEASE_NULL(m_pAnimationDatas);
    CC_SAFE_RELEASE_NULL(m_pArmarureDatas);
    CC_SAFE_RELEASE_NULL(m_pTextureDatas);
    CC_SAFE_RELEASE_NULL(m_pArmatureFileInfoDic);
}

bool ArmatureDataManager::init()
{
    bool bRet = false;
    do
    {
        m_pArmarureDatas = CCDictionary::create();
        CCAssert(m_pArmarureDatas, "create ArmatureDataManager::m_pArmarureDatas fail!");
        m_pArmarureDatas->retain();
        
        m_pAnimationDatas = CCDictionary::create();
        CCAssert(m_pAnimationDatas, "create ArmatureDataManager::m_pAnimationDatas fail!");
        m_pAnimationDatas->retain();

        m_pTextureDatas = CCDictionary::create();
        CCAssert(m_pTextureDatas, "create ArmatureDataManager::m_pTextureDatas fail!");
        m_pTextureDatas->retain();
        
        m_pArmatureFileInfoDic = CCDictionary::create();
        CCAssert(m_pArmatureFileInfoDic, "create ArmatureDataManager::m_pArmatureFileInfoDic fail!");
        m_pArmatureFileInfoDic->retain();
        
        bRet = true;
    }
    while (0);

    return bRet;
}

const long ArmatureDataManager::currentTime(){
    struct cc_timeval now;
    CCTime::gettimeofdayCocos2d(&now, NULL);
    return now.tv_usec;
}
    
void ArmatureDataManager::addArmatureData(const char *_id, ArmatureData *_armatureData)
{
    if(m_pArmarureDatas)
    {
        m_pArmarureDatas->setObject(_armatureData, _id);
    }
}
    
ArmatureData *ArmatureDataManager::getArmatureData(const char* _id)
{
    ArmatureData * _armatureData = NULL;
    if (m_pArmarureDatas)
    {
        _armatureData = (ArmatureData*)m_pArmarureDatas->objectForKey(_id);
    }
    return _armatureData;
}

void ArmatureDataManager::addAnimationData(const char *_id, AnimationData *_animationData)
{
    if(m_pAnimationDatas)
    {
        m_pAnimationDatas->setObject(_animationData, _id);
    }
}
    
void ArmatureDataManager::addTextureData(const char *_id, TextureData *_textureData)
{
    if(m_pTextureDatas)
    {
        m_pTextureDatas->setObject(_textureData, _id);
    }
}
    
AnimationData* ArmatureDataManager::getAnimationData(const char* _id)
{
    AnimationData *_animationData = NULL;
    if (m_pAnimationDatas){
        _animationData = (AnimationData*)m_pAnimationDatas->objectForKey(_id);
    }
    return _animationData;
}

TextureData *ArmatureDataManager::getTextureData(const char* _id)
{
    TextureData *_textureData = NULL;
    if (m_pTextureDatas){
        _textureData = (TextureData*)m_pTextureDatas->objectForKey(_id);
    }
    return _textureData;
}
    
ArmatureFileInfo *ArmatureDataManager::getArmatureFileInfo(const char *_id)
{
    ArmatureFileInfo *_armatureFileInfo = NULL;
    if (m_pArmatureFileInfoDic){
        _armatureFileInfo = (ArmatureFileInfo*)m_pArmatureFileInfoDic->objectForKey(_id);
    }
    return _armatureFileInfo;
}



void  ArmatureDataManager::addArmatureFileInfo(const char *_armatureName,
                                              const char *_imagePath,
                                              const char *_plistPath,
                                              const char *_configFilePath,
                                              const float positionReadScale)
{
    ArmatureFileInfo *_fileInfo = (ArmatureFileInfo*)m_pArmatureFileInfoDic->objectForKey(_armatureName);
    if(!_fileInfo){
        //CCLOG("addArmatureFileInfo %s",_configFilePath);
        _fileInfo = ArmatureFileInfo::create();
        _fileInfo->armatureName = _armatureName;
        _fileInfo->configFilePath = _configFilePath;
        m_pArmatureFileInfoDic->setObject(_fileInfo, _fileInfo->armatureName);
    }

    DataReaderHelper::setPositionReadScale(positionReadScale);
    DataReaderHelper::addDataFromFile(_configFilePath);
    DataReaderHelper::setPositionReadScale(1.0f);
    _fileInfo->isDecoded = true;
    
	for (std::vector<ImageInfo>::iterator it = _fileInfo->imageInfoVector.begin();
         it != _fileInfo->imageInfoVector.end();it++){
        if (it->imagePath.compare(_imagePath) == 0){
            return;
        }
    }
    
    ImageInfo _imageInfo;
    _imageInfo.imagePath = _imagePath;
    _imageInfo.plistPath = _plistPath;
    addSpriteFrameFromFile(_plistPath, _imagePath);
    _fileInfo->imageInfoVector.push_back(_imageInfo);
}
    
void ArmatureDataManager::addSpriteFrameFromFile(const char *_plistPath, const char *_imagePath){
    //TODO:需要测试
#if USING_COCOS2D_2_1_PLUS
    std::string pszPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(_plistPath);
#else
    std::string pszPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(_plistPath);
#endif
    
    CCDictionary *dict = CCDictionary::createWithContentsOfFileThreadSafe(pszPath.c_str());
    CCDictionary *framesDict = (CCDictionary*)dict->objectForKey("frames");
    CCDictElement* pElement = NULL;
    CCDICT_FOREACH(framesDict, pElement){
        const std::string spriteFrameName = pElement->getStrKey();
        m_Display2ImageMap[spriteFrameName] = _imagePath;
    }
    CC_SAFE_RELEASE_NULL(dict);
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(_plistPath, _imagePath);
}
    
const char *ArmatureDataManager::getDisplayImagePath(const char *_displayName)
{
    return m_Display2ImageMap[_displayName].c_str();
}

void ArmatureDataManager::removeAll()
{
    if( m_pAnimationDatas ){
        m_pAnimationDatas->removeAllObjects();
    }
    
    if( m_pArmarureDatas ){
        m_pArmarureDatas->removeAllObjects();
    }

    if( m_pTextureDatas ){
        m_pTextureDatas->removeAllObjects();
    }
    
    if( m_pArmatureFileInfoDic ){
        m_pArmatureFileInfoDic->removeAllObjects();
    }
}

void ArmatureDataManager::removeUnusedAnimations(){
    if( m_pArmatureFileInfoDic ){
        CCTextureCache * tc = CCTextureCache::sharedTextureCache();
        CCSpriteFrameCache * sfc = CCSpriteFrameCache::sharedSpriteFrameCache();
        std::vector<std::string> cleanlist;
        CCDictElement* pElement = NULL;
        CCDICT_FOREACH(m_pArmatureFileInfoDic, pElement){
            const std::string file = pElement->getStrKey();
            ArmatureFileInfo * _fileInfo = (ArmatureFileInfo*)pElement->getObject();
            if (_fileInfo && _fileInfo->retainCount() == 1) {
                
                //清理 m_pAnimationDatas、m_pArmarureDatas、m_pTextureDatas 信息
                if( m_pAnimationDatas ){
                    m_pAnimationDatas->removeObjectForKey(_fileInfo->configFilePath);
                }
                
                if( m_pArmarureDatas ){
                    m_pArmarureDatas->removeObjectForKey(_fileInfo->configFilePath);
                }
                
                if( m_pTextureDatas ){
                    m_pTextureDatas->removeObjectForKey(_fileInfo->configFilePath);
                }
                
                //清理精灵帧、纹理和标记需要清理的ArmatureFile
                for (std::vector<ImageInfo>::iterator it = _fileInfo->imageInfoVector.begin();
                     it != _fileInfo->imageInfoVector.end();
                     it++){
                    const std::string & plist = it->plistPath;
                    const std::string & texture = it->imagePath;
                    sfc->removeSpriteFramesFromFile(plist.c_str());
                    tc->removeTextureForKey(texture.c_str());
                    cleanlist.push_back(file);
                }
            }
        }
        
        
        
        int size = cleanlist.size();
        for(int i = 0; i < size; i++) {
            m_pArmatureFileInfoDic->removeObjectForKey(cleanlist[i]);
        }
        cleanlist.clear();
    }
}

}