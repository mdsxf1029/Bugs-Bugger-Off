
#include "tasks.h" 
#include"skills.h"
#include "npc.h"
#include<manager/manager.h>
//ǰ������
class Skill;
class LowLevelSkill;
class MidLevelSkill;
class HighLevelSkill;

//���� NPC��
//���캯�� ��������
NPC::NPC(const std::string name) : name(name)
{
}

//����
//�ѷ�NPC
//���캯�� ����task
FriendNpc::FriendNpc(const std::string name) : name(name)
{
	/*
	if (name == "KING")
		task = mainTask; //������
	//����Ϊ������
	//���Ը���Ϊ�������� �����趨
	else if (name == "FishStoreManager")						//���
		task = sideTaskThree;
	else if (name == "WeaponStoreManager")						//������
		task = sideTaskFour;
	else if (name == "VegetableStoreManager")					//�߲˵�
		task = sideTaskFive;
	else if (name == "OreStoreManager")							//��ʯ��
		task = sideTaskSix;
	else
		task = nonTask;
	*/
}

void FriendNpc::GiveTask()
{
	//������
//��������ʲô�ġ���
}


//�з�NPC   
//���캯�� ����Ԫ�����ͺ͵ȼ�
 
EnemyNpc::EnemyNpc(ElementType element, int level, std::shared_ptr<LowLevelSkill>skill) : element(element), level(level), isAlive(true), skill(skill)
{
	hp = ENEMY_HP * level;
	maxHp = hp;
	basic_attack = ENEMY_ATTACK * level;
	attack = basic_attack + skill->attack;
};

EnemyNpc::EnemyNpc(ElementType element, int level, std::shared_ptr<MidLevelSkill> skill) : element(element), level(level), isAlive(true), skill(skill)
{
	hp = ENEMY_HP * level;
	maxHp = hp;
	basic_attack = ENEMY_ATTACK * level;
	attack = basic_attack + skill->attack;
};


EnemyNpc::EnemyNpc(ElementType element, int level, std::shared_ptr<HighLevelSkill> skill) : element(element), level(level), isAlive(true), skill(skill)
{
	hp = ENEMY_HP * level;
	maxHp = hp;
	basic_attack = ENEMY_ATTACK * level;
	attack = basic_attack + skill->attack;
};

//�����ܵ��˺�
void EnemyNpc::TakeDamage(int damage)
{
	if ((hp - damage) > 0)
	{
		hp -= damage;
	}
	else
	{
		hp = 0;
		isAlive = false;
	}
}

//���˰�Ѫ ��
void EnemyNpc::Frenzy()
{
	if (hp <= maxHp * 0.5)
	{
		attack += 10;
	}
};//��

//�����ƶ�
void EnemyNpc::Move()
{
	//�ƶ�
}

const Vec2& EnemyNpc::getPosition() const { return this->position; };
const void EnemyNpc::setPosition(Vec2 position)
{
	this->position = position;
	Sprite::setPosition(position);
};