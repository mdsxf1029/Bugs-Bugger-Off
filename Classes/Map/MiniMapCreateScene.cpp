#include "MiniMap.h"
#include "cocos2d.h"
#include "TaskMenu.h"
#include "ui/CocosGUI.h"
#include "HelloWorldScene.h"
#include <vector>
#include <utility>  // std::pair
#include "SmallTask/QuizGame.h"
#include "BattleScene.h"
#include "Sets/manager.h"
#include "Map/BackgroundManager.h"
#include "Map/SettingScene.h"
#include "Backpack.h"
#include "BackpackLayer.h"
#include "AudioManager.h"
#include "SoilWaterGoldFireWood.h"
#include "GoldWoodSoilWater.h"
#include "GoldWoodSoil.h"
#include "GoldWood.h"
#include <Overmap.h>
cocos2d::Vec2 tilePos;
cocos2d::Size tileSize;
cocos2d::Vec2 playerPos;
std::string mapfile;
std::string files[2] = { "monster1","monster2" };
cocos2d::Label* _playerHealthLabel;
std::shared_ptr<Player> player = GlobalManager::getInstance().getPlayer();

cocos2d::Scene* MiniMap::createWithMap(const std::string& mapFile, bool fly)
{
	CCLOG("MiniMap::createWithMap - Start");														 // �����Ϣ
	MiniMap* scene = new(std::nothrow) MiniMap(mapFile, fly);										 // ����С��ͼ����
	if (scene && scene->initWithMap(mapFile)) {
		scene->autorelease();																		// �ͷų���
		scene->isFly = fly;																			// �����Ƿ����
		scene->mapName = mapFile;																	// ���õ�ͼ����

		CCLOG("MiniMap::createWithMap - Map file: %s, Fly: %d", mapFile.c_str(), fly);				// �����ͼ�ļ������Ƿ����

		/*�ڳ�ʼ����ɺ󴴽�����˵�*/
		scene->createTaskMenu();																	// �����������˵��Ĵ�������
		CCLOG("MiniMap::createWithMap - Task menu created");										// �����Ϣ

		/* ��������Ӵ��ͼ��ť*/
		auto bigMapButton = cocos2d::MenuItemImage::create(
			"CloseNormal.png",																		// ��ť������״̬ͼ��
			"CloseSelected.png",																	// ��ť��ѡ��״̬ͼ��
			[=](Ref* sender) {
				const auto& taskListmap = GlobalManager::getInstance().getTasks();					// ��ȡ�����б�
				if (taskListmap[5]->state >= 1)														// �������5�����
				{
					auto bigMapScene = Setting6::createScene();										// �������ͼ����
					cocos2d::Director::getInstance()->replaceScene(bigMapScene);					// ���ش��ͼ����
				}
				else if (taskListmap[4]->state >= 1)												//�������4�����
				{
					auto bigMapScene = Setting5::createScene();										// �������ͼ����
					cocos2d::Director::getInstance()->replaceScene(bigMapScene);					// ���ش��ͼ����
				}
				else if (taskListmap[3]->state >= 1)											    //�������3�����
				{
					auto bigMapScene = Setting4::createScene();										// �������ͼ����
					cocos2d::Director::getInstance()->replaceScene(bigMapScene);					// ���ش��ͼ����
				}
				else if (taskListmap[2]->state >= 1)	                                            // �������2�����
				{
					auto bigMapScene = Setting3::createScene();										// �������ͼ����
					cocos2d::Director::getInstance()->replaceScene(bigMapScene);					// ���ش��ͼ����
				}
				else if (taskListmap[1]->state >= 1)	                                            // �������1�����
				{
					auto bigMapScene = Setting2::createScene();										// �������ͼ����
					cocos2d::Director::getInstance()->replaceScene(bigMapScene);					// ���ش��ͼ����
				}
				else                                                                                //����
				{
					auto bigMapScene = Setting::createScene();										// �������ͼ����
					cocos2d::Director::getInstance()->replaceScene(bigMapScene);					// ���ش��ͼ����
				}
			}
		);

		auto switchMap = cocos2d::Menu::create(bigMapButton, nullptr);								// �����˵�
		switchMap->setPosition(cocos2d::Director::getInstance()->getVisibleSize().width / 2 - 950,
			cocos2d::Director::getInstance()->getVisibleSize().height / 2 + 450);					// ���ò˵�λ��
		scene->addChild(switchMap);																	// ���˵���ӵ�����
		AudioManager::getInstance().playIntroMusic();												// ���ű�������
		CCLOG("MiniMap::createWithMap - Big map button added to menu");								// �����Ϣ
		return scene;
	}

	CCLOG("MiniMap::createWithMap - Failed to create scene");
	CC_SAFE_DELETE(scene);
	return nullptr;
}

/*��������˵�*/
void MiniMap::createTaskMenu()
{
	CCLOG("MiniMap::createTaskMenu - Start");														// �����Ϣ
	auto taskMenu = TaskMenu::create();																// ��������˵�
	this->addChild(taskMenu, 1);																	// ������˵���ӵ�����
	CCLOG("MiniMap::createTaskMenu - Task menu added");												// �����Ϣ
}
/*�������ͼ*/
void MiniMap::createBigMap()
{
	CCLOG("MiniMap::createBigMap - Start");															// �����Ϣ
	const auto& taskListmap = GlobalManager::getInstance().getTasks();								// ��ȡ�����б�

	if (taskListmap[4]->state == 1)																	//�������4���
	{
		auto bigMapScene = Setting5::createScene();													// �������ͼ����
		if (bigMapScene) {																			// ������ͼ��������
			this->addChild(bigMapScene);															// �����ͼ������ӵ���ǰ����
			CCLOG("MiniMap::createBigMap - Big map scene added to MiniMap");						// �����Ϣ
		}
		else {
			CCLOG("MiniMap::createBigMap - Failed to create big map scene");						// ���������Ϣ
		}
	}
	else if (taskListmap[4]->state == 1)															// �������4���
	{
		auto bigMapScene = Setting5::createScene();													// �������ͼ����
		if (bigMapScene) {																			// ������ͼ��������
			this->addChild(bigMapScene);															// �����ͼ������ӵ���ǰ����
			CCLOG("MiniMap::createBigMap - Big map scene added to MiniMap");						// �����Ϣ
		}
		else {
			CCLOG("MiniMap::createBigMap - Failed to create big map scene");						// ���������Ϣ
		}
	}
	else if (taskListmap[3]->state == 1)															// �������3���
	{
		auto bigMapScene = Setting4::createScene();													// �������ͼ����
		if (bigMapScene) {																			// ������ͼ��������
			this->addChild(bigMapScene);															// �����ͼ������ӵ���ǰ����
			CCLOG("MiniMap::createBigMap - Big map scene added to MiniMap");						// �����Ϣ
		}
		else {
			CCLOG("MiniMap::createBigMap - Failed to create big map scene");						// ���������Ϣ
		}
	}
	else if (taskListmap[2]->state == 1)															// �������2���
	{
		auto bigMapScene = Setting3::createScene();													// �������ͼ����
		if (bigMapScene) {																			// ������ͼ��������
			this->addChild(bigMapScene);															// �����ͼ������ӵ���ǰ����
			CCLOG("MiniMap::createBigMap - Big map scene added to MiniMap");						// �����Ϣ
		}
		else {
			CCLOG("MiniMap::createBigMap - Failed to create big map scene");						// ���������Ϣ
		}
	}
	else if (taskListmap[1]->state == 1)															// �������1���
	{
		auto bigMapScene = Setting2::createScene();													// �������ͼ����
		if (bigMapScene) {																			// ������ͼ��������
			this->addChild(bigMapScene);															// �����ͼ������ӵ���ǰ����
			CCLOG("MiniMap::createBigMap - Big map scene added to MiniMap");						// �����Ϣ
		}
		else {
			CCLOG("MiniMap::createBigMap - Failed to create big map scene");						// ���������Ϣ
		}
	}
	else
	{
		auto bigMapScene = Setting::createScene();													// �������ͼ����
		if (bigMapScene) {																			// ������ͼ��������
			this->addChild(bigMapScene);															// �����ͼ������ӵ���ǰ����
			CCLOG("MiniMap::createBigMap - Big map scene added to MiniMap");						// �����Ϣ
		}
		else {
			CCLOG("MiniMap::createBigMap - Failed to create big map scene");						// ���������Ϣ
		}
	}

}

