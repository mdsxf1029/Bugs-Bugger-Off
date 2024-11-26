#ifndef SPECIAL_MAP_H
#define SPECIAL_MAP_H

#include "BaseMap.h"

class SpecialMap : public BaseMap {
public:
    // ���캯������������
    SpecialMap();
    virtual ~SpecialMap();

    // ��д���ص�ͼ����
    virtual void loadMap(const std::string& mapFile) override;

    // ��д����������
    virtual void handleInteraction(const cocos2d::Vec2& position) override;

    // �����Թ������߼�
    void generateMaze();

    // ����ս�������߼�
    void triggerBattle(const cocos2d::Vec2& position);
};

#endif // SPECIAL_MAP_H
#pragma once
