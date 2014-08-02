//
//  DBTutorialInfor.cpp
//  Henshin
//
//  Created by hoangdieu on 8/2/14.
//  Copyright (c) 2014 DNK. All rights reserved.
//

#include "DBTutorialInfor.h"

void DBTutorialInfor::init(int tutorial_id, int is_read)
{
    this->tutorial_id = tutorial_id;
    this->is_read = is_read;
}

int DBTutorialInfor::getTutorialId()
{
    return this->tutorial_id;
}

int DBTutorialInfor::isRead()
{
    return this->is_read;
}