//
//  DNKCommon.h
//  Henshin
//
//  Created by Đinh Văn Nhật on 2014/07/28.
//  Copyright (c) 2014年 (THE) ONE of THEM. All rights reserved.
//

#ifndef __Henshin__DNKCommon__
#define __Henshin__DNKCommon__

#include <iostream>
#include "cocos2d.h"
using namespace std;

class DNKCommon{
public:
    static float calculateHeightOfLabel(string str, int fontSize, float width);
    static float calculateHeightOfTalkCell(string str, int fontSize, float width);
    static float calculateHeightOfTalkMyCell(string str, int fontSize, float width);

};

#endif /* defined(__Henshin__DNKCommon__) */
