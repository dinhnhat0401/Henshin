//
//  DBConnect.cpp
//  Henshin
//
//  Created by hoangdieu on 8/2/14.
//  Copyright (c) 2014 DNK. All rights reserved.
//

#include "DBConnect.h"
USING_NS_CC;

bool DBConnect::getConnect()
{
    std::string path = cocos2d::CCFileUtils::sharedFileUtils()->fullPathForFilename(this->dbfile);
    
    
    std::string sql;
    int result;
    result=sqlite3_open(path.c_str(),&this->pdb);
    if(result!=SQLITE_OK)
        return false;
    return true;
}

bool DBConnect::executeCommand(char *query)
{
    int result=sqlite3_exec(this->pdb, "", NULL, NULL, NULL);
    if(result!=SQLITE_OK)
        return false;
    return true;
}

//get data
void DBConnect::getData(char *query)
{
    int rs =sqlite3_get_table(pdb,query,&this->data,&this->row,&this->column,NULL);
    log(rs);
}
std::string DBConnect::getDataIndex(int r,int c)
{
    if(r < 0 || c < 0 || r >this->row || c > this->column)
        return "NULL";
    return (std::string)this->data[(r-1)*this->column+c];
}
void DBConnect::freeTable()
{
    sqlite3_free_table(this->data);
}
void DBConnect::closeDB()
{
    sqlite3_close(this->pdb);
}
