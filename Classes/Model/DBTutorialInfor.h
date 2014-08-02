//
//  DBTutorialInfor.h
//  Henshin
//
//  Created by hoangdieu on 8/2/14.
//  Copyright (c) 2014 DNK. All rights reserved.
//

#ifndef __Henshin__DBTutorialInfor__
#define __Henshin__DBTutorialInfor__


class DBTutorialInfor
{
    char* table="tutorial_info";
    int tutorial_id;
    int is_read;
public:
    void init(int,int,int,int);
    void setTutorialId(int);
    void setIsRead(int);
    int getTutorialId();
    int getIsRead();
    
    //database
    bool update();
    bool getData();
    bool getDatas();
    bool delele();
    bool insert();
};

#endif /* defined(__Henshin__DBTutorialInfor__) */
