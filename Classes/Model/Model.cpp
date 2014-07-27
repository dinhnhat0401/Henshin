//
//  Model.cpp
//  Henshin
//
//  Created by Đinh Văn Nhật on 2014/07/26.
//
//

#include "Model.h"

void Model::set_values (int x, int y) {
    width = x;
    height = y;
}

int Model::get_Width () {
    return width;
}

int Model::get_Height () {
    return height;
}
