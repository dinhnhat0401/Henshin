//
//  FilePlists.cpp
//  Henshin
//
//  Created by hoangdieu on 7/26/14.
//  Copyright (c) 2014 (THE) ONE of THEM. All rights reserved.
//


#define COCOS2D_DEBUG 1
#include "FilePlists.h"

#include <iostream>
USING_NS_CC;

#define _(a) #a

void FilePlists::set(ValueMap map)
{
    this->plist = map;
}

void FilePlists::readFile(std::string filename)
{
    try {
        this->plist = FileUtils::getInstance()->getValueMapFromFile(filename);
    } catch (std::exception e) {
        this->plist = *new ValueMap();
    }
}

cocos2d::CCString* FilePlists::getValueString(std::string k)
{
    cocos2d::CCString* value = cocos2d::CCString::create("NULL");
    cocos2d::ValueMap obj = this->plist;
    try {
        value = cocos2d::CCString::create(obj.at(k).asString());
    } catch (std::exception) {
        
    }
    return value;
}

int FilePlists::getValueInt(std::string k)
{
    int value = 0;
    cocos2d::ValueMap obj = this->plist;
    try {
        value = obj.at(k).asInt();
    } catch (std::exception) {
        
    }
    return value;
}

float FilePlists::getValueFloat(std::string k)
{
    float value = 0;
    cocos2d::ValueMap obj = this->plist;
    try {
        value = obj.at(k).asFloat();
    } catch (std::exception) {
        
    }
    return value;
}

double FilePlists::getValueDouble(std::string k)
{
    double value = 0;
    cocos2d::ValueMap obj = this->plist;
    try {
        value = obj.at(k).asDouble();
    } catch (std::exception) {
        
    }
    return value;
}

bool FilePlists::getValueBool(std::string k)
{
    bool value = false;
    cocos2d::ValueMap obj = this->plist;
    try {
        value = obj.at(k).asBool();
    } catch (std::exception) {
        
    }
    return value;
}


char FilePlists::getValueByte(std::string k)
{
    char value;
    cocos2d::ValueMap obj = this->plist;
    try {
        value = obj.at(k).asByte();
    } catch (std::exception) {
        value = 'N';
    }
    return value;
}



DNKCharacterInfo* FilePlists::getValues()
{
    int old;
    std::string nickName;
    std::string name;
    bool isLady;
    std::string job;
    std::string profile;
    DNKTalk *talk;
    
    old = this->getValueInt("old");
    nickName = this->getValueString("nick_name")->getCString();
    name = this->getValueString("name")->getCString();
    isLady = this->getValueBool("lady");
    job = this->getValueString("job")->getCString();
    profile = this->getValueString("profile")->getCString();
    
    DNKCharacterInfo* userInfor = new DNKCharacterInfo();
    userInfor->init(old, nickName, name, isLady, job, profile,talk);
    
    return userInfor;
}
