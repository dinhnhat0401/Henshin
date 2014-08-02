
//
//  DBTalkHistory.cpp
//  Henshin
//
//  Created by hoangdieu on 8/2/14.
//  Copyright (c) 2014 DNK. All rights reserved.
//

#include "DBTalkHistory.h"

void DBTalkHistory::init(int chara_id, int is_self, int is_result, int talk_id, int option_id, int result_id, int time)
{
    this->chara_id = chara_id;
    this->is_self = is_self;
    this->is_result = is_result;
    this->talk_id = talk_id;
    this->option_id = option_id;
    this->result_id = result_id;
    this->time = time;
}

int DBTalkHistory::getCharaId()
{
    return this->chara_id;
}
int DBTalkHistory::getIsSelf()
{
    return this->is_self;
}
int DBTalkHistory::getIsResult()
{
    return this->is_result;
}
int DBTalkHistory::getTalkId()
{
    return this->talk_id;
}
int DBTalkHistory::getOptionId()
{
    return this->option_id;
}
int DBTalkHistory::getResultId()
{
    return  this->result_id;
}
int DBTalkHistory::getTime()
{
    return this->time;
}