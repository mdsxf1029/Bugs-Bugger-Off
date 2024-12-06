#include "npc.h"
#include "tasks.h"
#include"sets_variables.h"
#include"skills.h"
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
	if (name == "KING")
		task = mainTask; //������
	//����Ϊ������
	//���Ը���Ϊ�������� �����趨
	else if (name == "ClothesProvider")
		task = sideTaskThree;
	else if (name == "WeaponProvider")
		task = sideTaskFour;
	else if (name == "FoodProvider")
		task = sideTaskFive;
	else if (name == "SkillProvider")
		task = sideTaskSix;
	else
		task = nonTask;


}

void FriendNpc::GiveTask()
{
	//������
//��������ʲô�ġ���
}


//�з�NPC   
//���캯�� ����Ԫ�����ͺ͵ȼ�
EnemyNpc::EnemyNpc(ElementType element, int level, LowLevelSkill& skill) : element(element), level(level), isAlive(true), skill(&skill)
{
	hp = ENEMY_HP * level;
	maxHp = hp;
	basic_attack = ENEMY_ATTACK * level;
	attack = basic_attack + skill.attack;
};

EnemyNpc::EnemyNpc(ElementType element, int level, MidLevelSkill& skill) : element(element), level(level), isAlive(true), skill(&skill)
{
	hp = ENEMY_HP * level;
	maxHp = hp;
	basic_attack = ENEMY_ATTACK * level;
	attack = basic_attack + skill.attack;
};


EnemyNpc::EnemyNpc(ElementType element, int level, HighLevelSkill& skill) : element(element), level(level), isAlive(true), skill(&skill)
{
	hp = ENEMY_HP * level;
	maxHp = hp;
	basic_attack = ENEMY_ATTACK * level;
	attack = basic_attack + skill.attack;
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