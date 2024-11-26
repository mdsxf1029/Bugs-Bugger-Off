//creator: 冯俊财 2353924
//description: 玩家类的实现
#include <string>
#include <string.h>

#include "elements.h"
# include "player.h"
/*
* class player 的含参构造函数
* player 代表游戏中的玩家角色。   创建实例是 将其 设定为 hero 便于组中成员 完成代码
* names 玩家名字 element 玩家元素属性 1金 2木 3水 4火 5土
* level 初始化为0 hp初始化为50 attack初始化为10
*/


//构造函数 初始化姓名 元素属性 等级血量攻击力等等
Player::Player(std::string& names, int element) :name(names), level(0), hp(50), attrack(10)
{
	switch (elemnt)
	{
		case 1:
			player_element = ElementType::Gold;
			break;
		case 2:
			player_element = ElementType::Wood;
			break;
		case 3:
			player_element = ElementType::Water;
			break;
		case 4:
			player_element = ElementType::Fire;
			break;
		case 5:
			player_element = ElementType::Earth;
			break;
		default:
			player_element = ElementType::Gold;
			break;
	}
}
/*
* name:upgrade
* level ++， hp+25， attack+5
*/
void Player::Upgrade()
{
	level++;//等级加1
	max_hp += UPGRADE_HP;//血量增加
	hp = max_hp;//血量回复满
	basic_attack += UPGRADE_ATTACK;//攻击力增加
}


// 玩家攻击敌人
void Player::AttackEnemy(Player& enemy)
{//攻击敌人
	enemy.takeDamage(attack);
}

// 玩家受到伤害
void Player::TakeDamage(int damage)
{
	if ((hp - damage) > 0)
	{
		hp -= damage;
	}
	else
	{
		hp = 0;
		//玩家死亡
	//游戏结束 或者 返回上一个存档点 或者退出战斗场景
	}
}

// 玩家治疗  
// heal_hp 治疗的血量
void Player::Heal(int heal_hp)
{
	if ((hp + heal_hp)<=max_hp)
	{
		hp += heal_hp;
	}
	else
	{
		hp = max_hp;
	}
}


// 获取玩家的当前血量
int Player::GetHp() const
{
	return this->hp;
}

// 获取玩家的名字
std::string Player::GetName() const
{
	return this->name;
}

// 获取玩家的等级
int Player::GetLevel() const
{
	return this->level;
}

// 移动 需要坐标
void Player::Move()
{
	//坐标
}