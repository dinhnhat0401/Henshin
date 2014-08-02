//
//  DBConnect.h
//  Henshin
//
//  Created by hoangdieu on 8/2/14.
//  Copyright (c) 2014 DNK. All rights reserved.
//

#ifndef __Henshin__DBConnect__
#define __Henshin__DBConnect__

#include "cocos2d.h"
#include "sqlite3.h"


class DBConnect
{
    //database
    const std::string dbfile="henshin.db";
    //db
    sqlite3 *pdb=NULL;
    //data

    ///variable
    char **data;
    int row;
    int column;
public:
    //function
    bool getConnect();
    void freeTable();
    void closeDB();
    //insert,create table,delete,drop,alter...
    bool executeCommand(char *);
    //select
    void getData(char *);
    char* getDataIndex(int,int);
    int getRow();
    int getColumn();
    ///insert table
//    bool insert(cocos2d::CCDictionary *,std::string);
};

#endif /* defined(__Henshin__DBConnect__) */
