#include "MiniMap.h"
#include "cocos2d.h"

cocos2d::Scene* MiniMap::createWithMap(const std::string& mapFile, bool fly)
{
	MiniMap* scene = new(std::nothrow) MiniMap(mapFile, fly);
	if (scene && scene->initWithMap(mapFile)) {
		scene->autorelease();
		scene->isFly = fly;
		scene->mapName = mapFile;
		return scene;
	}
	CC_SAFE_DELETE(scene);
	return nullptr;
}

bool MiniMap::initWithMap(const std::string& mapFile)
{
	if (!Scene::init()) {
		return false;
	}
	// ��ȡ��ǰ��������Ĵ�С
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

	// ��ȡ��ǰ��������ԭ������
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	// ��ȡ��ͼ
	tiledMap = cocos2d::TMXTiledMap::create(mapFile);
	if (!tiledMap) {
		CCLOG("noMap");
		return false;
	}

	//�������ű���
	float scaleX = 3.0f;
	float scaleY = 3.0f;

	// ���ص�ͼ
	tiledMap->setScale(scaleX, scaleY);

	// ��ȡ��ǰ��Ƭ��ͼ��С
	cocos2d::Size mapSize = tiledMap->getMapSize();

	// ��ȡ��Ƭ��ͼ��Ƭ��С
	auto tileSize = tiledMap->getTileSize();

	// ������Ƭ���ź��С
	auto playerSize = tileSize;
	playerSize.width *= scaleX;
	playerSize.height *= scaleY;

	// �������ؾ���
	player = cocos2d::Sprite::create("HelloWorld.png");

	// �������ؾ����С
	player->setContentSize(playerSize);

	// ��ȡ���ؾ�����Ҫ������߼�����
	float bornPointX = 0.0f, bornPointY = 0.0f;

	// ���������
	auto transportPoint = (isFly == true ? tiledMap->getObjectGroup("TransportPoint") : tiledMap->getObjectGroup("Boat"));

	// ��ȡ����λ�õ��߼�����
	if (transportPoint) {
		auto transportObject = (isFly == true ? transportPoint->getObject("Fly") : transportPoint->getObject("Boat"));
		bornPointX = transportObject["x"].asFloat();
		bornPointY = transportObject["y"].asFloat();
	}

	if (!bornPointX && !bornPointY)
		CCLOG("noBornPoint");

	// �������ؾ������������
	auto bornWorld = tiledMap->convertToWorldSpace(cocos2d::Vec2(bornPointX, bornPointY));

	// �����Ӵ����ĵ���������
	cocos2d::Vec2 centerWorldPosition = cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 2);

	// ��ȡƫ����
	cocos2d::Vec2 offset = centerWorldPosition - bornWorld + cocos2d::Vec2(0.0f, -tileSize.height * scaleY);

	// ����ƫ�������Է��߽�������Ӵ��ڲ�
	if (offset.x > 0)
		offset.x = 0;
	else if (offset.x + mapSize.width * tileSize.width * scaleX < visibleSize.width)
		offset.x = visibleSize.width - mapSize.width * tileSize.width * scaleX;
	if (offset.y > 0)
		offset.y = 0;
	else if (offset.y + mapSize.height * tileSize.height * scaleY < visibleSize.height)
		offset.y = visibleSize.height - mapSize.height * tileSize.height * scaleY;

	// �������ؾ���λ��
	cocos2d::Vec2 playerPos = offset + bornWorld - cocos2d::Vec2(0.0f, -tileSize.height * scaleY);

	// �������ؾ���λ��
	player->setPosition(playerPos);
	tiledMap->setPosition(offset);

	// �Ѿ�����ӵ�����
	this->addChild(tiledMap);
	this->addChild(player);

	// ���ü����¼�������
	StartListening();

	return true;
}

// ���ü����¼�������
void MiniMap::StartListening()
{
	if (!keyboardListener) { // ȷ��û���ظ���Ӽ�����
		// ��������������¼�������
		keyboardListener = cocos2d::EventListenerKeyboard::create();

		// ���ü��̰����¼��Ļص�����
		keyboardListener->onKeyPressed = CC_CALLBACK_2(MiniMap::OnKeyPressed, this);

		// ���ü����ͷ��¼��Ļص�����
		keyboardListener->onKeyReleased = CC_CALLBACK_2(MiniMap::OnKeyReleased, this);

		// ��ӵ��¼���������
		_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
	}
}

// �������µĻص�����
void MiniMap::OnKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	switch (keyCode) {
	case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
	case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
	case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		UpdatePlayerPosition(keyCode);
		break;
	default:
		break;
	}
}

// �����ͷŵĻص���������ʱ������Ҫ���ȷ��Űɣ�
void MiniMap::OnKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
}

// ���������
void MiniMap::StopListening()
{
	if (keyboardListener) {
		_eventDispatcher->removeEventListener(keyboardListener);
		keyboardListener = nullptr; // ���ָ��
	}
}