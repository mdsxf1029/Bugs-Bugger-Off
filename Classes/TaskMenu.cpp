#include "TaskMenu.h"
#include "ui/UIScrollView.h"
#include "ui/UIButton.h"

USING_NS_CC;

bool TaskMenu::init()
{
	if (!Layer::init())
	{
		CCLOGERROR("TaskMenu::init: Failed to initialize Layer.");
		return false;
	}

	// �� GlobalManager ��ȡ�����б�
	const auto& taskList = GlobalManager::getInstance().getTasks();
	tasks = taskList;																		// �洢�����б�

	createTaskMenu();

	return true;
}

void TaskMenu::createTaskMenu()
{
	// ��������˵�����
	auto menuBg = LayerColor::create(Color4B(0, 0, 0, 180), 200, 200);						// ��200����300
	if (!menuBg)
	{
		CCLOGERROR("TaskMenu::createTaskMenu: Failed to create menu background.");
	}

	Vec2 center = Director::getInstance()->getVisibleSize() / 2;
	menuBg->setPosition(Director::getInstance()->getVisibleSize().width / 2+750, 
						Director::getInstance()->getVisibleSize().height / 2+300);			// λ�����Ͻ�
	this->addChild(menuBg);

	// ������ͼ
	auto scrollView = ui::ScrollView::create();
	if (!scrollView)
	{
		CCLOGERROR("TaskMenu::createTaskMenu: Failed to create ScrollView.");
	}

	scrollView->setDirection(ui::ScrollView::Direction::VERTICAL);
	scrollView->setContentSize(Size(200, 200));												// ������ͼ�ߴ��뱳��һ��
	scrollView->setInnerContainerSize(Size(200, tasks.size() * 40));						// �����и�������
	scrollView->setPosition(Vec2(0, 0));
	menuBg->addChild(scrollView);

	// ���û�������ʽ
	scrollView->setScrollBarEnabled(true);													// ���û�����
	scrollView->setScrollBarColor(Color3B::WHITE);											// ���û�������ɫ
	scrollView->setScrollBarOpacity(300);													// ���û�����͸����
	scrollView->setScrollBarAutoHideEnabled(false);

	// ���������
	for (size_t i = 0; i < tasks.size(); ++i)
	{
		auto task = tasks[i];
		
		if (task->state >= 0)
		{
			// ������ť
			auto taskButton = ui::Button::create("UI/UI_Flat_Bar01a.png", "UI/UI_Flat_Bar01a.png");
			if (!taskButton)
			{
				CCLOGERROR("TaskMenu::createTaskMenu: Failed to create task button for Task %d.", i + 1);
				continue;
			}


			// ���ð�ť�Ŵ�
			taskButton->setScale(6.0);															// �Ŵ�ťͼƬ�ı���

			// ���㰴ťλ��
			Vec2 buttonPosition = Vec2(100, scrollView->getInnerContainerSize().height - (i * 40) - 50);
			taskButton->setPosition(buttonPosition);																// ���ð�ťλ��

			// ��Ӱ�ť����¼�
			taskButton->addClickEventListener([=](Ref* sender) {
				this->showTaskDetails("Task details: \n" + task->getTaskDescription());
				});

			// ����ť��ӵ�������ͼ��
			scrollView->addChild(taskButton);

			// ���� Label ��������λ�ã����ڰ�ť�ײ���
			auto label = Label::createWithSystemFont(task->getTaskName(), "Arial", 12);								// ʹ�ú��ʵ�����ʹ�С
			label->setTextColor(Color4B::BLACK);
			label->setPosition(Vec2(buttonPosition.x, buttonPosition.y - taskButton->getContentSize().height / 2));  // ���� Label ��λ��
			scrollView->addChild(label);
		}
	}
}

void TaskMenu::showTaskDetails(const std::string& taskDetails)
{
	// ����
	auto detailLayer = LayerColor::create(Color4B(50, 50, 50, 230), 200, 200);
	if (!detailLayer)
	{
		CCLOGERROR("TaskMenu::showTaskDetails: Failed to create detail layer.");
	}

	detailLayer->setAnchorPoint(Vec2(0.5, 0.5));
	detailLayer->setPosition(Director::getInstance()->getVisibleSize().width / 2,
		Director::getInstance()->getVisibleSize().height / 2);
	this->addChild(detailLayer);

	auto closeButton = ui::Button::create("UI/X.png");
	if (!closeButton)
	{
		CCLOGERROR("TaskMenu::showTaskDetails: Failed to create close button.");
	} 

	closeButton->setPosition(Vec2(200, 200));
	closeButton->addClickEventListener([=](Ref* sender) {
		detailLayer->removeFromParent();
		});
	detailLayer->addChild(closeButton);

	auto detailLabel = Label::createWithSystemFont(taskDetails, "fonts/arial.ttf", 12);
	if (!detailLabel)
	{
		CCLOGERROR("TaskMenu::showTaskDetails: Failed to create detail label.");
	}

	detailLabel->setPosition(Vec2(150,100));
	detailLabel->setColor(Color3B::WHITE);
	detailLayer->addChild(detailLabel);
}