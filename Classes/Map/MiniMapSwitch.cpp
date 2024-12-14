/*2351271 ��߮��*/
#include "MiniMap.h"
#include "cocos2d.h"

// ����ȥ���ڵ�ͼ����ľˮ������ׯ�Ǳ�
void MiniMap::BoatingToMap(const std::string& objectMap)
{
	// ��ȡ�ɼ�����Ĵ�С
	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

	// �������ɳ���
	auto boatScene = cocos2d::Scene::create();

	// �������ɳ����ı�������
	auto boatSprite = cocos2d::Sprite::create("boat.png");

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

	// �����³���
	MiniMap newMap(objectMap,false);
	auto newScene = newMap.createScene();

	// ��ӹ��ɶ���
	auto boatTransition2 = cocos2d::TransitionSlideInT::create(0.5f, newScene);

	// �����³������ͷŵ����ɳ���
	cocos2d::Director::getInstance()->replaceScene(boatTransition2);
}

// ����ȥ���ڵ�ͼ����ת����ľˮ������ׯ�Ǳ���ǰ���Թ�/����������Թ�/�������˳�
void MiniMap::FlyToMap(const std::string& objectMap)
{
	// ��ȡ�ɼ�����Ĵ�С
	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

	// �������ɳ���
	auto flyScene = cocos2d::Scene::create();

	// �������ɳ����ı�������
	auto flySprite = cocos2d::Sprite::create("fly.png");

	// ���þ���Ĵ�С����Ļһ����
	flySprite->setContentSize(visibleSize);

	// ���þ����λ��Ϊ��Ļ����
	flySprite->setPosition(visibleSize / 2);

	// �ѱ���������ӵ����ɳ���
	flyScene->addChild(flySprite);

	// ��ӹ��ɶ���
	auto flyTransition1 = cocos2d::TransitionSlideInT::create(0.5f, flyScene);

	if (objectMap == "maze.tmx" || objectMap == "battle.tmx") { // �����ǰ���Թ��򾺼���
		// ���ϴε�ͼѹ��ջ�У�չʾ����ͼ��
		cocos2d::Director::getInstance()->pushScene(flyTransition1);
	}
	else { // ȥ�����ط�
		// ���ϴγ����ͷŵ���չʾ����ͼ��
		cocos2d::Director::getInstance()->replaceScene(flyTransition1);
	}

	if (mapName == "maze.tmx" || mapName == "battle.tmx") { // ����Ǵ��Թ��򾺼����˳�
		// ����һ����������
		auto fadeOut = cocos2d::FadeOut::create(0.5f);

		// �ڶ�����ɺ���� popScene
		auto callFunc = cocos2d::CallFunc::create([]() {
			cocos2d::Director::getInstance()->popScene();
			});

		// ����һ�����У��ȵ����ٵ��� popScene
		auto sequence = cocos2d::Sequence::create(fadeOut, callFunc, nullptr);

		// �����ж�����ӵ����ɳ���
		flyScene->runAction(sequence);
	}
	else { // ����ת��
		// �����³���
		MiniMap newMap(objectMap, true);
		auto newScene = newMap.createScene();

		// ��ӹ��ɶ���
		auto flyTransition2 = cocos2d::TransitionSlideInT::create(0.5f, newScene);

		// �����³������ͷŵ����ɳ���
		cocos2d::Director::getInstance()->replaceScene(flyTransition2);
	}
}
