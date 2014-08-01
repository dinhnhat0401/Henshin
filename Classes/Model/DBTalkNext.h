//
//  DBTalkNext.h
//  Henshin
//
//  Created by hoangdieu on 8/2/14.
//  Copyright (c) 2014 DNK. All rights reserved.
//

#ifndef __Henshin__DBTalkNext__
#define __Henshin__DBTalkNext__
#include <iostream>
class DBTalkNext
{
    const std::string table="talk_next";
    int uid;
    int chara_id;
    int talk_id;
    int time;
public:
    //database
    bool update();
    bool getData();
    bool getDatas();
    bool delele();
    bool insert();
};

#endif /* defined(__Henshin__DBTalkNext__) */