void MiniMap::createBackpack()
{
	CCLOG("MiniMap::createBackpack - Start");														// �����Ϣ
	BackpackLayer* backpackLayer = BackpackLayer::create();                                         // ����һ�� BackpackLayer ʵ��
	if (backpackLayer) {																			// ������������

		this->getParent()->addChild(backpackLayer);													// ����������ӵ����ڵ�
		CCLOG("MiniMap::createBigMap - Big map scene added to MiniMap");							// �����Ϣ
	}
	else {
		CCLOG("MiniMap::createBigMap - Failed to create big map scene");							// ���������Ϣ
	}
}

bool MiniMap::initWithMap(const std::string& mapFile)														// ��ʼ����ͼ
{
	if (!Scene::init()) {																					// ���������ʼ��ʧ��
		return false;
	}
	mapfile = mapFile;
	auto backpackButton = ui::Button::create("backpack.png");                                                // ʹ�����Լ���ͼ��
	backpackButton->setPosition(Vec2(cocos2d::Director::getInstance()->getVisibleSize().width / 2 + 825,
		cocos2d::Director::getInstance()->getVisibleSize().height / 2 + 150));                               // ��ťλ��
	backpackButton->addClickEventListener([this](Ref* sender) {
		this->openBackpack();
		BackpackLayer* backpackLayer = BackpackLayer::create();                                              // ����һ�� BackpackLayer ���󲢽�����ӵ���ǰ������
		if (backpackLayer) {
			// ����������ӵ���ǰ������
			Director::getInstance()->getRunningScene()->addChild(backpackLayer);                             // ����������ӵ���ǰ����
		}
		});
	this->addChild(backpackButton, 1);																		// ��������ť��ӵ�������                                    
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();							// ��ȡ���������С
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();							// ��ȡ��������ԭ��

	tiledMap = cocos2d::TMXTiledMap::create(mapFile);														// ������Ƭ��ͼ	
	if (!tiledMap) {
		CCLOG("noMap");
		return false;
	}

	// ��ʼ�����
	auto objectGroup = tiledMap->getObjectGroup("Objects");													// ��ȡ������
	auto ojectGroup = tiledMap->getObjectGroup("TransportPoint");											// ��ȡ���͵������
	auto boxGroup = tiledMap->getObjectGroup("Boxs");														// ��ȡ���Ӷ�����
	auto playerObj = objectGroup->getObject("Player");														// ��ȡ��Ҷ���
	auto kingObj = objectGroup->getObject("King");															// ��ȡ��������

	float playerX = playerObj["x"].asFloat();																// ��ȡ���x����
	float playerY = playerObj["y"].asFloat();																// ��ȡ���y����

	float scaleX = 3.0f;																					// ����x���ű���
	float scaleY = 3.0f;																					// ����y���ű���
	tiledMap->setScale(scaleX, scaleY);																		// ���õ�ͼ����
	cocos2d::Size mapSize = tiledMap->getMapSize();															// ��ȡ��ͼ��С
	auto tileSize = tiledMap->getTileSize();																// ��ȡ��Ƭ��С
	auto playerSize = tileSize;																				// ��ȡ��Ҵ�С
	playerSize.width *= scaleX * 2;																			// ������ҿ��
	playerSize.height *= scaleY * 2;																		// ������Ҹ߶�
	player->initWithFile(player->getFileName());															// ��ʼ�����ͼ��
	player->setContentSize(playerSize);																		// ������Ҵ�С
	float bornPointX = 0.0f, bornPointY = 0.0f;																// ��ʼ������������

	auto transportPoint = (isFly == true ? tiledMap->getObjectGroup("TransportPoint") : tiledMap->getObjectGroup("Boat"));	// ��ȡ����λ�õ��߼�����

	/* ��ȡ����λ�õ��߼�����*/
	if (transportPoint) {
		auto transportObject = (isFly == true ? transportPoint->getObject("Fly") : transportPoint->getObject("Boat"));		// ��ȡ����λ�õ��߼�����
		bornPointX = transportObject["x"].asFloat();																		// ��ȡ����λ�õ�x����
		bornPointY = transportObject["y"].asFloat();																		// ��ȡ����λ�õ�y����
	}
	if (!bornPointX && !bornPointY) 																						// ���û�д���λ��
		CCLOG("noBornPoint");																								// �����Ϣ

	auto bornWorld = tiledMap->convertToWorldSpace(cocos2d::Vec2(bornPointX, bornPointY));								// �������ؾ������������
	cocos2d::Vec2 centerWorldPosition = cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 2);					// �����Ӵ����ĵ���������
	cocos2d::Vec2 offset = centerWorldPosition - bornWorld + cocos2d::Vec2(0.0f, -tileSize.height * scaleY);			// ����ƫ����

	/*����ƫ�������Է��߽�������Ӵ��ڲ�*/
	if (offset.x > 0)																						// ���ƫ����x����0
		offset.x = 0;																						// ����ƫ����xΪ0
	else if (offset.x + mapSize.width * tileSize.width * scaleX < visibleSize.width)						// ���ƫ����x���ϵ�ͼ���С�ڿɼ����
		offset.x = visibleSize.width - mapSize.width * tileSize.width * scaleX;								// ����ƫ����xΪ�ɼ���ȼ�ȥ��ͼ���
	if (offset.y > 0)																						// ���ƫ����y����0
		offset.y = 0;																						// ����ƫ����yΪ0
	else if (offset.y + mapSize.height * tileSize.height * scaleY < visibleSize.height)						// ���ƫ����y���ϵ�ͼ�߶�С�ڿɼ��߶�
		offset.y = visibleSize.height - mapSize.height * tileSize.height * scaleY;							// ����ƫ����yΪ�ɼ��߶ȼ�ȥ��ͼ�߶�

	playerPos = offset + bornWorld - cocos2d::Vec2(0.0f, -tileSize.height * scaleY);						// �������ؾ���λ��
	player->setPosition(playerPos);																			// �������ؾ���λ��
	tiledMap->setPosition(offset);																			// ���õ�ͼλ��
	this->addChild(tiledMap);																				// ��ӵ�ͼ
	this->addChild(player.get(), 9);																		// ������ؾ���
	npcNode = Node::create();																				// ����NPC�ڵ�
	this->addChild(npcNode);																				// ���NPC�ڵ�
	itemNode = Node::create();																				// ������Ʒ�ڵ�
	this->addChild(itemNode);																				// �����Ʒ�ڵ�

	float kingX = kingObj["x"].asFloat();																	// ��ȡ����x����
	float kingY = kingObj["y"].asFloat();																	// ��ȡ����y����
	auto king = cocos2d::Sprite::create("king.png");														// ������������
	king->setPosition(kingX, kingY);																		// ���ù���λ��
	npcNode->addChild(king, 9);																				// ��ӹ�������
	king->setContentSize(playerSize);																		// ���ù�����С

	const auto& taskList = GlobalManager::getInstance().getTasks();											// ��ȡ�����б�
	auto npcGroup = objectGroup->getObjects();																// ��ʼ�� NPC ���������ͷ���

	auto objectGroup1 = tiledMap->getObjectGroup("GoldOre");												// ��ȡ��������
	if (objectGroup1 == nullptr) {																			// ���������Ϊ��
		CCLOG("Error: Object group 'GoldOre' not found!");													// ���������Ϣ
	}
	auto goldoreLayer = objectGroup1->getObjects();															// ��ȡ������
	if (goldoreLayer.empty()) {																				// ���������Ϊ��
		CCLOG("Error: No objects found in 'GoldOre' object group!");										// ���������Ϣ
	}

	for (const auto& object : goldoreLayer)																	//�������
	{
		cocos2d::ValueMap goldoreProperties = object.asValueMap();											// ��ȡ�������
		/*��������Ƿ����*/
		if (goldoreProperties.count("id") == 0 || goldoreProperties.count("x") == 0 || goldoreProperties.count("y") == 0) {
			CCLOG("Error: Missing required properties for GoldOre object!");								//���������	
			continue;																						//�����������
		}

		auto goldoreID = goldoreProperties["id"].asInt();													// ��ȡ���ID
		auto x = goldoreProperties["x"].asFloat();															// ��ȡx����
		auto y = goldoreProperties["y"].asFloat();															// ��ȡy����
		CCLOG("GoldOre Object ID: %d at Position: (%f, %f)", goldoreID, x, y);								// ���������ID��λ��

		auto goldore = cocos2d::Sprite::create("smallmap/GoldOre.png");										// ���������
		goldoreItems.push_back({ goldore,3, goldoreID, Vec2(x, y) });										// ��ӽ���鵽����б�������ײ�������ݣ�׼������ʹ�á�

		cocos2d::Vec2 itemPos = tiledMap->convertToWorldSpace(cocos2d::Vec2(x, y));							// ������λ��
		goldore->setPosition(itemPos);																		// ���ý��λ��

		if (itemNode) {																						// �����Ʒ�ڵ����
			itemNode->addChild(goldore);																	// ��ӽ���鵽��Ʒ�ڵ�
		}
		else {																								// �����Ʒ�ڵ㲻����
			CCLOG("Error: itemNode is not initialized!");													// ���������Ϣ
		}
		this->scheduleUpdate();																				// ���ȸ���
	}

	/*��ȡ�ɽ���ƻ�������*/ 
	auto appleGroup1 = tiledMap->getObjectGroup("Apple");													// ��ȡƻ��������
	if (appleGroup1 == nullptr) {																			// ���������Ϊ��
		CCLOG("Error: Object group 'GoldOre' not found!");													// ���������Ϣ
	}
	auto appleLayer = appleGroup1->getObjects();															// ��ȡƻ������
	if (appleLayer.empty()) {																				// ���ƻ������Ϊ��
		CCLOG("Error: No objects found in 'GoldOre' object group!");										// ���������Ϣ
	}

	for (const auto& object : appleLayer)																	//���������
	{
		cocos2d::ValueMap appleProperties = object.asValueMap();											// ��ȡƻ������
		// ��������Ƿ����
		if (appleProperties.count("id") == 0 || appleProperties.count("x") == 0 || appleProperties.count("y") == 0) {
			CCLOG("Error: Missing required properties for GoldOre object!");								// ���������Ϣ
			continue;																						// �����������
		}

		auto appleID = appleProperties["id"].asInt();														// ��ȡƻ��ID
		auto x = appleProperties["x"].asFloat();															// ��ȡx����
		auto y = appleProperties["y"].asFloat();															// ��ȡy����
			
		CCLOG("GoldOre Object ID: %d at Position: (%f, %f)", appleID, x, y);								// ���ƻ������ID��λ��

		auto apple = cocos2d::Sprite::create("Maze/apple.png");												// ����ƻ������
		appleItems.push_back({ apple,7, appleID, Vec2(x, y) });												// ���ƻ�����鵽ƻ���б��洢��ײ�������ݣ�׼������ʹ�á�

		cocos2d::Vec2 itemPos = tiledMap->convertToWorldSpace(cocos2d::Vec2(x, y));							// ����ƻ��λ��
		apple->setPosition(itemPos);																		// ����ƻ��λ��

		/*ȷ�� itemNode �Ѿ���ʼ��*/ 
		if (itemNode) {																						// �����Ʒ�ڵ����
			itemNode->addChild(apple);																		// ���ƻ�����鵽��Ʒ�ڵ�
		}
		else {
			CCLOG("Error: itemNode is not initialized!");													// ���������Ϣ
		}
		this->scheduleUpdate();																				// ���ȸ���
	}

	int i = 0;	

	for (auto& npcObj : npcGroup) 																			// ���� NPC
	{
		cocos2d::ValueMap npcData = npcObj.asValueMap();													// ��ȡnpc����
		if (!npcData.empty()) {																				// ���npc���ݲ�Ϊ��
			auto task = taskList[i];																		// ��ȡ����

			int indexnpc = 0;																				// ��ʼ��NPC����
			int indexmon = 0;																				// ��ʼ����������
			std::string npcFunction = npcData["npcFunction"].asString();									// ��ȡNPC����
			std::string targetScene = npcData["targetScene"].asString();									// ��ȡĿ�곡��
			std::string type = npcData["type"].asString();													
			indexnpc = npcData["index"].asInt();															// ��ȡNPC����
			if (type == "shopkeeper") {																		// ����������̵�곤
				int indexp = npcData["indexp"].asInt();														// ��ȡNPCͼƬ����
				auto npc = cocos2d::Sprite::create(std::to_string(indexp) + "NPC.png");						// ����NPC����
				cocos2d::Vec2 npcPos = tiledMap->convertToWorldSpace(cocos2d::Vec2(npcData["x"].asFloat(), npcData["y"].asFloat()));	// ����NPCλ��
				npc->setPosition(npcPos);																	// ����NPCλ��
				npc->setContentSize(playerSize);															// ����NPC��С
				npcNode->addChild(npc);																		// ���NPC��NPC�ڵ�
				_npcList.push_back({ npc, npcFunction, indexnpc,taskList[indexnpc],indexnpc,targetScene });	// ���NPC��NPC�б�
			}
			if (type == "NPC") {																			// ���������NPC
				auto npc = cocos2d::Sprite::create("4NPC.png");												// ����NPC����
				cocos2d::Vec2 npcPos = tiledMap->convertToWorldSpace(cocos2d::Vec2(npcData["x"].asFloat(), npcData["y"].asFloat()));	// ����NPCλ��
				npc->setPosition(npcPos);																	// ����NPCλ��
				npc->setContentSize(playerSize);															// ����NPC��С
				npcNode->addChild(npc);																		// ���NPC��NPC�ڵ�
				/* �Ի���NPC*/
				if (npcFunction == "chat")																	// ���NPC����������
					_npcList.push_back({ npc, npcFunction, indexnpc,taskList[indexnpc],indexnpc,targetScene });	// ���NPC��NPC�б�
				if (npcFunction == "quest")																	// ���NPC����������
					_npcList.push_back({ npc, npcFunction, indexnpc,taskList[indexnpc],indexnpc,targetScene });	// ���NPC��NPC�б�
			}
			else if (type == "box") {																		// �������������
				auto npc = cocos2d::Sprite::create("smallmap/boxlqy.png");									// �������Ӿ���
				auto pos = tiledMap->convertToWorldSpace(cocos2d::Vec2(npcData["x"].asFloat(), npcData["y"].asFloat()));				// ��������λ��
				npc->setPosition(pos);																		// ��������λ��
				npc->setContentSize(playerSize);															// �������Ӵ�С
				npcNode->addChild(npc);																		// ������ӵ�NPC�ڵ�
				_npcList.push_back({ npc, npcFunction,indexnpc, taskList[indexnpc],indexnpc,targetScene });	// ���NPC��NPC�б�
			}
			else if (type == "monster") {																	// ��������ǹ���
				indexmon = npcData["indexmon"].asInt();														// ��ȡ��������
				std::string mapf;																			// ��ʼ����ͼ�ļ�
				if (mapFile == "smallmap/whole3.tmx")														// �����ͼ�ļ���whole3
					mapf = "whole3";																		// ���õ�ͼ�ļ�Ϊwhole3
				else if (mapFile == "smallmap/gold1.tmx")													// �����ͼ�ļ���gold1
					mapf = "gold1";																			// ���õ�ͼ�ļ�Ϊgold1
				else if (mapFile == "smallmap/earth.tmx")													// �����ͼ�ļ���earth
					mapf = "earth";																			// ���õ�ͼ�ļ�Ϊearth
				else if (mapFile == "smallmap/fire.tmx")													// �����ͼ�ļ���fire
					mapf = "fire";																			// ���õ�ͼ�ļ�Ϊfire
				else if (mapFile == "smallmap/wood.tmx")													// �����ͼ�ļ���wood
					mapf = "wood";																			// ���õ�ͼ�ļ�Ϊwood

				auto npc = cocos2d::Sprite::create(mapf + "monster" + std::to_string(indexmon + 1) + ".png");			// �������ﾫ��
				npc->setContentSize(playerSize);																		// ���ù����С
				auto pos = tiledMap->convertToWorldSpace(cocos2d::Vec2(npcData["x"].asFloat(), npcData["y"].asFloat()));// �������λ��
				npc->setPosition(pos);																					// ���ù���λ��
				npcNode->addChild(npc);																					// ��ӹ��ﵽNPC�ڵ�
				_npcList.push_back({ npc, npcFunction, indexmon,taskList[indexnpc],indexnpc,targetScene });				// ��ӹ��ﵽNPC�б�
			}
		}
		this->scheduleUpdate();																				// ���ȸ���
	}
	StartListening();																						// ���ü����¼�������

	return true;

}

