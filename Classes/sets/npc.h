#pragma once
#ifndef NPC_H
#define NPC_H

#include <string>
#include <string.h>
#include "elements.h"
#include "inventory.h"
 
//�ѷ�
const string PRINCESS = "PRINCESS";//����
const string KING = "KING";//����
const string MINISTER = "MINISTER";//��

const string ClothesProvider = "ClothesProvider";//��װ��
const string WeaponProvider = "WeaponProvider";//������
const string FoodProvider = "FoodProvider";//ʳƷ��
const string SkillProvider = "SkillProvider";//������

//`ClothesProvider` `WeaponProvider ` `FoodProvider ` `SkillProvider`

//�з�
const stirng HIGH_LEVEL_MONSTER = "HIGH_LEVEL_MONSTER";
const stirng LOW_LEVEL_MONSTER = "LOW_LEVEL_MONSTER";
const int ATTACK = 10;//��ʼ��������
const int HP = 25;//��ʼ��������
//NPC��
class NPC
{
public:
	NPC(const string& name) :name{ name } {};
	virtual ~NPC() {};

protected:

private:
	string name;
};

//�ѷ�NPC
class FriendNpc : public NPC
{
public:
	FriendNpc(const string& name) :name{ name } {};
	~FriendNpc() {};
	void GiveTask() {};//������

protected:

private:
	string name;

};

//�з�NPC
class EnemyNpc : public NPC
{
public:
	EnemyNpc(ElemntType & element,int level ) :element(element),level(level)
	{
		hp = HP*level;
		basic_attack = ATTACK * level;
		attack = basic_attack;
	};
	void Attack() 
	{
		//����
	};//����
	~EnemyNpc() {};
protected:

private:
	string name;
	ElementType element;
	int hp;
	int basic_attack;
	int attack;
	int level;

};

//�ѷ�NPC
FriendNpc princess(PRINCESS);//����
FriendNpc king(KING);//����
FriendNpc minister(MINISTER);//��

FriendNpc clothesProvider(ClothesProvider);//��װ��
FriendNpc weaponProvider(WeaponProvider);//������
FriendNpc foodProvider(FoodProvider);//ʳƷ��
FriendNpc skillProvider(SkillProvider);//������


//�����������ڿ�����ô����
EnemyNpc highLevelFireMonster(ElementType::Fire, 2);//�߼������
EnemyNpc lowLevelFireMonster(ElementType::Fire, 1);//�ͼ������

EnemyNpc highLevelWaterMonster(ElementType::Water, 2);//�߼�ˮ����
EnemyNpc lowLevelWaterMonster(ElementType::Water, 1);//�ͼ�ˮ����

EnemyNpc highLevelWoodMonster(ElementType::Wood, 2);//�߼�ľ����
EnemyNpc lowLevelWoodMonster(ElementType::Wood, 1);//�ͼ�ľ����

EnemyNpc highLevelGoldMonster(ElementType::Gold, 2);//�߼������
EnemyNpc lowLevelGoldMonster(ElementType::Gold, 1);//�ͼ������

EnemyNpc highLevelEarthMonster(ElementType::Earth, 2);//�߼�������
EnemyNpc lowLevelEarthMonster(ElementType::Earth, 1);//�ͼ�������


#endif