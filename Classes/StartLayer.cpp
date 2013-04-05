#include "StartLayer.h"
#include "AboutLayer.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

StartLayer::StartLayer()
{}
StartLayer::~StartLayer()
{}

CCScene* StartLayer::scene()
{
	CCScene *pStartScene=NULL;
	do{
		pStartScene=CCScene::create();
		CC_BREAK_IF(! pStartScene);
		StartLayer *pStartLayer=StartLayer::create();
		CC_BREAK_IF(!pStartLayer);
		pStartScene->addChild(pStartLayer);
	}while(0);
	return pStartScene;
}

bool StartLayer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(! CCLayer::init());
		CCSize screenSize=CCDirector::sharedDirector()->getWinSize();
		CCSprite* p_BgStartSprite=CCSprite::create("bg_start_scene.jpg");
		p_BgStartSprite->setPosition(ccp(screenSize.width/2,screenSize.height/2));
		addChild(p_BgStartSprite);

		CCMenuItemImage *p_BtnAbout=CCMenuItemImage::create("btn_about.png","btn_about.png",this,menu_selector(StartLayer::menuCallBack));
		p_BtnAbout->setTag(eTagAbout);
		p_BtnAbout->setPosition(ccp(519,340));
		p_BtnAbout->setScale(1.4f);
		CCRepeatForever* actionJump=CCRepeatForever::actionWithAction(CCJumpBy::create(1.0f,ccp(0,0),10,1));
		p_BtnAbout->runAction(actionJump);

		CCSprite *p_TreeSprite=CCSprite::create("tree.png");
		p_TreeSprite->setAnchorPoint(ccp(0.4336f,0));
		p_TreeSprite->setPosition(ccp(75,125));
		addChild(p_TreeSprite);

		CCRotateBy *rotaBy1 = CCRotateBy::actionWithDuration(0.6,-8);//逆时针转20度
		CCEaseInOut *ease1 = CCEaseInOut::actionWithAction(rotaBy1,2);//逆时针时摆动时先匀加速再匀减速运动
		CCAction* actionsShake=CCSequence::create(ease1,ease1->reverse(),NULL);

		p_TreeSprite->runAction(CCRepeatForever::actionWithAction((CCActionInterval*)actionsShake));
		CCMenuItemImage *p_BtnStart=CCMenuItemImage::create("btn_start.png","btn_start.png",this,menu_selector(StartLayer::menuCallBack));
		p_BtnStart->setPosition(ccp(530,225));
		p_BtnStart->setTag(eTagPlay);
		CCEaseInOut *scaleEase=CCEaseInOut::actionWithAction(CCScaleBy::create(0.6f,1.2),2);
		CCAction* actionsScale=CCSequence::create(scaleEase,scaleEase->reverse(),NULL);
		p_BtnStart->runAction(CCRepeatForever::actionWithAction((CCActionInterval*)actionsScale));



		CCMenuItemImage *p_BtnMusic=CCMenuItemImage::create("music.png","music.png",this,menu_selector(StartLayer::menuCallBack));
		p_BtnMusic->setTag(eTagMusicCtrl);
		p_BtnMusic->setPosition(ccp(370,106));

		//CCFlipX3D *actionRotate=CCFlipX3D::create(0.6);
		CCActionInterval *actionRotate=CCOrbitCamera::create(1.0f,1, 0, 0, 360, 0, 0);
		//CCActionInterval *actionMusic=CCSpawn::actionOneTwo(actionRotate,CCJumpBy::create(1.0f,ccp(0,0),10,1));

		p_BtnMusic->runAction(CCRepeatForever::create(actionRotate));
		CCMenu *p_Menu=CCMenu::menuWithItems(p_BtnStart,p_BtnAbout,p_BtnMusic,NULL);
		p_Menu->setPosition(ccp(0,0));
		addChild(p_Menu);

		if (!CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic( CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("bg_sound.mp3") );
			CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.5);
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(std::string(CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("bg_sound.mp3")).c_str(),true);
		}
		bRet = true;
	} while (0);
	return bRet;

}

void StartLayer::menuCallBack(CCObject* pSender)
{
	CCNode* pNodeSender=(CCNode*)pSender;
	int tag=pNodeSender->getTag();
	if (tag==eTagPlay)
	{
		CCTransitionFade *pTransFade1=CCTransitionFade::create(1.2f,HelloWorld::scene());
		CCDirector::sharedDirector()->replaceScene(pTransFade1);
	}else if(tag==eTagAbout)
	{
		CCTransitionFade *pTransFade2=CCTransitionFade::create(1.2f,AboutLayer::scene());
		CCDirector::sharedDirector()->replaceScene(pTransFade2);
	}else if(tag==eTagMusicCtrl)
	{
		if (CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
		{
			pNodeSender->stopAllActions();
			CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
		}
		else
		{
			CCActionInterval *actionRotate=CCOrbitCamera::create(1.0f,1, 0, 0, 360, 0, 0);
			//CCActionInterval *actionMusic=CCSpawn::actionOneTwo(actionRotate,CCJumpBy::create(1.0f,ccp(0,0),10,1));
			pNodeSender->runAction(CCRepeatForever::create(actionRotate));
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(std::string(CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("bg_sound.mp3")).c_str(),true);
		}
	}
}