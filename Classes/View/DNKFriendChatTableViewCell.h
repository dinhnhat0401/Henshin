//
//  DNKGirlChatTableViewCell.h
//  Henshin
//
//  Created by Đinh Văn Nhật on 2014/07/26.
//  Copyright (c) 2014年 (THE) ONE of THEM. All rights reserved.
//

#ifndef Henshin_DNKFriendChatTableViewCell_h
#define Henshin_DNKFriendChatTableViewCell_h
#include "DNKItem.h"
#include "Cocos2d.h"
#include "cocos-ext.h"
#include "DNKCharacterInfo.h"
#include <UIImageView.h>
#include <UIButton.h>
USING_NS_CC_EXT;
USING_NS_CC;
using namespace ui;

class DNKFriendChatTableViewCell:public TableViewCell {
private:
    Button* friendIcon;
public:
    DNKFriendChatTableViewCell* initCell(string question, int talkTime, DNKCharacterInfo *friendInfo, int chara_id);
    string getTime(int _time);
    Button* getFriendIcon();
    void helpButtonOnclick(Ref* pSender);
};
#endif
