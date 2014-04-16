//
//  TGSpriterNode.cpp
//  motoGame
//
//  Created by xUanBing on 14-4-16.
//
//

#include "TGSpriterNode.h"
#include "DoubleNumber.h"

#include "tinyxml.h"
#include "GameUtils.h"
#include "SPConstValue.h"
#include "CCDictionary2.h"

#define KSpriterSCML         "spriter_scml"			/*表示节点采用一个图片文件和一个scml文件创建*/
#define KSpriteWithSCMLFrame "spriter_scml_frame"	/*表示节点采用framecache中frame和一个scml文件创建*/
#define KAnimateWithXML      "animate_editor_xml"			/*表示节点采用一个图片文件和一个xml文件创建*/
#define KAnimateWithXMLFrame "animate_editor_xml_frame"	    /*表示节点采用framecache中frame和一个xml文件创建*/

#define KAnimateWithArmatureFrame "animate_armature_frame"

#pragma mark Support Classes

TGSpriterConfigNodeCC::TGSpriterConfigNodeCC()
:_parent(NULL)
{
	
}

TGSpriterConfigNodeCC::~TGSpriterConfigNodeCC(){
	//释放子节点
	std::vector<TGSpriterConfigNodeCC *>::iterator iter;
	for (iter=_children.begin(); iter!=_children.end(); iter++) {
		delete *iter;
	}
	_children.clear();
    
}


TGSpriterConfigNodeDict::~TGSpriterConfigNodeDict(){
	if (_root) {
		delete _root;
		_root=NULL;
	}
}


TGSpriterConfigNodeDictMap::~TGSpriterConfigNodeDictMap(){
	//释放子节点
	std::map<std::string,TGSpriterConfigNodeDict*>::iterator iter;
	for (iter=_mapValue.begin(); iter!=_mapValue.end(); iter++) {
		delete (*iter).second;
	}
	_mapValue.clear();
}


TGSpriterConfigNodeDict * TGSpriterConfigNodeDictMap::objectForKey(const std::string & key){
	//释放子节点
	std::map<std::string,TGSpriterConfigNodeDict*>::iterator iter=_mapValue.find(key);
	if (iter!=_mapValue.end()) {
		return (*iter).second;
	}
	return NULL;
}

void  TGSpriterConfigNodeDictMap::setObject(TGSpriterConfigNodeDict *root,const std::string & key){
    
	_mapValue[key]=root;
}



TGSpriterFrame::TGSpriterFrame()
:CCObject(),
name_(NULL),
m_bFlipX(false)
,m_bFlipY(false){
	sprites_ = CCArray::create();
	sprites_->retain();
}

TGSpriterFrame::~TGSpriterFrame(){
	if (sprites_) {
		sprites_->removeAllObjects();
		sprites_->release();
		sprites_=NULL;
	}
	CC_SAFE_RELEASE_NULL(name_);
}

// holds the sprites associated with a given frame
TGSpriterFrame * TGSpriterFrame::spriterFrame() {
	TGSpriterFrame * frame=new TGSpriterFrame();
	frame->autorelease();
    return frame;
}

void TGSpriterFrame::addSprite(CCSprite* sprite) {
    sprites_->addObject(sprite);
}

void TGSpriterFrame::setVisible(bool visible) {
	
	CCSprite *tmpSprite=NULL;
	
	if (sprites_) {
		int count=sprites_->count();
		for ( int i=0;i < count;i++) {
			CCSprite * sprite=(CCSprite *)sprites_->objectAtIndex(i);
			sprite->setVisible(visible);
			tmpSprite=sprite;
		}
	}
}

CCObject* TGSpriterFrame::copyWithZone(CCZone* pZone){
	TGSpriterFrame * frame=new TGSpriterFrame();
	int count=sprites_->count();
	
	//TODO：注意这个地方的拷贝
	frame->sprites_=CCArray::createWithCapacity(count);
	for (int i=0; i<count; i++) {
		frame->sprites_->addObject(sprites_->objectAtIndex(i));
	}
	frame->sprites_->retain();
	frame->name_=CCString::create(name_->getCString());
	frame->name_->retain();
    return frame;
}

void TGSpriterFrame::setFlipX(bool bFlipX) {
    if (m_bFlipX != bFlipX && sprites_) {
		int count=sprites_->count();
		for (int i = 0;i < count; ++i) {
			CCSprite *sprite=(CCSprite*)sprites_->objectAtIndex(i);
            sprite->setFlipX(!sprite->isFlipX());
            float px = sprite->getPositionX();
            sprite->setRotation(180 - sprite->getRotation());
            sprite->setAnchorPoint(CCPoint(1 - sprite->getAnchorPoint().x, sprite->getAnchorPoint().y));
            sprite->setPositionX(-px);
		}
        m_bFlipX = bFlipX;
	}
}

void TGSpriterFrame::setFlipY(bool bFlipY) {
    if (m_bFlipY != bFlipY && sprites_) {
		int count=sprites_->count();
		for (int i = 0; i < count; ++i) {
			CCSprite *sprite=(CCSprite*)sprites_->objectAtIndex(i);
            sprite->setFlipY(!sprite->isFlipY());
            float py = sprite->getPositionY();
            sprite->setRotation(180 - sprite->getRotation());
            sprite->setAnchorPoint(CCPointMake(sprite->getAnchorPoint().x, 1 - sprite->getAnchorPoint().y));
            sprite->setPositionY(-py);
		}
        m_bFlipY = bFlipY;
	}
}

bool TGSpriterFrame::isFlipX() const {
    return m_bFlipX;
}

bool TGSpriterFrame::isFlipY() const {
    return m_bFlipY;
}

// holds the frames for a given animation
TGSpriterAnimation::TGSpriterAnimation():CCObject(),name_(NULL){
    
	frames_ = CCArray::create();
	frames_->retain();
	frameDurations_ = CCArray::create();
	frameDurations_->retain();
	frameIdx_ = 0;
	frameDuration_ = 0;
	animationDelegate_=NULL;
    
}

TGSpriterAnimation::~TGSpriterAnimation(){
    
	if (frames_) {
		frames_->removeAllObjects();
		frames_->release();
		frames_=NULL;
	}
    
	if (frameDurations_) {
		frameDurations_->removeAllObjects();
		frameDurations_->release();
		frameDurations_=NULL;
	}
	CC_SAFE_RELEASE_NULL(name_);
}

TGSpriterAnimation *  TGSpriterAnimation::spriterAnimation() {
	TGSpriterAnimation * frame=new TGSpriterAnimation();
	frame->autorelease();
    return frame;
}

void TGSpriterAnimation::addFrame(TGSpriterFrame * frame,double duration){
    frames_->addObject(frame);
    frameDurations_->addObject(CCDoubleNumber::doubleNumberWithValue(duration));
    frameIdx_ = frames_->count() - 1;
}

void TGSpriterAnimation::hide(){
	((TGSpriterFrame *)frames_->objectAtIndex(frameIdx_))->setVisible(false);
}

void TGSpriterAnimation::reset(){
	frameIdx_=0;
	frameDuration_=0;
	if (frames_->count()>0) {
		((TGSpriterFrame *)frames_->objectAtIndex(frameIdx_))->setVisible(true);
	}
}

