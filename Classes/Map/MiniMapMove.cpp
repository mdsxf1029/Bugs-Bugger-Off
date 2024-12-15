#include <cmath>
#include "MiniMap.h"
#include "cocos2d.h"
#include "Classes/manager/manager.h"

// �������ؾ���λ��
void MiniMap::UpdatePlayerPosition(const cocos2d::EventKeyboard::KeyCode keyCode)
{
    // ��ȡ���ؾ���ԭλ��
    cocos2d::Vec2 currentPos = player->getPosition();

    // ��ȡ���ؾ�����λ��
    cocos2d::Vec2 newPos = GlobalManager::getInstance().getPlayer()->Move(keyCode);

    // �Ƿ�����
    bool walkable = true;

    // ��ȡ��ײ���Ķ�̬������
    auto collisionLayer = tiledMap->getObjectGroup("Collision");

    // ��ȡ���ű���
    auto scaleX = tiledMap->getScaleX();
    auto scaleY = tiledMap->getScaleY();

    // ��ȡ��ǰ��������ԭ������
    cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

    // ��ȡ��ǰ��������Ĵ�С
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

    // �����Ӵ����ĵ���������
    cocos2d::Vec2 centralWorldPos = cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 2);

    // ��ȡ��ǰ��Ƭ��ͼ��С
    cocos2d::Size mapSize = tiledMap->getMapSize();

    // ��ȡ��Ƭ��ͼ��Ƭ��С
    cocos2d::Size tileSize = tiledMap->getTileSize();

    // ��ȡ��ǰ��Ƭ��ͼ����
    cocos2d::Vec2 currentMapPos = tiledMap->getPosition();

    // ������Ƭ���ź��С
    cocos2d::Size playerSize = tileSize;
    playerSize.width *= scaleX;
    playerSize.height *= scaleY;

    // ͨ�����������ȡ��������Ƭ���е��������
    cocos2d::Vec2 tilePos = tiledMap->convertToNodeSpace(newPos);

    // �������ײ���㣬��Collision����
    if (collisionLayer) {
        auto collisionObjects = collisionLayer->getObjects();
        for (const auto& object : collisionObjects) {
            cocos2d::ValueMap collisionProperties = object.asValueMap();
            auto x = collisionProperties["x"].asFloat();
            auto y = collisionProperties["y"].asFloat();
            auto width = collisionProperties["width"].asFloat();
            auto height = collisionProperties["height"].asFloat();
            if (tilePos.x >= x && tilePos.x <= x + width && tilePos.y >= y && tilePos.y <= y + height) {
                walkable = false;
                break;
            }
        }
    }

    // Ѱ���Ƿ���boat��
    auto boatLayer = tiledMap->getObjectGroup("Boat");

    // ��Ǵ������
    bool boat = false;

    // �����boat�㣬��boat����
    if (boatLayer) {
        auto boatObjects = boatLayer->getObjects();
        for (const auto& object : boatObjects) {
            cocos2d::ValueMap boatProperties = object.asValueMap();
            auto x = boatProperties["x"].asFloat();
            auto y = boatProperties["y"].asFloat();
            auto width = boatProperties["width"].asFloat();
            auto height = boatProperties["height"].asFloat();
            if (tilePos.x >= x && tilePos.x <= x + width && tilePos.y >= y && tilePos.y <= y + height) {
                boat = true;
                break;
            }
        }

    }

    // �������boat�����Ի���
    if (boat) {
        // �����Ի���ı�������
        auto background = cocos2d::Sprite::create();
        float width = visibleSize.width / 4, height = visibleSize.height / 5; // ���öԻ���Ĵ�С
        background->setTextureRect(cocos2d::Rect(0.0f, 0.0f, width, height)); // ��Ϊ����
        background->setColor(Color3B(255, 255, 255)); // ���öԻ��򱳾�Ϊ��ɫ        
        background->setPosition(centralWorldPos); // ���öԻ���λ��Ϊ�Ӵ�����       
        background->setOpacity(200); // ���öԻ���͸����Ϊ�ϸ�
        this->addChild(background);

        // �������ֱ�ǩ
        auto label = cocos2d::Label::createWithSystemFont("Where do you want to go?", "Arial", 24); // �����ı�
        label->setPosition(centralWorldPos + cocos2d::Vec2(0.0f, visibleSize.height / 20)); // ����λ��
        label->setColor(cocos2d::Color3B(255, 255, 255)); // �����ı���ɫΪ��ɫ
        this->addChild(label);

        // �������ڵ�ͼ
        std::string newMap1, newMap2;
        GetNeighborMap(newMap1, newMap2);

        // ������ť
        auto label1 = cocos2d::Label::createWithSystemFont(newMap1, "Arial", 24);
        auto label2 = cocos2d::Label::createWithSystemFont(newMap2, "Arial", 24);
        auto label3 = cocos2d::Label::createWithSystemFont("None", "Arial", 24);
        auto button1 = cocos2d::MenuItemLabel::create(label1, CC_CALLBACK_1(MiniMap::ButtonCallback, this));
        auto button2 = cocos2d::MenuItemLabel::create(label2, CC_CALLBACK_1(MiniMap::ButtonCallback, this));
        auto button3 = cocos2d::MenuItemLabel::create(label3, CC_CALLBACK_1(MiniMap::ButtonCallback, this));
        button1->setPosition(centralWorldPos + cocos2d::Vec2(-visibleSize.width / 8, -visibleSize.height / 20));
        button2->setPosition(centralWorldPos + cocos2d::Vec2(0.0f, -visibleSize.height / 20));
        button3->setPosition(centralWorldPos + cocos2d::Vec2(visibleSize.width / 8, -visibleSize.height / 20));
    }

    // ��������߽���������
    float minWorldX = centralWorldPos.x - visibleSize.width / 4;
    float minWorldY = centralWorldPos.y - visibleSize.height / 4;
    float maxWorldX = centralWorldPos.x + visibleSize.width / 4;
    float maxWorldY = centralWorldPos.y + visibleSize.height / 4;

    // �����ǰ��������
    if (walkable) {
        // ����ƫ����
        float offset;
        if (abs(newPos.x - currentPos.x))
            offset = abs(newPos.x - currentPos.x);
        else
            offset = abs(newPos.y - currentPos.y);

        // ��������
        if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW && newPos.x <= minWorldX && tilePos.x > 0
            && currentMapPos.x < 0) {
            cocos2d::Vec2 newMapPosition = currentMapPos + cocos2d::Vec2(offset, 0.0f);
            tiledMap->setPosition(newMapPosition);
        }

        // ��������
        else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW && newPos.x >= maxWorldX
            && tilePos.x < mapSize.width * tileSize.width && currentMapPos.x + (mapSize.width - 2) * tileSize.width * scaleX > visibleSize.width) {
            cocos2d::Vec2 newMapPosition = currentMapPos + cocos2d::Vec2(-offset, 0.0f);
            tiledMap->setPosition(newMapPosition);
        }

        // ��������
        else if (newPos.y >= maxWorldY && keyCode == cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW && tilePos.y > 0
            && currentMapPos.y + (mapSize.height - 2) * tileSize.height * scaleY > visibleSize.height) {
            cocos2d::Vec2 newMapPosition = currentMapPos + cocos2d::Vec2(0.0f, -offset);
            tiledMap->setPosition(newMapPosition);
        }

        // ��������
        else if (newPos.y <= minWorldY && keyCode == cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW
            && tilePos.y < mapSize.height * tileSize.height && currentMapPos.y < 0) {
            cocos2d::Vec2 newMapPosition = currentMapPos + cocos2d::Vec2(0.0f, offset);
            tiledMap->setPosition(newMapPosition);
        }

        else if (newPos.x > 0 && newPos.x < visibleSize.width && newPos.y>0 && newPos.y < visibleSize.height) {
            // ����ƽ���ƶ��Ķ���
            auto moveTo = cocos2d::MoveTo::create(0.1f, newPos);

            // ִ�ж���
            player->runAction(moveTo);

            // ������������
            GlobalManager::getInstance().getPlayer()->setPosition(newPos);
        }
    }
    else {
        CCLOG("�޷�ǰ��(%f,%f)", newPos.x, newPos.y);
    }
}

