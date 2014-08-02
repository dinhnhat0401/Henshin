//
//  TimeLineItem.cpp
//  Henshin
//
//  Created by duong minh khoa on 8/1/14.
//  Copyright (c) 2014 DNK. All rights reserved.
//

#include "TimeLineItem.h"

TimeLineItem * TimeLineItem::init(string image, string chara, string message, int time, bool isRead)
{
    this->_image        = image;
    this->_charaName    = chara;
    this->_message      = message;
    this->_time         = time;
    this->_isRead       = isRead;
    return this;
};

string TimeLineItem::getImage(){return _image;};
string TimeLineItem::getCharaName(){ return _charaName;};;
string TimeLineItem::getMessage() {return _message;};
int TimeLineItem::getTime(){ return _time; };
bool TimeLineItem::getStatus(){ return _isRead;};


