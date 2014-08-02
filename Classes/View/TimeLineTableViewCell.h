//
//  TimeLineTableViewCell.h
//  Henshin
//
//  Created by duong minh khoa on 8/1/14.
//  Copyright (c) 2014 DNK. All rights reserved.
//

#ifndef __Henshin__TimeLineTableViewCell__
#define __Henshin__TimeLineTableViewCell__

#include "Cocos2d.h"
#include "cocos-ext.h"
#include "TimeLineItem.h"
#include "ConstantValue.h"
USING_NS_CC_EXT;

class TimeLineCell:public TableViewCell
{
    public:
        TimeLineCell* init(TimeLineItem * item);
        inline std::string getTime(int time);
};

#endif /* defined(__Henshin__TimeLineTableViewCell__) */
