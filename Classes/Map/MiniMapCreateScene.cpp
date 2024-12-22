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
	CCLOG("MiniMap::createWithMap - Start"); 
	MiniMap* scene = new(std::nothrow) MiniMap(mapFile,fly);
	if (scene && scene->initWithMap(mapFile)) {
		scene->autorelease();
		scene->isFly = fly;
		scene->mapName = mapFile;

		CCLOG("MiniMap::createWithMap - Map file: %s, Fly: %d", mapFile.c_str(), fly);

																									// �ڳ�ʼ����ɺ󴴽�����˵�
		scene->createTaskMenu();																	// �����������˵��Ĵ�������
		CCLOG("MiniMap::createWithMap - Task menu created");

																									// ��������Ӵ��ͼ��ť
		auto bigMapButton = cocos2d::MenuItemImage::create(
			"CloseNormal.png",																		// ��ť������״̬ͼ��
			"CloseSelected.png",																	// ��ť��ѡ��״̬ͼ��
			[=](Ref* sender) {
				const auto& taskListmap = GlobalManager::getInstance().getTasks();
				
				if (taskListmap[5]->state >= 1)
				{
					auto bigMapScene = Setting6::createScene();
					/*
					if (bigMapScene) {
						this->addChild(bigMapScene);
						CCLOG("MiniMap::createBigMap - Big map scene added to MiniMap");
					}
					else {
						CCLOG("MiniMap::createBigMap - Failed to create big map scene");
					}
					*/
					cocos2d::Director::getInstance()->replaceScene(bigMapScene);
				}
				else if (taskListmap[4]->state >= 1)
				{
					auto bigMapScene = Setting5::createScene();
					/*
					if (bigMapScene) {
						this->addChild(bigMapScene);
						CCLOG("MiniMap::createBigMap - Big map scene added to MiniMap");
					}
					else {
						CCLOG("MiniMap::createBigMap - Failed to create big map scene");
					}
					*/
					cocos2d::Director::getInstance()->replaceScene(bigMapScene);
				}
				else if (taskListmap[3]->state >= 1)
				{
					auto bigMapScene = Setting4::createScene();
					/*
					if (bigMapScene) {
						this->addChild(bigMapScene);
						CCLOG("MiniMap::createBigMap - Big map scene added to MiniMap");
					}
					else {
						CCLOG("MiniMap::createBigMap - Failed to create big map scene");
					}
					*/
					cocos2d::Director::getInstance()->replaceScene(bigMapScene);
				}
				else if (taskListmap[2]->state >= 1)
				{
					auto bigMapScene = Setting3::createScene();
					/*
					if (bigMapScene) {
						this->addChild(bigMapScene);
						CCLOG("MiniMap::createBigMap - Big map scene added to MiniMap");
					}
					else {
						CCLOG("MiniMap::createBigMap - Failed to create big map scene");
					}
					*/
					cocos2d::Director::getInstance()->replaceScene(bigMapScene);
				}
				else if (taskListmap[1]->state >=1)
				{
					auto bigMapScene = Setting2::createScene();
					/*if (bigMapScene) {
						this->addChild(bigMapScene);
						CCLOG("MiniMap::createBigMap - Big map scene added to MiniMap");
					}
					else {
						CCLOG("MiniMap::createBigMap - Failed to create big map scene");
					}
					*/
					cocos2d::Director::getInstance()->replaceScene(bigMapScene);
				}// �л������ͼ����
				else
				{
					auto bigMapScene = Setting::createScene();
					/*if (bigMapScene) {
						this->addChild(bigMapScene);
						CCLOG("MiniMap::createBigMap - Big map scene added to MiniMap");
					}
					else {
						CCLOG("MiniMap::createBigMap - Failed to create big map scene");
					}
					*/
					cocos2d::Director::getInstance()->replaceScene(bigMapScene);
				}// �л������ͼ����

				//cocos2d::Director::getInstance()->replaceScene(bigMapScene);
			}
		);

		auto switchMap = cocos2d::Menu::create(bigMapButton, nullptr);
		switchMap->setPosition(cocos2d::Director::getInstance()->getVisibleSize().width / 2 -950, 
			cocos2d::Director::getInstance()->getVisibleSize().height / 2+450);
		scene->addChild(switchMap);

		AudioManager::getInstance().playIntroMusic();

		CCLOG("MiniMap::createWithMap - Big map button added to menu");
		
		return scene;
	}

	CCLOG("MiniMap::createWithMap - Failed to create scene");
	CC_SAFE_DELETE(scene);
	return nullptr;
}

void MiniMap::createTaskMenu()
{
	CCLOG("MiniMap::createTaskMenu - Start");
	auto taskMenu = TaskMenu::create();
	this->addChild(taskMenu, 1);
	CCLOG("MiniMap::createTaskMenu - Task menu added");
}

