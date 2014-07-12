//
//  UiUtils.cpp
//  iLostCity
//
//  Created by Ryan_Y on 13-4-22.
//
//

#include "UiUtils.h"
#include "GameUtils.h"


#include <stdlib.h>
//#include <hash_map.h>

#include <boost/regex.hpp>

USING_NS_CC;

CCNode * UiUtils::createTextScrollNode(const CCSize & viewSize
                                         ,const std::string & text
                                         ,const ccColor3B& color3
                                         ,const std::string & textFont
                                         ,const int fontSize
                                         ,const CCVerticalTextAlignment vertical
                                         ,const CCTextAlignment horizontal){
	
	CCNode * rootNode = CCNode::create();
	rootNode->setAnchorPoint(ccp(0, 0));
	rootNode->setContentSize(viewSize);
    
    CCLabelTTF * labelbody = CCLabelTTF::create(text.c_str(), textFont.c_str(),fontSize,CCSize(viewSize.width, 0), horizontal, vertical);
	labelbody->setColor(color3);
    if (labelbody->getContentSize().height < viewSize.height) {
        labelbody->setDimensions(viewSize);
    }
	
    cocos2d::extension::CCScrollView * labelbodyScrollView = cocos2d::extension::CCScrollView::create(viewSize, labelbody);
    labelbodyScrollView->setAnchorPoint(ccp(0, 0));
    labelbodyScrollView->setPosition(CCPoint(0, 0));
    labelbodyScrollView->setDirection(cocos2d::extension::kCCScrollViewDirectionVertical);
    labelbodyScrollView->setContentOffset(ccp(0, viewSize.height -labelbody->getContentSize().height));
    rootNode->addChild(labelbodyScrollView);
    labelbodyScrollView->updateInset();
	
	return rootNode;
}

float UiUtils::scaleTofit(const CCSize & containerSize,const CCSize & tgsize)
{
	float scale = 1.0f;
	bool width_scale = tgsize.width > containerSize.width;
	bool height_scale = tgsize.height > containerSize.height;
	if(width_scale || height_scale){
		if (width_scale && height_scale) {
			float scale_h = (containerSize.height / tgsize.height);
			float scale_w = (containerSize.width / tgsize.width);
			if (scale_h > scale_w) {
				scale = scale_w;
			}
			else{
				scale = scale_h;
			}
		}
		else if (width_scale) {
			scale = (containerSize.width / tgsize.width);
		}
		else{
			scale = (containerSize.height / tgsize.height);
		}
	}
	
	//缩放显示的内容
	return scale;
}

cocos2d::CCNode* UiUtils::nodeScaleTofit(cocos2d::CCNode * containerNode, const cocos2d::CCSize & tgsiz) {
    float scale = scaleTofit(tgsiz, containerNode->getContentSize());
    if (scale != 1.0f) {
        containerNode->setScale(scale);
    }
    return containerNode;
}

cocos2d::CCNode *UiUtils::scale9Sprite(const std::string& fileName,
                                       const cocos2d::CCSize& size) {
    CCSize contentSize = size;
    cocos2d::CCSpriteFrame *pFrame = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(fileName.c_str());
    cocos2d::extension::CCScale9Sprite * labelbodyScale9Sprite = cocos2d::extension::CCScale9Sprite::createWithSpriteFrame(pFrame);
    if (contentSize.width == 0) {
        contentSize.width = pFrame->getRect().size.width;
    } else if(contentSize.height == 0) {
        contentSize.height = pFrame->getRect().size.height;
    } 
    labelbodyScale9Sprite->setContentSize(contentSize);
    return labelbodyScale9Sprite;
}

cocos2d::CCSize UiUtils::getUIConstantSizeById(const std::string &Id) {
//    const cocos2d::CCString *str = GameConfig::sharedInstance()->getUIConstantById(Id);
//    const std::string &strVilue = str->getCString();
//    return GameUtils::string2Size(strVilue);
    
    return CCSizeMake(0, 0);
}

