#pragma once

#ifndef TASKS_H
#define TASKS_H

#include <string>
#include <string.h>

const std::string MAIN_TASK = "LOOK FOR THE PRINCESS";																		//Ѱ�ҹ���
const std::string MAIN_TASK_DESCRIPTION = "The princess is missing, you need to find her and bring her back to the castle"; //����ʧ�٣�����Ҫ�ҵ������������سǱ�

//������ һЩ���Բ��õ�����

const std::string SIDE_TASK_ONE = "GOLD TASK";															//��
const std::string SIDE_TASK_ONE_DESCRIPTION = "Explore the gold place";									
const std::string SIDE_TASK_ONE_REWARD = "you win the gold";													

const std::string SIDE_TASK_TWO = "WOOD TASK";															//ľ 
const std::string SIDE_TASK_TWO_DESCRIPTION = "Explore the wood place";
const std::string SIDE_TASK_TWO_REWARD = "skill is update";

const std::string SIDE_TASK_THREE = "EARTH TASK";				         								//��	
const std::string SIDE_TASK_THREE_DESCRIPTION = "Explore the earth place";
const std::string SIDE_TASK_THREE_REWARD = "skill is updated";

const std::string SIDE_TASK_FOUR = "WATER TASK";														//ˮ
const std::string SIDE_TASK_FOUR_DESCRIPTION = "Explore the water place";
const std::string SIDE_TASK_FOUR_REWARD = "skill is updated";


const std::string SIDE_TASK_FIVE = "FIRE TASK";															//��
const std::string SIDE_TASK_FIVE_DESCRIPTION = "Explore the fire place";
const std::string SIDE_TASK_FIVE_REWARD = "skill is updated";

const std::string SIDE_TASK_SIX = "QUIZ1 TASK";															
const std::string SIDE_TASK_SIX_DESCRIPTION = "answer the question";
const std::string SIDE_TASK_SIX_REWARD = "you win gold";

const std::string SIDE_TASK_SEVEN = "QUIZ2 TASK";														
const std::string SIDE_TASK_SEVEN_DESCRIPTION = "answer the question";
const std::string SIDE_TASK_SEVEN_REWARD = "you win gold";

const std::string SIDE_TASK_EIGHT = "GOLDENMINI TASK";												
const std::string SIDE_TASK_EIGHT_DESCRIPTION = "DEFEAT ME";
const std::string SIDE_TASK_EIGHT_REWARD = "you can go";

const std::string SIDE_TASK_NINE = "WOODMINI TASK";																
const std::string SIDE_TASK_NINE_DESCRIPTION = "DEFEAT ME";
const std::string SIDE_TASK_NINE_REWARD = "you can go";

const std::string SIDE_TASK_TEN = "EARTHMINI TASK";															
const std::string SIDE_TASK_TEN_DESCRIPTION = "DEFEAT ME";
const std::string SIDE_TASK_TEN_REWARD = "you can go";

const std::string SIDE_TASK_ELEVEN = "WATERMINI TASK";														
const std::string SIDE_TASK_ELEVEN_DESCRIPTION = "DEFEAT ME";
const std::string SIDE_TASK_ELEVEN_REWARD = "you can go";

const std::string SIDE_TASK_SHIER = "FIREMINI TASK";															
const std::string SIDE_TASK_SHIER_DESCRIPTION = "DEFEAT ME";
const std::string SIDE_TASK_SHIER_REWARD = "you can go";

const std::string SIDE_TASK_SHISAN = "APPLE TASK";															
const std::string SIDE_TASK_SHISAN_DESCRIPTION = "bring fish to me";
const std::string SIDE_TASK_SHISAN_REWARD = "GREAT!";

const std::string SIDE_TASK_SHISI = "TRAVEL TASK";																
const std::string SIDE_TASK_SHISI_DESCRIPTION = "Explore the whole place";
const std::string SIDE_TASK_SHISI_REWARD = "GREAT!";

const std::string SIDE_TASK_SHIWU = "FISH TASK";																	
const std::string SIDE_TASK_SHIWU_DESCRIPTION = "bring fish to me";
const std::string SIDE_TASK_SHIWU_REWARD = "GREAT!";

const std::string SIDE_TASK_SHILIU = "ORE TASK";																	
const std::string SIDE_TASK_SHILIU_DESCRIPTION = "bring ore to me";
const std::string SIDE_TASK_SHILIU_REWARD = "GREAT!";

const std::string NON_TASK = "NON_TASK";															//������	
const std::string NON_TASK_DESCRIPTION = "No task";													//����������
class Task {
public:

	Task() noexcept : name(NON_TASK), description(NON_TASK_DESCRIPTION),reward("string"), priority(0) {};//Ĭ�Ϲ��캯��
	Task(const std::string name, const std::string description ,const std::string reward);				//���ι��캯��

	void setid(int id) { this->id = id; };															//��������id											
	void finish() noexcept;																			//�������
	/*get*/
	std::string getTaskName() const { return name; };												//�õ���������
	std::string getTaskDescription() const { return description; };									//�õ���������
	std::string getTaskReward() const { return reward; };											//�õ�������
	int getid() { return id; };																		//�õ�����id
	int state = -1;																					//����״̬
	static int id;																					//����id
private:
	std::string name;																				//��������
	std::string description;																		//��������
	std::string reward;																				//������
	int priority;																					//���ȼ� 
};

#endif
