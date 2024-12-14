#include "BattleScene.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "HelloWorldScene.h"

// ���캯������������
BattleScene::BattleScene()
    : _battleState(BattleState::IDLE),
    _player(nullptr),
    _enemy(nullptr),
    _skillEffect(nullptr),
    _tileMap(nullptr),
    _skillDirection(cocos2d::Vec2::ZERO),
    _currentSkillState(SkillState::NONE), // ��ʼ����״̬ΪNONE
    _skill1Effect(nullptr),
    _skill2Effect(nullptr),
    _enemyHealthLabel(nullptr)
{
}

BattleScene::~BattleScene() {}

cocos2d::Scene* BattleScene::createScene()
{
    return BattleScene::create();
}

bool BattleScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    // ���� TMX ��ͼ
    _tileMap = cocos2d::TMXTiledMap::create("whole3.tmx");
    if (_tileMap == nullptr)
    {
        cocos2d::log("Failed to load map.");
        return false;
    }
    this->addChild(_tileMap);  // ����ͼ��ӵ�����

    // �ӵ�ͼ�� objects ���л�ȡ��Һ͵��˵���Ϣ
    cocos2d::TMXObjectGroup* objectGroup = _tileMap->getObjectGroup("Objects");
    if (objectGroup != nullptr)
    {
        // ��ȡ��ҵ���Ϣ��������ҵĶ�����Ϊ "player"��
        cocos2d::ValueMap playerData = objectGroup->getObject("Player");
        if (!playerData.empty())
        {
            float playerX = playerData["x"].asFloat();
            float playerY = playerData["y"].asFloat();
            _player = new BattleCharacter(cocos2d::Sprite::create("NPC1.png"), "Player", 100, 20, PlayerState::NORMAL);
            _player->sprite->setPosition(playerX, playerY);
            this->addChild(_player->sprite);  // �������ӵ�������
        }

        // ��ȡ���˵���Ϣ��������˵Ķ�����Ϊ "enemy"��
        cocos2d::ValueMap enemyData = objectGroup->getObject("NPC");
        if (!enemyData.empty())
        {
            float enemyX = enemyData["x"].asFloat();
            float enemyY = enemyData["y"].asFloat();
            _enemy = new BattleCharacter(cocos2d::Sprite::create("NPCc.png"), "Enemy", 100, 15, PlayerState::NORMAL);
            _enemy->sprite->setPosition(enemyX, enemyY);
            this->addChild(_enemy->sprite);  // ��������ӵ�������
        }
    }

    // ������������Ч��
    _skillEffect = cocos2d::ParticleSystemQuad::create("fire.plist");  // ����������Ч��
    _skillEffect->setVisible(false);  // ��ʼʱ����
    this->addChild(_skillEffect, 10);

    _skill1Effect = cocos2d::ParticleSystemQuad::create("fire1.plist");  // һ��������Ч��
    _skill1Effect->setVisible(false);  // ��ʼʱ����
    this->addChild(_skill1Effect, 10);

    _skill2Effect = cocos2d::ParticleSystemQuad::create("fireball2.plist");  // ����������Ч��
    _skill2Effect->setVisible(false);  // ��ʼʱ����
    this->addChild(_skill2Effect, 10);

    // ����һ�� Label ����ʾ���˵�ǰ������ֵ
    _enemyHealthLabel = cocos2d::Label::createWithTTF("Health: 100", "fonts/Marker Felt.ttf", 48);
    if (_enemyHealthLabel != nullptr)
    {
        _enemyHealthLabel->setPosition(cocos2d::Vec2(_enemy->sprite->getPosition().x, _enemy->sprite->getPosition().y + 50));
        this->addChild(_enemyHealthLabel, 1);  // �� Label ��ӵ�������
    }

    // ���ó�������
    schedule([=](float deltaTime) {
        update(deltaTime);
        }, "update_key");

    // ���ü��̺��������¼�
    auto listenerKeyboard = cocos2d::EventListenerKeyboard::create();
    listenerKeyboard->onKeyPressed = CC_CALLBACK_2(BattleScene::onKeyPressed, this);
    listenerKeyboard->onKeyReleased = CC_CALLBACK_2(BattleScene::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKeyboard, this);

    auto listenerMouse = cocos2d::EventListenerMouse::create();
    listenerMouse->onMouseDown = CC_CALLBACK_1(BattleScene::onMouseDown, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerMouse, this);

    return true;
}

