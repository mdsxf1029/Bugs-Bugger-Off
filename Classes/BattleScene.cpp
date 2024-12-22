#include "BattleScene.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "HelloWorldScene.h" 
#include<random>
#include<cstdlib>
#include"Map/MiniMap.h"
#include"SmallTask/QuizGame.h"
std::shared_ptr<Player> rawPlayer = GlobalManager::getInstance().getPlayer();

const int ATTACKRADIUS = 1000.0f;//��󹥻��뾶
const int NEARESTLENGTH = 100.0f;//�������
// ��ȡ����ָ��ָ��� Player �����ָ��

// ���캯������������
BattleScene::BattleScene()
    : _battleState(BattleState::IDLE),
    _tileMap(nullptr),
    _skillDirection(cocos2d::Vec2::ZERO),
    _currentSkillState(SkillState::NONE), // ��ʼ����״̬ΪNONE
    _enemyHealthLabel(nullptr),
    _playerHealthLabel(nullptr)
{
}

BattleScene::~BattleScene() {}

bool BattleScene::init()
{
    const  auto visibleSize = Director::getInstance()->getVisibleSize();
    const  auto origin = Director::getInstance()->getVisibleOrigin();
     
	if (!Scene::init())                                                             //��� ��ʼ��ʧ��  ����false
    {
        return false;
    }

    // ���� TMX ��ͼ
    _tileMap = cocos2d::TMXTiledMap::create("smallmap/battlefeild.tmx");
    _tileMap->setScale(8.0f);
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
            try {
               // rawPlayer = GlobalManager::getInstance().getPlayer();

                                                                                                        // 1. ��ָ����
                if (rawPlayer == nullptr) {
                    throw std::runtime_error("Player initialization failed: null pointer");
                }

                                                                                                        // 2. ��ʼ�����
               // if (!rawPlayer->init()) {
                   // throw std::runtime_error("Player initialization failed");
               // }
            }
            catch (const std::exception& e) {
                CCLOG("Exception during initialization: %s", e.what());
                cleanup(); 
				throw;                                                                                  // �����׳��쳣���ϲ㴦��
            } 
			rawPlayer->initWithFile(rawPlayer->getFileName());											// ��ʼ�����
            rawPlayer->setContentSize(playerSize);
            rawPlayer->setPosition(Vec2(playerX * 8, playerY * 8));
            rawPlayer->Sprite::setPosition(rawPlayer->getPosition());
            this->addChild(rawPlayer.get(),10);  // �������ӵ�������
        }

        // ��ȡ���˵���Ϣ 
        cocos2d::ValueMap enemyData = objectGroup->getObject("NPC");

        if (!enemyData.empty())
        {
            float enemyX = enemyData["x"].asFloat();
            float enemyY = enemyData["y"].asFloat();
            
            try {
                rawEnemy = GlobalManager::getInstance().getBattleNpc();
                // 1. ��ָ����
                if (rawEnemy == nullptr) {
                    throw std::runtime_error("Player initialization failed: null pointer");
                }

                // 2. ��ʼ�����
                if (!rawEnemy->init()) {
                    throw std::runtime_error("Player initialization failed");
                }
            }
            catch (const std::exception& e) {
                CCLOG("Exception during initialization: %s", e.what());
                cleanup();
                // �����׳��쳣���ϲ㴦��
                throw;
            }
			rawEnemy->initWithFile();                                               // ��ʼ������
			rawEnemy->setContentSize(playerSize);                                   // ���õ��˵Ĵ�С
			rawEnemy->setPosition(Vec2(enemyX * 8, enemyY * 8));					// ���õ��˵�λ��
			enemyskill = rawEnemy->getSkill();                                      // ��ȡ���˵ļ���
            this->addChild(rawEnemy.get(), 10);                                     // ��������ӵ�������
        }
    }

    

    // ������������Ч��
    askillList.at(0)->_effect = cocos2d::ParticleSystemQuad::create(askillList.at(0)->_info.particleFile);//��ʼ����Ч
    askillList.at(0)->_effect->setVisible(false);                                                         //��ʼʱ���� 
    this->addChild(askillList.at(0)->_effect, 10);
    askillList.at(1)->_effect = cocos2d::ParticleSystemQuad::create(askillList.at(1)->_info.particleFile);//��ʼ����Ч
    askillList.at(1)->_effect->setVisible(false);                                                         //��ʼʱ����
    this->addChild(askillList.at(1)->_effect, 10);
    askillList.at(2)->_effect = cocos2d::ParticleSystemQuad::create(askillList.at(2)->_info.particleFile);//��ʼ����Ч
    askillList.at(2)->_effect->setVisible(false);                                                         //��ʼʱ����
    this->addChild(askillList.at(2)->_effect, 10);

    enemyskill->_effect = cocos2d::ParticleSystemQuad::create(enemyskill->_info.particleFile);            //��ʼ����Ч
    enemyskill->_effect->setVisible(false);                                                               //��ʼʱ����
    this->addChild(enemyskill->_effect, 10);

	askillList.at(0)->setColor(rawPlayer->getElement());                                                    //���ü�����ɫ
    askillList.at(1)->setColor(rawPlayer->getElement());
    askillList.at(2)->setColor(rawPlayer->getElement());
    enemyskill->setColor(rawEnemy->getElement());
    
    _playerHealthLabel = cocos2d::Label::createWithTTF("Health: 100", "fonts/Marker Felt.ttf", 48);// ����һ�� Label ����ʾ��ҵ�ǰ������ֵ 
    if (_playerHealthLabel != nullptr)
    {
        _playerHealthLabel->setPosition(cocos2d::Vec2(rawPlayer->getPosition().x, rawPlayer->getPosition().y + 150));
        this->addChild(_playerHealthLabel, 1);                                                     // �� Label ��ӵ�������
    }         
	_enemyHealthLabel = cocos2d::Label::createWithTTF("Health: 100", "fonts/Marker Felt.ttf", 48);// ����һ�� Label ����ʾ���˵�ǰ������ֵ
    if (_enemyHealthLabel != nullptr)
    {
        _enemyHealthLabel->setPosition(cocos2d::Vec2(rawEnemy->getPosition().x, rawEnemy->getPosition().y + 150));
        this->addChild(_enemyHealthLabel, 1);                                                      // �� Label ��ӵ�������
    }

    // ���ó�������
    schedule([=](float deltaTime) 
    {
        update(deltaTime);
    }, "update_key");

    // ���ü��̺��������¼�
	auto listenerKeyboard = cocos2d::EventListenerKeyboard::create();                               // �������̼�����
	listenerKeyboard->onKeyPressed = CC_CALLBACK_2(BattleScene::onKeyPressed, this);                // ���ð������µĻص�����
	listenerKeyboard->onKeyReleased = CC_CALLBACK_2(BattleScene::onKeyReleased, this);  	        // ���ð����ͷŵĻص�����
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKeyboard, this);			    // ��Ӽ��̼�����������

	auto listenerMouse = cocos2d::EventListenerMouse::create();									    // ������������
	listenerMouse->onMouseDown = CC_CALLBACK_1(BattleScene::onMouseDown, this);					    // ������갴�µĻص�����
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerMouse, this);				    // �����������������

    return true;
}

