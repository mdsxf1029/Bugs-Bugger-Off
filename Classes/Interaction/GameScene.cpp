#include "GameScene.h"
#include "ui/CocosGUI.h"
#include "HelloWorldScene.h"
#include<vector>
#include <utility>  // std::pair
#include"QuizGame.h"
#include"BattleScene.h"
#include"sets\tasks.h"
#include"manager.h"
USING_NS_CC;

// ���캯������������
GameScene::GameScene() : _tileMap(nullptr),  _currentDialogueBox(nullptr), _currentChoiceBox(nullptr){}
GameScene::~GameScene() {}
std::shared_ptr<Player> _player = GlobalManager::getInstance().getPlayer();
// ��������
cocos2d::Scene* GameScene::createScene()
{
    return GameScene::create();
}


bool GameScene::init()
{

    if (!Scene::init()) return false;
   

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // ������ǩ
    auto label = Label::createWithTTF("jjj", "fonts/Marker Felt.ttf", 24);
    if (label != nullptr) {
        label->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height - label->getContentSize().height));
        this->addChild(label, 1);
    }

    // ���ص�ͼ
    _tileMap = cocos2d::TMXTiledMap::create("whole3.tmx");
    this->addChild(_tileMap);

    // ��ʼ�����
    auto objectGroup = _tileMap->getObjectGroup("Objects");
    auto ojectGroup = _tileMap->getObjectGroup("TransportPoint");
    auto boxGroup = _tileMap->getObjectGroup("Boxs");
    auto playerObj = objectGroup->getObject("Player");
    float playerX = playerObj["x"].asFloat();
    float playerY = playerObj["y"].asFloat();
   
    _player->initWithFile("NPC1.png");
    
    _player->setPosition(Vec2(playerX, playerY));
    
    this->addChild(_player.get());
    const auto& taskList = GlobalManager::getInstance().getTasks();
    // ��ʼ�� NPC ���������ͷ���
    auto npcGroup = objectGroup->getObjects();
    
    int i = 0,j=0;
    for (auto& npcObj : npcGroup)
    {
     
        cocos2d::ValueMap npcData = npcObj.asValueMap();
        if (!npcData.empty()) {
           

            
            auto task = taskList[i];
            

            
            std::string npcFunction = npcData["npcFunction"].asString();
            std::string targetScene = npcData["targetScene"].asString();
            std::string type = npcData["type"].asString();
            

            if (type == "NPC") {
                auto npc = cocos2d::Sprite::create("NPC1.png");
                npc->setPosition(npcData["x"].asFloat(), npcData["y"].asFloat());

                this->addChild(npc);
                // �Ի���NPC
                if(npcFunction=="chat")
                _npcList.push_back({ npc, npcFunction, taskList[i],targetScene });
                else
                    _npcList.push_back({ npc, npcFunction, taskList[i++],targetScene });

            }
            else if (type == "box") {
                auto npc = cocos2d::Sprite::create("boxlqy.png");
                npc->setPosition(npcData["x"].asFloat(), npcData["y"].asFloat());

                this->addChild(npc);
                // ������NPC
                _npcList.push_back({ npc, npcFunction, taskList[i],targetScene });
                i++;
            }
            else if (type == "monster") {
                auto npc = cocos2d::Sprite::create("monster.png");
                npc->setPosition(npcData["x"].asFloat(), npcData["y"].asFloat());

                this->addChild(npc);
                _npcList.push_back({ npc, npcFunction, taskList[i],targetScene });
                i++;
            }
        }
        
    }
    
    
    // ע������¼�
    auto keyListener = cocos2d::EventListenerKeyboard::create();
    keyListener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);

    // ע������¼�
    auto mouseListener = cocos2d::EventListenerMouse::create();
    mouseListener->onMouseUp = CC_CALLBACK_1(GameScene::onMouseUp, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

    this->scheduleUpdate();
    return true;
}


