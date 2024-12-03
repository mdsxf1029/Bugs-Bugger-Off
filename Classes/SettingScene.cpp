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

	// ����һ�����ڵ���������ͼ�����б�ǩ
	auto mapParentNode = Node::create();
	mapParentNode->setTag(100); // ���ø��ڵ�� tag
	mapParentNode->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(mapParentNode);

	// ��������ӱ��������ڵ�
	auto bg = Sprite::create("Gold.png");
	bg->setPosition(Vec2::ZERO); // ����ڸ��ڵ��λ��
	bg->setName("bgSprite");
	mapParentNode->addChild(bg);

	// ����������¼�������
	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseScroll = CC_CALLBACK_1(Setting::onMouseScroll, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
	
	

	// ������������ʵ��
	_backgroundManager = new BackgroundManager(this);
	// �����˵���
	auto downtownMenuItem = createTextButton("Downtown", "fonts/Marker Felt.ttf", 300, "downtown.png");
	auto castleMenuItem = createTextButton("Castle", "fonts/Marker Felt.ttf", 300, "castle.png");
	auto goldMenuItem = createTextButton("Gold", "fonts/Marker Felt.ttf", 300, "goldMap.png");

	// �����˵�
	auto menu = Menu::create(downtownMenuItem, castleMenuItem, goldMenuItem, nullptr);
	menu->setPosition(Vec2::ZERO);
	mapParentNode->addChild(menu); // ���˵���ӵ����ڵ�

	// ���ð�ť��λ�ã�����ڸ��ڵ㣩
	downtownMenuItem->setPosition(Vec2(-500, -100));
	castleMenuItem->setPosition(Vec2(0, 500));
	goldMenuItem->setPosition(Vec2(3000, -1000));

	return true;
}

void Setting::disableBigMapScrolling()
{
	// �Ƴ��������¼�������
	_eventDispatcher->removeEventListenersForTarget(this);
}

void Setting::menuItemCallback1(Ref* sender, const std::string& backgroundImage)
{
	// ���� BigMap �Ĺ�������
	disableBigMapScrolling();

	// �л�����
	_backgroundManager->setBackground(backgroundImage);

	// ���ػ��Ƴ� BigMap
	auto mapParentNode = this->getChildByTag(100); // ��ȡ���� BigMap �ĸ��ڵ�
	if (mapParentNode) {
		auto bgSprite = mapParentNode->getChildByName("bgSprite");
		if (bgSprite) {
			bgSprite->setVisible(false); // ��ʹ�� mapParentNode->removeChild(bgSprite);
		}
	}

	// ���ز˵�
	auto menuNode = this->getChildByTag(200); // ��ȡ�˵��ڵ�
	if (menuNode) {
		menuNode->setVisible(false); // ���ز˵�
		auto menuRef = dynamic_cast<Menu*>(menuNode);
		if (menuRef) {
			menuRef->setEnabled(false); // ���ý���
		}
	}
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
	float scrollY = mouseEvent->getScrollY();

	// ��ȡ���ڵ㣨������ͼ�ͱ�ǩ��
	auto mapParentNode = this->getChildByTag(100);
	if (mapParentNode) {
		// ��ȡ��ǰ���ű���
		float currentScale = mapParentNode->getScale();

		// ���ݹ��ַ���������ű���
		float newScale = currentScale + (scrollY > 0 ? 0.1f : -0.1f); // �ϻ��Ŵ��»���С
		newScale = std::max(0.5f, std::min(newScale, 5.0f)); // �������ŷ�Χ

		// ��ȡ�����Ļ����
		Vec2 mousePositionScreen = Vec2(mouseEvent->getCursorX(), mouseEvent->getCursorY());

		// �������Ļ����ת��Ϊ OpenGL ����
		Vec2 mousePositionGL = Director::getInstance()->convertToGL(mousePositionScreen);

		// ���������ת��Ϊ���ڵ�ľֲ�����
		Vec2 mousePositionLocalBeforeScale = mapParentNode->convertToNodeSpace(mousePositionGL);

		// ���Ÿ��ڵ�
		mapParentNode->setScale(newScale);

		// ��ȡ���ź�ĵ�ͼ��С
		auto mapSize = mapParentNode->getContentSize() * newScale;

		// �����λ������ת��Ϊ���ź���������
		Vec2 mousePositionLocalAfterScale = mapParentNode->convertToNodeSpace(mousePositionGL);

		// �����������ǰ���λ�ò���
		Vec2 positionOffset = mousePositionLocalBeforeScale - mousePositionLocalAfterScale;

		// ��ȡ��ǰ��ͼ��λ��
		Vec2 currentMapPosition = mapParentNode->getPosition();

		// ���µ�ͼλ�ã�ʹ���λ�ñ�������ͬ��λ��
		Vec2 newMapPosition = currentMapPosition + positionOffset;

		// ��ȡ��Ļ�ɼ�����
		auto visibleSize = Director::getInstance()->getVisibleSize();
		auto origin = Director::getInstance()->getVisibleOrigin();

		// ���Ƶ�ͼ��λ�ã���ֹ������Ļ
		newMapPosition.x =origin.x+visibleSize.width-3100;
		
		newMapPosition.y = origin.y + visibleSize.height-2000;


		if ((currentMapPosition.x == (origin.x + visibleSize.width - 3100)) &&
			(currentMapPosition.y == origin.y + visibleSize.height - 2000))
		{
			mapParentNode->setPosition(mousePositionGL);
		}
		else
		{
			mapParentNode->setPosition(newMapPosition);
		}
	
	
	}
}




