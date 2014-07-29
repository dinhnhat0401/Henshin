//
//  DNKSelection.cpp
//  Henshin
//
//  Created by Đinh Văn Nhật on 2014/07/27.
//  Copyright (c) 2014年 (THE) ONE of THEM. All rights reserved.
//

#include "DNKSelection.h"
DNKSelection* DNKSelection::initSelection(int point, string text, bool required){
    this->point = point;
    this->text = text;
    this->required = required;
    return this;
}

string DNKSelection::getAnswer(){
    return this->text;
}