void BattleScene::update(float delta)
{
    if (!gameOver)
    {    // ���¼���Ч��  ��λ��
		cooldownTime -= delta;                                                                 // ������ȴʱ��
        if(cooldownTime<=0)
			cooldownTime = 0;                                                                  // ��ȴʱ��С��0ʱ������Ϊ0
        if (askillList.at(0)->_effect->isVisible())
        {
            askillList.at(0)->_effect->setPosition(rawPlayer->getPosition());                   // ��������ϵͳ��λ��
        }

        if (askillList.at(1)->_effect->isVisible())
        {
            askillList.at(1)->_effect->setPosition(rawPlayer->getPosition());                   // ��������ϵͳ��λ��
        }

        if (askillList.at(2)->_effect->isVisible())
        {
            askillList.at(2)->_effect->setPosition(rawPlayer->getPosition());                   // ��������ϵͳ��λ��
        }
        if (enemyskill->_effect->isVisible())
        {
            enemyskill->_effect->setPosition(rawEnemy->getPosition());                          // ��������ϵͳ��λ��    
        }
        enemyMove();                                                                            // �����ƶ�
        EnemyAttack();  														    		    // ���˹���                                       

        if (rawEnemy != nullptr)                                                                // ���µ�������ֵ����ʾ
        {
            // ������ʾ�ĵ�������ֵ
            _enemyHealthLabel->setString("Health: " + std::to_string(rawEnemy->getHp()));
            // ���� Label λ�ã�ʹ��ʼ�ո������
            _enemyHealthLabel->setPosition(cocos2d::Vec2(rawEnemy->getPosition().x, rawEnemy->getPosition().y + 150));
        }
        if (rawPlayer != nullptr)   												            // �����������ֵ����ʾ                                                
        {
            // ������ʾ���������ֵ
            _playerHealthLabel->setString("Health: " + std::to_string(rawPlayer->getHp()));
            // ���� Label λ�ã�ʹ��ʼ�ո������
            _playerHealthLabel->setPosition(cocos2d::Vec2(rawPlayer->Sprite::getPosition().x, rawPlayer->Sprite::getPosition().y + 150));
        }

        // ���ս���Ƿ����
        checkBattleOver();
    }
}

