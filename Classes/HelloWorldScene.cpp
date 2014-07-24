#include "HelloWorldScene.h"
#include "TimelineScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if (!Layer::init())return false;
    
    // 画面いっぱいのサイズでテーブルを作成
    Size visibleSize = Director::getInstance()->getVisibleSize();
    TableView* tableView = TableView::create(this, visibleSize);
    
    // テーブルの方向（VERTICAL->縦方向）
    tableView->setDirection(TableView::Direction::VERTICAL);
    
    // セルの表示順（TOP_DOWN->上から下）
    tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    
    // 表示
    tableView->setDelegate(this);
    addChild(tableView);
    tableView->reloadData();
    
    return true;
}

Size HelloWorld::cellSizeForTable(TableView *table){
    Size visibleSize = Director::getInstance()->getVisibleSize();
    return Size(visibleSize.width, visibleSize.height*.2);
}

TableViewCell* HelloWorld::tableCellAtIndex(TableView *table, ssize_t idx){
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    TableViewCell *cell = table->dequeueCell();
    cell = new TableViewCell();
    cell->autorelease();
    
    // セルの背景
    auto bg = Sprite::create();
    bg->setAnchorPoint(Vec2(0, 0));
    bg->setTextureRect(Rect(0, 0, visibleSize.width, visibleSize.height*.2));
    bg->setColor(Color3B(230,230,230));
    cell->addChild(bg);
    
    // ボーダーライン
    auto line = Sprite::create();
    line->setAnchorPoint(Vec2(0, 0));
    line->setTextureRect(Rect(0, 0, visibleSize.width, 1));
    line->setColor(Color3B(100,100,100));
    cell->addChild(line);
    
    // テキスト
    auto text = StringUtils::format("Cell %zd", idx);
    auto label = Label::createWithSystemFont(text.c_str(), "Arial", 30);
    label->setAnchorPoint(Vec2(0, 0.5));
    label->setPosition(Vec2(visibleSize.width - 100, visibleSize.height*.1));
    label->setColor(Color3B(100,100,100));
    cell->addChild(label);
    
    auto image = Sprite::create("三輪田薫4.jpg");
    image->setScale(0.15);
    image->setAnchorPoint(Vec2(0.5, 0.5));
    image->setPosition(Vec2(50, visibleSize.height*0.1));
    cell->addChild(image);
    
    return cell;
}

ssize_t HelloWorld::numberOfCellsInTableView(TableView *table){
    return 10;
}

void HelloWorld::tableCellTouched(TableView* table, TableViewCell* cell){
    log("%zd番目がタップされました", cell->getIdx());
    auto newScene = Timeline::createScene();
    auto tran1 = TransitionMoveInR::create(0.3f, newScene);
    Director::getInstance()->replaceScene(tran1);
//    Director::getInstance()->pushScene(Timeline::createScene());
}

//void HelloWorld::menuCloseCallback(Ref* pSender)
//{
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
//	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
//    return;
//#endif
//
//    Director::getInstance()->end();
//
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    exit(0);
//#endif
//}
