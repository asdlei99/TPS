//============================================================================
// 文件名: AES.h (c++)
// 作者    : 幽灵剑客
// 版本    : 20080213
// 地址    ：http://blog.sina.com.cn/u/1216062855
// 描述    : AES的C++实现，只是对c版的简单封装，性能基本上一样。
//============================================================================

#ifndef AES_H_
#define AES_H_

#include "kdvtype.h"

#define    len16    16
#define    len24    24
#define    len32    32

class AES
{
private:
    unsigned long* State;
    unsigned long* Word;
	unsigned char  Nb,Nr;
	bool  isdecrypt;
public:
    AES();
    ~AES();

    int setMode(
        unsigned char* key,
        int     keySize,
        int     inSize,
        bool     isdecrypt);

    u8 cipher (
        const unsigned char* input,
              unsigned char* output);

    u8 invCipher(
        const unsigned char* input,
              unsigned char* output);
};


unsigned char* base64Decode( const char* in, unsigned int& resultSize, bool trimTrailingZeros = true);  
    // returns a newly allocated array - of size "resultSize" - that  
    // the caller is responsible for delete[]ing.  
  
char* base64Encode(char const* orig, unsigned origLength);  
    // returns a 0-terminated string that  
    // the caller is responsible for delete[]ing.  
#endif /*AES_H_*/