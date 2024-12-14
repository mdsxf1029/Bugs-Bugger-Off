#include "MiniMap.h"
#include "cocos2d.h"
constexpr int SPEED = 2000;//�ƶ��ٶ�

// �������ؾ���λ��
void MiniMap::UpdatePlayerPosition(const cocos2d::EventKeyboard::KeyCode keyCode)
{
    // ��ȡ���ؾ�����λ��
    //cocos2d::Vec2& newPos = hero.Move(keyCode);
    cocos2d::Vec2 next_position = player->getPosition(), currentPos = player->getPosition();
    switch (keyCode)
    {
    case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
        next_position.y += SPEED * cocos2d::Director::getInstance()->getDeltaTime();
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
        next_position.y -= SPEED * cocos2d::Director::getInstance()->getDeltaTime();
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        next_position.x -= SPEED * cocos2d::Director::getInstance()->getDeltaTime();
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        next_position.x += SPEED * cocos2d::Director::getInstance()->getDeltaTime();
        break;
    default:
        break;
    }
    cocos2d::Vec2 newPos = next_position;

    // �Ƿ�����
    bool walkable = true;

    // ��ȡ��ײ���Ķ�̬������
    auto collisionLayer = tiledMap->getObjectGroup("Collision");

    // ��ȡ���ű���
    auto scaleX = tiledMap->getScaleX();
    auto scaleY = tiledMap->getScaleY();

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
            /*if (collisionProperties["walkable"].isNull()) {
                walkable = true;
                break;
            }
            bool walkable = collisionProperties["walkable"].asBool();
            */
            if (tilePos.x >= x && tilePos.x <= x + width && tilePos.y >= y && tilePos.y <= y + height) {
                walkable = false;
                break;
            }
            // ����Ƿ�����Ҫ����Ƭ
            /*if (playerTile.x >= (x - tileSize.width / 2) && playerTile.x <= (x + tileSize.width / 2)
                && playerTile.y >= (y - tileSize.height/2) && playerTile.y <= (y + tileSize.height/2)) {
                walkable = false;
                break;
            }*/
        }
    }

    // ��ȡ��ǰ��������ԭ������
    cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

    // ��ȡ��ǰ��������Ĵ�С
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

    // �����Ӵ����ĵ���������
    cocos2d::Vec2 centralWorldPos = cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 2);

    // ��������߽���������
    float minWorldX = centralWorldPos.x - visibleSize.width / 4;
    float minWorldY = centralWorldPos.y - visibleSize.height / 4;
    float maxWorldX = centralWorldPos.x + visibleSize.width / 4;
    float maxWorldY = centralWorldPos.y + visibleSize.height / 4;

    // �����ǰ��������
    if (walkable) {
        // ������������
        //hero.setPosition(newPos);
        // ����ƫ����
        auto offset = SPEED * cocos2d::Director::getInstance()->getDeltaTime();

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
        }
    }
    else {
        CCLOG("�޷�ǰ��(%f,%f)", newPos.x, newPos.y);
    }
}