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
#include "MainAppScene.h"
#include "ConstantValue.h"
#include "DBChara.h"

USING_NS_CC;

bool TalkList::init()
{
    if(!Layer::init()) return false;
    auto label = cocos2d::Label::createWithSystemFont("Talk Layer", "Arial", 35);
    loadData();
    this->schedule(schedule_selector(TalkList::update),1.0);
    return true;
};

void TalkList::initTableView(Size size)
{
    tbv = TableView::create(this, size);
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    tbv->setPosition(0,visibleSize.height/2 - size.height/2);
    tbv->setBounceable(false);
    tbv->setDelegate(this);
    this->addChild(tbv);
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
    cell->setIdx(idx);
    cell->autorelease();
    return cell;
}

ssize_t TalkList::numberOfCellsInTableView(TableView *table){
    return listItem.size();
}


void  TalkList::tableCellTouched(TableView* table, TableViewCell* cell){
    printf("%zd番目がタップされました", cell->getIdx());
    TimeLineItem* item = listItem[cell->getIdx()];
    MainApp * mApp = MainApp::getInstance();
    mApp->setCurrentChara(item->getCharaId());
    mApp->changeState(ConstValue::STATE_TALK_DETAIL);
}

void TalkList::update(float d)
{
    if(nextTime > 0)
    {
        long int t = static_cast<long int>(time(NULL));
        if(t >= nextTime)
        {
            loadData();
            tbv->reloadData();
        }
    }
}

void TalkList::loadData()
{
    DBData *db = new DBData();
    long int t = static_cast<long int>(time(NULL));
    string query = StringUtils::format("select t1.* from local_notification  as t1 inner join ( select chara_id, max(time) as time from local_notification where time < %d group by chara_id) as t2 on t1.chara_id = t2.chara_id and t1.time = t2.time order by t1.time ",t);
    std::vector<DBLocalNotification*> data = db->getLocalNotifications(const_cast<char*>( query.c_str()));
    
    for(int i= 0;i< data.size(); i++)
    {
        string body = data[i]->getBody();
        string key  = data[i]->getKey();
        int time    = data[i]->getTime();
        int chara_id = data[i]->getCharaId();
        
        string pattern = "：";
        
        size_t point = body.find(pattern);
        string name = body.substr(0,point);
        string mesg = body.substr(point).replace(0,pattern.length(),"");
        
        string image = StringUtils::format("res/chara/%d/icon.png",chara_id);
        
        if(chara_id != NULL)
        {
            // get read status
            string condition = StringUtils::format(" chara_id = %d limit 1",chara_id);
            DBChara* chara = db->getChara(const_cast<char*> (condition.c_str()));
            
            if(chara != nullptr)
            {
                TimeLineItem* item = new TimeLineItem();
                bool isUnread = (chara->getUnRead() != 0) ? true : false;
                item->init(chara_id,image,name,mesg,time,isUnread);
                listItem.push_back(item);
            }
            
        }
        
        
    }
    nextTime = db->getNextTimeLine(t);
}


