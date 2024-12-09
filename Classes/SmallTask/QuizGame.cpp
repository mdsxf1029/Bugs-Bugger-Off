#include "QuizGame.h"
USING_NS_CC;

QuizGame* QuizGame::create()
{
    QuizGame* ret = new QuizGame();
    if (ret && ret->init())
    {
        ret->autorelease();
        return ret;
    }
    else
    {
        delete ret;
        return nullptr;
    }
}

bool QuizGame::init()
{
    // ��ʼ�����
    questions.push_back({ "What is 2 + 2?", {"3", "4", "5", "6"}, 1 });
    questions.push_back({ "What is the capital of France?", {"Berlin", "Madrid", "Paris", "Rome"}, 2 });
    questions.push_back({ "Which is the largest planet?", {"Earth", "Jupiter", "Mars", "Venus"}, 1 });

    totalQuestions = questions.size();
    CCLOG("Total questions: %d", totalQuestions);  // ��־���������

    // ��������˳��
    shuffleQuestions();
    CCLOG("Questions shuffled.");  // �����Ŀ�Ѵ���

    displayQuestion();
    return true;
}

void QuizGame::shuffleQuestions()
{
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(questions.begin(), questions.end(), g);

    CCLOG("Questions shuffled randomly.");  // ����Ѵ�����Ŀ����־
}

void QuizGame::shuffleOptions(int questionIndex)
{
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(questions[questionIndex].options.begin(), questions[questionIndex].options.end(), g);

    CCLOG("Options for question %d shuffled.", questionIndex);  // ��־���ѡ���Ѵ���
}

bool QuizGame::displayQuestion()
{
    if (currentQuestion >= questions.size())
    {
        // ���û�и������⣬��Ϸ����
        cocos2d::MessageBox("You've completed all questions!", "Quiz");
        CCLOG("Game completed. All questions answered.");  // �����Ϸ�����
        return true;
    }

    // ��ȡ��ǰ����
    auto& currentQ = questions[currentQuestion];
    CCLOG("Displaying question %d: %s", currentQuestion + 1, currentQ.questionText.c_str());  // �����ǰ��ʾ������

    // ��ʾ����
    auto questionLabel = cocos2d::Label::createWithSystemFont(currentQ.questionText, "Arial", 24);
    questionLabel->setPosition(cocos2d::Vec2(400, 300));
    this->addChild(questionLabel);

    // ����ѡ��
    shuffleOptions(currentQuestion);

    // ��ʾ��ѡ��
    for (int i = 0; i < currentQ.options.size(); ++i)
    {
        auto button = cocos2d::MenuItemLabel::create(cocos2d::Label::createWithSystemFont(currentQ.options[i], "Arial", 24),
            [this, i](Ref* sender) {
                onAnswerSelected(i);
            });
        button->setPosition(cocos2d::Vec2(400, 250 - i * 50));
        auto menu = cocos2d::Menu::create(button, nullptr);
        menu->setPosition(cocos2d::Vec2::ZERO);
        this->addChild(menu);
        CCLOG("Option %d: %s", i + 1, currentQ.options[i].c_str());  // ���ÿ��ѡ��
    }

    return false;
}

void QuizGame::onAnswerSelected(int answerIndex)
{
    auto& currentQ = questions[currentQuestion];

    CCLOG("Answer selected for question %d: Option %d", currentQuestion + 1, answerIndex + 1);  // ���ѡ��Ĵ�ѡ��

    // �����Ҵ�
    if (answerIndex == currentQ.correctAnswerIndex)
    {
        cocos2d::MessageBox("Correct!", "Quiz");
        CCLOG("Answer is correct!");  // �������ȷ����־
    }
    else
    {
        cocos2d::MessageBox("Wrong answer! Starting over.", "Quiz");
        CCLOG("Answer is wrong. Restarting the quiz.");  // ����𰸴�����������־
        currentQuestion = 0;  // ���������¿�ʼ
        shuffleQuestions();   // ���´�������˳��
        this->removeAllChildren();  // �Ƴ���ǰ�����ӽڵ�
        displayQuestion();    // ������ʾ����
        return;
    }

    // �л�����һ������
    ++currentQuestion;
    CCLOG("Moving to next question %d", currentQuestion + 1);  // �����ǰ�ƶ�����һ������

    // ����������ⶼ�ѻش𣬷��� true
    if (currentQuestion >= questions.size())
    {
        cocos2d::MessageBox("You've completed all questions!", "Quiz");
        CCLOG("All questions answered, game completed.");  // �����Ϸ�����־
        return;
    }

    this->removeAllChildren();  // �Ƴ���ǰ�����ӽڵ�
    displayQuestion();          // ��ʾ��һ������
}
