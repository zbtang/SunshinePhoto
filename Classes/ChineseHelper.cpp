#include "ChineseHelper.h"

//将Unicode小端转为UTF8
int UCS2LEToUTF8(const uint8 *unicode, uint8 *utf8, int size)
{
	int u = 0, i = 0;
	while((unicode[u] || unicode[u+1]) && i <= size-3) //i <= size-3 最多占3个字节，保件缓冲区不越界
	{
		if(unicode[u] < 128 && unicode[u+1] == 0)

		{
			// 0 - 7 bits
			utf8[i++] = unicode[u];
		}else if((unicode[u+1] & 0xf8) == 0){
			// 8 - 11 bits
			utf8[i++] = 0xc0 | (unicode[u+1] << 2) | (unicode[u] >> 6);
			utf8[i++] = 0x80 | (unicode[u] & 0x3f);
		}else{
			// 12 - 16 bits
			utf8[i++] = 0xe0 | (unicode[u+1] >> 4);
			utf8[i++] = 0x80 | ((unicode[u+1] & 0x0f) << 2) | (unicode[u] >> 6);
			utf8[i++] = 0x80 | (unicode[u] & 0x3f);
		}
		u+=2;
	}
	utf8[i] = 0;
	return i;
}

const char *getUTF8_buf(const char *unicode, char *buf, int bufSize)
{
	UCS2LEToUTF8((uint8 *)unicode, (uint8 *)buf, bufSize);
	return (const char*)buf;
}
static int wstrlen(const char *unicode)
{
	int i = 0;
	while(unicode[i] || unicode[i]) // unicode 00 结尾
		i += 2;
	return i/2;
}

const char *getUTF8(const char *unicode)
{
	int l =  wstrlen(unicode)*3 + 1; //一个unicode字符 转为 UTF8 最多3字节（更多的忽略它）
	uint8 *buf = (uint8 *)malloc(l);
	return getUTF8_buf(unicode, (char*)buf, l);
}