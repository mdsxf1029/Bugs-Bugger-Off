#ifndef __BACKPACK_LAYER_H__
#define __BACKPACK_LAYER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Backpack.h"  // 引入背包类
#include "items.h"      

USING_NS_CC;

class BackpackLayer : public Layer
{
public:
    // 构造和析构函数
    BackpackLayer();
    ~BackpackLayer();

    // 初始化函数
    virtual bool init();

    // 创建背包层的静态方法
    static BackpackLayer* create();

    // 设置背包数据（物品）
    void setBackpack(Backpack* backpack);

private:
    // 背包数据
    Backpack* _backpack;
    std::vector<Item*> _items;  // 存储物品的容器
    // 创建并显示背包内容的函数
    void createBackpackUI();
};

#endif // __BACKPACK_LAYER_H__
