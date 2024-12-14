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
	std::shared_ptr<Player> _hero;																						// ���
	std::shared_ptr<EnemyNpc>_battleNpc;																				// ս��NPC
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
		initializeElements();//��ʼ��Ԫ��
		initializeTasks();//��ʼ������
		initializeSkills();//��ʼ������
		initializeFriendNpcs();//��ʼ���ѷ�NPC
		initializePlayer();//��ʼ�����
		initializeEnemyNpcs();//��ʼ���з�NPC
		initializeWeapons();//��ʼ������
		initializeArmors();//��ʼ������
		initializeFoods();//��ʼ��ʳƷ
		initializeMaterials();//��ʼ������
		initializeTaskItems();//��ʼ��������Ʒ 
	}

	
public:

	// ��ȡȫ�ֹ�����ʵ��
    static GlobalManager& getInstance() {
        static GlobalManager instance;
        return instance;
    }
														// ����ս��NPC
	void initializeElements();//��ʼ��
	void initializePlayer();//��ʼ�����
	void initializeTasks();//��ʼ������
	void initializeSkills();//��ʼ������
	void initializeFriendNpcs();//��ʼ���ѷ�NPC
	void initializeEnemyNpcs();//��ʼ���з�NPC
	void initializeWeapons();//��ʼ������
	void initializeArmors();//��ʼ������
	void initializeFoods();//��ʼ��ʳƷ
	void initializeMaterials();//��ʼ������
	void initializeTaskItems();//��ʼ��������Ʒ 
	void initializeBag();//��ʼ������
	

	void setBattleNpc(std::shared_ptr<EnemyNpc> npc) { _battleNpc = npc; }
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
	const std::shared_ptr<Inventory> getInventory() const { return _bag; }														// ��ȡ����		
	const std::shared_ptr<EnemyNpc> getBattleNpc() const { return _battleNpc; }													// ��ȡս��NPC
	// ��ȡ����

    // ��ֹ��������͸�ֵ
	GlobalManager(const GlobalManager&) = delete;
	GlobalManager& operator=(const GlobalManager&) = delete;

    // ��������
    ~GlobalManager() {
		
    }
};





#endif // GLOBAL_MANAGER_H
