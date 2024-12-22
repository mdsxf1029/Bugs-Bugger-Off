#include "BossScene.h"
#include "BattleScene.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "HelloWorldScene.h" 
#include "Map/MiniMap.h"

std::shared_ptr<Player> rawPlayer1 = GlobalManager::getInstance().getPlayer();      // ��ȡ����ָ��ָ��� Player �����ָ��
BossScene::BossScene() : _tileMap(nullptr), _currentDialogueBox(nullptr), _currentChoiceBox(nullptr){}
BossScene::~BossScene()                                                             // ��������
{
}
cocos2d::Scene* BossScene::createScene()										    // ��������
{
	return BossScene::create();												        // ���ش����ĳ���
}
bool BossScene::init()															    // ��ʼ������
{
	const auto& task = GlobalManager::getInstance().getTasks().at(0);               // ��ȡ����
	const  auto visibleSize = Director::getInstance()->getVisibleSize();		    // ��ȡ��Ļ�ߴ�
	const  auto origin = Director::getInstance()->getVisibleOrigin();			    // ��ȡ��Ļԭ��
    if (!Scene::init())                                                             //��� ��ʼ��ʧ��  ����false
    {
        return false;
    }

    // ���� TMX ��ͼ
	_tileMap = cocos2d::TMXTiledMap::create("smallmap/boss.tmx");                   //��ʼ����ͼ
	_tileMap->setScale(2.5f);													    //���õ�ͼ����
	if (_tileMap == nullptr)														//�����ͼΪ��
    {
		cocos2d::log("Failed to load map.");										//��ӡ������Ϣ
		return false;														        //����false
    }
    this->addChild(_tileMap);                                                       // ����ͼ��ӵ�����
    //�������ű���
    float scaleX = 3.0f;                                                            // ���� X �����ű���
    float scaleY = 3.0f;															// ���� Y �����ű���
    auto tileSize = _tileMap->getTileSize();                                        //��ȡsize    

    // ������Ƭ���ź��С
    auto playerSize = tileSize;														// ��ȡ��ҵĴ�С
    playerSize.width *= scaleX * 2;                                                 // ������ҵĿ��
    playerSize.height *= scaleY * 2;												// ������ҵĸ߶�

    // �ӵ�ͼ�� objects ���л�ȡ��Һ͵��˵���Ϣ
	const cocos2d::TMXObjectGroup* objectGroup = _tileMap->getObjectGroup("Objects");    // ��ȡ������
	if (objectGroup != nullptr)														     // ��������鲻Ϊ��
    {
        cocos2d::ValueMap playerData = objectGroup->getObject("Player");                 // ��ȡ��ҵ���Ϣ  
		if (!playerData.empty())														 // ���������ݲ�Ϊ��
        {
			float playerX = playerData["x"].asFloat();								     // ��ȡ��ҵ� x ����
			float playerY = playerData["y"].asFloat();								     // ��ȡ��ҵ� y ����
            try 
            {                                                                                    
                if (rawPlayer1 == nullptr) {                                             // 1. ��ָ����
					throw std::runtime_error("Player initialization failed: null pointer");// �׳��쳣
                }
            }
			catch (const std::exception& e) {											// �����쳣
				CCLOG("Exception during initialization: %s", e.what());					// ��ӡ�쳣��Ϣ
				cleanup();																// ����
                throw;                                                                  // �����׳��쳣���ϲ㴦��
            }
            rawPlayer1->initWithFile(rawPlayer1->getFileName());						// ��ʼ�����
			rawPlayer1->setContentSize(playerSize);									    // ������ҵĴ�С
			rawPlayer1->setPosition(Vec2(playerX * 2.5, playerY * 2.5));				// �������λ�ñ���
			rawPlayer1->Sprite::setPosition(rawPlayer1->getPosition());                 // ������ҵ�λ��
            this->addChild(rawPlayer1.get(), 10);                                       // �������ӵ�������
        }

        // ��ȡ���˵���Ϣ 
		cocos2d::ValueMap enemyData = objectGroup->getObject("Boss");                   // ��ȡ���˵���Ϣ
		auto princessObj = objectGroup->getObject("Princess");						    // ��ȡ��������Ϣ
		float princessX = princessObj["x"].asFloat();									// ��ȡ������ x ����
		float princessY = princessObj["y"].asFloat();									// ��ȡ������ y ����
		auto princess = cocos2d::Sprite::create("princess.png");						// ��ʼ������
		princess->setPosition(princessX, princessY);									// ���ù�����λ��
		this->addChild(princess, 9);													// ��������ӵ�������
		princess->setContentSize(playerSize);											// ���ù����Ĵ�С

        if (!enemyData.empty())
        {
			float enemyX = enemyData["x"].asFloat();    					            // ��ȡ���˵� x ����   
			float enemyY = enemyData["y"].asFloat();					                // ��ȡ���˵� y ����

            auto boss = cocos2d::Sprite::create("enemyboss.png");                       // ��ʼ������
            boss->setContentSize(playerSize);                                           // ���õ��˵Ĵ�С
            boss->setPosition(Vec2(enemyX * 2.5, enemyY * 2.5));					    // ���õ��˵�λ��                          
			this->addChild(boss, 10); 												    // ��������ӵ�������
			Boss.bossSprite = boss;                                                     // �趨���˵ľ���
			Boss.bossFunction = enemyData["npcData"].asString();						// ��ȡ���˵Ĺ���
			Boss.targetScene = enemyData["targetScene"].asString();						// ��ȡ���˵�Ŀ�곡��
			Boss.ppp = task;															// ��ȡ����
			Boss.index = enemyData["index"].asInt();									// ��ȡ���˵�����
			Boss.taskid = 0;															// ��ʼ������id
           
        }
    }

    /*ע������¼�*/ 
	auto keyListener = cocos2d::EventListenerKeyboard::create();                        // �������̼�����
	keyListener->onKeyPressed = CC_CALLBACK_2(BossScene::onKeyPressed, this);		    // ���ð������µĻص�����
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);	    // ��Ӽ��̼�����������

	this->scheduleUpdate();															    // ���ȸ��º���
    return true;
}

void BossScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
    cocos2d::Vec2 moveDir;
	switch (keyCode)                                                                     // ���ݰ��������ƶ����򣨼��԰棩
    {
        case cocos2d::EventKeyboard::KeyCode::KEY_W: moveDir = cocos2d::Vec2(0, 1); break;
        case cocos2d::EventKeyboard::KeyCode::KEY_S: moveDir = cocos2d::Vec2(0, -1); break;
        case cocos2d::EventKeyboard::KeyCode::KEY_A: moveDir = cocos2d::Vec2(-1, 0); break;
        case cocos2d::EventKeyboard::KeyCode::KEY_D: moveDir = cocos2d::Vec2(1, 0); break;
        default: return;
    }
	rawPlayer1->setPosition(rawPlayer1->getPosition() + moveDir * 100);				     // �����������
	rawPlayer1->Sprite::setPosition(rawPlayer1->getPosition());                          // ����ͼ��λ��
}
/*�����߼�*/ 
bool BossScene::IsColliding(cocos2d::Vec2 position)
{
    // ��ȡ���ؾ��鵱ǰ��������
    auto playerPos = rawPlayer1->getPosition();                                          //��ȡ����   
	auto x = position.x, y = position.y;												 // ��ȡnpc������
	auto tileSize = _tileMap->getTileSize();											 //��ȡsize

    // ������npc�����Ϊ���ĵ��ĸ���Ƭ��Χ�������Ҫ��С��������/2
    if (playerPos.x >= x - tileSize.width && playerPos.x <= x + tileSize.width && playerPos.y >= y - tileSize.height && playerPos.y <= y + tileSize.height) {
        CCLOG("Collide npc");
        return true;
    }
    return false;
}

