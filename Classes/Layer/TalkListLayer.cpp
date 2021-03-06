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
#include "DNKCommon.h"
#include "DBService.h"
#include "DNKCharacterInfo.h"
#include "DNKStoreData.h"

USING_NS_CC;

bool TalkList::init()
{
    if(!Layer::init()) return false;
    Size visibleSize = Director::getInstance()->getVisibleSize();
    auto bg = Sprite::create();
    bg->setAnchorPoint(Vec2(0, 0));
    bg->setTextureRect(Rect(0, 0, visibleSize.width, visibleSize.height));
    bg->setColor(Color3B(255,255,255));
    this->addChild(bg,0);
    
    loadData();
//    this->schedule(schedule_selector(TalkList::update),1.0);
    return true;
};

bool TalkList::sortFunc(TimeLineItem *a, TimeLineItem * b)
{
    return a->getTime() < b->getTime();
}

bool TalkList::compareFunc(TimeLineItem *a, int chara_id)
{
    return a->getCharaId() == chara_id;
}

void TalkList::initTableView(Size size)
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




void TalkList::rlData(DBTalkNext* talkNext)
{

    int chara_id = talkNext->getCharaId();
    string mesg = StoreData::GetInstance()->GetTalk(chara_id, talkNext->getTalkId(),0);
    bool inList = false;
    for(int i = 0; i < listItem.size(); i ++)
    {
        TimeLineItem * item = listItem[i];
        if(item->getCharaId() == chara_id)
        {
            inList = true;
            item->updateItem(mesg, talkNext->getTime(), true);
        }
    }
    
    if(!inList)
    {
        string image = StringUtils::format("res/chara/%d/icon.png",chara_id);
        string name = StoreData::GetInstance()->GetCharaNickName(chara_id);
        TimeLineItem* item = new TimeLineItem();
        item->init(chara_id,image,name,mesg,talkNext->getTime(),true);
        listItem.push_back(item);

    }

    sort(listItem.begin(), listItem.end(), sortFunc);
    tbv->reloadData();

}

void TalkList::loadData()
{
    DNKCommon::updateTalk(0);
    listItem.clear();
    DBData *db = new DBData();
    long int t = static_cast<long int>(time(NULL));    
    string query = StringUtils::format("select t1.* from talk_history  as t1 inner join ( select chara_id, max(time) as time from talk_history where time < %d group by chara_id) as t2 on t1.chara_id = t2.chara_id and t1.time = t2.time order by t1.time ",t);

    std::vector<DBTalkHistory*> data = db->getTalkHistorys(const_cast<char*>(query.c_str()));
    for(int i= 0;i< data.size(); i++)
    {
        int time    = data[i]->getTime();
        int chara_id = data[i]->getCharaId();
        DNKCharacterInfo * info = StoreData::GetInstance()->GetData(chara_id);
        
        
        string name = info->getNickName();
        int talk_id = data[i]->getTalkId();
        int option  = data[i]->getOptionId();
        string mesg;
        if (talk_id < 10) {
            mesg = (data[i]->getIsSelf() == 0 ) ? info->getTalk()->getItem(talk_id)->getQuestion() :
            info->getTalk()->getItem(talk_id)->getOptions()->getSelection(option).getAnswer();
        } else {
            mesg = (data[i]->getIsSelf() == 0 ) ? info->getResult()->getResultAtIndex(0)->getOption() :
            info->getResult()->getResultAtIndex(0)->getText();
        }
        
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

}


