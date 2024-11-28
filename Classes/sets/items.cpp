#include "items.h"
#include"player.h"
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
	{
		in_bag = false;//����
		num = 0;//����Ϊ0
		//����ʾͼ��
	}
}//����

virtual void item::equip() = 0 {
	if (in_bag && is_equiped == false)//����ڱ�����
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
	if (in_bag&&is_equiped==false)
	{
		is_equiped = true;//װ��
	}
}

/*************************************************************************/

//װ���� ����
//����
virtual void Armor::upgrade() override
{
	if (in_bag && level <= 3)//����ڱ����� �� �ȼ�С�ڵ���3
	{
		level++;//����
		protect += UPGRADE_PROTECT;//���ӷ�����
	}
}

/*************************************************************************/

//ʳ���� ����

//���
virtual void Food::cook() override
{
	if (in_bag && !is_cooked)
	{
	//	���
		is_cooked = true;//���
	}
}

//ʳ��
virtual void Food::eat() override
{
	if (in_bag)
	{
		hero.heal(healHp);//�ظ�
		num--;//��������
		if (num == 0)
		{
			//����ʾͼ��
		}
		//ʹ��ʳ��
	}
}

/*************************************************************************/

//������

//ʹ��
virtual void Material::use() override
{
	//�������ľͷ��ʯͷ������������  ��ľȡ��ɣ����ǡ�
	if (in_bag)
	{
		//ʹ��  
		num--;//��������
		if (num == 0)
		{
			//����ʾͼ��
		}
	}
}


/**************************************************************************/

//������Ʒ��

//�������
virtual void Task::finish() override
{
	if (num == 5)//�������Ϊ5
	{
		//�������
		num = 0;//��������
		this->discard();//���� 
		//�滻����һ����־��

		//�Ի�
		//���վ�ս
	}
}


