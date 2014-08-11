//
//  FriendInfoLayer.cpp
//  Henshin
//
//  Created by Đinh Văn Nhật on 2014/08/11.
//  Copyright (c) 2014年 DNK. All rights reserved.
//

#include "FriendInfoLayer.h"
#include <UIImageView.h>
#include "DNKConstant.h"
#include "DNKCommon.h"
USING_NS_CC;

bool FriendInfo::initWithChara(int chara_id, DNKCharacterInfo* friendInfo)
{
    if(!Layer::init()) return false;
    zPos = 0;
    visibleSize = Director::getInstance()->getVisibleSize();

    ImageView* bgImage = cocos2d::ui::ImageView::create("res/common/dlgback.png");
    bgImage->setAnchorPoint(Vec2(0, 0));
    bgImage->setPosition(Vec2(0, 0));
    this->addChild(bgImage);
    
    string friendIconImg = StringUtils::format("res/chara/%d/profile.png",chara_id);
    ImageView* profile = ImageView::create(friendIconImg);
    profile->setAnchorPoint(Vec2(0, 0));
    float profileX = (visibleSize.width - profile->getContentSize().width)/2;
    float profileY = (visibleSize.height - profile->getContentSize().height)/2;
    profile->setPosition(Vec2(profileX, profileY));
    this->addChild(profile, zPos++);
    
    backButton = Button::create();
    backButton->setTouchEnabled(true);
    backButton->loadTextures("res/common/btn_close_single.png", "res/common/btn_close_single.png");
    backButton->setAnchorPoint(Vec2(0, 0));
    backButton->setPosition(Vec2(profileX, profileY));
    this->addChild(backButton, zPos++);

    string profileString = friendInfo->getProfile();
    float textHeight = DNKCommon::calculateHeightOfLabel(profileString, 27, 580);

    CCLabelTTF* profileLbl = CCLabelTTF::create(profileString, kDEFAULT_BOLD_FONT, 27);
    profileLbl->setColor(Color3B::BLACK);
    profileLbl->setHorizontalAlignment(cocos2d::TextHAlignment::LEFT);
    profileLbl->setAnchorPoint(Vec2(0, 0));
    profileLbl->setPosition(Vec2(profileX + kPADDING, profileY + 100 + (200 - textHeight)/2));
    profileLbl->setDimensions(Size(Vec2(580, 0)));
    this->addChild(profileLbl, zPos++);
    
    string tmp = StringUtils::format("%s (%d)",friendInfo->getName().c_str(), friendInfo->getYearsOld());
    CCLabelTTF* nameAndOld = CCLabelTTF::create(tmp, kDEFAULT_BOLD_FONT, 27);
    nameAndOld->setColor(Color3B::WHITE);
    nameAndOld->setHorizontalAlignment(TextHAlignment::CENTER);
    nameAndOld->setAnchorPoint(Vec2(0, 0));
    nameAndOld->setPosition(Vec2(profileX + 270 + kPADDING, profileY + 410));
    nameAndOld->setDimensions(Size(Vec2(300, 0)));
    this->addChild(nameAndOld, zPos++);
    
    CCLabelTTF* job = CCLabelTTF::create(friendInfo->getJob(), kDEFAULT_BOLD_FONT, 30);
    job->setColor(Color3B::WHITE);
    job->setHorizontalAlignment(TextHAlignment::CENTER);
    job->setAnchorPoint(Vec2(0, 0));
    job->setPosition(Vec2(profileX + 270 + kPADDING, profileY + 360));
    job->setDimensions(Size(Vec2(300, 0)));
    this->addChild(job, zPos++);
    return true;
};

void FriendInfo::closeInfoView(cocos2d::Ref* pSender)
{
    this->removeFromParent();
}

Button* FriendInfo::getBackButton()
{
    return this->backButton;
}