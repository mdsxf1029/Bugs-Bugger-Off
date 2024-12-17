#include "BackpackLayer.h"
#include "PopupLayer.h"
#include "ui/UIScrollView.h"

USING_NS_CC;

BackpackLayer::BackpackLayer()
    : _backpack(nullptr)  // Ĭ�ϳ�ʼ��Ϊ nullptr
{
}

BackpackLayer::~BackpackLayer()
{
}

bool BackpackLayer::init()
{
    if (!Layer::init()) {
        return false;
    }

    // ��������ı�����ɫ
    auto background = LayerColor::create(Color4B::WHITE, 3100, 2600);
    background->setPosition(Vec2(2500, 1000));  // �������λ��
    this->addChild(background);

    createBackpackUI();

    return true;
}

// ������������ UI
// ���������е���Ʒ�����豳����һ����Ʒ���Ƶ��б�
// ������������ UI
void BackpackLayer::createBackpackUI()
{
    // ����������ͼ��������ʾ��Ʒ
    auto scrollView = ui::ScrollView::create();
    scrollView->setContentSize(Size(3100, 2600));  // ���ù�����ͼ�Ĵ�С
    scrollView->setPosition(Vec2(2500, 1000));  // ���ù�����ͼ��λ��
    scrollView->setBounceEnabled(true);  // ���ûص�Ч��
    scrollView->setDirection(ui::ScrollView::Direction::VERTICAL);  // ��ֱ����
    this->addChild(scrollView);

    // ���ù�����ͼ���ڲ�������С����Ӧ������Ʒ��
    scrollView->setInnerContainerSize(Size(760, 1000));  // �ڲ������ĸ߶��㹻���ɶ����Ʒ


    auto closeButton = ui::Button::create("CloseNormal.png");
    closeButton->setPosition(Vec2(5700, 3500));  // ���ùرհ�ť��λ��
    closeButton->addClickEventListener([=](Ref* sender) {
        this->removeFromParent();  // �رյ���
        });
    this->addChild(closeButton);

    // ÿ����ť�Ŀ��
    const float itemWidth = 765; // ��Ʒ��ť�Ŀ��
    const float itemHeight = 765; // ��Ʒ��ť�ĸ߶�
    const float scrollViewWidth = 3800; // ������ͼ�Ŀ��

    // ÿ�п��ԷŶ��ٸ���Ʒ
    int itemsPerRow = static_cast<int>(scrollViewWidth / itemWidth);

    // ������Ʒ��ͼ��ͼƬӳ�䣨��Ʒ������ͼƬ֮��Ķ�Ӧ��ϵ��
    std::map<std::string, std::string> itemImageMap = {
     {"HELMET", "helmet(1).png"},										// ͷ��
     {"ARMOR", "shangyi.png"},											// ����
     {"SHOES", "xiazhuang.png"},											// Ь��
     {"MAGIC_RING", "ring.png"},								// ħ����ָ
     {"MAGIC_CRYSTAL", "shuijing.png"},							// ħ��ˮ��
     {"MAGIC_SCROLL", "shuijing.png"},							// ħ������
     {"FISH", "shuijing.png"},											// ��
     {"FRUIT", "shuijing.png"},											// ˮ��
     {"VEGETABLE", "shuijing.png"},									// �߲�
     {"HERB", "shuijing.png"},											// ��ҩ
     {"MEAT", "shuijing.png"},											// ��
     {"MUSHROOM", "shuijing.png"},									// Ģ��
     {"RICE", "shuijing.png"},											// ����
     {"APPLE", "shuijing.png"},											// ƻ��
     {"TREE", "shuijing.png"},											// ��
     {"WOOD", "shuijing.png"},											// ľͷ
     {"GOLD_MINE", "shuijing.png"},									// ���
     {"STONE", "shuijing.png"},											// ʯͷ
     {"CHEST", "shuijing.png"},											// ����
     {"KEY", "shuijing.png"},												// Կ��
     {"LETTER", "shuijing.png"}										// �ż�
    };


    int i = 0;
    if (_backpack)
    {
        for (auto& item : _backpack->getItems())
        {
            // ������Ʒ��Ӧ��ͼƬ
            std::string itemImage = itemImageMap[item.name]; //��ȡ��ƷͼƬ·��

            // ���㵱ǰ��Ʒ�ڵ�ǰ�е� x ����
            int row = i / itemsPerRow; // ��ǰ��Ʒ��������
            int col = i % itemsPerRow; // ��ǰ��Ʒ�ڵ�ǰ�е�λ��

            float xPos = 380 + (col * itemWidth);  // ������Ʒ�� X ����
            float yPos = 2200 - (row * itemHeight);  // ������Ʒ�� Y ����

            // ������Ʒ��ť����ʹ�ò�ͬ��ͼƬ
            auto itemButton = ui::Button::create(itemImage, itemImage);  // ���ð�ť��ͼƬ
            itemButton->setPosition(Vec2(xPos, yPos));  // ���ð�ťλ��
            itemButton->setTitleText(item.name + "*" + std::to_string(item.num));  // ���ð�ť����Ϊ��Ʒ����
            itemButton->setTitleFontSize(70);

            // ��Ӱ�ť����¼�
            itemButton->addClickEventListener([=](Ref* sender) {


                // ������Ʒ���䱸����ʾ��
                std::string message = "has been equipped";
                CCLOG("Showing popup with message: %s", message.c_str());  // ��ӡ������Ϣ
                auto popup = PopupLayer::create(message);
                CCLOG("Showing popup with message: %s", message.c_str());  // ��ӡ������Ϣ
                // ȷ��������ʾ�ڳ������Ϸ������ⱻ����
                auto scene = Director::getInstance()->getRunningScene();
                if (scene) {
                    scene->addChild(popup, 999);  // ȷ��������ʾ�����ϲ�
                }

                // ��������ڵ�����ʾһ��ʱ����Զ���ʧ������������
                popup->runAction(Sequence::create(
                    DelayTime::create(2.0f),  // ������ʾ2��
                    RemoveSelf::create(),      // �Զ��Ƴ�����
                    nullptr
                ));
                });
            // ����ť��ӵ�������ͼ��
            scrollView->addChild(itemButton);
            
            i++;
        }
    }
}






// ���ñ������ݣ���Ʒ��
void BackpackLayer::setBackpack(Backpack* backpack)
{
    _backpack = backpack;  // ���ñ�������
    // ���±��� UI���������»�����Ʒ��
    createBackpackUI();
}

// ������̬�� create �������򻯴�������Ĺ���
BackpackLayer* BackpackLayer::create()
{
    BackpackLayer* ret = new BackpackLayer();
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    else {
        delete ret;
        return nullptr;
    }
}
