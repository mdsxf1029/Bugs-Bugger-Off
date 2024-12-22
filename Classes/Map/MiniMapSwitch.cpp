/*2351271 ��߮��*/
#include "Map/MiniMap.h"
#include "cocos2d.h"
std::shared_ptr<Player> _player1 = GlobalManager::getInstance().getPlayer();
/*����ȥ���ڵ�ͼ����ľˮ������ׯ�Ǳ�*/ 
void MiniMap::BoatingToMap(const std::string& objectMap)
{
	CCLOG("boat to!!!!!!!");																							// �����Ϣ 
	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();												// ��ȡ�ɼ������С
	CCLOG("boat to2222");																								// �����Ϣ
	auto boatScene = cocos2d::Scene::create();																			// �������ɳ���
	CCLOG("boat to3333");																								// �����Ϣ 
	cocos2d::Sprite* boatSprite;																						// �������� -- ���ȳ���
	if (mapName == "smallmap/whole3.tmx" || (mapName == "smallmap/fire.tmx" && objectMap == "smallmap/whole3.tmx")) {	// ����Ǵ�ˮ��ׯ�Ǳ�ȥ�����ׯ�Ǳ�
		boatSprite = cocos2d::Sprite::create("CloseNormal.png");														// ��������
	}
	else {
		boatSprite = cocos2d::Sprite::create("CloseSelected.png");														// ��������
	}

	boatSprite->setContentSize(visibleSize);																			// ���þ����С �� �ɼ�����һ����
	boatSprite->setPosition(visibleSize / 2);																			// ���þ���λ��Ϊ��Ļ����
	boatScene->addChild(boatSprite);																					// ��������ӵ����ɳ���
	auto boatTransition1 = cocos2d::TransitionSlideInT::create(0.5f, boatScene);										// �������ɶ���
	cocos2d::Director::getInstance()->replaceScene(boatTransition1);													// ���ع��ȳ��������浱ǰ����
	std::shared_ptr<Player> player1 = GlobalManager::getInstance().getPlayer();											// ��ȡ���
	_player1->removeFromParent();																						// �Ƴ���ң��ϸ�������
	auto newScene = createWithMap(objectMap, false);																	// �����³���ͼ��
	auto boatTransition2 = cocos2d::TransitionSlideInT::create(0.5f, newScene);											// �����³���
	cocos2d::Director::getInstance()->replaceScene(boatTransition2);													// �����³�����������ɳ���
}

/*����ȥ���ڵ�ͼ����ת����ľˮ������ׯ�Ǳ���ǰ���Թ�/����������Թ�/�������˳�*/ 
void MiniMap::FlyToMap(const std::string& objectMap)
{
	CCLOG("flyto111"); 																									// �����Ϣ
	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();												// ��ȡ�ɼ�����Ĵ�С
	auto flyScene = cocos2d::Scene::create();																			// �������ɳ���
	auto flySprite = cocos2d::Sprite::create("UI/X.png");																// ��������
	flySprite->setContentSize(visibleSize);																				// ���þ���Ĵ�С����Ļһ����
	flySprite->setPosition(visibleSize / 2);																			// ���þ����λ��Ϊ��Ļ����
	flyScene->addChild(flySprite);																						// ��������ӵ����ɳ���
	auto flyTransition1 = cocos2d::TransitionSlideInT::create(2.0f, flyScene);											// �������ɶ���

	/*�����ǰ���Թ��򾺼���*/ 
	if (objectMap == "smallmap/maze.tmx" || objectMap == "smallmap/battlefeild.tmx") { 
		CCLOG("flyto222222");
		cocos2d::Director::getInstance()->pushScene(flyTransition1);													//���ϴε�ͼѹ��ջ�У�չʾ����ͼ��
	}
	/*ȥ�����ط�*/ 
	else {  
		cocos2d::Director::getInstance()->replaceScene(flyTransition1);													// ���ع��ɳ��������浱ǰ����
	}
	/*����Ǵ��Թ��򾺼����˳�*/ 
	if (mapName == "smallmap/maze.tmx" || mapName == "smallmap/battlefeild.tmx") { 
		auto fadeOut = cocos2d::FadeOut::create(2.0f);																	// ������������
		 
		auto callFunc = cocos2d::CallFunc::create([]() {
			cocos2d::Director::getInstance()->popScene();																// ������ɺ󣬵�������
			});

		auto sequence = cocos2d::Sequence::create(fadeOut, callFunc, nullptr);											// ����һ�����У��ȵ����ٵ��� popScene
		flyScene->runAction(sequence);																					// �����ж�����ӵ����ɳ���	
	}
	/*����ת��*/ 
	else {  
		this->cleanup();																								// ����ǰ����									
		auto newScene = createWithMap(objectMap, true);																	// �����³���										
		auto flyTransition2 = cocos2d::TransitionSlideInT::create(0.5f, newScene);										// ��ӹ��ɶ���
		cocos2d::Director::getInstance()->replaceScene(flyTransition2);													// �����³������ͷŵ����ɳ���
	}
}