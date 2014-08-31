//
//  TalkDetailHelpLayer.h
//  Henshin
//
//  Created by Đinh Văn Nhật on 2014/09/01.
//  Copyright (c) 2014年 DNK. All rights reserved.
//

#ifndef __Henshin__TalkDetailHelpLayer__
#define __Henshin__TalkDetailHelpLayer__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include <UIButton.h>
USING_NS_CC;

class TalkDetailHelpLayer : public cocos2d::Layer
{
private:
    int zPos;
    Size visibleSize;
    CCLabelTTF* _topMessage;
    CCLabelTTF* _bottomMessage;
public:
    virtual bool init();
    CREATE_FUNC(TalkDetailHelpLayer);
};

#endif /* defined(__Henshin__TalkDetailHelpLayer__) */
