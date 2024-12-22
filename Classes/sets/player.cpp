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


//���캯�� ��ʼ������ Ԫ������ �ȼ�Ѫ���������ȵ�
Player::Player() : level(0), hp(PLAYRT_BASE_HP), attack(PLAYRR_BASE_ATTACK), isAlive(true)
{
	state = PlayerState::NORMAL;												//��ʼ��״̬
	name = "hero";																//��ʼ������
	int elemnt = 1;															    //��ʼ��Ԫ������  ��ʼ����ʱ��ͨ��ѡ��Ԫ������
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

	//��ʼ��
	my_armor = nullptr;																				//����
	my_helmet = nullptr;																			//ͷ��
	my_shoes = nullptr;																				//Ь��
	weapon = nullptr;																				//����
	position = Vec2(0, 0);																			//��ʼλ�� 
} 
//����
void Player::Upgrade()																				//����
{
	level++;																						//�ȼ���1
	max_hp += PLAYER_UPGRADE_HP;																	//Ѫ������
	hp = max_hp;																					//Ѫ���ظ���
	basic_attack += PLAYER_UPGRADE_ATTACK;															//����������
}
//����
void Player::TakeDamage(int damage)																	//����ܵ��˺�											
{
	if ((hp - damage) > 0)
	{
		hp -= damage;																				//Ѫ������
	}
	else
	{
		hp = 0;																						//Ѫ��Ϊ0
		isAlive = false;																			//�������								
	}
}
//����
void Player::Heal(int heal_hp)																		//�������							
{
	if(hp>0&&hp<max_hp)																				//���Ѫ�����㣬������0
		hp += heal_hp;																				//Ѫ������
	if (hp > max_hp)																				//���Ѫ���������Ѫ��
		hp = max_hp;																				//Ѫ���ظ���
}
//��ȡ��ҵĵ�ǰѪ��
int Player::getHp() const																			//��ȡ��ҵĵ�ǰѪ��
{
	return this->hp;
}
//��ȡ��ҵĹ�����
int Player::getAttack() const																		// ��ȡ��ҵĹ�����
{
	return this->attack;
}

std::string Player::GetName() const {return this->name;}											// ��ȡ��ҵ�����		
int Player::getMaxHp() const {return max_hp; }														// ��ȡ��ҵ����Ѫ��
int Player::getSpeed() const {return SPEED; }														// ��ȡ��ҵ��ƶ��ٶ�
int Player::GetLevel() const {return this->level;}													// ��ȡ��ҵĵȼ�


Vec2 Player::Move(EventKeyboard::KeyCode keyCode)													// ����ƶ�
{
	Vec2 next_position = position;																	// ��һ��λ��					
	CCLOG("position:%f %f", position.x, position.y);
	if (isMoving)																					//��������ƶ�
	{																								//��ȡ��һ��λ��
		switch (keyCode)
		{
			case EventKeyboard::KeyCode::KEY_UP_ARROW:
				next_position.y += SPEED * Director::getInstance()->getDeltaTime();
				isMoving = false;
				break;
			case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
				next_position.y -= SPEED * Director::getInstance()->getDeltaTime();
				isMoving = false;
				break;
			case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
				next_position.x -= SPEED * Director::getInstance()->getDeltaTime();
				isMoving = false;
				break;
			case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
				next_position.x += SPEED * Director::getInstance()->getDeltaTime();
				isMoving = false;
				break;
			default:
				break;
		}
	}
	CCLOG("next_position:%f %f", next_position.x, next_position.y);
	return next_position;																			//������һ��λ��
}

//�趨����
void Player::setPosition(const Vec2& newPosition) {
	position = newPosition;																			// ���������Ա
}

//ͼ��
bool Player::initWithFile(const std::string& filename)												//��ʼ��ͼ���ļ�							
{
	if (!Sprite::initWithFile(filename)) {
		;
		return false;
	}
	return true;
}
 