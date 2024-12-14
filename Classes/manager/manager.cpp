
#include "manager.h"

// ��ʼ��
void GlobalManager::initializeElements() {
	// ��ʼ��Ԫ�� 
	_elements.emplace_back(std::make_shared<Element>(ElementType::Gold));				// ��
	_elements.emplace_back(std::make_shared<Element>(ElementType::Wood));				// ľ
	_elements.emplace_back(std::make_shared<Element>(ElementType::Water));				// ˮ
	_elements.emplace_back(std::make_shared<Element>(ElementType::Fire));				// ��
	_elements.emplace_back(std::make_shared<Element>(ElementType::Earth));				// ��
}
void GlobalManager::initializePlayer() {

	// ��ʼ�����
	_hero = std::make_shared<Player>();										// ���
}
void GlobalManager::initializeTasks() {
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
}
void GlobalManager::initializeSkills() {
	// ��ʼ������
	_lowLevelSkills.emplace_back(std::make_shared<LowLevelSkill>(ELEMENT_SURGE));					// �ͼ�����
	_midLevelSkills.emplace_back(std::make_shared<MidLevelSkill>(Elemental_Torrent));				// �м�����
	_highLevelSkills.emplace_back(std::make_shared<HighLevelSkill>(Energy_Vortex));					// �߼�����
	_highLevelSkills.emplace_back(std::make_shared<HighLevelSkill>(Arcane_Blast));					// ��ϼ���
}
void GlobalManager::initializeFriendNpcs() {
	// ��ʼ���ѷ�NPC
	_friendNpcs.emplace_back(std::make_shared<FriendNpc>(PRINCESS));								// ����
	_friendNpcs.emplace_back(std::make_shared<FriendNpc>(KING));									// ����
	_friendNpcs.emplace_back(std::make_shared<FriendNpc>(FishStoreManager));						// ����
	_friendNpcs.emplace_back(std::make_shared<FriendNpc>(WeaponStoreManager));						// ������
	_friendNpcs.emplace_back(std::make_shared<FriendNpc>(VegetableStoreManager));					// �߲���
	_friendNpcs.emplace_back(std::make_shared<FriendNpc>(OreStoreManager));							// ��ʯ��
}
void GlobalManager::initializeEnemyNpcs() {
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
}
void GlobalManager::initializeWeapons() {
	// ��ʼ����Ʒ
	// ����
	_weapons.emplace_back(std::make_shared<Weapon>(MAGIC_RING));
	_weapons.emplace_back(std::make_shared<Weapon>(MAGIC_CRYSTAL));
	_weapons.emplace_back(std::make_shared<Weapon>(MAGIC_SCROLL));
}
void GlobalManager::initializeArmors() {
	// ����
	_armors.emplace_back(std::make_shared<Armor>(HELMET));
	_armors.emplace_back(std::make_shared<Armor>(ARMOR));
	_armors.emplace_back(std::make_shared<Armor>(SHOES));
}
void GlobalManager::initializeFoods() {

	// ʳƷ
	_foods.emplace_back(std::make_shared<Food>(FISH));													//��
	_foods.emplace_back(std::make_shared<Food>(FRUIT));													//ˮ��
	_foods.emplace_back(std::make_shared<Food>(VEGETABLE));												//�߲�
	_foods.emplace_back(std::make_shared<Food>(HERB));													//��ҩ
	_foods.emplace_back(std::make_shared<Food>(MEAT));													//��
	_foods.emplace_back(std::make_shared<Food>(MUSHROOM));												//Ģ��
	_foods.emplace_back(std::make_shared<Food>(RICE));													//����
	_foods.emplace_back(std::make_shared<Food>(APPLE));													//ƻ��
}

void GlobalManager::initializeMaterials() {
	// ����
	_materials.emplace_back(std::make_shared<GameMaterial>(TREE));										//��
	_materials.emplace_back(std::make_shared<GameMaterial>(WOOD));										//ľͷ
	_materials.emplace_back(std::make_shared<GameMaterial>(STONE));										//ʯͷ
	_materials.emplace_back(std::make_shared<GameMaterial>(GOLD_MINE));									//���
	_materials.emplace_back(std::make_shared<GameMaterial>(CHEST));										//����
}
void GlobalManager::initializeTaskItems() {
	_taskItems.emplace_back(std::make_shared<TaskItem>(KEY));											//Կ��
	_taskItems.emplace_back(std::make_shared<TaskItem>(LETTER));										//�ż�
}
void GlobalManager::initializeBag() {
	_bag = std::make_shared<Inventory>();																//����
}