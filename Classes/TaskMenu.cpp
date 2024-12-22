#include "TaskMenu.h"
#include "ui/UIScrollView.h"
#include "ui/UIButton.h"

USING_NS_CC;

bool TaskMenu::init()																		// ��ʼ��
{
	if (!Layer::init())
	{
		CCLOGERROR("TaskMenu::init: Failed to initialize Layer.");
		return false;
	}
	const auto& taskList = GlobalManager::getInstance().getTasks();							// ��ȡ�����б�	
	tasks = taskList;																		// �洢�����б�
	createTaskMenu();																		// ��������˵�
	return true;
}

void TaskMenu::createTaskMenu()																// ��������˵�
{
	auto menuBg = LayerColor::create(Color4B(0, 0, 0, 180), 200, 200);						// ��������˵�������200����300
	if (!menuBg)
	{
		CCLOGERROR("TaskMenu::createTaskMenu: Failed to create menu background.");			// ��������ʧ��
	}

	Vec2 center = Director::getInstance()->getVisibleSize() / 2;							// ��ȡ��Ļ����
	menuBg->setPosition(Director::getInstance()->getVisibleSize().width / 2 + 750,			
						Director::getInstance()->getVisibleSize().height / 2+300);			// λ�����Ͻ�
	this->addChild(menuBg);																	// ��ӱ���

	/* ������ͼ*/
	auto scrollView = ui::ScrollView::create();												// ����������ͼ
	if (!scrollView)
	{
		CCLOGERROR("TaskMenu::createTaskMenu: Failed to create ScrollView.");				// ����������ͼʧ��
	}

	scrollView->setDirection(ui::ScrollView::Direction::VERTICAL);							// ��ֱ����
	scrollView->setContentSize(Size(200, 200));												// ������ͼ�ߴ��뱳��һ��
	scrollView->setInnerContainerSize(Size(200, tasks.size() * 40));						// �����и�������
	scrollView->setPosition(Vec2(0, 0));													// ���û�����ͼλ��
	menuBg->addChild(scrollView);															// ��������ͼ��ӵ�������

	/*���û�������ʽ*/ 
	scrollView->setScrollBarEnabled(true);													// ���û�����
	scrollView->setScrollBarColor(Color3B::WHITE);											// ���û�������ɫ
	scrollView->setScrollBarOpacity(300);													// ���û�����͸����
	scrollView->setScrollBarAutoHideEnabled(false);											// ���������Զ�����

	/*���������*/ 
	for (size_t i = 0; i < tasks.size(); ++i)												// ���������б�
	{
		auto task = tasks[i];																// ��ȡ��i������		
		if (task->state >= 0)																// �������״̬���ڵ���0
		{
			auto taskButton = ui::Button::create("UI/UI_Flat_Bar01a.png", "UI/UI_Flat_Bar01a.png");						// ��������ť
			if (!taskButton)
			{
				CCLOGERROR("TaskMenu::createTaskMenu: Failed to create task button for Task %d.", i + 1);				// ��������ťʧ��	
				continue;																								// ������һ������
			}
			taskButton->setScale(6.0);														// ���ð�ť�Ŵ� �Ŵ�ťͼƬ�ı���

			Vec2 buttonPosition = Vec2(100, scrollView->getInnerContainerSize().height - (i * 40) - 50);				// ���㰴ťλ��
			taskButton->setPosition(buttonPosition);																	// ���ð�ťλ��

			taskButton->addClickEventListener([=](Ref* sender) {														// ��Ӱ�ť����¼�
				this->showTaskDetails("Task details: \n" + task->getTaskDescription());									// ��ʾ��������
				});

			// ����ť��ӵ�������ͼ��
			scrollView->addChild(taskButton);

			// ���� Label ��������λ�ã����ڰ�ť�ײ���
			auto label = Label::createWithSystemFont(task->getTaskName(), "Arial", 12);									// ʹ�ú��ʵ�����ʹ�С
			label->setTextColor(Color4B::BLACK);																		// ����������ɫ
			label->setPosition(Vec2(buttonPosition.x, buttonPosition.y - taskButton->getContentSize().height / 2));		// ���� Label ��λ��
			scrollView->addChild(label);																				// �� Label ��ӵ�������ͼ��
		}
	}
}

void TaskMenu::showTaskDetails(const std::string& taskDetails)										// ��ʾ��������
{
	// ����
	auto detailLayer = LayerColor::create(Color4B(50, 50, 50, 230), 200, 200);						// ����һ����͸���ı���
	if (!detailLayer)
	{
		CCLOGERROR("TaskMenu::showTaskDetails: Failed to create detail layer.");					// ��������ʧ��
	}

	detailLayer->setAnchorPoint(Vec2(0.5, 0.5));													// ����ê��
	detailLayer->setPosition(Director::getInstance()->getVisibleSize().width / 2,					// ����λ��
		Director::getInstance()->getVisibleSize().height / 2);										
	this->addChild(detailLayer);																	// ��ӱ���

	auto closeButton = ui::Button::create("UI/X.png");												// �����رհ�ť
	if (!closeButton)
	{
		CCLOGERROR("TaskMenu::showTaskDetails: Failed to create close button.");					// �����رհ�ťʧ��
	} 

	closeButton->setPosition(Vec2(200, 200));														// ���ùرհ�ťλ��
	closeButton->addClickEventListener([=](Ref* sender) {											// ��ӵ���¼�
		detailLayer->removeFromParent();															// �Ƴ�����
		});
	detailLayer->addChild(closeButton);																// ��ӹرհ�ť

	auto detailLabel = Label::createWithSystemFont(taskDetails, "fonts/arial.ttf", 12);				// ������������ Label
	if (!detailLabel)																				// �������ʧ��
	{
		CCLOGERROR("TaskMenu::showTaskDetails: Failed to create detail label.");					// ������������ Label ʧ��
	}

	detailLabel->setPosition(Vec2(150, 100));														// ����λ��
	detailLabel->setColor(Color3B::WHITE);															// ������ɫ
	detailLayer->addChild(detailLabel);																// ����������� Label
}