double TGSpriterAnimation::frameDurationsSum(){
	double _frameDurationsSum=0;
	for (int i=0;i<frames_->count();i++) {
		_frameDurationsSum=_frameDurationsSum+(((CCDoubleNumber *)frameDurations_->objectAtIndex(i))->getValue());
	}
	return _frameDurationsSum;
}

void TGSpriterAnimation::update(float dt) {
	
    frameDuration_ += dt;
	
	double  tmp_duration=((CCDoubleNumber *)frameDurations_->objectAtIndex(frameIdx_))->getValue();
	
    if (frameDuration_ > tmp_duration) {
		int tmp=frameIdx_+1;
		int count=frames_->count();
		TGSpriterFrame * lastframe=((TGSpriterFrame *)frames_->objectAtIndex(frameIdx_));
 		lastframe->setVisible(false);
        frameIdx_ = tmp % count;
		
        TGSpriterFrame * curframe=((TGSpriterFrame *)frames_->objectAtIndex(frameIdx_));
		curframe->setVisible(true);
		
        frameDuration_=0;
		
		if (animationDelegate_) {
			animationDelegate_->animationFrameChanged(this->name_->getCString()
													  ,lastframe->getName()->getCString()
													  ,curframe->getName()->getCString());
		}
		
		if ((frameIdx_ == 0) && (tmp == count)) {
			if (animationDelegate_) {
				animationDelegate_->animationFinished(this->name_->getCString());
			}
		}
    }
}

TGSpriterFrame * TGSpriterAnimation::getCurFrame(){
	if (frames_) {
		int count=frames_->count();
		if (count > 0 && frameIdx_ >=0 && frameIdx_ <count) {
			return ((TGSpriterFrame *)frames_->objectAtIndex(frameIdx_));
		}
	}
	return NULL;
}


#pragma mark -------------------------------------TGSpriterNode--------------------------------------------


TGSpriterNode::TGSpriterNode()
:CCNode()
,BaseEffect()
,autoRemoveOnFinish_(false)
,spriterNodeDelegate_(NULL)
,animations_(NULL)
,frames_(NULL)
,curAnimation_(NULL)
,curFrame_(NULL)
,useBatchNode_(false)
,useAnimateEditor(false)
,_releaseRoot(true)
,configRoot_(NULL)
,curConfigNode_(NULL)
,animationNames_(NULL)/*保存配置文件中动画名和实际animations_的名字的映射*/
,frameNames_(NULL)/*保存配置文件中frame名和实际animations_的名字的映射*/
,_opacity(255)
,armatureAnim_(NULL)
{
	boxRect=CCRect();
}

TGSpriterNode::~TGSpriterNode(){
    if (armatureAnim_) {
        armatureAnim_->stopAnimation();
    }
    
	if (_releaseRoot && configRoot_) {
		delete configRoot_;
		configRoot_=NULL;
	}
    
	if (animationNames_) {
        animationNames_->removeAllObjects();
        animationNames_->release();
		animationNames_=NULL;
    }
	
	if (frameNames_) {
        frameNames_->removeAllObjects();
        frameNames_->release();
		frameNames_=NULL;
    }
	
	if (animations_) {
        animations_->removeAllObjects();
        animations_->release();
		animations_=NULL;
    }
	
	if (frames_) {
        frames_->removeAllObjects();
        frames_->release();
		frames_=NULL;
    }
}

void TGSpriterNode::handleAutoRemoveOnFinish(){
	if (_effectDelegate){
		_effectDelegate->handleEffectAutoRemoveOnFinish(this);
	}
}

CCString * TGSpriterNode::getAnimationNameByKey(const std::string & key){
	if (animationNames_) {
		return (CCString *)animationNames_->objectForKey(key);
	}
	return NULL;
}


double TGSpriterNode::getFrameDurationsSumByKey(const std::string & key) const {
    if(animations_) {
        TGSpriterAnimation* animation = (TGSpriterAnimation *)animations_->objectForKey(key);
        if (animation) {
            return animation->frameDurationsSum();
        }
    }
    return 0;
}

CCString * TGSpriterNode::getFrameNameByKey(const std::string & key){
	if (frameNames_) {
		return (CCString *)frameNames_->objectForKey(key);
	}
	return NULL;
}

void TGSpriterNode::setAnimationNameWithKey(CCString *name,const std::string & key){
    
	if (!name) {
		return;
	}
	if (!animationNames_) {
		animationNames_ = CCDictionary2::create();
		animationNames_->retain();
	}
	animationNames_->setObject(name, key);
}

void TGSpriterNode::setFrameNameWithKey(CCString *name,const std::string & key){
	if (!name) {
		return;
	}
	if (!frameNames_) {
		frameNames_ = CCDictionary2::create();
		frameNames_->retain();
	}
	frameNames_->setObject(name, key);
}

TGSpriterNode* TGSpriterNode::spriterNodeWithSpriteFileName(CCString* spriteFileName){
    TGSpriterNode *node = new TGSpriterNode();
	node->initNodeWithSpriteFileName(spriteFileName);
	node->autorelease();
    return node;
}

TGSpriterNode * TGSpriterNode::spriterNodeWithSpriteFrameName(CCString* spriteFrameName){
	TGSpriterNode * node=new TGSpriterNode;
	node->initNodeWithSpriteFrameName(spriteFrameName);
	node->autorelease();
    return node;
}

TGSpriterNode * TGSpriterNode::spriterNodeWithScmlFile(CCString* scmlFile) {
	
	TGSpriterNode * node=new TGSpriterNode;
	node->initNodeWithScmlFile(scmlFile);
	node->autorelease();
    return node;
}

TGSpriterNode * TGSpriterNode::spriterNodeWithScmlFileAndSpriteFrame(CCString * scmlFile) {
	
	TGSpriterNode * node=new TGSpriterNode;
	node->initNodeWithScmlFileAndSpriteFrame(scmlFile);
	node->autorelease();
    return node;
}

TGSpriterNode * TGSpriterNode::spriterNodeWithAnimateEidtorXml(CCString* scmlFile) {
	
	TGSpriterNode * node=new TGSpriterNode;
	node->initNodeWithAnimateEidtorXml(scmlFile);
	node->autorelease();
    return node;
}

TGSpriterNode * TGSpriterNode::spriterNodeWithAnimateEidtorXmlAndSpriteFrame(CCString * scmlFile) {
	
	TGSpriterNode * node=new TGSpriterNode;
	node->initNodeWithAnimateEidtorXmlAndSpriteFrame(scmlFile);
	node->autorelease();
    return node;
}

bool TGSpriterNode::initNodeWithSpriteFileName(CCString* sprite){
	
	std::string delfautFrameName=sprite->getCString();
	
	frames_ = CCDictionary2::create();
	frames_->retain();
	animations_ = CCDictionary2::create();
	animations_->retain();
	TGSpriterFrame * spriterFrame = TGSpriterFrame::spriterFrame();
	CCSprite * _sprite = CCSprite::create(delfautFrameName.c_str());
	addChild(_sprite);
	spriterFrame->addSprite(_sprite);
	spriterFrame->setName(CCString::create(delfautFrameName));
	spriterFrame->setVisible(false);
	
	frames_->setObject(spriterFrame,delfautFrameName);
	
	this->setContentSize(_sprite->getContentSize());
	
	showFrame(sprite);
	
    return true;
}

