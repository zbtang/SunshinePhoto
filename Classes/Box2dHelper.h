#ifndef __BOX2D_HELPER_H__
#define __BOX2D_HELPER_H__
#include "Box2D\Box2D.h"
#include "cocos2d.h"

class Box2dHelper
{
public:
	Box2dHelper();
	~Box2dHelper();
	static b2Body* createRectBody(b2World* world,cocos2d::CCPoint positionInPix,cocos2d::CCSize rectSizeInPix,bool isStatic,bool isSensor,cocos2d::CCSprite* userData,int groupIndex,bool isFixedRotation);
private:

};
#endif