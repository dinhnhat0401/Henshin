//
//  DBTutorialInfor.cpp
//  Henshin
//
//  Created by hoangdieu on 8/2/14.
//  Copyright (c) 2014 DNK. All rights reserved.
//

#include "DBTutorialInfor.h"
#include "DBConnect.h"
USING_NS_CC;

void DBTutorialInfor::init(int tutorial_id, int is_read)
{
    this->tutorial_id = tutorial_id;
    this->is_read = is_read;
}

int DBTutorialInfor::getTutorialId()
{
    return this->tutorial_id;
}

int DBTutorialInfor::isRead()
{
    return this->is_read;
}

///database
bool DBTutorialInfor::update()
{
    char *str;
    
    std::string query = "UPDATE tutorial_info SET is_read="+this->toString(this->is_read)+" WHERE tutorial_id="+this->toString(this->tutorial_id);
    
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

bool DBTutorialInfor::insert()
{
    char *str;
    
    std::string query = "INSERT INTO tutorial_info(tutorial_info) VALUES("+this->toString(this->tutorial_id)+","+this->toString(this->is_read)+")";
    
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
bool DBTutorialInfor::delele()
{
    char *str;
    
    std::string query ="DELETE FROM local_notification WHERE tutorial_id="+this->toString(this->tutorial_id);
    
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

std::string DBTutorialInfor::toString(const int value)
{
    std::ostringstream oss;
    oss << value;
    return oss.str();
}