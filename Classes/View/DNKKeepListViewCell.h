//
//  DNKKeepListViewCell.h
//  Henshin
//
//  Created by Đinh Văn Nhật on 2014/09/12.
//  Copyright (c) 2014年 DNK. All rights reserved.
//

#ifndef __Henshin__DNKKeepListViewCell__
#define __Henshin__DNKKeepListViewCell__

#include "Cocos2d.h"
#include "cocos-ext.h"
#include "DNKCharacterInfo.h"
USING_NS_CC_EXT;

class DNKKeepListViewCell:public TableViewCell{
private:
public:
    DNKKeepListViewCell *initCell(bool isMe, DNKCharacterInfo *info, int chara_id);
};

#endif /* defined(__Henshin__DNKKeepListViewCell__) */