// ���ü����¼�������
void MiniMap::StartListening()
{
	/*ȷ��û���ظ���Ӽ�����*/ 
	if (!keyboardListener) {
		keyboardListener = cocos2d::EventListenerKeyboard::create();                        		// ��������������¼�������
		keyboardListener->onKeyPressed = CC_CALLBACK_2(MiniMap::OnKeyPressed, this);	        	// ���ü��̰����¼��Ļص�����
		keyboardListener->onKeyReleased = CC_CALLBACK_2(MiniMap::OnKeyReleased, this);		        // ���ü����ͷ��¼��Ļص�����
		_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);		    // ��ӵ��¼���������
	}
}

/* �������µĻص�����*/
void MiniMap::OnKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	switch (keyCode) {																				// ���ݰ�����ִ����Ӧ����
		case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:											// ������µ����ϼ�ͷ��/
		case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:										// ������µ����¼�ͷ��
		case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:										// ������µ������ͷ��
		case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:										// ������µ����Ҽ�ͷ��
			GlobalManager::getInstance().getPlayer()->isMoving = true;								// ������������ƶ�
			UpdatePlayerPosition(keyCode);															// �������λ��
			break;
		default:																					// Ĭ�����
			break;																					// �˳�
	}
}

/*�����߼�*/ 
bool MiniMap::IsColliding(cocos2d::Vec2 position)
{
	/*��ȡ���ؾ��鵱ǰ��������*/ 
	auto playerPos = player->getPosition();															// ��ȡ���λ��
	auto x = position.x, y = position.y;															// ��ʼ��x��y����
	auto tileSize = tiledMap->getTileSize();														// ��ȡ��Ƭ��С

	// ������npc�����Ϊ���ĵ��ĸ���Ƭ��Χ�������Ҫ��С��������/2
	if (playerPos.x >= x - tileSize.width && playerPos.x <= x + tileSize.width && playerPos.y >= y - tileSize.height && playerPos.y <= y + tileSize.height) {
		CCLOG("Collide npc");																		// �����Ϣ
		return true;
	}
	return false;
}

