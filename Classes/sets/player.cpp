//creator: �뿡�� 2353924
//description: ������ʵ��
#include <string>
#include <string.h>

#include "elements.h"
# include "player.h"

#include "items.h"
/*
* class player �ĺ��ι��캯��
* player ������Ϸ�е���ҽ�ɫ��   ����ʵ���� ���� �趨Ϊ hero �������г�Ա ��ɴ���
* names ������� element ���Ԫ������ 1�� 2ľ 3ˮ 4�� 5��
* level ��ʼ��Ϊ0 hp��ʼ��Ϊ50 attack��ʼ��Ϊ10
*/

constexpr int PLAYRT_BASE_HP = 50;//��ҳ�ʼѪ��
constexpr int PLAYER_UPGRADE_HP = 25;//�������ӵ�Ѫ��
constexpr int PLAYRR_BASE_ATTACK = 10;//��ҳ�ʼ������
constexpr int PLAYER_UPGRADE_ATTACK = 5;//�������ӵĹ�����
constexpr int SPEED = 200;//�ƶ��ٶ�

//���캯�� ��ʼ������ Ԫ������ �ȼ�Ѫ���������ȵ�
Player::Player() : level(0), hp(PLAYRT_BASE_HP), attack(PLAYRR_BASE_ATTACK), isAlive(true)
{
	state = PlayerState::NORMAL;

	std::cout << "Ϊ���Ӣ����һ�����ְɣ�";
	std::cin >> name;
	 
	int elemnt = 0;
	// 1�� 2ľ 3ˮ 4�� 5��
	//����ͨ������ѡ��Ԫ������
	std::cin >> elemnt;//��������cin����

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

	//��ʼʱ װ��
	my_armor = nullptr;//����
	my_helmet = nullptr;//ͷ��
	my_shoes = nullptr;//Ь��
	//��ʼʱ ����
	weapon = nullptr;//����Ϊ��

	position = Vec2(0, 0);//��ʼλ��
	//��ʼ������
	bag = Inventory();
}
/*
* name:upgrade
* level ++�� hp+25�� attack+5
*/
void Player::Upgrade()
{
	level++;//�ȼ���1
	max_hp += PLAYER_UPGRADE_HP;//Ѫ������
	hp = max_hp;//Ѫ���ظ���
	basic_attack += PLAYER_UPGRADE_ATTACK;//����������
}


// ��ҹ�������
void Player::AttackEnemy(EnemyNpc& enemy, EventKeyboard::KeyCode KEY)
{//��������
	switch (KEY)
	{
		case EventKeyboard::KeyCode::KEY_0:
		//	Attack(enemy, elementSurge);
			break;
		case EventKeyboard::KeyCode::KEY_1:
			//����
	//		Attack(enemy, elementalTorrent);
			break;
		case EventKeyboard::KeyCode::KEY_2:
			//����
		//	Attack(enemy, energyVortex);
			break;
		default:
			break;
	}
	int damage = attack;
	if (damage > 0) {
		enemy.hp -= damage;
		// ��ʾ����Ч��
	}

	enemy.TakeDamage(attack);
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
		isAlive = false;
		//�������
//�˳�ս������
	//��Ϸ���� ���� ������һ���浵�� �����˳�ս������
	}
}

// �������  
// heal_hp ���Ƶ�Ѫ��
void Player::Heal(int heal_hp)
{
	if ((hp + heal_hp) <= max_hp)
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
Vec2 Player::Move(EventKeyboard::KeyCode keyCode)
{
	Vec2 next_position = position;
	if (isMoving)//��������ƶ�
	{
		switch (keyCode)
		{
			case EventKeyboard::KeyCode::KEY_UP_ARROW:
				next_position.y += SPEED * Director::getInstance()->getDeltaTime()*level;
				break;
			case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
				next_position.y -= SPEED * Director::getInstance()->getDeltaTime() * level;
				break;
			case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
				next_position.x -= SPEED * Director::getInstance()->getDeltaTime() * level;
				break;
			case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
				next_position.x += SPEED * Director::getInstance()->getDeltaTime() * level;
				break;
			default:
				break;
		}
	}
	return next_position;
}
//�趨����
void Player::setPosition(const Vec2& newPosition){
	position = newPosition;                 //��������洢
	Node::setPosition(position);            //���µ�ͼ����ʾ������
}
//ͼ��

bool Player::initWithFile(const std::string& filename)
{
	if (!Sprite::initWithFile(filename)) {
		std::cerr << "�޷������ļ���" << filename << std::endl;
		return false;
	}
	return true;
}
