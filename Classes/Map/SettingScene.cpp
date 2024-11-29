#include "SettingScene.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
USING_NS_CC;

bool Setting::init()
{
	if (!Scene::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// ��������ӱ���
	auto bg = Sprite::create("BigMap.png");
	float x = origin.x + visibleSize.width / 2;
	float y = origin.y + visibleSize.height / 2;
	bg->setPosition(Vec2(x, y));
	bg->setName("bgSprite"); // ��������Ϊ "bgSprite"
	this->addChild(bg);

	// ������������ʵ��
	_backgroundManager = new BackgroundManager(this);

	// �����˵���
	auto downtownMenuItem = createTextButton("Downtown", "fonts/Marker Felt.ttf", 300, "downtown.png");
	auto castleMenuItem = createTextButton("Castle", "fonts/Marker Felt.ttf", 300, "castle.png");
	auto goldMenuItem = createTextButton("Gold", "fonts/Marker Felt.ttf", 300, "gold.png");
	auto woodMenuItem = createTextButton("Wood", "fonts/Marker Felt.ttf", 300, "wood.png");
	auto waterMenuItem = createTextButton("Water", "fonts/Marker Felt.ttf", 300, "water.png");
	auto fireMenuItem = createTextButton("Fire", "fonts/Marker Felt.ttf", 300, "fire.png");
	auto soilMenuItem = createTextButton("Soil", "fonts/Marker Felt.ttf", 300, "soil.png");

	// �����˵�
	auto menu = Menu::create(downtownMenuItem, castleMenuItem, goldMenuItem, woodMenuItem, waterMenuItem, fireMenuItem, soilMenuItem, nullptr);
	menu->setPosition(Vec2::ZERO);
	menu->setTag(200); // ���ò˵��� tag
	this->addChild(menu);

	// ���ð�ť��λ��
	downtownMenuItem->setPosition(Vec2(origin.x + visibleSize.width / 2 - 500, origin.y + visibleSize.height / 2 - 100));
	castleMenuItem->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + 500));
	goldMenuItem->setPosition(Vec2(origin.x + visibleSize.width / 2 - 2000, origin.y + visibleSize.height / 2 + 500));
	woodMenuItem->setPosition(Vec2(origin.x + visibleSize.width / 2 + 1500, origin.y + visibleSize.height / 2 + 500));
	waterMenuItem->setPosition(Vec2(origin.x + visibleSize.width / 2 - 1500, origin.y + visibleSize.height / 2 - 1500));
	fireMenuItem->setPosition(Vec2(origin.x + visibleSize.width / 2 - 500, origin.y + visibleSize.height / 2 + 1500));
	soilMenuItem->setPosition(Vec2(origin.x + visibleSize.width / 2 + 500, origin.y + visibleSize.height / 2 - 1500));

	return true;
}


void Setting::menuItemCallback1(Ref* sender, const std::string& backgroundImage)
{
	// �л�����
	_backgroundManager->setBackground(backgroundImage);

	// �Ƴ���������
	this->removeChildByName("bgSprite");

	// ���ò��Ƴ��˵�
	auto menuNode = this->getChildByTag(200); // ��ȡ�˵��ڵ�
	if (menuNode) {
		auto menuRef = dynamic_cast<Menu*>(menuNode);
		if (menuRef) {
			menuRef->setEnabled(false); // ���ý���
		}
		this->removeChild(menuNode); // �Ƴ��˵��ڵ�
	}

	// ����������¼�������
	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseScroll = CC_CALLBACK_1(Setting::onMouseScroll, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
}


cocos2d::MenuItemLabel* Setting::createTextButton(const std::string& text, const std::string& fontFile, int fontSize, const std::string& backgroundImage)
{
	// �������ֱ�ǩ
	auto label = Label::createWithTTF(text, fontFile, fontSize);

	// ����������ɫ
	label->setTextColor(Color4B::BLACK); 

	// �������ְ�ť�����󶨻ص�����
	auto button = MenuItemLabel::create
	(label, [this, backgroundImage](Ref* sender) 
	{
		this->menuItemCallback1(sender, backgroundImage);
	}
	);

	return button;
}

//С��ͼ�ķŴ���С����
void Setting::onMouseScroll(cocos2d::Event* event) {
	auto mouseEvent = static_cast<cocos2d::EventMouse*>(event);
	float scrollY = mouseEvent->getScrollY(); // ��ȡ�����ֵĹ���ֵ

	auto map = this->getChildByTag(100); // ��ȡ��ͼ�ڵ�
	if (map) {
		// ��ȡ��ǰ���ű���
		float currentScale = map->getScale();

		// ���ݹ��ַ���������ű���
		float newScale = currentScale + (scrollY > 0 ? 0.1f : -0.1f); // �ϻ��Ŵ��»���С
		newScale = std::max(0.5f, std::min(newScale, 5.0f)); // �������ŷ�Χ

		// ��ȡ�������Ļ�ϵ�λ��
		Vec2 mousePositionScreen = Vec2(mouseEvent->getCursorX(), mouseEvent->getCursorY());

		// �������Ļ����ת��Ϊ OpenGL ����
		Vec2 mousePositionGL = Director::getInstance()->convertToGL(mousePositionScreen);

		// �� OpenGL ����ת��Ϊ��ͼ�ľֲ�����
		Vec2 mousePositionLocal = map->convertToNodeSpace(mousePositionGL);

		// ���ŵ�ͼ
		map->setScale(newScale);

		// ���¼����ͼ�ֲ������������ű����¶�Ӧ����������
		Vec2 mousePositionWorldAfterScale = map->convertToWorldSpace(mousePositionLocal);

		// ������ͼ��λ�ã�ȷ�����λ�ñ��̶ֹ�
		Vec2 mapPosition = map->getPosition();
		Vec2 offset = mousePositionGL - mousePositionWorldAfterScale;
		Vec2 newMapPosition = mapPosition + offset;

		// ��ȡ��ͼ���ź�Ĵ�С
		auto mapSize = map->getContentSize() * newScale;

		// ��ȡ��Ļ�Ŀ�������
		auto visibleSize = Director::getInstance()->getVisibleSize();
		auto origin = Director::getInstance()->getVisibleOrigin();

		// ����߽�����
		float minX = origin.x + visibleSize.width - mapSize.width / 2;
		float maxX = origin.x + mapSize.width / 2;
		float minY = origin.y + visibleSize.height - mapSize.height / 2;
		float maxY = origin.y + mapSize.height / 2;

		// ���Ƶ�ͼ��λ��
		newMapPosition.x = std::max(minX, std::min(maxX, newMapPosition.x));
		newMapPosition.y = std::max(minY, std::min(maxY, newMapPosition.y));

		map->setPosition(newMapPosition);
	}
}

