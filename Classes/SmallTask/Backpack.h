#ifndef __BACKPACK_H__
#define __BACKPACK_H__

#include <vector>
#include <string>
#include "manager.h"
struct item {
    int num;
    std::string name;
};
class Backpack
{
public:
    Backpack();
    ~Backpack();

    // �����Ʒ������
    void addItem(const std::string& item);

    // ��ȡ�����е�������Ʒ
    std::vector<item>& getItems() ;


    std::vector<item> _items; // �洢��Ʒ
};

#endif // __BACKPACK_H__