bool TGSpriterNode::initNodeWithSpriteFrameName(CCString* sprite){
	
	std::string delfautFrameName=sprite->getCString();
	useBatchNode_ = true;
	
	frames_ = CCDictionary2::create();
	frames_->retain();
	
	animations_ = CCDictionary2::create();
	animations_->retain();
	
	TGSpriterFrame * spriterFrame = TGSpriterFrame::spriterFrame();
	CCSprite * _sprite = CCSprite::createWithSpriteFrameName(delfautFrameName.c_str());
	addChild(_sprite);
	spriterFrame->addSprite(_sprite);
	spriterFrame->setName(CCString::create(delfautFrameName));
	spriterFrame->setVisible(false);
	
	frames_->setObject(spriterFrame,delfautFrameName);
	this->setContentSize(_sprite->getContentSize());
	showFrame(sprite);
    return true;
}

bool TGSpriterNode::initNodeWithScmlFile(CCString* scmlFile){
	
	frames_ = CCDictionary2::create();
	frames_->retain();
	
	animations_ = CCDictionary2::create();
	animations_->retain();
	
//	const char * path = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(scmlFile->getCString());
    const char* path = CCFileUtils::sharedFileUtils()->fullPathForFilename(scmlFile->getCString()).c_str();
	
	CCSAXParser parser;
    if (false == parser.init("UTF-8") )
    {
        return false;
    }
    parser.setDelegator(this);
	
	
	configRoot_=new TGSpriterConfigNodeCC;
	configRoot_->_name="root";
	curConfigNode_=configRoot_;
	bool result=parser.parse(path);
	if (result) {
		finishedinitNodeWithScmlFile();
	}
    return result;
}


bool TGSpriterNode::initNodeWithScmlFileAndSpriteFrame(CCString * scmlFile){
	
	frames_ = CCDictionary2::create();
	frames_->retain();
	
	animations_ = CCDictionary2::create();
	animations_->retain();
    
	useBatchNode_ = true;
	
//	const char * path = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(scmlFile->getCString());
    const char* path = CCFileUtils::sharedFileUtils()->fullPathForFilename(scmlFile->getCString()).c_str();
	
	CCSAXParser parser;
    if (false == parser.init("UTF-8") )
    {
        return false;
    }
    parser.setDelegator(this);
    
	configRoot_=new TGSpriterConfigNodeCC;
	configRoot_->_name="root";
	curConfigNode_=configRoot_;
	bool result=parser.parse(path);
	if (result) {
		finishedinitNodeWithScmlFile();
	}
    return result;
}


bool TGSpriterNode::initNodeWithAnimateEidtorXml(CCString* plistFile){
	
	frames_ = CCDictionary2::create();
	frames_->retain();
	
	animations_ = CCDictionary2::create();
	animations_->retain();
	
//	const char * path = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(plistFile->getCString());
    const char* path = CCFileUtils::sharedFileUtils()->fullPathForFilename(plistFile->getCString()).c_str();

	CCSAXParser parser;
    if (false == parser.init("UTF-8") )
    {
        return false;
    }
    parser.setDelegator(this);
	
	useAnimateEditor=true;
	configRoot_=new TGSpriterConfigNodeCC;
	configRoot_->_name="root";
	curConfigNode_=configRoot_;
	bool result=parser.parse(path);
	if (result) {
		finishedinitNodeWithAnimateEidtorXml();
	}
    return result;
}


bool TGSpriterNode::initNodeWithAnimateEidtorXmlAndSpriteFrame(CCString * plistFile){
	
	frames_ = CCDictionary2::create();
	frames_->retain();
	
	animations_ = CCDictionary2::create();
	animations_->retain();
	
	useBatchNode_ = true;
	
//	const char * path = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(plistFile->getCString());
	const char* path = CCFileUtils::sharedFileUtils()->fullPathForFilename(plistFile->getCString()).c_str();
    
    
	CCSAXParser parser;
    if (false == parser.init("UTF-8") )
    {
        return false;
    }
    parser.setDelegator(this);
	useAnimateEditor=true;
	configRoot_=new TGSpriterConfigNodeCC;
	configRoot_->_name="root";
	curConfigNode_=configRoot_;
	bool result=parser.parse(path);
	if (result) {
		finishedinitNodeWithAnimateEidtorXml();
	}
    return result;
}