void MiniMap::createBigMap()
{
	CCLOG("MiniMap::createBigMap - Start");
	// ֱ�ӵ���Setting::createScene()���������ͼ����
	const auto& taskListmap = GlobalManager::getInstance().getTasks();
	//taskListmap[4]->state = 0;
	if (taskListmap[4]->state == 1)
	{
		auto bigMapScene = Setting5::createScene();
		if (bigMapScene) {
			this->addChild(bigMapScene);
			CCLOG("MiniMap::createBigMap - Big map scene added to MiniMap");
		}
		else {
			CCLOG("MiniMap::createBigMap - Failed to create big map scene");
		}
	}
	 else if (taskListmap[4]->state == 1)
	{
		auto bigMapScene = Setting5::createScene();
		if (bigMapScene) {
			this->addChild(bigMapScene);
			CCLOG("MiniMap::createBigMap - Big map scene added to MiniMap");
		}
		else {
			CCLOG("MiniMap::createBigMap - Failed to create big map scene");
		}
	}
	else if (taskListmap[3]->state == 1)
	{
		auto bigMapScene = Setting4::createScene();
		if (bigMapScene) {
			this->addChild(bigMapScene);
			CCLOG("MiniMap::createBigMap - Big map scene added to MiniMap");
		}
		else {
			CCLOG("MiniMap::createBigMap - Failed to create big map scene");
		}
	}
	else if (taskListmap[2]->state == 1)
	{
		auto bigMapScene = Setting3::createScene();
		if (bigMapScene) {
			this->addChild(bigMapScene);
			CCLOG("MiniMap::createBigMap - Big map scene added to MiniMap");
		}
		else {
			CCLOG("MiniMap::createBigMap - Failed to create big map scene");
		}
	}
	else if (taskListmap[1]->state == 1)
	{
		auto bigMapScene = Setting2::createScene();
		if (bigMapScene) {
			this->addChild(bigMapScene);
			CCLOG("MiniMap::createBigMap - Big map scene added to MiniMap");
		}
		else {
			CCLOG("MiniMap::createBigMap - Failed to create big map scene");
		}
	}
	else 
	{
		auto bigMapScene = Setting::createScene();
		if (bigMapScene) {
			this->addChild(bigMapScene);
			CCLOG("MiniMap::createBigMap - Big map scene added to MiniMap");
		}
		else {
			CCLOG("MiniMap::createBigMap - Failed to create big map scene");
		}
	}
	
}

void MiniMap::createBackpack()
{
	CCLOG("MiniMap::createBackpack - Start");

	// ����һ�� BackpackLayer ʵ��
	BackpackLayer* backpackLayer = BackpackLayer::create();  // ����ʵ��

	if (backpackLayer) {

		this->getParent()->addChild(backpackLayer);
		CCLOG("MiniMap::createBigMap - Big map scene added to MiniMap");
	}
	else {
		CCLOG("MiniMap::createBigMap - Failed to create big map scene");
	}
}

