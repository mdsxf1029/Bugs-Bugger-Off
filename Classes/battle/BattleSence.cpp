#include "BattleSence.h"
#include "Player.h"
#include "npc.h"
#include "cocos2d.h"
#include"sets_variables.h"
#include"skills.h"
USING_NS_CC;//cococs2d �����ռ� ����ֱ�ӵ���cocos2d-x�ĺ���

//Sence ����   ��������
Scene* BattleScene::createScene() {
    return BattleScene::create();
}

bool BattleScene::init(Enemy & enemy_now) {
    if (!Scene::init()) {
        return false;
    }

    player = hero;
    player ->setPosition(Vec2(200, 300));
    this->addChild(player1);

	enemy = enemy_now;                      
    player2->setPosition(Vec2(400, 300));
    this->addChild(player2);

    // ���ü����¼�������
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(BattleScene::handleInput, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    this->scheduleUpdate(); // ÿ֡����
    return true;
}


/*#include "BattleScene.h"

USING_NS_CC;

Scene* BattleScene::createScene() {
    return BattleScene::create();
}

bool BattleScene::init() {
    if (!Scene::init()) {
        return false;
    }

    player1 = Player::create("player1.png");
    player1->setPosition(Vec2(200, 300));
    this->addChild(player1);

    player2 = Player::create("player2.png");
    player2->setPosition(Vec2(400, 300));
    this->addChild(player2);

    // ���ü����¼�������
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(BattleScene::handleInput, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    this->scheduleUpdate(); // ÿ֡����
    return true;
}

void BattleScene::update(float delta) {
    player1->update(delta);
    player2->update(delta);

    // �������ֵ
    if (!player1->isAlive()) {
        CCLOG("Player 1 defeated!");
        // �������1ʧ�ܵ��߼�
    }
    if (!player2->isAlive()) {
        CCLOG("Player 2 defeated!");
        // �������2ʧ�ܵ��߼�
    }
}

void BattleScene::handleInput(EventKeyboard::KeyCode keyCode, Event* event) {
    if (keyCode == EventKeyboard::KeyCode::KEY_A) {
        player1->attack(player2);
        CCLOG("Player 1 attacks Player 2!");
    }
    if (keyCode == EventKeyboard::KeyCode::KEY_L) {
        player2->attack(player1);
        CCLOG("Player 2 attacks Player 1!");
    }
}
*/