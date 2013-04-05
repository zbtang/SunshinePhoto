#include "cocos2d.h"
#include "CCEGLView.h"
#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "Settings.h"

//#include "SurpriseLayer.h"
#include "StartLayer.h"
using namespace CocosDenshion;

USING_NS_CC;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
    SimpleAudioEngine::end();
}

bool AppDelegate::applicationDidFinishLaunching()
{
	/*CCUserDefault* myUserDefault=CCUserDefault::sharedUserDefault();
	if (myUserDefault->getBoolForKey(KEY_IS_FIRST_RUN,true))
	{
		myUserDefault->setBoolForKey(KEY_IS_FIRST_RUN,false);

		CCLOG("first");

	}else
	{
		CCLOG("not first");
	}*/




    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());


	CCSize designSize=CCSizeMake(800,480);
	CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width,designSize.height,kResolutionExactFit);

    // turn on display FPS
	pDirector->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    //CCScene *pScene = HelloWorld::scene();

    // run
	pDirector->runWithScene(StartLayer::scene());
	//pDirector->runWithScene(SurpriseLayer::scene());
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();

    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();

    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
