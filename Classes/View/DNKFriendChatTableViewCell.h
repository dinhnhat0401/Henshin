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
#include "DNKCharaterInfo.h"
#include <UIImageView.h>
USING_NS_CC_EXT;

class DNKFriendChatTableViewCell:public TableViewCell {
private:
    cocos2d::ui::ImageView* friendIcon;
public:
    DNKFriendChatTableViewCell* initCell(DNKItem *item, DNKCharacterInfo *friendInfo);
};
#endif
