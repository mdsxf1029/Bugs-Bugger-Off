#ifndef __BACKPACK_H__
#define __BACKPACK_H__

#include <vector>
#include <string>
#include "Sets/manager.h"
struct item {
    int num;
    std::string name;
};
class Backpack
{
public:
    Backpack();
    ~Backpack();

    
	void addItem(const std::string& item);  // �����Ʒ

    std::vector<item>& getItems() ;         // ��ȡ�����е�������Ʒ
 
    std::vector<item> _items;                // �洢��Ʒ
};

#endif // __BACKPACK_H__