void MiniMap::update(float delta)
{
	for (auto& npcData : _npcList)																	// ����NPC
	{
		auto npc = npcData.npcSprite;																// ��ȡNPC����

		if (npcNode) {																				// ���NPC�ڵ����
			bool iscod = IsColliding(npc->getPosition() + npcNode->getPosition());					// ����Ƿ���NPC��ײ

			if (iscod && !_currentDialogueBox && !_currentChoiceBox && !npc->getUserData()) {		// ��������NPC��ײ����û�жԻ����ѡ���
				CCLOG("WE ARE NPC");																// �����Ϣ
				npc->setUserData((void*)1);															// ����NPC����
				if (npcData.npcFunction == "chat")													// ���NPC����������
				{
					displayChoice1(npc, "Can you talk with me?", {                                  // ��ʾ�Ի���
						{"Yes", [this, npc]() { {													// ��ʱ��ʾ��һ���Ի��򣬱����ڵ�
								this->scheduleOnce([=](float) {
									handleChatNPC(npc);
								}, 0.1f, "handleChatNPC");
							} }},
						{"No", nullptr}
						});
				}
				else if (npcData.npcFunction == "quest")											// ���NPC����������
				{
					CCLOG("KKKKKKKKKKKKK");
					switch (npcData.ppp->state) {													// ��������״ִ̬����Ӧ����
						case -1:																	// �������״̬��δ����
							CCLOG("Task state before assignment: %d", npcData.ppp->state);			// �����Ϣ
							displayTaskOptions(npcData);											// ��ʾ����ѡ�񵯴�
							break;
						case 0:																		// �������״̬���ѽ���
							CCLOG("Task state before assignment: %d", npcData.ppp->state);			// �����Ϣ
							displayDialogue(npc, "YOU've DONE" + npcData.ppp->getTaskName());		// ��ʾ�Ի���
							break;
						case 1:																		// �������״̬�������
							displayRewardOptions(npcData);											// ��ʾ������ȡ����
							break;
						case 2:																		// �������״̬������ȡ����
							displayDialogue(npc, "���Ѿ�������ҵ����񣬸�л��İ�����");			// ��ʾ�Ի���
							break;
					}
				}
				else if (npcData.npcFunction == "questpro") {
					// ������NPC
					switch (npcData.ppp->state) {																// ��������״ִ̬����Ӧ����
						case -1:
							/* ��ʾ����ѡ�񵯴�*/
							if (npcData.targetScene == "BattleScene") {											// ���Ŀ�곡����ս������
								if (mapfile == "smallmap/whole3.tmx") {											// �����ͼ�ļ���whole3
									const auto& MonList = GlobalManager::getInstance().getEnemyNpcsWater();		// ��ȡˮ���Թ����б�
									GlobalManager::getInstance().setBattleNpc(MonList[npcData.index]);			// ����ս��NPC
								}
								if (mapfile == "smallmap/gold1.tmx") {											// �����ͼ�ļ���gold1
									const auto& MonList = GlobalManager::getInstance().getEnemyNpcsGold();		// ��ȡ�����Թ����б�
									GlobalManager::getInstance().setBattleNpc(MonList[npcData.index]);			// ����ս��NPC
								}
								if (mapfile == "smallmap/earth.tmx") {											// �����ͼ�ļ���earth
									const auto& MonList = GlobalManager::getInstance().getEnemyNpcsEarth();		// ��ȡ�����Թ����б�
									GlobalManager::getInstance().setBattleNpc(MonList[npcData.index]);			// ����ս��NPC
								}
								if (mapfile == "smallmap/fire.tmx") {											// �����ͼ�ļ���fire
									const auto& MonList = GlobalManager::getInstance().getEnemyNpcsFire();		// ��ȡ�����Թ����б�
									GlobalManager::getInstance().setBattleNpc(MonList[npcData.index]);			// ����ս��NPC
								}
								if (mapfile == "smallmap/wood.tmx") {											// �����ͼ�ļ���wood
									const auto& MonList = GlobalManager::getInstance().getEnemyNpcsWood();		// ��ȡľ���Թ����б�
									GlobalManager::getInstance().setBattleNpc(MonList[npcData.index]);			// ����ս��NPC
								}
							}
							displayTaskPro(npcData);															// ��ʾ����ѡ�񵯴�
							break;
						case 0:																					// �������״̬���ѽ���
							/*��ӡ����״̬*/ 
							CCLOG("Task state before assignment: %d", npcData.ppp->state);						// �����Ϣ
							displayDialogue(npc, "YOU've DONE");												// ��ʾ�Ի���
							break;
						case 1:																					// �������״̬�������
							/*��ʾ������ȡ����*/ 
							displayRewardOptions(npcData);														// ��ʾ������ȡ����
							break;
						case 2:																					// �������״̬������ȡ����
							displayDialogue(npc, "thank you");													// ��ʾ�Ի���
							break;
					}
				}
			}
			/*�������� NPC û����ײ����֮ǰ�Ѿ��������������ý���״̬*/ 
			else if (!iscod && npc->getUserData() != nullptr)													// ��������NPCû����ײ����֮ǰ�Ѿ�������
			{
				npc->setUserData(nullptr);																		// ����NPC����
			}
		}
	}
	/*������Ʒ������Ƿ�������Ʒ*/ 
	for (auto it = goldoreItems.begin(); it != goldoreItems.end(); ++it)										// �������
	{
		auto item = it->itemSprite;																				// ��ȡ�����

		/*��ӡ��Ʒ�����λ�ã������ײ��Χ*/ 
		CCLOG("Item position: (%f, %f)", item->getPosition().x, item->getPosition().y);							// �����Ϣ
		CCLOG("Player position: (%f, %f)", player->getPosition().x, player->getPosition().y);					// �����Ϣ

		bool iscod = IsColliding(item->getPosition() + itemNode->getPosition());								// ����Ƿ�������Ʒ
		if (iscod)
		{
			checkPickUpItems();																					// ����һ�ε��ֻ��ʰȡһ����Ʒ
			break;
		}
	}

	/*������Ʒ������Ƿ�������Ʒ*/ 
	for (auto it = appleItems.begin(); it != appleItems.end(); ++it)	                                        //����ƻ��
	{
		auto item = it->itemSprite;																				// ��ȡƻ������

		/*��ӡ��Ʒ�����λ�ã������ײ��Χ*/ 
		CCLOG("Item position: (%f, %f)", item->getPosition().x, item->getPosition().y);							// �����Ϣ ��Ʒ
		CCLOG("Player position: (%f, %f)", player->getPosition().x, player->getPosition().y);					// �����Ϣ	���

		bool iscod = IsColliding(item->getPosition() + itemNode->getPosition());								// ����Ƿ�������Ʒ
		if (iscod)
		{
			checkPickUpItems();																					// ����һ�ε��ֻ��ʰȡһ����Ʒ
			break;
		}
	}
}

