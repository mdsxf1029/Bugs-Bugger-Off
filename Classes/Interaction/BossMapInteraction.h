#pragma once
#ifndef __BOSSMAP_INTERACTION_H__
#define __BOSSMAP_INTERACTION_H__

#include "cocos2d.h"  
#include "Map/Map.h"
#include "Sets/items.h"
#include "Sets/npc.h"

class BossMapInteraction : public cocos2d::Scene
{
public:
    virtual bool init();
    virtual void loadMapData();
    CREATE_FUNC(BossMapInteraction);

    void onEnter();  // ����������¼�
    void onExit();   // �˳�ʱ�Ƴ�����
    void PickUpInteraction(Item* item);
private:
    void checkItemClick(const cocos2d::Vec2& touchLocation);  // �����Ʒ�Ƿ񱻵��
    bool checkPlayerPosition(const cocos2d::Vec2& playerPosition);

    Map map;  // ��ͼ����
    std::vector<Item*> items;  // �洢���п��Խ�������Ʒ
    Item* selectedItem;  // ��ѡ�е���Ʒ

    // ����һ���ṹ�����洢��ײ�������Ϣ
    struct CollisionItem
    {
        int id;          // ��ײ����� ID
        cocos2d::Vec2 position;  // ��ײ�����λ��
    };

    // �洢��ײ���������
    std::vector<CollisionItem> collisionItems;
    // �洢��Ʒ������
    std::vector<Item> goldoreItems;

    // ��ײ�����ֵ����λ������
    float collisionThreshold = 50.0f;  // ����ʵ�����������ֵ
};

#endif // __BOSSMAP_INTERACTION_H__
