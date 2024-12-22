#ifndef __MINI_MAP_H__
#define __MINI_MAP_H__

#include "cocos2d.h"
#include <string>
#include <vector>
#include <functional>
#include "Sets/tasks.h"
#include "Sets/manager.h"
#include "Sets/items.h"
#include "HelloWorldScene.h"

struct NPCData {
	cocos2d::Sprite* npcSprite;																						// NPC ����												
	std::string npcFunction;																						// "chat" �� "quest"
	std::shared_ptr<Task> ppp;																						// ����												
	int index;																										// NPC ����
	int taskid;																										// task ����							
	std::string targetScene;																						// Ŀ�곡������NPC��������ת�ĳ�����

	NPCData(cocos2d::Sprite* sprite, const std::string& function, int index,std::shared_ptr<Task> ppp,int taskid, const std::string& target)
		: npcSprite(sprite), npcFunction(function), index(index), ppp(ppp), taskid(taskid), targetScene(target) {}  //���캯��																												// ���캯��
};

struct ItemList {
	cocos2d::Sprite* itemSprite;																					// ��Ʒ����
	int index;																										// ��Ʒ����
	int id;																											// ��Ʒ ID
	Vec2 position;																									// ��Ʒλ��

	ItemList(cocos2d::Sprite* sprite, int index,int id,Vec2 position)
		: itemSprite(sprite), index(index), id(id), position(position) {}											// ���캯��
};
class MiniMap : public cocos2d::Scene
{
public:
	
	MiniMap(const std::string& mapFile = "village.tmx", bool fly = true)												// ���캯��
	:mapName(mapFile), isFly(fly), tiledMap(nullptr),  keyboardListener(nullptr), _currentDialogueBox(nullptr),
		_currentChoiceBox(nullptr) {}		

	static cocos2d::Scene* createWithMap(const std::string& mapName, bool fly);											// ����С��ͼ����								
	/*���ó�ʼ��*/ 
	bool initWithMap(const std::string& mapName);																		// ��ʼ����ͼ
	void update(float delta) override;																					// �����߼�
	bool IsColliding(cocos2d::Vec2 position);																			// ��ײ���
	void createTaskMenu();																								// ��������˵�
	void createBigMap();																								// �������ͼ
	void createBackpack();																								// ��������
	void openBackpack();																								// �򿪱���

	/*��������*/ 
	 ~MiniMap()
	 {
		 StopListening();
	 }

	void StartListening();																							//���ü����¼�������
	void OnKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);								// �������µĻص�����
	void OnKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);								// �����ͷŵĻص�����
	void StopListening();																							// ֹͣ���������¼�								
	
 	void BoatingToMap(const std::string& objectMap);																// ����ȥ���ڵ�ͼ	 
	void FlyToMap(const std::string& objectMap);																	// ����ȥ���ڵ�ͼ
	
	void UpdatePlayerPosition(const cocos2d::EventKeyboard::KeyCode keyCode);										// ��������λ��
	void GetNeighborMap(std::string& newMap1, std::string& newMap2, int& map1, int& map2);							// ��ȡ���ڵ�ͼ
	void ButtonCallback(Ref* sender);																				// ��ť�ص�����
	
	//void onEnter() override;																						// ���볡��
	//void onEnterTransitionDidFinish() override;																	// ���볡����

///private:
	std::string mapName;																							// ��ǰ��ͼ������
	bool isFly;																										// �Ƿ���

	std::vector<NPCData> _npcList;																					// NPC �б�
	std::vector<ItemList> goldoreItems;																				// ���ʯ��Ʒ�б�
	std::vector<ItemList> appleItems;																				// ƻ����Ʒ�б�

	cocos2d::TMXTiledMap* tiledMap;																					// ��ǰ��ͼ����Ƭ��ͼ
	cocos2d::EventListenerKeyboard* keyboardListener;																// ���̼�����
	cocos2d::Sprite* _currentDialogueBox;																			// ��ǰ��ʾ�ĶԻ���
	cocos2d::Sprite* _currentChoiceBox;																				// ��ǰ��ʾ�ĶԻ���
	cocos2d::Node* npcNode;																							// NPC �ڵ�
	cocos2d::Node* itemNode;																						// ��Ʒ�ڵ�
	cocos2d::Scene* getSceneByName(const std::string& sceneName);													// ��ȡ����
	Vec2 touchLocation;																								// �����洢����λ��
	Vec2 preposition;																								// �����洢������һ��λ��

	void displayTaskOptions(NPCData& npcData);																		// ��ʾ����ѡ�񵯴�
	void displayTaskPro(NPCData& npcData);																			// �ᷢ����ת
	void displayTaskStatus(NPCData& npcData);																		// ��ʾ����״̬����
	void displayRewardOptions(NPCData& npcData);																	// ��ʾ������ȡ����
	void handleQuestAcceptance(NPCData& npcData);																	// �����������
	void handleQuestCompletion(NPCData& npcData);																	// ����������ɽ���
	void displayChoice1(cocos2d::Sprite* npc, const std::string& question,											// չʾѡ���1
		const std::vector<std::pair<std::string, std::function<void()>>>& choices);										
	void displayChoice2(cocos2d::Sprite* npc, const std::string& question,											// չʾѡ���2
		const std::vector<std::pair<std::string, std::function<void()>>>&choices); 

	void handleChatNPC(cocos2d::Sprite* npc);																		// ���� NPC �Ի�
	void displayDialogue(cocos2d::Sprite* npc, const std::string& text);											// չʾ�Ի���	
	void displayTownInfo(cocos2d::Sprite* npc);																		// չʾ������Ϣ
	void displayTownDetails(cocos2d::Sprite* npc);																	// չʾ��������
	void displayQuestInfo(cocos2d::Sprite* npc);																	// չʾ������Ϣ
	void displayQuestDetails(cocos2d::Sprite* npc);																	// չʾ��������
	void displayGoodbye(cocos2d::Sprite* npc);																		// չʾ�ټ�
	void checkPickUpItems();																						// ���ʰȡ��Ʒ	
	void PickUpInteraction(ItemList* item);																			// ʰȡ��Ʒ����									
	void restorePositionsAfterPop();																				//�ָ�����λ��
	void verifySprites();																							//��֤����
	void onEnter();
	void onEnterTransitionDidFinish();
};

#endif // __MINI_MAP_H__