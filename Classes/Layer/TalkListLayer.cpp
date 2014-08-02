//
//  TalkListLayer.cpp
//  Henshin
//
//  Created by duong minh khoa on 7/30/14.
//  Copyright (c) 2014 (THE) ONE of THEM. All rights reserved.
//

#include "TalkListLayer.h"
#include "TimeLineTableViewCell.h"
#include "DBLocalNotification.h"
#include "DBData.h"

USING_NS_CC;

bool TalkList::init()
{
    if(!Layer::init()) return false;
    auto label = cocos2d::Label::createWithSystemFont("Talk Layer", "Arial", 35);
    DBData *db = new DBData();
    DBLocalNotification* data = db->getLocalNotifications("1 LIMIT 30");
    
    int count = 0;
    for(int i= 0;i< sizeof(data); i++)
    {
        string body = data[i].getBody();
        string key  = data[i].getKey();
        int time    = data[i].getTime();
        int chara_id = data[i].getCharaId();
//        vector<string> arBody = split(body, ':');
        string name = "Test";
        string mesg = key;
        string image = StringUtils::format("res/chara/%d/icon.png",chara_id);
        printf("%s",body.c_str());
        printf("%s",image.c_str());
        if(chara_id != NULL)
        {
            TimeLineItem* item = new TimeLineItem();
            item->init(image,name,mesg,time,false);
            listItem.push_back(item);
        }
        
    }
    
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
    TimeLineItem * item = listItem[idx];
    cell->init(item);
    cell->autorelease();
    return cell;
}

ssize_t TalkList::numberOfCellsInTableView(TableView *table){
    return listItem.size();
}

void  TalkList::tableCellTouched(TableView* table, TableViewCell* cell){
    log("%zd番目がタップされました", cell->getIdx());
//    auto newScene = Timeline::createScene();
//    auto tran1 = TransitionMoveInR::create(0.3f, newScene);
//    Director::getInstance()->replaceScene(tran1);
    //    Director::getInstance()->pushScene(Timeline::createScene());
}


//std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
//    std::stringstream ss(s);
//    std::string item;
//    while (std::getline(ss, item, delim)) {
//        elems.push_back(item);
//    }
//    return elems;
//}
//
//
//std::vector<std::string> split(const std::string &s, char delim) {
//    std::vector<std::string> elems;
//    split(s, delim, elems);
//    return elems;
//}
//
