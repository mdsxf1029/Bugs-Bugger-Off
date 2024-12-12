#ifndef GLOBAL_MANAGER_H
#define GLOBAL_MANAGER_H

#include <string>
#include <vector>

#include "sets/Player.h"
#include "sets/NPC.h"
#include "sets/tasks.h"
#include "sets/Skills.h"
#include "sets/Items.h"
#include "sets/Elements.h"
#include "sets/Inventory.h"

// ǰ������
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
class Element;
class Inventory;

// ȫ�ֹ�����
class GlobalManager {
private:
	std::shared_ptr<Player> _hero;                                                                                  // ���
	std::vector <std::shared_ptr< Task >> _tasks;   														            // ����                                    
	
	std::vector <std::shared_ptr< LowLevelSkill >> _lowLevelSkills; 									    			// �ͼ�����         
	std::vector<std::shared_ptr<MidLevelSkill>> _midLevelSkills; 									    			// �м�����                             
	std::vector<std::shared_ptr<HighLevelSkill>> _highLevelSkills;   							        			// �߼�����                     
	
	std::vector<std::shared_ptr<FriendNpc>> _friendNpcs; 									    					// �ѷ�NPC                                
	
	std::vector<std::shared_ptr<EnemyNpc>> _enemyNpcsGold;   							    		        			// �з�NPC -- ��
	std::vector<std::shared_ptr<EnemyNpc>> _enemyNpcsWood;   							    		        			// �з�NPC -- ľ
	std::vector<std::shared_ptr<EnemyNpc>> _enemyNpcsWater;   							    		        			// �з�NPC -- ˮ
	std::vector<std::shared_ptr<EnemyNpc>> _enemyNpcsFire;   							    		        			// �з�NPC -- ��
	std::vector<std::shared_ptr<EnemyNpc>> _enemyNpcsEarth;   							    		        			// �з�NPC -- ��
	std::shared_ptr<EnemyNpc> _enemyNpcsBoss;   							    		        					// boss
	std::vector<std::shared_ptr<Weapon>> _weapons;   							    		            			// ����   
	std::vector<std::shared_ptr<Armor>> _armors;   							    		                			// ����   
	std::vector<std::shared_ptr<Food>> _foods;       			    		                            			// ʳƷ   
	std::vector<std::shared_ptr<GameMaterial>> _materials;   							    		            	// ����           
	std::vector<std::shared_ptr<TaskItem>> _taskItems;   							    		                	// ������Ʒ 
	std::vector<std::shared_ptr<Element>> _elements;   							    		                	    // Ԫ��
	std::shared_ptr<Inventory> _bag;   							    		                	                    // ����               

	// ���캯��
    GlobalManager() {
		initialize();                                                                               // ��ʼ��
    }

	void initialize();//��ʼ��

public:

	// ��ȡȫ�ֹ�����ʵ��
    static GlobalManager& getInstance() {
        static GlobalManager instance;
        return instance;
    }

	// ��ȡ��Ա����  
	std::shared_ptr<Player> getPlayer() const { return _hero; }																	// ��ȡ���
	const std::vector<std::shared_ptr<Task>>& getTasks() const { return _tasks; }												// ��ȡ����
	const std::vector<std::shared_ptr<LowLevelSkill>>& getLowLevelSkills() const { return _lowLevelSkills; }					// ��ȡ�ͼ�����
	const std::vector<std::shared_ptr<MidLevelSkill>>& getMidLevelSkills() const { return _midLevelSkills; }					// ��ȡ�м�����
	const std::vector<std::shared_ptr<HighLevelSkill>>& getHighLevelSkills() const { return _highLevelSkills; }					// ��ȡ�߼�����
	const std::vector<std::shared_ptr<FriendNpc>>& getFriendNpcs() const { return _friendNpcs; }								// ��ȡ�ѷ�NPC
	const std::vector<std::shared_ptr<EnemyNpc>>& getEnemyNpcsGold() const { return _enemyNpcsGold; }							// ��ȡ�з�NPC -- ��
	const std::vector<std::shared_ptr<EnemyNpc>>& getEnemyNpcsWood() const { return _enemyNpcsWood; }							// ��ȡ�з�NPC -- ľ
	const std::vector<std::shared_ptr<EnemyNpc>>& getEnemyNpcsWater() const { return _enemyNpcsWater; }							// ��ȡ�з�NPC -- ˮ
	const std::vector<std::shared_ptr<EnemyNpc>>& getEnemyNpcsFire() const { return _enemyNpcsFire; }							// ��ȡ�з�NPC -- ��
	const std::vector<std::shared_ptr<EnemyNpc>>& getEnemyNpcsEarth() const { return _enemyNpcsEarth; }							// ��ȡ�з�NPC -- ��
	const std::vector<std::shared_ptr<Weapon>>& getWeapons() const { return _weapons; }											// ��ȡ����
	const std::vector<std::shared_ptr<Armor>>& getArmors() const { return _armors; }											// ��ȡ����
	const std::vector<std::shared_ptr<Food>>& getFoods() const { return _foods; }												// ��ȡʳƷ
	const std::vector<std::shared_ptr<GameMaterial>>& getMaterials() const { return _materials; }								// ��ȡ����
	const std::vector<std::shared_ptr<TaskItem>>& getTaskItems() const { return _taskItems; }									// ��ȡ������Ʒ
	const std::vector<std::shared_ptr<Element>>& getElements() const { return _elements; }										// ��ȡԪ��
	std::shared_ptr<Inventory> getInventory() const { return _bag; }
	// ��ȡ����

