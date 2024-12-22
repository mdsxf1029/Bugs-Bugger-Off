#include "GoldWoodSoil.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
#include "Map/MiniMap.h"
USING_NS_CC;

bool Setting3::init()
{
	if (!Scene::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();										   // ��ȡ�ɼ�����Ĵ�С
	Vec2 origin = Director::getInstance()->getVisibleOrigin();											   // ��ȡ�ɼ������ԭ��

	/*����һ�����ڵ���������ͼ�����б�ǩ*/ 
	auto mapParentNode = Node::create();																   // ����һ�����ڵ�
	mapParentNode->setTag(100);																			   // ���ø��ڵ�� tag
	mapParentNode->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2)); // ���ø��ڵ��λ��
	this->addChild(mapParentNode);																		   // �����ڵ���ӵ�����

	/*��������ӱ��������ڵ�*/ 
	auto bg = Sprite::create("GoldWoodSoil.png");														   // ������������
	bg->setPosition(Vec2::ZERO);																		   // ����ڸ��ڵ��λ��
	bg->setName("bgSprite");																			   // ���ñ������������
	mapParentNode->addChild(bg);																		   // ������������ӵ����ڵ�

	/*����������¼�������*/ 
	auto mouseListener = EventListenerMouse::create();													   // ��������¼�������
	mouseListener->onMouseScroll = CC_CALLBACK_1(Setting3::onMouseScroll, this);						   // �����������¼��ص�����
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);					       // ����������¼�������
	_backgroundManager = new BackgroundManager(this);													   // ������������ʵ��
	/*�����˵���*/ 
	auto downtownMenuItem = createTextButton("Downtown", "fonts/Marker Felt.ttf", 80, "smallmap/village.tmx");	 // �����˵��
	auto castleMenuItem = createTextButton("Castle", "fonts/Marker Felt.ttf", 80, "smallmap/castle.tmx");		 // ������������֣����壬�����С������ͼƬ
	auto soilMenuItem = createTextButton("Soil", "fonts/Marker Felt.ttf", 80, "smallmap/earth.tmx");
	auto woodMenuItem = createTextButton("Wood", "fonts/Marker Felt.ttf", 80, "smallmap/wood.tmx");
	auto goldMenuItem = createTextButton("Gold", "fonts/Marker Felt.ttf", 80, "smallmap/gold1.tmx");

	/*�����˵�*/ 
	auto menu = Menu::create(downtownMenuItem, castleMenuItem, soilMenuItem, woodMenuItem, goldMenuItem, nullptr);// �����˵�������������˵����ָ��
	menu->setPosition(Vec2::ZERO);																				  // ���ò˵���λ��
	mapParentNode->addChild(menu);																				  // ���˵���ӵ����ڵ�

	/*���ð�ť��λ�ã�����ڸ��ڵ㣩*/ 
	downtownMenuItem->setPosition(Vec2(-100, -2.22));														      //���ò˵����λ�� ��ͬ
	castleMenuItem->setPosition(Vec2(0, 61.11));
	soilMenuItem->setPosition(Vec2(-800, 11.11));
	woodMenuItem->setPosition(Vec2(-300, -455.55));
	goldMenuItem->setPosition(Vec2(600, -132.22));

	return true;
}
cocos2d::Scene* Setting3::createScene()																			  // ��������
{
	auto scene = Setting3::create();																			  // ��������		
	return scene;																								  // ���س���
}
void Setting3::disableBigMapScrolling()																			  // ���ô��ͼ����
{
	_eventDispatcher->removeEventListenersForTarget(this);														  // �Ƴ��������¼�������
}