bool MiniMap::initWithMap(const std::string& mapFile)
{

	if (!Scene::init()) {
		return false;
	}
	mapfile = mapFile;
	auto backpackButton = ui::Button::create("backpack.png");                                                // ʹ�����Լ���ͼ��
	backpackButton->setPosition(Vec2(cocos2d::Director::getInstance()->getVisibleSize().width / 2 + 825,
		cocos2d::Director::getInstance()->getVisibleSize().height / 2 + 150));                               // ��ťλ��
	backpackButton->addClickEventListener([this](Ref* sender) {
		this->openBackpack();
		                                                                                                     // ����һ�� BackpackLayer ���󲢽�����ӵ���ǰ������
		BackpackLayer* backpackLayer = BackpackLayer::create();                                              // ����ʵ��
		if (backpackLayer) {
			                                                                                                 // ����������ӵ���ǰ������
			Director::getInstance()->getRunningScene()->addChild(backpackLayer);                             // ����������ӵ���ǰ����
		}
		});

	// ��������ť��ӵ�������
	this->addChild(backpackButton, 1);                                       
	// ��ȡ��ǰ��������Ĵ�С
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	// ��ȡ��ǰ��������ԭ������
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	// ��ȡ��ͼ
	tiledMap = cocos2d::TMXTiledMap::create(mapFile);
	if (!tiledMap) {
		CCLOG("noMap");
		return false;
	}

	// ��ʼ�����
	auto objectGroup = tiledMap->getObjectGroup("Objects");
	auto ojectGroup = tiledMap->getObjectGroup("TransportPoint");
	auto boxGroup = tiledMap->getObjectGroup("Boxs");
	auto playerObj = objectGroup->getObject("Player");
	auto kingObj = objectGroup->getObject("King");


	float playerX = playerObj["x"].asFloat();
	float playerY = playerObj["y"].asFloat();


	//�������ű���
	float scaleX = 3.0f;
	float scaleY = 3.0f;

	// ���ص�ͼ
	tiledMap->setScale(scaleX, scaleY);
	// ��ȡ��ǰ��Ƭ��ͼ��С
	cocos2d::Size mapSize = tiledMap->getMapSize();
	// ��ȡ��Ƭ��ͼ��Ƭ��С
	auto tileSize = tiledMap->getTileSize();
	// ������Ƭ���ź��С
	auto playerSize = tileSize;
	playerSize.width *= scaleX*2;
	playerSize.height *= scaleY*2;

	// �������ؾ���
	player->initWithFile(player->getFileName());
	// �������ؾ����С
	player->setContentSize(playerSize);
	
	// ��ȡ���ؾ�����Ҫ������߼�����
	float bornPointX = 0.0f, bornPointY = 0.0f;

	// ���������
	auto transportPoint = (isFly == true ? tiledMap->getObjectGroup("TransportPoint") : tiledMap->getObjectGroup("Boat"));

	// ��ȡ����λ�õ��߼�����
	if (transportPoint) {
		auto transportObject = (isFly == true ? transportPoint->getObject("Fly") : transportPoint->getObject("Boat"));
		bornPointX = transportObject["x"].asFloat();
		bornPointY = transportObject["y"].asFloat();
	}

	if (!bornPointX && !bornPointY)
		CCLOG("noBornPoint");

	// �������ؾ������������
	auto bornWorld = tiledMap->convertToWorldSpace(cocos2d::Vec2(bornPointX, bornPointY));

	// �����Ӵ����ĵ���������
	cocos2d::Vec2 centerWorldPosition = cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 2);

	// ��ȡƫ����
	cocos2d::Vec2 offset = centerWorldPosition - bornWorld + cocos2d::Vec2(0.0f, -tileSize.height * scaleY);

	// ����ƫ�������Է��߽�������Ӵ��ڲ�
	if (offset.x > 0)
		offset.x = 0;
	else if (offset.x + mapSize.width * tileSize.width * scaleX < visibleSize.width)
		offset.x = visibleSize.width - mapSize.width * tileSize.width * scaleX;
	if (offset.y > 0)
		offset.y = 0;
	else if (offset.y + mapSize.height * tileSize.height * scaleY < visibleSize.height)
		offset.y = visibleSize.height - mapSize.height * tileSize.height * scaleY;

	// �������ؾ���λ��
	playerPos = offset + bornWorld - cocos2d::Vec2(0.0f, -tileSize.height * scaleY);

	// �������ؾ���λ��
	player->setPosition(playerPos);

	// ���õ�ͼλ��
	tiledMap->setPosition(offset);

	// �Ѿ�����ӵ�����
	this->addChild(tiledMap);
	//if (mapName == "smallmap/battlefeild.tmx")
		//this->removeAllChildren();
	// �ѵ�ͼ��ӵ�����
	this->addChild(player.get(),9);
	npcNode = Node::create();
	this->addChild(npcNode);
	itemNode = Node::create();
	this->addChild(itemNode);

	float kingX = kingObj["x"].asFloat();
	float kingY = kingObj["y"].asFloat();
	auto king = cocos2d::Sprite::create("king.png");
	king->setPosition(kingX, kingY);
	npcNode->addChild(king, 9);
	king->setContentSize(playerSize);

	const auto& taskList = GlobalManager::getInstance().getTasks();
	// ��ʼ�� NPC ���������ͷ���
	auto npcGroup = objectGroup->getObjects();

	// ��ȡ�ɽ����������
	auto objectGroup1 = tiledMap->getObjectGroup("GoldOre");
	if (objectGroup1 == nullptr) {
		CCLOG("Error: Object group 'GoldOre' not found!");
	}
	auto goldoreLayer = objectGroup1->getObjects();
	if (goldoreLayer.empty()) {
		CCLOG("Error: No objects found in 'GoldOre' object group!");
	}

	for (const auto& object : goldoreLayer)
	{
		cocos2d::ValueMap goldoreProperties = object.asValueMap();

		// ��������Ƿ����
		if (goldoreProperties.count("id") == 0 || goldoreProperties.count("x") == 0 || goldoreProperties.count("y") == 0) {
			CCLOG("Error: Missing required properties for GoldOre object!");
			// �����������
			continue;  
		}

		auto goldoreID = goldoreProperties["id"].asInt();
		auto x = goldoreProperties["x"].asFloat();
		auto y = goldoreProperties["y"].asFloat();

		CCLOG("GoldOre Object ID: %d at Position: (%f, %f)", goldoreID, x, y);
		
		auto goldore = cocos2d::Sprite::create("smallmap/GoldOre.png");
		// �洢��ײ��������ݣ�׼������ʹ��
		goldoreItems.push_back({ goldore,3, goldoreID, Vec2(x, y) });

		cocos2d::Vec2 itemPos = tiledMap->convertToWorldSpace(cocos2d::Vec2(x, y));
		goldore->setPosition(itemPos);

		// ȷ�� itemNode �Ѿ���ʼ��
		if (itemNode) {  
			itemNode->addChild(goldore);
		}
		else {
			CCLOG("Error: itemNode is not initialized!");
		}
		this->scheduleUpdate();
	}

	// ��ȡ�ɽ���ƻ�������
	auto appleGroup1 = tiledMap->getObjectGroup("Apple");
	if (appleGroup1 == nullptr) {
		CCLOG("Error: Object group 'GoldOre' not found!");
	}
	auto appleLayer = appleGroup1->getObjects();
	if (appleLayer.empty()) {
		CCLOG("Error: No objects found in 'GoldOre' object group!");
	}

	for (const auto& object : appleLayer)
	{
		cocos2d::ValueMap appleProperties = object.asValueMap();

		// ��������Ƿ����
		if (appleProperties.count("id") == 0 || appleProperties.count("x") == 0 || appleProperties.count("y") == 0) {
			CCLOG("Error: Missing required properties for GoldOre object!");
			// �����������
			continue;
		}

		auto appleID = appleProperties["id"].asInt();
		auto x = appleProperties["x"].asFloat();
		auto y = appleProperties["y"].asFloat();

		CCLOG("GoldOre Object ID: %d at Position: (%f, %f)", appleID, x, y);

		auto apple = cocos2d::Sprite::create("Maze/apple.png");
		// �洢��ײ��������ݣ�׼������ʹ��
		appleItems.push_back({ apple,7, appleID, Vec2(x, y) });

		cocos2d::Vec2 itemPos = tiledMap->convertToWorldSpace(cocos2d::Vec2(x, y));
		apple->setPosition(itemPos);

		// ȷ�� itemNode �Ѿ���ʼ��
		if (itemNode) {
			itemNode->addChild(apple);
		}
		else {
			CCLOG("Error: itemNode is not initialized!");
		}
		this->scheduleUpdate();
	}

	int i = 0;

	for (auto& npcObj : npcGroup)
	{
		cocos2d::ValueMap npcData = npcObj.asValueMap();
		if (!npcData.empty()) {
			auto task = taskList[i];

			int indexnpc = 0;
			int indexmon = 0;
			std::string npcFunction = npcData["npcFunction"].asString();
			std::string targetScene = npcData["targetScene"].asString();
			std::string type = npcData["type"].asString();
			indexnpc = npcData["index"].asInt();
			if (type == "shopkeeper") {
				int indexp = npcData["indexp"].asInt();
				auto npc = cocos2d::Sprite::create(std::to_string(indexp)+"NPC.png");
				cocos2d::Vec2 npcPos = tiledMap->convertToWorldSpace(cocos2d::Vec2(npcData["x"].asFloat(), npcData["y"].asFloat()));
				npc->setPosition(npcPos);
				npc->setContentSize(playerSize);
				npcNode->addChild(npc);
				_npcList.push_back({ npc, npcFunction, indexnpc,taskList[indexnpc],indexnpc,targetScene });
			}
			if (type == "NPC") {
				auto npc = cocos2d::Sprite::create("4NPC.png");
				cocos2d::Vec2 npcPos = tiledMap->convertToWorldSpace(cocos2d::Vec2(npcData["x"].asFloat(), npcData["y"].asFloat()));
				npc->setPosition(npcPos);
				npc->setContentSize(playerSize);
				npcNode->addChild(npc);
				// �Ի���NPC
				if (npcFunction == "chat")
					_npcList.push_back({ npc, npcFunction, indexnpc,taskList[indexnpc],indexnpc,targetScene });
				if (npcFunction == "quest")
					_npcList.push_back({ npc, npcFunction, indexnpc,taskList[indexnpc],indexnpc,targetScene });
				
			}
			else if (type == "box") {
				auto npc = cocos2d::Sprite::create("smallmap/boxlqy.png");
				auto pos = tiledMap->convertToWorldSpace(cocos2d::Vec2(npcData["x"].asFloat(), npcData["y"].asFloat()));
				npc->setPosition(pos);
				npc->setContentSize(playerSize);
				npcNode->addChild(npc);
				// ������NPC
				_npcList.push_back({ npc, npcFunction,indexnpc, taskList[indexnpc],indexnpc,targetScene });
				
			}
			else if (type == "monster") {
				indexmon = npcData["indexmon"].asInt();
				std::string mapf;
				if (mapFile == "smallmap/whole3.tmx")
					mapf = "whole3";
				else if (mapFile == "smallmap/gold1.tmx")
					mapf = "gold1";
				else if (mapFile == "smallmap/earth.tmx")
					mapf = "earth";	
				else if (mapFile == "smallmap/fire.tmx")
					mapf = "fire";
				else if (mapFile == "smallmap/wood.tmx")
					mapf = "wood";
				auto npc = cocos2d::Sprite::create(mapf + "monster" + std::to_string(indexmon+1)+".png");
				npc->setContentSize(playerSize);
				auto pos = tiledMap->convertToWorldSpace(cocos2d::Vec2(npcData["x"].asFloat(), npcData["y"].asFloat()));
				npc->setPosition(pos);
				
				npcNode->addChild(npc);
				
				_npcList.push_back({ npc, npcFunction, indexmon,taskList[indexnpc],indexnpc,targetScene });
				
			}
		}
		this->scheduleUpdate();
	}

	// ���ü����¼�������
	StartListening();

	return true;
}