void BossScene::update(float delta)
{
    const cocos2d::TMXObjectGroup* objectGroup = _tileMap->getObjectGroup("Objects");

    cocos2d::ValueMap bossData = objectGroup->getObject("Boss");                                     // ��ȡtmxͼ�ϵ��˵���Ϣ    

    if (!bossData.empty())
    {
		GlobalManager::getInstance().setBattleNpc(GlobalManager::getInstance().getEnemyNpcsBoss());  // ��ȡ���˵�����ָ��
		auto bos = Boss.bossSprite;																     // ��ȡ���˵ľ���
		bool isColliding = rawPlayer1->getBoundingBox().intersectsRect(bos->getBoundingBox());	     // �ж������ NPC �Ƿ���ײ
		if (isColliding && !_currentDialogueBox && !_currentChoiceBox && !bos->getUserData())		 // �������� NPC ��ײ����û�жԻ���
        {
            bos->setUserData((void*)1);                                                              // ����ѽ���
			CCLOG("Collide npc");
            displayChoice1(bos, "You can't save the princess!!!Hahahaha!!!\nDo you want to talk with me?", {
    {"Yes",[this, bos]() { {
            this->scheduleOnce([=](float) {                                                          // ��ʱ��ʾ��һ���Ի��򣬱����ڵ�
                handleChatNPC(bos);
            }, 0.1f, "handleChatNPC");
        } }},
    {"No",[this, bos]() { {
            this->scheduleOnce([=](float) { 													     // ��ʱ��ʾ��һ���Ի��򣬱����ڵ�                                        
                displayTaskPro(Boss);
            }, 0.1f, "displaybossNPC");
        } }}
                });
        }
        /* �������� NPC û����ײ����֮ǰ�Ѿ��������������ý���״̬*/
        else if (!isColliding && bos->getUserData() != nullptr)
        {
            bos->setUserData(nullptr);                                                               // ���ý���״̬�������ٴδ���
        }
    }
   
}

void BossScene::displayChoice1(cocos2d::Sprite* npc, const std::string& question,
    const std::vector<std::pair<std::string, std::function<void()>>>& choices)
{
    if (_currentChoiceBox) {					    																             // ������ڵ�ǰ�Ի����Ƴ���
        _currentChoiceBox->removeFromParent();
        _currentChoiceBox = nullptr;
    }
	auto visibleSize = Director::getInstance()->getVisibleSize();												                // ��ȡ�ɼ�����Ĵ�С
	_currentChoiceBox = cocos2d::Sprite::create("smallmap/box.png");												            // �����Ի���
	_currentChoiceBox->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));									    // ���öԻ���λ��
	this->addChild(_currentChoiceBox);																							// ���Ի�����ӵ�����
    _currentChoiceBox->setLocalZOrder(100);																        				// �öԻ����ڽϸߵĲ㼶 
	auto label = cocos2d::Label::createWithTTF(question, "fonts/Marker Felt.ttf", 48);										    // ����һ�� Label ����ʾ�Ի��������
	label->setTextColor(cocos2d::Color4B::WHITE);																			    // ����������ɫ
	label->setPosition(_currentChoiceBox->getContentSize().width / 2, _currentChoiceBox->getContentSize().height / 2 + 100);	// ���� Label λ��
	_currentChoiceBox->addChild(label, 1);																						// �� Label ��ӵ��Ի�����
	label->setLocalZOrder(101);																									// �� Label ���ڽϸߵĲ㼶

	float buttonY = 50;																											// ���ð�ť�� Y ����
	for (size_t i = 0; i < choices.size(); ++i) 																				// ����ѡ��
    {
		cocos2d::ui::Button* button;																							// ������ť
        if (i == 0) {
			button = cocos2d::ui::Button::create("Yes1.png", "Yes2.png");													    // ������ť
        }
        else if (i == 1) {
			button = cocos2d::ui::Button::create("No1.png", "No2.png");														    // ������ť
        }
        button->setPosition(cocos2d::Vec2(_currentChoiceBox->getContentSize().width / 4 + i * 300 + 30, _currentChoiceBox->getContentSize().height / 4));
		_currentChoiceBox->addChild(button);																					// ����ť��ӵ��Ի�����

        button->addClickEventListener([=](cocos2d::Ref* sender) {
            if (choices[i].second) {
                choices[i].second();																						    // ִ��ѡ���Ļص�
            }
                                                                                                                                // ��Ҫ�������Ƴ��Ի����������µĶԻ���
            if (_currentChoiceBox) {
				_currentChoiceBox->removeFromParent();                                                                          // �Ƴ��Ի���
                _currentChoiceBox = nullptr;
            }

            });
    }
}