/*�����ͷŵĻص�����*/ 
void MiniMap::OnKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	GlobalManager::getInstance().getPlayer()->isMoving = false;													// ������Ҳ����ƶ�
}

void MiniMap::displayChoice1(cocos2d::Sprite* npc, const std::string& question,
	const std::vector<std::pair<std::string, std::function<void()>>>& choices)
{
	if (_currentChoiceBox) {																					           		  // ������ڵ�ǰ�Ի����Ƴ���
		_currentChoiceBox->removeFromParent();																					  // �Ƴ��Ի���
		_currentChoiceBox = nullptr;																					          // ���öԻ���
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();																  // ��ȡ�ɼ���С
	_currentChoiceBox = cocos2d::Sprite::create("smallmap/box.png");															  // �����Ի���
	_currentChoiceBox->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));										  // ���öԻ���λ��
	this->addChild(_currentChoiceBox);																							  // ��ӶԻ���
	_currentChoiceBox->setLocalZOrder(100);																        				  // �öԻ����ڽϸߵĲ㼶 
	auto label = cocos2d::Label::createWithTTF(question, "fonts/Marker Felt.ttf", 48);											  // ������ǩ
	label->setTextColor(cocos2d::Color4B::WHITE);																				  // ���ñ�ǩ��ɫ
	label->setPosition(_currentChoiceBox->getContentSize().width / 2, _currentChoiceBox->getContentSize().height / 2 + 100);	  // ���ñ�ǩλ��
	_currentChoiceBox->addChild(label, 1);																					      // ��ӱ�ǩ���Ի���
	label->setLocalZOrder(101);																									  // �ñ�ǩ���ڽϸߵĲ㼶

	float buttonY = 50;																											  // ��ʼ����ťY����
	for (size_t i = 0; i < choices.size(); ++i)								                                                      // ����ѡ��
	{
		cocos2d::ui::Button* button;
		if (i == 0) {
			button = cocos2d::ui::Button::create("Yes1.png", "Yes2.png");														  // ������ťyes
		}
		else if (i == 1) {
			button = cocos2d::ui::Button::create("No1.png", "No2.png");														      // ������ťno
		}
		button->setPosition(cocos2d::Vec2(_currentChoiceBox->getContentSize().width / 4 + i * 300 + 30, _currentChoiceBox->getContentSize().height / 4));
		_currentChoiceBox->addChild(button);																					  // ��Ӱ�ť���Ի���

		button->addClickEventListener([=](cocos2d::Ref* sender) {
			if (choices[i].second) {
				choices[i].second();																				// ִ��ѡ���Ļص�
			}
			/*��Ҫ�������Ƴ��Ի����������µĶԻ���*/ 
			if (_currentChoiceBox) {																				// ������ڵ�ǰ�Ի���
				_currentChoiceBox->removeFromParent();																// �Ƴ��Ի���
				_currentChoiceBox = nullptr;																		// ���öԻ���
			}

			});
	}
}

