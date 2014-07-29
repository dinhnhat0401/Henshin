//
//  DNKMyChatTableviewCell.h
//  Henshin
//
//  Created by Đinh Văn Nhật on 2014/07/26.
//  Copyright (c) 2014年 (THE) ONE of THEM. All rights reserved.
//

#ifndef Henshin_DNKMyChatTableviewCell_h
#define Henshin_DNKMyChatTableviewCell_h
#include "DNKSelection.h"
#include "Cocos2d.h"
#include "cocos-ext.h"
#include <UIImageView.h>
USING_NS_CC_EXT;

class DNKMyChatTableViewCell:public TableViewCell{
private:
    cocos2d::ui::ImageView* myIcon;
public:
    DNKMyChatTableViewCell* initCell(DNKSelection selection);
};

#endif
