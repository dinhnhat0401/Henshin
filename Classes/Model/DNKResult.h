//
//  DNKResult.h
//  Henshin
//
//  Created by Đinh Văn Nhật on 2014/08/01.
//  Copyright (c) 2014年 DNK. All rights reserved.
//

#ifndef __Henshin__DNKResult__
#define __Henshin__DNKResult__

#include <iostream>
#include "DNKResultItem.h"
using namespace std;

class DNKResult {
private:
    DNKResultItem items[3];
public:
    DNKResult* init(DNKResultItem *items);
    DNKResultItem* getResultAtIndex(int index);
};
#endif /* defined(__Henshin__DNKResult__) */