TGSpriterConfigNodeDict* TGSpriterNode::loadWithScmlFileAndSpriteFrame(const std::string & scmlFile){
	
#if 0
	
	useBatchNode_ = true;
	const char * path = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(scmlFile.c_str());
	CCSAXParser parser;
    if (false == parser.init("UTF-8") )
    {
        return NULL;
    }
    parser.setDelegator(this);
	configRoot_=new TGSpriterConfigNodeCC;
	configRoot_->_name="root";
	curConfigNode_=configRoot_;
	parser.parse(path);
	
	TGSpriterConfigNodeDict* dict=new TGSpriterConfigNodeDict;
	dict->setRoot(configRoot_);
	dict->_type=KSpriteWithSCMLFrame;
	configRoot_=NULL;
	
	return dict;
	
	
#else
	
	
	useBatchNode_ = true;
	
	configRoot_=new TGSpriterConfigNodeCC;
	configRoot_->_name="root";
	curConfigNode_=configRoot_;
    
	
	TGSpriterConfigNodeCC * rootTmp=new TGSpriterConfigNodeCC;
	rootTmp->_name="spriterdata";
	rootTmp->_parent=curConfigNode_;
	curConfigNode_->_children.push_back(rootTmp);
	
//	const char * path = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(scmlFile.c_str());
    const char* path = CCFileUtils::sharedFileUtils()->fullPathForFilename(scmlFile.c_str()).c_str();
    
	TiXmlDocument *document = new TiXmlDocument();
    if(document->LoadFile(path,TIXML_ENCODING_UTF8)){
	    
		TiXmlElement * root = document->RootElement();
		
		for (TiXmlElement * node = root->FirstChildElement(); node; node=node->NextSiblingElement()) {
			if (node->Type() == TiXmlNode::TINYXML_ELEMENT) {
				
				std::string nodeName=node->Value();
				
				if (nodeName.compare("char") == 0) {
					
					TGSpriterConfigNodeCC * charactor=new TGSpriterConfigNodeCC;
					charactor->_name=nodeName;
					charactor->_parent=rootTmp;
					rootTmp->_children.push_back(charactor);
					
					
					for (TiXmlElement * anim_node = node->FirstChildElement(); anim_node; anim_node=anim_node->NextSiblingElement()){
						
						if(anim_node->Type() == TiXmlNode::TINYXML_ELEMENT){
							
							std::string key=anim_node->Value();
							
							if(key.compare("anim") == 0){
								
								TGSpriterConfigNodeCC * anim=new TGSpriterConfigNodeCC;
								anim->_name=key;
								anim->_parent=charactor;
								charactor->_children.push_back(anim);
								
								//解析详情
								for (TiXmlElement * text_node = anim_node->FirstChildElement(); text_node; text_node=text_node->NextSiblingElement()){
									
									
									if(text_node->Type() == TiXmlNode::TINYXML_ELEMENT){
										
										std::string key=text_node->Value();
										
										if (key.compare("frame") == 0){
											
                                            TGSpriterConfigNodeCC * frame=new TGSpriterConfigNodeCC;
                                            frame->_name=key;
                                            frame->_parent=anim;
                                            anim->_children.push_back(frame);
											
											for (TiXmlElement * t_text_node = text_node->FirstChildElement(); t_text_node; t_text_node=t_text_node->NextSiblingElement()){
												
												if(t_text_node->Type() == TiXmlNode::TINYXML_ELEMENT){
													
													std::string key=t_text_node->Value();
													
													if (key.compare("duration") == 0 || key.compare("name") == 0) {
														
														TGSpriterConfigNodeCC * name=new TGSpriterConfigNodeCC;
														name->_name=key;
														name->_value=t_text_node->GetText();
														name->_parent=frame;
														frame->_children.push_back(name);
													}
												}
											}
										}
										else if (key.compare("name") == 0){
											
											TGSpriterConfigNodeCC * name=new TGSpriterConfigNodeCC;
											name->_name=key;
											name->_value=text_node->GetText();
											name->_parent=anim;
											anim->_children.push_back(name);
										}
									}
								}
							}
						}
					}
				}
				else if (nodeName.compare("frame") == 0){
					
					TGSpriterConfigNodeCC * frame=new TGSpriterConfigNodeCC;
					frame->_name=nodeName;
					frame->_parent=rootTmp;
					rootTmp->_children.push_back(frame);
					
					for (TiXmlElement * frame_node = node->FirstChildElement(); frame_node; frame_node=frame_node->NextSiblingElement()){
						
						if(frame_node->Type() == TiXmlNode::TINYXML_ELEMENT){
							
							std::string key=frame_node->Value();
							
							if (key.compare("sprite") == 0){
								
								TGSpriterConfigNodeCC * sprite=new TGSpriterConfigNodeCC;
								sprite->_name=key;
								sprite->_parent=frame;
								frame->_children.push_back(sprite);
								
								for (TiXmlElement * t_text_node = frame_node->FirstChildElement(); t_text_node; t_text_node=t_text_node->NextSiblingElement()){
									
									if(t_text_node->Type() == TiXmlNode::TINYXML_ELEMENT){
										
										std::string key=t_text_node->Value();
										if (key.compare("image") == 0 ||
											key.compare("x") == 0 ||
											key.compare("y") == 0 ||
											key.compare("width") == 0 ||
											key.compare("height") == 0 ||
											key.compare("color") == 0||
											key.compare("opacity") == 0||
											key.compare("angle") == 0||
											key.compare("xflip") == 0||
											key.compare("yflip") == 0) {
                                            
											std::string value=t_text_node->GetText();
											
											TGSpriterConfigNodeCC * name=new TGSpriterConfigNodeCC;
											name->_name=key;
											name->_value=value;
											name->_parent=sprite;
											sprite->_children.push_back(name);
										}
									}
								}
							}
							else if (key.compare("name") == 0){
								
								TGSpriterConfigNodeCC * name=new TGSpriterConfigNodeCC;
								name->_name=key;
								name->_value=frame_node->GetText();
								name->_parent=frame;
								frame->_children.push_back(name);
							}
						}
					}
				}
			}
		}
	}
	delete document;
	document=NULL;
    
	TGSpriterConfigNodeDict* dict=new TGSpriterConfigNodeDict;
	dict->setRoot(configRoot_);
	dict->_type=KSpriteWithSCMLFrame;
	configRoot_=NULL;
	
	return dict;
#endif
}

TGSpriterConfigNodeDict*  TGSpriterNode::loadWithAnimateEidtorXmlAndSpriteFrame(const std::string & scmlFile){
	
	useBatchNode_ = true;
//	const char * path = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(scmlFile.c_str());
    const char* path = CCFileUtils::sharedFileUtils()->fullPathForFilename(scmlFile.c_str()).c_str();
    
	CCSAXParser parser;
    if (false == parser.init("UTF-8") )
    {
        return NULL;
    }
    parser.setDelegator(this);
	useAnimateEditor=true;
	configRoot_=new TGSpriterConfigNodeCC;
	configRoot_->_name="root";
	curConfigNode_=configRoot_;
	parser.parse(path);
	
	TGSpriterConfigNodeDict* dict=new TGSpriterConfigNodeDict;
	dict->setRoot(configRoot_);
	dict->_type=KAnimateWithXMLFrame;
	configRoot_=NULL;
	
	return dict;
}



TGSpriterNode * TGSpriterNode::spriterNodeWithDictionaryFrameName(CCString* scmlFile,TGSpriterConfigNodeDict * dict) {
	
	TGSpriterNode * node=new TGSpriterNode;
	node->initNodeWithDictionaryFrameName(scmlFile,dict);
	node->autorelease();
    return node;
}


bool TGSpriterNode::initNodeWithDictionaryFrameName(CCString* scmlFile,TGSpriterConfigNodeDict * dict){
	
	frames_ = CCDictionary2::create();
	frames_->retain();
	animations_ = CCDictionary2::create();
	animations_->retain();
	if (dict) {
		TGSpriterConfigNodeDict* rootDic=dict;
		if (rootDic) {
			CCString * typeString=CCString::create(rootDic->_type);
			std::string type="";
			if (typeString) {
				type=typeString->getCString();
			}
			
			
			configRoot_=(TGSpriterConfigNodeCC *)rootDic->getRoot();
			if (configRoot_) {
				_releaseRoot=false;
				curConfigNode_=configRoot_;
				
				if (type == KAnimateWithXMLFrame){
					useBatchNode_ = true;
					finishedinitNodeWithAnimateEidtorXml();
				}
				else if (type == KSpriteWithSCMLFrame){
					useBatchNode_ = true;
					finishedinitNodeWithScmlFile();
				}
				else {
					return false;
				}
				
				return true;
			}
		}
	}
	return false;
}

TGSpriterNode * TGSpriterNode::spriterNodeWithArmature(CCDictionary2 * info,const float positionReadScale){
	TGSpriterNode * node=new TGSpriterNode;
    
	node->initNodeWithArmatureAndSpriteFrame(info,positionReadScale);
	node->autorelease();
    return node;
}

std::vector<std::string> stringToArrayByChar(const std::string & srcString ,const std::string & tag)
{
	std::vector<std::string> vals;
	std::string sizeString = srcString;
    size_t startPos = sizeString.find_first_of(tag);
    while(startPos != std::string::npos) {
		std::string tmp = sizeString.substr(0,startPos);
		vals.push_back(tmp);
        sizeString = sizeString.substr(startPos+tag.length());
		startPos = sizeString.find_first_of(tag);
    }
	
	return vals;
}

