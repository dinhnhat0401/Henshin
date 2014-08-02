//
//  DBData.cpp
//  Henshin
//
//  Created by hoangdieu on 8/2/14.
//  Copyright (c) 2014 DNK. All rights reserved.
//

#include "DBData.h"

USING_NS_CC;

//get Talk data
DBTalk* DBData::getTalk(char* condition)
{
    //db connect
    DBConnect *dbCon = new DBConnect();
    dbCon->getConnect();
    DBTalk *data = new DBTalk();
    const char* select= "SELECT * FROM talk WHERE ";
    char query[256]; // <- danger, only storage for 256 characters.
    strncpy(query, select, sizeof(query));
    strncat(query, condition, sizeof(query) - strlen(query) - 1);
    
    dbCon->getData(query);
    if(dbCon->getRow() <= 0)
        return data;
    log("Row:%s",dbCon->getDataIndex(1,1));
    int uid = atoi(dbCon->getDataIndex(1, 0));
    int chara_id = atoi(dbCon->getDataIndex(1, 1));;
    int talk_id = atoi(dbCon->getDataIndex(1, 2));;
    int option_id = atoi(dbCon->getDataIndex(1, 3));;
    int receive_time = atoi(dbCon->getDataIndex(1, 4));;
    int send_time = atoi(dbCon->getDataIndex(1, 5));;
    

    data->init(uid, chara_id, talk_id, option_id, receive_time, send_time);
    
    //free table and db
    dbCon->freeTable();
    dbCon->closeDB();
    return data;
}

//get Talk data
DBTalk* DBData::getTalks(char* condition)
{
    //db connect
    DBConnect *dbCon = new DBConnect();
    dbCon->getConnect();
    DBTalk data[100];
    
    const char* select= "SELECT * FROM talk WHERE ";
    char query[256]; // <- danger, only storage for 256 characters.
    strncpy(query, select, sizeof(query));
    strncat(query, condition, sizeof(query) - strlen(query) - 1);
    dbCon->getData(query);
    if(dbCon->getRow() <= 0)
        return data;
    for(int i=1; i <= dbCon->getRow();i++)
    {
        int uid = atoi(dbCon->getDataIndex(i, 0));
        int chara_id = atoi(dbCon->getDataIndex(i, 1));
        int talk_id = atoi(dbCon->getDataIndex(i, 2));
        int option_id = atoi(dbCon->getDataIndex(i, 3));
        int receive_time = atoi(dbCon->getDataIndex(i, 4));
        int send_time = atoi(dbCon->getDataIndex(i, 5));
        data[i-1] = *new DBTalk();
        data[i-1].init(uid, chara_id, talk_id, option_id, receive_time, send_time);
    }
    //free table and db
    dbCon->freeTable();
    dbCon->closeDB();
    
//    data->init(uid, chara_id, talk_id, option_id, receive_time, send_time);
    return data;
}


//talk next
DBTalkNext* DBData::getTalkNext(char *condition)
{
    //db connect
    DBConnect *dbCon = new DBConnect();
    dbCon->getConnect();
    DBTalkNext* data= new DBTalkNext();
    const char* select= "SELECT * FROM talk_next WHERE ";
    char query[256]; // <- danger, only storage for 256 characters.
    strncpy(query, select, sizeof(query));
    strncat(query, condition, sizeof(query) - strlen(query) - 1);
    dbCon->getData(query);
    if(dbCon->getRow() <= 0)
        return data;
    int uid = atoi(dbCon->getDataIndex(1, 0));
    int chara_id = atoi(dbCon->getDataIndex(1, 1));
    int talk_id = atoi(dbCon->getDataIndex(1, 2));
    int time = atoi(dbCon->getDataIndex(1, 3));
    
    //free table and db
    dbCon->freeTable();
    dbCon->closeDB();
    
    data->init(uid, chara_id, talk_id, time);
    return data;
}

//talk next
DBTalkNext* DBData::getTalkNexts(char *condition)
{
    //db connect
    DBConnect *dbCon = new DBConnect();
    dbCon->getConnect();
    DBTalkNext data[100];
    
    
    const char* select= "SELECT * FROM talk_next WHERE ";
    char query[256]; // <- danger, only storage for 256 characters.
    strncpy(query, select, sizeof(query));
    strncat(query, condition, sizeof(query) - strlen(query) - 1);
    dbCon->getData(query);
    if(dbCon->getRow() <= 0)
        return data;
    for(int i=1; i <= dbCon->getRow();i++)
    {
        int uid = atoi(dbCon->getDataIndex(i, 0));
        int chara_id = atoi(dbCon->getDataIndex(i, 1));
        int talk_id = atoi(dbCon->getDataIndex(i, 2));
        int time = atoi(dbCon->getDataIndex(i, 3));
        
        data[i-1] = *new DBTalkNext();
        data[i-1].init(uid, chara_id, talk_id, time);
    }
    //free table and db
    dbCon->freeTable();
    dbCon->closeDB();
    
    
    return data;
}


