#include "BaseMap.h"

USING_NS_CC;

BaseMap::BaseMap()
    : tiledMap(nullptr), isExplored(false), playerPosition(Vec2::ZERO) {}

BaseMap::~BaseMap() {}

void BaseMap::loadMap(const std::string& mapFile) {
    // ���� TMX ��ͼ�ļ�
    tiledMap = TMXTiledMap::create(mapFile);
    if (tiledMap) {
        this->addChild(tiledMap);
    }
    else {
        CCLOG("Failed to load map: %s", mapFile.c_str());
    }

    // ��ʼ�������㣨����ͨ�� TMX �Ķ�����ȡ��
    auto objectGroup = tiledMap->getObjectGroup("Objects");
    if (objectGroup) {
        auto objects = objectGroup->getObjects();
        for (const auto& obj : objects) {
            auto dict = obj.asValueMap();
            std::string name = dict["name"].asString();
            float x = dict["x"].asFloat();
            float y = dict["y"].asFloat();
            locationPoints[name] = Vec2(x, y);
        }
    }
}

void BaseMap::handleInteraction(const Vec2& position) {
    // ����ɫ�Ƿ�ӽ�ĳ��������
    for (const auto& point : locationPoints) {
        if (position.distance(point.second) < 32.0f) { // ����С�� 32 ����
            CCLOG("Interacting with: %s", point.first.c_str());
            // ���������д�˺���ʵ�־��彻���߼�
        }
    }
}

void BaseMap::updateExploration(const Vec2& position) {
    // ����ɫ�ƶ���ĳ������ʱ��ǵ�ͼΪ��̽��
    if (!isExplored) {
        CCLOG("Map is now explored!");
        isExplored = true;
    }
}

void BaseMap::setPlayerPosition(const Vec2& position) {
    playerPosition = position;
    // ���½�ɫ�ڵ�ͼ�е�λ��
    if (tiledMap) {
        auto playerSprite = dynamic_cast<cocos2d::Sprite*>(this->getChildByName("player"));
        if (playerSprite != nullptr) {
            playerSprite->setPosition(position);
        }

    }
}

Vec2 BaseMap::getPlayerPosition() const {
    return playerPosition;
}
