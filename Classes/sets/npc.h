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
const std::string PRINCESS = "PRINCESS";//����
const std::string KING = "KING";//����
const std::string MINISTER = "MINISTER";//��

const std::string ClothesProvider = "ClothesProvider";//��װ��
const std::string WeaponProvider = "WeaponProvider";//������
const std::string FoodProvider = "FoodProvider";//ʳƷ��
const std::string SkillProvider = "SkillProvider";//������

//`ClothesProvider` `WeaponProvider ` `FoodProvider ` `SkillProvider`

//�з�
const std::string HIGH_LEVEL_MONSTER = "HIGH_LEVEL_MONSTER";
const std::string LOW_LEVEL_MONSTER = "LOW_LEVEL_MONSTER";
const int ENEMY_ATTACK = 10;//��ʼ��������
const int ENEMY_HP = 25;//��ʼ��������
//NPC��
class NPC
{
public:
	NPC()noexcept {};//Ĭ�Ϲ��캯��
	NPC(const std::string name);//���ι��캯��
	virtual ~NPC() {}; 
protected:

private:
	std::string name;
};

//�ѷ�NPC
class FriendNpc : public NPC
{
public:
	FriendNpc(const std::string name);
	 
	void GiveTask()  ;//������

protected:

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

public:
	friend class Player;
	friend class Elements;
	EnemyNpc(ElementType element, int level, LowLevelSkill& skill);//���ι��캯��
	EnemyNpc(ElementType element, int level, MidLevelSkill& skill);//���ι��캯��
	EnemyNpc(ElementType element, int level, HighLevelSkill& skill);//���ι��캯��
	void Attack() 
	{
		//������
		//����
	};//����

	//�ܵ��˺�
	void TakeDamage(int damage);
	
	//��
	void Frenzy();
protected:

private:
	std::string name;
	ElementType element;
	int maxHp;
	int hp;
	int basic_attack;
	int attack;
	int level;
	bool isAlive;
	Skill * skill;
};



#endif