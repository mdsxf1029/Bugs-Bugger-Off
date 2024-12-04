#pragma once

#ifndef BATTELSENCE_H
#define BATTLESENCE_H

#include "cocos2d.h"
#include "Player.h"
#include "npc.h"
class BattleSence {
public:
    static cocos2d::Scene* createScene();//��������  ��ͼ 
    virtual bool init(); 
    void update(float delta);
    void handleInput(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

protected:

private:
	Player* player;//���
	EnemyNpc* enemy;//����

};




#endif 
