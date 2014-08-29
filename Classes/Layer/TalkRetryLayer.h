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
#include <UIButton.h>
USING_NS_CC;


using namespace std;
using namespace ui;
class TalkRetry : public cocos2d::LayerColor
{
private:
    Button *backButton;
    Button *retryButton;
    Button *goKeepList;
    CCLabelTTF* _message;
    int zPos;
    Size visibleSize;
    
    // retry type = 0 -> retry when end talk
    // retry type = 1 -> retry when go to talkdetail ended
    int retryType;
public:
//    void closeRetryView(cocos2d::Ref* pSender);
    Button* getBackButton();
    Button* getRetryButton();
    Button* getGoToKeepListButton();
    virtual bool initWithType(int type);
    static TalkRetry* create(int type)
    {
        TalkRetry *pRet = new TalkRetry();
        if (pRet && pRet->initWithType(type))
        {
            pRet->autorelease();
            return pRet;
        }
        else
        {
            delete pRet;
            pRet = NULL;
            return NULL;
        }
    }
};
#endif /* defined(__Henshin__TalkRetryLayer__) */
