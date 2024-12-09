#pragma once
#ifndef _MAZE_GAME_
#define _MAZE_GAME_

#include "cocos2d.h"
#include <vector>
USING_NS_CC;

const int MAZE_WIDTH = 100;
const int MAZE_HEIGHT = 100;

class MazeGame :public cocos2d::Scene
{
public:
	MazeGame() : player_X(1), player_Y(1), player(nullptr) {}
	virtual bool init();
	static MazeGame* create();
	Sprite* player;                                                               // ��Ҿ���

private:

	const int TILE_SIZE = 40;
	std::vector<std::vector<char>> maze;                                                // �Թ�����
	int player_X, player_Y;                                                             // ��¼������Թ���λ��

	void generateMaze();                                                                // ����һ���򵥵��Թ�
	void renderMaze();                                                                  // ��Ⱦ�Թ�
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);  // �����¼�����
};

#endif _MAZE_GAME_