void MiniMap::handleChatNPC(cocos2d::Sprite* npc)
{
	/*��ʾ�µĶԻ���*/ 
	displayChoice2(npc, "Hello! How can I help you today?", {
		{"Tell me about the town", [this, npc]() { {																// ��ʱ��ʾ��һ���Ի��򣬱����ڵ�
																													// ��ʱ��ʾ��һ���Ի��򣬱����ڵ�
				this->scheduleOnce([=](float) {																		// ��ʱ��ʾ��һ���Ի���
					displayTownInfo(npc);																			// ��ʾ������Ϣ
				}, 0.1f, "handleChatNPC");																			// ��ʱ0.1��
			} }},
		{"I need a quest", [this, npc]() { {
																													// ��ʱ��ʾ��һ���Ի��򣬱����ڵ�
				this->scheduleOnce([=](float) {																		// ��ʱ��ʾ��һ���Ի���
					displayQuestInfo(npc);																			// ��ʾ������Ϣ
				}, 0.1f, "handleChatNPC");																			// ��ʱ0.1��
			} }},
		{"Nothing, just passing by", [this, npc]() { {
																													// ��ʱ��ʾ��һ���Ի��򣬱����ڵ�
				this->scheduleOnce([=](float) {																		// ��ʱ��ʾ��һ���Ի���
					displayGoodbye(npc);																			// ��ʾ�ټ�
				}, 0.1f, "handleChatNPC");																			// ��ʱ0.1��	
			} }},
		});
}

void MiniMap::displayChoice2(cocos2d::Sprite* npc, const std::string& question,
	const std::vector<std::pair<std::string, std::function<void()>>>& choices)
{
	/*ȷ���ɶԻ������*/ 
	if (_currentChoiceBox) {																						// ������ڵ�ǰ�Ի���
		_currentChoiceBox->removeFromParent();																		// �Ƴ��Ի���
		_currentChoiceBox = nullptr;																				// ���öԻ���
	}

	_currentChoiceBox = cocos2d::Sprite::create("smallmap/box3.png");												// �����Ի���
	auto visibleSize = Director::getInstance()->getVisibleSize();													// ��ȡ�ɼ���С
	_currentChoiceBox->setPosition(Vec2(visibleSize.width / 2, 5 * visibleSize.height / 6));						// ���öԻ���λ��
	this->addChild(_currentChoiceBox, 1);																			// ��ӶԻ���
	_currentChoiceBox->setLocalZOrder(100);																			// �öԻ����ڽϸߵĲ㼶

	auto label = cocos2d::Label::createWithTTF(question, "fonts/Marker Felt.ttf", 48);								// ������ǩ
	label->setTextColor(cocos2d::Color4B::BLACK);																	// ���ñ�ǩ��ɫ
	label->setPosition(_currentChoiceBox->getContentSize().width / 2, _currentChoiceBox->getContentSize().height / 2 - 30);	// ���ñ�ǩλ��
	_currentChoiceBox->addChild(label, 1);																			// ��ӱ�ǩ���Ի���
	label->setLocalZOrder(101);																						// �ñ�ǩ���ڽϸߵĲ㼶

	float buttonY = 50;																								// ��ʼ����ťY����
	for (size_t i = 0; i < choices.size(); ++i)																		// ����ѡ��
	{
		auto button = cocos2d::ui::Button::create("button1.png", "button2.png");									// ������ť
		button->setTitleText(choices[i].first);																		// ���ð�ť�ı�	
		button->setTitleFontName("fonts/Marker Felt.ttf");															// ���ð�ť����
		button->setTitleColor(cocos2d::Color3B::BLACK);																// ���ð�ť�ı���ɫ
		button->setTitleFontSize(24);																				// ���ð�ť�ı���С
		button->setPosition(cocos2d::Vec2(_currentChoiceBox->getContentSize().width / 2, buttonY + i * 150 - 400));	// ���ð�ťλ��
		_currentChoiceBox->addChild(button);																		// ��Ӱ�ť���Ի���

		/* ִ��ѡ���Ļص�*/
		button->addClickEventListener([=](cocos2d::Ref* sender) {
			if (choices[i].second) {
				choices[i].second();
			}
			/*�ڻص������Ƴ��Ի���*/ 
			_currentChoiceBox->removeFromParent();																	// �Ƴ��Ի���										
			_currentChoiceBox = nullptr;																			// ���öԻ���
			});
	}
}
/*NPC �ش���ڳ�������*/ 
void MiniMap::displayTownInfo(cocos2d::Sprite* npc)																	// NPC�ش���ڳ�������
{
	displayChoice2(npc, "This is a peaceful town. You can find a shop,\n a tavern, and a blacksmith.", {		    // ��ʾ�Ի���
		{"I see, tell me more!", [this, npc]() { {													
				this->scheduleOnce([=](float) {																		// ��ʱ��ʾ��һ���Ի��򣬱����ڵ�
					displayTownDetails(npc);																		// ��ʾ������ϸ��Ϣ
				}, 0.1f, "handleChatNPC");																			// ��ʱ0.1��
			} }},
		{"That's enough, thanks!", [this, npc]() { displayGoodbye(npc); }}											// ��ʾ�ټ�
		});
}

