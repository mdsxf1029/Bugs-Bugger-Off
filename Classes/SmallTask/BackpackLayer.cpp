#include "BackpackLayer.h"
#include "PopupLayer.h"
#include "ui/UIScrollView.h"
#include "manager.h"
#include "items.h"

USING_NS_CC;
std::vector<std::shared_ptr<Item>> items;
BackpackLayer::BackpackLayer()
    : _backpack(nullptr) // Ĭ�ϳ�ʼ��Ϊ nullptr
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



void BackpackLayer::onItemClicked(Ref* sender)
{
    // ������Ʒ����¼�
    CCLOG("Item clicked!");
}

// ������������ UI
void BackpackLayer::createBackpackUI()
{
    // ��ȡ������������Ʒ������ͨ�� GlobalManager ��ȡ��
    const auto& weaponsList = GlobalManager::getInstance().getWeapons();
    const auto& armorsList = GlobalManager::getInstance().getArmors();
    const auto& foodsList = GlobalManager::getInstance().getFoods();
    const auto& materialsList = GlobalManager::getInstance().getMaterials();

    // ���֮ǰ����Ʒ
    items.clear();

    // ����������Ʒ����ӵ� items ����
    for (const auto& weapon : weaponsList) {
        items.push_back(weapon);  // �� weapon ��ӵ� items ������
    }

    for (const auto& armor : armorsList) {
        items.push_back(armor);  // �� armor ��ӵ� items ������
    }

    for (const auto& food : foodsList) {
        items.push_back(food);  // �� food ��ӵ� items ������
    }

    for (const auto& material : materialsList) {
        items.push_back(material);  // �� material ��ӵ� items ������
    }


    // ����������ͼ��������ʾ��Ʒ
    auto scrollView = ui::ScrollView::create();
    scrollView->setContentSize(Size(3100, 2600));  // ���ù�����ͼ�Ĵ�С
    scrollView->setPosition(Vec2(2500, 1000));  // ���ù�����ͼ��λ��
    scrollView->setBounceEnabled(true);  // ���ûص�Ч��
    scrollView->setDirection(ui::ScrollView::Direction::VERTICAL);  // ��ֱ����
    this->addChild(scrollView);

    // ���ù�����ͼ���ڲ�������С����Ӧ������Ʒ��
    scrollView->setInnerContainerSize(Size(760, 1000));  // �ڲ������ĸ߶��㹻���ɶ����Ʒ

    // ÿ����ť�Ŀ��
    const float itemWidth = 765; // ��Ʒ��ť�Ŀ��
    const float itemHeight = 765; // ��Ʒ��ť�ĸ߶�
    const float scrollViewWidth = 3800; // ������ͼ�Ŀ��

    // ÿ�п��ԷŶ��ٸ���Ʒ
    int itemsPerRow = static_cast<int>(scrollViewWidth / itemWidth);

    // ������Ʒ��ͼ��ͼƬӳ�䣨��Ʒ������ͼƬ֮��Ķ�Ӧ��ϵ��
    std::map<std::string, std::string> itemImageMap = {
     {"HELMET", "helmet.png"},
     {"ARMOR", "armor.png"},
     {"SHOES", "shoes.png"},
     {"MAGIC_RING", "magic_ring.png"},
     {"MAGIC_CRYSTAL", "magic_crystal.png"},
     {"MAGIC_SCROLL", "magic_scroll.png"},
     {"FISH", "fish.png"},
     {"FRUIT", "fruit.png"},
     {"VEGETABLE", "vegetable.png"},
     {"HERB", "herb.png"},
     {"MEAT", "meat.png"},
     {"MUSHROOM", "mushroom.png"},
     {"RICE", "rice.png"},
     {"APPLE", "apple.png"},
     {"TREE", "tree.png"},
     {"WOOD", "wood.png"},
     {"GOLD_MINE", "gold_mine.png"},
     {"STONE", "stone.png"},
     {"CHEST", "chest.png"},
     {"KEY", "key.png"},
     {"LETTER", "letter.png"}
    };

    int i = 0;
    for (const auto& item :items) {
        // ����ÿ����Ʒ����ȡ��ӦͼƬ��
        std::string itemImage = itemImageMap[item->getItemName()];

        // ���㵱ǰ��Ʒ�ڵ�ǰ�е� x ����
        int row = i / itemsPerRow;
        int col = i % itemsPerRow;

        float xPos = 380 + (col * itemWidth);
        float yPos = 2200 - (row * itemHeight);

        auto itemButton = ui::Button::create(itemImage, itemImage);
        itemButton->setPosition(Vec2(xPos, yPos));
        itemButton->setTitleText(std::to_string(item->getNum()));
        itemButton->setTitleFontSize(24);

        itemButton->addClickEventListener([=](Ref* sender) {
            CCLOG("Clicked item: %s", item->getItemName().c_str());

            // ������Ʒ���䱸����ʾ��
            std::string message = "has been equipped";
            auto popup = PopupLayer::create(message);
            auto scene = Director::getInstance()->getRunningScene();
            if (scene) {
                scene->addChild(popup, 999);  // ȷ��������ʾ�����ϲ�
            }

            // ������ʾ2����Զ���ʧ
            popup->runAction(Sequence::create(DelayTime::create(2.0f), RemoveSelf::create(), nullptr));
            });

        scrollView->addChild(itemButton);
        i++;
    }
}

// ���ñ������ݣ���Ʒ��
void BackpackLayer::setBackpack(Backpack* backpack)
{
    _backpack = backpack;  // ���ñ�������
    createBackpackUI();  // ���±��� UI
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
