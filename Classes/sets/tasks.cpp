#include "tasks.h"

//���캯��  ���ڳ�ʼ�� �������� �������� ���ȼ� ���������ȼ�Ϊ2 ���������ȼ�Ϊ1 ����״̬Ϊδ���
Task::Task(std::string& name��std::string& description) :name(name), description(description)
{
	//��ʼ������״̬
	isFinished = false;//��ʼ��Ϊδ���

	//��ʼ�����ȼ�
	if (name == MAIN_TASK)
		proirity = 2;
	else if (name == nonTask)
	{
		isFinished = true;
		proirity = 0;
	}
	else
		proirity = 1;
	
}

//��������
Task::~Task() {};

//�������
void Task::finish()
{
	//���δ��ɣ� ״̬��Ϊ���
	if(!isFinished)
		isFinished = true;

	//�������ʱ���øú���  ����������� ����Ϸ״̬
}
