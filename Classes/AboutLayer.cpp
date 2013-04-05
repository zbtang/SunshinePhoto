#include "StartLayer.h"
#include "AboutLayer.h"
USING_NS_CC;
CCScene* AboutLayer::scene()
{
	CCScene *pAboutScene=NULL;
	do{
		pAboutScene=CCScene::create();
		CC_BREAK_IF(! pAboutScene);
		AboutLayer *pAboutLayer=AboutLayer::create();
		CC_BREAK_IF(!pAboutLayer);
		pAboutScene->addChild(pAboutLayer);
	}while(0);
	return pAboutScene;
}

bool AboutLayer::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(! CCLayer::init());
		CCSprite *p_AboutSprite=CCSprite::create("bg_about.jpg");
		p_AboutSprite->setPosition(ccp(400,240));
		addChild(p_AboutSprite);

		CCMenuItemImage* p_BtnBack=CCMenuItemImage::create("btn_back1.png","btn_back2.png",this,menu_selector(AboutLayer::menuCallBack));
		p_BtnBack->setPosition(ccp(80,420));
		CCMenu *p_MenuAbout=CCMenu::menuWithItem(p_BtnBack);
		p_MenuAbout->setPosition(ccp(0,0));
		addChild(p_MenuAbout);

		bRet = true;
	} while (0);
	return bRet;
}

void AboutLayer::menuCallBack(CCObject* pSender)
{
	CCTransitionFade *pTransFade=CCTransitionFade::create(1.2f,StartLayer::scene());
	CCDirector::sharedDirector()->replaceScene(pTransFade);
}