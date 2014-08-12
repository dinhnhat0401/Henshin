//
//  DBService.cpp
//  Henshin
//
//  Created by duong minh khoa on 8/12/14.
//  Copyright (c) 2014 DNK. All rights reserved.
//

#include "DBService.h"
#include "DBTalkHistory.h"

void DBService::insertTalkHistory(int chara_id, int is_self,int talk_id, int option_id,int t = 0)
{
    DBTalkHistory * history = new DBTalkHistory();
    history->init(chara_id,is_self,0,talk_id,option_id,0,t);
    history->insert();

};

void DBService::insertTalkHistory(int chara_id, int is_self,int talk_id, int option_id)
{
    long int t = static_cast<long int>(time(NULL));
    insertTalkHistory(chara_id, is_self, talk_id, option_id,t);
}
