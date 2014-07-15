
//
//  GameUtils.h
//  MetalWar
//
//  Created by user on 12-7-19.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef MetalWar_GameUtils_h
#define MetalWar_GameUtils_h

#include <boost/date_time/posix_time/posix_time.hpp>

#include "cocos2d.h"

class GameUtils
{
public:
    /**
     CCString转化方法
     */
	static cocos2d::CCString * GXCCStringMake(uint32_t value);
	static cocos2d::CCString * GXCCStringMake(int32_t value);
	static cocos2d::CCString * GXCCStringMake(int16_t value);
	static cocos2d::CCString * GXCCStringMake(uint16_t value);
	static cocos2d::CCString * GXCCStringMake(float value);
    
    static const std::string StringMake(const uint32_t value);
    static const std::string StringMake(const int32_t value);
    static const std::string StringMake(const float value);
    /**
     把字节码转为十六进制码，一个字节两个十六进制，内部为字符串分配空间
     */
	static char* ByteToHex(const unsigned char* vByte, const int vLen);
    
    /**
     把十六进制字符串，转为字节码，每两个十六进制字符作为一个字节
     */
	static unsigned char* HexToByte(const char* szHex,const int iLen);
    
    /**
     替换过一个string(strbig)中的某些字符str成strdst
     */
    static std::string stringReplace(const std::string &strbig,
                                     const std::string &str,
                                     const std::string &strdst);
	
    /**
     char转成hex
     */
	static std::string Char2Hex(char a);
	static unsigned int Hex2Int(const char* str, int len);
    /**
     utf-8转成宽字符
     */
	static std::wstring UTF2Uni(const char* src, std::wstring &t);
    
    /**
     utf-8转成unicode
     */
	static std::string utf82ucs2(const char * aBufUTF8);
    
//    /**
//     RC4加密解密
//     */
//    static void encryptFile(const char * filename,
//                            unsigned char * aBuffer,
//                            int aBufferLength);
//    
	static void encryptRC4(char * aBuffer,
                           int aBufferLength,
                           const char *aToken,
                           int aTokenLength);
    
   static const std::string makeStringMd5(const char * text);
    
    /**
    BASE64加密解密
     */
	static std::string base64_encode(unsigned char const* , unsigned int len);
	static std::string base64_decode(std::string const& s);
    
    
    /**
     获取时间
     */
//    static std::string getTimeString(boost::posix_time::ptime &timestamp, const char* charT = NULL);
    
    /**
     获取时间精确到分钟
     */
//    static std::string getTimeStringm(boost::posix_time::ptime &timestamp, const char* charT = NULL);
//    static std::string getTimeString(boost::gregorian::date& date, const char* charT = NULL);
//    
//    
//    static boost::posix_time::ptime ptime_from_epoch(unsigned long long ms);
//	static boost::posix_time::ptime local_ptime_from_epoch(unsigned long long ms);
//    static boost::posix_time::ptime beijing_ptime_from_epoch(unsigned long long ms);
//    
//	static int64_t local_epoch_time();
//    static std::string getLastTime(std::string time1,std::string time2);
    
    /*
     把时间秒数转化成 HH:MM:SS
     */
	static std::string timeToString(const float secondsElapsed);
    
    /**
     HH:MM:SS
     */
    static std::string timeToStringFormat(const float secondsElapsed);
    
    /*
     对一个HEX字符串进行加密RC4加密
     */
	static std::string RC4WithToken(const std::string & text,
                                    const std::string & token);
    
    /*
     对一个字符串转化为坐标
     */
    static const std::vector<std::string>  string2Array(const std::string & text,
                                                        const std::string & tag = ",");
    static const std::vector<int32_t>  string2IntArray(const std::string & text,
                                                       const std::string & tag = ",");
    
	static const cocos2d::CCPoint string2Point(const std::string & text,const std::string & tag = ",");
	static const cocos2d::CCSize  string2Size(const std::string & text,const std::string & tag= ",");
    static cocos2d::CCRect  string2Rect(const std::string & text,const std::string & tag= ",");
    
    static const cocos2d::CCPoint uintVector(const cocos2d::CCPoint & start,
                                       const cocos2d::CCPoint & end);
    
    static const float vector2AngleDegress(const cocos2d::CCPoint & vector);
    static const cocos2d::CCPoint angleDegress2uintVector(const float angleDegress);
    
    static const std::string createDefaultRC4Key(const std::string& scretKey);
    
    const std::string string_rc4(const std::string &text, const std::string &rc4_token);
    
    static void changeOpacity(cocos2d::CCNode* node,GLubyte opacity);
    
    static float UiInterfaceScale();
    
private:
//    static void encryptFileItem(unsigned char * aBuffer,int start,int len,const std::string & key);
    
    


};

#endif
