#include "GameOverLayer.h"
#include "StartLayer.h"
#include "HelloWorldScene.h"
#include "Settings.h"
#include "ChineseHelper.h"
USING_NS_CC;

GameOverLayer::GameOverLayer()
{}

GameOverLayer::~GameOverLayer()
{}

CCScene* GameOverLayer::scene()
{
	CCScene* pGameOverScene=NULL;
	do
	{
		pGameOverScene=CCScene::create();
		CC_BREAK_IF(!pGameOverScene);
		GameOverLayer* pGameOverLayer=GameOverLayer::create();
		CC_BREAK_IF(!pGameOverLayer);
		pGameOverScene->addChild(pGameOverLayer);
	} while (0);
	return pGameOverScene;
}
bool GameOverLayer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(! CCLayer::init());
		wchar_t buf[128];
		wsprintf(buf, L"你个笨蛋\n这么久才晒了 %d 张\n得加油才行啊", CCUserDefault::sharedUserDefault()->getIntegerForKey(KEY_NUM_BASKED_PHOTO,0));
		char labelBufDia[128];
		CCLabelTTF *p_DiaLabel=CCLabelTTF::create(getUTF8_buf((char*)buf,labelBufDia,sizeof(labelBufDia)),"Arial",40);
		p_DiaLabel->setPosition(ccp(400,300));
		addChild(p_DiaLabel);
		char labelBufRestart[20]={0};
		CCMenuItemFont* p_ItemRestart=CCMenuItemFont::create(getUTF8_buf((const char*)L"哼，就是不服气", labelBufRestart, sizeof(labelBufRestart)),this,menu_selector(GameOverLayer::menuCallBack));
		p_ItemRestart->setTag(eTagRestart);
		char labelBufQuit[20]={0};
		CCMenuItemFont* p_ItemQuit=CCMenuItemFont::create(getUTF8_buf((const char*)L"算了，我认输好吧", labelBufQuit, sizeof(labelBufQuit)),this,menu_selector(GameOverLayer::menuCallBack));
		p_ItemQuit->setTag(eTagQuit);
		CCMenu *p_Menu=CCMenu::menuWithItems(p_ItemRestart,p_ItemQuit,NULL);
		p_Menu->alignItemsHorizontallyWithPadding(100);
		p_Menu->setPosition(ccp(400,100));
		addChild(p_Menu);
		bRet = true;
	} while (0);
	return bRet;
}

void GameOverLayer::menuCallBack(cocos2d::CCObject* pSender)
{
	CCNode *p_MenuItem=(CCNode*)pSender;
	int tag=p_MenuItem->getTag();
	if (tag==eTagQuit)
	{
		CCTransitionFade *pTransFade1=CCTransitionFade::create(1.2f,StartLayer::scene());
		CCDirector::sharedDirector()->replaceScene(pTransFade1);
	}else if(tag==eTagRestart)
	{
		CCTransitionFade *pTransFade2=CCTransitionFade::create(1.2f,HelloWorld::scene());
		CCDirector::sharedDirector()->replaceScene(pTransFade2);
	}
}



