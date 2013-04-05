#ifndef __ABOUT_H__
#define __ABOUT_H__
#include "cocos2d.h"

class AboutLayer : public cocos2d::CCLayer
{
public:
	virtual bool init();
	static cocos2d::CCScene* scene();
	void menuCallBack(cocos2d::CCObject* pSender);
	CREATE_FUNC(AboutLayer);
private:
};

#endif