void BattleScene::onMouseDown(cocos2d::Event* event)
{
    // ��ͨ���¼�ת��Ϊ����¼�
    cocos2d::EventMouse* mouseEvent = dynamic_cast<cocos2d::EventMouse*>(event);
    if (mouseEvent&&!gameOver)
    {
        float degrees;
        // ��ȡ���������������
        cocos2d::Vec2 clickPosition = mouseEvent->getLocation();                                // ʹ�� getLocation() ��ȡ���λ��
		CCLOG("Mouse clicked at (%f, %f)", clickPosition.x, clickPosition.y);                   // ����������λ��
		Vec2 mapclickPosition = Vec2(clickPosition.x, 1000 - clickPosition.y);                  // ��ȡ��ͼ�����λ��
		CCLOG("mapclickPosition at (%f, %f)", mapclickPosition.x, mapclickPosition.y);          // �����ͼ�����λ��
		if (mouseEvent->getMouseButton() == cocos2d::EventMouse::MouseButton::BUTTON_RIGHT)     // �Ҽ����
        {
			_battleState = BattleState::ATTACKING;                                              // ����ս��״̬Ϊ����
            if (_currentSkillState == SkillState::SKILL_1) {
                degrees = askillList.at(1)->cast(rawPlayer.get(), mapclickPosition);            // ִ��һ���� �ǶȻ�ȡ
                askillList.at(1)->_effect->setAngle(degrees);                                  // �������ӵķ���Ƕ� 
				askillList.at(1)->_effect->setPosition(rawPlayer->getPosition());              // ��������ϵͳ��λ�� 
                askillList.at(1)->_effect->setVisible(true);                                    // ��������Ч��������
                askillList.at(1)->_effect->resetSystem();                                       // ��������ϵͳ 
                scheduleOnce([this](float dt) {                                                 // ���ü��ܳ���ʱ�䣨2�룩
                    // 2���ֹͣ����Ч��
                    askillList.at(1)->_effect->stopSystem();                                    // ֹͣ����ϵͳ
                    askillList.at(1)->_effect->setVisible(false);                               // ��������ϵͳ
                    }, 1.0f, "stop_skill_effect");                                              // 2������
                _battleState = BattleState::ATTACKING;
                if (askillList.at(1)->isInRange(rawPlayer->getPosition(), rawEnemy->getPosition(), mapclickPosition))//�ж��Ƿ��ڹ�����Χ��
                {
                    if (rawEnemy->getElement() > rawPlayer->getElement())                                               //�жϵ��˵�Ԫ���Ƿ������ҵ�Ԫ��
                        rawEnemy->TakeDamage((askillList.at(1)->getAttack() + rawPlayer->getAttack()) / 2);             //�����ܵ��˺�����
                    else if (rawEnemy->getElement() > rawPlayer->getElement())  						                //�ж���ҵ�Ԫ���Ƿ���Ƶ��˵�Ԫ��
                        rawEnemy->TakeDamage((askillList.at(1)->getAttack() + rawPlayer->getAttack()) * 2);             //�����ܵ��˺�����
                    else
                        rawEnemy->TakeDamage(askillList.at(1)->getAttack() + rawPlayer->getAttack());                   //��ͨ�����˺�
                    CCLOG("Enemy is HURT!");
                }
            }
            else if (_currentSkillState == SkillState::SKILL_2) {
                degrees = askillList.at(2)->cast(rawPlayer.get(), mapclickPosition);            // ִ��һ����  
                askillList.at(2)->_effect->setAngle(degrees);                                   // �������ӵķ���Ƕ�
                CCLOG("degrees:%f", degrees);
                
                askillList.at(2)->_effect->setPosition(rawPlayer->getPosition());               // ��������ϵͳ��λ��
                 
				askillList.at(2)->_effect->setVisible(true);									// ��������Ч��������
                askillList.at(2)->_effect->resetSystem();                                       // ��������ϵͳ
                 
                scheduleOnce([this](float dt) {
                                                                                                // 2���ֹͣ����Ч��
                    askillList.at(2)->_effect->stopSystem();                                    // ֹͣ����ϵͳ
                    askillList.at(2)->_effect->setVisible(false);                               // ��������ϵͳ
                    }, 1.0f, "stop_skill_effect");                                              // 2������
                _battleState = BattleState::ATTACKING;
                if (askillList.at(2)->isInRange(rawPlayer->getPosition(), rawEnemy->getPosition(), mapclickPosition))//�ж��Ƿ��ڹ�����Χ��
                {
                    if (rawEnemy->getElement() > rawPlayer->getElement())                                               //�жϵ��˵�Ԫ���Ƿ������ҵ�Ԫ��
                        rawEnemy->TakeDamage((askillList.at(2)->getAttack() + rawPlayer->getAttack()) / 2);             //�����ܵ��˺�����
                    else if (rawEnemy->getElement() > rawPlayer->getElement())  						                //�ж���ҵ�Ԫ���Ƿ���Ƶ��˵�Ԫ��
                        rawEnemy->TakeDamage((askillList.at(2)->getAttack() + rawPlayer->getAttack()) * 2);             //�����ܵ��˺�����
                    else
                        rawEnemy->TakeDamage(askillList.at(2)->getAttack() + rawPlayer->getAttack());                   //��ͨ�����˺�
                    CCLOG("Enemy is HURT!");
                }
            }
        }
        else if (mouseEvent->getMouseButton() == cocos2d::EventMouse::MouseButton::BUTTON_LEFT)
        {// ��ͨ����
            degrees = askillList.at(0)->cast(rawPlayer.get(), mapclickPosition);                            // ִ����ͨ������Ч 
            askillList.at(0)->_effect->setAngle(degrees);                                                   // �������ӵķ���Ƕ� 
			askillList.at(0)->_effect->setPosition(rawPlayer->getPosition());							    // ��������ϵͳ��λ��  
			askillList.at(0)->_effect->setVisible(true);												    // ��������Ч��������
            askillList.at(0)->_effect->resetSystem();                                                       // ��������ϵͳ

            // ���ü��ܳ���ʱ�䣨2�룩
            scheduleOnce([this](float dt) {
                // 2���ֹͣ����Ч��
                askillList.at(0)->_effect->stopSystem();                                                    // ֹͣ����ϵͳ
                askillList.at(0)->_effect->setVisible(false);                                               // ��������ϵͳ
                }, 1.0f, "stop_skill_effect");                                                              // 2������
            _battleState = BattleState::ATTACKING;
            if (askillList.at(0)->isInRange(rawPlayer->getPosition(), rawEnemy->getPosition(), mapclickPosition))
            {
                if (rawEnemy->getElement() > rawPlayer->getElement())                                               //�жϵ��˵�Ԫ���Ƿ������ҵ�Ԫ��
                    rawEnemy->TakeDamage((askillList.at(0)->getAttack() + rawPlayer->getAttack()) / 2);             //�����ܵ��˺�����
                else if (rawEnemy->getElement() > rawPlayer->getElement())  						                //�ж���ҵ�Ԫ���Ƿ���Ƶ��˵�Ԫ��
                    rawEnemy->TakeDamage((askillList.at(0)->getAttack() + rawPlayer->getAttack()) * 2);             //�����ܵ��˺�����
                else
                    rawEnemy->TakeDamage(askillList.at(0)->getAttack() + rawPlayer->getAttack());                   //��ͨ�����˺�
                CCLOG("Enemy is HURT!");
            }
        }
    }

    // �ı�ս��״̬�ص�����
    _battleState = BattleState::IDLE;
    cocos2d::log("Player is attacking!");
}




void BattleScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    if (rawPlayer == nullptr) return;

    // ͨ�� Z ���л�Ϊһ���ܣ�X ���л�Ϊ������
    Vec2 nextpos = rawPlayer->getPosition();
    CCLOG("Key with keycode %d pressed", keyCode);
    switch (keyCode)
    {
        case cocos2d::EventKeyboard::KeyCode::KEY_SHIFT:
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_Z:
            _currentSkillState = SkillState::SKILL_1;  // �л���һ����
            cocos2d::log("Skill 1 selected.");
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_X:
            _currentSkillState = SkillState::SKILL_2;  // �л���������
            cocos2d::log("Skill 2 selected.");
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_W:
            nextpos.y = rawPlayer->getPosition().y + rawPlayer->getSpeed() * Director::getInstance()->getDeltaTime();
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_S:
            nextpos.y = rawPlayer->getPosition().y - rawPlayer->getSpeed() * Director::getInstance()->getDeltaTime();
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_A:
            nextpos.x = rawPlayer->getPosition().x - rawPlayer->getSpeed() * Director::getInstance()->getDeltaTime();
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_D:
            nextpos.x = rawPlayer->getPosition().x + rawPlayer->getSpeed() * Director::getInstance()->getDeltaTime();
            break;
        default:
            break;
    }
    rawPlayer->setPosition(nextpos);
    rawPlayer->Sprite::setPosition(nextpos);
    CCLOG("next_position:%f %f", nextpos.x, nextpos.y);
}

void BattleScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_Z || keyCode == cocos2d::EventKeyboard::KeyCode::KEY_X) {
        _currentSkillState = SkillState::NONE;  // �ͷż��ܼ��󽫼���״̬����ΪNONE
    }
    else {
        switch (keyCode)
        {
            case EventKeyboard::KeyCode::KEY_W:
                rawPlayer->isMovingUp = false;
                break;
            case EventKeyboard::KeyCode::KEY_S:
                rawPlayer->isMovingUp = false;
                break;
            case EventKeyboard::KeyCode::KEY_A:
                rawPlayer->isMovingUp = false;
                break;
            case EventKeyboard::KeyCode::KEY_D:
                rawPlayer->isMovingUp = false;
                break;
        }
    }
}

void BattleScene::checkBattleOver()
{
    // ���ս���Ƿ���� 
     // ���ս���Ƿ����
	if (rawEnemy->getHp() == 0 && rawEnemy->getLevel() >= 2)                            //�ж������Ƿ����         
    {
        ElementType type = rawEnemy->getElement();
        std::vector <std::shared_ptr< Task >> tasklist = GlobalManager::getInstance().getTasks();
        switch (type)
        {
            case ElementType::Gold:
                tasklist.at(1)->state = 1;
                break;
            case ElementType::Wood:
                tasklist.at(2)->state = 1;
                break;
            case ElementType::Earth:
                tasklist.at(3)->state = 1;
                break;
            case ElementType::Water:
                tasklist.at(4)->state = 1;
                break;
            case ElementType::Fire:
                tasklist.at(5)->state = 1;
                break;
        }
        if(rawEnemy->getLevel()==3)                                                     //boss
		{
			tasklist.at(0)->state = 1;                                                  //������������
		}
    }
    if (rawPlayer->getHp() == 0)                                                        //���������
    {
        // �������ֱ�ǩ
        auto winLabel = Label::createWithTTF("YOU LOSE", "fonts/arial.ttf", 80);
        Size visibleSize = Director::getInstance()->getVisibleSize();                   //��ȡvisibleSize
        winLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));     //��λ������
        winLabel->setColor(Color3B::YELLOW);                                            // ������ɫ
        this->addChild(winLabel);                                                       //����child
    }
    else if (rawEnemy->getHp() == 0)                                                    //�����Ӯ��
    { // �������ֱ�ǩ
        auto winLabel = Label::createWithTTF("YOU WIN!", "fonts/arial.ttf", 80);
        Size visibleSize = Director::getInstance()->getVisibleSize();                  //��ȡvisibleSize
        winLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));    //��λ������
        winLabel->setColor(Color3B::RED);                                              // ������ɫ
        this->addChild(winLabel,99);
        rawEnemy->dead();
        //rawEnemy->removeFromParent();
        //Director::getInstance()->replaceScene(TransitionFade::create(1.0f, MiniMap::create()));
        //Ϊ�˵���zhushidiao
    }
	if (rawPlayer->getHp() == 0 || rawEnemy->getHp() == 0)
	{
        rawPlayer->setHp(rawPlayer->getMaxHp());
        const auto& taskListbat = GlobalManager::getInstance().getTasks();
		int id=taskListbat[0]->getid();
		taskListbat[id]->state = 1;
        gameOver = true;
		endBattle();
	}
}

