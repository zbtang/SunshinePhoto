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
		CCLabelTTF *p_DiaLabel=CCLabelTTF::create(getUTF8_buf((char*)L"��ϲ��\n��֪������\n����ɹ����521����Ƭ\n������ر��������\n��������������̻�\n���ϲ��\n���Զ࿴һ��\n��Ϊֻ��һ��\n����\n�������¬����\n���绰����\n�и�����Ҫ����\n������ǣ�������ʶ��\n���æת��\nлл��",labelBuf,sizeof(labelBuf)),"Arial",40);
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