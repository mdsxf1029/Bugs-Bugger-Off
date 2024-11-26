//creator: �뿡�� 2353924
//description: ������ʵ��
#include <string>
#include <string.h>

#include "elements.h"
# include "player.h"
/*
* class player �ĺ��ι��캯��
* player ������Ϸ�е���ҽ�ɫ��   ����ʵ���� ���� �趨Ϊ hero �������г�Ա ��ɴ���
* names ������� element ���Ԫ������ 1�� 2ľ 3ˮ 4�� 5��
* level ��ʼ��Ϊ0 hp��ʼ��Ϊ50 attack��ʼ��Ϊ10
*/

//���캯�� ��ʼ������ Ԫ������ �ȼ�Ѫ���������ȵ�
player::player(string& names, int element) :name(names), level(0), hp(50), attrack(10)
{
	switch (elemnt)
	{
		case 1:
			player_element = ElementType::Gold;
			break;
		case 2:
			player_element = ElementType::Wood;
			break;
		case 3:
			player_element = ElementType::Water;
			break;
		case 4:
			player_element = ElementType::Fire;
			break;
		case 5:
			player_element = ElementType::Earth;
			break;
		default:
			player_element = ElementType::Gold;
			break;
	}
}
/*
* name:upgrade 
* level ++�� hp+25�� attack+5
*/
void player::upgrade()
{
	level++;//�ȼ���1
	hp += UPGRADE_HP;//Ѫ������
	basic_attack += UPGRADE_ATTACK;//����������
}


// ��ҹ�������
void player::attackEnemy(Player& enemy)
{//��������
	enemy.takeDamage(attack);
}

// ����ܵ��˺�
void player::takeDamage(int damage)
{
	hp -= damage;
}

// �������  
// heal_hp ���Ƶ�Ѫ��
void player::heal(int heal_hp)
{
	hp += heal_hp;
}

// ��ȡ��ҵĵ�ǰѪ��
int player::getHp() const
{
	return this->hp;
}

// ��ȡ��ҵ�����
std::string player::getName() const 
{
	return this-> name;
}