void BossScene::handleChatNPC(cocos2d::Sprite* npc)
{

    /*��ʾ�µĶԻ���*/ 
    displayChoice2(npc, "Hello! How can I help you today?", {
        {"Tell me about the town", [this, npc]() { {                
				this->scheduleOnce([=](float) { 													  // ��ʱ��ʾ��һ���Ի��򣬱����ڵ�                                        
                    displayTownInfo(npc);
                }, 0.1f, "handleChatNPC");
            } }},
{"I need a quest", [this, npc]() { {
		this->scheduleOnce([=](float) { 														      // ��ʱ��ʾ��һ���Ի��򣬱����ڵ�                    
            displayQuestInfo(npc);
        }, 0.1f, "handleChatNPC");
    } }},
{"Nothing, just passing by", [this, npc]() { {
		this->scheduleOnce([=](float) { 														      // ��ʱ��ʾ��һ���Ի��򣬱����ڵ�
            displayGoodbye(npc);
        }, 0.1f, "handleChatNPC");
    } }},
        });

}

void BossScene::displayChoice2(cocos2d::Sprite* npc, const std::string& question,
    const std::vector<std::pair<std::string, std::function<void()>>>& choices)
{
    // ȷ���ɶԻ������
    if (_currentChoiceBox) {
		_currentChoiceBox->removeFromParent();                                                         // �Ƴ��Ի���
		_currentChoiceBox = nullptr;                                                                   // ��Ϊ��ָ��
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();									   // ��ȡ�ɼ�����Ĵ�С
	_currentChoiceBox = cocos2d::Sprite::create("smallmap/box.png");								   // �����Ի���
	_currentChoiceBox->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 3 / 4));		   // ���öԻ���λ��
	this->addChild(_currentChoiceBox, 1);															   // ���Ի�����ӵ�����
	_currentChoiceBox->setLocalZOrder(100);														       // �öԻ����ڽϸߵĲ㼶

	auto label = cocos2d::Label::createWithTTF(question, "fonts/Marker Felt.ttf", 48);				   // ����һ�� Label ����ʾ�Ի��������
	label->setTextColor(cocos2d::Color4B::BLACK);													   // ����������ɫ
	label->setPosition(_currentChoiceBox->getContentSize().width / 2, _currentChoiceBox->getContentSize().height / 2); // ���� Label λ��
	_currentChoiceBox->addChild(label, 1);															   // �� Label ��ӵ��Ի�����
	label->setLocalZOrder(101);																		   // �� Label ���ڽϸߵĲ㼶

	float buttonY = 50;																				   // ���ð�ť�� Y ����
	for (size_t i = 0; i < choices.size(); ++i) 													   // ����ѡ��
    {
		auto button = cocos2d::ui::Button::create("button1.png", "button2.png");					   // ������ť
		button->setTitleText(choices[i].first);														   // ���ð�ť����
		button->setTitleFontName("fonts/Marker Felt.ttf");                                             // ���ð�ť����
		button->setTitleColor(cocos2d::Color3B::BLACK);												   // ���ð�ť������ɫ
		button->setTitleFontSize(24);																   // ���ð�ť�����С
        button->setPosition(cocos2d::Vec2(cocos2d::Vec2(_currentChoiceBox->getContentSize().width / 2, buttonY + i * 150 -200)));
		_currentChoiceBox->addChild(button);														   // ����ť��ӵ��Ի�����

        button->addClickEventListener([=](cocos2d::Ref* sender) {
            if (choices[i].second) {
                choices[i].second();                                                                   // ִ��ѡ���Ļص�
            }
			_currentChoiceBox->removeFromParent();													   // �ڻص������Ƴ��Ի���
			_currentChoiceBox = nullptr;															   // ��Ϊ��ָ��
            });
    }
}
/*NPC �ش���ڳ�������*/ 
void BossScene::displayTownInfo(cocos2d::Sprite* npc)
{   
    displayChoice2(npc, "This is a peaceful town. You can find a shop, a tavern, and a blacksmith.", {
        {"I see, tell me more!", [this, npc]() { {                                                     // ��ʱ��ʾ��һ���Ի��򣬱����ڵ�
                this->scheduleOnce([=](float) {
                    displayTownDetails(npc);
                }, 0.1f, "handleChatNPC");
            } }},
		{"That's enough, thanks!", [this, npc]() { {                                                    // ��ʱ��ʾ��һ���Ի��򣬱����ڵ�
                this->scheduleOnce([=](float) {
                    displayGoodbye(npc);
                }, 0.1f, "handleChatNPC");
            } }}
        });
}

