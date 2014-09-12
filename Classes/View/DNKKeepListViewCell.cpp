//
//  DNKKeepListViewCell.cpp
//  Henshin
//
//  Created by Đinh Văn Nhật on 2014/09/12.
//  Copyright (c) 2014年 DNK. All rights reserved.
//

#include "DNKKeepListViewCell.h"
#include <string.h>
#include <UIImageView.h>
#include "DNKConstant.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;

DNKKeepListViewCell* DNKKeepListViewCell::initCell(bool isMe, DNKCharacterInfo *info, int chara_id) {
    string avatarURL = "";
    Label *nameLbl;
    string user_name;
    if (isMe) {
        UserDefault *userDefalt = UserDefault::getInstance();
        user_name = userDefalt->getStringForKey("username");
        bool gender = userDefalt->getBoolForKey("gender");
        if (gender) {
            avatarURL = "res/keep/icon_0.png";
        } else {
            avatarURL = "res/keep/icon_1.png";
        }
    } else {
        avatarURL = StringUtils::format("res/chara/%d/icon.png",chara_id);
        user_name = info->getNickName();
    }
    ImageView* avatarImg = ImageView::create(avatarURL);
    avatarImg->setAnchorPoint(Vec2(0, 0));
    avatarImg->setPosition(Vec2(0, 0));
    this->addChild(avatarImg, 998);
    
    nameLbl = Label::createWithSystemFont(user_name, kDEFAULT_BOLD_FONT, 25);
    nameLbl->setColor(Color3B::BLACK);
    nameLbl->setAnchorPoint(Vec2(0, 0));
    nameLbl->setPosition(100,25);
    this->addChild(nameLbl, 999);

    return this;
}
