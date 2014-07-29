//
//  DNKTalk.h
//  Henshin
//
//  Created by Đinh Văn Nhật on 2014/07/27.
//  Copyright (c) 2014年 (THE) ONE of THEM. All rights reserved.
//

#ifndef __Henshin__DNKTalk__
#define __Henshin__DNKTalk__

#include <iostream>
#include "DNKItem.h"

class DNKTalk{
    DNKItem items[10];
public:
    DNKTalk* init(DNKItem* items);
    DNKItem* getItem(int index);
};
#endif /* defined(__Henshin__DNKTalk__) */
