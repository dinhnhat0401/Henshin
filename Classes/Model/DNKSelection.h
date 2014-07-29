//
//  DNKSelection.h
//  Henshin
//
//  Created by Đinh Văn Nhật on 2014/07/27.
//  Copyright (c) 2014年 (THE) ONE of THEM. All rights reserved.
//

#ifndef __Henshin__DNKSelection__
#define __Henshin__DNKSelection__

#include <iostream>
#include <string>   // using string
using namespace std;

class DNKSelection{
private:
    int point;
    string text;
    bool required;
public:
    DNKSelection* initSelection(int point, string text, bool required);
    string getAnswer();
};
#endif /* defined(__Henshin__DNKSelection__) */
