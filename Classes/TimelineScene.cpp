//
//  TimelineScene.cpp
//  Henshin
//
//  Created by Đinh Văn Nhật on 2014/07/24.
//
//
#include "HelloWorldScene.h"
#include "TimelineScene.h"
#include <UIButton.h>
#include <UIImageView.h>
#include <UIText.h>
#include <string.h>
#include "Model.h"
#include "DNKFriendChatTableViewCell.h"

USING_NS_CC;

Scene* Timeline::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Timeline::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool Timeline::init()
{
    if (!Layer::init())return false;
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    // Add tableview
    TableView* talkDetail = TableView::create(this, Size(visibleSize.width, visibleSize.height - 100));
    talkDetail->setDirection(TableView::Direction::VERTICAL);
    talkDetail->setBounceable(true);
//    talkDetail->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    talkDetail->setDelegate(this);
    addChild(talkDetail);
    talkDetail->reloadData();
    
    // Add header image
    cocos2d::ui::ImageView* imageView = cocos2d::ui::ImageView::create("bg_header.png");
    imageView->setAnchorPoint(Vec2(0, 0));
    imageView->setPosition(Vec2(0, visibleSize.height - imageView->getContentSize().height));
    this->addChild(imageView);

    //create back button
    cocos2d::ui::Button* backButton = cocos2d::ui::Button::create();
    backButton->loadTextures("btn_back.png", "btn_back_r.png", "");
    backButton->setAnchorPoint(Vec2(0, 0));
    backButton->setPosition(Point(0, visibleSize.height - backButton->getContentSize().height - 10));
    backButton->setTouchEnabled(true);
    backButton->addTouchEventListener(CC_CALLBACK_1(Timeline::menuCloseCallback, this));
    this->addChild(backButton);
    
    // add Title (screen name)
    std::string str = "五十嵐信介あろほほほaaaaaaaaaaaa";
    #pragma GCC diagnostic ignored "-Wdeprecated-declarations"
    CCLabelTTF* lbl = CCLabelTTF::create(str, "MSGothic", 34);
    lbl->setPosition(Vec2(130, visibleSize.height - 60));
    lbl->setAnchorPoint(Vec2(0, 0));
    lbl->setDimensions(Size(visibleSize.width - 130 * 2, 40));
    this->addChild(lbl);

    // Add heart image
    cocos2d::ui::ImageView* heart = cocos2d::ui::ImageView::create("heart_off.png");
    heart->setAnchorPoint(Vec2(0, 0));
    heart->setPosition(Vec2(visibleSize.width - 125, visibleSize.height - heart->getContentSize().height - 15));
    this->addChild(heart);
//    
//    Model* m = new Model();
//    
//    m->set_values(10, 10);
//    log("%d %d", m->get_Width(), m->get_Height());
    
    return true;
}

#pragma mark - Tableview Delegate
Size Timeline::cellSizeForTable(TableView *table){
    Size visibleSize = Director::getInstance()->getVisibleSize();
    return Size(visibleSize.width, visibleSize.height*.2);
}

ssize_t Timeline::numberOfCellsInTableView(TableView *table){
    return 10;
}

TableViewCell* Timeline::tableCellAtIndex(TableView* table, ssize_t idx){
    
    DNKFriendChatTableViewCell *cell = (DNKFriendChatTableViewCell*)table->dequeueCell();
    cell = new DNKFriendChatTableViewCell();
    
    DNKCharacterInfo *info = new DNKCharacterInfo();
    info->init(19, "alo", "aa", false, "a", "a");
    
    cell->initCell(info);
    cell->autorelease();
    return cell;
}

void Timeline::tableCellTouched(TableView* table, TableViewCell* cell){
    log("%zd番目がタップされました", cell->getIdx());
//    auto newScene = Timeline::createScene();
//    auto tran1 = TransitionMoveInR::create(0.3f, newScene);
//    Director::getInstance()->replaceScene(tran1);
    //    Director::getInstance()->pushScene(Timeline::createScene());
}

#pragma mark - private function
void Timeline::menuCloseCallback(Ref* pSender)
{
    log("back press");
//    Director::getInstance()->popScene();
    auto newScene = HelloWorld::createScene();
    auto tran1 = TransitionMoveInL::create(0.3f, newScene);
    Director::getInstance()->replaceScene(tran1);
}