/*NPC ��ϸ���ܳ���*/ 
void BossScene::displayTownDetails(cocos2d::Sprite* npc)
{
    displayDialogue(npc, "The shop sells potions, the tavern offers drinks and rumors, and the blacksmith can upgrade your gear.");
}

/*NPC ����������Ϣ*/ 
void BossScene::displayQuestInfo(cocos2d::Sprite* npc)
{
    displayChoice2(npc, "I have a quest for you: Collect 10 herbs.", {

        {"Maybe later", [this, npc]() { }},
        {"Tell me more", [this, npc]() { displayQuestDetails(npc); }}
        });
}
void BossScene::displayTaskPro(bossDATA& npcData) {
    displayChoice1(npcData.bossSprite, npcData.ppp->getTaskName(), {
        {"YES", [this, &npcData]() {
            npcData.ppp->state = 0;                                                                     // ��������״̬Ϊ�ѷ���
			CCLOG("message", npcData.targetScene);                                                      // ��ӡ��Ϣ
			rawPlayer1->removeFromParent();															    // �Ƴ����
			GlobalManager::getInstance().setLastMap("smallmap/castle.tmx");							    // ������һ����ͼ
			const auto& taskListbat = GlobalManager::getInstance().getTasks();                          // ��ȡ�����б�
			taskListbat[0]->id = 0;																	    // ��������id
            Director::getInstance()->replaceScene(TransitionFade::create(1.0f, BattleScene::create())); // ��ת�� NPC ���õ�Ŀ�곡��
			npcData.ppp->state = 1;																	    // ��������״̬Ϊ�����

        }},
        {"NO", nullptr}
        });
}
/*NPC ��ϸ������Ϣ*/ 
void BossScene::displayQuestDetails(cocos2d::Sprite* npc)
{
    displayDialogue(npc, "The herbs grow near the forest. Please bring them back to me once you've collected them.");
}

/*NPC ˵���ټ���*/ 
void BossScene::displayGoodbye(cocos2d::Sprite* npc)
{
    displayDialogue(npc, "Goodbye, and good luck on your adventures!");
}



void BossScene::displayDialogue(Sprite* npc, const std::string& text)
{
    /*������ڵ�ǰ�Ի����Ƴ���*/ 
    if (_currentDialogueBox) {
        _currentDialogueBox->removeFromParent();
        _currentDialogueBox = nullptr;
    }

    /* �����Ի���*/
    auto dialogueBox = Sprite::create("box3.png");
    if (!dialogueBox) {
        CCLOG("Failed to create dialogue box!");
        return;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();												// ��ȡ�ɼ�����Ĵ�С
	dialogueBox->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));								// ���öԻ���λ��
	this->addChild(dialogueBox);																				// ���Ի�����ӵ�����

    /* �����ı���ǩ*/
	auto label = Label::createWithTTF(text, "fonts/Marker Felt.ttf", 24);                                       // ����һ�� Label ����ʾ�Ի��������
	label->setTextColor(Color4B::BLACK);																		// ����������ɫ
	label->setPosition(dialogueBox->getContentSize() / 2);														// ���� Label λ��
	dialogueBox->addChild(label);																				// �� Label ��ӵ��Ի�����

    /*���õ�ǰ�Ի���*/ 
	_currentDialogueBox = dialogueBox;                                                                          // ���õ�ǰ�Ի���

    /*�Զ���ʧ�Ի���*/ 
    this->scheduleOnce([=](float) {
		dialogueBox->removeFromParent();                                                                        // �Ƴ��Ի���
        _currentDialogueBox = nullptr;
		}, 3.0f, "closeDialogue");                                                                              // 3 ����Զ���ʧ
}