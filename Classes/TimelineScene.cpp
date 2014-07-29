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
#include "DNKMyChatTableViewCell.h"
#include "FilePlists.h"
#include "DNKCommon.h"

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
    for(int i=0; i< 10; i++){
        selected[i] = -1;
    }
    // get from databse what use choiced
    selected[0] = 1;
    selected[1] = 2;
    selected[2] = 0;
    
    numberAnswered = 3;
    
    DNKOption* option = new DNKOption();
    DNKSelection *selections = new DNKSelection[3]();
    
    for (int i=0; i<3; i++) {
        DNKSelection* selection = new DNKSelection();
        selection->initSelection(100, "cu lac", false);
        selections[i] = *selection;
    }
    
    option->initOption(selections);
    DNKItem* item = new DNKItem();
    item->init(10, "cai nay la cai eo gi cai eo gi the asdf lasdf asdf", option);
    DNKItem *items = new DNKItem[10]();
    for (int i=0; i<10; i++) {
        items[i] = *item;
    }
    
    DNKTalk* talk = new DNKTalk();
    talk->init(items);
    
    info = new DNKCharacterInfo();
    info->init(19, "alo", "aa", false, "a", "a", talk);

    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    // Add backgound image
    cocos2d::ui::ImageView* bgImage = cocos2d::ui::ImageView::create("bg_0.jpg");
    bgImage->setAnchorPoint(Vec2(0, 0));
    bgImage->setPosition(Vec2(0, 0));
    this->addChild(bgImage);
    
    // Add tableview
    TableView* talkDetail = TableView::create(this, Size(visibleSize.width, visibleSize.height - 90));
    talkDetail->setDirection(TableView::Direction::VERTICAL);
    talkDetail->setBounceable(true);

    talkDetail->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
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
    
    
//    FilePlists *plist = new FilePlists();
//    plist->readFile("chara_talk_7.plist");
//    DNKCharacterInfo* info = new DNKCharacterInfo();
//    info = plist->getValues();
    
    return true;
}

#pragma mark - Tableview Delegate
//Size Timeline::cellSizeForTable(TableView *table){
//    Size visibleSize = Director::getInstance()->getVisibleSize();
//    return Size(visibleSize.width, visibleSize.height*.2);
//}
Size Timeline::tableCellSizeForIndex(TableView *table, ssize_t idx){

    float height;
    int row = (int)idx/2;
    if(idx%2==0){ // this is a question asked by machine
        string question = info->getTalk()->getItem(row)->getQuestion();
        height = DNKCommon::calculateHeightOfTalkCell(question, 30, 300);
    } else {      // this is an answer from user
        DNKSelection selection = info->getTalk()->getItem(row)->getOptions()->getSelection(selected[row]);
        height = DNKCommon::calculateHeightOfTalkCell(selection.getAnswer(), 30, 300);
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Size cellSize = Size(visibleSize.width, height);
    return cellSize;
}

ssize_t Timeline::numberOfCellsInTableView(TableView *table){
    int i = 0;
    for (i=0; i<10; i++) {
        if (selected[i] == -1) {
            break;
        }
    }
    return i + numberAnswered;
}

TableViewCell* Timeline::tableCellAtIndex(TableView* table, ssize_t idx){
    if(idx%2 == 0){
        DNKFriendChatTableViewCell *cell = (DNKFriendChatTableViewCell*)table->dequeueCell();
        cell = new DNKFriendChatTableViewCell();
        cell->initCell(info->getTalk()->getItem(0));
        cell->autorelease();
        return cell;
    }
    else {
        DNKMyChatTableViewCell *cell = (DNKMyChatTableViewCell*)table->dequeueCell();
        cell = new DNKMyChatTableViewCell();
        int row = (int)idx/2;
        DNKSelection selection = info->getTalk()->getItem(row)->getOptions()->getSelection(selected[row]);
        cell->initCell(selection);
        cell->autorelease();
        return cell;
    }
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