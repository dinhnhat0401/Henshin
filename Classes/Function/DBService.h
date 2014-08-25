//
//  DBService.h
//  Henshin
//
//  Created by duong minh khoa on 8/12/14.
//  Copyright (c) 2014 DNK. All rights reserved.
//

#ifndef __Henshin__DBService__
#define __Henshin__DBService__

#include <iostream>

using namespace std;

class DBService
{
    
    public:
    static void insertTalkHistory(int chara_id, int is_self,int talk_id, int option_id);
    static void insertTalkHistory(int chara_id, int is_self,int talk_id, int option_id,int t);
    static void insertTalkHistory(int chara_id, int is_self, int is_result,int talk_id, int option_id, int result_id,long t);
    static int getUnreadNum();
};

#endif /* defined(__Henshin__DBService__) */
