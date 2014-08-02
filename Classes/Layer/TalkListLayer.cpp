//
//  TalkListLayer.cpp
//  Henshin
//
//  Created by duong minh khoa on 7/30/14.
//  Copyright (c) 2014 (THE) ONE of THEM. All rights reserved.
//

#include "TalkListLayer.h"
#include "TimeLineTableViewCell.h"

USING_NS_CC;

bool TalkList::init()
{
    if(!Layer::init()) return false;
    auto label = cocos2d::Label::createWithSystemFont("Talk Layer", "Arial", 35);
//    label->setPosition(0,0);
//    this->addChild(label);
    
    // create table view
    
    
    
    return true;
};

void TalkList::initTableView(Size size)
{
    TableView* tableView = TableView::create(this, size);
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    tableView->setPosition(0,visibleSize.height/2 - size.height/2);
    tableView->setBounceable(false);
    this->addChild(tableView);
};

Size TalkList::cellSizeForTable(TableView *table){
    Size visibleSize = Director::getInstance()->getVisibleSize();
    return Size(visibleSize.width, visibleSize.height* ConstValue::TIME_LINE_ITEM_RATE);
};

TableViewCell* TalkList::tableCellAtIndex(TableView *table, ssize_t idx){
    TimeLineCell* cell = (TimeLineCell*)table->dequeueCell();
    cell = new TimeLineCell();
    cell->init(new TimeLineItem());
    cell->autorelease();
    return cell;
}

ssize_t TalkList::numberOfCellsInTableView(TableView *table){
    return 10;
}

void  TalkList::tableCellTouched(TableView* table, TableViewCell* cell){
    log("%zd番目がタップされました", cell->getIdx());
//    auto newScene = Timeline::createScene();
//    auto tran1 = TransitionMoveInR::create(0.3f, newScene);
//    Director::getInstance()->replaceScene(tran1);
    //    Director::getInstance()->pushScene(Timeline::createScene());
}

