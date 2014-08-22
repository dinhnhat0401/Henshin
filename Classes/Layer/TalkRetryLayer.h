//
//  TalkRetryLayer.h
//  Henshin
//
//  Created by Đinh Văn Nhật on 2014/08/15.
//  Copyright (c) 2014年 DNK. All rights reserved.
//

#ifndef __Henshin__TalkRetryLayer__
#define __Henshin__TalkRetryLayer__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;

using namespace std;
using namespace ui;
class TalkRetry : public cocos2d::LayerColor
{
private:
    int zPos;
    Size visibleSize;
public:
    virtual bool init();
    CREATE_FUNC(TalkRetry);
};
#endif /* defined(__Henshin__TalkRetryLayer__) */
