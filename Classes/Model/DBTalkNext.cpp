//
//  DBTalkNext.cpp
//  Henshin
//
//  Created by hoangdieu on 8/2/14.
//  Copyright (c) 2014 DNK. All rights reserved.
//

#include "DBTalkNext.h"
#include "DBConnect.h"
USING_NS_CC;

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


///database
bool DBTalkNext::update()
{
    char *str;
    
    std::string query = "UPDATE talk_next SET time="+this->toString(this->time)+" WHERE chara_id="+this->toString(this->chara_id)+" and uid="+this->toString(this->uid)+" and talk_id="+this->toString(this->talk_id);
    
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

bool DBTalkNext::insert()
{
    char *str;
    
    std::string query = "INSERT INTO talk_next(uuid,chara_id,talk_id,time) VALUES("+this->toString(this->uid)+","+this->toString(this->chara_id)+this->toString(this->talk_id)+","+this->toString(this->time)+")";
    
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
bool DBTalkNext::delele()
{
    char *str;
    
    std::string query ="DELETE FROM local_notification WHERE chara_id="+this->toString(this->chara_id)+" and uid="+this->toString(this->uid)+" and talk_id="+this->toString(this->talk_id);
    
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

std::string DBTalkNext::toString(const int value)
{
    std::ostringstream oss;
    oss << value;
    return oss.str();
}