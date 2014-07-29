//
//  DNKCommon.cpp
//  Henshin
//
//  Created by Đinh Văn Nhật on 2014/07/28.
//  Copyright (c) 2014年 (THE) ONE of THEM. All rights reserved.
//

#include "DNKCommon.h"
USING_NS_CC;
float DNKCommon::calculateHeightOfLabel(string str, int fontSize, float width){
    float height = 0;
    CCLabelTTF* lbl = CCLabelTTF::create(str, "MSGothic", fontSize);
    lbl->setHorizontalAlignment(cocos2d::TextHAlignment::LEFT);
    lbl->setDimensions(Size(Vec2(width, 0)));
    //    log("width = %f %f", lbl->getContentSize().width, lbl->getContentSize().height);
    height = lbl->getContentSize().height;
    return height;
}

float DNKCommon::calculateHeightOfTalkCell(string str, int fontSize, float width){
    float height = DNKCommon::calculateHeightOfLabel(str,fontSize,width);
    height += 40; // padding * 2
    height += 100; // user name height
    return height;
}