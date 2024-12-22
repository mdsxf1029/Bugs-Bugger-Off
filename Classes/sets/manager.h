#ifndef GLOBAL_MANAGER_H
#define GLOBAL_MANAGER_H

#include <string>
#include <vector>
#include <memory>
#include "sets/player.h"
#include "sets/nPC.h"
#include "sets/tasks.h"
#include "sets/skills.h"
#include "sets/items.h"
#include "sets/elements.h"

// ǰ������

struct SkillInfo;
class Player;
class Task;
class Skill;
class Weapon;
class Armor;
class Food;
class GameMaterial;
class TaskItem;
class FriendNpc;
class EnemyNpc;
class Element;

// ȫ�ֹ�����
class GlobalManager {
private:
	std::shared_ptr<Player> _hero;																						// ���
	std::shared_ptr<EnemyNpc>_battleNpc;																				// ս��NPC
	std::vector <std::shared_ptr< Task >> _tasks;   														            // ����                                    


	std::vector<std::shared_ptr<SkillInfo>> skillInfoList;   														    // ������Ϣ�б�
	std::vector<std::shared_ptr<Skill>>skillList;	  														            // �����б�												

	std::vector<std::shared_ptr<FriendNpc>> _friendNpcs; 									    						// �ѷ�NPC                                
	std::vector<std::shared_ptr<EnemyNpc>> _enemyNpcsGold;   							    		        			// �з�NPC -- ��
	std::vector<std::shared_ptr<EnemyNpc>> _enemyNpcsWood;   							    		        			// �з�NPC -- ľ
	std::vector<std::shared_ptr<EnemyNpc>> _enemyNpcsWater;   							    		        			// �з�NPC -- ˮ
	std::vector<std::shared_ptr<EnemyNpc>> _enemyNpcsFire;   							    		        			// �з�NPC -- ��
	std::vector<std::shared_ptr<EnemyNpc>> _enemyNpcsEarth;   							    		        			// �з�NPC -- ��
	std::shared_ptr<EnemyNpc> _enemyNpcsBoss;   							    		        						// boss
	std::vector<std::shared_ptr<Weapon>> _weapons;   							    		            				// ����   
	std::vector<std::shared_ptr<Armor>> _armors;   							    		                				// ����   
	std::vector<std::shared_ptr<Food>> _foods;       			    		                            				// ʳƷ   
	std::vector<std::shared_ptr<GameMaterial>> _materials;   							    		            		// ����           
	std::vector<std::shared_ptr<TaskItem>> _taskItems;   							    		                		// ������Ʒ 
	std::vector<std::shared_ptr<Element>> _elements;   							    		                			// Ԫ��
	std::string _lastMap;
	// ���캯��
	GlobalManager() {
		// ��ʼ��
		_elements.emplace_back(std::make_shared<Element>(ElementType::Gold));											// ��
		_elements.emplace_back(std::make_shared<Element>(ElementType::Wood));											// ľ
		_elements.emplace_back(std::make_shared<Element>(ElementType::Water));											// ˮ
		_elements.emplace_back(std::make_shared<Element>(ElementType::Fire));											// ��
		_elements.emplace_back(std::make_shared<Element>(ElementType::Earth));											// ��

		// ��ʼ�����
		try {
			_hero = std::make_shared<Player>();																			// ���
			if(_hero==nullptr){
				throw std::runtime_error("Player initialization failed: null pointer");
			}
		}
		catch (const std::exception& e) {
			CCLOG("Exception during initialization: %s", e.what());
			throw;
		}
		// ��ʼ������ 
		_tasks.emplace_back(std::make_shared<Task>(MAIN_TASK, MAIN_TASK_DESCRIPTION, SIDE_TASK_ONE_REWARD));					// ��������
		_tasks.emplace_back(std::make_shared<Task>(SIDE_TASK_ONE, SIDE_TASK_ONE_DESCRIPTION,SIDE_TASK_ONE_REWARD));				// ������1
		_tasks.emplace_back(std::make_shared<Task>(SIDE_TASK_TWO, SIDE_TASK_TWO_DESCRIPTION,SIDE_TASK_TWO_REWARD));				// ������2
		_tasks.emplace_back(std::make_shared<Task>(SIDE_TASK_THREE,SIDE_TASK_THREE_DESCRIPTION,SIDE_TASK_THREE_REWARD));		// ������3
		_tasks.emplace_back(std::make_shared<Task>(SIDE_TASK_FOUR, SIDE_TASK_FOUR_DESCRIPTION,SIDE_TASK_FOUR_REWARD));			// ������4
		_tasks.emplace_back(std::make_shared<Task>(SIDE_TASK_FIVE, SIDE_TASK_FIVE_DESCRIPTION,SIDE_TASK_FIVE_REWARD));			// ������5 
		_tasks.emplace_back(std::make_shared<Task>(SIDE_TASK_SIX, SIDE_TASK_SIX_DESCRIPTION, SIDE_TASK_SIX_REWARD));			// ������6		
		_tasks.emplace_back(std::make_shared<Task>(SIDE_TASK_SEVEN, SIDE_TASK_SEVEN_DESCRIPTION, SIDE_TASK_SEVEN_REWARD));		// ������7	
		_tasks.emplace_back(std::make_shared<Task>(SIDE_TASK_EIGHT, SIDE_TASK_EIGHT_DESCRIPTION, SIDE_TASK_EIGHT_REWARD));		// ������8
		_tasks.emplace_back(std::make_shared<Task>(SIDE_TASK_NINE, SIDE_TASK_NINE_DESCRIPTION, SIDE_TASK_NINE_REWARD));			// ������9
		_tasks.emplace_back(std::make_shared<Task>(SIDE_TASK_TEN, SIDE_TASK_TEN_DESCRIPTION, SIDE_TASK_TEN_REWARD));			// ������10
		_tasks.emplace_back(std::make_shared<Task>(SIDE_TASK_ELEVEN, SIDE_TASK_ELEVEN_DESCRIPTION, SIDE_TASK_ELEVEN_REWARD));	// ������11	
		_tasks.emplace_back(std::make_shared<Task>(SIDE_TASK_SHIER, SIDE_TASK_SHIER_DESCRIPTION, SIDE_TASK_SHIER_REWARD));		// ������12
		_tasks.emplace_back(std::make_shared<Task>(SIDE_TASK_SHISAN, SIDE_TASK_SHISAN_DESCRIPTION, SIDE_TASK_SHISAN_REWARD));	// ������13
		_tasks.emplace_back(std::make_shared<Task>(SIDE_TASK_SHISI, SIDE_TASK_SHISI_DESCRIPTION, SIDE_TASK_SHISI_REWARD));		// ������14
		_tasks.emplace_back(std::make_shared<Task>(SIDE_TASK_SHIWU, SIDE_TASK_SHIWU_DESCRIPTION, SIDE_TASK_SHIWU_REWARD));		// ������14
		_tasks.emplace_back(std::make_shared<Task>(SIDE_TASK_SHILIU, SIDE_TASK_SHILIU_DESCRIPTION, SIDE_TASK_SHILIU_REWARD));	// ������14

		_tasks.emplace_back(std::make_shared<Task>(NON_TASK, NON_TASK_DESCRIPTION, SIDE_TASK_ONE_REWARD));						// ������

		// ��ʼ���ѷ�NPC
		_friendNpcs.emplace_back(std::make_shared<FriendNpc>(PRINCESS));														// ����
		_friendNpcs.emplace_back(std::make_shared<FriendNpc>(KING));															// ����
		_friendNpcs.emplace_back(std::make_shared<FriendNpc>(FishStoreManager));												// ����
		_friendNpcs.emplace_back(std::make_shared<FriendNpc>(WeaponStoreManager));												// ������
		_friendNpcs.emplace_back(std::make_shared<FriendNpc>(VegetableStoreManager));											// �߲���
		_friendNpcs.emplace_back(std::make_shared<FriendNpc>(OreStoreManager));													// ��ʯ��

		// ��ʼ������
		skillInfoList.emplace_back(std::make_shared<SkillInfo>(SkillInfo{ "Element_Surge",  5,  90.0f,500.0f,"fire.plist" }));			//����:Element_Surge
		skillInfoList.emplace_back(std::make_shared<SkillInfo>(SkillInfo{ "Element_Torrent",10,  200.0f,360.0f,"fire1.plist" }));		//����:Element_Torrent
		skillInfoList.emplace_back(std::make_shared<SkillInfo>(SkillInfo{ "Energy_Vortex",  10,  300.0f,60.0f,"fireball2.plist" }));	//����:Energy_Vortex 
		skillInfoList.emplace_back(std::make_shared<SkillInfo>(SkillInfo{ "Element_Surge",  5,  50.0f,500.0f,"enemyskill1.plist" }));	//����:Element_Surge
		skillInfoList.emplace_back(std::make_shared<SkillInfo>(SkillInfo{ "Element_Torrent",10,  100.0f,360.0f,"enemyskill2.plist" }));	//����:Element_Torrent
		skillInfoList.emplace_back(std::make_shared<SkillInfo>(SkillInfo{ "Energy_Vortex",  10,  150.0f,60.0f,"enemyskill3.plist" }));	//����:Energy_Vortex 

		// ��ʼ������
		std::shared_ptr<Skill> skill0 = std::make_shared<Skill>(*skillInfoList.at(0));											// �ͼ�����
		std::shared_ptr<Skill> skill1 = std::make_shared<Skill>(*skillInfoList.at(1));											// �м�����
		std::shared_ptr<Skill> skill2 = std::make_shared<Skill>(*skillInfoList.at(2));											// �߼�����
		std::shared_ptr<Skill> enemyskill1 = std::make_shared<Skill>(*skillInfoList.at(3));										// �ͼ�����
		std::shared_ptr<Skill> enemyskill2 = std::make_shared<Skill>(*skillInfoList.at(4));										// �м�����
		std::shared_ptr<Skill> enemyskill3 = std::make_shared<Skill>(*skillInfoList.at(5));										// �߼����� 
		try {
			if (skill0 == nullptr) {
				throw std::runtime_error("Skill0 initialization failed: null pointer");
			}
			if (skill1 == nullptr) {
				throw std::runtime_error("Skill1 initialization failed: null pointer");
			}
			if (skill2 == nullptr) {
				throw std::runtime_error("Skill2 initialization failed: null pointer");
			}
			if (enemyskill1 == nullptr) {
				throw std::runtime_error("Skill3 initialization failed: null pointer");
			}
			if (enemyskill2 == nullptr) {
				throw std::runtime_error("Skill4 initialization failed: null pointer");
			}
			if (enemyskill3 == nullptr) {
				throw std::runtime_error("Skill5 initialization failed: null pointer");
			}
		}
		catch (const std::exception& e) {
			CCLOG("Exception during initialization: %s", e.what());
			throw;
		}
		// �����б�
		skillList.emplace_back(skill0);
		skillList.emplace_back(skill1);
		skillList.emplace_back(skill2);
		skillList.emplace_back(enemyskill1);
		skillList.emplace_back(enemyskill2);
		skillList.emplace_back(enemyskill3);

		// ��
		_enemyNpcsGold.emplace_back(std::make_shared<EnemyNpc>(ElementType::Gold, 1, enemyskill1, "gold1monster1.png"));
		_enemyNpcsGold.emplace_back(std::make_shared<EnemyNpc>(ElementType::Gold, 2, enemyskill2, "gold1monster2.png"));
		// ľ
		_enemyNpcsWood.emplace_back(std::make_shared<EnemyNpc>(ElementType::Wood, 1, enemyskill1, "enemywood1.png"));
		_enemyNpcsWood.emplace_back(std::make_shared<EnemyNpc>(ElementType::Wood, 2, enemyskill2, "enemywood2.png"));
		// ��
		_enemyNpcsEarth.emplace_back(std::make_shared<EnemyNpc>(ElementType::Earth, 1, enemyskill1, "enemyearth1.png"));
		_enemyNpcsEarth.emplace_back(std::make_shared<EnemyNpc>(ElementType::Earth, 2, enemyskill2, "enemyearth2.png"));
		// ˮ
		_enemyNpcsWater.emplace_back(std::make_shared<EnemyNpc>(ElementType::Water, 1, enemyskill1, "whole3monster1.png"));
		_enemyNpcsWater.emplace_back(std::make_shared<EnemyNpc>(ElementType::Water, 2, enemyskill2, "whole3monster2.png"));
		// ��
		_enemyNpcsFire.emplace_back(std::make_shared<EnemyNpc>(ElementType::Fire, 1, enemyskill1, "firemonster1.png"));
		_enemyNpcsFire.emplace_back(std::make_shared<EnemyNpc>(ElementType::Fire, 2, enemyskill2, "firemonster2.png"));

		// ��ʼ��Boss
		ElementType type = _hero->getElement();
		_enemyNpcsBoss = std::make_shared<EnemyNpc>(type, 3, enemyskill3, "enemyboss.png");

		//��ʼ������
		_weapons.emplace_back(std::make_shared<Weapon>(MAGIC_RING));									    //����1
		_weapons.emplace_back(std::make_shared<Weapon>(MAGIC_CRYSTAL));									    //����2	
		_weapons.emplace_back(std::make_shared<Weapon>(MAGIC_SCROLL));									    //����3

		_armors.emplace_back(std::make_shared<Armor>(HELMET));											    //ͷ��
		_armors.emplace_back(std::make_shared<Armor>(ARMOR));											    //����
		_armors.emplace_back(std::make_shared<Armor>(SHOES));											    //Ь��

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
		
		// ��һ����ͼ
		_lastMap = "";
	}

public:

	// ��ȡȫ�ֹ�����ʵ��
	static GlobalManager& getInstance() {
		static GlobalManager instance;
		return instance;
	}
	
	void setBattleNpc(std::shared_ptr<EnemyNpc> npc) { _battleNpc = npc; }														// ����ս��NPC
	void setLastMap(std::string map) { _lastMap = map; }																		// ������һ����ͼ
	
	// ��ȡ��Ա����  
	std::shared_ptr<Player> getPlayer() const { return _hero; }																	// ��ȡ���
	const std::vector<std::shared_ptr<Task>>& getTasks() const { return _tasks; }												// ��ȡ����
	const std::vector<std::shared_ptr<SkillInfo>>& getSkillInfos() const { return skillInfoList; }								// ��ȡ������Ϣ
	const std::vector<std::shared_ptr<Skill>>& getSkills() const { return skillList; }											// ��ȡ����
	const std::vector<std::shared_ptr<FriendNpc>>& getFriendNpcs() const { return _friendNpcs; }								// ��ȡ�ѷ�NPC
	const std::vector<std::shared_ptr<EnemyNpc>>& getEnemyNpcsGold() const { return _enemyNpcsGold; }							// ��ȡ�з�NPC -- ��
	const std::vector<std::shared_ptr<EnemyNpc>>& getEnemyNpcsWood() const { return _enemyNpcsWood; }							// ��ȡ�з�NPC -- ľ
	const std::vector<std::shared_ptr<EnemyNpc>>& getEnemyNpcsWater() const { return _enemyNpcsWater; }							// ��ȡ�з�NPC -- ˮ
	const std::vector<std::shared_ptr<EnemyNpc>>& getEnemyNpcsFire() const { return _enemyNpcsFire; }							// ��ȡ�з�NPC -- ��
	const std::vector<std::shared_ptr<EnemyNpc>>& getEnemyNpcsEarth() const { return _enemyNpcsEarth; }							// ��ȡ�з�NPC -- ��
	const std::shared_ptr<EnemyNpc> getEnemyNpcsBoss() const { return _enemyNpcsBoss; }											// ��ȡboss
	const std::vector<std::shared_ptr<Weapon>>& getWeapons() const { return _weapons; }											// ��ȡ����
	const std::vector<std::shared_ptr<Armor>>& getArmors() const { return _armors; }											// ��ȡ����
	const std::vector<std::shared_ptr<Food>>& getFoods() const { return _foods; }												// ��ȡʳƷ
	const std::vector<std::shared_ptr<GameMaterial>>& getMaterials() const { return _materials; }								// ��ȡ����
	const std::vector<std::shared_ptr<TaskItem>>& getTaskItems() const { return _taskItems; }									// ��ȡ������Ʒ
	const std::vector<std::shared_ptr<Element>>& getElements() const { return _elements; }										// ��ȡԪ��
	const std::shared_ptr<EnemyNpc> getBattleNpc() const { return _battleNpc; }													// ��ȡս��NPC
	std::string getLastMap() const { return _lastMap; }													     					// ��ȡ��һ����ͼ
	
	// ��ֹ��������͸�ֵ
	GlobalManager(const GlobalManager&) = delete;
	GlobalManager& operator=(const GlobalManager&) = delete;

	// ��������
	~GlobalManager() {}
};
#endif // GLOBAL_MANAGER_H