void MiniMap::ButtonCallback(Ref* sender)
{
    // �Ƴ���������
    removeChildByName("background");

    // �Ƴ����ֱ�ǩ
    removeChildByName("label1");
    removeChildByName("label2");
    removeChildByName("label3");

    // �Ƴ���ť�˵�
    removeChildByName("button1");
    removeChildByName("button2");
    removeChildByName("button3");

    // �Ӱ�ť�л�ȡ Label
    auto menuItemLabel = static_cast<cocos2d::MenuItemLabel*>(sender);
    auto label = dynamic_cast<cocos2d::Label*>(menuItemLabel->getLabel());

    // ��ȡ Label ���ı�
    std::string labelText = label->getString();
    if (labelText == "None")
        return;
    else {
        const auto& tasks = GlobalManager::getInstance().getTasks();
        std::string targetID = "TASK_";
        if (labelText == "gold")
            targetID += "GOLD";
        else if (labelText == "wood")
            targetID += "WOOD";
        else if (labelText == "water")
            targetID += "WATER";
        else if (labelText == "fire")
            targetID += "FIRE";
        else
            targetID += "EARTH";
        auto it = std::find_if(tasks.begin(), tasks.end(), [targetID](const std::shared_ptr<Task>& obj) {
            return (obj->getTaskName() == targetID && obj->isTaskFinished());
            });
        if (it != tasks.end()) {
            if (labelText == "gold")
                labelText += "1.tmx";
            else
                labelText += ".tmx";
            BoatingToMap(labelText);
        }
    }
}

void MiniMap::GetNeighborMap(std::string& newMap1, std::string& newMap2)
{
    if (mapName == "gold1.tmx") {
        newMap1 = "earth";
        newMap2 = "wood";
    }
    else if (mapName == "wood.tmx") {
        newMap1 = "gold";
        newMap2 = "water";
    }
    else if (mapName == "water.tmx") {
        newMap1 = "wood";
        newMap2 = "fire";
    }
    else if (mapName == "fire.tmx") {
        newMap1 = "water";
        newMap2 = "earth";
    }
    else {
        newMap1 = "fire";
        newMap2 = "earth";
    }
}