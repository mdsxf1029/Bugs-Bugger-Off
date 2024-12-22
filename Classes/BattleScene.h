#pragma once

#ifndef __BATTLE_SCENE_H__
#define __BATTLE_SCENE_H__

#include "cocos2d.h"
#include <vector>
#include <functional>
#include "sets/manager.h"
#include "Map/MiniMap.h"

// ս��״̬ö�٣��������ڹ���ս������
enum class BattleState {
    IDLE,           // ����״̬
    ATTACKING,      // ����״̬
    GAME_OVER       // ��Ϸ����
};


class BattleScene : public cocos2d::Scene
{
public:
    BattleScene();
    virtual ~BattleScene();
     
    virtual bool init();                                                                                // ��ʼ������
    void update(float delta) override;                                                                  // �����߼�
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);                  // ���̰����¼�  
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);                 // �����ͷ��¼�   
    void onMouseDown(cocos2d::Event* event);                                                            // ������¼�
	void enemyMove();                                                                                   // �����ƶ�
    void endBattle();                                                                                   // ����ս��
    void checkBattleOver();                                                                             // ���ڼ��ս����������
    void BattleScene::EnemyAttack();
    CREATE_FUNC(BattleScene);

private:
	cocos2d::TMXTiledMap* _tileMap;		                                                                // ��ͼ
    BattleState _battleState;                                                                           // ��ǰս��״̬
    std::shared_ptr<EnemyNpc> rawEnemy ;                                                                //����
	std::vector<std::shared_ptr<Skill>>askillList = GlobalManager::getInstance().getSkills();			//����
	std::shared_ptr<Skill>enemyskill;                       											//���˼���

    // ս������
    bool _isPlayerTurn;                                                                                 // �ж��Ƿ��ֵ�����ж�
    cocos2d::Vec2 _skillDirection;                                                                      // ���ܷ���
    cocos2d::Label* _enemyHealthLabel;		                                                            // ��������ֵ��ʾ
    cocos2d::Label* _playerHealthLabel;		                                                            // �������ֵ��ʾ
	SkillState _currentSkillState;			                                                            // ��ǰ����״̬
	float _coolDownTime = 3.0f;			                                                                // ������ȴʱ��
	bool _ableToAttack = true;                                                                          //�ܹ�����  
    bool gameOver = false;                                                                              //ս��������ʼ��Ϊfalse
	float cooldownTime = 2.0f;                                                                          //��ȴʱ��
    

};

#endif // __BATTLE_SCENE_H__

