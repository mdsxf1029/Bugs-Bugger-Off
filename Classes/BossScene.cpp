#include "BossScene.h"
#include "BattleScene.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "HelloWorldScene.h" 
#include "Map/MiniMap.h"

std::shared_ptr<Player> rawPlayer1 = GlobalManager::getInstance().getPlayer();
BossScene::BossScene() : _tileMap(nullptr), _currentDialogueBox(nullptr), _currentChoiceBox(nullptr){}
BossScene::~BossScene() 
{

}
cocos2d::Scene* BossScene::createScene()
{
    return BossScene::create();
}
bool BossScene::init()

{

    const auto& task = GlobalManager::getInstance().getTasks().at(0);
    const  auto visibleSize = Director::getInstance()->getVisibleSize();
    const  auto origin = Director::getInstance()->getVisibleOrigin();

    if (!Scene::init())                                                             //��� ��ʼ��ʧ��  ����false
    {
        return false;
    }

    // ���� TMX ��ͼ
    _tileMap = cocos2d::TMXTiledMap::create("smallmap/boss.tmx");
    _tileMap->setScale(2.5f);
    if (_tileMap == nullptr)
    {
        cocos2d::log("Failed to load map.");
        return false;
    }
    this->addChild(_tileMap);  // ����ͼ��ӵ�����

    //�������ű���
    float scaleX = 3.0f;                                                                // ���� X �����ű���
    float scaleY = 3.0f;																// ���� Y �����ű���
    auto tileSize = _tileMap->getTileSize();                                            //��ȡsize    

    // ������Ƭ���ź��С
    auto playerSize = tileSize;														    // ��ȡ��ҵĴ�С
    playerSize.width *= scaleX * 2;                                                     // ������ҵĿ��
    playerSize.height *= scaleY * 2;													// ������ҵĸ߶�

    // �ӵ�ͼ�� objects ���л�ȡ��Һ͵��˵���Ϣ
    const cocos2d::TMXObjectGroup* objectGroup = _tileMap->getObjectGroup("Objects");
    if (objectGroup != nullptr)
    {
        cocos2d::ValueMap playerData = objectGroup->getObject("Player");                 // ��ȡ��ҵ���Ϣ  
       
        if (!playerData.empty())
        {
            float playerX = playerData["x"].asFloat();
            float playerY = playerData["y"].asFloat();
            try 
            {                                                                                    // 1. ��ָ����
                if (rawPlayer1 == nullptr) {
                    throw std::runtime_error("Player initialization failed: null pointer");
                }
            }
            catch (const std::exception& e) {
                CCLOG("Exception during initialization: %s", e.what());
                cleanup();
                throw;                                                                                  // �����׳��쳣���ϲ㴦��
            }
            rawPlayer1->initWithFile(rawPlayer1->getFileName());											// ��ʼ�����
            //rawPlayer1->initWithFile("Tree.png");
            rawPlayer1->setContentSize(playerSize);
            rawPlayer1->setPosition(Vec2(playerX * 2.5, playerY * 2.5));
            rawPlayer1->Sprite::setPosition(rawPlayer1->getPosition());
            this->addChild(rawPlayer1.get(), 10);  // �������ӵ�������
        }

        // ��ȡ���˵���Ϣ 
        cocos2d::ValueMap enemyData = objectGroup->getObject("Boss");
        auto princessObj = objectGroup->getObject("Princess");
		float princessX = princessObj["x"].asFloat();
		float princessY = princessObj["y"].asFloat();
		auto princess = cocos2d::Sprite::create("princess.png");
		princess->setPosition(princessX, princessY);
		this->addChild(princess, 9);
		princess->setContentSize(playerSize);



        if (!enemyData.empty())
        {
            float enemyX = enemyData["x"].asFloat();
            float enemyY = enemyData["y"].asFloat();

            auto boss = cocos2d::Sprite::create("enemyboss.png");                                // ��ʼ������
            boss->setContentSize(playerSize);                                   // ���õ��˵Ĵ�С
            boss->setPosition(Vec2(enemyX * 2.5, enemyY * 2.5));					// ���õ��˵�λ��                                     // ��ȡ���˵ļ���
            this->addChild(boss, 10); 
            Boss.bossSprite = boss;
            Boss.bossFunction = enemyData["npcData"].asString();
			Boss.targetScene = enemyData["targetScene"].asString();
            Boss.ppp = task;
			Boss.index = enemyData["index"].asInt();
            Boss.taskid = 0;
          
            // ��������ӵ�������
        }
    }

    // ע������¼�
    auto keyListener = cocos2d::EventListenerKeyboard::create();
    keyListener->onKeyPressed = CC_CALLBACK_2(BossScene::onKeyPressed, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);

    
    this->scheduleUpdate();
    return true;

    return true;
}

void BossScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
    cocos2d::Vec2 moveDir;
    switch (keyCode)
    {
        case cocos2d::EventKeyboard::KeyCode::KEY_W: moveDir = cocos2d::Vec2(0, 1); break;
        case cocos2d::EventKeyboard::KeyCode::KEY_S: moveDir = cocos2d::Vec2(0, -1); break;
        case cocos2d::EventKeyboard::KeyCode::KEY_A: moveDir = cocos2d::Vec2(-1, 0); break;
        case cocos2d::EventKeyboard::KeyCode::KEY_D: moveDir = cocos2d::Vec2(1, 0); break;
        default: return;
    }
    rawPlayer1->setPosition(rawPlayer1->getPosition() + moveDir * 100);
	rawPlayer1->Sprite::setPosition(rawPlayer1->getPosition());
}
// �����߼�
bool BossScene::IsColliding(cocos2d::Vec2 position)
{
    // ��ȡ���ؾ��鵱ǰ��������
    auto playerPos = rawPlayer1->getPosition();
    auto x = position.x, y = position.y;

    // ��ȡ��Ƭ��ͼ����Ƭ��С
    auto tileSize = _tileMap->getTileSize();

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
    // ��ȡ���˵���Ϣ 
    cocos2d::ValueMap bossData = objectGroup->getObject("Boss");

    if (!bossData.empty())
    {
        GlobalManager::getInstance().setBattleNpc(GlobalManager::getInstance().getEnemyNpcsBoss());
        auto bos = Boss.bossSprite;
        bool isColliding = rawPlayer1->getBoundingBox().intersectsRect(bos->getBoundingBox());

        if (isColliding && !_currentDialogueBox && !_currentChoiceBox && !bos->getUserData())
        {
            bos->setUserData((void*)1); // ����ѽ�
			CCLOG("Collide npc");
            displayChoice1(bos, "You can't save the princess!!!Hahahaha!!!\nDo you want to talk with me?", {
    {"Yes",[this, bos]() { {
            // ��ʱ��ʾ��һ���Ի��򣬱����ڵ�
            this->scheduleOnce([=](float) {
                handleChatNPC(bos);
            }, 0.1f, "handleChatNPC");
        } }},
    {"No",[this, bos] () { {
            // ��ʱ��ʾ��һ���Ի��򣬱����ڵ�
            this->scheduleOnce([=](float) {
                displayTaskPro(Boss);
            }, 0.1f, "displaybossNPC");
        } }}
                });
        }
        // �������� NPC û����ײ����֮ǰ�Ѿ��������������ý���״̬
        else if (!isColliding && bos->getUserData() != nullptr)
        {
            bos->setUserData(nullptr);  // ���ý���״̬�������ٴδ���
        }
    }
   
}

