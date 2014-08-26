//
//  NotificationService.cpp
//  Henshin
//
//  Created by duong minh khoa on 8/12/14.
//  Copyright (c) 2014 DNK. All rights reserved.
//

#include "NotificationService.h"
#include "LocalNotification.h"
#include "DBLocalNotification.h"
#include "DBTalkNext.h"
#include "DBService.h"
#include "FilePlists.h"

USING_NS_CC;

typedef pair<int, int> intPair;

int NotificationService::pushNotification(int chara_id, int numberAsk,int point, int randTime)
{
    FilePlists* plist = new FilePlists();
    string fileName = "chara_talk/chara_talk_" + to_string(chara_id) + ".plist";
    plist->readFile(fileName);
    DNKCharacterInfo *info = plist->getValues();
    return pushNotification(chara_id, info, numberAsk,point, randTime);
};

int NotificationService::pushNotification(int chara_id,DNKCharacterInfo* info, int numberAsk, int point,int randTime)
{
    string message;
    string name;
    string body;
    string key;
    if (numberAsk == 10) {
        if (point >= 70) {
            body = info->getResult()->getResultAtIndex(0)->getText();
        } else {
            body = info->getResult()->getResultAtIndex(1)->getText();
        }
    } else {
        body = info->getTalk()->getItem(numberAsk)->getQuestion();
    }
    name = info->getNickName();
    key  = StringUtils::format("chara_%d",chara_id);
    
    if (body == "")
    {
        return 0;
    }
    message = name + "：" + body;
    
    long int t = static_cast<long int>(time(NULL));
    LocalNotification::show(message,randTime,chara_id);
    
    DBLocalNotification* notify = new DBLocalNotification();
    notify->init(chara_id, key, message, t+randTime);
    bool update = notify->insert();
    
    DBTalkNext* next = new DBTalkNext();
    next->init(0, chara_id, numberAsk, t+randTime);
    next->insert();
    
    DBService::insertTalkHistory(chara_id, 0, numberAsk, 0,t+randTime);
    int nextTime = t+randTime;
    return nextTime;
};

void NotificationService::makeCharaNotification(bool swx)
{
    map<int,int> list = initWomanList();
    for(auto p = list.begin(); p != list.end(); p ++)
    {
        int chara_id    = p->first;
        int time_plus   = p->second;
        pushNotification(chara_id, 0,0,time_plus);
    }
};
map<int,int> NotificationService::initWomanList()
{
    map<int,int> list ;
        list.insert(intPair(11,0));
        list.insert(intPair(12,60));
        list.insert(intPair(13,65));
        list.insert(intPair(14,70));
        list.insert(intPair(15,60*5));
        list.insert(intPair(16,60*7));
        list.insert(intPair(18,30));
        list.insert(intPair(19,60*60));
        list.insert(intPair(20,60*60*2));
        list.insert(intPair(22,60*60* 5));
        list.insert(intPair(23,60*60*10));
        list.insert(intPair(24,60*60*24));
        list.insert(intPair(30,60*60*25));
        list.insert(intPair(31,60*60*30));
        list.insert(intPair(32,60*60*40));
        list.insert(intPair(35,60*60*45));
        list.insert(intPair(36,60*60*48));
    return list;
    
};

map<int,int> NotificationService::initManList()
{
    
};
