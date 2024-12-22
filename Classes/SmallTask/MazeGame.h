#pragma once
#ifndef _MAZE_GAME_
#define _MAZE_GAME_

#include "cocos2d.h"
#include <vector>
USING_NS_CC;

class MazeGame :public cocos2d::Scene
{
public:
	MazeGame(){}  // ���캯����ʼ����Ϸδ���
	
	static MazeGame* create();
	bool init();

    void generateMaze();                                                                // ����һ���򵥵��Թ�
	void renderMaze();                                                                  // ��Ⱦ�Թ�
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);  // �����¼�����

private:
	const int MAZE_WIDTH = 100;
	const int MAZE_HEIGHT = 100;
	const int TILE_SIZE = 16.0f;

	std::vector<std::vector<char>> maze;                                                // �Թ�����
	Sprite* player;                                                                     // ��Ҿ���	
	int player_X, player_Y;                                                             // ��¼������Թ���λ��
};

#endif _MAZE_GAME_