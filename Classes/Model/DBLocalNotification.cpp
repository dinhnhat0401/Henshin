//
//  DBLocalNotification.cpp
//  Henshin
//
//  Created by hoangdieu on 8/2/14.
//  Copyright (c) 2014 DNK. All rights reserved.
//

#include "DBLocalNotification.h"
#include "DBConnect.h"
USING_NS_CC;


void DBLocalNotification::init(int chara_id, string key,string body,int time)
{
    this->chara_id = chara_id;
    this->key = key;
    this->body = body;
    this->time = time;
}
void DBLocalNotification::setBody(string body)
{
    this->body = body;
}
void DBLocalNotification::setCharaId(int chara_id)
{
    this->chara_id = chara_id;
}
void DBLocalNotification::setKey( string key)
{
    this->key = key;
}

void DBLocalNotification::setTime(int time)
{
    this->time = time;
}

////////////////////get
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


///database
bool DBLocalNotification::update()
{
    char *str;
    
    std::string query = "UPDATE local_notification SET key="+this->key+",body="+this->body+",time="+this->toString(this->time)+" WHERE chara_id="+this->toString(this->chara_id);
    
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

bool DBLocalNotification::insert()
{
    char *str;
    
    std::string query = "INSERT INTO local_notification(chara_id,key,body,time) VALUES("+this->toString(this->chara_id)+","+this->key+","+this->body+",="+this->toString(this->time)+")";
    
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
bool DBLocalNotification::delele()
{
    char *str;
    
    std::string query ="DELETE FROM local_notification WHERE chara_id="+this->toString(this->chara_id);
    
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

std::string DBLocalNotification::toString(const int value)
{
    std::ostringstream oss;
    oss << value;
    return oss.str();
}