void BattleScene::update(float delta)
{
    if (_skillEffect->isVisible()) {

    }
    // ���¼���Ч�����������Ҫ�Ļ���
    if (_skill1Effect->isVisible()) {

    }

    if (_skill2Effect->isVisible()) {

    }

    // ���µ�������ֵ����ʾ
    if (_enemy != nullptr && _enemyHealthLabel != nullptr)
    {
        // ������ʾ�ĵ�������ֵ
        _enemyHealthLabel->setString("Health: " + std::to_string(_enemy->health));
        // ���� Label λ�ã�ʹ��ʼ�ո������
        _enemyHealthLabel->setPosition(cocos2d::Vec2(_enemy->sprite->getPosition().x, _enemy->sprite->getPosition().y + 50));
    }

    // ���ս���Ƿ����
    checkBattleOver();
}

void BattleScene::onMouseDown(cocos2d::Event* event)
{
    // ��ͨ���¼�ת��Ϊ����¼�
    cocos2d::EventMouse* mouseEvent = dynamic_cast<cocos2d::EventMouse*>(event);
    if (mouseEvent)
    {
        // ��ȡ���������������
        cocos2d::Vec2 clickPosition = mouseEvent->getLocation();  // ʹ�� getLocation() ��ȡ���λ��

        if (mouseEvent->getMouseButton() == cocos2d::EventMouse::MouseButton::BUTTON_RIGHT)
        {
            _battleState = BattleState::ATTACKING;
            // �ж��Ҽ����ʱ��������Ӧ�ļ���
            if (_currentSkillState == SkillState::SKILL_1) {
                castSkill1();  // ִ��һ����
            }
            else if (_currentSkillState == SkillState::SKILL_2) {
                castSkill2();  // ִ�ж�����
            }
        }
        else if (mouseEvent->getMouseButton() == cocos2d::EventMouse::MouseButton::BUTTON_LEFT)
        {
            // ��ͨ����

            // ��ȡ���������������
            cocos2d::Vec2 clickPosition = mouseEvent->getLocation();  // ʹ�� getLocation() ��ȡ���λ��

            // �������ҵ������λ�õķ�������
            _skillDirection = clickPosition - _player->sprite->getPosition();
            _skillDirection.normalize();  // ������������һ��

            // �������ҵ������λ�õĽǶȣ����ȣ�
            float angle = std::atan2(_skillDirection.y, _skillDirection.x);  // atan2���ص��ǻ���

            // ������ת��Ϊ�Ƕ�
            float angleInDegrees = CC_RADIANS_TO_DEGREES(angle);  // ת��Ϊ�Ƕ�

            // ȷ���Ƕ��� [0, 360) ��Χ��
            if (angleInDegrees < 0) {
                angleInDegrees += 360;  // �����Ƕ�ת��Ϊ���Ƕ�
            }

            // ��������Ч���ķ���Ƕ�
            _skillEffect->setAngle(angleInDegrees);  // �������ӵķ���Ƕ�

            // ��������ϵͳ��λ��
            _skillEffect->setPosition(_player->sprite->getPosition());

            // ��������Ч��������
            _skillEffect->setVisible(true);
            _skillEffect->resetSystem();  // ��������ϵͳ

            // ���ü��ܳ���ʱ�䣨2�룩
            scheduleOnce([this](float dt) {
                // 2���ֹͣ����Ч��
                _skillEffect->stopSystem();  // ֹͣ����ϵͳ
                _skillEffect->setVisible(false);  // ��������ϵͳ
                }, 1.0f, "stop_skill_effect");  // 2������
            _battleState = BattleState::ATTACKING;
            playerAttack();
        }
    }
}

