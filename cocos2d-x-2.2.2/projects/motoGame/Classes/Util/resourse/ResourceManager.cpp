
#include "ResourceManager.h"
#include "CCScale9ProgressBar.h"
#include "CCShaderEffectSprite.h"

USING_NS_CC;
using std::set;
using std::string;
using std::map;
using namespace cocos2d;

ResourceManager::ResourceManager() {

}

void ResourceManager::addTexture(const char* imgFile,cocos2d::CCNode* node,bool isGlobalTexture){
    if (isGlobalTexture) {
        addGlobalTexture(imgFile);
    } else {
        map<cocos2d::CCNode*, set<string> >::iterator itNodeTextures = _nodeTextures.find(node);
        if (itNodeTextures != _nodeTextures.end()) {
            set<string> imageset = itNodeTextures->second;
            set<string>::iterator iter = imageset.find(imgFile);
            if (iter == imageset.end()) {
                (itNodeTextures->second).insert(imgFile);
                accumulateToTextures(imgFile);
            }
        }else{
            set<string> imageSet;
            imageSet.insert(imgFile);
            _nodeTextures.insert(map<CCNode*, set<string> >::value_type(node,imageSet));
            accumulateToTextures(imgFile);
        }
    }
    
}

void ResourceManager::addPlistFile(const char *plistFile,cocos2d::CCNode* node,bool isGlobalTexture){
    if (isGlobalTexture) {
        addGlobalPlistFile(plistFile);
    } else{
        map<cocos2d::CCNode*, set<string> >::iterator itNodePlists = _nodePlists.find(node);
        if (itNodePlists != _nodePlists.end()) {
            set<string> plistSet = itNodePlists->second;
            set<string>::iterator iter = plistSet.find(plistFile);
            if (iter == plistSet.end()) {
                (itNodePlists->second).insert(plistFile);
                accumulateToPlist(plistFile);
            }
            
        }else{
            set<string> plistSet;
            plistSet.insert(plistFile);
            _nodePlists.insert(map<CCNode*, set<string> >::value_type(node,plistSet));
            accumulateToPlist(plistFile);
        }
    }
    
}

void ResourceManager::addGlobalTexture(const char *imgFile){
    _globalTextures.insert(imgFile);
}

void ResourceManager::addGlobalPlistFile(const char *plistFile){
    _globalPlists.insert(plistFile);
}

void ResourceManager::accumulateToTextures(const char *imgFile){
    map<string, int>::iterator iter = _textures.find(imgFile);
    if (iter != _textures.end()) {
        ++(iter->second);
    }else{
        _textures.insert(map<string, int>::value_type(imgFile,1));
    }
}

void ResourceManager::accumulateToPlist(const char *plistFile){
    map<string, int>::iterator iter = _plists.find(plistFile);
    if (iter != _plists.end()) {
         ++(iter->second);
    }else{
        _plists.insert(std::pair<string, int>(plistFile,1));
    }
}

void ResourceManager::releaseLayerTextures(cocos2d::CCNode* node){
    CCTextureCache* textureCache = cocos2d::CCTextureCache::sharedTextureCache();
    
    map<cocos2d::CCNode*, set<string> >::iterator itNodeTextures = _nodeTextures.find(node);
    if (itNodeTextures != _nodeTextures.end()) {
        set<string> imageset = itNodeTextures->second;
        for (set<string>::iterator itSet = imageset.begin(); itSet != imageset.end(); ++itSet) {
            map<string, int>::iterator it = _textures.find(*itSet);
            if (it != _textures.end()) {
                (it->second)-- ;
                if (it->second == 0) {
                    textureCache->removeTextureForKey(it->first.c_str());
                    _textures.erase(it);
                }
            }
        }
        _nodeTextures.erase(itNodeTextures);
    }
}

