//
//  TGSpriterNode.h
//  motoGame
//
//  Created by xUanBing on 14-4-16.
//
//

#ifndef __motoGame__TGSpriterNode__
#define __motoGame__TGSpriterNode__


#include "cocos2d.h"
#include "platform/CCSAXParser.h"
#include <string>
#include "ParticleEffect.h"
#include "ArmatureAnim.h"
#include "CCDictionary2.h"

USING_NS_CC;

class TGSpriterConfigNodeCC{
public:
	TGSpriterConfigNodeCC();
	virtual ~TGSpriterConfigNodeCC();
public:
	std::string _name;
	std::string _value;
	TGSpriterConfigNodeCC * _parent;
	std::vector<TGSpriterConfigNodeCC *> _children;
};

class TGSpriterConfigNodeDict{
public:
	TGSpriterConfigNodeDict():_root(NULL){}
	virtual ~TGSpriterConfigNodeDict();
	TGSpriterConfigNodeCC * getRoot(){return _root;}
	void  setRoot(TGSpriterConfigNodeCC *root){	if(_root){delete _root;}	_root=root;	}
private:
	TGSpriterConfigNodeCC * _root;
public:
	std::string 			_type;
};

class TGSpriterConfigNodeDictMap{
public:
	TGSpriterConfigNodeDictMap(){}
	virtual ~TGSpriterConfigNodeDictMap();
	void  setObject(TGSpriterConfigNodeDict *root,const std::string & key);
	TGSpriterConfigNodeDict*  objectForKey(const std::string & key);
private:
	std::map<std::string,TGSpriterConfigNodeDict*> 			_mapValue;
};


// holds the sprites associated with a given frame
class TGSpriterFrame:public CCObject {
public:
	TGSpriterFrame();
	virtual ~TGSpriterFrame();
	static TGSpriterFrame * spriterFrame();
	void addSprite(CCSprite * sprite);
	void setVisible(bool visible);
	CCObject* copyWithZone(CCZone* pZone);
    void setFlipX(bool bFlipX);
    void setFlipY(bool bFlipY);
    bool isFlipX() const;
    bool isFlipY() const;
    
public:
	CCArray * sprites_;
	CC_SYNTHESIZE_RETAIN(CCString *, name_, Name);
	CC_SYNTHESIZE(CCSize, _contentSize, ContentSize);
    
private:
    bool m_bFlipX;
    bool m_bFlipY;
};

// holds the frames for a given animation
class SpriterAnimationDelegate{
public:
	virtual void animationFinished(std::string name)=0;
	virtual void animationFrameChanged(std::string anim_name,std::string lastframe,std::string name)=0;
	
};

class TGSpriterAnimation : public CCObject {
public:
	TGSpriterAnimation();
	virtual ~TGSpriterAnimation();
	static TGSpriterAnimation * spriterAnimation();
	void addFrame(TGSpriterFrame* frame, double duration);
	void hide();
	void update(float dt);
	double frameDurationsSum();
	TGSpriterFrame * getCurFrame();
    void reset();
    
public:
	CCArray * frames_;
	CCArray * frameDurations_;
	int frameIdx_;
    double frameDuration_;
	CC_SYNTHESIZE_RETAIN(CCString *, name_, Name);
	CC_SYNTHESIZE(SpriterAnimationDelegate *, animationDelegate_, AnimationDelegate);
	
};

class TGSpriterNode;

class SpriterNodeDelegate{
    
public:
	virtual void animationFinished(TGSpriterNode * spriterNode,std::string name)=0;
	virtual void animationFrameChanged(TGSpriterNode * spriterNode
									   ,std::string anim_name,std::string lastframe,std::string name)=0;
};

class TGSpriterNode : public CCNode, public CCSAXDelegator, public SpriterAnimationDelegate, public BaseEffect, public CCRGBAProtocol ,public AnimationDelegateExt {
    
public:
	TGSpriterNode();
	virtual ~TGSpriterNode();
    
	static TGSpriterNode * spriterNodeWithDictionaryFrameName(CCString* scmlFile,TGSpriterConfigNodeDict* dict);
	static TGSpriterNode * spriterNodeWithSpriteFileName(CCString* spriteFileName);
	static TGSpriterNode * spriterNodeWithSpriteFrameName(CCString* spriteFrameName);
	static TGSpriterNode * spriterNodeWithScmlFile(CCString* scmlFile);
	static TGSpriterNode * spriterNodeWithScmlFileAndSpriteFrame(CCString * scmlFile);
	static TGSpriterNode * spriterNodeWithAnimateEidtorXml(CCString* scmlFile);
	static TGSpriterNode * spriterNodeWithAnimateEidtorXmlAndSpriteFrame(CCString * scmlFile);
    static TGSpriterNode * spriterNodeWithArmature(CCDictionary2 * info,const float positionReadScale = 1.0f);
    