/*NPC ��ϸ���ܳ���*/ 
void MiniMap::displayTownDetails(cocos2d::Sprite* npc)																// NPC ��ϸ���ܳ���
{
	displayDialogue(npc, "The shop sells potions, the tavern offers drinks and rumors, and the blacksmith can upgrade your gear.");
}

/*NPC ����������Ϣ*/ 
void MiniMap::displayQuestInfo(cocos2d::Sprite* npc)																// NPC ����������Ϣ
{
	displayChoice2(npc, "I have a quest for you: Collect 10 herbs.", {
		{"Maybe later", [this, npc]() { displayGoodbye(npc); }},													// ��ʾ�ټ�
		{"Tell me more", [this, npc]() { displayQuestDetails(npc); }}												// ��ʾ������ϸ��Ϣ
		});
}

/* NPC ��ϸ������Ϣ*/
void MiniMap::displayQuestDetails(cocos2d::Sprite* npc)
{
	displayDialogue(npc, "The herbs grow near the forest. \nPlease bring them back to me once you've collected them.");
}

/*NPC ˵���ټ���*/ 
void MiniMap::displayGoodbye(cocos2d::Sprite* npc)
{
	displayDialogue(npc, "Goodbye, and good luck on your adventures!");
}

void MiniMap::displayDialogue(Sprite* npc, const std::string& text)
{
	if (_currentDialogueBox) {																//����Ի������			
		_currentDialogueBox->removeFromParent();											// �Ƴ��Ի���
		_currentDialogueBox = nullptr;														// ���öԻ���
	}

	auto dialogueBox = Sprite::create("smallmap/box3.png");									// �����Ի���
	if (!dialogueBox) {																		// ����Ի��򴴽�ʧ��
		CCLOG("Failed to create dialogue box!");											// ���������Ϣ
		return;																				// �˳�
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();							// ��ȡ�ɼ�����Ĵ�С
	dialogueBox->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));			// ���öԻ���λ��
	this->addChild(dialogueBox);															// ��ӶԻ��򵽳���

	auto label = Label::createWithTTF(text, "fonts/Marker Felt.ttf", 24);					// ������ǩ
	label->setTextColor(Color4B::BLACK);													// ���ñ�ǩ��ɫ
	label->setPosition(dialogueBox->getContentSize() / 2);									// ���ñ�ǩλ��
	dialogueBox->addChild(label);															// ��ӱ�ǩ���Ի���
	_currentDialogueBox = dialogueBox;														// ���õ�ǰ�Ի���

	/* �Զ���ʧ�Ի���*/
	this->scheduleOnce([=](float) {
		dialogueBox->removeFromParent();													// �Ƴ��Ի���
		_currentDialogueBox = nullptr;
		}, 3.0f, "closeDialogue");
}

void MiniMap::displayTaskOptions(NPCData& npcData) {										// ��ʾ����ѡ��
	displayChoice1(npcData.npcSprite, npcData.ppp->getTaskName(), {
		{"YES", [this, &npcData]() {
			npcData.ppp->state = 0;															// ��������״̬Ϊ�ѷ���
			createTaskMenu();																// ��������˵�
			displayDialogue(npcData.npcSprite, npcData.ppp->getTaskDescription());			// ��ʾ�Ի���
		}},
		{"NO", nullptr}																		// ����������
		});
}

void MiniMap::displayTaskPro(NPCData& npcData) {											// ��ʾ����ѡ��
	displayChoice1(npcData.npcSprite, npcData.ppp->getTaskName(), {		                    // ��ʾ����ѡ��
		{"YES", [this, &npcData]() {
			npcData.ppp->state = 0;															// ��������״̬Ϊ�ѷ���
			CCLOG("message", npcData.targetScene);											// �����Ϣ
			player->removeFromParent();														// �Ƴ����
			GlobalManager::getInstance().setLastMap(mapName);								// ������һ����ͼ
			const auto& taskListbat = GlobalManager::getInstance().getTasks();				// ��ȡ�����б�
			taskListbat[0]->id = npcData.taskid;											// ��������ID
			Director::getInstance()->replaceScene(TransitionFade::create(1.0f, getSceneByName(npcData.targetScene)));	// �滻����
			npcData.ppp->state = 1;															// ��������״̬Ϊ�����

		}},
		{"NO", nullptr}																		// ����������
		});
}

void MiniMap::displayTaskStatus(NPCData& npcData) {
	displayDialogue(npcData.npcSprite, "TASK");												// ��ʾ�Ի���
}

void MiniMap::displayRewardOptions(NPCData& npcData) {
	displayChoice1(npcData.npcSprite, npcData.ppp->getTaskReward(), {						// ��ʾ����ѡ��
		{"OF COURSE", [this, &npcData]() {
			if (npcData.ppp->state == 1) {													// �������״̬�������
				// �����������ȡ����
				if (npcData.ppp->getTaskName() == "WATER TASK" || npcData.ppp->getTaskName() == "GOLD TASK" 
					|| npcData.ppp->getTaskName() == "SOIL TASK" || npcData.ppp->getTaskName() == "FIRE TASK" 
					|| npcData.ppp->getTaskName() == "WOOD TASK") {
					player->Upgrade();														// �������
				}
				npcData.ppp->state = 2;														//displayDialogue(npcData.npcSprite, "congragulations��");
			}
		}},
		{"LATER", nullptr}
		});
}

cocos2d::Scene* MiniMap::getSceneByName(const std::string& sceneName) {
	if (sceneName == "QuizGame")															// �����������QuizGame
	{
		return QuizGame::create();															// ���� Task1Scene ����
	}
	else if (sceneName == "BattleScene")													// �����������BattleScene
	{
		return BattleScene::create();														// ���� Task2Scene ����
	}
	else
		return BattleScene::create();														// ���� Task2Scene ����
}

/*���������*/ 
void MiniMap::StopListening()
{
	if (keyboardListener) {
		_eventDispatcher->removeEventListener(keyboardListener);							// �Ƴ�������
		keyboardListener = nullptr;															// ���ü�����
	}
}

void MiniMap::openBackpack()																// �򿪱���
{
	auto _backpack = new Backpack();														// ��������
	auto _backpack_num = new Backpack();													// ��������
	const auto& backpack1 = GlobalManager::getInstance().getArmors();						// ��ȡ����1
	const auto& backpack2 = GlobalManager::getInstance().getFoods();						// ��ȡ����2
	const auto& backpack3 = GlobalManager::getInstance().getMaterials();					// ��ȡ����3
	const auto& backpack4 = GlobalManager::getInstance().getWeapons();						// ��ȡ����4

	for (auto back1 : backpack1) {															// ��������1
		if (back1->isPicked) {																// ����Ѿ�ʰȡ
			_backpack->_items.push_back({ back1->num,back1->name });						// ��ӵ�����
		}
	}
	for (auto back2 : backpack2) {															// ��������2
		if (back2->isPicked) {																// ����Ѿ�ʰȡ
			_backpack->_items.push_back({ back2->num,back2->name });						// ��ӵ�����
		}
	}
	for (auto back3 : backpack3) {															// ��������3
		if (back3->isPicked) {																// ����Ѿ�ʰȡ
			_backpack->_items.push_back({ back3->num,back3->name });						// ��ӵ�����
		}
	}
	for (auto back4 : backpack4) {															// ��������4
		if (back4->isPicked) {																// ����Ѿ�ʰȡ
			_backpack->_items.push_back({ back4->num,back4->name });						// ��ӵ�����
		}
	}
	 
	auto backpackLayer = BackpackLayer::create();											// ���������㣬���ñ�������
	backpackLayer->setBackpack(_backpack);													// ���ñ�������
	this->addChild(backpackLayer, 10);														// ��ӱ����㵽���������ò㼶���
}

