//
//  DNKCharaterProfile.cpp
//  Henshin
//
//  Created by Đinh Văn Nhật on 2014/07/27.
//  Copyright (c) 2014年 (THE) ONE of THEM. All rights reserved.
//

#include "DNKCharaterInfo.h"

DNKCharacterInfo* DNKCharacterInfo::init(int old, string nick_name, DNKResult* result, string name, bool isLady, string job, string profile, DNKTalk* talk) {
    this->old = old;
    this->nickName = nick_name;
    this->name = name;
    this->isLady = isLady;
    this->job = job;
    this->profile = profile;
    this->talk = talk;
    this->result = result;
    return this;
}

DNKTalk* DNKCharacterInfo::getTalk(){
    return this->talk;
}

DNKResult* DNKCharacterInfo::getResult(){
    return this->result;
}

string DNKCharacterInfo::getName(){
    return this->name;
}