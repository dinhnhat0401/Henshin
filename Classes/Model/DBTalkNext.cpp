//
//  DBTalkNext.cpp
//  Henshin
//
//  Created by hoangdieu on 8/2/14.
//  Copyright (c) 2014 DNK. All rights reserved.
//

#include "DBTalkNext.h"

void DBTalkNext::init(int uid, int chara_id, int talk_id, int time)
{
    this->uid = uid;
    this->chara_id = chara_id;
    this->talk_id = talk_id;
    this->time = time;
}
int DBTalkNext::getUid()
{
    return this->uid;
}
int DBTalkNext::getCharaId()
{
    return this->chara_id;
}
int DBTalkNext::getTalkId()
{
    return this->talk_id;
}
int DBTalkNext::getTime()
{
    return this->time;
}