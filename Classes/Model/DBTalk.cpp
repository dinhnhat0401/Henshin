//
//  DBTalk.cpp
//  Henshin
//
//  Created by hoangdieu on 8/2/14.
//  Copyright (c) 2014 DNK. All rights reserved.
//

#include "DBTalk.h"
#include <iostream>

#define _(x) #x;
USING_NS_CC;
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


///database
bool DBTalk::update()
{
    char *str;
    
    std::string query = "UPDATE talk SET chara_id="+this->toString(this->chara_id)+",option_id="+this->toString(this->option_id)+",talk_id="+this->toString(this->talk_id)+",receive_time="+this->toString(this->receive_time)+",send_time="+this->toString(this->send_time)+" WHERE uid="+this->toString(this->uid);

    str =(char *) query.c_str();

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

bool DBTalk::insert()
{
    char *str;
    
    std::string query = "INSERT INTO talk(uid,chara_id,talk_id,option_id,receive_time,send_time) VALUES("+this->toString(this->uid)+","+this->toString(this->chara_id)+","+this->toString(this->option_id)+","+this->toString(this->talk_id)+","+this->toString(this->receive_time)+","+this->toString(this->send_time)+")";
    
    str =(char *) query.c_str();
    log(str);
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
bool DBTalk::delele()
{
    char *str;
    
    std::string query ="DELETE FROM talk WHERE uid="+this->toString(this->uid);
    
    str =(char *) query.c_str();
    
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
std::string DBTalk::toString(const int value)
{
    std::ostringstream oss;
    oss << value;
    return oss.str();
}
 