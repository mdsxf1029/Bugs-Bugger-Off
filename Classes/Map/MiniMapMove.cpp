#include <cmath>
#include <vector>
#include "MiniMap.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
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
        float width = visibleSize.width / 2, height = visibleSize.height; // ���öԻ���Ĵ�С
        background->setTextureRect(cocos2d::Rect(0.0f, 0.0f, width, height)); // ��Ϊ����
        background->setColor(Color3B(255, 255, 255)); // ���öԻ��򱳾�Ϊ��ɫ        
        background->setPosition(centralWorldPos); // ���öԻ���λ��Ϊ�Ӵ�����       
        background->setOpacity(200); // ���öԻ���͸����Ϊ�ϸ�
        this->addChild(background);

        // �������ֱ�ǩ
        auto label = cocos2d::Label::createWithSystemFont("Where do you want to go?", "Arial", 64); // �����ı�
        label->setPosition(centralWorldPos + cocos2d::Vec2(0.0f, visibleSize.height / 4)); // ����λ��
        label->setColor(cocos2d::Color3B(0, 0, 0)); // �����ı���ɫΪ��ɫ
        this->addChild(label);

        // ��ͬ��ͼ
        std::vector<std::string> map = { "gold","wood","water","fire","earth","none","village"};

        // ��������Ǵ�ׯ
        if (mapName == "village.tmx") {
            for (int i = 0; i < 6; i++) {
                // ������ť
                auto button = ui::Button::create("button_normal.png", "button_pressed.png", "button_disabled.png");

                // ���ð�ť����
                button->setTitleText(map[i]); // �����ı�
                button->setTitleFontSize(48); // �����ֺ�
                button->setTitleColor(Color3B(0, 0, 0)); // ���ñ���Ϊ��ɫ
                button->setTitleFontName("Arial"); // ���ñ�������

                // ��ȡ����
                const auto& tasks = GlobalManager::getInstance().getTasks();
                std::string targetID = "TASK_";
                std::string need = map[i];
                std::transform(need.begin(), need.end(), need.begin(),
                    [](unsigned char c) { return std::toupper(c); }); // ת��д
                targetID += need;

                // ��ѯ�����Ƿ����
                auto it = std::find_if(tasks.begin(), tasks.end(), [targetID](const std::shared_ptr<Task>& obj) {
                    return (obj->getTaskName() == targetID && obj->isTaskFinished());
                    });

                // ���δ��ɣ����ð�ť
                if (it == tasks.end()) {
                    button->setEnabled(false); // ���ð�ť
                }

                // ��Ӱ�ť����¼�
                button->addClickEventListener(std::bind(&MiniMap::ButtonCallback, this, std::placeholders::_1));

                // ���ð�ťλ��
                button->setPosition(cocos2d::Vec2(centralWorldPos.x, visibleSize.height * 3 / 4 - i * 100));

                // ����ť��ӵ�������
                this->addChild(button);
            }
        }
        else if (mapName == "castle.tmx") {
            // ������ť
            auto button1 = ui::Button::create("button_normal.png", "button_pressed.png", "button_disabled.png");
            auto button2 = ui::Button::create("button_normal.png", "button_pressed.png", "button_disabled.png");

            // ���ð�ť��λ��
            button1->setPosition(cocos2d::Vec2(centralWorldPos.x, centralWorldPos.y - visibleSize.height / 3));
            button2->setPosition(cocos2d::Vec2(centralWorldPos.x, centralWorldPos.y + visibleSize.height / 3));

            // ���ð�ť����
            button1->setTitleText(map[6]); // �����ı�
            button1->setTitleFontSize(48); // �����ֺ�
            button1->setTitleColor(Color3B(0, 0, 0)); // ���ñ���Ϊ��ɫ
            button1->setTitleFontName("Arial"); // ���ñ�������
            button2->setTitleText(map[5]); // �����ı�
            button2->setTitleFontSize(48); // �����ֺ�
            button2->setTitleColor(Color3B(0, 0, 0)); // ���ñ���Ϊ��ɫ
            button2->setTitleFontName("Arial"); // ���ñ�������

            // ��Ӱ�ť����¼�
            button1->addClickEventListener(std::bind(&MiniMap::ButtonCallback, this, std::placeholders::_1));
            button2->addClickEventListener(std::bind(&MiniMap::ButtonCallback, this, std::placeholders::_1));

            // ����ť��ӵ�������
            this->addChild(button1);
            this->addChild(button2);
        }
        else {
            // �������ڵ�ͼ
            std::string newMap1, newMap2;
            GetNeighborMap(newMap1, newMap2);
            
            for (int i = 0; i < 4; i++) {
                // ������ť
                auto button = ui::Button::create("button_normal.png", "button_pressed.png", "button_disabled.png");

                // ���ð�ťλ��
                button->setPosition(cocos2d::Vec2(centralWorldPos.x, visibleSize.height * 3 / 4 - i * 100));

                // ���ð�ť����
                button->setTitleFontSize(48); // �����ֺ�
                button->setTitleColor(Color3B(0, 0, 0)); // ���ñ���Ϊ��ɫ
                button->setTitleFontName("Arial"); // ���ñ�������
                
                // ���ñ����ı�
                if (i == 0 || i == 1) {
                    std::string need;
                    if (i == 0) {
                        button->setTitleText(newMap1);
                        need = newMap1;
                    }
                    else {
                        button->setTitleText(newMap2);
                        need = newMap2;
                    }

                    // ��ȡ����
                    const auto& tasks = GlobalManager::getInstance().getTasks();
                    std::string targetID = "TASK_";
                    std::transform(need.begin(), need.end(), need.begin(),
                        [](unsigned char c) { return std::toupper(c); }); // ת��д
                    targetID += need;

                    // ��ѯ�����Ƿ����
                    auto it = std::find_if(tasks.begin(), tasks.end(), [targetID](const std::shared_ptr<Task>& obj) {
                        return (obj->getTaskName() == targetID && obj->isTaskFinished());
                        });

                    // ���δ��ɣ����ð�ť
                    if (it == tasks.end()) {
                        button->setEnabled(false); // ���ð�ť
                    }
                }
                else if (i == 3) {
                    button->setTitleText("village");
                }
                else
                    button->setTitleText("none");

                // ��Ӱ�ť����¼�
                button->addClickEventListener(std::bind(&MiniMap::ButtonCallback, this, std::placeholders::_1));

                // ����ť��ӵ�������
                this->addChild(button);
            }
        }
    }

    // ����Ǵ�ׯ
    if (mapName == "village.tmx") {
        // Ѱ���Ƿ���gate��
        auto gateLayer = tiledMap->getObjectGroup("Gate");

        // ��Ǵ������
        bool gate = false;

        // �����gate�㣬��gate����
        if (gateLayer) {
            auto gateObjects = gateLayer->getObjects();
            for (const auto& object : gateObjects) {
                cocos2d::ValueMap boatProperties = object.asValueMap();
                auto x = boatProperties["x"].asFloat();
                auto y = boatProperties["y"].asFloat();
                auto width = boatProperties["width"].asFloat();
                auto height = boatProperties["height"].asFloat();
                if (tilePos.x >= x && tilePos.x <= x + width && tilePos.y >= y && tilePos.y <= y + height) {
                    gate = true;
                    break;
                }
            }
        }

        // �����gate��
        if (gate) {
            // ������ť
            auto button1 = ui::Button::create("button_normal.png", "button_pressed.png", "button_disabled.png");
            auto button2 = ui::Button::create("button_normal.png", "button_pressed.png", "button_disabled.png");

            // ���ð�ť��λ��
            button1->setPosition(cocos2d::Vec2(centralWorldPos.x, centralWorldPos.y - visibleSize.height / 3));
            button2->setPosition(cocos2d::Vec2(centralWorldPos.x, centralWorldPos.y + visibleSize.height / 3));

            // ���ð�ť����
            button1->setTitleText("castle"); // �����ı�
            button1->setTitleFontSize(48); // �����ֺ�
            button1->setTitleColor(Color3B(0, 0, 0)); // ���ñ���Ϊ��ɫ
            button1->setTitleFontName("Arial"); // ���ñ�������
            button2->setTitleText("none"); // �����ı�
            button2->setTitleFontSize(48); // �����ֺ�
            button2->setTitleColor(Color3B(0, 0, 0)); // ���ñ���Ϊ��ɫ
            button2->setTitleFontName("Arial"); // ���ñ�������

            // ��Ӱ�ť����¼�
            button1->addClickEventListener(std::bind(&MiniMap::ButtonCallback, this, std::placeholders::_1));
            button2->addClickEventListener(std::bind(&MiniMap::ButtonCallback, this, std::placeholders::_1));

            // ����ť��ӵ�������
            this->addChild(button1);
            this->addChild(button2);
        }
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
    removeChildByName("label");

    // �� Ref ָ��ת��Ϊ Button ָ��
    ui::Button* button = static_cast<ui::Button*>(sender);

    // ��ȡ��ť����
    std::string title = button->getTitleText();

    // �������Ϊ�����ļ���
    if (title == "gold")
        title += "1.tmx";
    else
        title += ".tmx";

    // �Ƴ���ť
    button->removeFromParent();

    // ǰ���µ�ͼ
    BoatingToMap(title);
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