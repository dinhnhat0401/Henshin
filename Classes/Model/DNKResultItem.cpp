//
//  DNKResultItem.cpp
//  Henshin
//
//  Created by Đinh Văn Nhật on 2014/08/01.
//  Copyright (c) 2014年 DNK. All rights reserved.
//

#include "DNKResultItem.h"

DNKResultItem* DNKResultItem::init(string text, string option){
    this->text = text;
    this->option = option;
    return this;
}