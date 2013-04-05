#include "HelloWorldScene.h"
#include "Settings.h"
#include "vrope.h"
#include "Box2dHelper.h"
#include "GameOverLayer.h"
#include "SurpriseLayer.h"
//#include "PhotoManager.h"
#include "Photo.h"
using namespace cocos2d;
HelloWorld::~HelloWorld()
{
	CCUserDefault::sharedUserDefault()->setIntegerForKey(KEY_TOTAL_NUM_OF_BASKED_PHOTO,totalCountOfBPhoto);
	CCUserDefault::sharedUserDefault()->flush();
}
CCScene* HelloWorld::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		HelloWorld *layer = HelloWorld::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}
bool HelloWorld::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(! CCLayer::init());

		countBaskedPhoto=0;
		countDownTime=COUNT_DOWN_TIME;
		totalCountOfBPhoto=CCUserDefault::sharedUserDefault()->getIntegerForKey(KEY_TOTAL_NUM_OF_BASKED_PHOTO,0);

		CCSize  screenSize=CCDirector::sharedDirector()->getWinSize();
		setTouchEnabled(true);//启用触摸
		//setAccelerometerEnabled(true);//开启加速器，使用重力感应
		CCSprite *pBackGroundSprite=CCSprite::create("bg_sunday.jpg");
		pBackGroundSprite->setPosition(ccp(screenSize.width/2,screenSize.height/2));
		addChild(pBackGroundSprite,0,eTagBackGroundSp);

		CCSprite* p_fengCheSprite=CCSprite::create("fengche.png");
		p_fengCheSprite->setPosition(ccp(66,144));
		addChild(p_fengCheSprite);
		CCActionInterval *p_rotateAction=CCRotateBy::create(3,360);
		p_fengCheSprite->runAction(CCRepeatForever::actionWithAction(p_rotateAction));

		initPuGongYing();
		createWorld();
		defineGroundBody();
		createRopeAndHook();
		createDandelionParticle();
		schedule(schedule_selector(HelloWorld::tick));
		schedule(schedule_selector(HelloWorld::addUnbaskPhoto),PHOTO_CREATE_INTERVAL);
		addUnbaskPhoto(1);
		myWorld->SetContactListener(this);

		CCSprite* p_ScoreBoardSprite=CCSprite::create("score.png");
		p_ScoreBoardSprite->setPosition(ccp(507,430));
		addChild(p_ScoreBoardSprite);

		p_CountLabel=CCLabelTTF::create("0","Arial", 20);
		p_ScoreBoardSprite->addChild(p_CountLabel);
		p_CountLabel->setPosition(ccp(95,24));
		p_CountLabel->setColor(ccRED);
		p_CountLabel->setAnchorPoint(ccp(0,0));

		CCEaseInOut *actionMove=CCEaseInOut::actionWithAction(CCMoveBy::create(1.2f,ccp(40,0)),2);
		p_ScoreBoardSprite->runAction(CCRepeatForever::actionWithAction((CCActionInterval*)CCSequence::create(actionMove,actionMove->reverse(),NULL)));
		p_ScoreBoardSprite->setScale(0.8f);

		char tempString[20]={0};
		sprintf(tempString,"Time Left:%ds",COUNT_DOWN_TIME);
		CCLabelTTF *timeNumber=CCLabelTTF::labelWithString(tempString,"Arial", 20);
		timeNumber->setPosition(ccp(120,440));
		timeNumber->setTag(eTagTimeBoarSp);
		addChild(timeNumber);

		schedule(schedule_selector(HelloWorld::countDown),1);

		bRet = true;
	} while (0);
	return bRet;
}
void HelloWorld::initPuGongYing()
{
	/*CCSprite* p_SpritePugongying=CCSprite::create();
	CCMenuItemSprite* p_ItemPugonyin=CCMenuItemSprite::itemWithNormalSprite(p_SpritePugongying,p_SpritePugongying,this,menu_selector(HelloWorld::menuCallback));*/
	CCMenuItemImage* p_ItemPugongying1=CCMenuItemImage::create("pugongying1.png","pugongying1.png",this,menu_selector(HelloWorld::menuCallback));
	p_ItemPugongying1->setAnchorPoint(ccp(0.7841f,0));
	p_ItemPugongying1->setPosition(ccp(275,0));
	p_ItemPugongying1->setScale(0.6f);

	CCMenuItemImage* p_ItemPugongying2=CCMenuItemImage::create("pugongying1.png","pugongying1.png",this,menu_selector(HelloWorld::menuCallback));
	p_ItemPugongying2->setAnchorPoint(ccp(0.7841f,0));
	p_ItemPugongying2->setPosition(ccp(80,0));
	p_ItemPugongying2->setScale(0.9f);


	CCMenuItemImage* p_ItemPugongying3=CCMenuItemImage::create("pugongying1.png","pugongying1.png",this,menu_selector(HelloWorld::menuCallback));
	p_ItemPugongying3->setAnchorPoint(ccp(0.7841f,0));
	p_ItemPugongying3->setPosition(ccp(700,0));
	p_ItemPugongying3->setScale(0.8f);


	CCMenu* p_Menu=CCMenu::menuWithItems(p_ItemPugongying1,p_ItemPugongying2,p_ItemPugongying3,NULL); 
	p_Menu->setPosition(ccp(0,0));
	addChild(p_Menu);
}
void HelloWorld::createRopeAndHook()
{
	CCSize  screenSize=CCDirector::sharedDirector()->getWinSize();


	CCSprite *p_jiazi1Sprite=CCSprite::create("jiazi.png");
	p_jiazi1Sprite->setPosition(ccp(screenSize.width*0.2f,400));
	addChild(p_jiazi1Sprite);
	CCSprite *p_jiazi2Sprite=CCSprite::create("jiazi.png");
	p_jiazi2Sprite->setPosition(ccp(screenSize.width*0.5f,400));
	addChild(p_jiazi2Sprite);
	CCSprite *p_jiazi3Sprite=CCSprite::create("jiazi.png");
	p_jiazi3Sprite->setPosition(ccp(screenSize.width*0.8f,400));
	addChild(p_jiazi3Sprite);

	JiaZi* p_jiazi1=new JiaZi();
	JiaZi* p_jiazi2=new JiaZi();
	JiaZi* p_jiazi3=new JiaZi();

	p_jiazi1Sprite->setUserData(p_jiazi1);
	p_jiazi2Sprite->setUserData(p_jiazi2);
	p_jiazi3Sprite->setUserData(p_jiazi3);
	p_jiazi1->retain();
	p_jiazi2->retain();
	p_jiazi3->retain();
	p_jiazi1->autorelease();
	p_jiazi2->autorelease();
	p_jiazi3->autorelease();
	/*CCSprite *p_jiazi4Sprite=CCSprite::create("jiazi.png");
	p_jiazi4Sprite->setPosition(ccp(650,400));
	addChild(p_jiazi4Sprite);*/
	p_jiazi1Body=Box2dHelper::createRectBody(myWorld,p_jiazi1Sprite->getPosition(),p_jiazi1Sprite->getContentSize(),false,false,p_jiazi1Sprite,GROUP_INDEX_JIAZI,true);
	p_jiazi2Body=Box2dHelper::createRectBody(myWorld,p_jiazi2Sprite->getPosition(),p_jiazi2Sprite->getContentSize(),false,false,p_jiazi2Sprite,GROUP_INDEX_JIAZI,true);
	p_jiazi3Body=Box2dHelper::createRectBody(myWorld,p_jiazi3Sprite->getPosition(),p_jiazi3Sprite->getContentSize(),false,false,p_jiazi3Sprite,GROUP_INDEX_JIAZI,true);
	//p_jiazi4Body=Box2dHelper::createRectBody(myWorld,p_jiazi4Sprite->getPosition(),p_jiazi4Sprite->getContentSize(),false,false,p_jiazi4Sprite,GROUP_INDEX_JIAZI,true);
	ropeSpriteSheet=CCSpriteBatchNode::create("rope.png");
	addChild(ropeSpriteSheet);
	createRopeWithBody(groundBody,p_jiazi1Body,b2Vec2(0/PTM_RATIO, screenSize.height*0.9/PTM_RATIO),p_jiazi1Body->GetLocalCenter(),1);
	createRopeWithBody(p_jiazi1Body,p_jiazi2Body,p_jiazi1Body->GetLocalCenter(),p_jiazi2Body->GetLocalCenter(),1);
	createRopeWithBody(p_jiazi2Body,p_jiazi3Body,p_jiazi2Body->GetLocalCenter(),p_jiazi3Body->GetLocalCenter(),1);
	//createRopeWithBody(p_jiazi3Body,p_jiazi4Body,p_jiazi3Body->GetLocalCenter(),p_jiazi4Body->GetLocalCenter(),1);
	createRopeWithBody(groundBody,p_jiazi3Body,b2Vec2(screenSize.width/PTM_RATIO,screenSize.height*0.9/PTM_RATIO),p_jiazi3Body->GetLocalCenter(),1);
}
void HelloWorld::createDandelionParticle()
{
	CCParticleRain *pRainParticle=CCParticleRain::create();
	pRainParticle->retain();
	pRainParticle->setLife(10);
	pRainParticle->setSpeed(-2);
	pRainParticle->setStartSize(80);
	pRainParticle->setEndSize(50);
	pRainParticle->setGravity(ccp(0,4));
	pRainParticle->setEmissionRate(2);
	pRainParticle->setPositionY(0);
	pRainParticle->setTexture(CCTextureCache::sharedTextureCache()->addImage("pugongying.png"));
	this->addChild(pRainParticle);
}
void HelloWorld::createRopeWithBody(b2Body *bodyA,b2Body *bodyB,b2Vec2 anchorA,b2Vec2 anchorB,float sag)
{
	b2RopeJointDef jd;  
	jd.bodyA = bodyA;  
	jd.bodyB = bodyB; 
	jd.localAnchorA.Set(anchorA.x,anchorA.y);  
	jd.localAnchorB.Set(anchorB.x,anchorB.y);  
	float32 ropeLength = (bodyA->GetWorldPoint(anchorA) - bodyB->GetWorldPoint(anchorB)).Length() * sag;  
	jd.maxLength = ropeLength; 
	b2RopeJoint *ropeJoint = (b2RopeJoint *)myWorld->CreateJoint(&jd); 
	VRope *newRope = new VRope(ropeJoint,ropeSpriteSheet);  
	vRopes.push_back(newRope);
}
void HelloWorld::createWorld()
{
	b2Vec2 gravity;
	gravity.Set(0,-9.8f);
	bool doSleep=true;
	myWorld=new b2World(gravity);
	myWorld->SetAllowSleeping(doSleep);
	myWorld->SetContinuousPhysics(true);

}
void HelloWorld::defineGroundBody()
{
	CCSize  screenSize=CCDirector::sharedDirector()->getWinSize();
	// Define the ground body.
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0, 0); // bottom-left corner
	groundBody = myWorld->CreateBody(&groundBodyDef);
	// Define the ground box shape.
	b2EdgeShape groundBox;
	//bottom
	groundBox.Set(b2Vec2(-screenSize.width/PTM_RATIO,-screenSize.height/PTM_RATIO), b2Vec2(2*screenSize.width/PTM_RATIO,-screenSize.height/PTM_RATIO));
	groundBody->CreateFixture(&groundBox,0);

	// top
	groundBox.Set(b2Vec2(-120.0f/PTM_RATIO,(screenSize.height+150.0f)/PTM_RATIO), b2Vec2((120.0f+screenSize.width)/PTM_RATIO,(screenSize.height+150.0f)/PTM_RATIO));
	groundBody->CreateFixture(&groundBox,0);

	/*groundBox.Set(b2Vec2(-0/PTM_RATIO,(screenSize.height)/PTM_RATIO), b2Vec2((screenSize.width)/PTM_RATIO,(screenSize.height)/PTM_RATIO));
	groundBody->CreateFixture(&groundBox,0);*/
	// left
	groundBox.Set(b2Vec2(-120/PTM_RATIO,(screenSize.height+120.0f)/PTM_RATIO), b2Vec2(-120.0f/PTM_RATIO,0/PTM_RATIO));
	groundBody->CreateFixture(&groundBox,0);

	// right
	groundBox.Set(b2Vec2((screenSize.width+120.0f)/PTM_RATIO,0/PTM_RATIO), b2Vec2((screenSize.width+120.0f)/PTM_RATIO,(screenSize.height+120.0f)/PTM_RATIO));
	groundBody->CreateFixture(&groundBox,0);
}
void HelloWorld::tick(float dt)
{
	int32 velocityIterations = 8;  
	int32 positionIterations = 1;  
	// Instruct the world to perform a single step of simulation.  
	myWorld->Step(dt, velocityIterations, positionIterations); 
	for (b2Body* b = myWorld->GetBodyList(); b;)  
	{  
		CCSprite *myActor = (CCSprite*)b->GetUserData();  
		if (myActor)  
		{  
			//Synchronize the AtlasSprites position and rotation with the corresponding body  
			myActor->setPosition(CCPointMake( b->GetPosition().x * PTM_RATIO, b->GetPosition().y * PTM_RATIO));  
			myActor->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle())); 
			Photo* myPhotoTemp=(Photo*)myActor->getUserData();
			if (myPhotoTemp&&(myPhotoTemp->currentState==myPhotoTemp->eStateFloating))
			{
				b->ApplyForceToCenter(b2Vec2(0,10*b->GetMass()));
			}else if(myPhotoTemp&&myPhotoTemp->currentState==myPhotoTemp->eStateGone)
			{
				b2Body* b2BodyTemp=b;
				b=b->GetNext();
				b2BodyTemp->SetUserData(NULL);
				myActor->setUserData(NULL);
				myPhotoTemp->release();
				removeChild(myActor,true);
				myWorld->DestroyBody(b2BodyTemp);
				b2BodyTemp=NULL;
				myActor=NULL;
				myPhotoTemp=NULL;
				continue;
			}else if(myPhotoTemp&&myPhotoTemp->currentState==myPhotoTemp->eStateHanging)
			{
				if(!myPhotoTemp->hasConnectWithJiazi)
				{
					myPhotoTemp->hasConnectWithJiazi=true;
					connect2BodyWithRevoJoint(b,myPhotoTemp->jiaZiToConnect,myPhotoTemp->jiaZiToConnect->GetPosition());

					CCAnimation* p_animationTemp=CCAnimation::animation();
					char frameName[20]={0};
					for (int i = 2; i > 0; i--)
					{
						sprintf(frameName,"photo_%d_%d.jpg",myPhotoTemp->photoId+1,i);
						CCLOG("%s",frameName);
						p_animationTemp->addSpriteFrameWithFileName(frameName);
					}
					p_animationTemp->setRestoreOriginalFrame(false);
					p_animationTemp->setDelayPerUnit(TIME_TO_BASK_PHOTO);
					CCAnimate* p_actionTemp=CCAnimate::create(p_animationTemp);

					CCFiniteTimeAction* actions=CCSequence::actions(p_actionTemp,CCFadeOut::actionWithDuration(1.5f),CCCallFuncND::actionWithTarget(this, callfuncND_selector(HelloWorld::callBackAnim),(void*)myPhotoTemp),NULL);
					myActor->runAction(actions);

				}
			}
		}  
		b = b->GetNext();
	}  
	// Update all the ropes  
	std::vector<VRope*>::iterator pos;  
	for (pos=vRopes.begin();pos!=vRopes.end();pos++)  
	{  
		(*pos)->update(dt);  
		(*pos)->updateSprites();  
	}  
}
void HelloWorld::countDown(float time)
{
	countDownTime--;
	if(countDownTime>=0){
		CCLabelTTF *tempLabel=(CCLabelTTF*)getChildByTag(eTagTimeBoarSp);
		char timeLeftString[20]={0};
		sprintf(timeLeftString,"Time Left:%ds",countDownTime);
		tempLabel->setString(timeLeftString);
	}else{

		CCUserDefault::sharedUserDefault()->setIntegerForKey(KEY_NUM_BASKED_PHOTO,countBaskedPhoto);
		CCUserDefault::sharedUserDefault()->flush();
		CCTransitionFade *pTransFade2=CCTransitionFade::create(1.2f,GameOverLayer::scene());
		CCDirector::sharedDirector()->replaceScene(pTransFade2);
	}


}
void HelloWorld::menuCallback(CCObject* pSender)
{

	CCNode* pMenuNode=(CCNode*)pSender;
	;
	if(pMenuNode->getActionByTag(eTagActionShake)&&(!pMenuNode->getActionByTag(eTagActionShake)->isDone())) return;

	CCRotateBy *rotaBy1 = CCRotateBy::actionWithDuration(0.2,-10);//逆时针转20度
	CCRotateBy *rotaBy2 = CCRotateBy::actionWithDuration(0.2,10);//顺时针转20度
	CCEaseInOut *ease1 = CCEaseInOut::actionWithAction(rotaBy1,2);//逆时针时摆动时先匀加速再匀减速运动
	CCEaseInOut *ease2 = CCEaseInOut::actionWithAction(rotaBy2,2);//顺时针时摆动时先匀加速再匀减速运动
	CCEaseInOut *ease3=CCEaseInOut::actionWithAction(CCRotateBy::actionWithDuration(0.2,-5),2);
	CCEaseInOut *ease4=CCEaseInOut::actionWithAction(CCRotateBy::actionWithDuration(0.2,5),2);
	CCAction* actionsShake=CCSequence::create(ease1,ease2,ease3,ease4,NULL);
	actionsShake->setTag(eTagActionShake);

	pMenuNode->runAction(actionsShake);
	CCPoint tempPoint=pMenuNode->getPosition();
	if (photoFloating)
	{
		photoFloating->ApplyLinearImpulse(getImpulseByPosition(b2Vec2(tempPoint.x/PTM_RATIO,tempPoint.y/PTM_RATIO),photoFloating->GetPosition()),photoFloating->GetPosition());
	} 

	CCParticleFlower* p_ParticalFlower=CCParticleFlower::create();
	addChild(p_ParticalFlower);
	p_ParticalFlower->setTexture(CCTextureCache::sharedTextureCache()->addImage("dandelion_seed.png"));
	p_ParticalFlower->setPosition(ccp(tempPoint.x,tempPoint.y+pMenuNode->getContentSize().height*pMenuNode->getScaleY()*0.8f));
	p_ParticalFlower->setDuration(2);
	p_ParticalFlower->setAutoRemoveOnFinish(true);
}
void HelloWorld::callBackAnim(CCNode* sender,void* photoData)
{
	countBaskedPhoto++;
	totalCountOfBPhoto++;
	if (totalCountOfBPhoto==SURPRISE_PHOTO_COUNT)
	{
		CCTransitionFade *pTransFade2=CCTransitionFade::create(1.2f,SurpriseLayer::scene());
		CCDirector::sharedDirector()->replaceScene(pTransFade2);
		return;
	}
	char tempString[10]={0};
	sprintf(tempString,"%d",countBaskedPhoto);
	p_CountLabel->setString(tempString);
	Photo* photo=(Photo*)photoData;
	photo->currentState=photo->eStateGone;
	b2Body* jiaziBodyTemp=photo->jiaZiToConnect;
	JiaZi* jiaziData=(JiaZi*)((CCSprite*)jiaziBodyTemp->GetUserData())->getUserData();
	jiaziData->isUsing=false;
	myWorld->DestroyJoint(jiaziBodyTemp->GetJointList()->joint);
}
void HelloWorld::ccTouchesBegan(CCSet *touches, CCEvent *pEvent) 
{
	//CCLOG("touch began!");

}
void HelloWorld::connect2BodyWithRevoJoint(b2Body* body1,b2Body* body2,b2Vec2 position)
{
	b2RevoluteJointDef m_revoluteJointDef;
	m_revoluteJointDef.Initialize(body1,body2,position);
	myWorld->CreateJoint(&m_revoluteJointDef);
}
void HelloWorld::addUnbaskPhoto(float dt)
{
	int photoIdTemp=(int)(CCRANDOM_0_1()*MAX_PHOTO_ID);
	Photo* photoTemp=new Photo(photoIdTemp);
	photoTemp->currentState=photoTemp->eStateFloating;

	char tempPhotoName[20]={0};
	sprintf(tempPhotoName,"photo_%d_2.jpg",photoIdTemp+1);
	CCSprite* photoSpriteTemp=CCSprite::create(tempPhotoName);

	photoSpriteTemp->setPosition(ccp(100.0f+CCRANDOM_0_1()*500.0f,60));
	photoSpriteTemp->setUserData(photoTemp);
	photoTemp->retain();
	addChild(photoSpriteTemp);
	b2Body* p_bodyTemp=Box2dHelper::createRectBody(myWorld,photoSpriteTemp->getPosition(),photoSpriteTemp->getContentSize(),false,false,photoSpriteTemp,GROUP_INDEX_PHOTO,false);
	p_bodyTemp->SetLinearVelocity(b2Vec2(-2.0f+CCRANDOM_0_1()*4.0f,1.0f));
	photoTemp->autorelease();
	photoFloating=p_bodyTemp;
}
void HelloWorld::BeginContact(b2Contact* contact)
{
	b2Fixture *fixtureA,*fixtureB;
	fixtureA=contact->GetFixtureA();
	fixtureB=contact->GetFixtureB();

	CCSprite* tempSprite;
	Photo* tempPhoto;
	JiaZi* tempJiazi;
	if(fixtureA->GetBody()==groundBody){
		//bodiesTodelete.push_back(fixtureB->GetBody());
		tempSprite= (CCSprite*)fixtureB->GetBody()->GetUserData();
		tempPhoto=(Photo*)tempSprite->getUserData();
		tempPhoto->currentState=tempPhoto->eStateGone;

	}else if(fixtureB->GetBody()==groundBody){
		//bodiesTodelete.push_back(fixtureA->GetBody());
		tempSprite= (CCSprite*)fixtureA->GetBody()->GetUserData();
		tempPhoto=(Photo*)tempSprite->getUserData();
		tempPhoto->currentState=tempPhoto->eStateGone;
	}else if(isJiazi(fixtureA->GetBody()))
	{
		b2Body* jiaZiBody=fixtureA->GetBody();
		tempSprite=(CCSprite*)jiaZiBody->GetUserData();
		tempJiazi=(JiaZi*)tempSprite->getUserData();
		if(tempJiazi->isUsing)
		{
			return;
		}else
		{
			b2Body* photoBody=fixtureB->GetBody();
			tempSprite=(CCSprite*)photoBody->GetUserData();
			tempPhoto=(Photo*)tempSprite->getUserData();
			tempPhoto->currentState=tempPhoto->eStateHanging;
			tempPhoto->jiaZiToConnect=jiaZiBody;
			tempJiazi->isUsing=true;
		}
	}else if(isJiazi(fixtureB->GetBody()))
	{
		b2Body* jiaZiBody=fixtureB->GetBody();
		tempSprite=(CCSprite*)jiaZiBody->GetUserData();
		tempJiazi=(JiaZi*)tempSprite->getUserData();
		if(tempJiazi->isUsing)
		{
			return;
		}else
		{
			b2Body* photoBody=fixtureA->GetBody();
			tempSprite=(CCSprite*)photoBody->GetUserData();
			tempPhoto=(Photo*)tempSprite->getUserData();
			tempPhoto->currentState=tempPhoto->eStateHanging;
			tempPhoto->jiaZiToConnect=jiaZiBody;
		}
	}
}
void HelloWorld::EndContact(b2Contact* contact)
{
	//CCLOG("End contact");

}
void HelloWorld::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
	//CCLOG("presolve");
}
bool HelloWorld::isJiazi(b2Body* body)
{
	bool isJiaZiBool=true;
	if (body!=p_jiazi1Body&&body!=p_jiazi2Body&&body!=p_jiazi3Body)
	{
		isJiaZiBool=false;
	}
	return isJiaZiBool;
}
b2Vec2 HelloWorld::getImpulseByPosition(b2Vec2 sourcePosition,b2Vec2 targetPosition)
{
	b2Vec2 tempVec2=targetPosition-sourcePosition;

	tempVec2*=(5.0f/tempVec2.Length());
	return tempVec2;
}
JiaZi::JiaZi():isUsing(false)
{}
JiaZi::~JiaZi()
{}