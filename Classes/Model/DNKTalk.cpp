//
//  DNKTalk.cpp
//  Henshin
//
//  Created by Đinh Văn Nhật on 2014/07/27.
//  Copyright (c) 2014年 (THE) ONE of THEM. All rights reserved.
//

#include "DNKTalk.h"

DNKTalk* DNKTalk::init(DNKItem *items){
    for (int i=0; i<10; i++) {
        this->items[i] = items[i];
    }
    return this;
}