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
    int result=sqlite3_exec(this->pdb, query, NULL, NULL, NULL);
    if(result!=SQLITE_OK)
        return false;
    return true;
}

//get data
void DBConnect::getData(char *query)
{
    sqlite3_get_table(pdb,query,&this->data,&this->row,&this->column,NULL);
}
char* DBConnect::getDataIndex(int r,int c)
{
    if(r < 0 || c < 0 || r > this->row || c > this->column)
        return "NULL";
    return this->data[r*this->column+c];
}

int DBConnect::getColumn()
{
    return this->column;
}

int DBConnect::getRow()
{
    return this->row;
}

void DBConnect::freeTable()
{
    sqlite3_free_table(this->data);
}
void DBConnect::closeDB()
{
    sqlite3_close(this->pdb);
}
