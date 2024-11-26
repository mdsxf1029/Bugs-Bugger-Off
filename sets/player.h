// Creator : 冯俊财 2353924
// Description: 玩家类的声明

#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <string.h>
#include "elements.h"
#include "inventory.h"

const int UPGRADE_HP = 25;//升级增加的血量
const int UPGRADE_ATTACK = 5;//升级增加的攻击力 
/******************************************************************************************
 class Player
 代表游戏中的玩家角色。

 class Player包含角色的基本属性，如名字、等级、血量、元素属性以及攻击力。
 此处的 初始化的 攻击力是不包含武器技能等的攻击力，只是基础攻击力
 该类提供了构造函数以初始化玩家的名字，并默认初始化其他属性。

属性：
 - name: 玩家名字
 - level: 玩家等级
 - hp: 玩家当前血量
 - player_element: 玩家元素属性
 - attack: 玩家攻击力
 - inventory: 玩家背包

*******************************************************************************************/

class Player {
public:
	//含参
    player(string& names, int element);
	void upgrade();//升级

protected:


private:
    string name; //名字
    int level;  //等级
    int hp;      //血量
    ElementType player_element;//元素属性
    int attack;  //攻击力
    inventory bag;
};

#endif