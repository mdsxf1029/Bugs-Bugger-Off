#include "items.h"

//����
/
virtual void item::pick() = 0 {
	if (!in_bag)//������ڱ�����
		in_bag = true;//ʰȡ
};//ʰȡ

virtual void item::drop() = 0 {
	if (!in_bag)//������ڱ�����
		in_bag = false;//����
//�����뱳��
};//����

virtual void item::discard() = 0 {
	if (in_bag)//����ڱ�����
		in_bag = false;//����
};//����

virtual void item::equip() = 0 {
	if (in_bag)//����ڱ�����
	{
		is_equiped = true;
	}
};//װ��

virtual void item::unequip() = 0 {
	if (in_bag && is_equiped)//����ڱ����� �� װ��
	{
		is_equiped = false;
	}
};//ж��

/*************************************************************************/

//������ ����

//����
virtual void Weapon::upgrade() override 
{ 
	if(in_bag)
	{
		level++; //����
		attack += UPGRADE_ATTACK;//����ɱ����
	}
} 

//װ��
virtual void Weapon::equip() override
{
	if (in_bag)
	{
		is_equiped = true;//װ��
	}
}

/*************************************************************************/

//װ���� ����

virtual void upgrade() override
{
	if (in_bag && level <= 3)//����ڱ����� �� �ȼ�С�ڵ���3
	{
		level++;//����
		protect += UPGRADE_PROTECT;//���ӷ�����
	}
}

/*************************************************************************/

//ʳ���� ����

//ʳ���಻��Ҫ����
virtual void use() override
{
	if (in_bag)
	{
		//ʹ��ʳ��
	}
}

