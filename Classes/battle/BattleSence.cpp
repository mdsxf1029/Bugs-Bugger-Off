#include "BattleSence.h"
#include "cocos2d.h"

#include <sets/inventory.h>
#include <sets/npc.h>
#include <sets/player.h>
#include <sets/items.h>
#include <sets/elements.h>

USING_NS_CC;//cococs2d �����ռ� ����ֱ�ӵ���cocos2d-x�ĺ���

//��ҳ�ʼλ��
const int PLAYER_BEGIN_X = 200;
const int PLAYER_BEGIN_Y = 300;
//���˳�ʼλ��
const int ENEMY_BEGIN_X = 400;
const int ENEMY_BEGIN_Y = 300;

//Sence ����   ��������
Scene* BattleSence::createScene() {
    return BattleSence::create();
    //��ͨ���̳��� Node ���ӻ�õĹ��ܡ�
}

bool BattleSence::init(EnemyNpc& enemy_now) {
    if (!Scene::init()) {//��ʼ�� ����
        return false;
    }

    // ���ñ���
    auto background = Sprite::create("battle_background.png");//������������
    background->setPosition(Director::getInstance()->getVisibleSize() / 2);//����λ��Ϊ����
    this->addChild(background);//��ӵ�������
    /*��δ����Ŀ����Ϊ���������Ӿ�������
    ʹ�������Ϸ�п���һ�������ͼ�񣬶����ǿհ׵ĳ�����*/

    // ������Һ͵��� 
    //���
    player = &hero;
    player->setPosition(Vec2(PLAYER_BEGIN_X, PLAYER_BEGIN_Y));//����λ��
    this->addChild(player);//��ӵ�������
    //����
    enemy = &enemy_now;
    enemy->setPosition(Vec2(ENEMY_BEGIN_X, ENEMY_BEGIN_X));//����λ��
    this->addChild(player);//��ӵ�������

    // ��ʼ������״̬
    isAttacking = false;

    // ���ü����¼�������
    auto listener = EventListenerKeyboard::create();//���������¼�������
    listener->onKeyPressed = CC_CALLBACK_2(BattleSence::keyPressed, this);//��������ʱ����handleInput����
    listener->onKeyReleased = CC_CALLBACK_2(BattleSence::keyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);//��ӵ��¼��ַ�����

    this->scheduleUpdate(); // ÿ֡����
    return true;
}
//ÿ֡����
void BattleSence::update(float delta)
{
    player->update(delta);
    enemy->update(delta);
    // �������ֵ
    if (!player->isAlive) {
        CCLOG("Player defeated!");
        // �������ʧ�ܵ��߼�


    }
    if (!enemy->isAlive) {
        if (enemy->level == 2)
			(player->level)++;//���˵ȼ�Ϊ2ʱ���������
        CCLOG("Enemy defeated!");
        // ����enemyʧ�ܵ��߼�
    }
    //�ƶ�  
}
//�����������--����
void BattleSence::keyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    switch (keyCode)
    {
        case EventKeyboard::KeyCode::KEY_UP_ARROW:
            player->isMoving = true;
            player->Move(EventKeyboard::KeyCode::KEY_UP_ARROW);
            break;
        case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
            player->isMoving = true;
            player->Move(EventKeyboard::KeyCode::KEY_DOWN_ARROW);
            break;
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            player->isMoving = true;
            player->Move(EventKeyboard::KeyCode::KEY_LEFT_ARROW);
            break;
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            player->isMoving = true;
            player->Move(EventKeyboard::KeyCode::KEY_RIGHT_ARROW);
            break;
        case EventKeyboard::KeyCode::KEY_0:
			player->AttackEnemy(*enemy, EventKeyboard::KeyCode::KEY_0);
			break;
    } 
}

//�����������--�ͷ�
void BattleSence::keyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    switch (keyCode) {
		case EventKeyboard::KeyCode::KEY_UP_ARROW://������ϼ�
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW://������¼�
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW://��������
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW://������Ҽ�
            player->isMoving = false; // ֹͣ�ƶ�
            break;
        case EventKeyboard::KeyCode::KEY_A:
            CCLOG("Player stops attacking!");
            break;
        case EventKeyboard::KeyCode::KEY_L:
            CCLOG("Enemy stops attacking!");
            break;
    }
}


// ս��
void BattleSence::battle()
{

   
}