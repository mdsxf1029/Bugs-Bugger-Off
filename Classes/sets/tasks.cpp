#include "tasks.h"

int Task::id = 0;
Task::Task(std::string name, std::string description, std::string reward) : name(name), description(description),reward(reward)
{
	//��ʼ��
	if (name == "MAIN_TASK")
		priority = 2;
	else if (name == "nonTask")
	{
		state = true;
		priority = 0;
	}
	else
		priority = 1;
}

//�������
void Task::finish() noexcept                               //�������ʱ���øú���
{
	//���δ��ɣ� ״̬��Ϊ���
	if (state==0)
		state = 1;
}
