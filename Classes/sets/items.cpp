#include "items.h"
#include"player.h" 
//ǰ������
class Player;

//����
//ʰȡ
void Item::pick()
{
	if (!inBag)								//������ڱ�����
		inBag = true;						//ʰȡ
}

//����
void  Item::drop()
{
	if (!inBag)								//������ڱ�����
		inBag = false;						//����  �����뱳��
}

//װ��
void Item::equip()
{
	if (inBag && isEquiped == false)		//����ڱ�����
		isEquiped = true;					//װ��	

}

//ж��
void Item::unequip()
{
	if (inBag && isEquiped)					//����ڱ����� �� װ��
		isEquiped = false;					//ж��	

}
//����										//����ͨ������ʵ�� ���������ͻ���
void Item::upgrade() {}


//����
void Item::discard()
{
	if (inBag)								//����ڱ�����
	{
		inBag = false;						//����
		num = 0;							//����Ϊ0
		//����ʾͼ��
	}
}

/*************************************************************************/

//������ ����

//װ��
void Weapon::equip()
{
	Item::equip();							//���û����װ������ 
}

//ж��
void Weapon::unequip()
{
	Item::unequip();						//���û����ж�º��� 
}

//����
void Weapon::upgrade()
{
	if (inBag && level <= 3)
	{
		level++;							//����
		attack += SIDE_UPGRADE_ATTACK;		//����ɱ����
	}
}


/*************************************************************************/

//װ���� ����
//����

// װ��
void Armor::equip()
{
	if (inBag && !isEquiped)
	{
		isEquiped = true;					//װ��
	}
}
//ж��
void Armor::unequip()
{
	if (inBag && isEquiped)
	{
		isEquiped = false;					//ж��
	}
}
//����
void Armor::upgrade()
{
	if (inBag && level <= 3)				//����ڱ����� �� �ȼ�С�ڵ���3
	{
		level++;							//����
		protect += SIDE_UPGRADE_PROTECT;	//���ӷ�����
	}
}

/*************************************************************************/

//ʳ���� ����

//���
void Food::cook()
{
	if (inBag && !isCooked)
	{
		isCooked = true;					//���
		name = "Cooked " + name;			//���ָı�
		value = BASIC_VALUE * 8;			//��ֵ�ı�
	}
}

//ʳ��
void Food::eat()
{
	if (inBag && num != 0)
	{
		num--;								//��������
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
void GameMaterial::use()					//�������ľͷ��ʯͷ������������  ��ľȡ��ɣ����ǡ�
{
	if (inBag)
	{
		//ʹ��  
		num--;								//��������
		if (num == 0)
		{
			//����ʾͼ��
		}
	}
}


/**************************************************************************/

//������Ʒ��

//�������
void TaskItem::Finish()
{
	if (num == 5)							//�������Ϊ5
	{
		//�������
		num = 0;							//��������
		this->discard();					//���� 
		//�滻����һ����־��
		isFinished = true;//���
		//�Ի�
		//���վ�ս
	}
}


