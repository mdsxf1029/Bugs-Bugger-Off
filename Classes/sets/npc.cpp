#include "npc.h"
//���� NPC��

//���캯�� ��������
NPC::NPC(const std::string& name) : name(name) {};
//��������
NPC::~NPC() {};

//����
//�ѷ�NPC
//���캯�� ����task
FriendNpc::FriendNpc(){
	switch (name)
	{
		case King:
			task = mainTask; //������
			break; 
		//����Ϊ������
		//���Ը���Ϊ�������� �����趨
		case ClothesProvider:
			task = sideTaskThree;
			break;
		case WeaponProvider:
			task = sideTaskFour;
			break;
		case FoodProvider:
			task = sideTaskFive;
			break;
		case SkillProvider:
			task = sideTaskSix;
			break;
		default:
			task = nontask;
			break;
	}
}

void FriendNpc::GiveTask()
{
	//������
//��������ʲô�ġ���
}


//�з�NPC   
//���캯�� ����Ԫ�����ͺ͵ȼ�
EnemyNpc::EnemyNpc(ElemntType& element, int level) : element(element), level(level)
{
	hp = HP * level;
	basic_attack = ATTACK * level;
	attack = basic_attack;
}