#include "GoldWood.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
#include <Sets/manager.h>
#include "Map/MiniMap.h"
USING_NS_CC;

bool Setting2::init()
{
	if (!Scene::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();												// ��ȡ�ɼ�����Ĵ�С
	Vec2 origin = Director::getInstance()->getVisibleOrigin();													// ��ȡ�ɼ������ԭ��

	// ����һ�����ڵ���������ͼ�����б�ǩ
	auto mapParentNode = Node::create();																		// ����һ�����ڵ�
	mapParentNode->setTag(100);																					// ���ø��ڵ�� tag
	mapParentNode->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));		// ���ø��ڵ��λ��
	this->addChild(mapParentNode);																				// �����ڵ���ӵ�����
	const auto& taskList = GlobalManager::getInstance().getTasks();
	// ��������ӱ��������ڵ�

	auto bg = Sprite::create("GoldWood.png");																	// ������������
	bg->setPosition(Vec2::ZERO);																				// ����ڸ��ڵ��λ��
	bg->setName("bgSprite");
	mapParentNode->addChild(bg);																				// ������������ӵ����ڵ�

	// ����������¼�������
	auto mouseListener = EventListenerMouse::create();															// ��������¼�������
	mouseListener->onMouseScroll = CC_CALLBACK_1(Setting2::onMouseScroll, this);								// �����������¼��ص�����
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);								// ����������¼�������
	  
	// ������������ʵ��
	_backgroundManager = new BackgroundManager(this);															// ������������ʵ��
	// �����˵���
	auto downtownMenuItem = createTextButton("Downtown", "fonts/Marker Felt.ttf", 80, "smallmap/village.tmx");			// �����˵������������ı������塢�����С������ͼƬ
	auto castleMenuItem = createTextButton("Castle", "fonts/Marker Felt.ttf",80, "smallmap/castle.tmx");
	auto woodMenuItem = createTextButton("Wood", "fonts/Marker Felt.ttf", 80, "smallmap/wood.tmx");
	auto goldMenuItem = createTextButton("Gold", "fonts/Marker Felt.ttf", 80, "smallmap/gold1.tmx");

	// �����˵�
	auto menu = Menu::create(downtownMenuItem, castleMenuItem, woodMenuItem, goldMenuItem, nullptr);			// �����˵�������������˵����ָ��
	menu->setPosition(Vec2::ZERO);																				// ���ò˵���λ��
	mapParentNode->addChild(menu); // ���˵���ӵ����ڵ�

	// ���ð�ť��λ�ã�����ڸ��ڵ㣩
	// ���ð�ť��λ�ã�����ڸ��ڵ㣩
	downtownMenuItem->setPosition(Vec2(-100, -2.22));														                                      //���ò˵����λ�� ��ͬ
	castleMenuItem->setPosition(Vec2(0, 61.11));
	woodMenuItem->setPosition(Vec2(-300, -455.55));
	goldMenuItem->setPosition(Vec2(600, -132.22));

	return true;
}

cocos2d::Scene* Setting2::createScene()
{
	auto scene = Setting2::create();																			    // ��������		
	return scene;
}

void Setting2::disableBigMapScrolling()																			// �Ƴ��������¼�������
{
	_eventDispatcher->removeEventListenersForTarget(this);														
}

void Setting2::menuItemCallback1(Ref* sender, const std::string& backgroundImage)
{
	disableBigMapScrolling();																					// �Ƴ��������¼�������
	MiniMap* miniMap = new MiniMap();																	      // ���� MiniMap ʵ��
	if (miniMap)
	{
		miniMap->autorelease();																				  // �ͷ� MiniMap ʵ��
		miniMap->FlyToMap(backgroundImage);																	  // ��ת��ָ����ͼ
	}
													// ���ñ���
	// ���ػ��Ƴ� BigMap
	auto mapParentNode = this->getChildByTag(100);																// ��ȡ���� BigMap �ĸ��ڵ�
	if (mapParentNode) {
		auto bgSprite = mapParentNode->getChildByName("bgSprite");												// ��ȡ��������
		if (bgSprite) {
			bgSprite->setVisible(false);                                                                        // ��������������Ϊ���ɼ�
		}
	}

	// ���ز˵�
	auto menuNode = this->getChildByTag(200);																	// ��ȡ�˵��ڵ�
	if (menuNode) {
		menuNode->setVisible(false);																			// ���ز˵�
		auto menuRef = dynamic_cast<Menu*>(menuNode);
		if (menuRef) {
			menuRef->setEnabled(false);																			// ���ý���
		}
	}
}


cocos2d::MenuItemLabel* Setting2::createTextButton(const std::string& text, const std::string& fontFile, int fontSize, const std::string& backgroundImage)
{
	auto label = Label::createWithTTF(text, fontFile, fontSize);												// �������ֱ�ǩ
	label->setTextColor(Color4B::BLACK);																		// ����������ɫ

	// �������ְ�ť�����󶨻ص�����
	auto button = MenuItemLabel::create                                                                         //�������ְ�ť
	(label, [this, backgroundImage](Ref* sender)
		{
			this->menuItemCallback1(sender, backgroundImage);													// ���ò˵���ص�����
		}
	); 
	return button;
}

//С��ͼ�ķŴ���С����
void Setting2::onMouseScroll(cocos2d::Event* event) {
	auto mouseEvent = static_cast<cocos2d::EventMouse*>(event);
	float scrollY = mouseEvent->getScrollY();
	auto mapParentNode = this->getChildByTag(100);

	if (!mapParentNode) return;

	// ��ȡ��ǰ���ź��µ�����ֵ
	float currentScale = mapParentNode->getScale();
	float scaleChange = scrollY > 0 ? 0.1f : -0.1f;
	float newScale = currentScale + scaleChange;
	// �������ŷ�Χ
	newScale = std::max(0.5f, std::min(newScale, 5.0f));

	// �������ֵû�иı䣬ֱ�ӷ���
	if (std::abs(newScale - currentScale) < 0.001f) return;

	// ƽ������Ч��
	mapParentNode->stopAllActions();
	auto scaleTo = ScaleTo::create(0.1f, newScale);
	auto easeAction = EaseOut::create(scaleTo, 2.0f);
	mapParentNode->runAction(easeAction);

	// ��ȡ��Ļ�߽�
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	// ȷ��λ������Ч��Χ��
	Vec2 currentPos = mapParentNode->getPosition();
	float minX = origin.x + visibleSize.width - 3100;
	float minY = origin.y + visibleSize.height - 2000;

	currentPos.x = std::max(currentPos.x, minX);
	currentPos.y = std::max(currentPos.y, minY);

	mapParentNode->setPosition(currentPos);
}





