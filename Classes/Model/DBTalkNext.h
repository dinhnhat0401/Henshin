//
//  DBTalkNext.h
//  Henshin
//
//  Created by hoangdieu on 8/2/14.
//  Copyright (c) 2014 DNK. All rights reserved.
//

#ifndef __Henshin__DBTalkNext__
#define __Henshin__DBTalkNext__

#include "cocos2d.h"

class DBTalkNext
{
    char* table="talk_next";
    int uid;
    int chara_id;
    int talk_id;
    int time;
public:
    void init(int,int,int,int);
    void setUid(int);
    void setCharaId(int);
    void setTalkId(int);
    void setTime(int);
    
    int getUid();
    int getCharaId();
    int getTalkId();
    int getTime();
    std::string toString(const int);
    //database
    bool update();
    bool getData();
    bool getDatas();
    bool delele();
    bool insert();
};

#endif /* defined(__Henshin__DBTalkNext__) */
