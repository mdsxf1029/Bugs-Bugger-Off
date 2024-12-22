#include "BossMapInteraction.h"
#include "Sets/inventory.h"  // ������ұ���

USING_NS_CC;

bool BossMapInteraction::init()
{
    // ��ʼ����ͼ
    map.loadMap("boss.tmx");
    selectedItem = nullptr;

    // ����������¼�
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [=](Touch* touch, Event* event) {
        Vec2 touchLocation = touch->getLocation();
        checkItemClick(touchLocation);
        return true;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    // ���ص�ͼ���ݣ�������Ʒ����ײ�����
    loadMapData();

    return true;
}

void BossMapInteraction::loadMapData()
{
    // ���ص�ͼ
    map.loadMap("boss.tmx");

    // ��ȡ��ײ��
    auto collisionLayer = map->getObjectGroup("Collision");
    if (collisionLayer)
    {
        auto collisionObjects = collisionLayer->getObjects();
        for (const auto& object : collisionObjects)
        {
            ValueMap collisionProperties = object.asValueMap();
            auto collisionID = collisionProperties["id"].asInt();  // ��ȡ��ײ����� ID
            auto x = collisionProperties["x"].asFloat();
            auto y = collisionProperties["y"].asFloat();
            CCLOG("Collision Object ID: %d at Position: (%f, %f)", collisionID, x, y);

            // �洢��ײ��������ݣ�׼������ʹ��
            collisionItems.push_back(CollisionItem{ collisionID, Vec2(x, y) });
        }
    }
    // ��ȡ�ɽ����������
    auto goldoreLayer = map->getObjectGroup("GoldOre");
    if (goldoreLayer)
    {
        auto goldoreObjects = collisionLayer->getObjects();
        for (const auto& object : goldoreObjects)
        {
            ValueMap goldoreProperties = object.asValueMap();
            auto goldoreID = goldoreProperties["id"].asInt();  // ��ȡ��ײ����� ID
            auto x = goldoreProperties["x"].asFloat();
            auto y = goldoreProperties["y"].asFloat();
            CCLOG("GoldOre Object ID: %d at Position: (%f, %f)", goldoreID, x, y);

            // �洢��ײ��������ݣ�׼������ʹ��
            goldoreItems.push_back(Item{ goldoreID, Vec2(x, y) });
        }
    }
}

void BossMapInteraction::onEnter()
{
    Scene::onEnter();
    // ����һЩ��ʼ������
}

void BossMapInteraction::onExit()
{
    // ������Դ
    _eventDispatcher->removeEventListenersForTarget(this);
    Scene::onExit();
}

void BossMapInteraction::checkItemClick(const Vec2& touchLocation)
{
    // ������Ʒ������Ƿ�������Ʒ
    for (auto it = goldoreItems.begin(); it != goldoreItems.end(); ++it)
    {
        // ������Ʒ�ĵ����Χ��һ���̶��İ뾶������Ը���ʵ������������ֵ
        float radius = 30.0f;  // ������Ʒ�ĵ����Χ�� 30 ����

        if (it->position.distance(touchLocation) < radius)
        {
            // ����������Ʒ�ˣ�ִ��ʰȡ����
            PickUpInteraction(&(*it));  // ����ָ����Ʒ��ָ�룬����ʰȡ

            // ����Ʒ������ɾ���Ѿ�ʰȡ����Ʒ
            goldoreItems.erase(it);  // ɾ����ǰ��Ʒ
            CCLOG("Picked up GoldOre Item with ID: %d", it->id);

            // ��ȡ�����Ʒ���ڵĶ����
            auto goldoreLayer = map->getObjectGroup("GoldOre");
            if (goldoreLayer)
            {
                // �������ж����ҵ��뵱ǰ�����Ʒƥ��� ID�����Ӷ����ɾ��
                auto goldoreObjects = goldoreLayer->getObjects();
                for (auto& object : goldoreObjects)
                {
                    ValueMap goldoreProperties = object.asValueMap();
                    int goldOreID = goldoreProperties["id"].asInt();
                    if (goldOreID == it->id)  // ƥ����Ʒ ID
                    {
                        goldoreLayer->removeObject(object);  // �Ӷ����ɾ����Ʒ
                        CCLOG("Removed GoldOre Object ID: %d at Position: (%f, %f)", goldOreID, it->position.x, it->position.y);
                        break;  // �ҵ���ɾ�����˳�
                    }
                }
            }

            break;  // ����һ�ε��ֻ��ʰȡһ����Ʒ
        }
    }
}

bool BossMapInteraction::checkPlayerPosition(const Vec2& playerPosition)
{
    // �������Ƿ�Ӵ�����ײ����
    for (const auto& collisionItem : collisionItems)
    {
        if (collisionItem.position.distance(playerPosition) < collisionThreshold)
        {
            // �����������ײ����
            CCLOG("Player cannot pass through Collision Object ID: %d", collisionItem.id);
            return false;  // ��ֹ��ɫ�����ƶ�
        }
    }
}

void BossMapInteraction::PickUpInteraction(Item* item)
{
    // ��ʾʰȡ��ʾ
    if (!Inventory::isFull)
    {
        auto label = Label::createWithTTF("You picked up: " + item->getName(), "fonts/arial.ttf", 24);
        label->setPosition(Director::getInstance()->getVisibleSize() / 2);
        this->addChild(label);
        label->runAction(Sequence::create(
            FadeOut::create(2.0f),
            RemoveSelf::create(),
            nullptr));

        // ����Ʒ���뱳��
        Inventory::addItem(item);
    }
    else
    {
        auto label = Label::createWithTTF("Inventory is full", "fonts/arial.ttf", 24);
        label->setPosition(Director::getInstance()->getVisibleSize() / 2);
        this->addChild(label);
        label->runAction(Sequence::create(
            FadeOut::create(2.0f),
            RemoveSelf::create(),
            nullptr));
    }
}