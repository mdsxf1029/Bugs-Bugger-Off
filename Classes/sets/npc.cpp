
#include "tasks.h" 
#include"skills.h"
#include "npc.h"
#include "Sets/manager.h"

//ǰ������
class Skill;

//���� NPC��
//���캯�� ��������
NPC::NPC(const std::string name) : name(name) {} 

//����
//�ѷ�NPC
//���캯��
FriendNpc::FriendNpc(const std::string name) : name(name)
{

}

void FriendNpc::GiveTask()
{

}

//�з�NPC   
//���캯�� ����Ԫ�����ͺ͵ȼ� 
EnemyNpc::EnemyNpc(ElementType element, int level, std::shared_ptr<Skill>skill, std::string afilename) :
	element(element), level(level), isAlive(true), skill(skill), filename(afilename)
{
	hp = ENEMY_HP * level;														//��ʼ��Ѫ��
	maxHp = hp;																	//���Ѫ��
	basic_attack = ENEMY_ATTACK * level;										//��ʼ��������
	attack = basic_attack + skill->getInfo().attack;							//������
};

void EnemyNpc::TakeDamage(int damage)											//�����ܵ��˺�
{
	if ((hp - damage) > 0)														//���Ѫ��-�˺�����0
	{
		hp -= damage;															//������Ѫ
	}
	else																		//���� hp=0
	{
		hp = 0;
		isAlive = false;														//����
	}
}
  


void EnemyNpc::setPosition(Vec2 position)							//����λ��
{
	this->position = position;
	Sprite::setPosition(position);
};


bool EnemyNpc::initWithFile()                                         //����ͼ��
{
	if (!Sprite::initWithFile(filename)) {
		std::cerr << "�޷������ļ���" << filename << std::endl;
		return false;
	}
	return true;
}