    // ��ֹ��������͸�ֵ
  //  GlobalManager(const GlobalManager&) = delete;                                                       
   // GlobalManager& operator=(const GlobalManager&) = delete;

    // ��������
    ~GlobalManager() {
		
    }
};

// ��ʼ��
void GlobalManager::initialize() {
	// ��ʼ��Ԫ�� 
	_elements.emplace_back(std::make_shared<Element>(ElementType::Gold));				// ��
	_elements.emplace_back(std::make_shared<Element>(ElementType::Wood));				// ľ
	_elements.emplace_back(std::make_shared<Element>(ElementType::Water));				// ˮ
	_elements.emplace_back(std::make_shared<Element>(ElementType::Fire));				// ��
	_elements.emplace_back(std::make_shared<Element>(ElementType::Earth));				// ��


	// ��ʼ�����
	_hero = std::make_shared<Player>("try.png");										// ���

	// ��ʼ������ 
	_tasks.emplace_back(std::make_shared<Task>(MAIN_TASK, MAIN_TASK_DESCRIPTION));					// ��������
	_tasks.emplace_back(std::make_shared<Task>(SIDE_TASK_ONE, SIDE_TASK_ONE_DESCRIPTION));			// ������1
	_tasks.emplace_back(std::make_shared<Task>(SIDE_TASK_TWO, SIDE_TASK_TWO_DESCRIPTION));			// ������2
	_tasks.emplace_back(std::make_shared<Task>(SIDE_TASK_THREE, SIDE_TASK_THREE_DESCRIPTION));		// ������3
	_tasks.emplace_back(std::make_shared<Task>(SIDE_TASK_FOUR, SIDE_TASK_FOUR_DESCRIPTION));		// ������4
	_tasks.emplace_back(std::make_shared<Task>(SIDE_TASK_FIVE, SIDE_TASK_FIVE_DESCRIPTION));		// ������5
	_tasks.emplace_back(std::make_shared<Task>(SIDE_TASK_SIX, SIDE_TASK_SIX_DESCRIPTION));			// ������6
	_tasks.emplace_back(std::make_shared<Task>(SIDE_TASK_SEVEN, SIDE_TASK_SEVEN_DESCRIPTION));		// ������7
	_tasks.emplace_back(std::make_shared<Task>(NON_TASK, NON_TASK_DESCRIPTION));					// ������
	
	// ��ʼ������
	_lowLevelSkills.emplace_back(std::make_shared<LowLevelSkill>(ELEMENT_SURGE));					// �ͼ�����
	_midLevelSkills.emplace_back(std::make_shared<MidLevelSkill>(Elemental_Torrent));				// �м�����
	_highLevelSkills.emplace_back(std::make_shared<HighLevelSkill>(Energy_Vortex));					// �߼�����
	_highLevelSkills.emplace_back(std::make_shared<HighLevelSkill>(Arcane_Blast));					// ��ϼ���

	// ��ʼ���ѷ�NPC
	_friendNpcs.emplace_back(std::make_shared<FriendNpc>(PRINCESS));								// ����
	_friendNpcs.emplace_back(std::make_shared<FriendNpc>(KING));									// ����
	_friendNpcs.emplace_back(std::make_shared<FriendNpc>(FishStoreManager));						// ����
	_friendNpcs.emplace_back(std::make_shared<FriendNpc>(WeaponStoreManager));						// ������
	_friendNpcs.emplace_back(std::make_shared<FriendNpc>(VegetableStoreManager));					// �߲���
	_friendNpcs.emplace_back(std::make_shared<FriendNpc>(OreStoreManager));							// ��ʯ��

	// ��ʼ���з�NPC
	// ��
	_enemyNpcsGold.emplace_back(std::make_shared<EnemyNpc>(ElementType::Gold, 2, _lowLevelSkills[0]));		
	_enemyNpcsGold.emplace_back(std::make_shared<EnemyNpc>(ElementType::Gold, 1, _midLevelSkills[0]));
	// ľ
	_enemyNpcsWood.emplace_back(std::make_shared<EnemyNpc>(ElementType::Wood, 2, _lowLevelSkills[0]));
	_enemyNpcsWood.emplace_back(std::make_shared<EnemyNpc>(ElementType::Wood, 1, _midLevelSkills[0]));
	// ��
	_enemyNpcsEarth.emplace_back(std::make_shared<EnemyNpc>(ElementType::Earth, 2, _lowLevelSkills[0]));
	_enemyNpcsEarth.emplace_back(std::make_shared<EnemyNpc>(ElementType::Earth, 1, _midLevelSkills[0]));
	// ˮ
	_enemyNpcsWater.emplace_back(std::make_shared<EnemyNpc>(ElementType::Water, 2, _lowLevelSkills[0]));
	_enemyNpcsWater.emplace_back(std::make_shared<EnemyNpc>(ElementType::Water, 1, _midLevelSkills[0]));
	// ��
	_enemyNpcsFire.emplace_back(std::make_shared<EnemyNpc>(ElementType::Fire, 2, _lowLevelSkills[0]));
	_enemyNpcsFire.emplace_back(std::make_shared<EnemyNpc>(ElementType::Fire, 1, _midLevelSkills[0]));

	// ��ʼ��Boss
	ElementType type = _hero->getPlayerElement();					
	_enemyNpcsBoss = std::make_shared<EnemyNpc>(type, 3, _highLevelSkills[0]);

	// ��ʼ����Ʒ
	// ����
	_weapons.emplace_back(std::make_shared<Weapon>(MAGIC_RING));						
	_weapons.emplace_back(std::make_shared<Weapon>(MAGIC_CRYSTAL));
	_weapons.emplace_back(std::make_shared<Weapon>(MAGIC_SCROLL));
	// ����
	_armors.emplace_back(std::make_shared<Armor>(HELMET));
	_armors.emplace_back(std::make_shared<Armor>(ARMOR));
	_armors.emplace_back(std::make_shared<Armor>(SHOES));
	// ʳƷ
	_foods.emplace_back(std::make_shared<Food>(FISH));													//��
	_foods.emplace_back(std::make_shared<Food>(FRUIT));													//ˮ��
	_foods.emplace_back(std::make_shared<Food>(VEGETABLE));												//�߲�
	_foods.emplace_back(std::make_shared<Food>(HERB));													//��ҩ
	_foods.emplace_back(std::make_shared<Food>(MEAT));													//��
	_foods.emplace_back(std::make_shared<Food>(MUSHROOM));												//Ģ��
	_foods.emplace_back(std::make_shared<Food>(RICE));													//����
	_foods.emplace_back(std::make_shared<Food>(APPLE));													//ƻ��
	// ����
	_materials.emplace_back(std::make_shared<GameMaterial>(TREE));										//��
	_materials.emplace_back(std::make_shared<GameMaterial>(WOOD));										//ľͷ
	_materials.emplace_back(std::make_shared<GameMaterial>(STONE));										//ʯͷ
	_materials.emplace_back(std::make_shared<GameMaterial>(GOLD_MINE));									//���
	_materials.emplace_back(std::make_shared<GameMaterial>(CHEST));										//����
	_taskItems.emplace_back(std::make_shared<TaskItem>(KEY));											//Կ��
	_taskItems.emplace_back(std::make_shared<TaskItem>(LETTER));										//�ż�
}
#endif // GLOBAL_MANAGER_H
