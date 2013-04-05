#ifndef __CHINESE_HELPER__
#define __CHINESE_HELPER__
#include "cocos2d.h"
typedef unsigned char uint8;
int UCS2LEToUTF8(const uint8 *unicode, uint8 *utf8, int size);
const char *getUTF8_buf(const char *unicode, char *buf, int bufSize);
static int wstrlen(const char *unicode);
const char *getUTF8(const char *unicode);

#endif