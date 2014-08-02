//
//  TimeLineItem.h
//  Henshin
//
//  Created by duong minh khoa on 8/1/14.
//  Copyright (c) 2014 DNK. All rights reserved.
//

#ifndef __Henshin__TimeLineItem__
#define __Henshin__TimeLineItem__

#include <iostream>
using namespace std;
class TimeLineItem
{
    private:
        string _image;
        string  _charaName;
        string _message;
        int _time;
        bool _isRead;
    public:
    string getImage();
    string getCharaName();
    string getMessage();
    int getTime();
    bool getStatus();
    TimeLineItem * init(string image, string chara, string message, int time, bool isRead);
};

#endif /* defined(__Henshin__TimeLineItem__) */