// �����߼�
void GameScene::update(float delta)
{
    for (auto& npcData : _npcList)
    {
        auto npc = npcData.npcSprite;


        // �������� NPC �Ƿ���ײ
        bool isColliding = _player->getBoundingBox().intersectsRect(npc->getBoundingBox());


        if (isColliding && !_currentDialogueBox&& !_currentChoiceBox && !npc->getUserData())
        {
            npc->setUserData((void*)1); // ����ѽ���
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
                // ������NPC
                switch (npcData.ppp->state) {
                case -1:
                    CCLOG("Task state before assignment: %d", npcData.ppp->state);
                    displayTaskPro(npcData); // ��ʾ����ѡ�񵯴�
                    break;
                case 0:
                    CCLOG("Task state before assignment: %d", npcData.ppp->state); // ��ӡ����״̬
                    displayDialogue(npc, "YOU've DONE"+ npcData.ppp->name);
                    //displayTaskStatus(npcData); // ��ʾ����״̬

                    break;
                case 1:
                    displayRewardOptions(npcData); // ��ʾ������ȡ����
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

                    displayTaskPro(npcData); // ��ʾ����ѡ�񵯴�
                    break;
                case 0:
                    CCLOG("Task state before assignment: %d", npcData.ppp->state); // ��ӡ����״̬
                    displayDialogue(npc, "YOU've DONE");
                    //displayTaskStatus(npcData); // ��ʾ����״̬

                    break;
                case 1:
                    displayRewardOptions(npcData); // ��ʾ������ȡ����
                    break;
                case 2:
                    displayDialogue(npc, "���Ѿ�������ҵ����񣬸�л��İ�����");
                    break;
                }
            }
        }
        // �������� NPC û����ײ����֮ǰ�Ѿ��������������ý���״̬
        else if (!isColliding && npc->getUserData() != nullptr)
        {
            npc->setUserData(nullptr);  // ���ý���״̬�������ٴδ���
        }
    }
}

// �������봦��
void GameScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
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
    _player->setPosition(_player->getPosition() + moveDir * playerSpeed);
}

// ����¼�����
void GameScene::onMouseUp(cocos2d::Event* event)
{
    // ����ӵ���߼�
}

void GameScene::displayChoice1(cocos2d::Sprite* npc, const std::string& question,
    const std::vector<std::pair<std::string, std::function<void()>>>& choices)
{
    // ������ڵ�ǰ�Ի����Ƴ���
    if (_currentChoiceBox) {
        _currentChoiceBox->removeFromParent();
        _currentChoiceBox = nullptr;
    }

    _currentChoiceBox = cocos2d::Sprite::create("box.png");
    _currentChoiceBox->setPosition(npc->getPosition() + cocos2d::Vec2(0, 80));
    this->addChild(_currentChoiceBox);
    _currentChoiceBox->setLocalZOrder(100); // �öԻ����ڽϸߵĲ㼶

    auto label = cocos2d::Label::createWithTTF(question, "fonts/Marker Felt.ttf", 48);
    label->setTextColor(cocos2d::Color4B::WHITE);
    label->setPosition(_currentChoiceBox->getContentSize().width / 2, _currentChoiceBox->getContentSize().height / 2 + 100);
    _currentChoiceBox->addChild(label, 1);
    label->setLocalZOrder(101);

    float buttonY = 50;
    for (size_t i = 0; i < choices.size(); ++i)
    {
        auto button = cocos2d::ui::Button::create("CloseNormal.png", "CloseSelected.png");
        button->setTitleText(choices[i].first);
        button->setTitleFontName("fonts/Marker Felt.ttf");
        button->setTitleFontSize(24);
        button->setPosition(cocos2d::Vec2(_currentChoiceBox->getContentSize().width / 2, buttonY + i * 100 + 300));
        _currentChoiceBox->addChild(button);

        button->addClickEventListener([=](cocos2d::Ref* sender) {
            if (choices[i].second) {
                choices[i].second();  // ִ��ѡ���Ļص�
            }
            // ��Ҫ�������Ƴ��Ի����������µĶԻ���
            _currentChoiceBox->removeFromParent();
            _currentChoiceBox = nullptr;

            });
    }
}

void GameScene::handleChatNPC(cocos2d::Sprite* npc)
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

