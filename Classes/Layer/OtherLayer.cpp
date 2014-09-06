//
//  OtherLayer.cpp
//  Henshin
//
//  Created by duong minh khoa on 7/30/14.
//  Copyright (c) 2014 (THE) ONE of THEM. All rights reserved.
//

#include "OtherLayer.h"

void Other::initTableView(Size size)
{
    tbv = TableView::create(this, size);
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    tbv->setPosition(0,visibleSize.height/2 - size.height/2);
    tbv->setVerticalFillOrder(TableView::VerticalFillOrder::BOTTOM_UP);
    tbv->setDirection(TableView::Direction::VERTICAL);
    tbv->setBounceable(false);
    tbv->setDelegate(this);
    
    this->addChild(tbv);
};

Size Other::cellSizeForTable(TableView *table){
    Size visibleSize = Director::getInstance()->getVisibleSize();
    return Size(visibleSize.width, visibleSize.height* ConstValue::TIME_LINE_ITEM_RATE);
};

TableViewCell* Other::tableCellAtIndex(TableView *table, ssize_t idx){
    TimeLineCell* cell = (TimeLineCell*)table->dequeueCell();
    cell = new TimeLineCell();
    TimeLineItem * item = listItem[idx];
    cell->init(item);
    cell->setIdx(idx);
    cell->autorelease();
    return cell;
}

ssize_t Other::numberOfCellsInTableView(TableView *table){
    return listItem.size();
}


void  Other::tableCellTouched(TableView* table, TableViewCell* cell){
    printf("%zd番目がタップされました", cell->getIdx());
    TimeLineItem* item = listItem[cell->getIdx()];
    MainApp * mApp = MainApp::getInstance();
    mApp->setCurrentChara(item->getCharaId());
    mApp->changeState(ConstValue::STATE_TALK_DETAIL);
}