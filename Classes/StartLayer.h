#ifndef __START_LAYER_H_
#define __START_LAYER_H_
#include "cocos2d.h"

class StartLayer : public cocos2d::CCLayer
{
public:
	StartLayer();
	~StartLayer();
	virtual bool init();
	static cocos2d::CCScene* scene();
	void menuCallBack(cocos2d::CCObject* pSender);
	CREATE_FUNC(StartLayer);
	enum{
	eTagAbout=0,
	eTagPlay=1,
	eTagMusicCtrl=2
	};

private:
};

#endif