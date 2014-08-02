
//
//  DBTalkHistory.cpp
//  Henshin
//
//  Created by hoangdieu on 8/2/14.
//  Copyright (c) 2014 DNK. All rights reserved.
//

#include "DBTalkHistory.h"
#include "DBConnect.h"
USING_NS_CC;
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

///database
bool DBTalkHistory::update()
{
    char *str;
    
    std::string query = "UPDATE talk_history SET is_self="+this->toString(this->is_self)+",is_result="+this->toString(this->is_result)+",time="+this->toString(this->time)+" WHERE chara_id="+this->toString(this->chara_id)+" and talk_id="+this->toString(this->talk_id)+" and option_id="+this->toString(this->option_id)+" and result_id="+this->toString(this->result_id);
    
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

bool DBTalkHistory::insert()
{
    char *str;
    
    std::string query = "INSERT INTO talk_history(chara_id,is_self,is_result,talk_id,option_id,result_id,time) VALUES("+this->toString(this->chara_id)+","+this->toString(this->is_self)+","+this->toString(this->is_result)+","+this->toString(this->talk_id)+","+this->toString(this->option_id)+","+this->toString(this->result_id)+","+this->toString(this->time)+")";
    
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
bool DBTalkHistory::delele()
{
    char *str;
    
    std::string query ="DELETE FROM talk_history WHERE chara_id="+this->toString(this->chara_id)+" and talk_id="+this->toString(this->talk_id)+" and option_id="+this->toString(this->option_id)+" and result_id="+this->toString(this->result_id);
    
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

std::string DBTalkHistory::toString(const int value)
{
    std::ostringstream oss;
    oss << value;
    return oss.str();
}
