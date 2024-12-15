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

const std::string NON_TASK = "NON_TASK";//������	
const std::string NON_TASK_DESCRIPTION = "No task";//����������

const std::string MAIN_TASK_GOLD = "TASK_GOLD";//������
const std::string MAIN_TASK_GOLD_DESCRIPTION = "TASK_GOLD";//������

const std::string MAIN_TASK_WOOD = "TASK_WOOD";//ľ����
const std::string MAIN_TASK_WOOD_DESCRIPTION = "TASK_WOOD";//������

const std::string MAIN_TASK_WATER = "TASK_WATER";//ˮ����
const std::string MAIN_TASK_WATER_DESCRIPTION = "TASK_WATER";//������

const std::string MAIN_TASK_FIRE = "TASK_FIRE";//������
const std::string MAIN_TASK_FIRE_DESCRIPTION = "TASK_FIRE";//������

const std::string MAIN_TASK_EARTH = "TASK_EARTH";//������
const std::string MAIN_TASK_EARTH_DESCRIPTION = "TASK_EARTH";//������

class Task {
public:

	Task() noexcept : name(NON_TASK), description(NON_TASK_DESCRIPTION), priority(0), isFinished(false) {};//Ĭ�Ϲ��캯��
	Task(const std::string name, const std::string description);//���ι��캯��
	void finish() noexcept;//�������
	std::string getTaskName() const { return name; };
	std::string getTaskDescription() const { return description; };
	bool isTaskFinished() const { return isFinished; };

protected:

private:
	std::string name;//��������
	std::string description;//��������
	int priority;//���ȼ�
	bool isFinished;//�Ƿ����
};



#endif
