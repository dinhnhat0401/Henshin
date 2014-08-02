//
//  DBLocalNotification.h
//  Henshin
//
//  Created by hoangdieu on 8/2/14.
//  Copyright (c) 2014 DNK. All rights reserved.
//

#ifndef __Henshin__DBLocalNotification__
#define __Henshin__DBLocalNotification__

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
    
    //database
    bool update();
    bool getData();
    bool getDatas();
    bool delele();
    bool insert();
};
#endif /* defined(__Henshin__DBLocalNotification__) */
