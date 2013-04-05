#ifndef __GAMEOVER_LAYER__
#define __GAMEOVER_LAYER__
#include "cocos2d.h"
class GameOverLayer:public cocos2d::CCLayer
{
public:
	GameOverLayer();
	~GameOverLayer();
	virtual bool init();
	static cocos2d::CCScene* scene();
	void menuCallBack(cocos2d::CCObject* pSender);
	CREATE_FUNC(GameOverLayer);
	enum{
		eTagRestart=1,
		eTagQuit=2,
	};
	
private:
};

#endif