cocos2d::CCPoint UiUtils::getUIConstantPointById(const std::string & Id) {
//    const cocos2d::CCString *str = GameConfig::sharedInstance()->getUIConstantById(Id);
//    const std::string &strVilue = str->getCString();
//    return GameUtils::string2Point(strVilue);
    return CCSizeMake(0, 0);
}

/*
 *一代的正则表达式判断用户名密码是否合法
 */
bool UiUtils::isNameCurrect(const std::string text) {
    boost::regex pattern("[～＾“”｢」＿／∙＠＄≪≫€﹤﹥｛｝％［］＊＋＝（），。：；！？¥、=]*");
    boost::regex pattern1("[0-9a-zA-Z]");
    for (int i = 0; i < text.length(); i++) {
        unsigned char ch = (unsigned char)text.at(i);
        if (ch < 127) {
            std::string str = text.substr(i,1);
            if(!boost::regex_match(str, pattern1)) {
                return  true;
            }
        } else if(ch >= 127 ){
            std::string str = text.substr(i,3);
            if(boost::regex_match(str, pattern)) {
                return true;
            } else {
                i = i + 2;
            }
        }
    }
    return false;
}

bool UiUtils::isPasswordCurrect(const std::string psw) {
    boost::regex pattern("[～＾“”｢」＿／∙＠＄≪≫€﹤﹥｛｝％［］＊＋＝（），。：；！？¥、=]*");
    boost::regex pattern1("[0-9a-zA-Z]");
    for (int i = 0; i < psw.length(); i++) {
        unsigned char ch = (unsigned char)psw.at(i);
        if (ch < 127) {
            std::string str = psw.substr(i,1);
            if(!boost::regex_match(str, pattern1)) {
                return  true;
            }
        } else if(ch >= 127 ){
            return true;
        }
    }
    return false;
}

const int UiUtils::stringLength(const std::string &str) {
    int en = 0;     //英文
    int zh = 0;     //中文
    for (int i = 0; i < str.length(); i++) {
        unsigned char ch = (unsigned char)str.at(i);
        if (ch < 127) {
            en += 1;
        } else if(ch >= 127 ){
            zh += 1;
        }
    }
    return (en + (zh / 3 + (zh % 3 == 0 ? 0 : 1)) * 2);
}

void UiUtils::createBackgroundWhitPlist(const std::string &plist, cocos2d::CCNode *node) {
    cocos2d::CCDictionary* dictionary = cocos2d::CCDictionary::createWithContentsOfFile(plist.c_str());
    cocos2d::CCDictionary *framesDict = (cocos2d::CCDictionary *)dictionary->objectForKey("frames");
    
    cocos2d::CCDictElement* pElement = NULL;
    int KMaxWidthCount = 10;
    int KMaxHeightCount = 10; //10 * 10
    float width = 0.0f;
    float height = 0.0f;
    CCSize spriteSize = CCSize(0, 0);
    bool spriteInit = false;
    
    cocos2d::CCDICT_FOREACH(framesDict, pElement) {
        cocos2d::CCDictionary* frameDict = (cocos2d::CCDictionary *)pElement->getObject();
        std::string spriteFrameName = pElement->getStrKey();
        std::string name = spriteFrameName.substr(0, spriteFrameName.find_last_of("."));
        int index[2];   //row.index
        int from = name.size();
        for (int i = 0; i < 2; i++) {
            int pos = name.find_last_of("_", from);
            std::string s = name.substr(pos + 1, from - pos);
            from = pos - 1;
            index[i] = atoi(s.c_str());
        }
        cocos2d::CCSprite *sprite = cocos2d::CCSprite::createWithSpriteFrameName(spriteFrameName.c_str());
        sprite->setAnchorPoint(ccp(0, 0));
        
        int line = index[0] % KMaxWidthCount == 0 ? index[0] / KMaxWidthCount - 1: index[0] / KMaxWidthCount;
        int row =  index[0] % KMaxWidthCount == 0 ? KMaxWidthCount : index[0] % KMaxWidthCount;
        
        CCSize sourceSize = cocos2d::CCSizeFromString(frameDict->valueForKey("sourceSize")->getCString());
        if(!spriteInit) {
            spriteInit = true;
            
            const CCSize& winSize = cocos2d::CCDirector::sharedDirector()->getWinSize();
            if (winSize.height > 768) {
                spriteSize.width = sourceSize.width - 2;
                spriteSize.height = sourceSize.height - 2;
            } else {
                spriteSize.width = sourceSize.width - 1;
                spriteSize.height = sourceSize.height - 1;
            }
        }
        sourceSize.width -= 1;
        sourceSize.height -= 1;
        
        width = (index[1] % 2 == 0 ? 1 : 0) * spriteSize.width * KMaxWidthCount;
        height = (index[1] > 2 ? 1 : 0) * spriteSize.height * KMaxHeightCount;
        
        float pointX = (row - 1) * spriteSize.width + width - (spriteSize.width - sourceSize.width);
        float pointY = (line + 1) * spriteSize.height - (spriteSize.height - sourceSize.height);
        
        sprite->setPosition(ccp(pointX, node->getContentSize().height - pointY - height));
        
        node->addChild(sprite);
        
//        std::stringstream stream; stream << row << "," << line;
//        LabelView *view = LabelView::createWithFontStyle(stream.str().c_str(), kFontSytle_36_YELLOW);
//        view->setAnchorPoint(ccp(0.5, 0.5));
//        view->setPosition(ccp(spriteSize.width/2, spriteSize.height/2));
//        sprite->addChild(view);
    }

}


