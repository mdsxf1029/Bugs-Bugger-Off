#pragma once

#ifndef __BATTLE_SCENE_H__
#define __BATTLE_SCENE_H__

#include "cocos2d.h"
#include <vector>
#include <functional>

// ս��״̬ö�٣��������ڹ���ս������
enum class BattleState {
    IDLE,           // ����״̬
    ATTACKING,      // ����״̬
    GAME_OVER       // ��Ϸ����
};
enum class SkillState
{
    NONE,   // û�м��ܼ���
    SKILL_1,  // һ����
    SKILL_2   // ������
};
// ��ҽ�ɫ��״̬���������ڽ�ɫ���Թ���
enum class PlayerState {
    NORMAL,
    STUNNED,
    DEAD
};

struct BattleCharacter {
    cocos2d::Sprite* sprite;        // ��ɫ����
    std::string name;               // ��ɫ����
    int health;                     // ��ɫ����ֵ
    int attack;                     // ��ɫ������
    PlayerState state;              // ��ǰ״̬

    BattleCharacter(cocos2d::Sprite* sprite, const std::string& name, int health, int attack, PlayerState state)
        : sprite(sprite), name(name), health(health), attack(attack), state(state) {
    }
};

class BattleScene : public cocos2d::Scene
{
public:
    BattleScene();
    virtual ~BattleScene();

    static cocos2d::Scene* createScene();
    virtual bool init();                      // ��ʼ������
    void update(float delta) override;        // �����߼�
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void onMouseDown(cocos2d::Event* event);  // ������¼�

    CREATE_FUNC(BattleScene);

private:
    cocos2d::TMXTiledMap* _tileMap;
    BattleState _battleState;                 // ��ǰս��״̬
    BattleCharacter* _player;                 // ��ҽ�ɫ
    BattleCharacter* _enemy;                  // ���˽�ɫ

    // ս���غ�����
    int _turnCounter;                         // �غϼ�����
    bool _isPlayerTurn;                       // �ж��Ƿ��ֵ�����ж�
    cocos2d::Vec2 _skillDirection;            // ���ܷ���
    cocos2d::Label* _enemyHealthLabel;
    // ����ϵͳ��������ʾ����Ч��
    // ��ǰ����״̬
    SkillState _currentSkillState;

    cocos2d::ParticleSystemQuad* _skillEffect;
    // ����Ч��
    cocos2d::ParticleSystemQuad* _skill1Effect;
    cocos2d::ParticleSystemQuad* _skill2Effect;

    void startBattle();                       // ��ʼս��
    void endBattle();                         // ����ս��
    void playerAttack();                      // ��ҹ���
    void enemyAttack();                       // ���˹���

    void castSkill1();
    void castSkill2();

    void displayBattleInfo();                 // ��ʾս����Ϣ��Ѫ����״̬�ȣ�
    void displayAttackAnimation();            // ���Ź�������

    // ����ս��״̬�ı仯
    void handleBattleState();

    // ��ʾ�Ի���״̬�Ƚ���
    void displayDialogue(const std::string& text);

    // ���ڼ��ս����������
    void checkBattleOver();

    // ����ƶ�����
    void movePlayer(cocos2d::Vec2 direction); // ��������ƶ�
};

#endif // __BATTLE_SCENE_H__

