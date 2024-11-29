#pragma once

#ifndef TASKS_H
#define TASKS_H

#include <string>
#include <string.h>

const std::string MAIN_TASK = "LOOK FOR THE PRINCESS";//Ѱ�ҹ���
const std::string MAIN_TASK_DESCRIPTION = "The princess is missing, you need to find her and bring her back to the castle";//����ʧ�٣�����Ҫ�ҵ������������سǱ�

//������ һЩ���Բ��õ�����
const std::string SIDE_TASK_ONE = "LOOK FOR THE TREASURE";//̽���Թ����ҵ�����
const std::string SIDE_TASK_ONE_DESCRIPTION = "The treasure is hidden in the maze, you need to find it";//���ز����Թ��У�����Ҫ�ҵ���

const std::string SIDE_TASK_TWO = "DEFEAT THE MONSTER";//���ܹ���
const std::string SIDE_TASK_TWO_DESCRIPTION = "The monster is blocking the way, you need to defeat it";//���ﵲס��ȥ·������Ҫ������

const std::string SIDE_TASK_THREE = "HELP THE VILLAGERS";//�������� 
const std::string SIDE_TASK_THREE_DESCRIPTION = "The villagers are in trouble, you need to help them";//�������������鷳������Ҫ��������

const std::string SIDE_TASK_FOUR = "FIND THE WAY OUT";//�ҵ�����
const std::string SIDE_TASK_FOUR_DESCRIPTION = "There is a maze, you need to find the way out";//��һ���Թ�������Ҫ�ҵ�����

const std::string SIDE_TASK_FIVE = "FIND THE SECRET";//�ҵ�����
const std::string SIDE_TASK_FIVE_DESCRIPTION = "There is a secret hidden in the castle, you need to find it";//�Ǳ�����һ�����ܣ�����Ҫ�ҵ���

const std::string SIDE_TASK_SIX = "FIND THE TREASURE";//�ҵ�����
const std::string SIDE_TASK_SIX_DESCRIPTION = "The treasure is hidden in the forest, you need to find it";//���ز���ɭ���У�����Ҫ�ҵ���

const std::string SIDE_TASK_SEVEN = "FIND THE KEY";//�ҵ�Կ��
const std::string SIDE_TASK_SEVEN_DESCRIPTION = "The key is hidden in the cave, you need to find it";//Կ�ײ��ڶ�Ѩ�У�����Ҫ�ҵ���

class Task {
public:
	Task(std::string& name��std::string& description);
	~Task();
	void finish();//�������
protected:

private:
	std::string name;//��������
	std::string description;//��������
	int proirity;//���ȼ�
	bool isFinished;//�Ƿ����
};

//������
Task mainTask(MAIN_TASK��MAIN_TASK_DESCRIPTION);
//������
Task sideTaskOne(SIDE_TASK_ONE, SIDE_TASK_ONE_DESCRIPTION);
Task sideTaskTwo(SIDE_TASK_TWO, SIDE_TASK_TWO_DESCRIPTION);
Task sideTaskThree(SIDE_TASK_THREE, SIDE_TASK_THREE_DESCRIPTION);
Task sideTaskFour(SIDE_TASK_FOUR, SIDE_TASK_FOUR_DESCRIPTION);
Task sideTaskFive(SIDE_TASK_FIVE, SIDE_TASK_FIVE_DESCRIPTION);
Task sideTaskSix(SIDE_TASK_SIX, SIDE_TASK_SIX_DESCRIPTION);
Task sideTaskSeven(SIDE_TASK_SEVEN, SIDE_TASK_SEVEN_DESCRIPTION);

//������
Task nonTask("NO TASK", "No task now");//���� ���� ��Щû�������NPC �����������Ѿ���ɵ�NPC

#endif
