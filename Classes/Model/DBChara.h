//
//  DBChara.h
//  Henshin
//
//  Created by hoangdieu on 8/2/14.
//  Copyright (c) 2014 DNK. All rights reserved.
//

#ifndef __Henshin__DBChara__
#define __Henshin__DBChara__
#include "cocos2d.h"
#include "DBConnect.h"
#define _(a) #a
class DBChara
{
    char* table="chara";
    int chara_id;
    int unread;
    int point;
    int is_talk_end;
    int is_recieve_result;
    int is_send_result;
    int is_keep;
    int time;
    int best_point;
    int is_add_keep;
    int is_start;
    int talk_end_time;
    int result_time;
    int is_show_profile;
public:
    void init(int,int,int,int,int,int,int,int,int,int,int,int,int,int);
    
    void setCharaId(int);
    void setUnRead(int);
    void setPoint(int);
    void setIsTalkEnd(int);
    void setIsKeep(int);
    void setIsAddKeep(int);
    void setIsReceiveResult(int);
    void setIsSendResult(int);
    void setIsStart(int);

    int getCharaId();
    int getUnRead();
    int getPoint();
    int isTalkEnd();
    int isReceiveResult();
    int isSendResult();
    int isKeep();
    int getTime();
    int getBestPoint();
    int isAddKeep();
    int isStart();
    int getTalkEndTime();
    int getResultTime();
    int isShowProfile();
    std::string toString(const int);
    
    ///database
    bool update();
    bool getData();
    bool getDatas();
    bool delele();
    bool insert();
    int getUnreadNotification();
};

#endif /* defined(__Henshin__DBChara__) */
