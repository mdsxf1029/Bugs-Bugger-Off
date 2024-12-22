#include "BackpackLayer.h"
#include "PopupLayer.h"
#include "ui/UIScrollView.h"

USING_NS_CC;

BackpackLayer::BackpackLayer() : _backpack(nullptr)  // Ĭ�ϳ�ʼ��Ϊ nullptr
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


    auto background = LayerColor::create(Color4B::WHITE, 620, 577); // ��������ı�����ɫ
    background->setPosition(Vec2(500, 222));                        // �������λ��
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
    CCLOG("SCORLL");
    scrollView->setDirection(ui::ScrollView::Direction::VERTICAL);  // ��ֱ����
    scrollView->setContentSize(Size(620, 577));                     // ���ù�����ͼ�Ĵ�С
    scrollView->setInnerContainerSize(Size(620, 877));
    scrollView->setPosition(Vec2(500, 222));                        // ���ù�����ͼ��λ��
    this->addChild(scrollView, 10);


    // ���û�������ʽ
    scrollView->setScrollBarEnabled(true);                       // ���û�����
    scrollView->setScrollBarColor(Color3B::WHITE);               // ���û�������ɫ
    scrollView->setScrollBarOpacity(300);                        // ���û�����͸����
    scrollView->setScrollBarAutoHideEnabled(false);

    // ���ù�����ͼ���ڲ�������С����Ӧ������Ʒ��
    //scrollView->setInnerContainerSize(Size(152, 300));         // �ڲ������ĸ߶��㹻���ɶ����Ʒ


    auto closeButton = ui::Button::create("CloseNormal.png");
    closeButton->setPosition(Vec2(1140, 800));                  // ���ùرհ�ť��λ��
    closeButton->addClickEventListener([=](Ref* sender) {
        this->removeFromParent();                               // �رյ���
        });
    this->addChild(closeButton);

    // ÿ����ť�Ŀ��
    const float itemWidth = 153;                                // ��Ʒ��ť�Ŀ��
    const float itemHeight = 170;                               // ��Ʒ��ť�ĸ߶�
    const float scrollViewWidth = 760;                          // ������ͼ�Ŀ��

    // ÿ�п��ԷŶ��ٸ���Ʒ
    int itemsPerRow = static_cast<int>(scrollViewWidth / itemWidth);

    // ������Ʒ��ͼ��ͼƬӳ�䣨��Ʒ������ͼƬ֮��Ķ�Ӧ��ϵ��
    std::map<std::string, std::string> itemImageMap = {
     {"HELMET", "helmet.png"},										    // ͷ��
     {"ARMOR", "shangyi.png"},											// ����
     {"SHOES", "xiazhuang.png"},										// Ь��
     {"MAGIC_RING", "ring.png"},								        // ħ����ָ
     {"MAGIC_CRYSTAL", "shuijing.png"},							        // ħ��ˮ��
     {"MAGIC_SCROLL", "juanzhou(1).png"},							        // ħ������
     {"FISH", "shuijing.png"},											// ��
     {"FRUIT", "shuijing.png"},											// ˮ��
     {"VEGETABLE", "Vegetable.png"},									    // �߲�
     {"HERB", "Herb.png"},											// ��ҩ
     {"MEAT", "Meat.png"},											// ��
     {"MUSHROOM", "shuijing.png"},									    // Ģ��
     {"RICE", "wheat.png"},											// ����
     {"APPLE", "Apple.png"},											// ƻ��
     {"TREE", "Tree.png"},											// ��
     {"WOOD", "Littlewood.png"},											// ľͷ
     {"GOLD_MINE", "LittleGold.png"},									    // ���
     {"STONE", "stone.png"},											// ʯͷ
     {"CHEST", "chest.png"},											// ����
     {"KEY", "shuijing.png"},											// Կ��
     {"LETTER", "shuijing.png"}										    // �ż�
    };


    int i = 0;
    if (_backpack)
    {
        CCLOG("KKK");
        for (auto& item : _backpack->getItems())
        {
            CCLOG("EEE");
            // ������Ʒ��Ӧ��ͼƬ
            std::string itemImage = itemImageMap[item.name];                                    //��ȡ��ƷͼƬ·��

            // ���㵱ǰ��Ʒ�ڵ�ǰ�е� x ����
            int row = i / itemsPerRow;                                                          // ��ǰ��Ʒ��������
            int col = i % itemsPerRow;                                                          // ��ǰ��Ʒ�ڵ�ǰ�е�λ��

            float xPos = 76 + (col * itemWidth);  // ������Ʒ�� X ����
            float yPos = scrollView->getInnerContainerSize().height - (row * itemHeight) - 100;   // ������Ʒ�� Y ����

            // ������Ʒ��ť����ʹ�ò�ͬ��ͼƬ
            auto itemButton = ui::Button::create(itemImage, itemImage);                         // ���ð�ť��ͼƬ
            itemButton->setPosition(Vec2(xPos, yPos));                                          // ���ð�ťλ��
            itemButton->setTitleText(item.name + "*" + std::to_string(item.num));               // ���ð�ť����Ϊ��Ʒ����
            itemButton->setTitleFontSize(20);

            // ��Ӱ�ť����¼�
            itemButton->addClickEventListener([=](Ref* sender) {


                // ������Ʒ���䱸����ʾ��
                std::string message = "has been equipped";
                CCLOG("Showing popup with message: %s", message.c_str());                       // ��ӡ������Ϣ
                auto popup = PopupLayer::create(message);
                CCLOG("Showing popup with message: %s", message.c_str());                       // ��ӡ������Ϣ
                // ȷ��������ʾ�ڳ������Ϸ������ⱻ����
                auto scene = Director::getInstance()->getRunningScene();
                if (scene) {
                    scene->addChild(popup, 999);                                                // ȷ��������ʾ�����ϲ�
                }

                // ��������ڵ�����ʾһ��ʱ����Զ���ʧ������������
                popup->runAction(Sequence::create(
                    DelayTime::create(2.0f),                                                    // ������ʾ2��
                    RemoveSelf::create(),                                                       // �Զ��Ƴ�����
                    nullptr
                ));
                });
            scrollView->addChild(itemButton);                                                   // ����ť��ӵ�������ͼ��

            i++;
        }
    }
}






// ���ñ������ݣ���Ʒ��
void BackpackLayer::setBackpack(Backpack* backpack)
{
    _backpack = backpack;                                   // ���ñ�������
    if (_backpack) {
        CCLOG("HHH");
    } 
    createBackpackUI();                                     // ���±��� UI���������»�����Ʒ��
}

// ������̬�� create �������򻯴�������Ĺ���
BackpackLayer* BackpackLayer::create()
{
	BackpackLayer* ret = new BackpackLayer();               // �������������
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    else {
        delete ret;
        return nullptr;
    }
}