bool TGSpriterNode::initNodeWithArmatureAndSpriteFrame(CCDictionary2 * info,const float positionReadScale){
    armatureAnim_ = ArmatureAnim::create();
    armatureAnim_->setAnimDelegateExt(this);
    std::vector<sp::ImageInfo> list;
    CCArray * images = static_cast<CCArray *>(info->objectForKey("image"));
    if (images) {
        sp::ImageInfo inf;
        for (int i = 0; i < images->count(); i++) {
            CCDictionary2 * dict = static_cast<CCDictionary2 *>(images->objectAtIndex(i));
            inf.imagePath = static_cast<CCString *>(dict->objectForKey("image"))->m_sString;
            inf.plistPath = static_cast<CCString *>(dict->objectForKey("plist"))->m_sString;
            list.push_back(inf);
        }
    }
    CCString * armatureValue = (CCString *)info->objectForKey("armature");
    CCString * strValue = (CCString *)info->objectForKey("file");
    armatureAnim_->load(armatureValue->m_sString,list,strValue->m_sString,positionReadScale);
	
	CCString * sizeValue = (CCString *)info->objectForKey("size");
	if (sizeValue && sizeValue->length() > 0) {
		CCSize nodeSize = GameUtils::string2Size(sizeValue->m_sString);
		
		nodeSize.width *= positionReadScale;
		nodeSize.height *= positionReadScale;
		
		armatureAnim_->setMaxContentSize(nodeSize);
		this->setContentSize(nodeSize);
		armatureAnim_->setPosition(ccp(0, - nodeSize.height * 0.5));
	}
    this->addChild(armatureAnim_);
	
    return false;
}

#pragma mark Animation

bool TGSpriterNode::runAnimation(CCString* animation, bool stopFirst) {
	
	CCAssert(animation != NULL, "animation must not be null!");
	if (armatureAnim_) {
        armatureAnim_->runAnimation(animation->m_sString);
        return true;
    }
    
	bool ret=false;
	
	std::string new_animation=animation->getCString();
	
	this->unscheduleUpdate();
	
	
	
	
	if (stopFirst) {
		
		
		if (curAnimation_){
			curAnimation_->setAnimationDelegate(NULL);
			curAnimation_->hide();
		}
        
        
        if (curFrame_) {
            curFrame_->setVisible(false);
		}
        
		curAnimation_=NULL;
		curFrame_=NULL;
        
        
		if (animations_) {
			curAnimation_ = (TGSpriterAnimation *)animations_->objectForKey(new_animation);
			if (curAnimation_) {
				curAnimation_->reset();
				curFrame_=curAnimation_->getCurFrame();
			}
		}
		
	}
	else {
		
		
		if (curAnimation_)
		{
			curAnimation_->setAnimationDelegate(NULL);
			
			if ((curAnimation_->getName()->compare(new_animation.c_str())!=0)) {
				
				curAnimation_->hide();
				
				curAnimation_=NULL;
				
				if (curFrame_) {
					curFrame_->setVisible(false);
				}
				curFrame_=NULL;
				
				if (animations_) {
					curAnimation_ =(TGSpriterAnimation *)animations_->objectForKey(new_animation);
					if (curAnimation_) {
						curAnimation_->reset();
						curFrame_=curAnimation_->getCurFrame();
					}
				}
			}
		}
		else {
			
			
			if (curFrame_) {
				curFrame_->setVisible(false);
			}
			curFrame_=NULL;
			
			if (animations_) {
				curAnimation_ =(TGSpriterAnimation *)animations_->objectForKey(new_animation);
				if (curAnimation_) {
					curAnimation_->reset();
					curFrame_=curAnimation_->getCurFrame();
				}
			}
		}
	}
	
	if (curAnimation_) {
		curAnimation_->setAnimationDelegate(this);
        
		ret=true;
	}
	
	this->setVisible(true);
    this->scheduleUpdate();
	//this->schedule(schedule_selector(TGSpriterNode::update));
	
	return ret;
}

void TGSpriterNode::update(float dt) {
	if (curAnimation_) {
		curAnimation_->update(dt);
	}
}

void TGSpriterNode::showFrame(CCString* frameName){
    
    if (armatureAnim_) {
        armatureAnim_->showFrame(frameName->m_sString);
        return;
    }
    
	curAnimation_ = NULL;
	
	if (frameName) {
		this->unscheduleUpdate();
		TGSpriterFrame * tmp_curFrame_=(TGSpriterFrame *)frames_->objectForKey(frameName->getCString());
		if (tmp_curFrame_) {
			
			CCDict2Element* pElement = NULL;
			CCDICT2_FOREACH(frames_, pElement)
			{
				TGSpriterFrame* frame = (TGSpriterFrame*)pElement->getObject();
				if(frame)
					frame->setVisible(false);
			}
			
			tmp_curFrame_->setVisible(true);
			
			curFrame_=tmp_curFrame_;
		}
	}
}

void TGSpriterNode::setCurFrameFlipX(bool bFlipX) {
    if(curFrame_) {
        curFrame_->setFlipX(bFlipX);
    } else if (curAnimation_) {
		TGSpriterFrame * temp=curAnimation_->getCurFrame();
		temp->setFlipX(bFlipX);
	}
}

void TGSpriterNode::setCurFrameFlipY(bool bFlipY) {
    if(curFrame_) {
        curFrame_->setFlipY(bFlipY);
    } else if (curAnimation_) {
		TGSpriterFrame * temp=curAnimation_->getCurFrame();
		temp->setFlipY(bFlipY);
	}
}

void TGSpriterNode::setFlipX(CCString* frameName, bool bFlipX) {
    if (frameName) {
		TGSpriterFrame * tmp_curFrame_=(TGSpriterFrame *)frames_->objectForKey(frameName->getCString());
		if (tmp_curFrame_) {
            tmp_curFrame_->setFlipX(bFlipX);
		}
	}
}

void TGSpriterNode::setFlipY(CCString* frameName, bool bFlipY) {
    if (frameName) {
		TGSpriterFrame * tmp_curFrame_=(TGSpriterFrame *)frames_->objectForKey(frameName->getCString());
		if (tmp_curFrame_) {
            tmp_curFrame_->setFlipY(bFlipY);
		}
	}
}

bool TGSpriterNode::isCurFrameFlipX() const {
    if(curFrame_) {
        return curFrame_->isFlipX();
    } else if (curAnimation_) {
		TGSpriterFrame * temp=curAnimation_->getCurFrame();
		return temp->isFlipX();
	}
    return false;
}

bool TGSpriterNode::isCurFrameFlipY() const {
    if(curFrame_) {
        return curFrame_->isFlipY();
    } else if (curAnimation_) {
		TGSpriterFrame * temp=curAnimation_->getCurFrame();
		return temp->isFlipY();
	}
    return false;
}

void TGSpriterNode::setFlipX(bool bFlipX) {
	CCDict2Element* pElement = NULL;
	CCDICT2_FOREACH(frames_, pElement){
        TGSpriterFrame *keyvalue=(TGSpriterFrame*)pElement->getObject();
        keyvalue->setFlipX(bFlipX);
    }
}

void TGSpriterNode::setFlipY(bool bFlipY) {
	CCDict2Element* pElement = NULL;
	CCDICT2_FOREACH(frames_, pElement){
        TGSpriterFrame *keyvalue=(TGSpriterFrame*)pElement->getObject();
        keyvalue->setFlipY(bFlipY);
    }
}

CCString * TGSpriterNode::getCurAnimationName()const{
    if(armatureAnim_){
        return CCString::create(armatureAnim_->currentAnimation());
    }
    
    if (curAnimation_) {
		return curAnimation_->getName();
	}
	return NULL;
}

