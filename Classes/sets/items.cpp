#include "items.h"
#include "player.h" 

class Player;                               //ǰ������

//����
void Item::pick()                           //ʰȡ
{
	if (!inBag)								//������ڱ�����
		inBag = true;						//ʰȡ
}

void  Item::drop()                          //����
{
	if (!inBag)								//������ڱ�����
		inBag = false;						//����  �����뱳��
}

void Item::equip()                          //װ��
{
	if (inBag && isEquiped == false)		//����ڱ�����
		isEquiped = true;					//װ��	
}

void Item::unequip()                        //ж��
{
	if (inBag && isEquiped)					//����ڱ����� �� װ��
		isEquiped = false;					//ж��	
}

void Item::upgrade() {}                     //����������ͨ������ʵ�� ���������ͻ���

void Item::discard()                        //����
{
	if (inBag)								//����ڱ�����
	{
		inBag = false;						//����
		num = 0;							//����Ϊ0
	}
}

bool Item::initwithFile(const std::string& filename)
{
	if (!Sprite::initWithFile(filename)) {
		std::cerr << "�޷������ļ���" << filename << std::endl;
		return false;
	}
	return true;
}

//������ ����
void Weapon::equip()                        //װ��
{
	Item::equip();							//���û����װ������ 
}

void Weapon::unequip()                      //ж��
{
	Item::unequip();						//���û����ж�º��� 
}

void Weapon::upgrade()                      //����
{
	if (inBag && level <= 3)
	{
		level++;							//����
		attack += SIDE_UPGRADE_ATTACK;		//����ɱ����
	}
}

//װ���� ����
void Armor::equip()                         //װ��
{
	if (inBag && !isEquiped)
	{
		isEquiped = true;					//װ��
	}
}

void Armor::unequip()                       //ж��
{
	if (inBag && isEquiped)
	{
		isEquiped = false;					//ж��
	}
}

void Armor::upgrade()                       //����
{
	if (inBag && level <= 3)				//����ڱ����� �� �ȼ�С�ڵ���3
	{
		level++;							//����
		protect += SIDE_UPGRADE_PROTECT;	//���ӷ�����
	}
}

//ʳ���� ����
void Food::cook()                           //���
{
	if (inBag && !isCooked)
	{
		isCooked = true;					//���
		name = "Cooked " + name;			//���ָı�
		value = BASIC_VALUE * 8;			//��ֵ�ı�
	}
}

void Food::eat()                            //ʳ��
{
	if (inBag && num != 0)
	{
		num--;								//��������
		if (num == 0){}                     //����ʾͼ��
	}
}

//������
void GameMaterial::use()					//ʹ��
{
	if (inBag)	
	{
		num--;						  	    //��������
		if (num == 0) {}                    //����ʾͼ��
	}
}

//������Ʒ��
void TaskItem::Finish()                     //�������
{
	if (num == 5)							//�������Ϊ5
	{
											//�������
		num = 0;							//�������� 
		isFinished = true;					//��� 
	}
}


