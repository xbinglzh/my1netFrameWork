//
//  CCSpriteExt.cpp
//  iLostCity
//
//  Created by Ryan_Y on 13-6-6.
//
//

#include "CCSpriteExt.h"
std::map<std::string, int32_t> CCSpriteExt::_textureRefs;

CCSpriteExt::CCSpriteExt(){

}

CCSpriteExt::~CCSpriteExt(){
    if (_texturefileName.length() > 0) {
        std::map<std::string, int32_t>::iterator iter =  _textureRefs.find(_texturefileName);
        if (iter != _textureRefs.end()) {
            iter->second --;
            if (iter->second <= 0) {
                iter->second = 0;
                CCTextureCache::sharedTextureCache()->removeTextureForKey(_texturefileName.c_str());
            }
        }
    }
}

bool CCSpriteExt::initWithFile(const char *pszFilename)
{
    if(CCSprite::initWithFile(pszFilename)) {
        std::map<std::string, int32_t>::iterator iter =  _textureRefs.find(pszFilename);
        if (iter != _textureRefs.end()) {
            iter->second ++;
        }else{
            _textureRefs[pszFilename] = 1;
        }
        this->_texturefileName = pszFilename;
        return true;
    }
    return false;
}

CCSpriteExt* CCSpriteExt::create(const char *pszFileName){
    CCSpriteExt *pobSprite = new CCSpriteExt();
    if (pobSprite && pobSprite->initWithFile(pszFileName))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}