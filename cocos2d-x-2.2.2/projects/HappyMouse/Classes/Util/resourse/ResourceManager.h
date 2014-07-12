

#ifndef DinosaurIos_ResourceManager_h
#define DinosaurIos_ResourceManager_h

#include <set>
#include <string>
#include "cocos-ext.h"
using std::set;
using std::string;
using std::map;
class ProgressBar;
class ScrollBar;
class CCScale9ProgressBar;
class CCShaderEffectSprite;

class ResourceManager {
public:
    
    static ResourceManager* getInstance() {
        static ResourceManager instance;
        return &instance;
    }
    
    void releaseLayerTextures(cocos2d::CCNode* node);
    void releaseLayerPlist(cocos2d::CCNode* node);
    
private:
    void addGlobalTexture(const char* imgFile);
    void addGlobalPlistFile(const char* plistFile);

private:
    ResourceManager();
    ResourceManager(const ResourceManager&);
    ResourceManager& operator=(const ResourceManager&);
private:
    void accumulateToTextures(const char* imgFile);
    void accumulateToPlist(const char *plistFile);
    void addTexture(const char* imgFile,cocos2d::CCNode* node,bool isGlobalTexture);
    void addPlistFile(const char* plistFile,cocos2d::CCNode* node,bool isGlobalTexture);


public:
    void loadPlist(const char* plist, const char* textureFileName,cocos2d::CCNode* node, bool isGlobalTexture = false);
    cocos2d::CCSprite* createSprite(const char* fileName,cocos2d::CCNode* node,bool isGlobalTexture = false);
    cocos2d::CCSpriteFrame* createFrame(const char* fileName,cocos2d::CCNode* node,bool isGlobalTexture = false);
    cocos2d::CCLabelAtlas* createCCLabelAtlas(const char* label, const char* charMapFile, unsigned int itemWidth, int unsigned itemHeight, unsigned int startCharMap,cocos2d::CCNode* node,bool isGlobalTexture = false);
    cocos2d::extension::CCScale9Sprite* createScale9(const char *file,cocos2d::CCNode* node,bool isGlobalTexture = false);
    cocos2d::extension::CCScale9Sprite* createScale9(cocos2d::CCRect capInsets, const char *file,cocos2d::CCNode* node,bool isGlobalTexture = false);
    
    CCScale9ProgressBar* createScale9ProgressBar(const char* file,cocos2d::CCNode* node, bool isGlobalTexture = false);
    CCScale9ProgressBar* createScale9ProgressBar(cocos2d::CCRect capInsets, const char* file,cocos2d::CCNode* node, bool isGlobalTexture = false);
    
    cocos2d::CCMenuItemSprite* getStretchButton(const char *normal, const char *selected,const char *disabled,float width,cocos2d::CCNode* node, bool isGlobalTexture = false);
    
    CCShaderEffectSprite *createShaderEffectSprite(const char* fileName,string shaderType,cocos2d::CCNode* node, bool isGlobalTexture = false);
    
//    cocos2d::extension::CCScale9Sprite*  createScale9(const char *file, cocos2d::CCRect rect, cocos2d::CCRect capInsets,cocos2d::CCNode* node,bool isGlobalTexture = false);
//    ProgressBar* createProgressBar(const char *bgName, const char *fgName, float width, cocos2d::CCRect &rect, cocos2d::CCRect &capRect,cocos2d::CCNode* node,bool isGlobalTexture = false);
//    ProgressBar* createProgressBar(const char *bgName, const char *fgName, float width,cocos2d::CCNode* node,bool isGlobalTexture = false);
//    cocos2d::CCMenuItemSprite *getCommonButton(float width,cocos2d::CCNode* node,bool isGlobalTexture = false);
//    ScrollBar* create(const char *bg, const char *fg, float maxLength,cocos2d::CCNode* node, bool isGlobalTexture = false);

private:
    map<string,int> _textures;
    map<string,int> _plists;
    map<cocos2d::CCNode*, set<string> > _nodeTextures;
    map<cocos2d::CCNode*, set<string> > _nodePlists;
    
    set<string> _globalTextures;
    set<string> _globalPlists;
};

#endif