CCString * TGSpriterNode::getCurFrameName()const{
    if(armatureAnim_){
        return CCString::create(armatureAnim_->currentFrame());
    }
    
	if (curFrame_) {
		return curFrame_->getName();
	}
	else if (curAnimation_) {
		TGSpriterFrame * temp=curAnimation_->getCurFrame();
		if (temp) {
			return temp->getName();
		}
	}
	return NULL;
}

void TGSpriterNode::setChildrenAnchorPoint(const CCPoint& point) {
    if(m_pChildren && m_pChildren->count() > 0)
    {
        CCObject* child;
        CCARRAY_FOREACH(m_pChildren, child)
        {
            CCNode* pChild = (CCNode*) child;
            if (pChild)
            {
                pChild->setAnchorPoint(point);
            }
        }
    }
}

CCSprite* TGSpriterNode::getDefaultSpriter()
{
    if(curFrame_)
    {
        int count = curFrame_->sprites_->count();
        if(count>0)
        {
            CCSprite* sprite = (CCSprite*)(curFrame_->sprites_->objectAtIndex(0));
            return sprite;
        }
    }
    return NULL;
}

TGSpriterFrame* TGSpriterNode::getCurFrame() const {
    return curFrame_;
}

void TGSpriterNode::Test(){
    
	if(curFrame_)
    {
		CCObject* child;
        CCARRAY_FOREACH(curFrame_->sprites_, child)
        {
            CCNode* pChild = (CCNode*) child;
			if (pChild->getTag()!=1000) {
				if (pChild->isVisible()) {
					CCLog("TGSpriterNode::Test() %x isVisible:true", pChild);
				}
				else {
					CCLog("TGSpriterNode::Test() %x isVisible:false",pChild);
				}
			}
			
			CCLog("TGSpriterNode::Test %x false",pChild->getParent()->getParent());
        }
    }
    
}

void TGSpriterNode::animationFrameChanged(std::string anim_name,std::string lastframe,std::string name){
	
	if (spriterNodeDelegate_) {
		spriterNodeDelegate_->animationFrameChanged(this,anim_name,lastframe,name);
	}
}

void TGSpriterNode::animationFinished(std::string name){
    
	if (spriterNodeDelegate_) {
		spriterNodeDelegate_->animationFinished(this,name);
	}
	
	if (autoRemoveOnFinish_) {
		this->stopAnimation();
		this->handleAutoRemoveOnFinish();
		this->removeFromParentAndCleanup(true);
	}
}

#pragma mark CCSAXDelegator ####################################################

void TGSpriterNode::startElement(void *ctx, const char *name, const char **atts){
	CC_UNUSED_PARAM(ctx);
	TGSpriterConfigNodeCC * newNode=new TGSpriterConfigNodeCC;
	newNode->_name=name;
	newNode->_parent=curConfigNode_;
	curConfigNode_->_children.push_back(newNode);
	curConfigNode_=newNode;
}

void TGSpriterNode::textHandler(void *ctx, const char *s, int len){
	CC_UNUSED_PARAM(ctx);
	std::string new_str(s,0,len);
	if (curConfigNode_->_value.length() == 0) {
		curConfigNode_->_value=new_str;
	}
}


void TGSpriterNode::endElement(void *ctx, const char *name){
	CC_UNUSED_PARAM(ctx);
	std::string new_str=name;
	curConfigNode_ = curConfigNode_->_parent;
}

