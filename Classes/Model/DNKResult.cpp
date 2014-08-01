//
//  DNKResult.cpp
//  Henshin
//
//  Created by Đinh Văn Nhật on 2014/08/01.
//  Copyright (c) 2014年 DNK. All rights reserved.
//

#include "DNKResult.h"

DNKResult* DNKResult::init(DNKResultItem *items){
    for (int i=0; i<3; i++) {
        this->items[i] = items[i];
    }
    return this;
}

DNKResultItem* DNKResult::getResultAtIndex(int index){
    return &this->items[index];
}
