#include "SurpriseLayer.h"
#include "ChineseHelper.h"
#include "HelloWorldScene.h"
USING_NS_CC;
SurpriseLayer::SurpriseLayer()
{
}

SurpriseLayer::~SurpriseLayer()
{
}
CCScene* SurpriseLayer::scene()
{
	CCScene* pSurpriseScene=NULL;
	do
	{
		pSurpriseScene=CCScene::create();
		CC_BREAK_IF(!pSurpriseScene);
		SurpriseLayer* pSurpriseLayer=SurpriseLayer::create();
		CC_BREAK_IF(!pSurpriseLayer);
		pSurpriseScene->addChild(pSurpriseLayer);
	} while (0);
	return pSurpriseScene;
}

bool SurpriseLayer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(! CCLayer::init());
		schedule(schedule_selector(SurpriseLayer::tick),1);
		char labelBuf[300];
		CCLabelTTF *p_DiaLabel=CCLabelTTF::create(getUTF8_buf((char*)L"恭喜你\n不知不觉间\n你已晒好了521张照片\n在这个特别的数字里\n送你漫天的浪漫烟花\n如果喜欢\n可以多看一会\n因为只有一次\n另外\n如果你是卢秋燕\n请打电话给我\n有个东西要给你\n如果不是，但你认识她\n请帮忙转告\n谢谢啦",labelBuf,sizeof(labelBuf)),"Arial",40);
		p_DiaLabel->setPosition(ccp(400,300));
		p_DiaLabel->setFontSize(15);
		addChild(p_DiaLabel,1);

		CCMenuItemFont *p_BtnBack=CCMenuItemFont::create("BACK",this,menu_selector(SurpriseLayer::menuCallBack));
		CCMenu *p_Menu=CCMenu::menuWithItem(p_BtnBack);
		p_Menu->setPosition(ccp(700,70));
		addChild(p_Menu,1);
		bRet = true;
	} while (0);
	return bRet;
}
void SurpriseLayer::menuCallBack(cocos2d::CCObject* pSender)
{
	CCTransitionFade *pTransFade2=CCTransitionFade::create(1.2f,HelloWorld::scene());
	CCDirector::sharedDirector()->replaceScene(pTransFade2);
}
void SurpriseLayer::tick(float dt)
{
	CCParticleExplosion *tempExplosion=CCParticleExplosion::create();
	addChild(tempExplosion,0);
	tempExplosion->setTexture( CCTextureCache::sharedTextureCache()->addImage("stars.png") );
	tempExplosion->setDuration(1);
	tempExplosion->setAutoRemoveOnFinish(true);
	tempExplosion->setPosition(ccp(800*CCRANDOM_0_1(),480*CCRANDOM_0_1()));
}