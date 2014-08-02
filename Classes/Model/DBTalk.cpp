//
//  DBTalk.cpp
//  Henshin
//
//  Created by hoangdieu on 8/2/14.
//  Copyright (c) 2014 DNK. All rights reserved.
//

#include "DBTalk.h"


char* DBTalk::tableName()
{
    return this->table;
}

void DBTalk::init(int uid, int chara_id, int talk_id, int option_id,int receive_time,int send_time)
{
    this->uid = uid;
    this->chara_id = chara_id;
    this->talk_id= talk_id;
    this->option_id = option_id;
    this->receive_time = receive_time;
    this->send_time = send_time;
}
int DBTalk::getUid()
{
    return this->uid;
}

int DBTalk::getCharaId()
{
    return this->chara_id;
}
int DBTalk::getOptionId()
{
    return this->option_id;
}
int DBTalk::getReceiveTime()
{
    return this->receive_time;
}
int DBTalk::getSendTime()
{
    return this->send_time;
}