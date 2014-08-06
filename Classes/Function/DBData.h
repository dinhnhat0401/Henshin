//
//  DBData.h
//  Henshin
//
//  Created by hoangdieu on 8/2/14.
//  Copyright (c) 2014 DNK. All rights reserved.
//

#ifndef __Henshin__DBData__
#define __Henshin__DBData__
#include "DBTalk.h"
#include "DBTalkNext.h"
#include "DBTalkHistory.h"
#include "DBTutorialInfor.h"
#include "DBChara.h"
#include "DBLocalNotification.h"
#include "DBConnect.h"

using namespace std;

class DBData
{
public:

    DBTalk* getTalk(char*);
    vector<DBTalk*> getTalks(char*);
    
    DBTalkNext* getTalkNext(char*);
    vector<DBTalkNext*> getTalkNexts(char*);
    
    DBTalkHistory* getTalkHistory(char*);
    vector<DBTalkHistory*> getTalkHistorys(char*);
    
    DBTutorialInfor* getTurorialInfor(char*);
    vector<DBTutorialInfor*> getTurorialInfors(char*);
    
    DBChara* getChara(char*);
    vector<DBChara*> getCharas(char*);
    
    DBLocalNotification* getLocalNotification(char*);
    vector<DBLocalNotification*> getLocalNotifications(char*);
    int getNextTimeLine(int t);
    int getNextTalk(int chara_id,int t);
    
};

#endif /* defined(__Henshin__DBData__) */