// ���ü����¼�������
void MiniMap::StartListening()
{
	// ȷ��û���ظ���Ӽ�����
	if (!keyboardListener) { 
		keyboardListener = cocos2d::EventListenerKeyboard::create();                        		// ��������������¼�������
		keyboardListener->onKeyPressed = CC_CALLBACK_2(MiniMap::OnKeyPressed, this);	        	// ���ü��̰����¼��Ļص�����
		keyboardListener->onKeyReleased = CC_CALLBACK_2(MiniMap::OnKeyReleased, this);		        // ���ü����ͷ��¼��Ļص�����
		_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);		    // ��ӵ��¼���������
	}
}

// �������µĻص�����
void MiniMap::OnKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	switch (keyCode) {
	case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
	case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
	case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		GlobalManager::getInstance().getPlayer()->isMoving = true;
		UpdatePlayerPosition(keyCode);
		break;
	default:
		break;
	}
}

// �����߼�
bool MiniMap::IsColliding(cocos2d::Vec2 position)
{
	// ��ȡ���ؾ��鵱ǰ��������
	auto playerPos = player->getPosition();
	auto x = position.x, y = position.y;

	// ��ȡ��Ƭ��ͼ����Ƭ��С
	auto tileSize = tiledMap->getTileSize();
	
	// ������npc�����Ϊ���ĵ��ĸ���Ƭ��Χ�������Ҫ��С��������/2
	if (playerPos.x >= x - tileSize.width && playerPos.x <= x + tileSize.width && playerPos.y >= y - tileSize.height && playerPos.y <= y + tileSize.height) {
		CCLOG("Collide npc");
		return true;
	}
	return false;
}

