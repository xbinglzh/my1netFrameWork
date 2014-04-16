#include "CCDictionary2.h"
#include "CCString.h"
#include "CCInteger.h"

using namespace std;

extern cocos2d::CCDictionary2* ccFileUtils_dictionary2WithContentsOfFileThreadSafe(const char *pFileName);

NS_CC_BEGIN

CCDictionary2::CCDictionary2()
: m_pElements(NULL)
, m_eDictType(kCCDictUnknown)
, m_eOldDictType(kCCDictUnknown)
{

}

CCDictionary2::~CCDictionary2()
{
    removeAllObjects();
}

unsigned int CCDictionary2::count()
{
    return HASH_COUNT(m_pElements);
}

CCArray* CCDictionary2::allKeys()
{
    int iKeyCount = this->count();
    if (iKeyCount <= 0) return NULL;

    CCArray* pArray = CCArray::createWithCapacity(iKeyCount);

    CCDict2Element *pElement, *tmp;
    if (m_eDictType == kCCDictStr)
    {
        HASH_ITER(hh, m_pElements, pElement, tmp) 
        {
            CCString* pOneKey = new CCString(pElement->m_szKey);
            pOneKey->autorelease();
            pArray->addObject(pOneKey);
        }
    }
    else if (m_eDictType == kCCDictInt)
    {
        HASH_ITER(hh, m_pElements, pElement, tmp) 
        {
            CCInteger* pOneKey = new CCInteger(pElement->m_iKey);
            pOneKey->autorelease();
            pArray->addObject(pOneKey);
        }
    }
    
    return pArray;
}

CCArray* CCDictionary2::allKeysForObject(CCObject* object)
{
    int iKeyCount = this->count();
    if (iKeyCount <= 0) return NULL;
    CCArray* pArray = CCArray::create();

    CCDict2Element *pElement, *tmp;

    if (m_eDictType == kCCDictStr)
    {
        HASH_ITER(hh, m_pElements, pElement, tmp) 
        {
            if (object == pElement->m_pObject)
            {
                CCString* pOneKey = new CCString(pElement->m_szKey);
                pArray->addObject(pOneKey);
                pOneKey->release();
            }
        }
    }
    else if (m_eDictType == kCCDictInt)
    {
        HASH_ITER(hh, m_pElements, pElement, tmp) 
        {
            if (object == pElement->m_pObject)
            {
                CCInteger* pOneKey = new CCInteger(pElement->m_iKey);
                pArray->addObject(pOneKey);
                pOneKey->release();
            }
        }
    }
    return pArray;
}

CCObject* CCDictionary2::objectForKey(const std::string& key)
{
    if (m_eDictType == kCCDictUnknown && m_eDictType == kCCDictUnknown) return NULL;
    CCAssert(m_eDictType == kCCDictStr, "this dictionary does not use string as key.");

    CCObject* pRetObject = NULL;
    CCDict2Element *pElement = NULL;
    HASH_FIND_STR(m_pElements, key.c_str(), pElement);
    if (pElement != NULL)
    {
        pRetObject = pElement->m_pObject;
    }
    return pRetObject;
}

CCObject* CCDictionary2::objectForKey(int key)
{
    if (m_eDictType == kCCDictUnknown && m_eDictType == kCCDictUnknown) return NULL;
    CCAssert(m_eDictType == kCCDictInt, "this dictionary does not use integer as key.");

    CCObject* pRetObject = NULL;
    CCDict2Element *pElement = NULL;
    HASH_FIND_INT(m_pElements, &key, pElement);
    if (pElement != NULL)
    {
        pRetObject = pElement->m_pObject;
    }
    return pRetObject;
}

const CCString* CCDictionary2::valueForKey(const std::string& key)
{
    CCString* pStr = (CCString*)objectForKey(key);
    if (pStr == NULL)
    {
        pStr = CCString::create("");
    }
    return pStr;
}

const CCString* CCDictionary2::valueForKey(int key)
{
    CCString* pStr = (CCString*)objectForKey(key);
    if (pStr == NULL)
    {
        pStr = CCString::create("");
    }
    return pStr;
}

void CCDictionary2::setObject(CCObject* pObject, const std::string& key)
{
    CCAssert(key.length() > 0 && pObject != NULL, "Invalid Argument!");
    if (m_eOldDictType == kCCDictUnknown)
    {
        m_eOldDictType = kCCDictStr;
    }
    m_eDictType = kCCDictStr;
    CCAssert(m_eDictType == m_eOldDictType, "this dictionary does not use string as key.");

    CCDict2Element *pElement = NULL;
    HASH_FIND_STR(m_pElements, key.c_str(), pElement);
    if (pElement == NULL)
    {
        setObjectUnSafe(pObject, key);
    }
    else if (pElement->m_pObject != pObject)
    {
        CCObject* pTmpObj = pElement->m_pObject;
        pTmpObj->retain();
        removeObjectForElememt(pElement);
        setObjectUnSafe(pObject, key);
        pTmpObj->release();
    }
}

