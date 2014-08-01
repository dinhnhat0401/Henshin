//
//  DBTalkHistory.h
//  Henshin
//
//  Created by hoangdieu on 8/2/14.
//  Copyright (c) 2014 DNK. All rights reserved.
//

#ifndef __Henshin__DBTalkHistory__
#define __Henshin__DBTalkHistory__

class DBHistory
{
    int chara_id;
    int is_seft;
    int is_result;
    int talk_id;
    int option_id;
    int result_id;
    int time;
public:
    
    //database
    bool update();
    bool getData();
    bool getDatas();
    bool delele();
    bool insert();
};

#endif /* defined(__Henshin__DBTalkHistory__) */
