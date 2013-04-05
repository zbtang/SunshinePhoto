#include "Box2dHelper.h"
#include "Settings.h"
USING_NS_CC;
Box2dHelper::Box2dHelper()
{
}
Box2dHelper::~Box2dHelper()
{
}

b2Body* Box2dHelper::createRectBody(b2World* world,cocos2d::CCPoint positionInPix,CCSize rectSizeInPix,bool isStatic,bool isSensor,cocos2d::CCSprite* userData,int groupIndex,bool isFixedRotation)
{
	b2BodyDef rectBodyDef;

	rectBodyDef.fixedRotation=isFixedRotation;
	if (isStatic)
	{
		rectBodyDef.type=b2_staticBody;
	}else{
		rectBodyDef.type=b2_dynamicBody;
	}
	rectBodyDef.position.Set(positionInPix.x/PTM_RATIO,positionInPix.y/PTM_RATIO);
	b2Body* p_RectBody=world->CreateBody(&rectBodyDef);

	b2PolygonShape rectShape;
	rectShape.SetAsBox(rectSizeInPix.width/2/PTM_RATIO,rectSizeInPix.height/2/PTM_RATIO);
	b2FixtureDef bodyFixtureDef;
	bodyFixtureDef.shape=&rectShape;//设置形状
	
	
	bodyFixtureDef.filter.groupIndex=groupIndex;//设置不发生碰撞

	if (isSensor)
	{
		bodyFixtureDef.isSensor=true;
	}else{

		bodyFixtureDef.isSensor=false;
		bodyFixtureDef.density=0.2;//设置密度
		bodyFixtureDef.friction=0.3f;//设置反弹系数
	}
	p_RectBody->CreateFixture(&bodyFixtureDef);
	if (userData)
	{
		p_RectBody->SetUserData(userData);
	}
	return p_RectBody;
}