void BattleScene::playerAttack()
{
    // ��ͨ�����߼�
    // �������������ӹ����߼������ܻ��漰���˺�����Χ��
    if (_battleState != BattleState::ATTACKING) return;

    // ��������Ч����λ��
    _skillEffect->setPosition(_player->sprite->getPosition());
    _skillEffect->setVisible(true);

    // ���ż�������Ч��
    _skillEffect->resetSystem();

    // ��ȡ���˵�ǰλ��
    cocos2d::Vec2 enemyPosition = _enemy->sprite->getPosition();
    cocos2d::Vec2 playerPosition = _player->sprite->getPosition();

    // ������˺����֮��ľ���
    float distance = playerPosition.distance(enemyPosition);

    // ���������Χ�뾶
    float attackRadius = 1000.0f;  // ���������Ϊ����Ҫ�Ĺ����뾶
    if (distance > attackRadius) {
        return;  // ������˳���������Χ��ֱ�ӷ���
    }


    // �������ҵ�����֮��ĽǶȣ����ȣ�
    cocos2d::Vec2 direction = enemyPosition - playerPosition;
    float enemyAngle = std::atan2(direction.y, direction.x);  // atan2���ص��ǻ���

    // ������ת��Ϊ�Ƕ�
    float enemyAngleInDegrees = CC_RADIANS_TO_DEGREES(enemyAngle);
    if (enemyAngleInDegrees < 0) {
        enemyAngleInDegrees += 360;  // �����Ƕ�ת��Ϊ���Ƕ�
    }

    // �������εĽǶȷ�Χ
    float attackAngle = 360.0f;  // ���� 45 ������
    float attackRange = attackAngle / 2;  // ���νǶȵİ뾶

    // ������ҵĹ����Ƕ�
    float playerAngleInDegrees = std::atan2(_skillDirection.y, _skillDirection.x);  // ʹ����ҵĹ�������
    if (playerAngleInDegrees < 0) {
        playerAngleInDegrees += 360;  // �����Ƕ�ת��Ϊ���Ƕ�
    }

    // �����������ҹ�������ĽǶȲ�
    float angleDifference = std::abs(playerAngleInDegrees - enemyAngleInDegrees);
    if (angleDifference > 180) {
        angleDifference = 360 - angleDifference;  // ȷ���ǶȲ���� 180 ��
    }

    // �жϵ����Ƿ��ڹ������η�Χ��
    if (angleDifference <= attackRange) {
        // ��������ڹ�����Χ��
        // �����������ִ�й����߼�
        _enemy->health -= 20;  // �����˺������� 20
        cocos2d::log("Enemy hit! Health: %d", _enemy->health);

        // ���µ�������ֵ��ʾ
        if (_enemyHealthLabel != nullptr)
        {
            _enemyHealthLabel->setString("Health: " + std::to_string(_enemy->health));
        }

        // �����������
        if (_enemy->health <= 0)
        {
            _battleState = BattleState::GAME_OVER;
            cocos2d::log("You win!");

            // �����Ի�����ʾս������
            ::MessageBoxA(NULL, "Game Over! You win!", "Battle Ended", MB_OK);  // ʹ�� Windows API

        }
    }

    // �ı�ս��״̬�ص�����
    _battleState = BattleState::IDLE;
    cocos2d::log("Player is attacking!");
}

