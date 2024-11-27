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
Player::Player(std::string& names, int element) :name(names), level(0), hp(50), attrack(10)
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
void Player::Upgrade()
{
	level++;//�ȼ���1
	max_hp += UPGRADE_HP;//Ѫ������
	hp = max_hp;//Ѫ���ظ���
	basic_attack += UPGRADE_ATTACK;//����������
}


// ��ҹ�������
void Player::AttackEnemy(Player& enemy)
{//��������
	enemy.takeDamage(attack);
}

// ����ܵ��˺�
void Player::TakeDamage(int damage)
{
	if ((hp - damage) > 0)
	{
		hp -= damage;
	}
	else
	{
		hp = 0;
		//�������
	//��Ϸ���� ���� ������һ���浵�� �����˳�ս������
	}
}

// �������  
// heal_hp ���Ƶ�Ѫ��
void Player::Heal(int heal_hp)
{
	if ((hp + heal_hp)<=max_hp)
	{
		hp += heal_hp;
	}
	else
	{
		hp = max_hp;
	}
}


// ��ȡ��ҵĵ�ǰѪ��
int Player::GetHp() const
{
	return this->hp;
}

// ��ȡ��ҵ�����
std::string Player::GetName() const
{
	return this->name;
}

// ��ȡ��ҵĵȼ�
int Player::GetLevel() const
{
	return this->level;
}

// �ƶ� ��Ҫ����
void Player::Move()
{
	//����
}