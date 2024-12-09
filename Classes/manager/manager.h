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
	Player* _hero;                                                                                  // ���
	std::vector<Task> _tasks;   														            // ����                                    
	std::vector<LowLevelSkill> _lowLevelSkills; 									    			// �ͼ�����         
	std::vector<MidLevelSkill> _midLevelSkills; 									    			// �м�����                             
	std::vector<HighLevelSkill> _highLevelSkills;   							        			// �߼�����                     
	std::vector<FriendNpc> _friendNpcs; 									    					// �ѷ�NPC                                
	std::vector<EnemyNpc> _enemyNpcs;   							    		        			// �з�NPC                            
	std::vector<Weapon> _weapons;   							    		            			// ����   
	std::vector<Armor> _armors;   							    		                			// ����   
	std::vector<Food> _foods;       			    		                            			// ʳƷ   
	std::vector<GameMaterial> _materials;   							    		            	// ����           
	std::vector<TaskItem> _taskItems;   							    		                	// ������Ʒ 
	std::vector<Element> _elements;   							    		                	    // Ԫ��
	Inventory _bag;   							    		                	                    // ����               

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
	Player* getPlayer() { return _hero; }                                                                           // ��ȡ���
	const std::vector<Task>& getTasks() const { return _tasks; }												    // ��ȡ����
	const std::vector<LowLevelSkill>& getLowLevelSkills() const { return _lowLevelSkills; } 					    // ��ȡ�ͼ�����
	const std::vector<MidLevelSkill>& getMidLevelSkills() const { return _midLevelSkills; } 						// ��ȡ�м�����
	const std::vector<HighLevelSkill>& getHighLevelSkills() const { return _highLevelSkills; } 				    	// ��ȡ�߼�����
	const std::vector<FriendNpc>& getFriendNpcs() const { return _friendNpcs; } 								    // ��ȡ�ѷ�NPC
	const std::vector<EnemyNpc>& getEnemyNpcs() const { return _enemyNpcs; }    					                // ��ȡ�з�NPC
	const std::vector<Weapon>& getWeapons() const { return _weapons; } 										        // ��ȡ����
	const std::vector<Armor>& getArmors() const { return _armors; } 										        // ��ȡ����
	const std::vector<Food>& getFoods() const { return _foods; } 										            // ��ȡʳƷ
	const std::vector<GameMaterial>& getMaterials() const { return _materials; } 								    // ��ȡ����
	const std::vector<TaskItem>& getTaskItems() const { return _taskItems; } 									    // ��ȡ������Ʒ
	const std::vector<Element>& getElements() const { return _elements; } 						    			    // ��ȡԪ��
	Inventory& getInventory() { return _bag; } 									                                    // ��ȡ����

    // ��ֹ��������͸�ֵ
    GlobalManager(const GlobalManager&) = delete;                                                       
    GlobalManager& operator=(const GlobalManager&) = delete;

    // ��������
    ~GlobalManager() {
        delete _hero;                                                                                               // �ͷ������Դ
		delete& _bag;                                                                                               // �ͷű�����Դ
		delete[] & _tasks;                                                                                          // �ͷ�������Դ
		delete[] & _lowLevelSkills;                                                                                 // �ͷŵͼ�������Դ
		delete[] & _midLevelSkills;                                                                                 // �ͷ��м�������Դ
		delete[] & _highLevelSkills;                                                                                // �ͷŸ߼�������Դ
		delete[] & _friendNpcs;                                                                                     // �ͷ��ѷ�NPC��Դ
		delete[] & _enemyNpcs;                                                                                      // �ͷŵз�NPC��Դ
		delete[] & _weapons;                                                                                        // �ͷ�������Դ
		delete[] & _armors;                                                                                         // �ͷŻ�����Դ
		delete[] & _foods;                                                                                          // �ͷ�ʳƷ��Դ
		delete[] & _materials;                                                                                      // �ͷŲ�����Դ
		delete[] & _taskItems;                                                                                      // �ͷ�������Ʒ��Դ
		delete[] & _elements;                                                                                        // �ͷ�Ԫ����Դ
    }
};

