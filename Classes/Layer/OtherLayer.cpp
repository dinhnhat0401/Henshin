//
//  OtherLayer.cpp
//  Henshin
//
//  Created by duong minh khoa on 7/30/14.
//  Copyright (c) 2014 (THE) ONE of THEM. All rights reserved.
//

#include "OtherLayer.h"

using namespace cocos2d::network;
USING_NS_CC;

bool Other::init()
{
//    Size visibleSize = Director::getInstance()->getVisibleSize();
//    Size s = Director::sharedDirector()->getWinSize();
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();
    int xCenter = origin.x + visibleSize.width/2;
    int yCenter = origin.y + visibleSize.height/2;
    
    tbv = TableView::create(this, visibleSize);
    tbv->setPosition(-xCenter,-yCenter);
    tbv->setVerticalFillOrder(TableView::VerticalFillOrder::BOTTOM_UP);
    tbv->setDirection(TableView::Direction::VERTICAL);
    tbv->setBounceable(false);
    tbv->setDelegate(this);
    
    this->addChild(tbv);
    tbv->reloadData();    return true;
};

void Other::initTableView(Size size)
{
    tbv = TableView::create(this, size);
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    tbv->setPosition(0,visibleSize.height/2 - size.height/2);
    tbv->setVerticalFillOrder(TableView::VerticalFillOrder::BOTTOM_UP);
    tbv->setDirection(TableView::Direction::VERTICAL);
    tbv->setBounceable(false);
    tbv->setDelegate(this);
    
    this->addChild(tbv);
    tbv->reloadData();
};

Size Other::cellSizeForTable(TableView *table){
    Size visibleSize = Director::getInstance()->getVisibleSize();
    return Size(visibleSize.width, visibleSize.height* ConstValue::TIME_LINE_ITEM_RATE);
};

TableViewCell* Other::tableCellAtIndex(TableView *table, ssize_t idx){
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    TableViewCell *cell = table->dequeueCell();
    cell = new TableViewCell();
    cell->autorelease();
    
    // セルの背景
    auto bg = Sprite::create();
    bg->setAnchorPoint(Vec2(0, 0));
    bg->setTextureRect(Rect(0, 0, visibleSize.width, visibleSize.height*.2));
    bg->setColor(Color3B(230,230,230));
    cell->addChild(bg);
    
    // ボーダーライン
    auto line = Sprite::create();
    line->setAnchorPoint(Vec2(0, 0));
    line->setTextureRect(Rect(0, 0, visibleSize.width, 1));
    line->setColor(Color3B(100,100,100));
    cell->addChild(line);
    
    // テキスト
    auto text = StringUtils::format("Cell %zd", idx);
    auto label = Label::createWithSystemFont(text.c_str(), "Arial", 30);
    label->setAnchorPoint(Vec2(0, 0.5));
    label->setPosition(Vec2(50, visibleSize.height*.1));
    label->setColor(Color3B(100,100,100));
    cell->addChild(label);
    
    return cell;
}

ssize_t Other::numberOfCellsInTableView(TableView *table){
    return 8;
}


void  Other::tableCellTouched(TableView* table, TableViewCell* cell){
    printf("%zd番目がタップされました", cell->getIdx());
    
}


//////////////load data from url
bool Other::getContentURL(const char *url)
{
    auto request = new HttpRequest();
    
    request->setUrl(url);
    
    request->setRequestType(HttpRequest::Type::GET);
    
    request->setResponseCallback(this, httpresponse_selector(Other::onHttpRequestCompleted));
    
    network::HttpClient::getInstance()->send(request);
    return true;
}

void Other::onHttpRequestCompleted(HttpClient* sender, HttpResponse* response)
{
    if (response->isSucceed()) {
        
        std::vector<char>* buffer = response->getResponseData();
        
        char divTag[] = "<section class=\"section apps grid\">";
        char ulTag[] = "<ul>";
        char endTag[] = "</ul>";
        
        char liTag[] = "<li>";
        char eliTag[] = "</li>";
        
        bool appStatus = false;
        
//        char out[buffer->size()];
        bool startUl = false;
        bool startli = false;
        bool startLink = false;
        bool startImg = false;
        bool startName = false;
        
        cocos2d::CCString *str = cocos2d::CCString::create("");
        for (unsigned int i = 0; i < buffer->size(); i++) {
            if(!appStatus)
            {
                if(std::strstr(str->getCString(),divTag) !=NULL)
                {
                    
                    str = cocos2d::CCString::create("");
                    appStatus = true;
                }
            }
            else if(!startUl)
            {
                if(std::strstr(str->getCString(),ulTag) !=NULL)
                {
                    startUl = true;
                    str = cocos2d::CCString::create("");
                }
            }
            else
            {
                if(std::strstr(str->getCString(),endTag) !=NULL)
                {
                    break;
                }
                else if(std::strstr(str->getCString(),liTag) != NULL)
                {
                    startli = true;
                    str = cocos2d::CCString::create("");
                }
                else
                {
                    if(std::strstr(str->getCString(),eliTag) != NULL)
                    {
                        startli = false;
                        str = cocos2d::CCString::create("");
                    }
                }
            }
            
            if(startli)
            {
                //catch link
                if(std::strstr(str->getCString(),"<a href=\"") != NULL)
                {
                    startLink = true;
                    str = cocos2d::CCString::create("");
                }
                if (startLink) {
                    if (std::strstr(str->getCString(),"\">") != NULL) {
                        startLink = false;
                        
                        const char *link = str->getCString();
                        std::string link1(link);
                        link1.replace(link1.end()-2, link1.end(), "");
                        links.push_back(link1);
                        
                    }
                }
                else if (std::strstr(str->getCString(),"<img src=\"") != NULL)
                {
                    startImg = true;
                    str = cocos2d::CCString::create("");
                }
                
                if(startImg)
                {
                    if (std::strstr(str->getCString(),"\" width") != NULL) {
                        startImg = false;
                        std::string img(str->getCString());
                        img.replace(img.end()-7, img.end(), "");
                        imgs.push_back(img);
                        str = cocos2d::CCString::create("");
                        //                            startli = false;
                    }
                }
                else
                {
                    if (std::strstr(str->getCString(),"alt=\"") != NULL)
                    {
                        startName = true;
                        str = cocos2d::CCString::create("");
                    }
                }
                
                if(startName)
                {
                    if (std::strstr(str->getCString(),"\">") != NULL)
                    {
                        startName = false;
                        std::string name(str->getCString());
                        name.replace(name.end()-2, name.end(), "");
                        names.push_back(name);
                        startli = false;
                    }
                }
            }
            
            str->appendWithFormat("%c",buffer->at(i));
            
        }
        
        for (int i=0; i < links.size();i++)
        {
            log("%s",links[i].c_str());
        }
        
    }
}