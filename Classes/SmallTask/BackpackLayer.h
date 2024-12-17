#ifndef __BACKPACK_LAYER_H__
#define __BACKPACK_LAYER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Backpack.h"  // ���뱳����
#include "items.h"      

USING_NS_CC;

class BackpackLayer : public Layer
{
public:
    // �������������
    BackpackLayer();
    ~BackpackLayer();

    // ��ʼ������
    virtual bool init();

    // ����������ľ�̬����
    static BackpackLayer* create();

    // ���ñ������ݣ���Ʒ��
    void setBackpack(Backpack* backpack);

private:
    // ��������
    Backpack* _backpack;
    std::vector<Item*> _items;  // �洢��Ʒ������
    // ��������ʾ�������ݵĺ���
    void createBackpackUI();
};

#endif // __BACKPACK_LAYER_H__