void CCDictionary2::setObject(CCObject* pObject, int key)
{
    CCAssert(pObject != NULL, "Invalid Argument!");
    if (m_eOldDictType == kCCDictUnknown)
    {
        m_eOldDictType = kCCDictInt;
    }
    m_eDictType = kCCDictInt;
    CCAssert(m_eDictType == m_eOldDictType, "this dictionary does not use integer as key.");

    CCDict2Element *pElement = NULL;
    HASH_FIND_INT(m_pElements, &key, pElement);
    if (pElement == NULL)
    {
        setObjectUnSafe(pObject, key);
    }
    else if (pElement->m_pObject != pObject)
    {
        CCObject* pTmpObj = pElement->m_pObject;
        pTmpObj->retain();
        removeObjectForElememt(pElement);
        setObjectUnSafe(pObject, key);
        pTmpObj->release();
    }

}

void CCDictionary2::removeObjectForKey(const std::string& key)
{
    if (m_eOldDictType == kCCDictUnknown) 
    {
        return;
    }
    CCAssert(m_eDictType == kCCDictStr, "this dictionary does not use string as its key");
    CCAssert(key.length() > 0, "Invalid Argument!");
    CCDict2Element *pElement = NULL;
    HASH_FIND_STR(m_pElements, key.c_str(), pElement);
    removeObjectForElememt(pElement);
}

void CCDictionary2::removeObjectForKey(int key)
{
    if (m_eOldDictType == kCCDictUnknown) 
    {
        return;
    }
    CCAssert(m_eDictType == kCCDictInt, "this dictionary does not use integer as its key");
    CCDict2Element *pElement = NULL;
    HASH_FIND_INT(m_pElements, &key, pElement);
    removeObjectForElememt(pElement);
}

void CCDictionary2::setObjectUnSafe(CCObject* pObject, const std::string& key)
{
    pObject->retain();
    CCDict2Element* pElement = new CCDict2Element(key.c_str(), pObject);
    HASH_ADD_STR(m_pElements, m_szKey, pElement);
}

void CCDictionary2::setObjectUnSafe(CCObject* pObject, const int key)
{
    pObject->retain();
    CCDict2Element* pElement = new CCDict2Element(key, pObject);
    HASH_ADD_INT(m_pElements, m_iKey, pElement);
}

void CCDictionary2::removeObjectsForKeys(CCArray* pKeyArray)
{
    CCObject* pObj = NULL;
    CCARRAY_FOREACH(pKeyArray, pObj)
    {
        CCString* pStr = (CCString*)pObj;
        removeObjectForKey(pStr->getCString());
    }
}

void CCDictionary2::removeObjectForElememt(CCDict2Element* pElement)
{
    if (pElement != NULL)
    {
        HASH_DEL(m_pElements, pElement);
        pElement->m_pObject->release();
        CC_SAFE_DELETE(pElement);
    }
}

void CCDictionary2::removeAllObjects()
{
    CCDict2Element *pElement, *tmp;
    HASH_ITER(hh, m_pElements, pElement, tmp) 
    {
        HASH_DEL(m_pElements, pElement);
        pElement->m_pObject->release();
        CC_SAFE_DELETE(pElement);
    }
}

CCObject* CCDictionary2::copyWithZone(CCZone* pZone)
{
    CCAssert(pZone == NULL, "CCDirctionary should not be inherited.");
    CCDictionary2* pNewDict = new CCDictionary2();

    CCDict2Element* pElement = NULL;
    CCObject* pTmpObj = NULL;

    if (m_eDictType == kCCDictInt)
    {
        CCDICT2_FOREACH(this, pElement)
        {
            pTmpObj = pElement->getObject()->copy();
            pNewDict->setObject(pTmpObj, pElement->getIntKey());
            pTmpObj->release();
        }
    }
    else if (m_eDictType == kCCDictStr)
    {
        CCDICT2_FOREACH(this, pElement)
        {
            pTmpObj = pElement->getObject()->copy();
            pNewDict->setObject(pTmpObj, pElement->getStrKey());
            pTmpObj->release();
        }
    }

    return pNewDict;
}

CCDictionary2* CCDictionary2::dictionary()
{
    return CCDictionary2::create();
}

CCDictionary2* CCDictionary2::create()
{
    CCDictionary2* pRet = new CCDictionary2();
    if (pRet != NULL)
    {
        pRet->autorelease();
    }
    return pRet;
}

CCDictionary2* CCDictionary2::dictionaryWithDictionary(CCDictionary2* srcDict)
{
    return CCDictionary2::create(srcDict);
}

CCDictionary2* CCDictionary2::create(CCDictionary2* srcDict)
{
    CCDictionary2* pNewDict = (CCDictionary2*)srcDict->copy();
    pNewDict->autorelease();
    return pNewDict;
}

CCDictionary2* CCDictionary2::dictionaryWithContentsOfFileThreadSafe(const char *pFileName)
{
    return CCDictionary2::createWithContentsOfFileThreadSafe(pFileName);
}

CCDictionary2* CCDictionary2::createWithContentsOfFileThreadSafe(const char *pFileName)
{
    return ccFileUtils_dictionary2WithContentsOfFileThreadSafe(pFileName);
}

CCDictionary2* CCDictionary2::dictionaryWithContentsOfFile(const char *pFileName)
{
    return CCDictionary2::create(pFileName);
}

CCDictionary2* CCDictionary2::create(const char *pFileName)
{
    CCDictionary2* pRet = createWithContentsOfFileThreadSafe(pFileName);
    pRet->autorelease();
    return pRet;
}

NS_CC_END
