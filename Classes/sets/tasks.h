#pragma once

#ifndef TASKS_H
#define TASKS_H

#include <string>
#include <string.h>

const string MAIN_TASK = "LOOK FOR THE PRINCESS";//Ѱ�ҹ���

//�������� һЩ���Բ��õ�����
const string SIDE_TASK_ONE = "LOOK FOR THE TREASURE";//̽���Թ����ҵ�����
const string SIDE_TASK_TWO = "DEFEAT THE MONSTER";//���ܹ���
const string SIDE_TASK_THREE = "HELP THE VILLAGERS";//�������� 
const string SIDE_TASK_FOUR = "FIND THE WAY OUT";//�ҵ�����
const string SIDE_TASK_FIVE = "FIND THE SECRET";//�ҵ�����
const string SIDE_TASK_SIX = "FIND THE TREASURE";//�ҵ�����
const string SIDE_TASK_SEVEN = "FIND THE KEY";//�ҵ�Կ��

class Task {
public:
	Task();
	virtual ~Task();
protected:

private:

};

class MainTask :public Task
{
public:


protected:

private:

};
class SideTask : public Task
{
public:


protected:


private:


};


#endif
