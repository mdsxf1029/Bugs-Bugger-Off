//2353924 �뿡��
//inverntory Ϊ��ҵı��� �ĺ���ʵ��

#include "inventory.h"

Inventory::~Inventory() {};

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
bool Inventory::addItem(Item* item)
{
	if (items.size() < size)
	{
		items.push_back(item);
		item_num++;
		return true;
	}
	else
	{
		//��������
		cout << "��������" << endl;//��ʾ ��ʱ��Ϊ����
		return false;
	}
} 

//�Ƴ���Ʒ
void Inventory::removeItem(Item* item) 
{
	for (int i=0;i<BAG_SIZE;i++)
	{
		if (items[i] == item)
		{
			items.erase(items.begin() + i);
			item_num--;
			break;
		}
	}

}

//ʹ����Ʒ
void Inventory::useItem(Item* item)
{
	//ʹ����Ʒ
	//������Ʒ�����࣬���ò�ͬ�ĺ���
	//���������������
	//����ǻ��ߣ����÷�������
	//�����ʳƷ�����ûظ�����
	//����ǲ��ϣ����úϳɺ���
	//�����������Ʒ������������
	
	auto type = item->getType();
	switch (type)
	{
		case ItemType::WEAPON:
		{
			// ��ȡ�����Ʒ��ѡ��
			//�˴�����cin����	
			int choice = 0;
			
			switch (choice)
			{
				case 1:
					//����
					item->upgrade();
					break;
				case 2:
					//װ��
					item->equip();
					break;
				case 3:
					//ж��
					item->unequip();
					break;
				default:
					break;
			} 
			break;
		}
		case ItemType::ARMOR:
		{
			int choice=0;
			cin >> choice;
			switch(choice)
			{
				case 1:
					//����
					item->upgrade();
					break;
				case 2:
					//װ��
					item->equip();
					break;
				case 3:
					//ж��
					item->unequip();
					break;
				default:
					break;
			}
			
			break;
		}
		case ItemType::FOOD:
		{
			//�ظ�����
			int choice = 0;
			cin >> choice;
			switch (choice)
			{
				case 1:
					//�ظ�
					item->heal();
					break;
				case 2:
					//���
					item->cook();
					break;
	 			default:
					break;
			}
			break;
		}
		case ItemType::MATERIAL:
		{
			//�ϳɺ���
			if()
			break;
		}
		case ItemType::TASK:
		{
	
			//������
			 
			break;
		}

		default:
			break;	
	}

} 

//�õ���С
int Inventory::getSize() 
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
