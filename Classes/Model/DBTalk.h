//
//  DBTalk.h
//  Henshin
//
//  Created by hoangdieu on 8/2/14.
//  Copyright (c) 2014 DNK. All rights reserved.
//

#ifndef __Henshin__DBTalk__
#define __Henshin__DBTalk__

class DBTalk
{
    char* table="talk";
    int uid;
    int chara_id;
    int talk_id;
    int option_id;
    int receive_time;
    int send_time;
public:
    void init(int,int,int,int,int,int);
    
    int getUid();
    int getCharaId();
    int getOptionId();
    int getReceiveTime();
    int getSendTime();
    char* tableName();
    
    bool update();
    bool getData();
    bool getDatas();
    bool delele();
    bool insert();
    
};

#endif /* defined(__Henshin__DBTalk__) */
