//
//  DBChara.cpp
//  Henshin
//
//  Created by hoangdieu on 8/2/14.
//  Copyright (c) 2014 DNK. All rights reserved.
//

#include "DBChara.h"
USING_NS_CC;
void DBChara::init(int chara_id,int unread,int point,int is_talk_end,int is_recieve_result,int is_send_result,int is_keep,int time,int best_point,int is_add_keep,int is_start,int talk_end_time,int result_time,int is_show_profile)
{
    this->chara_id = chara_id;
    this->unread = unread;
    this->point = point;
    this->is_talk_end = is_talk_end;
    this->is_recieve_result = is_recieve_result;
    this->is_send_result = is_send_result;
    this->is_keep = is_keep;
    this->time = time;
    this->best_point = best_point;
    this->is_add_keep= is_add_keep;
    this->is_start = is_start;
    this->talk_end_time = talk_end_time;
    this->result_time = result_time;
    this->is_show_profile = is_show_profile;
}

int DBChara::getCharaId()
{
    return this->chara_id;
}
int DBChara::getUnRead()
{
    return this->unread;
}
int DBChara::getPoint()
{
    return this->point;
}
int DBChara::isTalkEnd()
{
    return this->talk_end_time;
}
int DBChara::isReceiveResult()
{
    return this->result_time;
}
int DBChara::isSendResult()
{
    return this->is_send_result;
}
int DBChara::isKeep()
{
    return this->is_keep;
}
int DBChara::getTime()
{
    return this->time;
}
int DBChara::getBestPoint()
{
    return this->best_point;
}
int DBChara::isAddKeep()
{
    return this->is_add_keep;
}
int DBChara::isStart()
{
    return this->is_start;
}
int DBChara::getTalkEndTime()
{
    return this->talk_end_time;
}
int DBChara::getResultTime()
{
    return this->result_time;
}
int DBChara::isShowProfile()
{
    return this->is_show_profile;
}

void DBChara::setPoint(int p)
{
    this->point = p;
}
///database
bool DBChara::update()
{
    char *str;
    
    std::string query = "UPDATE chara SET unread="+this->toString(this->unread)+",point="+this->toString(this->point)+",is_talk_end="+this->toString(this->is_talk_end)+",is_recieve_result="+this->toString(this->is_recieve_result)+",is_send_result="+this->toString(this->is_send_result)+",is_keep="+this->toString(this->is_keep)+",time="+this->toString(this->time)+",best_point="+this->toString(this->best_point)+",is_add_keep="+this->toString(this->is_add_keep)+",is_start="+this->toString(this->is_start)+",talk_end_time="+this->toString(this->talk_end_time)+",result_time="+this->toString(this->result_time)+",is_show_profile="+this->toString(this->is_show_profile)+" WHERE chara_id="+this->toString(this->chara_id);
    
    str =(char *) query.c_str();
    log("Query:%s",str);
    DBConnect *dbCon = new DBConnect();
    if(!dbCon->getConnect())
    {
        log("coud not connect!");
        return false;
    }
    int rs =dbCon->executeCommand(str);
    if(rs != SQLITE_OK)
        return false;
    dbCon->freeTable();
    dbCon->closeDB();
    return true;
}

bool DBChara::insert()
{
    char *str;
    
    std::string query = "INSERT INTO chara(chara_id,unread,point,is_talk_end,is_recieve_result,is_send_result,is_keep,time, best_point,is_add_keep,is_start,talk_end_time,result_time,is_show_profile) VALUES("+this->toString(this->chara_id)+","+this->toString(this->unread)+","+this->toString(this->point)+","+this->toString(this->is_talk_end)+","+this->toString(this->is_recieve_result)+","+this->toString(this->is_send_result)+","+this->toString(this->is_keep)+","+this->toString(this->time)+","+this->toString(this->best_point)+","+this->toString(this->is_add_keep)+","+this->toString(this->is_start)+","+this->toString(this->talk_end_time)+","+this->toString(this->result_time)+","+this->toString(this->is_show_profile)+")";
    
    str =(char *) query.c_str();
    log("Query:%s",str);
    DBConnect *dbCon = new DBConnect();
    if(!dbCon->getConnect())
    {
        log("coud not connect!");
        return false;
    }
    int rs =dbCon->executeCommand(str);
    if(rs != SQLITE_OK)
        return false;
    dbCon->freeTable();
    dbCon->closeDB();
    return true;
}
bool DBChara::delele()
{
    char *str;
    
    std::string query ="DELETE FROM talk WHERE chara_id="+this->toString(this->chara_id);
    
    str =(char *) query.c_str();
    log("Query:%s",str);
    DBConnect *dbCon = new DBConnect();
    if(!dbCon->getConnect())
    {
        log("coud not connect!");
        return false;
    }
    int rs =dbCon->executeCommand(str);
    if(rs != SQLITE_OK)
        return false;
    dbCon->freeTable();
    dbCon->closeDB();
    return true;
    
}

std::string DBChara::toString(const int value)
{
    std::ostringstream oss;
    oss << value;
    return oss.str();
}