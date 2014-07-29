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

using namespace std;

class DNKCharacterInfo {
    int old;
    string nickName;
    string name;
    bool isLady;
    string job;
    string profile;
    DNKTalk *talk;
public:
    DNKCharacterInfo* init(int old, string nick_name, string name, bool isLady, string job, string profile, DNKTalk* talk);
    DNKTalk* getTalk();
};

#endif /* defined(__Henshin__DNKCharaterInfo__) */
