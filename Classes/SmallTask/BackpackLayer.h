#ifndef __BACKPACK_LAYER_H__
#define __BACKPACK_LAYER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Backpack.h"  // ������

USING_NS_CC;

class BackpackLayer : public Layer
{
public:
    // �������������
    BackpackLayer();
    ~BackpackLayer();

    // ��ʼ������
    virtual bool init();

    void createItemUI(const Item& item);

    void onItemClicked(Ref* sender);

    // ����������ľ�̬����
    static BackpackLayer* create();

    // ���ñ������ݣ���Ʒ��
    void setBackpack(Backpack* backpack);

private:
    // ��������
    Backpack* _backpack;

    // ��������ʾ�������ݵĺ���
    void createBackpackUI();
};

#endif // __BACKPACK_LAYER_H__