void BattleScene::castSkill1()
{
    // һ���ܵ�Ч��
    if (_battleState != BattleState::ATTACKING) return;

    _skill1Effect->setPosition(_player->sprite->getPosition());
    _skill1Effect->setVisible(true);
    _skill1Effect->resetSystem();  // ��������Ч��

    // ���ü��ܳ���ʱ�䣨2�룩
    scheduleOnce([this](float dt) {
        // 2���ֹͣ����Ч��
        _skill1Effect->stopSystem();  // ֹͣ����ϵͳ
        _skill1Effect->setVisible(false);  // ��������ϵͳ
        }, 1.0f, "stop_skill1_effect");  // 2������

    // ��ȡ���˵�ǰλ��
    cocos2d::Vec2 enemyPosition = _enemy->sprite->getPosition();
    cocos2d::Vec2 playerPosition = _player->sprite->getPosition();

    // ������˺����֮��ľ���
    float distance = playerPosition.distance(enemyPosition);

    // ���������Χ�뾶
    float attackRadius = 1000.0f;  // ���������Ϊ����Ҫ�Ĺ����뾶
    if (distance > attackRadius) {
        return;  // ������˳���������Χ��ֱ�ӷ���
    }


    // �������ҵ�����֮��ĽǶȣ����ȣ�
    cocos2d::Vec2 direction = enemyPosition - playerPosition;
    float enemyAngle = std::atan2(direction.y, direction.x);  // atan2���ص��ǻ���

    // ������ת��Ϊ�Ƕ�
    float enemyAngleInDegrees = CC_RADIANS_TO_DEGREES(enemyAngle);
    if (enemyAngleInDegrees < 0) {
        enemyAngleInDegrees += 360;  // �����Ƕ�ת��Ϊ���Ƕ�
    }

    // �������εĽǶȷ�Χ
    float attackAngle = 90.0f;  // ���� 45 ������
    float attackRange = attackAngle / 2;  // ���νǶȵİ뾶

    // ������ҵĹ����Ƕ�
    float playerAngleInDegrees = std::atan2(_skillDirection.y, _skillDirection.x);  // ʹ����ҵĹ�������
    if (playerAngleInDegrees < 0) {
        playerAngleInDegrees += 360;  // �����Ƕ�ת��Ϊ���Ƕ�
    }

    // �����������ҹ�������ĽǶȲ�
    float angleDifference = std::abs(playerAngleInDegrees - enemyAngleInDegrees);
    if (angleDifference > 180) {
        angleDifference = 360 - angleDifference;  // ȷ���ǶȲ���� 180 ��
    }

    // �жϵ����Ƿ��ڹ������η�Χ��
    if (angleDifference <= attackRange) {
        // ��������ڹ�����Χ��
        // �����������ִ�й����߼�
        _enemy->health -= 20;  // �����˺������� 20
        cocos2d::log("Enemy hit! Health: %d", _enemy->health);

        // ���µ�������ֵ��ʾ
        if (_enemyHealthLabel != nullptr)
        {
            _enemyHealthLabel->setString("Health: " + std::to_string(_enemy->health));
        }

        // �����������
        if (_enemy->health <= 0)
        {
            _battleState = BattleState::GAME_OVER;
            cocos2d::log("You win!");

            // �����Ի�����ʾս������
            ::MessageBoxA(NULL, "Game Over! You win!", "Battle Ended", MB_OK);  // ʹ�� Windows API

        }
    }

    // �ı�ս��״̬�ص�����
    _battleState = BattleState::IDLE;
    // ��������������һ���ܵ����⹥���߼�
    cocos2d::log("Casting Skill 1!");
}