/*�������Ƿ񿿽���Ʒ��ִ��ʰȡ����*/ 
void MiniMap::checkPickUpItems()
{
	auto& item_ = GlobalManager::getInstance().getFoods();									// ��ȡʳ��
	auto& item_1 = GlobalManager::getInstance().getMaterials();								// ��ȡ����

	CCLOG("Checking for nearby items...");													// �����Ϣ

	for (auto it = goldoreItems.begin(); it != goldoreItems.end(); )						// �������
	{
		auto& item = *it;																	// ��ȡ��Ʒ
		auto itemSprite = item.itemSprite;													// ��ȡ��Ʒ����
		bool isNear = IsColliding(itemSprite->getPosition() + itemNode->getPosition());		// ����Ƿ񿿽���Ʒ

		if (isNear)
		{
			/*����ʰȡ����*/ 
			PickUpInteraction(&item);														// ʰȡ����					
			item_1[item.index]->num++;														// ��Ʒ������1
			item_1[item.index]->isPicked = 1;												// ������Ʒ��ʰȡ
			it = goldoreItems.erase(it);													// ɾ����ǰ��Ʒ�����µ�����

			/* �ӵ�ͼ���Ƴ���Ʒ*/
			itemSprite->setVisible(false);													// ������Ʒͼ��
			CCLOG("Picked up GoldOre Item with ID: %d", item.id);							// �����Ϣ

			break;																			// һ��ʰȡ���˳�ѭ��
		}
		else
		{
			++it;  // ���û�п�����Ʒ�����������һ����Ʒ
		}
	}

	for (auto it = appleItems.begin(); it != appleItems.end(); )							// ����ƻ��
	{
		auto& item = *it;																	// ��ȡ��Ʒ
		auto itemSprite = item.itemSprite;													// ��ȡ��Ʒ����
		bool isNear = IsColliding(itemSprite->getPosition() + itemNode->getPosition());		// ����Ƿ񿿽���Ʒ

		if (isNear)																			// ���������Ʒ,ִ��ʰȡ����
		{
			PickUpInteraction(&item);														// ʰȡ����
			item_[item.index]->num++;														// ��Ʒ������1
			item_[item.index]->isPicked = 1;												// ������Ʒ��ʰȡ

			it = appleItems.erase(it);														// ����Ʒ������ɾ���Ѿ�ʰȡ����Ʒ, 
																							// ɾ����ǰ��Ʒ�����µ�����

			/*�ӵ�ͼ���Ƴ���Ʒ*/ 
			itemSprite->setVisible(false);													// ������Ʒͼ��
			CCLOG("Picked up GoldOre Item with ID: %d", item.id);							// �����Ϣ

			break;																			// һ��ʰȡ���˳�ѭ��												
		}
		else
		{
			++it;																			// ���û�п�����Ʒ�����������һ����Ʒ
		}
	}
}

void MiniMap::PickUpInteraction(ItemList* item)												// ʰȡ����
{
	// ��ʾʰȡ��ʾ
	auto label = Label::createWithTTF("You picked up !", "fonts/arial.ttf", 100);			// ������ǩ
	auto visibleSize = Director::getInstance()->getVisibleSize();							// ��ȡ�ɼ���С
	label->setColor(Color3B::YELLOW);														// ʹ��Ԥ����Ļ�ɫ
	label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));				// ����λ��
	this->addChild(label);																	// ��ӵ�����
	label->runAction(Sequence::create(														// ���ж�������
		FadeOut::create(2.0f),																// ����
		RemoveSelf::create(),																// �Ƴ�����
		nullptr));																			// ��ָ��
}

void MiniMap::onEnter() {
	Scene::onEnter();																		// ������ø����ʵ��
	CCLOG("SimpleSceneA onEnter");															// �����Ϣ
	/*�������ű���*/
	float scaleX = 3.0f;																	// ����X�����ű���
	float scaleY = 3.0f;																	// ����Y�����ű���
	
	auto tileSize = tiledMap->getTileSize();												// ��ȡ��Ƭ��ͼ��Ƭ��С

	// ������Ƭ���ź��С
	auto playerSize = tileSize;																// ������Ҵ�С
	playerSize.width *= scaleX * 2;															// ������ҿ��
	playerSize.height *= scaleY * 2;														// ������Ҹ߶�

	player->initWithFile(player->getFileName());											// �������ؾ���ͼ��
	player->setContentSize(playerSize);														// �������ؾ����С
	player->Sprite::setPosition(playerPos);													// �������ؾ���λ��
	player->setVisible(true);																// �������ؾ���ɼ�
	player->setLocalZOrder(255);															// �������ؾ���㼶
	this->resume();																			// ��������ӳ����ָ�ʱ��Ҫִ�еĴ���
}

void MiniMap::onEnterTransitionDidFinish() {
	Scene::onEnterTransitionDidFinish();													// ������ø����ʵ��
	CCLOG("SimpleSceneA onEnterTransitionDidFinish");										// �����Ϣ
	/*�������ű���*/
	float scaleX = 3.0f;																	// ����X�����ű���
	float scaleY = 3.0f;																	// ����Y�����ű���
	auto tileSize = tiledMap->getTileSize();												// ��ȡ��Ƭ��ͼ��Ƭ��С

	/*������Ƭ���ź��С*/ 
	auto playerSize = tileSize;																// ������Ҵ�С					
	playerSize.width *= scaleX * 2;															// ������ҿ��
	playerSize.height *= scaleY * 2;														// ������Ҹ߶�
	 
	player->initWithFile(player->getFileName());											// �������ؾ���ͼ�� 
	player->setContentSize(playerSize);														// �������ؾ����С
	player->setPosition(playerPos);															// �������ؾ���λ��
	player->setVisible(true);																// �������ؾ���ɼ�
	player->setLocalZOrder(255);															// �������ؾ���㼶
	this->resume();																			// ��������ӳ����ָ�ʱ��Ҫִ�еĴ���
}

void MiniMap::restorePositionsAfterPop()
{
	auto player = GlobalManager::getInstance().getPlayer();									// ��ȡ���
	player->setPosition(preposition);														// �������λ��
	player->Sprite::setPosition(preposition);												// �������λ��
}
// ��֤����λ��
void MiniMap::verifySprites() {};