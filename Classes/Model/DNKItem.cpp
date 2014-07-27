//
//  DNKItem.cpp
//  Henshin
//
//  Created by Đinh Văn Nhật on 2014/07/27.
//  Copyright (c) 2014年 (THE) ONE of THEM. All rights reserved.
//

#include "DNKItem.h"

DNKItem* DNKItem::init(int sec, string question, DNKOption* options)
{
    this->sec = sec;
    this->question = question;
    this->options = options;
    return this;
}