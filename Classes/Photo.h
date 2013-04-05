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
		eStateUnborn=0,//��Ƭ��δ����
		eStateFloating,//��ƬƮ�ڿ���
		eStateHanging,//��Ƭ������������
		eStateGone,//��ƬƮ��������
		eStateFinished//��Ƭɹ����
	}currentState;
};

#endif 