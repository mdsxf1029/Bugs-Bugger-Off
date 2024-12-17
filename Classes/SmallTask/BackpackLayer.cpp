#include "BackpackLayer.h"
#include "PopupLayer.h"
#include "ui/UIScrollView.h"

USING_NS_CC;

BackpackLayer::BackpackLayer()
    : _backpack(nullptr)  // 默认初始化为 nullptr
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

    // 背包界面的背景颜色
    auto background = LayerColor::create(Color4B::WHITE, 3100, 2600);
    background->setPosition(Vec2(2500, 1000));  // 背包层的位置
    this->addChild(background);

    createBackpackUI();

    return true;
}

// 创建背包界面 UI
// 创建背包中的物品，假设背包是一个物品名称的列表
// 创建背包界面 UI
void BackpackLayer::createBackpackUI()
{
    // 创建滚动视图，用于显示物品
    auto scrollView = ui::ScrollView::create();
    scrollView->setContentSize(Size(3100, 2600));  // 设置滚动视图的大小
    scrollView->setPosition(Vec2(2500, 1000));  // 设置滚动视图的位置
    scrollView->setBounceEnabled(true);  // 启用回弹效果
    scrollView->setDirection(ui::ScrollView::Direction::VERTICAL);  // 垂直滚动
    this->addChild(scrollView);

    // 设置滚动视图的内部容器大小（适应所有物品）
    scrollView->setInnerContainerSize(Size(760, 1000));  // 内部容器的高度足够容纳多个物品


    auto closeButton = ui::Button::create("CloseNormal.png");
    closeButton->setPosition(Vec2(5700, 3500));  // 设置关闭按钮的位置
    closeButton->addClickEventListener([=](Ref* sender) {
        this->removeFromParent();  // 关闭弹窗
        });
    this->addChild(closeButton);

    // 每个按钮的宽度
    const float itemWidth = 765; // 物品按钮的宽度
    const float itemHeight = 765; // 物品按钮的高度
    const float scrollViewWidth = 3800; // 滚动视图的宽度

    // 每行可以放多少个物品
    int itemsPerRow = static_cast<int>(scrollViewWidth / itemWidth);

    // 创建物品的图标图片映射（物品名称与图片之间的对应关系）
    std::map<std::string, std::string> itemImageMap = {
     {"HELMET", "helmet(1).png"},										// 头盔
     {"ARMOR", "shangyi.png"},											// 盔甲
     {"SHOES", "xiazhuang.png"},											// 鞋子
     {"MAGIC_RING", "ring.png"},								// 魔法戒指
     {"MAGIC_CRYSTAL", "shuijing.png"},							// 魔法水晶
     {"MAGIC_SCROLL", "shuijing.png"},							// 魔法卷轴
     {"FISH", "shuijing.png"},											// 鱼
     {"FRUIT", "shuijing.png"},											// 水果
     {"VEGETABLE", "shuijing.png"},									// 蔬菜
     {"HERB", "shuijing.png"},											// 草药
     {"MEAT", "shuijing.png"},											// 肉
     {"MUSHROOM", "shuijing.png"},									// 蘑菇
     {"RICE", "shuijing.png"},											// 稻谷
     {"APPLE", "shuijing.png"},											// 苹果
     {"TREE", "shuijing.png"},											// 树
     {"WOOD", "shuijing.png"},											// 木头
     {"GOLD_MINE", "shuijing.png"},									// 金矿
     {"STONE", "shuijing.png"},											// 石头
     {"CHEST", "shuijing.png"},											// 宝箱
     {"KEY", "shuijing.png"},												// 钥匙
     {"LETTER", "shuijing.png"}										// 信件
    };


    int i = 0;
    if (_backpack)
    {
        for (auto& item : _backpack->getItems())
        {
            // 查找物品对应的图片
            std::string itemImage = itemImageMap[item.name]; //获取物品图片路径

            // 计算当前物品在当前行的 x 坐标
            int row = i / itemsPerRow; // 当前物品所在行数
            int col = i % itemsPerRow; // 当前物品在当前行的位置

            float xPos = 380 + (col * itemWidth);  // 计算物品的 X 坐标
            float yPos = 2200 - (row * itemHeight);  // 计算物品的 Y 坐标

            // 创建物品按钮，并使用不同的图片
            auto itemButton = ui::Button::create(itemImage, itemImage);  // 设置按钮的图片
            itemButton->setPosition(Vec2(xPos, yPos));  // 设置按钮位置
            itemButton->setTitleText(item.name + "*" + std::to_string(item.num));  // 设置按钮标题为物品名称
            itemButton->setTitleFontSize(70);

            // 添加按钮点击事件
            itemButton->addClickEventListener([=](Ref* sender) {


                // 弹出物品已配备的提示框
                std::string message = "has been equipped";
                CCLOG("Showing popup with message: %s", message.c_str());  // 打印弹窗消息
                auto popup = PopupLayer::create(message);
                CCLOG("Showing popup with message: %s", message.c_str());  // 打印弹窗消息
                // 确保弹窗显示在场景最上方，避免被覆盖
                auto scene = Director::getInstance()->getRunningScene();
                if (scene) {
                    scene->addChild(popup, 999);  // 确保弹窗显示在最上层
                }

                // 如果你想在弹窗显示一段时间后自动消失，可以这样做
                popup->runAction(Sequence::create(
                    DelayTime::create(2.0f),  // 弹窗显示2秒
                    RemoveSelf::create(),      // 自动移除弹窗
                    nullptr
                ));
                });
            // 将按钮添加到滚动视图中
            scrollView->addChild(itemButton);
            
            i++;
        }
    }
}






// 设置背包数据（物品）
void BackpackLayer::setBackpack(Backpack* backpack)
{
    _backpack = backpack;  // 设置背包数据
    // 更新背包 UI（例如重新绘制物品）
    createBackpackUI();
}

// 创建静态的 create 方法，简化创建对象的过程
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
