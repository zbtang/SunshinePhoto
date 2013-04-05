#ifndef __PHOTO_H__
#define __PHOTO_H__
#include "cocos2d.h"
#include "Box2D\Box2D.h"
class Photo:public cocos2d::CCObject
{
public:
	Photo(int photoID);
	~Photo();
	b2Body* jiaZiToConnect;
	bool hasConnectWithJiazi;
	int photoId;
	int photoLife;
	enum CurrentState{
		eStateUnborn=0,//照片还未出生
		eStateFloating,//照片飘在空中
		eStateHanging,//照片正挂在绳子上
		eStateGone,//照片飘出了世界
		eStateFinished//照片晒好了
	}currentState;
};

#endif 