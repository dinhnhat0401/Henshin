//
//  NotificationService.h
//  Henshin
//
//  Created by duong minh khoa on 8/12/14.
//  Copyright (c) 2014 DNK. All rights reserved.
//

#ifndef __Henshin__NotificationService__
#define __Henshin__NotificationService__

#include "cocos2d.h"
#include "DNKCharaterInfo.h"
using namespace std;
class NotificationService
{
public:
    static int pushNotification(int chara_id,int numberAsk);
    static int pushNotification(int chara_id,DNKCharacterInfo* info, int numberAsk);
};

#endif /* defined(__Henshin__NotificationService__) */
