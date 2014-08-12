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

USING_NS_CC;

int NotificationService::pushNotification(int chara_id,DNKCharacterInfo* info, int numberAsk)
{
    string message;
    string name;
    string body;
    string key;
    body = info->getTalk()->getItem(numberAsk)->getQuestion();
    name = info->getNickName();
    key  = StringUtils::format("chara_%d",chara_id);
    
    if (body == "")
    {
        return 0;
    }
    message = name + "：" + body;
    
    int randTime    = rand() % 100 + 10;
    long int t = static_cast<long int>(time(NULL));
    LocalNotification::show(message,randTime,1);
    
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