//
//  DBTalkHistory.h
//  Henshin
//
//  Created by hoangdieu on 8/2/14.
//  Copyright (c) 2014 DNK. All rights reserved.
//

#ifndef __Henshin__DBTalkHistory__
#define __Henshin__DBTalkHistory__

class DBTalkHistory
{
    char* table="talk_history";
    int chara_id;
    int is_self;
    int is_result;
    int talk_id;
    int option_id;
    int result_id;
    int time;
public:
    void init(int,int,int,int,int,int,int);
    void setCharaId(int);
    void setIsSelf(int);
    void setIsResult(int);
    void setTalkId(int);
    void setOptionId(int);
    void setResultId(int);
    void setTime(int);
    
    int getCharaId();
    int getIsSelf();
    int getIsResult();
    int getTalkId();
    int getOptionId();
    int getResultId();
    int getTime();
    //database
    bool update();
    bool getData();
    bool getDatas();
    bool delele();
    bool insert();
};

#endif /* defined(__Henshin__DBTalkHistory__) */