void TGSpriterNode::finishedinitNodeWithAnimateEidtorXml(){
	//获取所有的动画帧
	CCString * delfautFrameName=NULL;
	
	std::vector<TGSpriterConfigNodeCC *> & root_children=configRoot_->_children[0]->_children;
	CCSize  tempSize=CCSize(0,0);
	CCSize  tempMaxSize=CCSize(0,0);
	
	for (int r_index=0;r_index<root_children.size();r_index++) {
		
		TGSpriterConfigNodeCC * c=root_children[r_index];
		std::string c_name = c->_name;
		
		if (c_name!= "animations")
			continue;
		
		std::vector<TGSpriterConfigNodeCC *> & char_children=c->_children;
		for (int char_index=0;char_index<char_children.size();char_index++) {
			TGSpriterConfigNodeCC * charNodes=char_children[char_index];
			std::string char_name = charNodes->_name;
			if (char_name == "animation") {
				std::vector<TGSpriterConfigNodeCC *> & frame_children=charNodes->_children;
				
				bool flipX=false;
				bool flipY=false;
				int  tick=0;
				for (int f_index=0;f_index<frame_children.size();f_index++) {
					TGSpriterConfigNodeCC *frames=frame_children[f_index];
					const std::string& f_name = frames->_name;
					const std::string& f_value = frames->_value;
					if (f_name == "flipX") {
						flipX=CCString::create(f_value)->boolValue();
						tick++;
					}
					else if (f_name == "flipY") {
						flipY=CCString::create(f_value)->boolValue();
						tick++;
					}
					
					if (tick >= 2) {
						break;
					}
				}
				
				for (int f_index=0;f_index<frame_children.size();f_index++) {
					TGSpriterConfigNodeCC * frames=frame_children[f_index];
					
					const std::string& f_name = frames->_name;
					const std::string& f_value = frames->_value;
					
					if (f_name == "spriteFrame") {
						
						TGSpriterFrame * spriterFrame = TGSpriterFrame::spriterFrame();
						CCSprite * sprite=NULL;
						if (useBatchNode_) {
							sprite = CCSprite::createWithSpriteFrameName(f_value.c_str());
						} else {
							sprite = CCSprite::create(f_value.c_str());
						}
						
						sprite->setFlipX(flipX);
						sprite->setFlipY(flipY);
						sprite->setVisible(false);
						
						tempSize=sprite->getContentSize();
						this->addChild(sprite);
						spriterFrame->addSprite(sprite);
						spriterFrame->setName(CCString::create(f_value));
						spriterFrame->setContentSize(tempSize);
						if (!delfautFrameName) {
							delfautFrameName=spriterFrame->getName();
						}
						
						//std::cout << (int32_t)frames_ << ":" << f_value << std::endl;
						
						frames_->setObject(spriterFrame, f_value);
						
						if (tempMaxSize.width < tempSize.width) {
							tempMaxSize.width=tempSize.width;
						}
						
						if (tempMaxSize.height < tempSize.height) {
							tempMaxSize.height=tempSize.height;
						}
					}
				}
			}
		}
	}
	
	
	
	//获取所有的动画信息
	std::vector<TGSpriterConfigNodeCC *> & c_children=configRoot_->_children[0]->_children;
	for (int c_index=0;c_index<c_children.size();c_index++){
		TGSpriterConfigNodeCC * c=c_children[c_index];
		std::string c_name = c->_name;
		if (c_name !="animations")
			continue;
        std::vector<TGSpriterConfigNodeCC *> &char_children=c->_children;
		for (int char_index=0;char_index<char_children.size();char_index++) {
			TGSpriterConfigNodeCC * charNodes=(TGSpriterConfigNodeCC *)char_children[char_index];
			std::string char_name = charNodes->_name;
			if (char_name == "animation") {
				TGSpriterAnimation * animation = TGSpriterAnimation::spriterAnimation();
				std::string animationName = "";
				std::vector<TGSpriterConfigNodeCC *> & frame_children=charNodes->_children;
				float frameDuration=0.3;
				int  tick=0;
				for (int f_index=0;f_index<frame_children.size();f_index++) {
					TGSpriterConfigNodeCC * frames=frame_children[f_index];
					std::string f_name = frames->_name;
					std::string f_value = frames->_value;
					if (f_name == "name") {
						animation->setName(CCString::create(f_value));
						tick++;
					}
					else if (f_name == "delay") {
						frameDuration=CCString::create(f_value)->floatValue();
						tick++;
					}
					
					if (tick >= 2) {
						break;
					}
				}
				
				for (int f_index=0;f_index<frame_children.size();f_index++) {
					TGSpriterConfigNodeCC * frames=(TGSpriterConfigNodeCC *)frame_children[f_index];
					std::string f_name = frames->_name;
					std::string f_value = frames->_value;
					if (f_name == "spriteFrame") {
						animation->addFrame((TGSpriterFrame*)frames_->objectForKey(f_value),frameDuration);
					}
				}
				
				animations_->setObject(animation, animation->getName()->getCString());
			}
		}
	}
	
	// clean up
	
	if(_releaseRoot) CC_SAFE_DELETE(configRoot_);
	this->setContentSize(tempMaxSize);
	
	if (delfautFrameName) {
		this->showFrame(delfautFrameName);
	}
    
}
void TGSpriterNode::finishedinitNodeWithScmlFile()
{
	//获取所有的动画帧
    if (configRoot_ && configRoot_->_children.size() <= 0) {
        if(_releaseRoot) CC_SAFE_DELETE(configRoot_);
        return;
    }
    
	CCString * delfautFrameName=NULL;
	std::vector<TGSpriterConfigNodeCC *> & root_children=configRoot_->_children[0]->_children;
	CCSize  tempSize=CCSize(0,0);
	CCSize  tempMaxSize=CCSize(0,0);
	for (int r_index=0;r_index<root_children.size();r_index++) {
		
		TGSpriterConfigNodeCC * c=root_children[r_index];
		
		std::string c_name = c->_name;
		
		if (c_name!= "frame")
			continue;
		
		std::string spriterFrameName="";
		
		CCPoint minPos=CCPoint(0, 0);
		CCPoint maxPos=CCPoint(0, 0);
		
		TGSpriterFrame * spriterFrame = TGSpriterFrame::spriterFrame();
		
		std::vector<TGSpriterConfigNodeCC *> & c_children=c->_children;
		
		for (int c_index=0;c_index<c_children.size();c_index++) {
			
			TGSpriterConfigNodeCC * frameNodes=c_children[c_index];
			std::string f_name = frameNodes->_name;
			
			if (f_name == "name") {
				spriterFrameName = frameNodes->_value;
			} else if (f_name == "sprite") {
				
				std::string img="";
				
				float x = 0, y = 0, angle=0, width = 0, height = 0;
                
				int opacity =  255;
				
				bool flipX = false, flipY = false;
				
				ccColor3B color = ccc3(255, 255, 255);
				
				std::vector<TGSpriterConfigNodeCC *> & f_children=frameNodes->_children;
				
				for (int f_index=0;f_index<f_children.size();f_index++) {
					
					TGSpriterConfigNodeCC * spriteProp=f_children[f_index];
					
					std::string name = spriteProp->_name;
					std::string value = spriteProp->_value;
					
					if (name == "image") {
						int pos=value.find_last_of("\\");
						img=value.substr(pos+1);
					} else if (name == "x") {
						x = (float)CCString::create(value)->doubleValue() * GameUtils::UiInterfaceScale();
					} else if (name == "y") {
						y = - (float)CCString::create(value)->doubleValue() * GameUtils::UiInterfaceScale();
					} else if (name == "angle") {
						angle = -(float)CCString::create(value)->doubleValue();
					} else if (name == "opacity") {
						opacity =CCString::create(value)->doubleValue() / 100.0 * 255;
					} else if (name == "xflip"||name == "flipX") {
						flipX = CCString::create(value)->boolValue();
					} else if (name == "yflip"||name == "flipY") {
						flipY = CCString::create(value)->boolValue();
					} else if (name == "color") {
						int c = CCString::create(value)->intValue();
						int red = c / ::pow(256, 2);
						int green = (c - red * ::pow(256, 2)) / 256;
						int blue = c -  red * ::pow(256, 2) - blue * 256;
						color = ccc3(red, green, blue);
					} else if (name == "width") {
						width = (float)CCString::create(value)->doubleValue() * GameUtils::UiInterfaceScale();
					} else if (name == "height") {
						height= (float)CCString::create(value)->doubleValue() * GameUtils::UiInterfaceScale();
					}
				}
				
				CCSprite * sprite=NULL;
				if (useBatchNode_) {
					sprite = CCSprite::createWithSpriteFrameName(img.c_str());
				} else {
					sprite = CCSprite::create(img.c_str());
				}
				CCSize contentSize = sprite->getContentSize();
				
                sprite->setAnchorPoint(CCPointMake(0.5f, 0.5f));
                
                
                if (width < 0) {
                    x += width * cos(CC_DEGREES_TO_RADIANS(angle));
                    y -= width * sin(CC_DEGREES_TO_RADIANS(angle));
                }
                
                if (height < 0) {
                    x += height * cos(CC_DEGREES_TO_RADIANS(90 + angle));
                    y -= height * sin(CC_DEGREES_TO_RADIANS(90 + angle));
                }
                
				sprite->setPosition(CCPointMake(x, y));
                
				sprite->setRotation(angle);
				sprite->setFlipX(flipX);
				sprite->setFlipY(flipY);
				sprite->setColor(color);
				sprite->setScaleX(width /contentSize.width);
				sprite->setScaleY(height / contentSize.height);
				sprite->setVisible(false);
                sprite->setOpacity(opacity);
				this->addChild(sprite);
				spriterFrame->addSprite(sprite);
				
				const float tempWidthHalf=width/2;
				
				float temp=x-tempWidthHalf;
				if (minPos.x > temp) {
					minPos.x=temp;
				}
				
				temp=x+tempWidthHalf;
				if (maxPos.x < temp) {
					maxPos.x=temp;
				}
				
				const float tempheightHalf=height/2;
				
				temp=y-tempheightHalf;
				if (minPos.y > temp) {
					minPos.y=temp;
				}
				
				temp=y+tempheightHalf;
				if (maxPos.y < temp) {
					maxPos.y=temp;
				}
			}
		}
		
		tempSize.width=(maxPos.x-minPos.x);
		tempSize.height=(maxPos.y-minPos.y);
		
		spriterFrame->setContentSize(tempSize);
		
		spriterFrame->setName(CCString::create(spriterFrameName));
		
		if (!delfautFrameName) {
			delfautFrameName=spriterFrame->getName();
		}
		//std::cout << "--->" << (int32_t)frames_ << ":" << spriterFrameName << std::endl;
		frames_->setObject(spriterFrame, spriterFrameName);
		
		if (tempMaxSize.width < tempSize.width) {
			tempMaxSize.width=tempSize.width;
		}
		
		if (tempMaxSize.height < tempSize.height) {
			tempMaxSize.height=tempSize.height;
		}
		//CCLog("%s--->maxSize(%f,%f)",spriterFrameName.c_str(),tempMaxSize.width,tempMaxSize.height);
	}
	
    
	
	//获取所有的动画信息
	std::vector<TGSpriterConfigNodeCC *> & c_children=configRoot_->_children[0]->_children;
	
	for (int c_index=0;c_index<c_children.size();c_index++){
		
		TGSpriterConfigNodeCC * c=c_children[c_index];
		
		std::string c_name = c->_name;
		
		if (c_name !="char")
			continue;
		
		std::vector<TGSpriterConfigNodeCC *> & char_children=c->_children;
		for (int char_index=0;char_index<char_children.size();char_index++) {
			
			TGSpriterConfigNodeCC * charNodes=char_children[char_index];
			std::string char_name = charNodes->_name;
			
			if (char_name   == "name") {
				continue;
			}
			else if (char_name == "box"){
                
				std::vector<TGSpriterConfigNodeCC *> & f_children=charNodes->_children;
				
				CCPoint lefttop_pos;
				CCPoint rightbottom_pos;
				
				for (int f_index=0;f_index<f_children.size();f_index++) {
					
					TGSpriterConfigNodeCC * spriteProp=(TGSpriterConfigNodeCC *)f_children[f_index];
					std::string name = spriteProp->_name;
					std::string value = spriteProp->_value;
                    
					if (name == "bottom") {
						rightbottom_pos.y = CCString::create(value)->doubleValue() * GameUtils::UiInterfaceScale();
					}else if (name == "top") {
						lefttop_pos.y = CCString::create(value)->doubleValue() * GameUtils::UiInterfaceScale();
					} else if (name == "right") {
						rightbottom_pos.x = CCString::create(value)->doubleValue() * GameUtils::UiInterfaceScale();
					} else if (name == "left") {
						lefttop_pos.x = CCString::create(value)->doubleValue() * GameUtils::UiInterfaceScale();
                        
					}
				}
				
				boxRect.setRect(lefttop_pos.x,lefttop_pos.y,abs(rightbottom_pos.x-lefttop_pos.x),abs(lefttop_pos.y-rightbottom_pos.y));
			}
			else if (char_name == "anim") {
				
				TGSpriterAnimation * animation = TGSpriterAnimation::spriterAnimation();
				
				std::string animationName = "";
				std::vector<TGSpriterConfigNodeCC *> & frame_children=charNodes->_children;
				for (int f_index=0;f_index<frame_children.size();f_index++) {
					
					TGSpriterConfigNodeCC * frames=frame_children[f_index];
					const std::string &f_name = frames->_name;
					const std::string &f_value = frames->_value;
					if (f_name == "name") { // animation name
						animationName = f_value;
					} else if (f_name == "frame") {
						std::string frameName = "";
						double frameDuration = 0;
						
						std::vector<TGSpriterConfigNodeCC *> & frameProp_children=frames->_children;
						for (int fp_index=0;fp_index<frameProp_children.size();fp_index++){
							
							TGSpriterConfigNodeCC * frameProp=frameProp_children[fp_index];
							
							const std::string &fp_name = frameProp->_name;
							const std::string &fp_value = frameProp->_value;
							
							if (fp_name == "name") {
								frameName = fp_value;
							} else if (fp_name == "duration") {
								// milliseconds?? should be 1000，
							    // ps:the spec stats milliseconds, but this doesn't match the reference implementation.
								frameDuration =CCString::create(fp_value)->doubleValue() / 100.0;
                                //                                frameDuration =CCString::create(fp_value)->doubleValue();
							}
						}
						animation->addFrame((TGSpriterFrame*)frames_->objectForKey(frameName),frameDuration);
					}
				}
				
				animation->setName(CCString::create(animationName));
				animations_->setObject(animation, animationName);
			}
		}
	}
	
	// clean up
	if(_releaseRoot) CC_SAFE_DELETE(configRoot_);
	
	this->setContentSize(tempMaxSize);
	
	if (delfautFrameName) {
		this->showFrame(delfautFrameName);
	}
}

