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

	CCLOG("TaskMenu::init: Successfully initialized Layer.");
	this->createTaskMenu();
	return true;
}

void TaskMenu::createTaskMenu()
{
	CCLOG("TaskMenu::createTaskMenu: Creating task menu.");

	// ��������˵�����
	auto menuBg = LayerColor::create(Color4B(0, 0, 0, 180), 800, 900);                     // ��200����300
	if (!menuBg)
	{
		CCLOGERROR("TaskMenu::createTaskMenu: Failed to create menu background.");
	}

	Vec2 center = Director::getInstance()->getVisibleSize() / 2;
	menuBg->setPosition(Director::getInstance()->getVisibleSize().width / 2+3550, 
						Director::getInstance()->getVisibleSize().height / 2+1000);    // λ�����Ͻ�
	this->addChild(menuBg);
	CCLOG("TaskMenu::createTaskMenu: Menu background created at position (%.2f, %.2f).",
		menuBg->getPositionX(), menuBg->getPositionY());

	// ������ͼ
	auto scrollView = ui::ScrollView::create();
	if (!scrollView)
	{
		CCLOGERROR("TaskMenu::createTaskMenu: Failed to create ScrollView.");
	}

	scrollView->setDirection(ui::ScrollView::Direction::VERTICAL);
	scrollView->setContentSize(Size(800, 900));                                          // ������ͼ�ߴ��뱳��һ��
	scrollView->setInnerContainerSize(Size(800, taskNames.size() * 200));                  // �����и�������
	scrollView->setPosition(Vec2(0, 0));
	menuBg->addChild(scrollView);
	CCLOG("TaskMenu::createTaskMenu: ScrollView created with content size (200, 300).");

	// ���û�������ʽ
	scrollView->setScrollBarEnabled(true);                       // ���û�����
	scrollView->setScrollBarColor(Color3B::WHITE);               // ���û�������ɫ
	scrollView->setScrollBarOpacity(300);                        // ���û�����͸����
	scrollView->setScrollBarAutoHideEnabled(false);

	// ���������
	for (int i = 0; i < taskNames.size(); ++i)
	{
		// ������ť
		auto taskButton = ui::Button::create("UI/UI_Flat_Bar01a.png", "UI/UI_Flat_Bar01a.png");
		if (!taskButton)
		{
			CCLOGERROR("TaskMenu::createTaskMenu: Failed to create task button for Task %d.", i + 1);
			continue;
		}

		// ���ð�ť�Ŵ�
		taskButton->setScale(5.0);  // �Ŵ�ťͼƬ�ı���

		// ���㰴ťλ��
		Vec2 buttonPosition = Vec2(400, scrollView->getInnerContainerSize().height - (i * 180) - 90);
		taskButton->setPosition(buttonPosition);

		// ��Ӱ�ť����¼�
		taskButton->addClickEventListener([=](Ref* sender) {
			CCLOG("TaskMenu::createTaskMenu: Task %d button clicked.", i + 1);
			this->showTaskDetails("Task details: " + taskNames[i]);
			});

		// ����ť��ӵ�������ͼ��
		scrollView->addChild(taskButton);

		// ���� Label ��������λ�ã����ڰ�ť�ײ���
		auto label = Label::createWithSystemFont(taskNames[i], "Arial", 60);  // ʹ�ú��ʵ�����ʹ�С
		label->setTextColor(Color4B::BLACK);
		label->setPosition(Vec2(buttonPosition.x, buttonPosition.y - taskButton->getContentSize().height / 2));  // ���� Label ��λ��
		scrollView->addChild(label);

		CCLOG("TaskMenu::createTaskMenu: Task %d button created at position (%.2f, %.2f).", i + 1, buttonPosition.x, buttonPosition.y);
	}


	/*// ���������
	for (int i = 0; i < taskNames.size(); ++i)
	{
		auto taskButton = ui::Button::create("UI/UI_Flat_Bar01a.png", "UI/UI_Flat_Bar01a.png");  // ��û�Ҿ���ͼƬ
		if (!taskButton)
		{
			CCLOGERROR("TaskMenu::createTaskMenu: Failed to create task button for Task %d.", i + 1);
			continue;
		}

		taskButton->setScale(4.0); // ����ťͼƬ�Ŵ�1.5��
		auto label = Label::createWithSystemFont(taskNames[i], "Arial", 50);
		label->setTextColor(Color4B::WHITE);
		label->setPosition(Vec2(100, scrollView->getInnerContainerSize().height - (i * 180) - 90));
		scrollView->addChild(label);
		/*taskButton->setTitleText(taskNames[i]);
		taskButton->setTitleFontSize(30);
		taskButton->setTitleColor(Color3B::BLACK);
		taskButton->setPosition(Vec2(370, scrollView->getInnerContainerSize().height - (i * 180) - 90));                          // ��̬����λ��
		taskButton->addClickEventListener([=](Ref* sender) {
			CCLOG("TaskMenu::createTaskMenu: Task %d button clicked.", taskNames[i].c_str());
			this->showTaskDetails("Task detals: " + taskNames[i]);
			});
		scrollView->addChild(taskButton);
		CCLOG("TaskMenu::createTaskMenu: Task %d button created at position (%.2f, %.2f).",
			taskNames[i].c_str(), taskButton->getPositionX(), taskButton->getPositionY());
	}*/
}

void TaskMenu::showTaskDetails(const std::string& taskDetails)
{
	// ����
	auto detailLayer = LayerColor::create(Color4B(50, 50, 50, 230), 1500, 1000);
	if (!detailLayer)
	{
		CCLOGERROR("TaskMenu::showTaskDetails: Failed to create detail layer.");
	}

	detailLayer->setPosition(Director::getInstance()->getVisibleSize().width / 2+500,
		Director::getInstance()->getVisibleSize().height / 2);
	this->addChild(detailLayer);
	CCLOG("TaskMenu::showTaskDetails: Detail layer created at position (%.2f, %.2f).",
		detailLayer->getPositionX(), detailLayer->getPositionY());

	auto closeButton = ui::Button::create("UI/X.png");
	if (!closeButton)
	{
		CCLOGERROR("TaskMenu::showTaskDetails: Failed to create close button.");
	} 

	closeButton->setPosition(Vec2(1500, 990));
	closeButton->addClickEventListener([=](Ref* sender) {
		CCLOG("TaskMenu::showTaskDetails: Close button clicked, removing detail layer.");
		detailLayer->removeFromParent();
		});
	detailLayer->addChild(closeButton);
	CCLOG("TaskMenu::showTaskDetails: Close button added to detail layer.");

	auto detailLabel = Label::createWithSystemFont(taskDetails, "fonts/arial.ttf", 60);
	if (!detailLabel)
	{
		CCLOGERROR("TaskMenu::showTaskDetails: Failed to create detail label.");
	}

	detailLabel->setPosition(Vec2(875, 500));
	detailLabel->setColor(Color3B::WHITE);
	detailLayer->addChild(detailLabel);
	CCLOG("TaskMenu::showTaskDetails: Detail label added with text: %s", taskDetails.c_str());
}