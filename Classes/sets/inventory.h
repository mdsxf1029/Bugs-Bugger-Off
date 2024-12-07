#pragma once
#ifndef INVENTORY_H
#define INVENTORY_H

#include <string>
#include <vector>

class Item;//ǰ������

constexpr int BAG_SIZE = 10;
//������
class Inventory {
public: 
	//����
	void showInventory();//չʾ����
	//����
	bool addItem(Item* item);//�����Ʒ
	void removeItem(Item* item);//�Ƴ���Ʒ
	void useItem(Item* item);//ʹ����Ʒ


	int getSize() const;//�õ���С
	bool isFull();//�Ƿ�����
protected:

private:
	friend class Player;
	friend class Item;

	std::vector<Item*> items;//��Ʒ ָ�� (items�ඨ����������)
	int size=BAG_SIZE;//������С
	int item_num=0;//��Ʒ����
};


#endif