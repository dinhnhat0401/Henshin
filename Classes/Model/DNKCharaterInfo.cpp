//
//  DNKCharaterProfile.cpp
//  Henshin
//
//  Created by Đinh Văn Nhật on 2014/07/27.
//  Copyright (c) 2014年 (THE) ONE of THEM. All rights reserved.
//

#include "DNKCharaterInfo.h"

DNKCharacterInfo* DNKCharacterInfo::init(int old, std::string nick_name, std::string name, bool isLady, std::string job, std::string profile, DNKTalk* talk) {
    characterInfo = new CharaterInfo();
    characterInfo->old = old;
    characterInfo->nickName = nick_name;
    characterInfo->name = name;
    characterInfo->isLady = isLady;
    characterInfo->job = job;
    characterInfo->profile = profile;
    characterInfo->talk = talk;
//    characterInfo->result = result;
    return this;
}

CharaterInfo* DNKCharacterInfo::getCharacterInfo(){
    return characterInfo;
}

void DNKCharacterInfo::setCharacterInfo(CharaterInfo *_characterInfo){
    characterInfo = _characterInfo;
}
