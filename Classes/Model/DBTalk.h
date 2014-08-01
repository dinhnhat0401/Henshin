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
    int uid;
    int chara_id;
    int talk_id;
    int option_id;
    int receive_time;
    int send_time;
public:
    void init(int,int,int,int,int,int);
    void getUid();
    void getCharaId();
    void getOptionId();
    void getReceiveTime();
    void getSendTime();
    
    bool update();
    bool getData();
    bool getDatas();
    bool delele();
    bool insert();
    
};

#endif /* defined(__Henshin__DBTalk__) */