void BattleScene::endBattle()
{
    auto exitButton = cocos2d::ui::Button::create("CloseNormal.png", "CloseSelected.png");
    if (!exitButton)
    {
        CCLOGERROR("Failed to create exit button.");
        return;
    }

    // ���ð�ťλ�ã���Ļ���Ͻǣ�
    auto visibleSize = Director::getInstance()->getVisibleSize();               // ��ȡ��Ļ�ߴ�
    auto origin = Director::getInstance()->getVisibleOrigin();				    // ��ȡ��Ļԭ��
    exitButton->setPosition(cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 2-100));						    // ���ð�ťλ��

    // ���ð�ť����¼�
    
    exitButton->addClickEventListener([](Ref* sender) {
        CCLOG("Exit button clicked. Exiting game.");
        rawPlayer->removeFromParent();
        auto newScene = MiniMap::createWithMap(GlobalManager::getInstance().getLastMap(), false);
        Director::getInstance()->replaceScene(TransitionFade::create(1.0f, newScene));  // �˳���Ϸ
        });

    this->addChild(exitButton, 10);                                             // ��Ӱ�ť������
}


void BattleScene::enemyMove()
{
    // �����ƶ��߼�
    // �������������ӵ����ƶ����߼�
    Vec2 playerPos = rawPlayer->getPosition();
    Vec2 enemyPos = rawEnemy->getPosition();
    float thedistance = playerPos.distance(enemyPos);
    if (thedistance > NEARESTLENGTH)
    {
        if (playerPos.y < enemyPos.y) {//�����ҵ�y����С�ڵ��˵�y����
            enemyPos.y -= 50 * Director::getInstance()->getDeltaTime();
        }
        else
            enemyPos.y += 50 * Director::getInstance()->getDeltaTime();

        if (playerPos.x < enemyPos.x) {//
            enemyPos.x -= 50 * Director::getInstance()->getDeltaTime();
        }
        else
            enemyPos.x += 50 * Director::getInstance()->getDeltaTime();
        CCLOG("enemy position:%f %f", enemyPos.x, enemyPos.y);
        CCLOG("player position:%f %f", playerPos.x, playerPos.y);
    }
    rawEnemy->setPosition(enemyPos);

}

