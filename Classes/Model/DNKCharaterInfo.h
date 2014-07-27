//
//  DNKCharaterProfile.h
//  Henshin
//
//  Created by Đinh Văn Nhật on 2014/07/27.
//  Copyright (c) 2014年 (THE) ONE of THEM. All rights reserved.
//

#ifndef __Henshin__DNKCharaterProfile__
#define __Henshin__DNKCharaterProfile__

#include "cocos-ext.h"
#include "DNKTalk.h"
USING_NS_CC_EXT;
typedef struct {
    int old;
    std::string nickName;
    std::string name;
    bool isLady;
    std::string job;
    std::string profile;
    DNKTalk *talk;
//    std::string *result;
}CharaterInfo;

//#include <iostream>
class DNKCharacterInfo {
    CharaterInfo *characterInfo;
public:
    DNKCharacterInfo* init(int old, std::string nick_name, std::string name, bool isLady, std::string job, std::string profile, DNKTalk* talk);
    CharaterInfo* getCharacterInfo();
    void setCharacterInfo(CharaterInfo* characterInfo);
};

#endif /* defined(__Henshin__DNKCharaterProfile__) */
