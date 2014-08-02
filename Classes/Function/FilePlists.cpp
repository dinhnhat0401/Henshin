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

DNKTalk* FilePlists::getTalks(std::string k)
{
    DNKTalk *talk;
    DNKItem items[10];
    int i = 0;
    cocos2d::ValueMap obj = this->plist;
    try {
        auto talk = obj.at(k).asValueVector();
        
        for(const auto &value:talk)
        {
            auto itemTalk = value.asValueMap();
            auto options = itemTalk.at("option").asValueVector();
            DNKSelection *select = new DNKSelection[3]();
            int jop =0;
            for(const auto &item:options)
            {
                auto option = item.asValueMap();
                select[jop].initSelection(option.at("point").asInt(), option.at("text").asString(), option.at("required").asBool());
                jop++;
            }
            
            DNKOption *opts =new DNKOption();
            opts->initOption(select);
//            free(select);
//            items[i] = *new DNKItem();
            items[i].init(itemTalk.at("sec").asInt(), itemTalk.at("text").asString().c_str(), opts);
//            items[i].init(itemTalk.at("sec").asInt(), "aaa", opts);
//            free(opts);
            i++;
        }
    } catch (std::exception) {
        
    }
    talk = new DNKTalk();
    talk->init(items);
    return talk;
}

DNKCharacterInfo* FilePlists::getValues()
{
    int old;
    std::string nickName;
    std::string name;
    bool isLady;
    std::string job;
    std::string profile;
    DNKTalk *talk=new DNKTalk();
    talk= this->getTalks("talk");
    old = this->getValueInt("old");
    nickName = this->getValueString("nick_name")->getCString();
    name = this->getValueString("name")->getCString();
    isLady = this->getValueBool("lady");
    job = this->getValueString("job")->getCString();
    profile = this->getValueString("profile")->getCString();
    
    DNKResultItem* resultItem = new DNKResultItem();
    resultItem->init("culac", "gion tan");

    DNKResultItem *resultItems = new DNKResultItem[3]();
    for (int i=0; i<3; i++) {
        resultItems[i] = *resultItem;
    }
    DNKResult* result = new DNKResult();
        result->init(resultItems);
    
    DNKCharacterInfo* userInfor = new DNKCharacterInfo();
    userInfor->init(old, nickName,result, name, isLady, job, profile,talk);
    
    return userInfor;
}