void BattleScene::EnemyAttack()
{// ���˹����߼�
    std::srand(std::time(0));                                               // �������������
    Vec2 rawplayerpos = rawPlayer->getPosition();                           //���λ��
    Vec2 rawenemypos = rawEnemy->getPosition();                             //����λ��  
    float thedistance = rawplayerpos.distance(rawenemypos);                 //����
    float degrees = askillList.at(0)->cast(rawEnemy.get(), rawplayerpos);   // ִ�й��� �ĽǶ���� 
    enemyskill->_effect->setAngle(degrees);                                 // �������ӵķ���Ƕ� 
	enemyskill->_effect->setPosition(rawEnemy->getPosition());			    // ��������ϵͳ��λ��
    int randomnum1 = std::rand() % 100 + 1;                                 // ���� 1 �� 100 ֮��������
    
	if (enemyskill->isInRange(rawPlayer->getPosition(), rawEnemy->getPosition()))//�ж��Ƿ��ڹ�����Χ��
    {
		if (randomnum1 > 50&&cooldownTime==0)                                                    // 10%�ĸ���ʹ�ü���
        {
			cocos2d::log("Enemy is attacking!");                                // ����������ڹ���
            enemyskill->_effect->setVisible(true);  						    // ��������Ч��������                                
            enemyskill->_effect->resetSystem();                                 // ��������ϵͳ
            scheduleOnce([this](float dt) {
                enemyskill->_effect->stopSystem();                              // ֹͣ����ϵͳ
                enemyskill->_effect->setVisible(false);                         // ��������ϵͳ
				}, 2.0f, "stop_skill_effect");                                  // 2s�����
            _battleState = BattleState::ATTACKING;                              //����ս��״̬    
        }
        int randomnum = std::rand() % 100 + 1;                                  // ���� 1 �� 100 ֮��������
        if (randomnum > 80&& cooldownTime == 0)                                                             //10%�Ļ��и���
        {
			// �жϵ���Ԫ�������Ԫ�صĹ�ϵ
            if (rawEnemy->getElement() > rawPlayer->getElement())                                          //�жϵ��˵�Ԫ���Ƿ������ҵ�Ԫ��
                rawPlayer->TakeDamage((askillList.at(1)->getAttack() + rawPlayer->getAttack()) * 2);       //����ܵ��˺��ӱ�
            else if (rawEnemy->getElement() > rawPlayer->getElement())  						           //�ж���ҵ�Ԫ���Ƿ���Ƶ��˵�Ԫ��
                rawPlayer->TakeDamage((askillList.at(1)->getAttack() + rawPlayer->getAttack()) / 2);       //����ܵ��˺�����
            else
                rawPlayer->TakeDamage(rawEnemy->getAttack() + enemyskill->getAttack());                    //����ܵ���ͨ�˺�    
            cooldownTime = 2.0f;    								                                       // ������ȴʱ��       
        }
    
        CCLOG("Player is HURT!");
    }

    // �ı�ս��״̬�ص�����
    _battleState = BattleState::IDLE;

}

