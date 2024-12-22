#ifndef __BACKPACK_LAYER_H__
#define __BACKPACK_LAYER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Backpack.h"  // ���뱳����
#include "Sets/items.h"      

USING_NS_CC;

class BackpackLayer : public Layer
{
public:
    // �������������
    BackpackLayer();
    ~BackpackLayer();
     
    virtual bool init();                // ��ʼ������
	static BackpackLayer* create();     // ������̬�� create �������򻯴�������Ĺ���
    void createBackpackUI();             // ��������ʾ�������ݵĺ���
    void setBackpack(Backpack* backpack);// ���ñ������ݣ���Ʒ��

private:
    // ��������
    Backpack* _backpack;
    std::vector<Item*> _items;  // �洢��Ʒ������

};

#endif // __BACKPACK_LAYER_H__
