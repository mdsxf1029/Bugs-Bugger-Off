#pragma once
#ifndef INVENTORY_H
#define INVENTORY_H

#include <string>
#include <vector>
#include "items.h"

const int BAG_SIZE = 10;

//������
class Inventory {
public:
	Inventory(int size) :size(size), items(0),item_num(0) {};
	~Inventory() {};
	//����
	void showInventory();//չʾ����
	//����
	bool addItem(Item* item);//�����Ʒ
	void removeItem(Item* item);//�Ƴ���Ʒ
	void useItem(Item* item);//ʹ����Ʒ
	int getSize();//�õ���С
	bool isFull();//�Ƿ�����
	
protected:

private:
	friend class Player;
	friend class Item;

	std::vector<Item*> items;//��Ʒ ָ�� (items�ඨ����������)
	int size;//������С
};

Inventory bag(BAG_SIZE);

#endif