#pragma once
#ifndef SET_VARIABLES_H
#define SET_VARIABLES_H

#include<string>
#include<string.h>

#include"items.h"
#include"player.h"
#include"tasks.h"
#include"skills.h"
#include"npc.h"
#include"elements.h"
#include"inventory.h"


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

//���� ����
extern Material tree;
extern Material stone;

//������Ʒ ����
extern TaskItem key;
extern TaskItem letter;
 

//����
extern Inventory bag;//����

#endif // !SET_VARIABLES_H
