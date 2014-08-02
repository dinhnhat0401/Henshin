//
//  DBLocalNotification.cpp
//  Henshin
//
//  Created by hoangdieu on 8/2/14.
//  Copyright (c) 2014 DNK. All rights reserved.
//

#include "DBLocalNotification.h"

void DBLocalNotification::init(int chara_id, string key,string body,int time)
{
    this->chara_id = chara_id;
    this->key = key;
    this->body = body;
    this->time = time;
}

int DBLocalNotification::getCharaId()
{
    return this->chara_id;
}
string DBLocalNotification::getKey()
{
    return this->key;
}
string DBLocalNotification::getBody()
{
    return this->body;
}
int DBLocalNotification::getTime()
{
    return this->time;
}