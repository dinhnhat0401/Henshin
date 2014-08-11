//
//  FriendInfoLayer.h
//  Henshin
//
//  Created by Đinh Văn Nhật on 2014/08/11.
//  Copyright (c) 2014年 DNK. All rights reserved.
//

#ifndef __Henshin__FriendInfoLayer__
#define __Henshin__FriendInfoLayer__

#include <iostream>
#include "cocos2d.h"
#include <UIButton.h>
#include "DNKCharaterInfo.h"

USING_NS_CC;
using namespace ui;
using namespace std;

class FriendInfo : public cocos2d::Layer
{
private:
    Size visibleSize;
    Button *backButton;
    int zPos;
public:
    virtual bool initWithChara(int chara_id, DNKCharacterInfo* friendInfo);
    void closeInfoView(cocos2d::Ref* pSender);
    Button* getBackButton();
    
    static FriendInfo* create(int chara_id, DNKCharacterInfo* friendInfo)
    {
        FriendInfo *pRet = new FriendInfo();
        if (pRet && pRet->initWithChara(chara_id, friendInfo))
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


#endif /* defined(__Henshin__FriendInfoLayer__) */
