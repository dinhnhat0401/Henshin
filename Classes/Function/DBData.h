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
class DBData
{
public:

    DBTalk* getTalk(char*);
    DBTalk* getTalks(char*);
    
    DBTalkNext* getTalkNext(char*);
    DBTalkNext* getTalkNexts(char*);
    
    DBTalkHistory* getTalkHistory(char*);
    DBTalkHistory* getTalkHistorys(char*);
    
    DBTutorialInfor* getTurorialInfor(char*);
    DBTutorialInfor* getTurorialInfors(char*);
    
    DBChara* getChara(char*);
    DBChara* getCharas(char*);
    
    DBLocalNotification* getLocalNotification(char*);
    DBLocalNotification* getLocalNotifications(char*);
};

#endif /* defined(__Henshin__DBData__) */