void BattleScene::castSkill2()
{
    // �����ܵ�Ч��
    if (_battleState != BattleState::ATTACKING) return;

    _skill2Effect->setPosition(_player->sprite->getPosition());
    _skill2Effect->setVisible(true);
    _skill2Effect->resetSystem();  // ��������Ч��
    // ���ü��ܳ���ʱ�䣨2�룩
    scheduleOnce([this](float dt) {
        // 2���ֹͣ����Ч��
        _skill2Effect->stopSystem();  // ֹͣ����ϵͳ
        _skill2Effect->setVisible(false);  // ��������ϵͳ
        }, 1.0f, "stop_skil2_effect");  // 2������

    // ��ȡ���˵�ǰλ��
    cocos2d::Vec2 enemyPosition = _enemy->sprite->getPosition();
    cocos2d::Vec2 playerPosition = _player->sprite->getPosition();

    // ������˺����֮��ľ���
    float distance = playerPosition.distance(enemyPosition);

    // ���������Χ�뾶
    float attackRadius = 1000.0f;  // ���������Ϊ����Ҫ�Ĺ����뾶
    if (distance > attackRadius) {
        return;  // ������˳���������Χ��ֱ�ӷ���
    }


    // �������ҵ�����֮��ĽǶȣ����ȣ�
    cocos2d::Vec2 direction = enemyPosition - playerPosition;
    float enemyAngle = std::atan2(direction.y, direction.x);  // atan2���ص��ǻ���

    // ������ת��Ϊ�Ƕ�
    float enemyAngleInDegrees = CC_RADIANS_TO_DEGREES(enemyAngle);
    if (enemyAngleInDegrees < 0) {
        enemyAngleInDegrees += 360;  // �����Ƕ�ת��Ϊ���Ƕ�
    }

    // �������εĽǶȷ�Χ
    float attackAngle = 90.0f;  // ���� 45 ������
    float attackRange = attackAngle / 2;  // ���νǶȵİ뾶

    // ������ҵĹ����Ƕ�
    float playerAngleInDegrees = std::atan2(_skillDirection.y, _skillDirection.x);  // ʹ����ҵĹ�������
    if (playerAngleInDegrees < 0) {
        playerAngleInDegrees += 360;  // �����Ƕ�ת��Ϊ���Ƕ�
    }

    // �����������ҹ�������ĽǶȲ�
    float angleDifference = std::abs(playerAngleInDegrees - enemyAngleInDegrees);
    if (angleDifference > 180) {
        angleDifference = 360 - angleDifference;  // ȷ���ǶȲ���� 180 ��
    }

    // �жϵ����Ƿ��ڹ������η�Χ��
    if (angleDifference <= attackRange) {
        // ��������ڹ�����Χ��
        // �����������ִ�й����߼�
        _enemy->health -= 20;  // �����˺������� 20
        cocos2d::log("Enemy hit! Health: %d", _enemy->health);

        // ���µ�������ֵ��ʾ
        if (_enemyHealthLabel != nullptr)
        {
            _enemyHealthLabel->setString("Health: " + std::to_string(_enemy->health));
        }

        // �����������
        if (_enemy->health <= 0)
        {
            _battleState = BattleState::GAME_OVER;
            cocos2d::log("You win!");

            // �����Ի�����ʾս������
            ::MessageBoxA(NULL, "Game Over! You win!", "Battle Ended", MB_OK);  // ʹ�� Windows API

        }
    }

    // �ı�ս��״̬�ص�����
    _battleState = BattleState::IDLE;// �������������Ӷ����ܵ����⹥���߼�
    cocos2d::log("Casting Skill 2!");
}

void BattleScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    if (_player == nullptr) return;

    // ͨ�� Z ���л�Ϊһ���ܣ�X ���л�Ϊ������
    switch (keyCode)
    {
        case cocos2d::EventKeyboard::KeyCode::KEY_Z:
            _currentSkillState = SkillState::SKILL_1;  // �л���һ����
            cocos2d::log("Skill 1 selected.");
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_X:
            _currentSkillState = SkillState::SKILL_2;  // �л���������
            cocos2d::log("Skill 2 selected.");
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_W:
            _player->sprite->setPositionY(_player->sprite->getPositionY() + 5);
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_S:
            _player->sprite->setPositionY(_player->sprite->getPositionY() - 5);
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_A:
            _player->sprite->setPositionX(_player->sprite->getPositionX() - 5);
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_D:
            _player->sprite->setPositionX(_player->sprite->getPositionX() + 5);
            break;
        default:
            break;
    }
}

void BattleScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_Z || keyCode == cocos2d::EventKeyboard::KeyCode::KEY_X) {
        _currentSkillState = SkillState::NONE;  // �ͷż��ܼ��󽫼���״̬����ΪNONE
    }
}

void BattleScene::checkBattleOver()
{
    // ���ս���Ƿ����
    if (_enemy != nullptr && _enemy->health <= 0)
    {
        endBattle();
    }
}

void BattleScene::endBattle()
{
    // ս����������߼�
    cocos2d::log("Battle Over!");
}