#pragma once
#ifndef NPC_H
#define NPC_H

#include <string>
#include <string.h>
#include "elements.h"
#include "tasks.h"

#include "player.h"
#include "skills.h"
//�ѷ�
const std::string PRINCESS = "PRINCESS";									//����
const std::string KING = "KING";											//����
const std::string MINISTER = "MINISTER";									//��


// ���  ����ʯ�꣬�߲�ˮ���꣬������  �곤
const std::string FishStoreManager = "FishStoreManager";					//���
const std::string OreStoreManager = "OreStoreManager";						//��ʯ��
const std::string VegetableStoreManager = "VegetableStoreManager";			//�߲˵�
const std::string WeaponStoreManager = "WeaponStoreManager";				//������

 
//�з�

constexpr int ENEMY_ATTACK = 10;											//��ʼ��������
constexpr int ENEMY_HP = 50;												//��ʼ��Ѫ��
//NPC��
class NPC : public Sprite
{
public:
	NPC()noexcept {
		position = Vec2(0.0f, 0.0f);
	};//Ĭ�Ϲ��캯��
	NPC(const std::string name);//���ι��캯��
	virtual ~NPC() {};

	virtual const Vec2& getPosition() const { return this->position; };		//��ȡλ��

protected:
	Vec2 position;															//λ��
	std::string name;														//����
};

//�ѷ�NPC
class FriendNpc : public NPC
{
public:
	FriendNpc(const std::string name);										//���ι��캯��
	void GiveTask();														//��������
private:
	std::string name;														//����
	Task task;																//����
};

//�з�NPC
class EnemyNpc : public NPC
{
	friend class Player;
	friend class Elements;
	friend class Skill;
	friend class BattleSence;
public:
	EnemyNpc(ElementType element, int level, std::shared_ptr<Skill> skill, std::string filename);//���ι��캯�� 
	void TakeDamage(int damage);										//�ܵ��˺�
	void setPosition(Vec2 position);									//����λ�� 
	bool initWithFile();												//����ͼ��

	int getHp() { return hp; }											//��ȡѪ��
	int getAttack() { return attack; }									//��ȡ������	
	int getLevel() { return level; }									//��ȡ�ȼ�
	ElementType getElement() { return element; }						//��ȡԪ������
	std::shared_ptr<Skill> getSkill() { return skill; }					//��ȡ����
	std::string getFileName() { return filename; }						//��ȡ�ļ���
	const Vec2& EnemyNpc::getPosition() { return this->position; };		//�õ�λ��
	void dead() { isAlive = false; }									//����
private:
	//�趨
	std::string name;													//����
	ElementType element;												//Ԫ������
	int maxHp;															//���Ѫ��
	int hp;																//Ѫ��
	int basic_attack;													//����������
	int attack;															//������
	int level;															//�ȼ�
	std::string filename;												//�ļ���
	Vec2 position = Vec2(0.0f, 0.0f);									//λ��
	//״̬
	bool isAlive = true;												//��ʼ��Ϊ���״̬
	bool isMoving = false;												//��ʼ��Ϊ�����ƶ�״̬
	std::shared_ptr<Skill> skill;										//����	
};



#endif