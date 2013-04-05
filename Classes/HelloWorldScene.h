#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "vrope.h"

class JiaZi : public cocos2d::CCObject
{
public:
	JiaZi();
	~JiaZi();
	bool isUsing;
};

class HelloWorld : public cocos2d::CCLayer,public b2ContactListener
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();
	b2Body* photoFloating;
	// a selector callback
	void menuCallback(cocos2d::CCObject* pSender);

	void ccTouchesBegan(cocos2d::CCSet *touches, cocos2d::CCEvent *pEvent);

	~HelloWorld();
	// implement the "static node()" method manually
	CREATE_FUNC(HelloWorld);
	enum SpriteTags{
		eTagBackGroundSp=0,
		eTagActionShake=1,
		eTagTimeBoarSp=2,
	};
	enum {
		kPhStateBask=0,
		kPhStateUnbask=1
	};
	b2World *myWorld;
	b2Body* groundBody;
	b2Body* p_jiazi1Body;
	b2Body* p_jiazi2Body;
	b2Body* p_jiazi3Body;
	cocos2d::CCLabelTTF *p_CountLabel;
	int totalCountOfBPhoto;
	int countBaskedPhoto;
	int countDownTime;

	cocos2d::CCSpriteBatchNode *ropeSpriteSheet;
	std::vector<VRope*> vRopes;
	void initPuGongYing();
	void defineGroundBody();
	void createWorld();
	void createDandelionParticle();
	void createRopeAndHook();
	void tick(float time);
	void connect2BodyWithRevoJoint(b2Body* body1,b2Body* body2,b2Vec2 position);
	void createRopeWithBody(b2Body *bodyA,b2Body *bodyB,b2Vec2 anchorA,b2Vec2 anchorB,float sag);
	void addUnbaskPhoto(float dt);
	bool isJiazi(b2Body* body);
	void callBackAnim(CCNode* sender,void* photoData);

	void countDown(float time);


	b2Vec2 getImpulseByPosition(b2Vec2 sourcePosition,b2Vec2 targetPosition);
	virtual void BeginContact(b2Contact* contact);
	virtual void EndContact(b2Contact* contact);
	virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
};
#endif  // __HELLOWORLD_SCENE_H__