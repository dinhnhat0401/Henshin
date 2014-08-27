//
//  DBLocalNotification.h
//  Henshin
//
//  Created by hoangdieu on 8/2/14.
//  Copyright (c) 2014 DNK. All rights reserved.
//

#ifndef __Henshin__DBLocalNotification__
#define __Henshin__DBLocalNotification__
#include "cocos2d.h"

#include<iostream>

using namespace std;
class DBLocalNotification
{
private:
    char* table="local_notification";
    int chara_id;
    std::string key;
    std::string body;
    int time;
public:
    void init(int,string,string,int);
    void setCharaId(int);
    void setKey(string);
    void setBody(string);
    void setTime(int);
    
    int getCharaId();
    string getKey();
    string getBody();
    int getTime();
    
    std::string toString(const int);
    std::string toString(const long int);
    //database
    bool update();
    bool getData();
    bool getDatas();
    bool delele();
    bool insert();
    int getNotificationNotPush();
};
#endif /* defined(__Henshin__DBLocalNotification__) */