void TGSpriterNode::stopAnimation(){
    
    if (armatureAnim_) {
        armatureAnim_->stopAnimation();
        return;
    }
    
	this->unscheduleUpdate();
	
	if (curAnimation_)
		curAnimation_->hide();
	
	curAnimation_=NULL;
}

void TGSpriterNode::setVisible(bool bVisible)
{
    CCNode::setVisible(bVisible);
}

void TGSpriterNode::showFrameByIndex(int index){
    
}

void TGSpriterNode::setShaderProgram(cocos2d::CCGLProgram *var) {
    if (frames_) {
        CCDict2Element* dict2Element = NULL;
        CCDICT2_FOREACH(frames_, dict2Element) {
            CCObject* sp = NULL;
            CCARRAY_FOREACH(((TGSpriterFrame*)(dict2Element->getObject()))->sprites_, sp) {
                ((CCNode*)sp)->setShaderProgram(var);
            }
        }
    }
}

void TGSpriterNode::setColor(const ccColor3B& color) {
    _color = color;
    if (frames_) {
        CCDict2Element* dict2Element = NULL;
        CCDICT2_FOREACH(frames_, dict2Element) {
            CCObject* sp = NULL;
            CCARRAY_FOREACH(((TGSpriterFrame*)(dict2Element->getObject()))->sprites_, sp) {
                ((CCSprite*)sp)->setColor(color);
            }
        }
    }
}

const ccColor3B& TGSpriterNode::getColor(void) {
    return _color;
}

GLubyte TGSpriterNode::getOpacity(void) {
    return _opacity;
}

void TGSpriterNode::setOpacity(GLubyte opacity) {
    _opacity = opacity;
    if (frames_) {
        CCDict2Element* dict2Element = NULL;
        CCDICT2_FOREACH(frames_, dict2Element) {
            CCObject* sp = NULL;
            CCARRAY_FOREACH(((TGSpriterFrame*)(dict2Element->getObject()))->sprites_, sp) {
                ((CCSprite*)sp)->setOpacity(opacity);
            }
        }
    }
}

void TGSpriterNode::setOpacityModifyRGB(bool bValue) {
    CC_UNUSED_PARAM(bValue);
}

bool TGSpriterNode::isOpacityModifyRGB(void)  {
    return true;
}

void TGSpriterNode::onAnimationEvent(void * animation, const char * eventType, const char * movementID){
    std::string even =  eventType;
    if (armatureAnim_ == animation) {
        if (even.compare(COMPLETE) == 0) {
			if (spriterNodeDelegate_) spriterNodeDelegate_->animationFinished(this, armatureAnim_->currentAnimation());
        }
        else if (even.compare(MOVEMENT_RUNNING) == 0){
            if (armature_lastframe_.compare(armatureAnim_->currentFrame()) != 0) {
                std::string lastframe = armature_lastframe_;
                armature_lastframe_ = armatureAnim_->currentFrame();
				std::cout << "onAnimationEvent:"<< movementID <<" lastframe:" << lastframe << " currentFrame:" << armature_lastframe_ << std::endl;
				if (spriterNodeDelegate_) spriterNodeDelegate_->animationFrameChanged(this,armatureAnim_->currentAnimation(),lastframe,armature_lastframe_);
            }
        }
        
    }
}