std::string  UiUtils::cutHex(const std::string & h){
	return ((h[0] == '#') ? h.substr(1,7):h);
}

const uint8_t UiUtils::hexToR(const std::string & h) {
	const std::string & tmp = (cutHex(h)).substr(0, 2);
	return GameUtils::Hex2Int(tmp.c_str(),tmp.length());
}

const uint8_t UiUtils::hexToG(const std::string & h) {
	const std::string & tmp = (cutHex(h)).substr(2, 2);
	return GameUtils::Hex2Int(tmp.c_str(),tmp.length());
}

const uint8_t UiUtils::hexToB(const std::string & h){
	const std::string & tmp = (cutHex(h)).substr(4, 2);
	return GameUtils::Hex2Int(tmp.c_str(),tmp.length());
}

bool UiUtils::endsWith(const char* pString, const char* pEnding) {
    std::string string(pString);
    std::string ending(pEnding);
    if(string.length() >= ending.length()) {
        return (string.compare(string.length() - ending.length(), ending.length(), ending) == 0);
    } else {
        return false;
    }
}

cocos2d::CCSprite* UiUtils::maskedSprite(cocos2d::CCSprite* textureSprite, cocos2d::CCSprite* maskSprite)
{
    if (!maskSprite) {
        return textureSprite;
    }
    
    const cocos2d::CCSize & maskSize = maskSprite->getContentSize();
    const int w = maskSize.width * maskSprite->getScaleX();
    const int h = maskSize.height * maskSprite->getScaleY();
    cocos2d::CCRenderTexture* rt = cocos2d::CCRenderTexture::create(w, h);
    
    maskSprite->setPosition( ccp(maskSize.width *  maskSprite->getScaleX()/2,
                                 maskSize.height * maskSprite->getScaleY()/2));
    
    const cocos2d::CCSize & textureSize = textureSprite->getContentSize();
    textureSprite->setPosition( ccp(textureSize.width *  textureSprite->getScaleX() /2,
                                    textureSize.height * textureSprite->getScaleY()/2));
    
    cocos2d::ccBlendFunc blendFunc;
    blendFunc.src = GL_ONE;
    blendFunc.dst = GL_ZERO;
    maskSprite->setBlendFunc(blendFunc);
    
    blendFunc.src = GL_DST_ALPHA;           // mask图片的当前alpha值是多少，如果是0（完全透明），那么就显示mask的。如果是1（完全不透明）
    blendFunc.dst = GL_ZERO;                // maskSprite不可见
    textureSprite->setBlendFunc(blendFunc);
    
    rt->begin();
    maskSprite->visit();
    textureSprite->visit();
    rt->end();
    
    cocos2d::CCSprite* retval = cocos2d::CCSprite::createWithTexture(rt->getSprite()->getTexture());
    retval->setFlipY(true);
    return retval;
}

