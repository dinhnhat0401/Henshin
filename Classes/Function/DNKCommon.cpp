//
//  DNKCommon.cpp
//  Henshin
//
//  Created by Đinh Văn Nhật on 2014/07/28.
//  Copyright (c) 2014年 (THE) ONE of THEM. All rights reserved.
//

#include "DNKCommon.h"
#include "DNKConstant.h"
#include "DBTalkNext.h"
#include "DBData.h"
USING_NS_CC;
float DNKCommon::calculateHeightOfLabel(string str, int fontSize, float width){
    float height = 0;
    CCLabelTTF* lbl = CCLabelTTF::create(str, kDEFAULT_BOLD_FONT, fontSize);
    lbl->setHorizontalAlignment(cocos2d::TextHAlignment::LEFT);
    lbl->setDimensions(Size(Vec2(width, 0)));
    //    log("width = %f %f", lbl->getContentSize().width, lbl->getContentSize().height);
    height = lbl->getContentSize().height;
    return height;
}

float DNKCommon::calculateHeightOfTalkCell(string str, int fontSize, float width){
    float height = DNKCommon::calculateHeightOfLabel(str,fontSize,width);
    height += 40; // padding * 2
    height += 100; // user name height
    return height;
}

float DNKCommon::calculateHeightOfTalkMyCell(string str, int fontSize, float width){
    float height = DNKCommon::calculateHeightOfLabel(str,fontSize,width);
    height += 40; // padding * 2
    return height;
}

void DNKCommon::updateTalk(int chara_id)
{
    long int now = static_cast<long int>(time(NULL));
    string condition = StringUtils::format(" time <= %d",now);
    condition = (chara_id == 0) ? condition : condition + StringUtils::format(" and chara_id =",chara_id);
    DBData * db = new DBData();
    vector<DBTalkNext*> talkNexts = db->getTalkNexts(const_cast<char*>(condition.c_str()));
    int size = talkNexts.size();
    if(size == 0)
        return;
    DBConnect *dbCon = new DBConnect();
    dbCon->getConnect();
    for(int i = 0; i < size; i++)
    {
        int unReadId = talkNexts[i]->getCharaId();
        string update = StringUtils::format("update chara set unread = 1 where chara_id = %d",unReadId);
        int uid = talkNexts[i]->getUid();
        dbCon->executeCommand(const_cast<char *>(update.c_str()));
        
        string deleteC = StringUtils::format(" delete from talk_next where uid = %d",uid);
        dbCon->executeCommand(const_cast<char *>(deleteC.c_str()));
    }
}

string DNKCommon::convertTime(int _time)
{
    time_t now;
    time(&now);
    struct tm * tm_now;
    tm_now = localtime(&now);
    std::string timeStr;
    time_t messageTime = (time_t)_time;
    struct tm * tm_msg;
    tm_msg = localtime(&messageTime);
    timeStr = StringUtils::format("%02d:%02d",tm_msg->tm_hour,tm_msg->tm_min);
    return timeStr;
}

