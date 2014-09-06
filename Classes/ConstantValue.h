//
//  ConstantValue.h
//  Henshin
//
//  Created by duong minh khoa on 7/31/14.
//  Copyright (c) 2014 (THE) ONE of THEM. All rights reserved.
//

#ifndef Henshin_ConstantValue_h
#define Henshin_ConstantValue_h

class ConstValue
{
    public:
        static const int STATE_KEEP     = 1;
        static const int STATE_TALK     = 2;
        static const int STATE_OTHER    = 3;
        static const int STATE_GAME     = 4;
        static const int STATE_TALK_DETAIL = 5;
        static const int MENU_TAG = 0;
//        static const int TALKLIST_TAG = 1;
        constexpr static const float TIME_LINE_ITEM_RATE = 0.13f;
        static const int MEASSAGE_LIMIT = 30;
        static const int AD_HEIGHT = 100;
};


#endif