void MiniMap::update(float delta)
{
	//createTaskMenu();

	for (auto& npcData : _npcList)
	{
		auto npc = npcData.npcSprite;

		if (npcNode) {
			bool iscod = IsColliding(npc->getPosition() + npcNode->getPosition());

			if (iscod && !_currentDialogueBox && !_currentChoiceBox && !npc->getUserData()) {
				CCLOG("WE ARE NPC");
				// ����ѽ���
				npc->setUserData((void*)1); 
				if (npcData.npcFunction == "chat")
				{
					displayChoice1(npc, "Can you talk with me?", {
						{"Yes", [this, npc]() { {
								// ��ʱ��ʾ��һ���Ի��򣬱����ڵ�
								this->scheduleOnce([=](float) {
									handleChatNPC(npc);
								}, 0.1f, "handleChatNPC");
							} }},
						{"No", nullptr}
						});
				}
				else if (npcData.npcFunction == "quest")
				{
					CCLOG("KKKKKKKKKKKKK");
					// ������NPC
					switch (npcData.ppp->state) {
						case -1:
							CCLOG("Task state before assignment: %d", npcData.ppp->state);
							// ��ʾ����ѡ�񵯴�
							displayTaskOptions(npcData); 
							break;
						case 0:
							// ��ӡ����״̬
							CCLOG("Task state before assignment: %d", npcData.ppp->state); 
							displayDialogue(npc, "YOU've DONE" + npcData.ppp->getTaskName());
							break;
						case 1:
							// ��ʾ������ȡ����
							displayRewardOptions(npcData); 
							break;
						case 2:
							displayDialogue(npc, "���Ѿ�������ҵ����񣬸�л��İ�����");
							break;
					}
				}
				else if (npcData.npcFunction == "questpro") {
					// ������NPC
					switch (npcData.ppp->state) {
						case -1:
							// ��ʾ����ѡ�񵯴�
							if (npcData.targetScene == "BattleScene") {
								if (mapfile == "smallmap/whole3.tmx") {
									const auto& MonList = GlobalManager::getInstance().getEnemyNpcsWater();
									GlobalManager::getInstance().setBattleNpc(MonList[npcData.index]);
								}
								if (mapfile == "smallmap/gold1.tmx") {
									const auto& MonList = GlobalManager::getInstance().getEnemyNpcsGold();
									GlobalManager::getInstance().setBattleNpc(MonList[npcData.index]);
								}
								if (mapfile == "smallmap/earth.tmx") {
									const auto& MonList = GlobalManager::getInstance().getEnemyNpcsEarth();
									GlobalManager::getInstance().setBattleNpc(MonList[npcData.index]);
								}
								if (mapfile == "smallmap/fire.tmx") {
									const auto& MonList = GlobalManager::getInstance().getEnemyNpcsFire();
									GlobalManager::getInstance().setBattleNpc(MonList[npcData.index]);
								}
								if (mapfile == "smallmap/wood.tmx") {
									const auto& MonList = GlobalManager::getInstance().getEnemyNpcsWood();
									GlobalManager::getInstance().setBattleNpc(MonList[npcData.index]);
								}
							}
							displayTaskPro(npcData); 
							break;
						case 0:
							// ��ӡ����״̬
							CCLOG("Task state before assignment: %d", npcData.ppp->state); 
							displayDialogue(npc, "YOU've DONE");
							break;
						case 1:
							// ��ʾ������ȡ����
							displayRewardOptions(npcData); 
							break;
						case 2:
							displayDialogue(npc, "thank you");
							break;
					}
				}
			}
			// �������� NPC û����ײ����֮ǰ�Ѿ��������������ý���״̬
			else if (!iscod && npc->getUserData() != nullptr)
			{
				// ���ý���״̬�������ٴδ���
				npc->setUserData(nullptr);
			}
		}
	}

	// ������Ʒ������Ƿ�������Ʒ
	for (auto it = goldoreItems.begin(); it != goldoreItems.end(); ++it)
	{
		auto item = it->itemSprite;

		// ��ӡ��Ʒ�����λ�ã������ײ��Χ
		CCLOG("Item position: (%f, %f)", item->getPosition().x, item->getPosition().y);
		CCLOG("Player position: (%f, %f)", player->getPosition().x, player->getPosition().y);

		bool iscod = IsColliding(item->getPosition() + itemNode->getPosition());
		if (iscod)
		{
			checkPickUpItems();
			// ����һ�ε��ֻ��ʰȡһ����Ʒ
			break; 
		}
	}

	// ������Ʒ������Ƿ�������Ʒ
	for (auto it = appleItems.begin(); it != appleItems.end(); ++it)
	{
		auto item = it->itemSprite;

		// ��ӡ��Ʒ�����λ�ã������ײ��Χ
		CCLOG("Item position: (%f, %f)", item->getPosition().x, item->getPosition().y);
		CCLOG("Player position: (%f, %f)", player->getPosition().x, player->getPosition().y);

		bool iscod = IsColliding(item->getPosition() + itemNode->getPosition());
		if (iscod)
		{
			checkPickUpItems();
			// ����һ�ε��ֻ��ʰȡһ����Ʒ
			break;
		}
	}
}

// �����ͷŵĻص�����
void MiniMap::OnKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	GlobalManager::getInstance().getPlayer()->isMoving = false;
}

