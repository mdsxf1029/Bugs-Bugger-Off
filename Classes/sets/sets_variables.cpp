
#include<string>
#include<string.h>

#include"items.h"
#include"player.h"
#include"tasks.h"
#include"skills.h"
#include"npc.h"
#include"elements.h"
#include"inventory.h"

//ǰ������
class Player;																//���
class Task;																	//����		
class LowLevelSkill;														//�ͼ�����	
class MidLevelSkill;														//�м�����
class HighLevelSkill;														//�߼�����
class Weapon;																//����
class Armor;																//����
class Food;																	//ʳƷ
class GameMaterial;															//����
class TaskItem;																//������Ʒ
class FriendNpc;															//�ѷ�NPC
class EnemyNpc;																//�з�NPC
class Element;																//Ԫ��
class Inventory;															//����
enum ElementType;															//Ԫ������


//�����
std::string spritetry = "try.png";
Player hero(spritetry);													//���

//����

Task mainTask(MAIN_TASK, MAIN_TASK_DESCRIPTION);						//��������
Task sideTaskOne(SIDE_TASK_ONE, SIDE_TASK_ONE_DESCRIPTION);				//������1
Task sideTaskTwo(SIDE_TASK_TWO, SIDE_TASK_TWO_DESCRIPTION);				//������2	
Task sideTaskThree(SIDE_TASK_THREE, SIDE_TASK_THREE_DESCRIPTION);		//������3
Task sideTaskFour(SIDE_TASK_FOUR, SIDE_TASK_FOUR_DESCRIPTION);			//������4
Task sideTaskFive(SIDE_TASK_FIVE, SIDE_TASK_FIVE_DESCRIPTION);			//������5
Task sideTaskSix(SIDE_TASK_SIX, SIDE_TASK_SIX_DESCRIPTION);				//������6
Task sideTaskSeven(SIDE_TASK_SEVEN, SIDE_TASK_SEVEN_DESCRIPTION);		//������7
Task nonTask(NON_TASK, NON_TASK_DESCRIPTION);							//������

//����

LowLevelSkill elementSurge(ELEMENT_SURGE);								//Ԫ�س��
MidLevelSkill elementalTorrent(Elemental_Torrent);						//Ԫ�غ���
HighLevelSkill energyVortex(Energy_Vortex);								//��������
//��ϼ���
HighLevelSkill arcaneBlast(Arcane_Blast);								//��������


//NPC

//�ѷ�NPC
FriendNpc princess(PRINCESS);											//����
FriendNpc king(KING);													//����
FriendNpc minister(MINISTER);											//��

FriendNpc fishStoreManager(FishStoreManager);							//��װ��
FriendNpc weaponStoreManager(WeaponStoreManager);						//������
FriendNpc vegetableStoreManager(VegetableStoreManager);					//ʳƷ��
FriendNpc oreStoreManager(OreStoreManager);								//������



//�����������ڿ�����ô����
EnemyNpc highLevelFireMonster(ElementType::Fire, 2, elementalTorrent);		//�߼������
EnemyNpc lowLevelFireMonster(ElementType::Fire, 1, elementSurge);			//�ͼ������

EnemyNpc highLevelWaterMonster(ElementType::Water, 2, elementalTorrent);	//�߼�ˮ����
EnemyNpc lowLevelWaterMonster(ElementType::Water, 1, elementSurge);			//�ͼ�ˮ����

EnemyNpc highLevelWoodMonster(ElementType::Wood, 2, elementalTorrent);		//�߼�ľ����
EnemyNpc lowLevelWoodMonster(ElementType::Wood, 1, elementSurge);			//�ͼ�ľ����

EnemyNpc highLevelGoldMonster(ElementType::Gold, 2, elementalTorrent);		//�߼������
EnemyNpc lowLevelGoldMonster(ElementType::Gold, 1, elementSurge);			//�ͼ������

EnemyNpc highLevelEarthMonster(ElementType::Earth, 2, elementalTorrent);	//�߼�������
EnemyNpc lowLevelEarthMonster(ElementType::Earth, 1, elementSurge);			//�ͼ�������

ElementType playerElement = hero.getPlayerElement();
EnemyNpc BOSS(playerElement, 3, energyVortex);								//boss �����Ԫ����ͬ �ȼ�Ϊ3  //������˸��� ��������

//��Ʒ

//���� ����
Weapon  magicRing(MAGIC_RING);												//ħ��
Weapon  magicCrystal(MAGIC_CRYSTAL);										//ħ��		
Weapon  magicScroll(MAGIC_SCROLL);											//ħ��	

//���� ����
Armor helmet(HELMET);														//ͷ��
Armor armor(ARMOR);															//����	
Armor shoes(SHOES);															//Ь��

//ʳƷ ����
Food fish(FISH);															//��
Food fruit(FRUIT);															//ˮ��
Food vegetable(VEGETABLE);													//�߲�
Food herb(HERB);															//��ҩ
Food meat(MEAT);															//��
Food mushroom(MUSHROOM);													//Ģ��
Food rice(RICE);															//����
Food apple(APPLE);															//ƻ��



//���� ����
GameMaterial tree(TREE);													//��
GameMaterial woods(WOOD);													//ľͷ
GameMaterial stone(STONE);													//ʯͷ
GameMaterial goldMine(GOLD_MINE);											//���
GameMaterial chest(CHEST);													//����

//������Ʒ ����
TaskItem key(KEY);															//Կ��   //����Ҫ��������
TaskItem letter(LETTER);													//�ż�	//���ܵ�������Ʒ

//Ԫ�� ����
Element gold(ElementType::Gold);											//��
Element wood(ElementType::Wood);											//ľ					
Element water(ElementType::Water);											//ˮ	
Element fire(ElementType::Fire);											//��			
Element earth(ElementType::Earth);											//��			

//����
Inventory bag;																//����
