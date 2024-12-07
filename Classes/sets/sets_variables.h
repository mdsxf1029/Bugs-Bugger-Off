#pragma once
#ifndef SET_VARIABLES_H
#define SET_VARIABLES_H

#include<string>
#include<string.h>

#include "player.h"

//ǰ������
class Player;
class Task;
class LowLevelSkill;
class MidLevelSkill;
class HighLevelSkill;
class Weapon;
class Armor;
class Food;
class GameMaterial;
class TaskItem;
class FriendNpc;
class EnemyNpc;
	

//����� 
extern Player hero;

//����

extern Task mainTask;//��������
extern Task sideTaskOne;//������1
extern Task sideTaskTwo;//������2	
extern Task sideTaskThree;//������3
extern Task sideTaskFour;//������4
extern Task sideTaskFive;//������5
extern Task sideTaskSix;//������6
extern Task sideTaskSeven;//������7
extern Task nonTask;//������

//����

extern LowLevelSkill elementSurge;//Ԫ�س��
extern MidLevelSkill elementalTorrent;//Ԫ�غ���
extern HighLevelSkill energyVortex;//��������
//��ϼ���
extern HighLevelSkill arcaneBlast;//��������


//NPC

//�ѷ�NPC
extern FriendNpc princess;//����
extern FriendNpc king;//����
extern FriendNpc minister;//��

extern FriendNpc clothesProvider;//��װ��
extern FriendNpc weaponProvider;//������
extern FriendNpc foodProvider;//ʳƷ��
extern FriendNpc skillProvider;//������


//�����������ڿ�����ô����
extern EnemyNpc highLevelFireMonster;//�߼������
extern EnemyNpc lowLevelFireMonster;//�ͼ������

extern EnemyNpc highLevelWaterMonster;//�߼�ˮ����
extern EnemyNpc lowLevelWaterMonster;//�ͼ�ˮ����

extern EnemyNpc highLevelWoodMonster;//�߼�ľ����
extern EnemyNpc lowLevelWoodMonster;//�ͼ�ľ����

extern EnemyNpc highLevelGoldMonster;//�߼������
extern EnemyNpc lowLevelGoldMonster;//�ͼ������

extern EnemyNpc highLevelEarthMonster;//�߼�������
extern EnemyNpc lowLevelEarthMonster;//�ͼ�������

extern EnemyNpc BOSS;//�߼�����
//��Ʒ

//���� ����
extern Weapon  magicRing;
extern Weapon  magicCrystal;
extern Weapon  magicScroll;

//���� ����
extern Armor helmet;
extern Armor armor;
extern Armor shoes;

//ʳƷ ����
extern Food fish;
extern Food fruit;
extern Food vegetable;
extern Food herb;
extern Food meat;
extern Food mushroom;
//���� ����
extern GameMaterial tree;
extern GameMaterial stone;

//������Ʒ ����
extern TaskItem key;
extern TaskItem letter;


#endif // !SET_VARIABLES_H
