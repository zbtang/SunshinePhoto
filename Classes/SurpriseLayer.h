#ifndef __SURPRISE_LAYER__
#define __SURPRISE_LAYER__
#include "cocos2d.h"

class SurpriseLayer:public cocos2d::CCLayer
{
public:
	SurpriseLayer();
	~SurpriseLayer();
	static cocos2d::CCScene* scene();
	virtual bool init();
	void menuCallBack(cocos2d::CCObject* pSender);
	void tick(float dt);
	CREATE_FUNC(SurpriseLayer);
private:
};



#endif