#include "SpecialMap.h"

USING_NS_CC;

SpecialMap::SpecialMap() {}

SpecialMap::~SpecialMap() {}

void SpecialMap::loadMap(const std::string& mapFile) {
    // ���û���ļ��ص�ͼ����
    BaseMap::loadMap(mapFile);

    // ���������ͼ�ĳ�ʼ���߼�
    CCLOG("SpecialMap loaded: %s", mapFile.c_str());
}

void SpecialMap::handleInteraction(const Vec2& position) {
    // ���û���Ľ����߼�
    BaseMap::handleInteraction(position);

    // �������⽻���߼�
    CCLOG("SpecialMap interaction at position: (%f, %f)", position.x, position.y);

    // ʾ��������ս��
    triggerBattle(position);
}

void SpecialMap::generateMaze() {
    // 
    CCLOG("Generating maze...");
    // �������ʵ���Թ������㷨
}

void SpecialMap::triggerBattle(const Vec2& position) {
    //����ս���߼�
    CCLOG("Battle triggered at position: (%f, %f)", position.x, position.y);
    // ������Լ���ս�������򴥷�ս���¼�
}
