#include "Map.h"
#include "cocos2d.h"

Map::Map(const std::string& name) :mapName(name)
{
	std::string N = mapName + ".tmx";
	tiledMap = cocos2d::TMXTiledMap::create(N);
}

cocos2d::Scene* Map::createScene()
{
	auto current_scene = cocos2d::Scene::create();
	auto map_layer = Map::create();
	current_scene->addChild(map_layer);
	return current_scene;
}

bool Map::init()
{
	if (!Layer::init()) {
		return false;
	}
	// ��ȡ��ǰ��������Ĵ�С
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	// ��ȡ��ǰ��������ԭ������
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();
	// ���ص�ͼ
	Map::addChild(tiledMap);
	return true;
}

bool Map::SwitchBetweenSmallMaps(const std::string& objectMap)
{
	
	// ���Ҫǰ���Թ���ս����������һ�εĵ�ͼ
	if (objectMap == "maze" || objectMap == "battle") {
		Map newMap(objectMap);
		auto newScene = newMap.createScene();
		cocos2d::Director::getInstance()->pushScene(newScene);
	}
	// ������Թ���ս���������ص���һ�ε�ͼ
	else if (this->mapName == "maze" || this->mapName == "battle") {
		cocos2d::Director::getInstance()->popScene();
	}
	// ���ֻ�ǵ�������ת�����ͷŵ���һ�εĵ�ͼ
	else {
		Map newMap(objectMap);
		auto newScene = newMap.createScene();
		cocos2d::Director::getInstance()->replaceScene(newScene);
	}
}

void Map::Pan(const cocos2d::Vec2& roleWorldPosition, const cocos2d::EventKeyboard::KeyCode keyCode)
{
	// ��ȡ��ǰ�ɼ�����Ĵ�С
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	// ��ȡ��ǰ��������ԭ������
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();
	// ��������߽�����
	int minWorldX = origin.x;
	int minWorldY = origin.y;
	int maxWorldX = origin.x + visibleSize.width;
	int maxWorldY = origin.y + visibleSize.height;

	// ��ȡ��ǰ��Ƭ��ͼ����
	cocos2d::Vec2 mapPosition = tiledMap->getPosition();
	// ��ȡ��ǰ��Ƭ��ͼ��С
	cocos2d::Size mapSize = tiledMap->getMapSize();
	// ��ȡ��ǰ��Ƭ��ͼ��Ƭ��С
	cocos2d::Size tileSize = tiledMap->getTileSize();
	// ������Ƭ��ͼ�߽�����
	int minTileX = 0;
	int minTileY = 0;
	int maxTileX = mapSize.width - 1;
	int maxTileY = mapSize.height - 1;
	// ͨ�����������ȡ��������Ƭ���е��������
	cocos2d::Vec2 tilePosInMap = tiledMap->convertToNodeSpace(roleWorldPosition);
	// ���㾫����߼�����
	int roleTileX = tilePosInMap.x / tileSize.width;  // ����� X �߼�����
	int roleTileY = tilePosInMap.y / tileSize.height; // ����� Y �߼�����

	// �������ߵ�����߽紦����δ�ִ��ͼ�߽紦���ŻỬ����ͼ
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