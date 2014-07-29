//
//  FilePlists.h
//  Henshin
//
//  Created by hoangdieu on 7/26/14.
//  Copyright (c) 2014 (THE) ONE of THEM. All rights reserved.
//

#ifndef __Henshin__FilePlists__
#define __Henshin__FilePlists__

#include "cocos2d.h"
#include "DNKCharaterInfo.h"
class FilePlists
{
public:
    cocos2d::ValueMap plist;
    void set(cocos2d::ValueMap);
    void readFile(std::string);
    cocos2d::CCString* getValueString(std::string);
    int getValueInt(std::string);
    float getValueFloat(std::string);
    double getValueDouble(std::string);
    bool getValueBool(std::string);
    char getValueByte(std::string);
    DNKTalk * getTalks(std::string);

    DNKCharacterInfo* getValues();
};

#endif 
