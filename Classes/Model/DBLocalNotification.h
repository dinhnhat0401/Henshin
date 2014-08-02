//
//  DBLocalNotification.h
//  Henshin
//
//  Created by hoangdieu on 8/2/14.
//  Copyright (c) 2014 DNK. All rights reserved.
//

#ifndef __Henshin__DBLocalNotification__
#define __Henshin__DBLocalNotification__

class DBLocalNotification
{
    char* table="local_notification";
    int chara_id;
    int key;
    int body;
    int time;
public:
    void init(int,int,int,int);
    void setCharaId(int);
    void setKey(int);
    void setBody(int);
    void setTime(int);
    
    int getCharaId();
    int getKey();
    int getBody();
    int getTime();
    
    //database
    bool update();
    bool getData();
    bool getDatas();
    bool delele();
    bool insert();
};
#endif /* defined(__Henshin__DBLocalNotification__) */
