#ifndef BASE_MAP_H
#define BASE_MAP_H

#include "cocos2d.h"
#include <map>
#include <string>

class BaseMap : public cocos2d::Node {
public:
    // ���캯������������
    BaseMap();
    virtual ~BaseMap();

    // ���ص�ͼ�ļ�
    virtual void loadMap(const std::string& mapFile);

    // ���������麯�������������д��
    virtual void handleInteraction(const cocos2d::Vec2& position);

    // ����̽��״̬���麯�������������д��
    virtual void updateExploration(const cocos2d::Vec2& position);

    // ���ý�ɫ�ڵ�ͼ�е�λ��
    void setPlayerPosition(const cocos2d::Vec2& position);

    // ��ȡ��ɫ��ǰλ��
    cocos2d::Vec2 getPlayerPosition() const;

protected:
    cocos2d::TMXTiledMap* tiledMap;                // ��ǰ��ͼ����Ƭ��ͼ
    std::map<std::string, cocos2d::Vec2> locationPoints; // ��ͼ�ϵĽ�����
    bool isExplored;                               // �Ƿ���̽��
    cocos2d::Vec2 playerPosition;                 // ��ɫ��ǰλ��
};

#endif // BASE_MAP_H

#pragma once
#pragma once
