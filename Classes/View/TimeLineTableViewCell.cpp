//
//  TimeLineTableViewCell.cpp
//  Henshin
//
//  Created by duong minh khoa on 8/1/14.
//  Copyright (c) 2014 DNK. All rights reserved.
//

#include "TimeLineTableViewCell.h"
#include "Time.h"
USING_NS_CC;

TimeLineCell* TimeLineCell::init(TimeLineItem* item)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();

//    this->autorelease();
    
    // セルの背景
    auto bg = Sprite::create();
    bg->setAnchorPoint(Vec2(0, 0));
    bg->setTextureRect(Rect(0, 0, visibleSize.width, visibleSize.height*ConstValue::TIME_LINE_ITEM_RATE));
    bg->setColor(Color3B(255,255,255));
    this->addChild(bg);
    
    // ボーダーライン
    auto line = Sprite::create();
    line->setAnchorPoint(Vec2(0, 0));
    line->setTextureRect(Rect(0, 0, visibleSize.width, 1));
    line->setColor(Color3B(100,100,100));
    this->addChild(line);
    
   
    printf("%s\n",item->getImage().c_str());
    
    auto image = Sprite::create("res/chara/11/icon.png");
    image->setAnchorPoint(Vec2(0.5, 0.5));
    image->setPosition(Vec2(60, visibleSize.height* ConstValue::TIME_LINE_ITEM_RATE/2));
    this->addChild(image,2);
    
    auto image_r = Sprite::create("res/common/icon_r.png");
    image_r->setAnchorPoint(Vec2(0.5, 0.5));
    image_r->setPosition(Vec2(60, visibleSize.height* ConstValue::TIME_LINE_ITEM_RATE/2));
    if(item->getStatus())
    {
        this->addChild(image_r,4);
    }
    
    
    auto icon_new = Sprite::create("res/talk/icon_new.png");
    icon_new->setAnchorPoint(Vec2(0.5, 0.5));
    icon_new->setPosition(Vec2(visibleSize.width - 30 - icon_new->getContentSize().width/2, visibleSize.height* ConstValue::TIME_LINE_ITEM_RATE/2 - 20));
    this->addChild(icon_new,4);
    
    // テキスト
    auto textName = item->getCharaName();
    auto labelName = Label::createWithSystemFont(textName, "Helvetica-Bold", 30);
    labelName->setAnchorPoint(Vec2(0, 0.5));
    labelName->setPosition(Vec2(10 + image->getPosition().x + image->getContentSize().width/2, visibleSize.height*ConstValue::TIME_LINE_ITEM_RATE-40));
    labelName->setColor(Color3B(0,0,0));
    this->addChild(labelName);
    
    
    std::string textMsg = item->getMessage();
//    
//    std::string sub = (textMsg.size() >= ConstValue::MEASSAGE_LIMIT) ? textMsg.substr(0,ConstValue::MEASSAGE_LIMIT) :textMsg ;
    auto labelMsg = Label::createWithSystemFont(textMsg, "Helvetica-Bold", 22);
    labelMsg->setAnchorPoint(Vec2(0, 0.5));
    labelMsg->setWidth(400);
    labelMsg->setHeight(50);
    labelMsg->setPosition(Vec2(10+image->getPosition().x + image->getContentSize().width/2, visibleSize.height*ConstValue::TIME_LINE_ITEM_RATE-100));
    labelMsg->setColor(Color3B(100,100,100));
    this->addChild(labelMsg);
    
    
    std::string msgTime = getTime(item->getTime());
    auto labelTime = Label::createWithSystemFont(msgTime, "Helvetica-Bold", 18);
    labelTime->setPosition(Vec2(visibleSize.width - 30 - icon_new->getContentSize().width/2, visibleSize.height* ConstValue::TIME_LINE_ITEM_RATE/2 + 30));
    labelTime->setColor(Color3B(100,100,100));
    this->addChild(labelTime);
    
    return this;
};

std::string TimeLineCell::getTime(int _time)
{
    
    time_t now;
    time(&now);
    
    struct tm * tm_now;

    
    tm_now = localtime(&now);
    
   
    
    std::string week[] = {"日曜日","月曜日","火曜日","水曜日","木曜日","金曜日","土曜日"};
    std::string timeStr;
    int currentDay = tm_now->tm_mday;
    int currentMon = tm_now->tm_mon;
    
    time_t messageTime = (time_t)_time;
    
    struct tm * tm_msg;
    
    tm_msg = localtime(&messageTime);
    
    int dateDiff = currentDay - tm_msg->tm_mday;
    
    if(dateDiff >=7 || (currentMon > tm_msg->tm_mon))
    {
        timeStr = StringUtils::format("%d/%d",tm_msg->tm_mon+1,tm_msg->tm_mday);
        return timeStr;
    }
    else if(dateDiff < 7 && dateDiff > 1)
    {
        timeStr = week[tm_msg->tm_wday];

    }
    else if(dateDiff == 1)
    {
        timeStr = "昨日";
    }
    else
    {
        timeStr = StringUtils::format("%d:%d",tm_msg->tm_hour,tm_msg->tm_min);
    }
    return timeStr;
//    if(messageTime.)
    
}

