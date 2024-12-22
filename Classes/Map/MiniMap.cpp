#include "MiniMap.h"
#include "cocos2d.h"

// ȷ��������ֵ��ĳ����Χ�ڣ���Ҫ���������������λ��
template<typename T>
T clamp(const T& value, const T& min, const T& max)
{
	if (value < min)
		return min;
	else if (value > max)
		return max;
	else
		return value;
}

// ��ʼ��
MiniMap::MiniMap(const std::string& map, bool fly)
{
	mapName = map;
	isFly = fly;
	tiledMap = nullptr;
	player = nullptr;
	keyboardListener = nullptr;
}

cocos2d::Scene* MiniMap::createScene()
{
	auto current_scene = cocos2d::Scene::create();
	auto map = MiniMap::create();
	current_scene->addChild(map);
	return current_scene;
}

bool MiniMap::init()
{
	if (!Scene::init()) {
		return false;
	}

	// ��ȡ��ǰ��������Ĵ�С
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

	// ��ȡ��ǰ��������ԭ������
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	// ��ȡ��ͼ
	tiledMap = cocos2d::TMXTiledMap::create("smallmap/wood.tmx");

	// ���ص�ͼ
	MiniMap::addChild(tiledMap);

	// �������
	auto camera = cocos2d::Camera::create();
	this->addChild(camera);

	// �������ű���
	float scaleX = 1.0f;
	float scaleY = 1.0f;
	camera->setScaleX(scaleX);
	camera->setScaleY(scaleY);

	// ��ȡ��Ƭ��ͼ��Ƭ��С
	auto tileSize = tiledMap->getTileSize();

	// ������Ƭ���ź��С
	auto playerSize = tileSize;
	playerSize.width *= scaleX;
	playerSize.height *= scaleY;

	// �������ؾ���
	player = cocos2d::Sprite::create("CloseSelected.png");

	// �������ؾ����С
	player->setContentSize(playerSize);

	// ���������
	auto objectLayer = tiledMap->getLayer("TransportPoint");
	
	// ��ȡ���ؾ�����Ҫ������߼�����
	float bornPointX = 0.0f, bornPointY = 0.0f;
	if (objectLayer) {
		// ��ȡ��Ĵ�С
		auto layerSize = objectLayer->getLayerSize();

		// ��ȡ���ؾ�����Ҫ������߼�����
		float bornPointX = 0.0f, bornPointY = 0.0f;
		for (int y = 0; y < layerSize.height; ++y) { // ����ÿ����Ƭ
			for (int x = 0; x < layerSize.width; ++x) {
				// ��ȡ��Ƭ�� GID
				int tileGID = objectLayer->getTileGIDAt(cocos2d::Vec2(x, y));

				// ��� GID �Ƿ���Ч
				if (tileGID != 0) {
					// ��ȡ��Ƭ����������
					auto properties = tiledMap->getPropertiesForGID(tileGID).asValueMap();

					//��ȡ��Ƭ��type
					auto tileType = properties["type"].asString();

					// �жϸ���Ƭ�Ƿ���Ŀ����Ƭ
					if (isFly && tileType == "flyPoint") { // ���ͷ�ʽ
						bornPointX = properties["X"].asFloat();
						bornPointY = properties["Y"].asFloat();
					}
					else if (!isFly && tileType == "boatPoint") { // ������ʽ
						bornPointX = properties["X"].asFloat();
						bornPointY = properties["Y"].asFloat();
					}
				}
			}
		}
	}
	if (!bornPointX && !bornPointY)
		CCLOG("û�ҵ�������");

	// �������ؾ������������
	float bornWorldX = bornPointX * tileSize.width * scaleX;
	float bornWorldY = bornPointY * tileSize.height * scaleY;

	// �������ؾ���λ��
	player->setPosition(cocos2d::Vec2(bornWorldX, bornWorldY));

	// ������������ʵ�ʳߴ�
	float visibleWidth = visibleSize.width / scaleX;
	float visibleHeight = visibleSize.height / scaleY;

	// �����������λ��
	float cameraX = clamp<float>(bornWorldX, visibleWidth / 2, tiledMap->getMapSize().width * tileSize.width - visibleWidth / 2);
	float cameraY = clamp<float>(bornWorldY, visibleHeight / 2, tiledMap->getMapSize().height * tileSize.height - visibleHeight / 2);

	// ���������λ��
	camera->setPosition(cocos2d::Vec2(cameraX,cameraY));

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


/*
// ����ȥ���ڵ�ͼ
void MiniMap::BoatingToMap(const std::string& objectMap)
{
	// ������Ҫǰ���ĵ�ͼ����
	MiniMap object(objectMap, false);

	// ���ص�ͼ
	object.createScene();

}*/

/*
bool MiniMap::SwitchBetweenSmallMaps(const std::string& objectMap, const bool walk)
{
	// ���Ҫǰ���Թ���ս����������һ�εĵ�ͼ
	if (objectMap == "maze" || objectMap == "battle") {
		// ��ȡ�ɼ�����Ĵ�С
		auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

		// �������ɳ����ı�������
		auto transitionSprite = cocos2d::Sprite::create("GameTransition.png");

		// ���þ���Ĵ�С����Ļһ����
		transitionSprite->setContentSize(visibleSize);

		// ���þ����λ��Ϊ��Ļ����
		transitionSprite->setPosition(visibleSize / 2);

		// �������ɳ���
		cocos2d::Scene* transitionScene = cocos2d::Scene::create();

		// ������������ӵ����ɳ�����
		transitionScene->addChild(transitionSprite);

		// ��ӹ��ɶ���
		auto transition = cocos2d::TransitionSlideInT::create(0.5f, transitionScene);

		// ���ϴε�ͼѹ��ջ�У�չʾ����ͼ��
		cocos2d::Director::getInstance()->pushScene(transition);

		// �����³���
		Map newMap(objectMap);
		auto newScene = newMap.createScene();

		// ��ӹ��ɶ���
		auto newTransition = cocos2d::TransitionSlideInT::create(0.5f, newScene);

		// �����³������ͷŵ����ɳ���
		cocos2d::Director::getInstance()->replaceScene(newScene);
	}
	// ������Թ���ս���������ص���һ�ε�ͼ
	else if (this->mapName == "maze" || this->mapName == "battle") {
		cocos2d::Director::getInstance()->popScene();
	}
	// ��������������ͼ֮�����ת
	else {
		// ��ȡ�ɼ�����Ĵ�С
		auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

		// �������ɳ����ı�������
		cocos2d::Sprite* transitionSprite;
		if (walk == true) // ���ڵ�ͼ
			transitionSprite = cocos2d::Sprite::create("GoByWalking.png");
		else // ê�㴫��
			transitionSprite = cocos2d::Sprite::create("GoByPortal.png");

		// ���þ���Ĵ�С����Ļһ����
		transitionSprite->setContentSize(visibleSize);

		// ���þ����λ��Ϊ��Ļ����
		transitionSprite->setPosition(visibleSize / 2);

		// �������ɳ���
		cocos2d::Scene* transitionScene = cocos2d::Scene::create();

		// ������������ӵ����ɳ�����
		transitionScene->addChild(transitionSprite);

		// ��ӹ��ɶ���
		auto transition = cocos2d::TransitionSlideInL::create(0.5f, transitionScene);

		// ���ϴε�ͼѹ��ջ�У�չʾ����ͼ��
		cocos2d::Director::getInstance()->replaceScene(transition);

		// �����³���
		Map newMap(objectMap);
		auto newScene = newMap.createScene();

		// ��ӹ��ɶ���
		auto newTransition = cocos2d::TransitionSlideInT::create(0.5f, newScene);

		// �����³������ͷŵ����ɳ���
		cocos2d::Director::getInstance()->replaceScene(newScene);
	}
	return true;
}
// �Ұ�װ�¼�����������������ƶ�������Player��ļ��㺯�������ƶ�������������㺯���������µ����ꡣ
// ���ж��������Ƿ�ɵ����ɣ�����Sprite��png��ʾ��������Player��ĸ��º�������Player�����������ԡ�
void MiniMap::Pan(const cocos2d::Vec2& roleWorldPosition, const cocos2d::EventKeyboard::KeyCode keyCode)
{
	// ��ȡ��ǰ�ɼ�����Ĵ�С
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

	// ��ȡ��ǰ��������ԭ������
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	// ��ȡ��ǰ��Ƭ��ͼ����
	cocos2d::Vec2 mapPosition = tiledMap->getPosition();

	// ��ȡ��ǰ��Ƭ��ͼ��С
	cocos2d::Size mapSize = tiledMap->getMapSize();

	// ��ȡ��ǰ��Ƭ��ͼ��Ƭ��С
	cocos2d::Size tileSize = tiledMap->getTileSize();

	// ������Ƭ��ͼ�߽�����
	float minTileX = 0.0f;
	float minTileY = 0.0f;
	float maxTileX = mapSize.width - 1;
	float maxTileY = mapSize.height - 1;

	// ����������������
	float centralWorldX = (origin.x + visibleSize.width) / 2;
	float centralWorldY = (origin.y + visibleSize.height) / 2;

	// ��������߽�����
	float minWorldX = centralWorldX - visibleSize.width / 4;
	float minWorldY = centralWorldY - visibleSize.height / 4;
	float maxWorldX = centralWorldX + visibleSize.width / 4;
	float maxWorldY = centralWorldY + visibleSize.height / 4;

	// ͨ�����������ȡ��������Ƭ���е��������
	cocos2d::Vec2 tilePosInMap = tiledMap->convertToNodeSpace(roleWorldPosition);

	// ���㾫����߼�����
	float roleTileX = tilePosInMap.x / tileSize.width;  // ����� X �߼�����
	float roleTileY = tilePosInMap.y / tileSize.height; // ����� Y �߼�����

	// �˳���Ϸ
	if ((mapName == "maze" || mapName == "battle") && keyCode == cocos2d::EventKeyboard::KeyCode::KEY_Q) {
		// ������ϵͳ�ĶԻ����ٸ��ҷ���һ��ֵ��ʾ�Ƿ��˳���
		
		// ���ȷ���˳�������С��ͼת��
		SwitchBetweenSmallMaps("lastMap", false);
	}

	// �������ߵ���������������߽紦����δ�ִ��ͼ�߽紦���ŻỬ����ͼ
	// ��������
	if (roleWorldPosition.x <= minWorldX && keyCode == cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW && roleTileX > 0) {
		cocos2d::Vec2 newMapPosition = cocos2d::Vec2(mapPosition.x + tileSize.width, mapPosition.y);
		tiledMap->setPosition(newMapPosition);
	}
	// ��������
	else if (roleWorldPosition.x >= maxWorldX && keyCode == cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW && roleTileX < maxTileX) {
		cocos2d::Vec2 newMapPosition = cocos2d::Vec2(mapPosition.x - tileSize.width, mapPosition.y);
		tiledMap->setPosition(newMapPosition);
	}
	// ��������
	else if (roleWorldPosition.x >= maxWorldY && keyCode == cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW && roleTileY < maxTileY) {
		cocos2d::Vec2 newMapPosition = cocos2d::Vec2(mapPosition.x, mapPosition.y-tileSize.height);
		tiledMap->setPosition(newMapPosition);
	}
	// ��������
	else if (roleWorldPosition.x <= minWorldY && keyCode == cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW && roleTileY > 0) {
		cocos2d::Vec2 newMapPosition = cocos2d::Vec2(mapPosition.x, mapPosition.y+tileSize.height);
		tiledMap->setPosition(newMapPosition);
	}
}
*/

void MiniMap::UpdatePlayerPosition(const cocos2d::EventKeyboard::KeyCode keyCode)
{
	// ����ʵ�ִ���
}