void ResourceManager::releaseLayerPlist(cocos2d::CCNode* node){
    CCSpriteFrameCache* frameCache = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache();
    
    map<cocos2d::CCNode*, set<string> >::iterator itNodePlists = _nodePlists.find(node);
    if (itNodePlists != _nodePlists.end()) {
        set<string> plistSet = itNodePlists->second;
        for (set<string>::iterator itSet = plistSet.begin(); itSet != plistSet.end(); ++itSet) {
            map<string, int>::iterator it = _plists.find(*itSet);
            if (it != _plists.end()) {
                (it->second)--;
                if (it->second == 0) {
                    frameCache->removeSpriteFrameByName(it->first.c_str());
                    _plists.erase(it);
                }
            }
        }
        _nodePlists.erase(itNodePlists);
    }
    
}

CCScale9ProgressBar* ResourceManager::createScale9ProgressBar(cocos2d::CCRect capInsets, const char* file,cocos2d::CCNode* node, bool isGlobalTexture /* = false*/){
    addTexture(file, node, isGlobalTexture);
    CCSpriteFrame *frame = createFrame(file,node);
    CCRect r= frame->getRect();
    capInsets.origin.x = capInsets.origin.x + r.origin.x;
    capInsets.origin.y = capInsets.origin.y + r.origin.y;
    return CCScale9ProgressBar::createWithSpriteFrame(frame, capInsets);
}

extension::CCScale9Sprite* ResourceManager::createScale9(const char *file,cocos2d::CCNode* node,bool isGlobalTexture/* = false*/){
    addTexture(file, node, isGlobalTexture);
    return extension::CCScale9Sprite::createWithSpriteFrame(createFrame(file,node));
//    extension::CCScale9Sprite::createWithSpriteFrame(file);
}

//extension::CCScale9Sprite* ResourceManager::createScale9(const char *file, cocos2d::CCRect rect, cocos2d::CCRect capInsets,cocos2d::CCNode* node,bool isGlobalTexture/* = false*/){
//    addTexture(file, node, isGlobalTexture);
//    return extension::CCScale9Sprite:: createWithSpriteFrame(createFrame(file,node), rect, capInsets);
//}

extension::CCScale9Sprite* ResourceManager::createScale9(cocos2d::CCRect capInsets, const char *file,cocos2d::CCNode* node,bool isGlobalTexture/* = false*/){
    addTexture(file, node, isGlobalTexture);
    CCSpriteFrame *frame = createFrame(file,node);
    CCRect r= frame->getRect();
    capInsets.origin.x = capInsets.origin.x + r.origin.x;
    capInsets.origin.y = capInsets.origin.y + r.origin.y;
    return extension::CCScale9Sprite::createWithSpriteFrame(frame, capInsets);
    //(capInsets,createFrame(file,node));
}

CCScale9ProgressBar* ResourceManager::createScale9ProgressBar(const char *file,cocos2d::CCNode* node,bool isGlobalTexture/* = false*/){
    addTexture(file, node, isGlobalTexture);
    return CCScale9ProgressBar::createWithSpriteFrame(createFrame(file, node));
//    CCScale9ProgressBar::create(file);
}


//ProgressBar* ResourceManager::createProgressBar(const char *bgName, const char *fgName, float width, cocos2d::CCRect &rect, cocos2d::CCRect &capRect,cocos2d::CCNode* node,bool isGlobalTexture/* = false*/){
//   addTexture(bgName, node, isGlobalTexture);
//    addTexture(fgName, node, isGlobalTexture);
//    return ProgressBar::create(bgName, fgName, width, rect, capRect);
//}
//
//ProgressBar* ResourceManager::createProgressBar(const char *bgName, const char *fgName, float width,cocos2d::CCNode* node,bool isGlobalTexture/* = false*/){
//    addTexture(bgName, node, isGlobalTexture);
//    addTexture(fgName, node, isGlobalTexture);
//    return ProgressBar::create(bgName, fgName, width);
//}

CCSprite* ResourceManager::createSprite(const char* fileName ,cocos2d::CCNode* node, bool isGlobalTexture /* = false*/) {
    addTexture(fileName, node, isGlobalTexture);
    // search pictures from CCSpriteFrameCache first, if not found, search from Resource then
    CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(fileName);
    CCSprite* sprite = NULL;
    
    if (frame != NULL) {
        sprite = CCSprite::createWithSpriteFrame(frame);
    } else {
        sprite = CCSprite::create(fileName);
    }
    return sprite;
}

