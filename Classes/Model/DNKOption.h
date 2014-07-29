//
//  DNKOption.h
//  Henshin
//
//  Created by Đinh Văn Nhật on 2014/07/27.
//  Copyright (c) 2014年 (THE) ONE of THEM. All rights reserved.
//

#ifndef __Henshin__DNKOption__
#define __Henshin__DNKOption__

#include <iostream>
#include "DNKSelection.h"
class DNKOption{
private:
    DNKSelection selections[3];
public:
    DNKOption* initOption(DNKSelection *selections);
    DNKSelection getSelection(int index);
};
#endif /* defined(__Henshin__DNKOption__) */