cocos2d::CCRect UiUtils::scaleNodeToShowAll(cocos2d::CCNode* node) {
    cocos2d::CCRect returnRect = cocos2d::CCRectMake(0, 0, 0, 0);
    if(node) {
    
        float scale = CCDirector::sharedDirector()->getContentScaleFactor();
        CCSize contentSize = node->getContentSize();
        float viewPortW = contentSize.width * scale;
        float viewPortH = contentSize.height * scale;
        node->setScale(scale);
        node->setAnchorPoint(ccp(0,0));
        returnRect.origin.x = (contentSize.width - viewPortW) / 2;
        returnRect.origin.y = (contentSize.height - viewPortH) / 2;
        returnRect.size.width = contentSize.width * scale;
        returnRect.size.height = contentSize.height * scale;
        node->setPosition(returnRect.origin);
    }
    return returnRect;
}

void UiUtils::revertScaleShowAllNode(cocos2d::CCNode* node) {
    cocos2d::CCRect returnRect = cocos2d::CCRectMake(0, 0, 0, 0);
    if(node) {
        float scale = cocos2d::CCDirector::sharedDirector()->getContentScaleFactor();
        CCSize contentSize = node->getContentSize();
        node->setScale(1.0/scale);
        node->setAnchorPoint(ccp(0,0));
        returnRect.origin.x = 0;
        returnRect.origin.y = 0;
        returnRect.size = contentSize;
        node->setPosition(returnRect.origin);
    }
}

cocos2d::CCRect UiUtils::scaleNodeToExactFit(cocos2d::CCNode* node) {
    CCSize screenSize = cocos2d::CCEGLView::sharedOpenGLView()->getFrameSize();  //屏幕大小
    const cocos2d::CCRect& rect = cocos2d::CCEGLView::sharedOpenGLView()->getViewPortRect();  //view大小
    float openGLViewScale = cocos2d::CCEGLView::sharedOpenGLView()->getScaleX();
    float contentScaleX = screenSize.width/rect.size.width;
    float contentScaleY = screenSize.height/rect.size.height;
    cocos2d::CCRect returnRect = cocos2d::CCRectMake(0, 0, 0, 0);
    if(node) {
        node->setScaleX(contentScaleX);
        node->setScaleY(contentScaleY);
        CCPoint point = node->getPosition();
        CCSize contentSize = node->getContentSize();
        float viewPortW = contentSize.width * contentScaleX;
        float viewPortH = contentSize.height * contentScaleY;
        node->setAnchorPoint(ccp(0,0));
        returnRect.origin.x = (contentSize.width - viewPortW) / 2;
        returnRect.origin.y = (contentSize.height - viewPortH) / 2;
//        returnRect.origin.x = (rect.size.width - screenSize.width) / 2;
//        returnRect.origin.y = (rect.size.height - screenSize.height) / 2;
        returnRect.size.width = contentSize.width * openGLViewScale * contentScaleX;
        returnRect.size.height = contentSize.height * openGLViewScale * contentScaleY;
        node->setPosition(returnRect.origin);
    }
    return returnRect;
}

cocos2d::CCRect UiUtils::scaleNodeByScaleFactor(cocos2d::CCNode* node,const float scale) {
    cocos2d::CCRect returnRect = cocos2d::CCRectMake(0, 0, 0, 0);
    float openGLViewScale = cocos2d::CCEGLView::sharedOpenGLView()->getScaleX();
    if(node) {
        float contentScale = cocos2d::CCDirector::sharedDirector()->getContentScaleFactor();
        node->setScale(contentScale);
        node->setAnchorPoint(ccp(0,0));
        CCSize size = node->getContentSize();
        node->setPosition(ccpAdd(node->getPosition(), ccp(size.width*(1-contentScale)/2,size.height*(1-contentScale)/2)));
        
        returnRect.origin = node->getPosition();
        returnRect.size.width = size.width * openGLViewScale * contentScale;
        returnRect.size.height = size.height * openGLViewScale * contentScale;
    }
    return returnRect;
}