CCSpriteFrame* ResourceManager::createFrame(const char* fileName ,cocos2d::CCNode* node,bool isGlobalTexture/* = false*/) {
    addTexture(fileName, node, isGlobalTexture);
    //search pictures from CCSpriteFrameCache first, if not found, search from Resource then
    CCSpriteFrameCache* frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
    CCSpriteFrame* frame = frameCache->spriteFrameByName(fileName);
    
    if (frame == NULL) {
        CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage(fileName);
        CCRect rect = CCRectZero;
        rect.size = texture->getContentSize();
        frame = CCSpriteFrame::createWithTexture(texture, rect);
        frameCache->addSpriteFrame (frame, fileName); // cache the created frame for reuse
        addPlistFile(fileName, node, isGlobalTexture);
    }
    return frame;
}

CCLabelAtlas* ResourceManager::createCCLabelAtlas(const char* label, const char* charMapFile, unsigned int itemWidth, int unsigned itemHeight, unsigned int startCharMap,cocos2d::CCNode* node,bool isGlobalTexture /*= false*/) {
    addTexture(charMapFile, node, isGlobalTexture);
    CCLabelAtlas* ret = CCLabelAtlas::create(label, charMapFile, itemWidth, itemHeight, startCharMap);
    return ret;
}

void ResourceManager::loadPlist(const char *plist, const char *textureFileName,cocos2d::CCNode* node,bool isGlobalTexture/* = false*/){
    addTexture(textureFileName, node, isGlobalTexture);     
    addPlistFile(plist, node, isGlobalTexture);
    CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->addSpriteFramesWithFile(plist, textureFileName);
    
}

CCMenuItemSprite* ResourceManager::getStretchButton(const char *normal, const char *selected,const char *disabled,float width,CCNode* node,bool isGlobalTexture/* = false*/){
    
    cocos2d::extension::CCScale9Sprite *icon_a = createScale9(normal,node,isGlobalTexture);
    cocos2d::extension::CCScale9Sprite *icon_b = createScale9(selected,node,isGlobalTexture);
    cocos2d::extension::CCScale9Sprite *icon_c = NULL;
    if (disabled != NULL) {
        icon_c = createScale9(disabled,node,isGlobalTexture);
        icon_c->setContentSize(CCSize(width, icon_c->getContentSize().height));
    }
    
    icon_a->setContentSize(CCSize(width ,icon_a->getContentSize().height));
    icon_b->setContentSize(CCSize(width,icon_b->getContentSize().height));
    
    CCMenuItemSprite* button = CCMenuItemSprite::create(icon_a, icon_b,icon_c);
    return button;
}

//ScrollBar* ResourceManager::create(const char *bg, const char *fg, float maxLength,CCNode* node,bool isGlobalTexture /*= false*/){
//    addTexture(bg, node, isGlobalTexture);
//    addTexture(fg, node, isGlobalTexture);
//    return ScrollBar::create(bg, fg, maxLength);
//}

CCShaderEffectSprite *ResourceManager::createShaderEffectSprite(const char *fileName, string shaderType, cocos2d::CCNode* node, bool isGlobalTexture ){
    addTexture(fileName, node, isGlobalTexture);
    CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(fileName);
    CCShaderEffectSprite *sprite = NULL;
    
    if (frame != NULL) {
        sprite = CCShaderEffectSprite::createWithSpriteFrame(frame, shaderType);
     //   CCSprite::createWithSpriteFrame(frame);
    } else {
        sprite = CCShaderEffectSprite::create(fileName, shaderType);
//        sprite = CCSprite::create(fileName);
    }
    return sprite;
}

//CCMenuItemSprite *ResourceManager::getCommonButton(float width,CCNode* node,bool isGlobalTexture/* = false*/){
//    return getStretchButton(ResourceName::Images::building::UPGRADE_BTN, ResourceName::Images::building::UPGRADE_BTN, width,node,isGlobalTexture);
//}

