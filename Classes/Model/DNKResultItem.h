//
//  DNKResultItem.h
//  Henshin
//
//  Created by Đinh Văn Nhật on 2014/08/01.
//  Copyright (c) 2014年 DNK. All rights reserved.
//

#ifndef __Henshin__DNKResultItem__
#define __Henshin__DNKResultItem__

#include <iostream>
using namespace std;

class DNKResultItem{
private:
    string text;
    string option;
public:
    DNKResultItem* init(string text, string option);
};
#endif /* defined(__Henshin__DNKResultItem__) */
