//
//  DNKCharaterProfile.h
//  Henshin
//
//  Created by Đinh Văn Nhật on 2014/07/27.
//  Copyright (c) 2014年 (THE) ONE of THEM. All rights reserved.
//

#ifndef __Henshin__DNKCharaterInfo__
#define __Henshin__DNKCharaterInfo__

#include "cocos-ext.h"
#include "DNKTalk.h"
#include "DNKResult.h"

using namespace std;

class DNKCharacterInfo {
    int old;
    string nickName;
    DNKResult *result;
    string name;
    bool isLady;
    string job;
    string profile;
    DNKTalk *talk;
public:
    DNKCharacterInfo* init(int old, string nick_name, DNKResult* result, string name, bool isLady, string job, string profile, DNKTalk* talk);
    DNKTalk* getTalk();
    DNKResult* getResult();
    string getName();
};

#endif /* defined(__Henshin__DNKCharaterInfo__) */
