//
//  AppTableViewCell.h
//  Henshin
//
//  Created by hoangdieu on 9/7/14.
//  Copyright (c) 2014 DNK. All rights reserved.
//

#ifndef __Henshin__AppTableViewCell__
#define __Henshin__AppTableViewCell__

#include "cocos2d.h"
#include "cocos-ext.h"

#include "network/HttpClient.h"
#include <string>

USING_NS_CC_EXT;
using namespace std;

class AppCell: public TableViewCell
{
private:
    vector<string> imgPath;
    vector<string> filenames;
    vector<string> listName;
    vector<string> listLinks;
    bool status = false;
    int index = 0;
    int num = 0;
    int heightCell = 150;
    int yAxis = 0;
public:
    AppCell *init(vector<string>,vector<string>,vector<string>,int);
    void getSpriteURL (const char*);
    void onHttpRequestCompleted(cocos2d::network::HttpClient* sender,
                                cocos2d::network::HttpResponse* response);
    void clickApp(Ref* pSender);
};

#endif /* defined(__Henshin__AppTableViewCell__) */
