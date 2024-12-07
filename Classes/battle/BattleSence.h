#pragma once

#ifndef BATTELSENCE_H
#define BATTLESENCE_H

#include "cocos2d.h"
#include <sets/inventory.h>
#include <sets/npc.h>
#include <sets/player.h>
#include <sets/items.h>
#include <sets/elements.h>
class BattleSence :public cocos2d::Scene {
public:
    friend class Player;
    friend class EnemyNpc;
    static cocos2d::Scene* createScene();//��������  ��ͼ 

    virtual bool init(EnemyNpc& enemy_now);//��ʼ��
    void update(float delta);//ÿ֡����
    void keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void keyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void battle();//ս��
protected:

private:
    Player* player;//���
    EnemyNpc* enemy;//����
    bool isAttacking; // ����״̬��־
};




#endif 
