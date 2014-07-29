//
//  DNKItem.h
//  Henshin
//
//  Created by Đinh Văn Nhật on 2014/07/27.
//  Copyright (c) 2014年 (THE) ONE of THEM. All rights reserved.
//

#ifndef __Henshin__DNKItem__
#define __Henshin__DNKItem__

#include <iostream>
#include "DNKOption.h"
using namespace std;
class DNKItem{
private:
    int sec;
    string question;
    DNKOption *options;
public:
    DNKItem* init(int sec, string question, DNKOption* options);
    string getQuestion();
    DNKOption* getOptions();
};
#endif /* defined(__Henshin__DNKItem__) */
