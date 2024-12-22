/*2351271 ��߮��*/
#include "Map/MiniMap.h"
#include "cocos2d.h"
std::shared_ptr<Player> _player1 = GlobalManager::getInstance().getPlayer();
// ����ȥ���ڵ�ͼ����ľˮ������ׯ�Ǳ�
void MiniMap::BoatingToMap(const std::string& objectMap)
{
	CCLOG("boat to!!!!!!!");
	// ��ȡ�ɼ�����Ĵ�С
	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	CCLOG("boat to2222");
	// �������ɳ���
	auto boatScene = cocos2d::Scene::create();
	CCLOG("boat to3333");
	// �������ɳ����ı�������
	cocos2d::Sprite* boatSprite;
	if (mapName == "smallmap/whole3.tmx" || (mapName == "smallmap/fire.tmx" && objectMap == "smallmap/whole3.tmx")) {
		boatSprite = cocos2d::Sprite::create("CloseNormal.png");
	}
	else {
		boatSprite = cocos2d::Sprite::create("CloseSelected.png");
	}

	// ���þ���Ĵ�С����Ļһ����
	boatSprite->setContentSize(visibleSize);

	// ���þ����λ��Ϊ��Ļ����
	boatSprite->setPosition(visibleSize / 2);

	// �ѱ���������ӵ����ɳ���
	boatScene->addChild(boatSprite);

	// ��ӹ��ɶ���
	auto boatTransition1 = cocos2d::TransitionSlideInT::create(0.5f, boatScene);

	// �ͷŵ��ϴγ�����չʾ����ͼ��
	cocos2d::Director::getInstance()->replaceScene(boatTransition1);
	std::shared_ptr<Player> player1 = GlobalManager::getInstance().getPlayer();
	// �����³���
	_player1->removeFromParent();
	auto newScene = createWithMap(objectMap, false);
	
	// ��ӹ��ɶ���
	auto boatTransition2 = cocos2d::TransitionSlideInT::create(0.5f, newScene);

	// �����³������ͷŵ����ɳ���
	cocos2d::Director::getInstance()->replaceScene(boatTransition2);
}

// ����ȥ���ڵ�ͼ����ת����ľˮ������ׯ�Ǳ���ǰ���Թ�/����������Թ�/�������˳�
void MiniMap::FlyToMap(const std::string& objectMap)
{
	CCLOG("flyto111");
	// ��ȡ�ɼ�����Ĵ�С
	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

	// �������ɳ���
	auto flyScene = cocos2d::Scene::create();

	// �������ɳ����ı�������
	auto flySprite = cocos2d::Sprite::create("UI/X.png");

	// ���þ���Ĵ�С����Ļһ����
	flySprite->setContentSize(visibleSize);

	// ���þ����λ��Ϊ��Ļ����
	flySprite->setPosition(visibleSize / 2);

	// �ѱ���������ӵ����ɳ���
	flyScene->addChild(flySprite);

	// ��ӹ��ɶ���
	auto flyTransition1 = cocos2d::TransitionSlideInT::create(2.0f, flyScene);

	// �����ǰ���Թ��򾺼���
	if (objectMap == "smallmap/maze.tmx" || objectMap == "smallmap/battlefeild.tmx") { 
		// ���ϴε�ͼѹ��ջ�У�չʾ����ͼ��
		CCLOG("flyto222222");
		cocos2d::Director::getInstance()->pushScene(flyTransition1);
	}
	// ȥ�����ط�
	else { 
		// ���ϴγ����ͷŵ���չʾ����ͼ��
		cocos2d::Director::getInstance()->replaceScene(flyTransition1);
	}
	// ����Ǵ��Թ��򾺼����˳�
	if (mapName == "smallmap/maze.tmx" || mapName == "smallmap/battlefeild.tmx") { 
		// ����һ����������
		auto fadeOut = cocos2d::FadeOut::create(2.0f);

		// �ڶ�����ɺ���� popScene
		auto callFunc = cocos2d::CallFunc::create([]() {
			cocos2d::Director::getInstance()->popScene();
			});

		// ����һ�����У��ȵ����ٵ��� popScene
		auto sequence = cocos2d::Sequence::create(fadeOut, callFunc, nullptr);

		// �����ж�����ӵ����ɳ���
		flyScene->runAction(sequence);
	}
	// ����ת��
	else { 
		// �����³���
		this->cleanup();
		auto newScene = createWithMap(objectMap, true);

		// ��ӹ��ɶ���
		auto flyTransition2 = cocos2d::TransitionSlideInT::create(0.5f, newScene);

		// �����³������ͷŵ����ɳ���
		cocos2d::Director::getInstance()->replaceScene(flyTransition2);
	}
}