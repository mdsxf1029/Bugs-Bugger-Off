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
    CCLOG("Current player position: (%f, %f)", currentPos.x, currentPos.y);

    // ��ȡ���ؾ�����λ��
    cocos2d::Vec2 newPos = GlobalManager::getInstance().getPlayer()->Move(keyCode);
    CCLOG("New player position: (%f, %f)", newPos.x, newPos.y);

    // �Ƿ�����
    bool walkable = true;

    // ��ȡ��ײ���Ķ�̬������
    auto collisionLayer = tiledMap->getObjectGroup("Collision");

    // ��ȡ���ű���
    auto scaleX = tiledMap->getScaleX();
    auto scaleY = tiledMap->getScaleY();
    CCLOG("Scale factors: (%f, %f)", scaleX, scaleY);

    // ��ȡ��ǰ��������ԭ������
    cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    CCLOG("Visible area: origin(%f, %f), size(%f, %f)", origin.x, origin.y, visibleSize.width, visibleSize.height);

    // �����Ӵ����ĵ���������
    cocos2d::Vec2 centralWorldPos = cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 2);
    CCLOG("Window center world position: (%f, %f)", centralWorldPos.x, centralWorldPos.y);

    // ��ȡ��ǰ��Ƭ��ͼ��С
    cocos2d::Size mapSize = tiledMap->getMapSize();
    CCLOG("Tile map size: (%f, %f)", mapSize.width, mapSize.height);

    // ��ȡ��Ƭ��ͼ��Ƭ��С
    cocos2d::Size tileSize = tiledMap->getTileSize();
    CCLOG("Tile size: (%f, %f)", tileSize.width, tileSize.height);

    // ��ȡ��ǰ��Ƭ��ͼ����
    cocos2d::Vec2 currentMapPos = tiledMap->getPosition();
    CCLOG("Current tile map position: (%f, %f)", currentMapPos.x, currentMapPos.y);

    // ������Ƭ���ź��С
    cocos2d::Size playerSize = tileSize;
    playerSize.width *= scaleX;
    playerSize.height *= scaleY;

    // ͨ�����������ȡ��������Ƭ���е��������
    cocos2d::Vec2 tilePos = tiledMap->convertToNodeSpace(newPos);
    CCLOG("Relative tile position: (%f, %f)", tilePos.x, tilePos.y);

    // �������ײ���㣬��Collision����
    if (collisionLayer) {
        auto collisionObjects = collisionLayer->getObjects();
        CCLOG("Number of collision objects: %lu", collisionObjects.size());
        for (const auto& object : collisionObjects) {
            cocos2d::ValueMap collisionProperties = object.asValueMap();
            auto x = collisionProperties["x"].asFloat();
            auto y = collisionProperties["y"].asFloat();
            auto width = collisionProperties["width"].asFloat();
            auto height = collisionProperties["height"].asFloat();
            CCLOG("Collision area: (%f, %f), width: %f, height: %f", x, y, width, height);
            if (tilePos.x >= x && tilePos.x <= x + width && tilePos.y >= y && tilePos.y <= y + height) {
                walkable = false;
                CCLOG("Collision detected: cannot move to (%f, %f)", tilePos.x, tilePos.y);
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
        CCLOG("Number of boat objects: %lu", boatObjects.size());
        for (const auto& object : boatObjects) {
            cocos2d::ValueMap boatProperties = object.asValueMap();
            auto x = boatProperties["x"].asFloat();
            auto y = boatProperties["y"].asFloat();
            auto width = boatProperties["width"].asFloat();
            auto height = boatProperties["height"].asFloat();
            CCLOG("Boat area: (%f, %f), width: %f, height: %f", x, y, width, height);
            if (tilePos.x >= x && tilePos.x <= x + width && tilePos.y >= y && tilePos.y <= y + height) {
                boat = true;
                CCLOG("Boat detected: player is on a boat spot");
                break;
            }
        }
    }

    // �������boat�����Ի���
    if (boat) {
        CCLOG("Entering boat dialog");

        // �����Ի���ı�������
        auto background = cocos2d::Sprite::create();
        float width = visibleSize.width / 2, height = visibleSize.height / 2; // ���öԻ���Ĵ�С
        background->setTextureRect(cocos2d::Rect(0.0f, 0.0f, width, height)); // ��Ϊ����
        background->setColor(Color3B(255, 255, 255)); // ���öԻ��򱳾�Ϊ��ɫ        
        background->setPosition(centralWorldPos); // ���öԻ���λ��Ϊ�Ӵ�����       
        background->setOpacity(200); // ���öԻ���͸����Ϊ�ϸ�
        background->setName("background"); // ���ñ������������
        this->addChild(background);

        // �������ֱ�ǩ
        auto label = cocos2d::Label::createWithSystemFont("Where do you want to go?", "fonts/arial.ttf", 64); // �����ı�
        label->setPosition(centralWorldPos + cocos2d::Vec2(0.0f, visibleSize.height / 3)); // ����λ��
        label->setColor(cocos2d::Color3B(0, 0, 0)); // �����ı���ɫΪ��ɫ
        label->setName("label"); // �����ı���ǩ������
        this->addChild(label);

        // �������ڵ�������а�ť
        auto buttonParentNode = cocos2d::Node::create();
        this->addChild(buttonParentNode);

        // �����رհ�ť
        auto closeButton = ui::Button::create("CloseSelected.png");

        // ���ùرհ�ťλ��
        closeButton->setPosition(centralWorldPos + cocos2d::Vec2(width / 2, height / 2));

        // ��Ӱ�ť����¼�
        closeButton->addClickEventListener([this, buttonParentNode](cocos2d::Ref* sender) {
            // ���ұ�������
            auto sprite = this->getChildByName("background");

            // �Ƴ���������
            if (sprite) {
                sprite->removeFromParentAndCleanup(true);
                CCLOG("background sprite has been removed.");
            }

            // �������ֱ�ǩ
            auto label = this->getChildByName("label");

            // �Ƴ����ֱ�ǩ
            if (label) {
                label->removeFromParentAndCleanup(true);
                CCLOG("label has been removed.");
            }

            // �Ƴ����а�ť
            buttonParentNode->removeAllChildren();
            });
        // ����ť��ӵ����ڵ�
        buttonParentNode->addChild(closeButton);

        // ��ͬ��ͼ
        std::vector<std::string> map = { "gold","wood","water","fire","earth","none","village" };

        // ��������Ǵ�ׯ
        if (mapName == "smallmap/village.tmx")
        {
            for (int i = 0; i < 6; i++)
            {
                // ������ť
                auto button = ui::Button::create("CloseSelected.png", "CloseSelected.png", "CloseSelected.png");

                // ���ð�ť����
                button->setTitleText(map[i]); // �����ı�
                CCLOG("Build button %s", map[i].c_str());
                button->setTitleFontSize(48); // �����ֺ�
                button->setTitleColor(Color3B(0, 0, 0)); // ���ñ���Ϊ��ɫ
                button->setTitleFontName("Arial"); // ���ñ�������

                // ��ȡ����
                const auto& tasks = GlobalManager::getInstance().getTasks();
                std::string targetID = "TASK_";
                std::string need;
                if (i != 0)
                    need = map[i - 1];
                std::transform(need.begin(), need.end(), need.begin(),
                    [](unsigned char c) { return std::toupper(c); }); // ת��д
                targetID += need;

                // ��ѯ�����Ƿ����
                auto it = std::find_if(tasks.begin(), tasks.end(), [targetID](const std::shared_ptr<Task>& obj) {
                    return (obj->getTaskName() == targetID && obj->isTaskFinished());
                    });

                // ���δ��ɣ����ð�ť
                if (it == tasks.end() && i != 0)
                {
                    button->setEnabled(false); // ���ð�ť
                }

                // ��Ӱ�ť����¼�
                button->addClickEventListener(std::bind(&MiniMap::ButtonCallback, this, std::placeholders::_1));

                // ���ð�ťλ��
                button->setPosition(cocos2d::Vec2(centralWorldPos.x, visibleSize.height * 2 / 3 - i * 70));

                // ����ť��ӵ����ڵ���
                buttonParentNode->addChild(button);
            }
        }
        else if (mapName == "smallmap/castle.tmx")
        {
            // ������ť
            auto button1 = ui::Button::create("CloseNormal.png", "CloseNormal.png", "CloseNormal.png");
            auto button2 = ui::Button::create("CloseSelected.png", "CloseSelected.png", "CloseSelected.png");

            // ���ð�ť��λ��
            button1->setPosition(cocos2d::Vec2(centralWorldPos.x, centralWorldPos.y - visibleSize.height / 10));
            button2->setPosition(cocos2d::Vec2(centralWorldPos.x, centralWorldPos.y + visibleSize.height / 10));

            // ���ð�ť����
            button1->setTitleText(map[6]); // �����ı�
            CCLOG("Build button %s", map[6].c_str());
            button1->setTitleFontSize(48); // �����ֺ�
            button1->setTitleColor(Color3B(0, 0, 0)); // ���ñ���Ϊ��ɫ
            button1->setTitleFontName("Arial"); // ���ñ�������
            button2->setTitleText(map[5]); // �����ı�
            CCLOG("Build button %s", map[5].c_str());
            button2->setTitleFontSize(48); // �����ֺ�
            button2->setTitleColor(Color3B(0, 0, 0)); // ���ñ���Ϊ��ɫ
            button2->setTitleFontName("Arial"); // ���ñ�������

            // ��Ӱ�ť����¼�
            button1->addClickEventListener(std::bind(&MiniMap::ButtonCallback, this, std::placeholders::_1));
            button2->addClickEventListener(std::bind(&MiniMap::ButtonCallback, this, std::placeholders::_1));

            // ����ť��ӵ����ڵ���
            buttonParentNode->addChild(button1);
            buttonParentNode->addChild(button2);
        }
        else
        {
            // �������ڵ�ͼ
            std::string newMap1, newMap2;
            GetNeighborMap(newMap1, newMap2);

            for (int i = 0; i < 4; i++)
            {
                // ������ť
                auto button = ui::Button::create("CloseSelected.png", "CloseSelected.png", "CloseSelected.png");

                // ���ð�ťλ��
                button->setPosition(cocos2d::Vec2(centralWorldPos.x, visibleSize.height * 2 / 3 - i * 100));

                // ���ð�ť����
                button->setTitleFontSize(48); // �����ֺ�
                button->setTitleColor(Color3B(0, 0, 0)); // ���ñ���Ϊ��ɫ
                button->setTitleFontName("Arial"); // ���ñ�������

                // ���ñ����ı�
                if (i == 0 || i == 1)
                {
                    std::string need;
                    if (i == 0)
                    {
                        button->setTitleText(newMap1);
                        need = newMap1;
                    }
                    else
                    {
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
                    if (it == tasks.end())
                    {
                        button->setEnabled(false); // ���ð�ť
                    }
                }
                else if (i == 3)
                {
                    button->setTitleText("village");
                }
                else
                    button->setTitleText("none");

                // ��Ӱ�ť����¼�
                button->addClickEventListener(std::bind(&MiniMap::ButtonCallback, this, std::placeholders::_1));

                // ����ť��ӵ�������
                buttonParentNode->addChild(button);
            }
        }
    }

    // ����Ǵ�ׯ
    if (mapName == "smallmap/village.tmx")
    {
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
        if (gate)
        {
            // �������ڵ�������а�ť
            auto buttonParentNode = cocos2d::Node::create();
            this->addChild(buttonParentNode);

            // ������ť
            auto button1 = ui::Button::create("CloseNormal.png", "CloseNormal.png", "CloseNormal.png");
            auto button2 = ui::Button::create("CloseSelected.png", "CloseSelected.png", "CloseSelected.png");

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

            // ����ť��ӵ����ڵ���
            buttonParentNode->addChild(button1);
            buttonParentNode->addChild(button2);
        }
    }
    // ��������߽���������
    float minWorldX = centralWorldPos.x - visibleSize.width / 4;
    float minWorldY = centralWorldPos.y - visibleSize.height / 4;
    float maxWorldX = centralWorldPos.x + visibleSize.width / 4;
    float maxWorldY = centralWorldPos.y + visibleSize.height / 4;

    // �����ǰ��������
    if (walkable)
    {
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
    else
    {
        CCLOG("�޷�ǰ��(%f,%f)", newPos.x, newPos.y);
    }
}

void MiniMap::ButtonCallback(Ref* sender)
{
    // �Ƴ���������
    this->removeChildByName("background");

    // �Ƴ����ֱ�ǩ
    this->removeChildByName("label");

    // �� Ref ָ��ת��Ϊ Button ָ��
    ui::Button* button = static_cast<ui::Button*>(sender);

    // ��ȡ��ť����
    std::string title = button->getTitleText();

    // �������Ϊ�����ļ���
    title = "smallmap/" + title;
    if (title == "smallmap/gold")
        title += "1.tmx";
    else
        title += ".tmx";

    // ��ȡ��ť�ĸ��ڵ�
    auto parentNode = button->getParent();

    // �Ƴ����а�ť
    if (parentNode)
        parentNode->removeAllChildren();
    else
        button->removeFromParentAndCleanup(true);

    // ǰ���µ�ͼ
    if (title != "smallmap/none.tmx")
        BoatingToMap(title);
}

void MiniMap::GetNeighborMap(std::string& newMap1, std::string& newMap2)
{
    if (mapName == "smallmap/gold1.tmx")
    {
        newMap1 = "earth";
        newMap2 = "wood";
    }
    else if (mapName == "smallmap/wood.tmx")
    {
        newMap1 = "gold";
        newMap2 = "water";
    }
    else if (mapName == "smallmap/water.tmx")
    {
        newMap1 = "wood";
        newMap2 = "fire";
    }
    else if (mapName == "smallmap/fire.tmx")
    {
        newMap1 = "water";
        newMap2 = "earth";
    }
    else if (mapName == "smallmap/earth.tmx")
    {
        newMap1 = "fire";
        newMap2 = "gold";
    }
}