// ��ʼ��
void GlobalManager::initialize() {
	// ��ʼ��Ԫ��
	_elements.emplace_back(ElementType::Gold);																// ��
	_elements.emplace_back(ElementType::Wood);																// ľ		
	_elements.emplace_back(ElementType::Water);																// ˮ			
	_elements.emplace_back(ElementType::Fire);																// ��		
	_elements.emplace_back(ElementType::Earth);																// ��						

	// ��ʼ�����
	_hero = new Player("try.png");

	// ��ʼ������
	_tasks.emplace_back(MAIN_TASK, MAIN_TASK_DESCRIPTION);
	_tasks.emplace_back(SIDE_TASK_ONE, SIDE_TASK_ONE_DESCRIPTION);
	_tasks.emplace_back(SIDE_TASK_TWO, SIDE_TASK_TWO_DESCRIPTION);
	_tasks.emplace_back(SIDE_TASK_THREE, SIDE_TASK_THREE_DESCRIPTION);
	_tasks.emplace_back(SIDE_TASK_FOUR, SIDE_TASK_FOUR_DESCRIPTION);
	_tasks.emplace_back(SIDE_TASK_FIVE, SIDE_TASK_FIVE_DESCRIPTION);
	_tasks.emplace_back(SIDE_TASK_SIX, SIDE_TASK_SIX_DESCRIPTION);
	_tasks.emplace_back(SIDE_TASK_SEVEN, SIDE_TASK_SEVEN_DESCRIPTION);
	_tasks.emplace_back(NON_TASK, NON_TASK_DESCRIPTION);

	// ��ʼ������
	_lowLevelSkills.emplace_back(ELEMENT_SURGE);															// Ԫ�س��
	_midLevelSkills.emplace_back(Elemental_Torrent);														// Ԫ�غ���				
	_highLevelSkills.emplace_back(Energy_Vortex);															// ��������								
	_highLevelSkills.emplace_back(Arcane_Blast);															// ��������													

	// ��ʼ���ѷ�NPC
	_friendNpcs.emplace_back(PRINCESS);                                                                      // ����
	_friendNpcs.emplace_back(KING); 														    			 // ���� 

	_friendNpcs.emplace_back(FishStoreManager); 														 // ��װ��
	_friendNpcs.emplace_back(WeaponStoreManager); 														 // ������
	_friendNpcs.emplace_back(VegetableStoreManager); 													 // ʳƷ��
	_friendNpcs.emplace_back(OreStoreManager); 														     // ������

	// ��ʼ���з�NPC
	//��
	_enemyNpcs.emplace_back(ElementType::Gold, 2, Elemental_Torrent);                                           //�ͼ������
	_enemyNpcs.emplace_back(ElementType::Gold, 1, ELEMENT_SURGE);   								            //�߼������                  
	//ľ
	_enemyNpcs.emplace_back(ElementType::Wood, 2, Elemental_Torrent);                                           //�ͼ�ľ����
	_enemyNpcs.emplace_back(ElementType::Wood, 1, ELEMENT_SURGE);   								            //�߼�ľ����
	//��
	_enemyNpcs.emplace_back(ElementType::Earth, 2, Elemental_Torrent);                                          //�ͼ�������
	_enemyNpcs.emplace_back(ElementType::Earth, 1, ELEMENT_SURGE);                                              //�߼�������
	//ˮ
	_enemyNpcs.emplace_back(ElementType::Water, 2, Elemental_Torrent);                                          //�ͼ�ˮ����
	_enemyNpcs.emplace_back(ElementType::Water, 1, ELEMENT_SURGE);      					                    //�߼�ˮ����
	//��
	_enemyNpcs.emplace_back(ElementType::Fire, 2, Elemental_Torrent);       			                        //�ͼ������
	_enemyNpcs.emplace_back(ElementType::Fire, 1, ELEMENT_SURGE);    			                                //�߼������

	ElementType type = _hero->getPlayerElement();
	_enemyNpcs.emplace_back(type, 3, Energy_Vortex);                                                               //boss


	// �����з�NPC���԰�����Ҫ�������

	// ��ʼ����Ʒ
	// ����
	_weapons.emplace_back(MAGIC_RING);																	// ħ��
	_weapons.emplace_back(MAGIC_CRYSTAL);																// ħ��
	_weapons.emplace_back(MAGIC_SCROLL);																// ħ��
	// ����
	_armors.emplace_back(HELMET);																		// ͷ��						
	_armors.emplace_back(ARMOR);																		// ����						
	_armors.emplace_back(SHOES);																		// Ь��					
	// ʳƷ
	_foods.emplace_back(FISH);																			// ��
	_foods.emplace_back(FRUIT);																			// ˮ��				
	_foods.emplace_back(VEGETABLE);																		// �߲�						
	_foods.emplace_back(HERB);																			// ��ҩ					
	_foods.emplace_back(MEAT);																			// ��				
	_foods.emplace_back(MUSHROOM);																		// Ģ��			
	_foods.emplace_back(RICE);																			// �׷�							
	_foods.emplace_back(APPLE);																			// ƻ��					
	// ����
	_materials.emplace_back(TREE);																		// ��
	_materials.emplace_back(WOOD);																		// ľ��
	_materials.emplace_back(STONE);																		// ʯͷ
	_materials.emplace_back(GOLD_MINE);																	// ���
	_materials.emplace_back(CHEST);																		// ����	
	_taskItems.emplace_back(KEY);																		// Կ��
	_taskItems.emplace_back(LETTER);																	// ��						


}
#endif // GLOBAL_MANAGER_H