	CCString * getCurAnimationName()const;
	CCString * getCurFrameName()const;
    
	bool runAnimation(CCString* animation,bool stopFirst=true);
	void showFrame(CCString* frameName);
	void showFrameByIndex(int index);
    void setCurFrameFlipX(bool bFlipX);
    void setCurFrameFlipY(bool bFlipY);
    void setFlipX(CCString* frameName, bool bFlipX);
    void setFlipY(CCString* frameName, bool bFlipY);
    bool isCurFrameFlipX() const;
    bool isCurFrameFlipY() const;
    void setFlipX(bool bFlipX);
    void setFlipY(bool bFlipY);
    
    void setChildrenAnchorPoint(const CCPoint& point);
    
    CCSprite* getDefaultSpriter();
	TGSpriterFrame* getCurFrame() const;
    
	CCString * getAnimationNameByKey(const std::string & key);
	CCString * getFrameNameByKey(const std::string & key);
    double getFrameDurationsSumByKey(const std::string & key) const;
    
    
	void setAnimationNameWithKey(CCString *name,const std::string & key);
	void setFrameNameWithKey(CCString *name,const std::string & key);
    
	void Test();
    
public:
    virtual void onAnimationEvent(void * animation, const char * eventType, const char * movementID);
    
public:
	CC_SYNTHESIZE(bool, autoRemoveOnFinish_, AutoRemoveOnFinish);
	CC_SYNTHESIZE(SpriterNodeDelegate *, spriterNodeDelegate_, SpriterNodeDelegate_);
    
public:
    virtual void startElement(void *ctx, const char *name, const char **atts);
    virtual void endElement(void *ctx, const char *name);
    virtual void textHandler(void *ctx, const char *s, int len);
	void handleAutoRemoveOnFinish();
    
	bool initNodeWithSpriteFileName(CCString* sprite);
	bool initNodeWithSpriteFrameName(CCString* sprite);
	bool initNodeWithScmlFile(CCString* scmlFile);
	bool initNodeWithScmlFileAndSpriteFrame(CCString * scmlFile);
	bool initNodeWithAnimateEidtorXml(CCString* plistFile);
	bool initNodeWithAnimateEidtorXmlAndSpriteFrame(CCString * plistFile);
	bool initNodeWithDictionaryFrameName(CCString* scmlFile,TGSpriterConfigNodeDict * dict);
    bool initNodeWithArmatureAndSpriteFrame(CCDictionary2 * info,const float positionReadScale);
    
	void update(float dt);
	virtual void stopAnimation();
	virtual void setVisible(bool bVisible);
    
    //SpriterAnimationDelegate
	virtual void animationFinished(std::string name);
	virtual void animationFrameChanged(std::string anim_name,std::string lastframe,std::string name);
	
	TGSpriterConfigNodeDict*  loadWithScmlFileAndSpriteFrame(const std::string & scmlFile);
	TGSpriterConfigNodeDict*  loadWithAnimateEidtorXmlAndSpriteFrame(const std::string & scmlFile);
    
private:
	void finishedinitNodeWithScmlFile();
	void finishedinitNodeWithAnimateEidtorXml();
    
private:
	bool _releaseRoot;
	CCRect boxRect;
    CCDictionary2 * animations_; // {name: TGSpriterAnimation,...}
    CCDictionary2 * frames_; // {name: TGSpriterFrame,..}
    
    TGSpriterAnimation * curAnimation_;
	TGSpriterFrame *  curFrame_;
    bool useBatchNode_;
	bool useAnimateEditor;
    
    // parsing vars
    TGSpriterConfigNodeCC * configRoot_;
    TGSpriterConfigNodeCC * curConfigNode_;
	CCDictionary2 * animationNames_; /*保存配置文件中动画名和实际animations_的名字的映射*/
	CCDictionary2 * frameNames_; /*保存配置文件中frame名和实际animations_的名字的映射*/
    
    ArmatureAnim * armatureAnim_;
    std::string    armature_lastframe_;
    
protected:
    virtual void setShaderProgram(cocos2d::CCGLProgram *var);
    
public: //CCRGBAProtocol
    virtual void setColor(const ccColor3B& color);
    virtual const ccColor3B& getColor(void);
    virtual GLubyte getOpacity(void);
    virtual void setOpacity(GLubyte opacity);
    virtual void setOpacityModifyRGB(bool bValue);
    virtual bool isOpacityModifyRGB(void);
    
private:
    ccColor3B _color;
    GLubyte _opacity;
    
};

typedef TGSpriterNode  AnimationEffect;






#endif /* defined(__motoGame__TGSpriterNode__) */
