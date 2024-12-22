#include <cmath>
#include <vector>
#include "Map/MiniMap.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Sets/manager.h"
#include "HelloWorldScene.h"

std::shared_ptr<Player> _player = GlobalManager::getInstance().getPlayer();

// �������ؾ���λ��
void MiniMap::UpdatePlayerPosition(const cocos2d::EventKeyboard::KeyCode keyCode)
{
    cocos2d::Vec2 currentPos = _player->getPosition();                                                              // ��ȡ���ؾ���ԭλ��
	CCLOG("Current player position: (%f, %f)", currentPos.x, currentPos.y);                                         // ���ԭλ��
	preposition = currentPos;                                                                                       // ��¼ԭλ��
    
	cocos2d::Vec2 newPos = GlobalManager::getInstance().getPlayer()->Move(keyCode);								   // ��ȡ���ؾ�����λ��
	CCLOG("New player position: (%f, %f)", newPos.x, newPos.y);													   // �����λ��

	bool walkable = true;																						   // ����Ƿ������
    auto collisionLayer = tiledMap->getObjectGroup("Collision");                                                   //��ȡ��ײ���Ķ�̬������  

    // ��ȡ���ű���
	auto scaleX = tiledMap->getScaleX();                                                                            // ��ȡx�����ű���
	auto scaleY = tiledMap->getScaleY();																			// ��ȡy�����ű���
	CCLOG("Scale factors: (%f, %f)", scaleX, scaleY);															    // ������ű���

	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();                                    // ��ȡ��������ԭ������
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();								    // ��ȡ���������С
	CCLOG("Visible area: origin(%f, %f), size(%f, %f)", origin.x, origin.y, visibleSize.width, visibleSize.height); // �������������Ϣ

	cocos2d::Vec2 centralWorldPos = cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 2);					// �����Ӵ����ĵ���������
	CCLOG("Window center world position: (%f, %f)", centralWorldPos.x, centralWorldPos.y);						    // ����Ӵ����ĵ���������

    // ��ȡ��ǰ��Ƭ��ͼ��С
	cocos2d::Size mapSize = tiledMap->getMapSize();															       // ��ȡ��ͼ��С
    CCLOG("Tile map size: (%f, %f)", mapSize.width, mapSize.height);

    // ��ȡ��Ƭ��ͼ��Ƭ��С
	cocos2d::Size tileSize = tiledMap->getTileSize();															   // ��ȡ��Ƭ��С
    CCLOG("Tile size: (%f, %f)", tileSize.width, tileSize.height);

    // ��ȡ��ǰ��Ƭ��ͼ����
	cocos2d::Vec2 currentMapPos = tiledMap->getPosition();														   // ��ȡ��ͼλ��
	CCLOG("Current tile map position: (%f, %f)", currentMapPos.x, currentMapPos.y);                                // �����ͼλ��

    // ������Ƭ���ź��С
	cocos2d::Size playerSize = tileSize;                                                                           // ��ȡ��Ƭ��С
	playerSize.width *= scaleX;																					   // �������ź���
	playerSize.height *= scaleY;																				   // �������ź�߶�

    // ͨ�����������ȡ��������Ƭ���е��������
	cocos2d::Vec2 tilePos = tiledMap->convertToNodeSpace(newPos);												   // ��ȡ��λ�õ���Ƭ����
	CCLOG("Relative tile position: (%f, %f)", tilePos.x, tilePos.y);										       // �����Ƭ����

    // �������ײ���㣬��Collision����
    if (collisionLayer) {
		auto collisionObjects = collisionLayer->getObjects();                                                       // ��ȡ��ײ����
		CCLOG("Number of collision objects: %lu", collisionObjects.size());										    // �����ײ��������
        for (const auto& object : collisionObjects) {
			cocos2d::ValueMap collisionProperties = object.asValueMap();										   // ��ȡ��ײ����
			auto x = collisionProperties["x"].asFloat();														   // ��ȡx����
			auto y = collisionProperties["y"].asFloat();														   // ��ȡy����
			auto width = collisionProperties["width"].asFloat();												   // ��ȡ���
			auto height = collisionProperties["height"].asFloat();												   // ��ȡ�߶�
			CCLOG("Collision area: (%f, %f), width: %f, height: %f", x, y, width, height);						   // �����ײ����
			if (tilePos.x >= x && tilePos.x <= x + width && tilePos.y >= y && tilePos.y <= y + height) {		   // �����ײ
				walkable = false;																				   // ��������
				CCLOG("Collision detected: cannot move to (%f, %f)", tilePos.x, tilePos.y);						   // �����ײ��Ϣ
                break;
            }
        }
    }

    // Ѱ���Ƿ���boat��
	auto boatLayer = tiledMap->getObjectGroup("Boat");															   // ��ȡboat�� 
    // ��Ǵ������
	bool boat = false;																							   // ����Ƿ���boat��
     
	if (boatLayer) {                                                                                               // �����boat��
		auto boatObjects = boatLayer->getObjects();																   // ��ȡboat����
		CCLOG("Number of boat objects: %lu", boatObjects.size());												   // ���boat��������
		for (const auto& object : boatObjects) {																   // ����boat����
			cocos2d::ValueMap boatProperties = object.asValueMap();												   // ��ȡboat����
			auto x = boatProperties["x"].asFloat();																   // ��ȡx����
			auto y = boatProperties["y"].asFloat();																   // ��ȡy����
			auto width = boatProperties["width"].asFloat();														   // ��ȡ���
			auto height = boatProperties["height"].asFloat();													   // ��ȡ�߶�
			CCLOG("Boat area: (%f, %f), width: %f, height: %f", x, y, width, height);							   // ���boat����
            if (tilePos.x >= x && tilePos.x <= x + width && tilePos.y >= y && tilePos.y <= y + height) {
				boat = true;																					   // ����boat
                CCLOG("Boat detected: player is on a boat spot");
                break;
            }
        }
    }

    // �������boat�����Ի���
    if (boat) {
        CCLOG("Entering boat dialog");

        // �����Ի���ı�������
        auto background = cocos2d::Sprite::create();
        float width = visibleSize.width / 2, height = visibleSize.height / 2;                                    // ���öԻ���Ĵ�С
        background->setTextureRect(cocos2d::Rect(0.0f, 0.0f, width, height));                                    // ��Ϊ����
        background->setColor(Color3B(255, 255, 255));                                                            // ���öԻ��򱳾�Ϊ��ɫ        
        background->setPosition(centralWorldPos);                                                                // ���öԻ���λ��Ϊ�Ӵ�����       
        background->setOpacity(200);                                                                             // ���öԻ���͸����Ϊ�ϸ�
        background->setName("background");                                                                       // ���ñ������������
		this->addChild(background); 																		     // ��ӱ�������                    
		CCLOG("Background sprite has been added.");

        // �������ֱ�ǩ
        auto label = cocos2d::Label::createWithSystemFont("Where do you want to go?", "fonts/arial.ttf", 64);    // �����ı�
        label->setPosition(centralWorldPos + cocos2d::Vec2(0.0f, visibleSize.height / 3));                       // ����λ��
        label->setColor(cocos2d::Color3B(0, 0, 0));                                                              // �����ı���ɫΪ��ɫ
        label->setName("label");                                                                                 // �����ı���ǩ������
		this->addChild(label);  																		         // ����ı���ǩ                 
		CCLOG("Label has been added.");

        // �������ڵ�������а�ť
		auto buttonParentNode = cocos2d::Node::create();														// �������ڵ�
		this->addChild(buttonParentNode);																		// ��Ӹ��ڵ� 
		auto closeButton = ui::Button::create("CloseSelected.png");												// �����رհ�ť
		closeButton->setPosition(centralWorldPos + cocos2d::Vec2(width / 2, height / 2));						// ���ùرհ�ťλ��

		closeButton->addClickEventListener([this, buttonParentNode](cocos2d::Ref* sender) {					    // ��ӵ���¼�
			auto sprite = this->getChildByName("background");                                                   // ���ұ�������
             
            if (sprite) {
				sprite->removeFromParentAndCleanup(true);												   	    // �Ƴ���������
                CCLOG("background sprite has been removed.");
            }
			auto label = this->getChildByName("label");														    // �����ı���ǩ
             
            if (label) {
				label->removeFromParentAndCleanup(true);                                                        //�Ƴ��ı���ǩ
                CCLOG("label has been removed.");
            }
			buttonParentNode->removeAllChildren();															    // �Ƴ������ӽڵ�--��ť
            });
        buttonParentNode->addChild(closeButton);                                                                // ����ť��ӵ����ڵ�

		std::vector<std::string> map = { "gold","wood","earth","water","fire","none","village" };			    // ������ͼ����

        // ��ȡ����
        const auto& tasks = GlobalManager::getInstance().getTasks();										    // ��ȡ����

        if (mapName == "smallmap/village.tmx")                                                                  //�����ǰ��village
        {
            for (int i = 0; i < 6; i++)
            {
                auto button = ui::Button::create("CloseSelected.png", "CloseSelected.png", "CloseSelected.png");                // ������ť
                // ���ð�ť����
                button->setTitleText(map[i]);                                                                                   // �����ı�
				CCLOG("Build button %s", map[i].c_str());																		// �����ť��Ϣ   
                button->setTitleFontSize(48);                                                                                   // �����ֺ�
                button->setTitleColor(Color3B(0, 0, 0));                                                                        // ���ñ���Ϊ��ɫ
                button->setTitleFontName("Arial");                                                                              // ���ñ�������

				// ��ѯǰһ����ͼ�������Ƿ���ɣ����˽��ͼ��
                if (tasks[i]->state <= 0 && i < 5 && i != 0)      														            // ���δ��ɣ����ð�ť                                              
                {
                    button->setEnabled(false);
                }

                button->addClickEventListener(std::bind(&MiniMap::ButtonCallback, this, std::placeholders::_1));                // ��Ӱ�ť����¼�
                button->setPosition(cocos2d::Vec2(centralWorldPos.x, visibleSize.height * 2 / 3 - i * 70));                     // ���ð�ťλ��
                buttonParentNode->addChild(button);                                                                             // ����ť��ӵ����ڵ���
            }
        }
        else if (mapName == "smallmap/castle.tmx")
        {
            // ������ť
			auto button1 = ui::Button::create("CloseNormal.png", "CloseNormal.png", "CloseNormal.png");                  // ������ť
            auto button2 = ui::Button::create("CloseSelected.png", "CloseSelected.png", "CloseSelected.png");

            // ���ð�ť��λ��
			button1->setPosition(cocos2d::Vec2(centralWorldPos.x, centralWorldPos.y - visibleSize.height / 10));		 // ���ð�ťλ��
            button2->setPosition(cocos2d::Vec2(centralWorldPos.x, centralWorldPos.y + visibleSize.height / 10));

            // ���ð�ť����
            button1->setTitleText(map[6]);                                                                               // �����ı�
            CCLOG("Build button %s", map[6].c_str());
            button1->setTitleFontSize(48);                                                                               // �����ֺ�
            button1->setTitleColor(Color3B(0, 0, 0));                                                                    // ���ñ���Ϊ��ɫ
            button1->setTitleFontName("Arial");                                                                          // ���ñ�������
            button2->setTitleText(map[5]);                                                                               // �����ı�
            CCLOG("Build button %s", map[5].c_str());                                                                          
            button2->setTitleFontSize(48);                                                                               // �����ֺ�
            button2->setTitleColor(Color3B(0, 0, 0));                                                                    // ���ñ���Ϊ��ɫ
            button2->setTitleFontName("Arial");                                                                          // ���ñ�������

			button1->addClickEventListener(std::bind(&MiniMap::ButtonCallback, this, std::placeholders::_1));		     // ��Ӱ�ť����¼�
            button2->addClickEventListener(std::bind(&MiniMap::ButtonCallback, this, std::placeholders::_1));

			buttonParentNode->addChild(button1);																	     // ����ť��ӵ����ڵ���
            buttonParentNode->addChild(button2);
        }
        else
        {
			std::string newMap1, newMap2;
            int map1, map2;
            GetNeighborMap(newMap1, newMap2, map1, map2);															     // ��ȡ���ڵ�ͼ
            for (int i = 0; i < 4; i++)
            {
				auto button = ui::Button::create("CloseSelected.png", "CloseSelected.png", "CloseSelected.png");	     // ������ť
				button->setPosition(cocos2d::Vec2(centralWorldPos.x, visibleSize.height * 2 / 3 - i * 100));		     // ���ð�ťλ��

                // ���ð�ť����
                button->setTitleFontSize(48);                                                                            // �����ֺ�
                button->setTitleColor(Color3B(0, 0, 0));                                                                 // ���ñ���Ϊ��ɫ
                button->setTitleFontName("Arial");                                                                       // ���ñ�������

                // ���ñ����ı�
                if (i == 0 || i == 1)
                {
                    if (i == 0)
                    {
						button->setTitleText(newMap1);                                                                   // �����ı�
                    }
                    else
                    {
						button->setTitleText(newMap2);																    // �����ı�
                    }

                    // ��ȡ����
                    if ((i == 0 && tasks[map1]->state <= 0) || (i == 1 && tasks[map2]->state <= 0))                                                                              // ���δ���
                    {
                        button->setEnabled(false);                                                                      // ���ð�ť
                    }
                }
				else if (i == 3)                                                                                        // ����Ǵ�ׯ
                {
					button->setTitleText("village");															    	// �����ı�
                }
                else
					button->setTitleText("none");																       // �����ı�

				button->addClickEventListener(std::bind(&MiniMap::ButtonCallback, this, std::placeholders::_1));	   // ��Ӱ�ť����¼�
				buttonParentNode->addChild(button);																	   // ����ť��ӵ����ڵ���
            }
        }
    }

    // ����Ǵ�ׯ
    if (mapName == "smallmap/village.tmx")
    {
        auto gateLayer = tiledMap->getObjectGroup("Gate");                                                            // Ѱ���Ƿ���gate��
        bool gate = false;                                                                                            // ��Ǵ������

        // �����gate�㣬��gate����
        if (gateLayer) {
			auto gateObjects = gateLayer->getObjects();															      // ��ȡgate����
            for (const auto& object : gateObjects) {
				cocos2d::ValueMap boatProperties = object.asValueMap();											      // ��ȡgate����
				auto x = boatProperties["x"].asFloat();															      // ��ȡx����
				auto y = boatProperties["y"].asFloat();															      // ��ȡy����
				auto width = boatProperties["width"].asFloat();													      // ��ȡ���
				auto height = boatProperties["height"].asFloat();											          // ��ȡ�߶�
				if (tilePos.x >= x && tilePos.x <= x + width && tilePos.y >= y && tilePos.y <= y + height) {		  // �����gate��
					gate = true; 																			          // ����gate
                    break;
                }
            }
        }

        // �����gate��
        if (gate)
        {
			auto buttonParentNode = cocos2d::Node::create();													  // �������ڵ�
            this->addChild(buttonParentNode);																	    // �������а�ť

            // ������ť
			auto button1 = ui::Button::create("CloseNormal.png", "CloseNormal.png", "CloseNormal.png");		        // ������ť
            auto button2 = ui::Button::create("CloseSelected.png", "CloseSelected.png", "CloseSelected.png");

            // ���ð�ť��λ��
			button1->setPosition(cocos2d::Vec2(centralWorldPos.x, centralWorldPos.y - visibleSize.height / 3));     // ���ð�ťλ��
            button2->setPosition(cocos2d::Vec2(centralWorldPos.x, centralWorldPos.y + visibleSize.height / 3));

            // ���ð�ť����
            button1->setTitleText("castle");                                                                        // �����ı�
            button1->setTitleFontSize(48);                                                                          // �����ֺ�
            button1->setTitleColor(Color3B(0, 0, 0));                                                               // ���ñ���Ϊ��ɫ
            button1->setTitleFontName("Arial");                                                                     // ���ñ�������
            button2->setTitleText("none");                                                                          // �����ı�
            button2->setTitleFontSize(48);                                                                          // �����ֺ�
            button2->setTitleColor(Color3B(0, 0, 0));                                                               // ���ñ���Ϊ��ɫ
            button2->setTitleFontName("Arial");                                                                     // ���ñ�������

            // ��Ӱ�ť����¼�
			button1->addClickEventListener(std::bind(&MiniMap::ButtonCallback, this, std::placeholders::_1));	  // ��Ӱ�ť����¼�
            button2->addClickEventListener(std::bind(&MiniMap::ButtonCallback, this, std::placeholders::_1));

            // ����ť��ӵ����ڵ���
			buttonParentNode->addChild(button1);																  // ����ť��ӵ����ڵ���
            buttonParentNode->addChild(button2);
        }
    }
    // ��������߽���������
	float minWorldX = centralWorldPos.x - visibleSize.width / 4;                                                  // ��������߽���������x��С
	float minWorldY = centralWorldPos.y - visibleSize.height / 4;                                                 // ��������߽���������y��С
	float maxWorldX = centralWorldPos.x + visibleSize.width / 4;												  // ��������߽���������x���
	float maxWorldY = centralWorldPos.y + visibleSize.height / 4;												  // ��������߽���������y���

    static int a = 0;
	auto objectGroupp = tiledMap->getObjectGroup("Objects");                                                      // ��ȡ������
    if (objectGroupp) {
		auto npcGroup = objectGroupp->getObjects();															      // ��ȡ����
        for (auto& npcObj : npcGroup) {
			cocos2d::ValueMap npcData = npcObj.asValueMap();													  // ��ȡnpc����
            if (!npcData.empty()) {
				auto x = npcData["x"].asFloat();                                                                  // ��ȡx����
				auto y = npcData["y"].asFloat();																  // ��ȡy����
                
                if (tilePos.x >= x - tileSize.width && tilePos.x <= x + tileSize.width && tilePos.y >= y - tileSize.height && tilePos.y <= y + tileSize.height) {
                    CCLOG("Collide npc��%d", a);
                    CCLOG("X1,Y1 %f,%f", x, y);
                    a++;
                    break;
                }
            }
        }
    }
    // �����ǰ��������
    if (walkable)
    {
		float offset;                                                                                   // ����ƫ����
		if (abs(newPos.x - currentPos.x))															    // ���x��ƫ��
			offset = abs(newPos.x - currentPos.x);													    // ����x��ƫ��
        else
			offset = abs(newPos.y - currentPos.y);													    // ����y��ƫ��

        // ��������
        if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW && newPos.x <= minWorldX && tilePos.x > 0
            && currentMapPos.x < 0) {
			cocos2d::Vec2 newMapPosition = currentMapPos + cocos2d::Vec2(offset, 0.0f);                 // �����µ�ͼλ��
			cocos2d::Vec2 newNPCPos = npcNode->getPosition() + cocos2d::Vec2(offset, 0.0f);			    // ������NPCλ��
			cocos2d::Vec2 newItemPos = itemNode->getPosition() + cocos2d::Vec2(offset, 0.0f);	        // ��������Ʒλ��

			CCLOG("newposition x:%f,y:%f", newMapPosition.x, newMapPosition.y);						    // ����µ�ͼλ��
			CCLOG("newPos x:%f,y:%f", newPos.x, newPos.y);											    // �����λ��
			CCLOG("minWorld x:%f,y:%f", minWorldX, minWorldY);										    // �������߽�
			CCLOG("npcNode x:%f,y%f", npcNode->getPositionX(), npcNode->getPositionY());			    // ���NPCλ��

			tiledMap->setPosition(newMapPosition);														// �����µ�ͼλ��
			npcNode->setPosition(newNPCPos);															// ������NPCλ��
			itemNode->setPosition(newItemPos);															// ��������Ʒλ��
        }

        // ��������
		else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW && newPos.x >= maxWorldX    
            && tilePos.x < mapSize.width * tileSize.width && currentMapPos.x + (mapSize.width - 2) * tileSize.width * scaleX > visibleSize.width) {
			cocos2d::Vec2 newMapPosition = currentMapPos - cocos2d::Vec2(offset, 0.0f);                 // �����µ�ͼλ��
			cocos2d::Vec2 newNPCPos = npcNode->getPosition() - cocos2d::Vec2(offset, 0.0f);			    // ������NPCλ��
			cocos2d::Vec2 newItemPos = itemNode->getPosition() - cocos2d::Vec2(offset, 0.0f);	        // ��������Ʒλ��
			CCLOG("newposition x:%f,y:%f", newMapPosition.x, newMapPosition.y);						    // ����µ�ͼλ��
			CCLOG("newPos x:%f,y:%f", newPos.x, newPos.y);											    // �����λ��
			CCLOG("minWorld x:%f,y:%f", minWorldX, minWorldY);										    // �������߽�
			CCLOG("npcNode x:%f,y%f", npcNode->getPositionX(), npcNode->getPositionY());			    // ���NPCλ��
			tiledMap->setPosition(newMapPosition);														// �����µ�ͼλ��
			npcNode->setPosition(newNPCPos);															// ������NPCλ��
			itemNode->setPosition(newItemPos);															// ��������Ʒλ��
        }

        // ��������
        else if (newPos.y >= maxWorldY && keyCode == cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW && tilePos.y > 0
            && currentMapPos.y + (mapSize.height - 2) * tileSize.height * scaleY > visibleSize.height) {
            cocos2d::Vec2 newMapPosition = currentMapPos - cocos2d::Vec2(0.0f, offset);                 //ͬ��
            cocos2d::Vec2 newNPCPos = npcNode->getPosition() - cocos2d::Vec2(0.0f, offset);
            cocos2d::Vec2 newItemPos = itemNode->getPosition() - cocos2d::Vec2(0.0f, offset);
            CCLOG("newposition x:%f,y:%f", newMapPosition.x, newMapPosition.y);
            CCLOG("newPos x:%f,y:%f", newPos.x, newPos.y);
            CCLOG("minWorld x:%f,y:%f", minWorldX, minWorldY);
            CCLOG("npcNode x:%f,y%f", npcNode->getPositionX(), npcNode->getPositionY());
            tiledMap->setPosition(newMapPosition);
            npcNode->setPosition(newNPCPos);
            itemNode->setPosition(newItemPos);
        }

        // ��������
        else if (newPos.y <= minWorldY && keyCode == cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW
            && tilePos.y < mapSize.height * tileSize.height && currentMapPos.y < 0) {
			cocos2d::Vec2 newMapPosition = currentMapPos + cocos2d::Vec2(0.0f, offset);				 //ͬ��   
            cocos2d::Vec2 newNPCPos = npcNode->getPosition() + cocos2d::Vec2(0.0f, offset);
            cocos2d::Vec2 newItemPos = itemNode->getPosition() + cocos2d::Vec2(0.0f, offset);
            CCLOG("newposition x:%f,y:%f", newMapPosition.x, newMapPosition.y);
            CCLOG("newPos x:%f,y:%f", newPos.x, newPos.y);
            CCLOG("minWorld x:%f,y:%f", minWorldX, minWorldY);
            CCLOG("npcNode x:%f,y%f", npcNode->getPositionX(), npcNode->getPositionY());
            tiledMap->setPosition(newMapPosition);
            npcNode->setPosition(newNPCPos);
            itemNode->setPosition(newItemPos);
        }

        else if (newPos.x > 0 && newPos.x < visibleSize.width && newPos.y>0 && newPos.y < visibleSize.height) {
			auto moveTo = cocos2d::MoveTo::create(0.1f, newPos);									     		// ����ƽ������
			_player->runAction(moveTo);																			// ���ж���
            GlobalManager::getInstance().getPlayer()->setPosition(newPos);                                      // ������������
        }
    }
    else
    {
		CCLOG("�޷�ǰ��(%f,%f)", newPos.x, newPos.y);															// ����޷�ǰ����Ϣ
    }
}