void MiniMap::displayChoice1(cocos2d::Sprite* npc, const std::string& question,
	const std::vector<std::pair<std::string, std::function<void()>>>& choices)
{ 
	if (_currentChoiceBox) {																					           		  // ������ڵ�ǰ�Ի����Ƴ���
		_currentChoiceBox->removeFromParent();
		_currentChoiceBox = nullptr;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	_currentChoiceBox = cocos2d::Sprite::create("smallmap/box.png");
	//_currentChoiceBox->setPosition(npc->getPosition() + cocos2d::Vec2(0, 80)); 
	_currentChoiceBox->setPosition(Vec2(visibleSize.width / 2,  visibleSize.height / 2));
	this->addChild(_currentChoiceBox);
	_currentChoiceBox->setLocalZOrder(100);																        				 // �öԻ����ڽϸߵĲ㼶 
	auto label = cocos2d::Label::createWithTTF(question, "fonts/Marker Felt.ttf", 48);
	label->setTextColor(cocos2d::Color4B::WHITE);
	label->setPosition(_currentChoiceBox->getContentSize().width / 2, _currentChoiceBox->getContentSize().height / 2 + 100);
	_currentChoiceBox->addChild(label, 1);
	label->setLocalZOrder(101);

	float buttonY = 50;
	for (size_t i = 0; i < choices.size(); ++i)
	{
		cocos2d::ui::Button* button;
		if (i == 0) {
			button = cocos2d::ui::Button::create("Yes1.png", "Yes2.png");
		}
		else if(i==1){
			button = cocos2d::ui::Button::create("No1.png", "No2.png");
		}
		//button->setTitleText(choices[i].first);
		//button->setTitleFontName("fonts/Marker Felt.ttf");
		//button->setTitleFontSize(24);
		button->setPosition(cocos2d::Vec2(_currentChoiceBox->getContentSize().width / 4+ i * 300+30, _currentChoiceBox->getContentSize().height/4));
		_currentChoiceBox->addChild(button);

		button->addClickEventListener([=](cocos2d::Ref* sender) {
			if (choices[i].second) {
				choices[i].second();																						// ִ��ѡ���Ļص�
			}
																															// ��Ҫ�������Ƴ��Ի����������µĶԻ���
			if (_currentChoiceBox) {
				_currentChoiceBox->removeFromParent();
				_currentChoiceBox = nullptr;
			}

			});
	}
}

void MiniMap::handleChatNPC(cocos2d::Sprite* npc)
{

	// ��ʾ�µĶԻ���
	displayChoice2(npc, "Hello! How can I help you today?", {
		{"Tell me about the town", [this, npc]() { {
				// ��ʱ��ʾ��һ���Ի��򣬱����ڵ�
				this->scheduleOnce([=](float) {
					displayTownInfo(npc);
				}, 0.1f, "handleChatNPC");
			} }},
		{"I need a quest", [this, npc]() { {
				// ��ʱ��ʾ��һ���Ի��򣬱����ڵ�
				this->scheduleOnce([=](float) {
					displayQuestInfo(npc);
				}, 0.1f, "handleChatNPC");
			} }},
		{"Nothing, just passing by", [this, npc]() { {
				// ��ʱ��ʾ��һ���Ի��򣬱����ڵ�
				this->scheduleOnce([=](float) {
					displayGoodbye(npc);
				}, 0.1f, "handleChatNPC");
			} }},
	});
}

void MiniMap::displayChoice2(cocos2d::Sprite* npc, const std::string& question,
	const std::vector<std::pair<std::string, std::function<void()>>>& choices)
{
	// ȷ���ɶԻ������
	if (_currentChoiceBox) {
		_currentChoiceBox->removeFromParent();
		_currentChoiceBox = nullptr;
	}

	_currentChoiceBox = cocos2d::Sprite::create("smallmap/box3.png");
	auto visibleSize = Director::getInstance()->getVisibleSize();
	_currentChoiceBox->setPosition(Vec2(visibleSize.width / 2, 5*visibleSize.height / 6));
	this->addChild(_currentChoiceBox, 1);
	_currentChoiceBox->setLocalZOrder(100);

	auto label = cocos2d::Label::createWithTTF(question, "fonts/Marker Felt.ttf", 48);
	label->setTextColor(cocos2d::Color4B::BLACK);
	label->setPosition(_currentChoiceBox->getContentSize().width / 2, _currentChoiceBox->getContentSize().height / 2 - 30);
	_currentChoiceBox->addChild(label, 1);
	label->setLocalZOrder(101);

	float buttonY = 50;
	for (size_t i = 0; i < choices.size(); ++i)
	{
		auto button = cocos2d::ui::Button::create("button1.png", "button2.png");
		button->setTitleText(choices[i].first);
		button->setTitleFontName("fonts/Marker Felt.ttf");
		button->setTitleColor(cocos2d::Color3B::BLACK);
		button->setTitleFontSize(24);
		button->setPosition(cocos2d::Vec2(_currentChoiceBox->getContentSize().width / 2, buttonY + i * 150 -400));
		_currentChoiceBox->addChild(button);

		button->addClickEventListener([=](cocos2d::Ref* sender) {
			// ִ��ѡ���Ļص�
			if (choices[i].second) {
				choices[i].second(); 
			}
			// �ڻص������Ƴ��Ի���
			_currentChoiceBox->removeFromParent();
			_currentChoiceBox = nullptr;
			});
	}
}
// NPC �ش���ڳ�������
void MiniMap::displayTownInfo(cocos2d::Sprite* npc)
{
	displayChoice2(npc, "This is a peaceful town. You can find a shop,\n a tavern, and a blacksmith.", {
		{"I see, tell me more!", [this, npc]() { {
				// ��ʱ��ʾ��һ���Ի��򣬱����ڵ�
				this->scheduleOnce([=](float) {
					displayTownDetails(npc);
				}, 0.1f, "handleChatNPC");
			} }},
		{"That's enough, thanks!", [this, npc]() { displayGoodbye(npc); }}
	});
}

// NPC ��ϸ���ܳ���
void MiniMap::displayTownDetails(cocos2d::Sprite* npc)
{
	displayDialogue(npc, "The shop sells potions, the tavern offers drinks and rumors, and the blacksmith can upgrade your gear.");
}

// NPC ����������Ϣ
void MiniMap::displayQuestInfo(cocos2d::Sprite* npc)
{
	displayChoice2(npc, "I have a quest for you: Collect 10 herbs.", {

		{"Maybe later", [this, npc]() { displayGoodbye(npc); }},
		{"Tell me more", [this, npc]() { displayQuestDetails(npc); }}
	});
}

// NPC ��ϸ������Ϣ
void MiniMap::displayQuestDetails(cocos2d::Sprite* npc)
{
	displayDialogue(npc, "The herbs grow near the forest. \nPlease bring them back to me once you've collected them.");
}

// NPC ˵���ټ���
void MiniMap::displayGoodbye(cocos2d::Sprite* npc)
{
	displayDialogue(npc, "Goodbye, and good luck on your adventures!");
}

void MiniMap::displayDialogue(Sprite* npc, const std::string& text)
{
	// ������ڵ�ǰ�Ի����Ƴ���
	if (_currentDialogueBox) {
		_currentDialogueBox->removeFromParent();
		_currentDialogueBox = nullptr;
	}

	// �����Ի���
	auto dialogueBox = Sprite::create("smallmap/box3.png");
	if (!dialogueBox) {
		CCLOG("Failed to create dialogue box!");
		return;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();												// ��ȡ�ɼ�����Ĵ�С
	dialogueBox->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(dialogueBox);

	// �����ı���ǩ
	auto label = Label::createWithTTF(text, "fonts/Marker Felt.ttf", 24);
	label->setTextColor(Color4B::BLACK);
	label->setPosition(dialogueBox->getContentSize() / 2);
	dialogueBox->addChild(label);

	// ���õ�ǰ�Ի���
	_currentDialogueBox = dialogueBox;

	// �Զ���ʧ�Ի���
	this->scheduleOnce([=](float) {
		dialogueBox->removeFromParent();
		_currentDialogueBox = nullptr;
		}, 3.0f, "closeDialogue");
}

void MiniMap::displayTaskOptions(NPCData& npcData) {
	displayChoice1(npcData.npcSprite, npcData.ppp->getTaskName(), {
		{"YES", [this, &npcData]() {
			// ��������״̬Ϊ�ѷ���
			npcData.ppp->state = 0; 
			createTaskMenu();
			// չʾ�Ի���
			displayDialogue(npcData.npcSprite, npcData.ppp->getTaskDescription());
		}},
		{"NO", nullptr}
	});
}

void MiniMap::displayTaskPro(NPCData& npcData) {
	displayChoice1(npcData.npcSprite, npcData.ppp->getTaskName(), {
		{"YES", [this, &npcData]() {
			// ��������״̬Ϊ�ѷ���
			npcData.ppp->state = 0; 
			// ��ת�� NPC ���õ�Ŀ�곡��
			CCLOG("message", npcData.targetScene);
			player->removeFromParent();
			GlobalManager::getInstance().setLastMap(mapName);
			const auto& taskListbat = GlobalManager::getInstance().getTasks();
			taskListbat[0]->id= npcData.taskid;
			Director::getInstance()->replaceScene(TransitionFade::create(1.0f, getSceneByName(npcData.targetScene)));
			npcData.ppp->state = 1;
		
		}},
		{"NO", nullptr}
	});
}

void MiniMap::displayTaskStatus(NPCData& npcData) {
	displayDialogue(npcData.npcSprite, "TASK");
}

void MiniMap::displayRewardOptions(NPCData& npcData) {
	displayChoice1(npcData.npcSprite, npcData.ppp->getTaskReward(), {
		{"OF COURSE", [this, &npcData]() {
			if (npcData.ppp->state == 1) {
				// �����������ȡ����
				if (npcData.ppp->getTaskName() == "WATER TASK"|| npcData.ppp->getTaskName() == "GOLD TASK"|| npcData.ppp->getTaskName() == "SOIL TASK"|| npcData.ppp->getTaskName() == "FIRE TASK"|| npcData.ppp->getTaskName() == "WOOD TASK") {

					player->Upgrade();
				}
			
				npcData.ppp->state = 2; 
				//displayDialogue(npcData.npcSprite, "congragulations��");
			}
		}},
		{"LATER", nullptr}
	});
}

cocos2d::Scene* MiniMap::getSceneByName(const std::string& sceneName) {
	if (sceneName == "QuizGame")
	{
		return QuizGame::create();                                          // ���� Task1Scene ����
	}
	else if (sceneName == "BattleScene")
	{
		return BattleScene::create();                                       // ���� Task2Scene ����
	}
	else
		return BattleScene::create();
}

// ���������
void MiniMap::StopListening()
{
	if (keyboardListener) {
		_eventDispatcher->removeEventListener(keyboardListener);
		// ���ָ��
		keyboardListener = nullptr; 
	}
}

void MiniMap::openBackpack()
{
	auto _backpack = new Backpack();
	auto _backpack_num = new Backpack();
	const auto& backpack1 = GlobalManager::getInstance().getArmors();
	const auto& backpack2 = GlobalManager::getInstance().getFoods();
	const auto& backpack3 = GlobalManager::getInstance().getMaterials();
	const auto& backpack4 = GlobalManager::getInstance().getWeapons();

	for (auto back1 : backpack1) {
		if (back1->isPicked) {
			_backpack->_items.push_back({ back1->num,back1->name });
		}
	}
	for (auto back2 : backpack2) {
		if (back2->isPicked) {
			_backpack->_items.push_back({ back2->num,back2->name });
		}
	}
	for (auto back3 : backpack3) {
		if (back3->isPicked) {
			_backpack->_items.push_back({ back3->num,back3->name });
		}
	}
	for (auto back4 : backpack4) {
		if (back4->isPicked) {
			_backpack->_items.push_back({ back4->num,back4->name });
		}
	}

	// ���������㲢���ñ�������
	auto backpackLayer = BackpackLayer::create();
	// ���������ݴ��ݸ�������
	backpackLayer->setBackpack(_backpack);  

	// ����������ӵ�������
	// �� z-order ȷ��������ʾ���ϲ�
	this->addChild(backpackLayer, 10);  
}

// �������Ƿ񿿽���Ʒ��ִ��ʰȡ����
void MiniMap::checkPickUpItems()
{
	auto& item_ = GlobalManager::getInstance().getFoods();
	auto& item_1 = GlobalManager::getInstance().getMaterials();

	// ��¼����˺�������־
	CCLOG("Checking for nearby items...");  

	for (auto it = goldoreItems.begin(); it != goldoreItems.end(); )
	{
		auto& item = *it;
		auto itemSprite = item.itemSprite;

		// �������Ƿ񿿽���Ʒ
		bool isNear = IsColliding(itemSprite->getPosition() + itemNode->getPosition());

		if (isNear)
		{
			// ����ʰȡ����
			PickUpInteraction(&item);
			item_1[item.index]->num++;
			item_1[item.index]->isPicked = 1;

			// ����Ʒ������ɾ���Ѿ�ʰȡ����Ʒ
			it = goldoreItems.erase(it);  // ɾ����ǰ��Ʒ�����µ�����

			// �ӵ�ͼ���Ƴ���Ʒ
			itemSprite->setVisible(false);  // ������Ʒͼ��
			CCLOG("Picked up GoldOre Item with ID: %d", item.id);

			// һ��ʰȡ���˳�ѭ��
			break;
		}
		else
		{
			++it;  // ���û�п�����Ʒ�����������һ����Ʒ
		}
	}

	for (auto it = appleItems.begin(); it != appleItems.end(); )
	{
		auto& item = *it;
		auto itemSprite = item.itemSprite;

		// �������Ƿ񿿽���Ʒ
		bool isNear = IsColliding(itemSprite->getPosition() + itemNode->getPosition());

		if (isNear)
		{
			// ����ʰȡ����
			PickUpInteraction(&item);
			item_[item.index]->num++;
			item_[item.index]->isPicked = 1;

			// ����Ʒ������ɾ���Ѿ�ʰȡ����Ʒ
			it = appleItems.erase(it);  // ɾ����ǰ��Ʒ�����µ�����

			// �ӵ�ͼ���Ƴ���Ʒ
			itemSprite->setVisible(false);  // ������Ʒͼ��
			CCLOG("Picked up GoldOre Item with ID: %d", item.id);

			// һ��ʰȡ���˳�ѭ��
			break;
		}
		else
		{
			++it;  // ���û�п�����Ʒ�����������һ����Ʒ
		}
	}
}

void MiniMap::PickUpInteraction(ItemList* item)
{
	// ��ʾʰȡ��ʾ
	auto label = Label::createWithTTF("You picked up !", "fonts/arial.ttf", 100);
	auto visibleSize = Director::getInstance()->getVisibleSize();
	label->setColor(Color3B::YELLOW);  // ʹ��Ԥ����Ļ�ɫ
	label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(label);
	label->runAction(Sequence::create(
		FadeOut::create(2.0f),
		RemoveSelf::create(),
		nullptr));
}

void MiniMap::onEnter() {
	Scene::onEnter();  // ������ø����ʵ��
	CCLOG("SimpleSceneA onEnter");
	//�������ű���
	float scaleX = 3.0f;
	float scaleY = 3.0f;
	// ��ȡ��Ƭ��ͼ��Ƭ��С
	auto tileSize = tiledMap->getTileSize();

	// ������Ƭ���ź��С
	auto playerSize = tileSize;
	playerSize.width *= scaleX * 2;
	playerSize.height *= scaleY * 2;

	// �������ؾ���
	player->initWithFile(player->getFileName());
	// �������ؾ����С
	player->setContentSize(playerSize);
	player->Sprite::setPosition(playerPos);
	player->setVisible(true);
	player->setLocalZOrder(255);
	// ��������ӳ����ָ�ʱ��Ҫִ�еĴ���
	this->resume();
}

void MiniMap::onEnterTransitionDidFinish() {
	Scene::onEnterTransitionDidFinish();  // ������ø����ʵ��
	CCLOG("SimpleSceneA onEnterTransitionDidFinish");
	//�������ű���
	float scaleX = 3.0f;
	float scaleY = 3.0f;
	// ��ȡ��Ƭ��ͼ��Ƭ��С
	auto tileSize = tiledMap->getTileSize();

	// ������Ƭ���ź��С
	auto playerSize = tileSize;
	playerSize.width *= scaleX * 2;
	playerSize.height *= scaleY * 2;

	// ������ʾ���������ֵ
	//_playerHealthLabel->setString("Health: ");
	// ���� Label λ�ã�ʹ��ʼ�ո������
	//_playerHealthLabel->setPosition(cocos2d::Vec2(player->Sprite::getPosition().x, player->Sprite::getPosition().y + 150));
	// �������ؾ���
	player->initWithFile(player->getFileName());
	// �������ؾ����С
	player->setContentSize(playerSize);
	//player->Sprite::setPosition(playerPos);
	player->setPosition(playerPos);
	player->setVisible(true);
	player->setLocalZOrder(255);
	// ��������ӳ�����ȫ�ָ�����Ҫִ�еĴ���
	this->resume();
}

void MiniMap::restorePositionsAfterPop()
{
	auto player = GlobalManager::getInstance().getPlayer();
	player->setPosition(preposition);
	player->Sprite::setPosition(preposition);
}
// ��֤����λ��
void MiniMap::verifySprites() {};