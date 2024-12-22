#include "SoilWaterGoldFireWood.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
#include "Map/MiniMap.h"
USING_NS_CC;

bool Setting5::init()																						//��ʼ��
{
	if (!Scene::init())																						//���û���ĳ�ʼ������ ���������ʼ��ʧ��
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();											//��ȡ�ɼ�����Ĵ�С
	Vec2 origin = Director::getInstance()->getVisibleOrigin();												//��ȡ�ɼ������ԭ��

	// ����һ�����ڵ���������ͼ�����б�ǩ
	auto mapParentNode = Node::create();																	//����һ���ڵ�
	mapParentNode->setTag(100);																				// ���ø��ڵ�� tag
	mapParentNode->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));	//���ýڵ��λ��	
	this->addChild(mapParentNode);																			//���ڵ���ӵ�������
	//
	// ��������ӱ��������ڵ�
	auto bg = Sprite::create("GoldWoodSoilWaterFire.png");													//����һ������
	bg->setPosition(Vec2::ZERO);																			// ����ڸ��ڵ��λ��  ���λ��
	bg->setName("bgSprite");																				//���þ��������
	mapParentNode->addChild(bg);																			//��������ӵ��ڵ���

	// ����������¼�������
	auto mouseListener = EventListenerMouse::create();														//����һ������¼�������
	mouseListener->onMouseScroll = CC_CALLBACK_1(Setting5::onMouseScroll, this);							//�����������¼�������
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);							//����������¼�������



	// ������������ʵ��
	_backgroundManager = new BackgroundManager(this);														//������������ʵ��
	// �����˵���
	auto downtownMenuItem = createTextButton("Downtown", "fonts/Marker Felt.ttf", 80, "smallmap/village.tmx");		//����һ���˵���   ���о�Ϊ�˵���
	auto castleMenuItem = createTextButton("Castle", "fonts/Marker Felt.ttf", 80, "smallmap/castle.tmx");		
	auto soilMenuItem = createTextButton("Soil", "fonts/Marker Felt.ttf", 80, "smallmap/earth.tmx");
	auto fireMenuItem = createTextButton("Fire", "fonts/Marker Felt.ttf", 80, "smallmap/fire.tmx");
	auto woodMenuItem = createTextButton("Wood", "fonts/Marker Felt.ttf", 80, "smallmap/wood.tmx");
	auto waterMenuItem = createTextButton("Water", "fonts/Marker Felt.ttf", 80, "smallmap/whole3.tmx");
	auto goldMenuItem = createTextButton("Gold", "fonts/Marker Felt.ttf", 80, "smallmap/gold1.tmx");

	// �����˵�
	auto menu = Menu::create(downtownMenuItem, castleMenuItem, soilMenuItem, fireMenuItem, woodMenuItem, waterMenuItem, goldMenuItem, nullptr);	  //����һ���˵�
	menu->setPosition(Vec2::ZERO);																			                                      //���ò˵���λ��
	mapParentNode->addChild(menu);																			                                      // ���˵���ӵ����ڵ�

	// ���ð�ť��λ�ã�����ڸ��ڵ㣩
	downtownMenuItem->setPosition(Vec2(-100, -2.22));														                                      //���ò˵����λ�� ��ͬ
	castleMenuItem->setPosition(Vec2(0, 61.11));	
	soilMenuItem->setPosition(Vec2(-800,11.11));
	fireMenuItem->setPosition(Vec2(400, 555.55));
	woodMenuItem->setPosition(Vec2(-300, -455.55));
	waterMenuItem->setPosition(Vec2(-500, 566.66));
	goldMenuItem->setPosition(Vec2(600, -132.22));

	return true;
}

void Setting5::disableBigMapScrolling()																		//���ô��ͼ����	
{ 
	_eventDispatcher->removeEventListenersForTarget(this);													// �Ƴ��������¼�������
}
cocos2d::Scene* Setting5::createScene()
{
	auto scene = Setting5::create();																			    // ��������		
	return scene;
}
void Setting5::menuItemCallback1(Ref* sender, const std::string& backgroundImage)							//�˵���ص�����
{
	disableBigMapScrolling();																				// ���� BigMap �Ĺ�������
	 
	MiniMap* miniMap = new MiniMap();																	      // ���� MiniMap ʵ��
	if (miniMap)
	{
		miniMap->autorelease();																				  // �ͷ� MiniMap ʵ��
		miniMap->FlyToMap(backgroundImage);																	  // ��ת��ָ����ͼ
	}													// �л�����

	// ���ػ��Ƴ� BigMap
	auto mapParentNode = this->getChildByTag(100);															// ��ȡ���� BigMap �ĸ��ڵ�
	if (mapParentNode) {
		auto bgSprite = mapParentNode->getChildByName("bgSprite");
		if (bgSprite) {
			bgSprite->setVisible(false);																	// ��ʹ�� mapParentNode->removeChild(bgSprite);
		}
	}

	// ���ز˵�
	auto menuNode = this->getChildByTag(200);																// ��ȡ�˵��ڵ�
	if (menuNode) {
		menuNode->setVisible(false);																		// ���ز˵�
		auto menuRef = dynamic_cast<Menu*>(menuNode);														// ת��Ϊ Menu ����
		if (menuRef) {
			menuRef->setEnabled(false);																		// ���ý���
		}
	}
}


cocos2d::MenuItemLabel* Setting5::createTextButton(const std::string& text, const std::string& fontFile, int fontSize, const std::string& backgroundImage)
{ 
	auto label = Label::createWithTTF(text, fontFile, fontSize);											//����һ�����ֱ�ǩ	 
	label->setTextColor(Color4B::BLACK);																	// ����������ɫ
	auto button = MenuItemLabel::create                                                                     // �������ְ�ť�����󶨻ص�����
	(label, [this, backgroundImage](Ref* sender)
		{
			this->menuItemCallback1(sender, backgroundImage);
		}
	);

	return button;																							//���ذ�ť
}

void Setting5::onMouseScroll(cocos2d::Event* event) {
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