void Setting3::menuItemCallback1(Ref* sender, const std::string& backgroundImage)
{
	disableBigMapScrolling();																// ���ô��ͼ����											

	MiniMap* miniMap = new MiniMap();														// ���� MiniMap ʵ��
	if (miniMap)																			// ��� MiniMap ʵ�������ɹ�
	{
		miniMap->autorelease();																// �ͷ� MiniMap ʵ��
		miniMap->FlyToMap(backgroundImage);													// ��ת��ָ����ͼ
	}													

	/*���ػ��Ƴ� BigMap*/ 
	auto mapParentNode = this->getChildByTag(100);											// ��ȡ���� BigMap �ĸ��ڵ�
	if (mapParentNode) {																	// ������ڵ����
		auto bgSprite = mapParentNode->getChildByName("bgSprite");							// ��ȡ��������
		if (bgSprite) {																		// ��������������
			bgSprite->setVisible(false);													// ��ʹ�� mapParentNode->removeChild(bgSprite);
		}
	}

	/*���ز˵�*/ 
	auto menuNode = this->getChildByTag(200);												// ��ȡ�˵��ڵ�
	if (menuNode) {																			// ����˵��ڵ����
		menuNode->setVisible(false);														// ���ز˵�
		auto menuRef = dynamic_cast<Menu*>(menuNode);										// ���˵��ڵ�ת��Ϊ�˵�
		if (menuRef) {																		// ����˵�����
			menuRef->setEnabled(false);														// ���ý���
		}
	}
}


cocos2d::MenuItemLabel* Setting3::createTextButton(const std::string& text, const std::string& fontFile, int fontSize, const std::string& backgroundImage)
{
	auto label = Label::createWithTTF(text, fontFile, fontSize);							// �������ֱ�ǩ
	label->setTextColor(Color4B::BLACK);													// ����������ɫ									

	/*�������ְ�ť�����󶨻ص�����*/ 
	auto button = MenuItemLabel::create                                                     //�������ְ�ť
	(label, [this, backgroundImage](Ref* sender)											// ���ûص�����
		{
			this->menuItemCallback1(sender, backgroundImage);								// ���ﴫ����Ǳ���ͼƬ
		}
	);

	return button;
}

/*С��ͼ�ķŴ���С����*/
void Setting3::onMouseScroll(cocos2d::Event* event) {
	auto mouseEvent = static_cast<cocos2d::EventMouse*>(event);								// ��ȡ����¼�
	float scrollY = mouseEvent->getScrollY();												// ��ȡ�����ֵĹ���ֵ
	auto mapParentNode = this->getChildByTag(100);											// ��ȡ���� BigMap �ĸ��ڵ�

	if (!mapParentNode) return;																// ������ڵ㲻���ڣ�ֱ�ӷ���

	/* ��ȡ��ǰ���ź��µ�����ֵ*/
	float currentScale = mapParentNode->getScale();											// ��ȡ��ǰ����ֵ
	float scaleChange = scrollY > 0 ? 0.1f : -0.1f;											// �������ű仯ֵ
	float newScale = currentScale + scaleChange;											// �����µ�����ֵ
	newScale = std::max(0.5f, std::min(newScale, 5.0f));									// �������ŷ�Χ
	if (std::abs(newScale - currentScale) < 0.001f) return;									// �������ֵû�иı䣬ֱ�ӷ���

	/*ƽ������Ч��*/ 
	mapParentNode->stopAllActions();														// ֹͣ���ж���
	auto scaleTo = ScaleTo::create(0.1f, newScale);											// �������Ŷ���
	auto easeAction = EaseOut::create(scaleTo, 2.0f);										// ������������
	mapParentNode->runAction(easeAction);													// ִ�ж���

	/*��ȡ��Ļ�߽�*/ 
	auto visibleSize = Director::getInstance()->getVisibleSize();							// ��ȡ�ɼ�����Ĵ�С
	auto origin = Director::getInstance()->getVisibleOrigin();								// ��ȡ�ɼ������ԭ��

	/*ȷ��λ������Ч��Χ��*/ 
	Vec2 currentPos = mapParentNode->getPosition();											// ��ȡ��ǰλ��
	float minX = origin.x + visibleSize.width - 3100;										// ������С x ����
	float minY = origin.y + visibleSize.height - 2000;										// ������С y ����

	currentPos.x = std::max(currentPos.x, minX);											// ���� x ����
	currentPos.y = std::max(currentPos.y, minY);											// ���� y ����

	mapParentNode->setPosition(currentPos);
}
