#pragma once
#ifndef _QUIZ_GAME_
#define _QUIZ_GAME_

#include "cocos2d.h"
#include <vector>
USING_NS_CC;

class QuizGame :public cocos2d::Scene
{
public:
	QuizGame() :currentQuestion(0) {}

	static QuizGame* create();

	bool init() override;
	void createExitButton();
	bool displayQuestion();
	void onAnswerSelected(int answerIndex);

	// ��⣺ÿ���������������ݺ�ѡ�����
	struct Question
	{
		std::string questionText;             // �����ı�
		std::vector<std::string> options;     // ѡ��
		int correctAnswerIndex;               // ��ȷ�𰸵�����
	};

	std::vector<Question> questions;          // ���
	int currentQuestion;                      // ��ǰ��������
	int totalQuestions;                       // ��������
	int correctAnswersCount;

private:
	void shuffleQuestions();                  // ��������˳��
	void shuffleOptions(int questionIndex);   // ���Ҵ�˳��
};

#endif _QUIZ_GAME_