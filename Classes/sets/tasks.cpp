#include "tasks.h"
#include"sets_variables.h"
 
Task::Task(std::string name, std::string description) : name(name), description(description)
{
	//��ʼ������״̬
	isFinished = false; //��ʼ��Ϊδ���

	//��ʼ�����ȼ�
	if (name == "MAIN_TASK")
		priority = 2;
	else if (name == "nonTask")
	{
		isFinished = true;
		priority = 0;
	}
	else
		priority = 1;
}

//�������
void Task::finish() noexcept
{
	//���δ��ɣ� ״̬��Ϊ���
	if (!isFinished)
		isFinished = true;

	//�������ʱ���øú���  ����������� ����Ϸ״̬
}