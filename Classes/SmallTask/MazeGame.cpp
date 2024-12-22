#include "cocos2d.h"
#include "SmallTask/MazeGame.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

// ���޷����أ�ת��tmx��Ⱦ����

bool MazeGame::init()
{
	if (!Scene::init())
	{
		return false;
	}

	// ��������ʼ����Ҿ���
	player = Sprite::create("HelloWorld.png");											// Ĭ������
	if (player == nullptr)																// ȷ�����鴴���ɹ�
	{
		CCLOG("Failed to create player sprite!");
		return false;
	}

	player->setScale(5000.0f);															// �Ŵ���
	player->setPosition(Director::getInstance()->getVisibleSize().width / 2 + player_X * TILE_SIZE, Director::getInstance()->getVisibleSize().height / 2 + (MAZE_HEIGHT - player_Y) * TILE_SIZE);
	this->addChild(player,5);

	// ע������¼�������
	auto listener = cocos2d::EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(MazeGame::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	generateMaze();																		// ��ʼ���Թ�
	renderMaze();																		// ��Ⱦ�Թ�

	return true;
}

MazeGame* MazeGame::create()
{
	srand(time(0));

	// �����Թ�����
	MazeGame* mazeGame = new MazeGame();												// ������Ϸʵ��
	if (mazeGame && mazeGame->init())													// ��ʼ����Ϸ
	{
		return mazeGame;																// ������Ϸʵ��
	}
	else
	{
		delete mazeGame;
		return nullptr;
	}
}

void MazeGame::generateMaze()
{
	CCLOG("Generating maze...");

	// ��ʼ���Թ�����
	maze.resize(MAZE_HEIGHT + 2, std::vector<char>(MAZE_WIDTH + 2, '#'));  // ���ӱ߿�

	// ����Թ���0 Ϊͨ����X Ϊǽ
	for (int i = 1; i <= MAZE_HEIGHT; i++)
	{
		for (int j = 1; j <= MAZE_WIDTH; j++)
		{
			maze[i][j] = rand() % 2 ? '0' : 'X';
		}
	}

	// ���ѡ�������յ�
	player_X = rand() % MAZE_WIDTH + 1;
	player_Y = rand() % MAZE_HEIGHT + 1;
	maze[player_X][player_Y] = 'S';											// ������

	int exit_X, exit_Y;
	do
	{
		exit_X = rand() % MAZE_WIDTH + 1;
		exit_Y = rand() % MAZE_HEIGHT + 1;
	} while (exit_X == player_X && exit_Y == player_Y);						// ȷ���յ㲻������غ� 
	maze[exit_X][exit_Y] = 'E';												// ����յ� 
	CCLOG("Maze generated.");												// ����Թ����ɳɹ�
}

void MazeGame::renderMaze()
{
	CCLOG("Rendering maze...");

	for (int i = 0; i < MAZE_HEIGHT + 2; i++)
	{
		for (int j = 0; j < MAZE_WIDTH + 2; j++) 
		{
			char tile = maze[i][j];
			if (tile == 'S')
			{
				// �������
				auto startSprite = Sprite::create("Maze/apple.png");
				if (startSprite)
				{
					startSprite->setScale(50.0f);  // �Ŵ���
					startSprite->setPosition(Director::getInstance()->getVisibleSize().width / 2 + j * TILE_SIZE, Director::getInstance()->getVisibleSize().height / 2 + (MAZE_HEIGHT - i) * TILE_SIZE);
					this->addChild(startSprite);
					CCLOG("Placed start sprite at (%d, %d)", Director::getInstance()->getVisibleSize().width / 2 + j * TILE_SIZE, Director::getInstance()->getVisibleSize().height / 2 + (MAZE_HEIGHT - i) * TILE_SIZE);
				}
			}
			else if (tile == 'E')
			{
				// �����յ�
				auto endSprite = Sprite::create("Maze/strawberry.png");
				if (endSprite) 
				{
					endSprite->setScale(50.0f);  // �Ŵ���
					endSprite->setPosition(Director::getInstance()->getVisibleSize().width / 2 + j * TILE_SIZE, Director::getInstance()->getVisibleSize().height / 2 + (MAZE_HEIGHT - i) * TILE_SIZE);
					this->addChild(endSprite);
					CCLOG("Placed end sprite at (%d, %d)", j * TILE_SIZE, (MAZE_HEIGHT - i) * TILE_SIZE);
				}
			}
			else if (tile == 'X') 
			{
				// ����ǽ��
				auto wallSprite = Sprite::create("Maze/blue_ghost.png");
				if (wallSprite) 
				{
					wallSprite->setScale(500000.0f);  // �Ŵ���
					wallSprite->setPosition(Director::getInstance()->getVisibleSize().width / 2 + j * TILE_SIZE, Director::getInstance()->getVisibleSize().height / 2 + (MAZE_HEIGHT - i) * TILE_SIZE);
					this->addChild(wallSprite,100);
					CCLOG("Placed wall sprite at (%d, %d)", j * TILE_SIZE, (MAZE_HEIGHT - i) * TILE_SIZE);
				}
			}
		}
	}

	CCLOG("Maze rendered.");
}


void MazeGame::onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event)
{
	// ɾ���ɵ���Ҿ���
	if (player)
	{
		this->removeChild(player);											// ɾ��֮ǰ�ľ���
	}

	int newPlayerX = player_X;
	int newPlayerY = player_Y;

	if (keycode == cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW)
	{
		newPlayerY = player_Y + 1;
		if (maze[newPlayerX][newPlayerY] != 'X')							// �������ǽ�����ƶ�
		{
			player->setTexture("Maze/pacman_up.png");
		}
	}
	else if (keycode == cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW)
	{
		newPlayerY = player_Y - 1;
		if (maze[newPlayerX][newPlayerY] != 'X')							// �������ǽ�����ƶ�
		{
			player->setTexture("Maze/pacman_down.png");
		}
	}
	else if (keycode == cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		newPlayerX = player_X - 1;
		if (maze[newPlayerX][newPlayerY] != 'X')							// �������ǽ�����ƶ�
		{
			player->setTexture("Maze/pacman_left.png");
		}
	}
	else if (keycode == cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		newPlayerX = player_X + 1;
		if (maze[newPlayerX][newPlayerY] != 'X')							// �������ǽ�����ƶ�
		{
			player->setTexture("Maze/pacman_right.png");
		}
	}

	// ����������겢�ƶ�����
	if (maze[newPlayerX][newPlayerY] != 'X')								// ����µ�λ���ǿ��ߵ�
	{
		player_X = newPlayerX;
		player_Y = newPlayerY;
		player->setScale(50.0f);  // �Ŵ���
		player->setPosition(player_X * TILE_SIZE, (MAZE_HEIGHT - player_Y) * TILE_SIZE);

																			// ���µľ�����ӵ�����
		this->addChild(player);

																			// �������Ƿ񵽴��յ�
		if (maze[player_X][player_Y] == 'E')								// �����յ�
		{
			auto winLabel = Label::createWithTTF("You Win!", "fonts/Marker Felt.ttf", 64); // ��ʾʤ����ʾ
			winLabel->setPosition(Director::getInstance()->getVisibleSize() / 2);		   // ������ʾ
			winLabel->setTextColor(Color4B::YELLOW);
			this->addChild(winLabel);													   // ȷ����ʾ�����ϲ�
			CCLOG("Player has won the game!");											   // ֹͣ��Ϸ����������
			return;
		}
	}
}
