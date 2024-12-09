#pragma once
#ifndef NPC_H
#define NPC_H

#include <string>
#include <string.h>
#include "elements.h"
#include "inventory.h"
#include "tasks.h"
#include "sets_variables.h"
#include "player.h"
#include "skills.h"
//�ѷ�
const std::string PRINCESS = "PRINCESS";								//����
const std::string KING = "KING";										//����
const std::string MINISTER = "MINISTER";								//��
         

// ���  ����ʯ�꣬�߲�ˮ���꣬������  �곤
const std::string FishStoreManager = "FishStoreManager";				//���
const std::string OreStoreManager = "OreStoreManager";					//��ʯ��
const std::string VegetableStoreManager = "VegetableStoreManager";		//�߲˵�
const std::string WeaponStoreManager = "WeaponStoreManager";			//������


//`FishStoreManager` `WeaponStoreManager ` `VegetableStoreManager ` `OreStoreManager`

//�з�

const int ENEMY_ATTACK = 10;											//��ʼ��������
const int ENEMY_HP = 25;												//��ʼ��������
//NPC��
class NPC : public Sprite
{
public:
	NPC()noexcept {
		position = Vec2(0, 0);
	};//Ĭ�Ϲ��캯��
	NPC(const std::string name);//���ι��캯��
	virtual ~NPC() {};
	//virtual void setPosition(Vec2 position) { this->position = position; };//����λ��

	//��ȡλ��
	virtual const Vec2& getPosition() const { return this->position; };

protected:
	Vec2 position;//λ��
private:
	std::string name;

};

//�ѷ�NPC
class FriendNpc : public NPC
{
public:
	FriendNpc(const std::string name);

	void GiveTask();//������

private:
	std::string name;
	Task task;
};

//�з�NPC
class EnemyNpc : public NPC
{
	friend class Player;
	friend class Elements;
	friend class Skill;
	friend class LowLevelSkill;
	friend class MidLevelSkill;
	friend class HighLevelSkill;
	friend class BattleSence;
public:
	friend class Player;
	friend class Elements;
	EnemyNpc(ElementType element, int level, LowLevelSkill& skill);//���ι��캯��
	EnemyNpc(ElementType element, int level, MidLevelSkill& skill);//���ι��캯��
	EnemyNpc(ElementType element, int level, HighLevelSkill& skill);//���ι��캯��


	//�ܵ��˺�
	void TakeDamage(int damage);

	//��
	void Frenzy();

	//�������
	void AttackPlayer(Player& player)
	{
		//������
	}
	void Move();

private:
	std::string name;
	ElementType element;
	int maxHp;
	int hp;
	int basic_attack;
	int attack;
	int level;
	bool isAlive;
	bool isFrenzy = false;//��ʼ��Ϊ�ǿ�״̬
	bool isMoving = false;//��ʼ��Ϊ�����ƶ�״̬
	Skill* skill;
};



#endif