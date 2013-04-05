#ifndef __PHYSICS_SPRITE_H__
#define __PHYSICS_SPRITE_H__

#include "cocos2d.h"
#include "Box2D\Box2D.h"

class PhysicsSprite:public cocos2d::CCSprite
{
public:
	PhysicsSprite();
	void setPhysicsBody(b2Body * body);
	virtual bool isDirty(void);
	virtual cocos2d::CCAffineTransform nodeToParentTransform(void);
private:
	b2Body* m_pBody;
};
#endif