#include "QuizGame.h"
#include "ui/CocosGUI.h"
#include"Map\MiniMap.h"
USING_NS_CC;

QuizGame* QuizGame::create()
{
	QuizGame* ret = new QuizGame();                                 // ������Ϸʵ��
	if (ret && ret->init())										    // ��ʼ����Ϸ
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
    questions.push_back({ "Who wrote 'Romeo and Juliet'?", {"Shakespeare", "Dickens", "Hemingway", "Austen"}, 0 });
    questions.push_back({ "What is the speed of light?", {"3 x 10^8 m/s", "3 x 10^6 m/s", "3 x 10^10 m/s", "300 m/s"}, 0 });
    questions.push_back({ "Which is the longest river in the world?", {"Amazon", "Nile", "Yangtze", "Mississippi"}, 1 });
    questions.push_back({ "What is the square root of 64?", {"6", "8", "10", "12"}, 1 });
    questions.push_back({ "What is the capital of Japan?", {"Seoul", "Beijing", "Tokyo", "Osaka"}, 2 });
    questions.push_back({ "Which element has the chemical symbol 'O'?", {"Oxygen", "Osmium", "Ozone", "Oganesson"}, 0 });
    questions.push_back({ "Who painted the Mona Lisa?", {"Picasso", "Da Vinci", "Van Gogh", "Rembrandt"}, 1 });
    questions.push_back({ "What is the largest ocean on Earth?", {"Atlantic", "Indian", "Arctic", "Pacific"}, 3 });

    totalQuestions = questions.size();
    CCLOG("Total questions: %d", totalQuestions);                   // ��־���������
     
    shuffleQuestions();                                             //���ҳ���˳��    
    CCLOG("Questions shuffled.");                                   // �����Ŀ�Ѵ���

	createExitButton();                                             // �����˳���ť
	displayQuestion();											    // ��ʾ����*/
    return true;
}

void QuizGame::createExitButton()
{
    auto exitButton = cocos2d::ui::Button::create("CloseNormal.png", "CloseSelected.png");
    if (!exitButton)
    {
        CCLOGERROR("Failed to create exit button.");
        return;
    }

    // ���ð�ťλ�ã���Ļ���Ͻǣ�
	auto visibleSize = Director::getInstance()->getVisibleSize();               // ��ȡ��Ļ�ߴ�
	auto origin = Director::getInstance()->getVisibleOrigin();				    // ��ȡ��Ļԭ��
	exitButton->setPosition(cocos2d::Vec2(600, 400));						    // ���ð�ťλ��

    // ���ð�ť����¼�
    exitButton->addClickEventListener([](Ref* sender) {
        CCLOG("Exit button clicked. Exiting game.");
        auto newScene = MiniMap::createWithMap("smallmap/whole3.tmx", false);
        Director::getInstance()->replaceScene(TransitionFade::create(1.0f, newScene));  // �˳���Ϸ
        });
     
	this->addChild(exitButton, 10);                                             // ��Ӱ�ť������
}

void QuizGame::shuffleQuestions()
{
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(questions.begin(), questions.end(), g);

    CCLOG("Questions shuffled randomly.");                                      // ����Ѵ�����Ŀ����־
}

void QuizGame::shuffleOptions(int questionIndex)
{
    auto& currentQ = questions[questionIndex];
     
    std::string correctOption = currentQ.options[currentQ.correctAnswerIndex]; // ���浱ǰ��ȷ������

    // ����ѡ��
	std::random_device rd;                                                      // ����豸
	std::mt19937 g(rd());                                                       // ���������
	std::shuffle(currentQ.options.begin(), currentQ.options.end(), g);          // ����ѡ��

    // ������ȷ������
    auto it = std::find(currentQ.options.begin(), currentQ.options.end(), correctOption);
    currentQ.correctAnswerIndex = std::distance(currentQ.options.begin(), it);

    CCLOG("Options for question %d shuffled. New correct answer index: %d", questionIndex, currentQ.correctAnswerIndex);
}


bool QuizGame::displayQuestion()
{
    if (currentQuestion >= questions.size())
    {
        ::MessageBoxA(NULL, "You've completed all questions!", "Quiz", MB_OK);  // ���û�и������⣬��Ϸ����
        CCLOG("Game completed. All questions answered.");                       // �����Ϸ�����
        return true;
    }
     
	auto& currentQ = questions[currentQuestion];                                              // ��ȡ��ǰ����                               
    CCLOG("Displaying question %d: %s", currentQuestion + 1, currentQ.questionText.c_str());  // �����ǰ��ʾ������

    // ��ʾ����
    auto questionLabel = cocos2d::Label::createWithSystemFont(currentQ.questionText, "fonts/arial.ttf", 24);
    questionLabel->setTextColor(cocos2d::Color4B::WHITE);
    questionLabel->setPosition(cocos2d::Vec2(1800, 800));
    this->addChild(questionLabel, 1);
    this->setLocalZOrder(101);

    // ����ѡ��
    shuffleOptions(currentQuestion);

    // ��ʾ��ѡ��
    for (int i = 0; i < currentQ.options.size(); ++i)
    {
        auto button = cocos2d::MenuItemLabel::create(cocos2d::Label::createWithSystemFont(currentQ.options[i], "Arial", 24),
            [this, i](Ref* sender) {
                onAnswerSelected(i);
            });
        button->setPosition(cocos2d::Vec2(1800, 700 - i * 50));
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
        ::MessageBoxA(NULL, "Correct!", "Quiz", MB_OK);
        CCLOG("Answer is correct!");                                                    // �������ȷ����־

        correctAnswersCount++;  // �����Ŀ��������

        // ����Ƿ����� 3 ����
        if (correctAnswersCount >= 3)
        {
            ::MessageBoxA(NULL, "Congratulations! You've answered 3 questions correctly!", "Quiz", MB_OK);
            CCLOG("Player answered 3 questions correctly. Game success.");  // �����Ϸ�ɹ�����־
            return;
        }
    }
    else
    {
        ::MessageBoxA(NULL, "Wrong answer! Starting over.", "Quiz", MB_OK);
        CCLOG("Answer is wrong. Restarting the quiz.");                                 // ����𰸴�����������־
        currentQuestion = 0;                                                            // ���������¿�ʼ
        shuffleQuestions();                                                             // ���´�������˳��
        this->removeAllChildren();                                                      // �Ƴ���ǰ�����ӽڵ�
		createExitButton();                                                             // �����˳���ť
        displayQuestion();                                                              // ������ʾ����
        return;
    }

    // �л�����һ������
    ++currentQuestion;
    CCLOG("Moving to next question %d", currentQuestion + 1);                           // �����ǰ�ƶ�����һ������

                                                                                        // ����������ⶼ�ѻش𣬷��� true
    if (currentQuestion >= questions.size())
    {
        ::MessageBoxA(NULL, "You've completed all questions!", "Quiz", MB_OK);
        CCLOG("All questions answered, game completed.");                               // �����Ϸ�����־
        return;
    }
    this->removeAllChildren();                                                          // �Ƴ���ǰ�����ӽڵ�
	createExitButton(); 															    // �����˳���ť                          
    displayQuestion();                                                                  // ��ʾ��һ������
}