void BossScene::displayChoice1(cocos2d::Sprite* npc, const std::string& question,
    const std::vector<std::pair<std::string, std::function<void()>>>& choices)
{
    if (_currentChoiceBox) {																					           		  // ������ڵ�ǰ�Ի����Ƴ���
        _currentChoiceBox->removeFromParent();
        _currentChoiceBox = nullptr;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    _currentChoiceBox = cocos2d::Sprite::create("smallmap/box.png");
    //_currentChoiceBox->setPosition(npc->getPosition() + cocos2d::Vec2(0, 80)); 
    _currentChoiceBox->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
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
        else if (i == 1) {
            button = cocos2d::ui::Button::create("No1.png", "No2.png");
        }
        //button->setTitleText(choices[i].first);
        //button->setTitleFontName("fonts/Marker Felt.ttf");
        //button->setTitleFontSize(24);
        button->setPosition(cocos2d::Vec2(_currentChoiceBox->getContentSize().width / 4 + i * 300 + 30, _currentChoiceBox->getContentSize().height / 4));
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

void BossScene::handleChatNPC(cocos2d::Sprite* npc)
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

void BossScene::displayChoice2(cocos2d::Sprite* npc, const std::string& question,
    const std::vector<std::pair<std::string, std::function<void()>>>& choices)
{

    // ȷ���ɶԻ������
    if (_currentChoiceBox) {
        _currentChoiceBox->removeFromParent();
        _currentChoiceBox = nullptr;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();												// ��ȡ�ɼ�����Ĵ�С
    _currentChoiceBox = cocos2d::Sprite::create("smallmap/box.png");
    _currentChoiceBox->setPosition(Vec2(visibleSize.width / 2,visibleSize.height*3/4));
    this->addChild(_currentChoiceBox, 1);
    _currentChoiceBox->setLocalZOrder(100);

    auto label = cocos2d::Label::createWithTTF(question, "fonts/Marker Felt.ttf", 48);
    label->setTextColor(cocos2d::Color4B::BLACK);
    label->setPosition(_currentChoiceBox->getContentSize().width / 2, _currentChoiceBox->getContentSize().height / 2);
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
        button->setPosition(cocos2d::Vec2(cocos2d::Vec2(_currentChoiceBox->getContentSize().width / 2, buttonY + i * 150 -200)));
        _currentChoiceBox->addChild(button);

        button->addClickEventListener([=](cocos2d::Ref* sender) {
            if (choices[i].second) {
                choices[i].second();  // ִ��ѡ���Ļص�
            }
            // �ڻص������Ƴ��Ի���
            _currentChoiceBox->removeFromParent();
            _currentChoiceBox = nullptr;
            });
    }
}
// NPC �ش���ڳ�������
void BossScene::displayTownInfo(cocos2d::Sprite* npc)
{
    displayChoice2(npc, "This is a peaceful town. You can find a shop, a tavern, and a blacksmith.", {
        {"I see, tell me more!", [this, npc]() { {
                // ��ʱ��ʾ��һ���Ի��򣬱����ڵ�
                this->scheduleOnce([=](float) {
                    displayTownDetails(npc);
                }, 0.1f, "handleChatNPC");
            } }},
        {"That's enough, thanks!", [this, npc]() { {
                // ��ʱ��ʾ��һ���Ի��򣬱����ڵ�
                this->scheduleOnce([=](float) {
                    displayGoodbye(npc);
                }, 0.1f, "handleChatNPC");
            } }}
        });
}

// NPC ��ϸ���ܳ���
void BossScene::displayTownDetails(cocos2d::Sprite* npc)
{
    displayDialogue(npc, "The shop sells potions, the tavern offers drinks and rumors, and the blacksmith can upgrade your gear.");
}

// NPC ����������Ϣ
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
            // ��������״̬Ϊ�ѷ���
            npcData.ppp->state = 0;
            // ��ת�� NPC ���õ�Ŀ�곡��
            CCLOG("message", npcData.targetScene);
            rawPlayer1->removeFromParent();
            GlobalManager::getInstance().setLastMap("smallmap/castle.tmx");
            const auto& taskListbat = GlobalManager::getInstance().getTasks();
            taskListbat[0]->id = 0;
            Director::getInstance()->replaceScene(TransitionFade::create(1.0f, BattleScene::create()));
            npcData.ppp->state = 1;

        }},
        {"NO", nullptr}
        });
}
// NPC ��ϸ������Ϣ
void BossScene::displayQuestDetails(cocos2d::Sprite* npc)
{
    displayDialogue(npc, "The herbs grow near the forest. Please bring them back to me once you've collected them.");
}

// NPC ˵���ټ���
void BossScene::displayGoodbye(cocos2d::Sprite* npc)
{
    displayDialogue(npc, "Goodbye, and good luck on your adventures!");
}



void BossScene::displayDialogue(Sprite* npc, const std::string& text)
{
    // ������ڵ�ǰ�Ի����Ƴ���
    if (_currentDialogueBox) {
        _currentDialogueBox->removeFromParent();
        _currentDialogueBox = nullptr;
    }

    // �����Ի���
    auto dialogueBox = Sprite::create("box3.png");
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