void GameScene::displayChoice2(cocos2d::Sprite* npc, const std::string& question,
    const std::vector<std::pair<std::string, std::function<void()>>>& choices)
{

    // ȷ���ɶԻ������
    if (_currentChoiceBox) {
        _currentChoiceBox->removeFromParent();
        _currentChoiceBox = nullptr;
    }

    _currentChoiceBox = cocos2d::Sprite::create("boxx.png");
    _currentChoiceBox->setPosition(npc->getPosition() + cocos2d::Vec2(0, 80));
    this->addChild(_currentChoiceBox, 1);
    _currentChoiceBox->setLocalZOrder(100);

    auto label = cocos2d::Label::createWithTTF(question, "fonts/Marker Felt.ttf", 48);
    label->setTextColor(cocos2d::Color4B::BLACK);
    label->setPosition(_currentChoiceBox->getContentSize().width / 2, _currentChoiceBox->getContentSize().height / 2 + 100);
    _currentChoiceBox->addChild(label, 1);
    label->setLocalZOrder(101);

    float buttonY = 50;
    for (size_t i = 0; i < choices.size(); ++i)
    {
        auto button = cocos2d::ui::Button::create("CloseNormal.png", "CloseSelected.png");
        button->setTitleText(choices[i].first);
        button->setTitleFontName("fonts/Marker Felt.ttf");
        button->setTitleColor(cocos2d::Color3B::BLACK);
        button->setTitleFontSize(24);
        button->setPosition(cocos2d::Vec2(_currentChoiceBox->getContentSize().width / 2, buttonY + i * 100 + 300));
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
void GameScene::displayTownInfo(cocos2d::Sprite* npc)
{
    displayChoice2(npc, "This is a peaceful town. You can find a shop, a tavern, and a blacksmith.", {
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
void GameScene::displayTownDetails(cocos2d::Sprite* npc)
{
    displayDialogue(npc, "The shop sells potions, the tavern offers drinks and rumors, and the blacksmith can upgrade your gear.");
}

// NPC ����������Ϣ
void GameScene::displayQuestInfo(cocos2d::Sprite* npc)
{
    displayChoice2(npc, "I have a quest for you: Collect 10 herbs.", {

        {"Maybe later", [this, npc]() { displayGoodbye(npc); }},
        {"Tell me more", [this, npc]() { displayQuestDetails(npc); }}
        });
}

// NPC ��ϸ������Ϣ
void GameScene::displayQuestDetails(cocos2d::Sprite* npc)
{
    displayDialogue(npc, "The herbs grow near the forest. Please bring them back to me once you've collected them.");
}

// NPC ˵���ټ���
void GameScene::displayGoodbye(cocos2d::Sprite* npc)
{
    displayDialogue(npc, "Goodbye, and good luck on your adventures!");
}



void GameScene::displayDialogue(Sprite* npc, const std::string& text)
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
    dialogueBox->setPosition(npc->getPosition() + Vec2(0, 80));
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

void GameScene::displayTaskOptions(NPCData& npcData) {
    displayChoice1(npcData.npcSprite, npcData.ppp->name, {
        {"YES", [this, &npcData]() {
            npcData.ppp->state =0; // ��������״̬Ϊ�ѷ���
            // չʾ�Ի���
            displayDialogue(npcData.npcSprite, npcData.ppp->description);
        }},
        {"NO", nullptr}
        });
}

void GameScene::displayTaskPro(NPCData& npcData) {
    displayChoice1(npcData.npcSprite, npcData.ppp->name, {
        {"YES", [this, &npcData]() {
            npcData.ppp->state=0; // ��������״̬Ϊ�ѷ���
            // ��ת�� NPC ���õ�Ŀ�곡��
            CCLOG("message", npcData.targetScene);
            Director::getInstance()->replaceScene(TransitionFade::create(1.0f, getSceneByName(npcData.targetScene)));
            npcData.ppp->state = 1;
        }},
        {"NO", nullptr}
        });
}

void GameScene::displayTaskStatus(NPCData& npcData) {
    displayDialogue(npcData.npcSprite, "TASK");
}

void GameScene::displayRewardOptions(NPCData& npcData) {
    displayChoice1(npcData.npcSprite, "GOOD JOB,MONEY��", {
        {"OF COURSE", [this, &npcData]() {
            if (npcData.ppp->state ==1) {
                npcData.ppp->state =2; // �����������ȡ����
                displayDialogue(npcData.npcSprite, "CONGRAGULATION��");
            }
        }},
        {"LATER", nullptr}
        });
}

cocos2d::Scene* GameScene::getSceneByName(const std::string& sceneName) {
    if (sceneName == "QuizGame")
    {
        return QuizGame::create();  // ���� Task1Scene ����
    }
    else
        return HelloWorld::create();
}