//get array data
DBChara* DBData::getChara(char* condition)
{
    //db connect
    DBConnect *dbCon = new DBConnect();
    dbCon->getConnect();
    DBChara *data = new DBChara();
    const char* select= "SELECT * FROM chara WHERE ";
    char query[256]; // <- danger, only storage for 256 characters.
    strncpy(query, select, sizeof(query));
    strncat(query, condition, sizeof(query) - strlen(query) - 1);
    dbCon->getData(query);
    if(dbCon->getRow() <= 0)
        return data;
    for(int i=1; i <= dbCon->getRow();i++)
    {
        int chara_id = atoi(dbCon->getDataIndex(i, 0));
        int unread = atoi(dbCon->getDataIndex(i, 1));
        int point = atoi(dbCon->getDataIndex(i, 2));
        int is_talk_end = atoi(dbCon->getDataIndex(i,3 ));
        int is_receive_result = atoi(dbCon->getDataIndex(i,4));
        int is_send_result = atoi(dbCon->getDataIndex(i, 5));
        int is_keep = atoi(dbCon->getDataIndex(i, 6));
        int time = atoi(dbCon->getDataIndex(i, 7));
        int best_point = atoi(dbCon->getDataIndex(i, 8));
        int is_add_keep = atoi(dbCon->getDataIndex(i, 9));
        int is_start = atoi(dbCon->getDataIndex(i, 10));
        int talk_end_time = atoi(dbCon->getDataIndex(i,11));
        int result_time = atoi(dbCon->getDataIndex(i, 12));
        int is_show_profile = atoi(dbCon->getDataIndex(i, 13));
        
        data[i-1]= *new DBChara();
        data[i-1].init(chara_id, unread, point, is_talk_end, is_receive_result, is_send_result, is_keep, time, best_point, is_add_keep, is_start, talk_end_time, result_time, is_show_profile);
    }
    //free table and db
    dbCon->freeTable();
    dbCon->closeDB();
    
    
    
    return data;
}

//get array DBChara
DBChara* DBData::getCharas(char* condition)
{
    //db connect
    DBConnect *dbCon = new DBConnect();
    dbCon->getConnect();
    DBChara data[100];
    const char* select= "SELECT * FROM chara WHERE ";
    char query[256]; // <- danger, only storage for 256 characters.
    strncpy(query, select, sizeof(query));
    strncat(query, condition, sizeof(query) - strlen(query) - 1);
    dbCon->getData(query);
    if(dbCon->getRow() <= 0)
        return data;
    int chara_id = atoi(dbCon->getDataIndex(1, 0));
    int unread = atoi(dbCon->getDataIndex(1, 1));
    int point = atoi(dbCon->getDataIndex(1, 2));
    int is_talk_end = atoi(dbCon->getDataIndex(1,3 ));
    int is_receive_result = atoi(dbCon->getDataIndex(1,4));
    int is_send_result = atoi(dbCon->getDataIndex(1, 5));
    int is_keep = atoi(dbCon->getDataIndex(1, 6));
    int time = atoi(dbCon->getDataIndex(1, 7));
    int best_point = atoi(dbCon->getDataIndex(1, 8));
    int is_add_keep = atoi(dbCon->getDataIndex(1, 9));
    int is_start = atoi(dbCon->getDataIndex(1, 10));
    int talk_end_time = atoi(dbCon->getDataIndex(1,11));
    int result_time = atoi(dbCon->getDataIndex(1, 12));
    int is_show_profile = atoi(dbCon->getDataIndex(1, 13));
    

    data->init(chara_id, unread, point, is_talk_end, is_receive_result, is_send_result, is_keep, time, best_point, is_add_keep, is_start, talk_end_time, result_time, is_show_profile);
    
    //free table and db
    dbCon->freeTable();
    dbCon->closeDB();
    
    return data;
}

DBTalkHistory* DBData::getTalkHistory(char *condition)
{
    //db connect
    DBConnect *dbCon = new DBConnect();
    dbCon->getConnect();
    DBTalkHistory *data = new DBTalkHistory();
    const char* select= "SELECT * FROM talk_history WHERE ";
    char query[256]; // <- danger, only storage for 256 characters.
    strncpy(query, select, sizeof(query));
    strncat(query, condition, sizeof(query) - strlen(query) - 1);
    dbCon->getData(query);
    if(dbCon->getRow() <= 0)
        return data;

    
    int chara_id = atoi(dbCon->getDataIndex(1, 0));
    int is_self = atoi(dbCon->getDataIndex(1, 1));
    int is_result = atoi(dbCon->getDataIndex(1, 2));
    int talk_id = atoi(dbCon->getDataIndex(1, 3));
    int option_id = atoi(dbCon->getDataIndex(1, 4));
    int result_id = atoi(dbCon->getDataIndex(1, 5));
    int time = atoi(dbCon->getDataIndex(1, 6));
    
    
    data->init(chara_id, is_self, is_result, talk_id, option_id,result_id,time);
    //free table and db
    dbCon->freeTable();
    dbCon->closeDB();
    
    return data;

}

