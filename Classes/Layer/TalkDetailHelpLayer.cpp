//
//  TalkDetailHelpLayer.cpp
//  Henshin
//
//  Created by Đinh Văn Nhật on 2014/09/01.
//  Copyright (c) 2014年 DNK. All rights reserved.
//

#include "TalkDetailHelpLayer.h"
#include <UIImageView.h>
#include "DNKConstant.h"
using namespace std;
using namespace ui;

bool TalkDetailHelpLayer::init()
{
    if(!Layer::init()) return false;

    zPos = 0;
    visibleSize = Director::getInstance()->getVisibleSize();
    visibleSize.height -= 100;
    ImageView* bgImage = ImageView::create("res/common/dlgback.png");
    bgImage->setAnchorPoint(Vec2(0, 0));
    bgImage->setPosition(Vec2(0, 0));
    this->addChild(bgImage);
    
    ImageView* helpTop = ImageView::create("res/talk/f_help_t.png");
    helpTop->setAnchorPoint(Vec2(0, 0));
    helpTop->setPosition(Vec2(0, visibleSize.height - 360));
    this->addChild(helpTop);
    
    ImageView* helpBottom = ImageView::create("res/talk/f_help_b.png");
    helpBottom->setAnchorPoint(Vec2(0, 0));
    helpBottom->setPosition(Vec2(0, 90));
    this->addChild(helpBottom);
    float profileX = (visibleSize.width - helpBottom->getContentSize().width)/2;

    string str = "相手の好みに合った返信をすると好感度が貯まっていきます。\n♡色がピンクに染まったら相手はあなたに首ったけですよ。";
    _topMessage = CCLabelTTF::create(str, kDEFAULT_BOLD_FONT, 26);
    _topMessage->setColor(Color3B::BLACK);
    _topMessage->setHorizontalAlignment(TextHAlignment::LEFT);
    _topMessage->setAnchorPoint(Vec2(0, 0));
    _topMessage->setPosition(Vec2(profileX + 40, helpTop->getPosition().y + 45));
    _topMessage->setDimensions(Size(Vec2(visibleSize.width - 80, 0)));
    this->addChild(_topMessage, zPos++);

    str = "ここをタップで返信内容の選択肢が表示されます。\n相手に好印象を与える返信を選びましょう。\nあなたのテクニックの見せ所ですね。";
    _bottomMessage = CCLabelTTF::create(str, kDEFAULT_BOLD_FONT, 26);
    _bottomMessage->setColor(Color3B::BLACK);
    _bottomMessage->setHorizontalAlignment(TextHAlignment::LEFT);
    _bottomMessage->setAnchorPoint(Vec2(0, 0));
    _bottomMessage->setPosition(Vec2(profileX + 40, helpBottom->getPosition().y + 70));
    _bottomMessage->setDimensions(Size(Vec2(visibleSize.width - 80, 0)));
    this->addChild(_bottomMessage, zPos++);
    
    return true;
};
