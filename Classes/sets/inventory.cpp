//2353924 �뿡��
//inverntory Ϊ��ҵı��� �ĺ���ʵ��
#include<iostream>
#include <typeinfo>
#include "inventory.h"
#include"sets_variables.h"
 

//����
//չʾ����
void Inventory::showInventory()
{

	//��������
	//��ʾ�����е���Ʒ png
	//��ʾ��Ʒ�����֣������֮���ԱߵĽ��棩
	//��ʾ��Ʒ��������ͬ�ϣ�
	//��ʾ��Ʒ�����ԣ�ͬ�ϣ�  ���� Ч��֮��
	//��ʾ��Ʒ�ĵȼ���ͬ�ϣ�
	//��ʾ��Ʒ���Ƿ�װ����ͬ�ϣ� 
}
//����
//�����Ʒ
bool Inventory::addItem(Item& item)
{
	if (items.size() < size)
	{
		items.push_back(&item);
		item_num++;
		return true;
	}
	else
	{
		//��������
		std::cout << "��������" << std::endl;//��ʾ ��ʱ��Ϊ����
		return false;
	}
}

//�Ƴ���Ʒ
void Inventory::removeItem(Item& item)
{
	for (int i = 0; i < BAG_SIZE; i++)
	{
		if (items[i] == &item)
		{
			items.erase(items.begin() + i);
			item_num--;
			break;
		}
	}

}

//ʹ����Ʒvoid 
void Inventory::useItem(Item& item)
{
	//ʹ����Ʒ
	//������Ʒ�����࣬���ò�ͬ�ĺ���
	//���������������
	//����ǻ��ߣ����÷�������
	//�����ʳƷ�����ûظ�����
	//����ǲ��ϣ����úϳɺ���
	//�����������Ʒ������������

	std::string name = item.getName();
	if (name == "Weapon")
	{			// ��ȡ�����Ʒ��ѡ��
			//�˴�����cin����	
		int choice = 0;
		std::cin >> choice;

		switch (choice)
		{
			case 1:
				//����
				item.upgrade();
				break;
			case 2:
				//װ��
				item.equip();
				break;
			case 3:
				//ж��
				item.unequip();
				break;
			default:
				break;
		} 
	}
	else if (name == "Armor")
	{
		int choice = 0;
		std::cin >> choice;
		switch (choice)
		{
			case 1:
				//����
				item.upgrade();
					break;
			case 2:
				//װ��
				item.equip();
				break;
			case 3:
				//ж��
				item.unequip();
				break;
			default:
				break;
		} 
	}
	else if (name == "Food")
	{
		//�ظ�����
		int choice = 0;
		std::cin >> choice;
		switch (choice)
		{
			case 1:
				//ʳ��
				item.eat();
				break;
			case 2:
				//���
				item.cook();
				break;
			default:
				break;
		}
	}
	else if (name == "GameMaterial")
	{
		//ʹ�ú���
		item.use();//����

	} 
		//������Ʒ����������

	else if (name == "TaskItem")
	{
		//������
		//����
		//item->task();
	} 
}


//�õ���С
int Inventory::getSize() const
{
	return size;
}

//�Ƿ�����
bool Inventory::isFull()
{
	if (items.size() == size)
	{
		return true;
	}
	else
	{
		return false;
	}
}
