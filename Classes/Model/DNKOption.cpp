//
//  DNKOption.cpp
//  Henshin
//
//  Created by Đinh Văn Nhật on 2014/07/27.
//  Copyright (c) 2014年 (THE) ONE of THEM. All rights reserved.
//

#include "DNKOption.h"

DNKOption* DNKOption::initOption(DNKSelection *selections){
    for (int i=0; i < 3; i ++) {
        this->selections[i] = selections[i];
    }
    return this;
}

DNKSelection DNKOption::getSelection(int index){
    return this->selections[index];
}