void MiniMap::ButtonCallback(Ref* sender)
{
	this->removeChildByName("background");                                                                    // �Ƴ���������
	this->removeChildByName("label");																		  // �Ƴ��ı���ǩ
    ui::Button* button = static_cast<ui::Button*>(sender);													  // ��ȡ��ť �� Ref ָ��ת��Ϊ Button ָ��
	std::string title = button->getTitleText();																  // ��ȡ��ť����
    // �������Ϊ�����ļ���
	title = "smallmap/" + title;    																          // �������                           
	if (title == "smallmap/gold")                                                                             // �����gold
		title += "1.tmx";                                                                                     // �������
	else if (title == "smallmap/water")                                                                       // �����water
		title = "smallmap/whole3.tmx";                                                                        // �������
    else
		title += ".tmx";                                                                                      // �������

	auto parentNode = button->getParent();                                                                    //��ȡ���ڵ�
 
    if (parentNode)
		parentNode->removeAllChildren();																	  // �Ƴ������ӽڵ�-- ��ť
    else
		button->removeFromParentAndCleanup(true);															  // �Ƴ���ť
    if (title != "smallmap/none.tmx")
		BoatingToMap(title);    																              // ���е���ͼ                     
}

void MiniMap::GetNeighborMap(std::string& newMap1, std::string& newMap2, int& map1, int& map2)                                      // ��ȡ���ڵ�ͼ
{
    if (mapName == "smallmap/gold1.tmx")                                                                      // �����gold1
    {
		newMap1 = "fire";                                                                                     //���ڵ�ͼ1��fire
        newMap2 = "wood";                                                                                     //���ڵ�ͼ2��wood
        map1 = 4;
        map2 = 1;
    }
    else if (mapName == "smallmap/wood.tmx")                                                                  // �����wood   
    {
        newMap1 = "gold";                                                                                     //���ڵ�ͼ1��gold
        newMap2 = "earth";                                                                                    //���ڵ�ͼ2��earth
        map1 = 1;
        map2 = 2;
    }
    else if (mapName == "smallmap/earth.tmx")                                                                 //�����earth
    {
        newMap1 = "wood";                                                                                     //���ڵ�ͼ1��wood
        newMap2 = "water";                                                                                     //���ڵ�ͼ2��water
        map1 = 1;
        map2 = 3;
    }
    else if (mapName == "smallmap/whole3.tmx")                                                                 //�����water
    {
        newMap1 = "earth";                                                                                     //���ڵ�ͼ1��earth
        newMap2 = "fire";                                                                                     //���ڵ�ͼ2��fire          
        map1 = 2;
        map2 = 4;
    }
    else if (mapName == "smallmap/fire.tmx")                                                                  //�����fire
    {
        newMap1 = "water";                                                                                    //���ڵ�ͼ1��water
        newMap2 = "gold";                                                                                    //���ڵ�ͼ2��gold
        map1 = 3;
        map2 = 1;
    }
}