DBTalkHistory* DBData::getTalkHistorys(char *condition)
{
    //db connect
    DBConnect *dbCon = new DBConnect();
    dbCon->getConnect();
    DBTalkHistory data[100];
    const char* select= "SELECT * FROM talk_history WHERE ";
    char query[256]; // <- danger, only storage for 256 characters.
    strncpy(query, select, sizeof(query));
    strncat(query, condition, sizeof(query) - strlen(query) - 1);
    dbCon->getData(query);
    if(dbCon->getRow() <= 0)
        return data;
    
    for(int i=1; i <= dbCon->getRow();i++)
    {
        int chara_id = atoi(dbCon->getDataIndex(i, 0));
        int is_self = atoi(dbCon->getDataIndex(i, 1));
        int is_result = atoi(dbCon->getDataIndex(i, 2));
        int talk_id = atoi(dbCon->getDataIndex(i, 3));
        int option_id = atoi(dbCon->getDataIndex(i, 4));
        int result_id = atoi(dbCon->getDataIndex(i, 5));
        int time = atoi(dbCon->getDataIndex(i, 6));
        data[i-1] = *new DBTalkHistory();
        data[i-1].init(chara_id, is_self, is_result, talk_id, option_id,result_id,time);
    }
    //free table and db
    dbCon->freeTable();
    dbCon->closeDB();
    
    
    return data;
    
}


DBLocalNotification* DBData::getLocalNotification(char *condition)
{
    //db connect
    DBConnect *dbCon = new DBConnect();
    dbCon->getConnect();
    DBLocalNotification *data = new DBLocalNotification();
    const char* select= "SELECT * FROM local_notification WHERE ";
    char query[256]; // <- danger, only storage for 256 characters.
    strncpy(query, select, sizeof(query));
    strncat(query, condition, sizeof(query) - strlen(query) - 1);
    dbCon->getData(query);
    if(dbCon->getRow() <= 0)
        return data;
    
    
    int chara_id = atoi(dbCon->getDataIndex(1, 0));
    string body = dbCon->getDataIndex(1, 1);
    string key = dbCon->getDataIndex(1, 2);
    int time = atoi(dbCon->getDataIndex(1, 3));
    
    
    data->init(chara_id, key, body, time);
    //free table and db
    dbCon->freeTable();
    dbCon->closeDB();
    
    return data;
    
}

DBLocalNotification* DBData::getLocalNotifications(char *condition)
{
    //db connect
    DBConnect *dbCon = new DBConnect();
    dbCon->getConnect();
    DBLocalNotification data[100];
    const char* select= "SELECT * FROM local_notification WHERE ";
    char query[256]; // <- danger, only storage for 256 characters.
    strncpy(query, select, sizeof(query));
    strncat(query, condition, sizeof(query) - strlen(query) - 1);
    dbCon->getData(query);
    if(dbCon->getRow() <= 0)
        return data;
    
    for(int i=1; i <= dbCon->getRow();i++)
    {

        int chara_id = atoi(dbCon->getDataIndex(i, 0));
        string body = dbCon->getDataIndex(i, 1);
        string key = dbCon->getDataIndex(i, 2);
        int time = atoi(dbCon->getDataIndex(i, 3));
        
        data[i-1] = *new DBLocalNotification();
        data[i-1].init(chara_id, key, body, time);
    }
    //free table and db
    dbCon->freeTable();
    dbCon->closeDB();
    
    
    return data;
}



/////////////////// tutorial

DBTutorialInfor* DBData::getTurorialInfor(char *condition)
{
    //db connect
    DBConnect *dbCon = new DBConnect();
    dbCon->getConnect();
    DBTutorialInfor *data = new DBTutorialInfor();
    const char* select= "SELECT * FROM tutorial_info WHERE ";
    char query[256]; // <- danger, only storage for 256 characters.
    strncpy(query, select, sizeof(query));
    strncat(query, condition, sizeof(query) - strlen(query) - 1);
    dbCon->getData(query);
    if(dbCon->getRow() <= 0)
        return data;
    
    int tutorial_id =  atoi(dbCon->getDataIndex(1, 0));
    int is_read =  atoi(dbCon->getDataIndex(1, 1));
    
    
    data->init(tutorial_id, is_read);
    //free table and db
    dbCon->freeTable();
    dbCon->closeDB();
    
    return data;
    
}

DBTutorialInfor* DBData::getTurorialInfors(char *condition)
{
    //db connect
    DBConnect *dbCon = new DBConnect();
    dbCon->getConnect();
    DBTutorialInfor data[100];
    const char* select= "SELECT * FROM tutorial_info WHERE ";
    char query[256]; // <- danger, only storage for 256 characters.
    strncpy(query, select, sizeof(query));
    strncat(query, condition, sizeof(query) - strlen(query) - 1);
    dbCon->getData(query);
    if(dbCon->getRow() <= 0)
        return data;
    
    for(int i=1; i <= dbCon->getRow();i++)
    {
        int tutorial_id =  atoi(dbCon->getDataIndex(i, 0));
        int is_read =  atoi(dbCon->getDataIndex(i, 1));
        
        
        data[i-1] = *new DBTutorialInfor();
        data[i-1].init(tutorial_id, is_read);
    }
    //free table and db
    dbCon->freeTable();
    dbCon->closeDB();
    
    
    return data;
}