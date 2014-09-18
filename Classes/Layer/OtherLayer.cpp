//
//  OtherLayer.cpp
//  Henshin
//
//  Created by duong minh khoa on 7/30/14.
//  Copyright (c) 2014 (THE) ONE of THEM. All rights reserved.
//

#include "OtherLayer.h"
#include <stdlib.h>
using namespace cocos2d::network;
USING_NS_CC;

bool Other::init()
{
    if(!Layer::init()) return false;
    Size visibleSize = Director::getInstance()->getVisibleSize();
    if ( !cocos2d::CCLayerColor::initWithColor(Color4B(255, 255, 255, 255)))
    {
        return false;
    }
//    auto bg = Sprite::create();
//    bg->setAnchorPoint(Vec2(0, 0));
//    bg->setTextureRect(Rect(0, 0, visibleSize.width, visibleSize.height));
//    bg->setColor(Color3B(255,255,255));
//    this->addChild(bg,0);
    
    return true;
};

void Other::initTableView(Size size)
{
    tbv = TableView::create(this, size);
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    tbv->setPosition(0,visibleSize.height/2 - size.height/2);
    tbv->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    tbv->setDirection(TableView::Direction::VERTICAL);
    tbv->setBounceable(false);
    tbv->setDelegate(this);
    
    this->addChild(tbv);
    tbv->reloadData();
    this->loadData("https://www.apple.com/itunes/charts/paid-apps/");
};

Size Other::cellSizeForTable(TableView *table){
    Size visibleSize = this->getContentSize();
    return Size(visibleSize.width, visibleSize.height*0.15);
};

TableViewCell* Other::tableCellAtIndex(TableView *table, ssize_t idx){
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    AppCell *cell = (AppCell*)table->dequeueCell();
    cell = new AppCell();
    cell->init(listNames[idx], listImgs[idx], listLinks[idx],idx);
    cell->autorelease();
    
    return cell;
}

ssize_t Other::numberOfCellsInTableView(TableView *table){
    return listNames.size();
}


void  Other::tableCellTouched(TableView* table, TableViewCell* cell){
//    printf("%zd番目がタップされました", cell->getIdx());
    
}

///load data
void Other::loadData (const char *url)
{
    if(Application::getInstance()->checkInternetConnected())
    {
        log("Internet connected!");
        this->getContentURL(url);
    }
    else
    {
        
        log("Internet can't connect!");
        FilePlists *file = new FilePlists();
        std::string _path = CCFileUtils::sharedFileUtils()->getWritablePath();
        _path.append ("dataOther.plist");
        
        file->readFile(_path);
        log("So phan tu %d",file->getSize()/3);
//        cocos2d::UserDefault* dataFile = cocos2d::UserDefault::sharedUserDefault();
        
        int size = file->getSize()/3;
        if(size == 0 )
            return;
        
        int num = (int)(size-1)/3;
        for (int i = 0; i < num; i++)
        {
            vector<string> nameTmp;
            
            string name_key = "appnames-"+to_string(i*3);
            string name_key1 = "appnames-"+to_string(i*3+1);
            string name_key2 = "appnames-"+to_string(i*3+2);
            
            nameTmp.push_back (file->getValueStdString(name_key));
            nameTmp.push_back (file->getValueStdString(name_key1));
            nameTmp.push_back (file->getValueStdString(name_key2));
            
        
            
            vector<string> imgTmp;
            
            
            string img_key = "appimgs-"+to_string(i*3);
            string img_key1 = "appimgs-"+to_string(i*3+1);
            string img_key2 = "appimgs-"+to_string(i*3+2);
            
//            log("%s",file->getValueStdString(img_key).c_str());
            
            imgTmp.push_back (file->getValueStdString(img_key));
            imgTmp.push_back (file->getValueStdString(img_key1));
            imgTmp.push_back (file->getValueStdString(img_key2));
            
            //log
            log("Hinh anh::%s",file->getValueStdString(img_key).c_str());
            log("Hinh anh::%s",file->getValueStdString(img_key1).c_str());
            log("Hinh anh::%s",file->getValueStdString(img_key2).c_str());
            
            vector<string> linkTmp;
            
            string link_key = "applinks-"+to_string(i*3);
            string link_key1 = "applinks-"+to_string(i*3+1);
            string link_key2 = "applinks-"+to_string(i*3+2);
            
            linkTmp.push_back (file->getValueStdString(link_key));
            linkTmp.push_back (file->getValueStdString(link_key1));
            linkTmp.push_back (file->getValueStdString(link_key2));
            
            listLinks.push_back(linkTmp);
            listImgs.push_back(imgTmp);
            listNames.push_back(nameTmp);
        }
        vector<string> nameTmp1;
        vector<string> imgTmp1;
        vector<string> linkTmp1;
        for (int i= num*3; i <size-1; i++) {
            
            string name_key = "appnames-"+to_string(i);
            
            nameTmp1.push_back (file->getValueStdString(name_key));
            
            string img_key = "appimgs-"+to_string(i);
            
            imgTmp1.push_back (file->getValueStdString(img_key));
            
            string link_key = "applinks-"+to_string(i);
            linkTmp1.push_back (file->getValueStdString(link_key));
        }
        
        listLinks.push_back(linkTmp1);
        listImgs.push_back(imgTmp1);
        listNames.push_back(nameTmp1);
        tbv->reloadData();
    }
    
}

//////////////load data from url
bool Other::getContentURL(const char *url)
{
    auto request = new HttpRequest();
    
    request->setUrl(url);
    
    request->setRequestType(HttpRequest::Type::GET);
    
    request->setResponseCallback(this, httpresponse_selector(Other::onHttpRequestCompleted));
    
    network::HttpClient::getInstance()->send(request);
    request->release();
    return true;
}

void Other::onHttpRequestCompleted(HttpClient* sender, HttpResponse* response)
{
    int num = 0;
    if (response->isSucceed()) {
        
        std::vector<char>* buffer = response->getResponseData();
        
        char divTag[] = "<section class=\"";
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
                        num++;
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
            if(num > 20)
                break;
            str->appendWithFormat("%c",buffer->at(i));
            
        }
        
        /// get list;
        int size = links.size();
        log("sizeD %d",size);
        if(size== 0)
        {
            FilePlists *file = new FilePlists();
            std::string _path = CCFileUtils::sharedFileUtils()->getWritablePath();
            _path.append ("dataOther.plist");
            
            file->readFile(_path);
            size = file->getSize()/3;
            if(size == 0 )
                return;
            
            int num = (int)(size-1)/3;
            for (int i = 0; i < num; i++)
            {
                vector<string> nameTmp;
                
                string name_key = "appnames-"+to_string(i*3);
                string name_key1 = "appnames-"+to_string(i*3+1);
                string name_key2 = "appnames-"+to_string(i*3+2);
                
                nameTmp.push_back (file->getValueStdString(name_key));
                nameTmp.push_back (file->getValueStdString(name_key1));
                nameTmp.push_back (file->getValueStdString(name_key2));
                
                vector<string> imgTmp;
                
                //save img
                string img_key = "appimgs-"+to_string(i*3);
                string img_key1 = "appimgs-"+to_string(i*3+1);
                string img_key2 = "appimgs-"+to_string(i*3+2);
                
                imgTmp.push_back (file->getValueStdString(img_key));
                imgTmp.push_back (file->getValueStdString(img_key1));
                imgTmp.push_back (file->getValueStdString(img_key2));
                
                vector<string> linkTmp;
                
                string link_key = "applinks-"+to_string(i*3);
                string link_key1 = "applinks-"+to_string(i*3+1);
                string link_key2 = "applinks-"+to_string(i*3+2);
                
                linkTmp.push_back (file->getValueStdString(link_key));
                linkTmp.push_back (file->getValueStdString(link_key1));
                linkTmp.push_back (file->getValueStdString(link_key2));
                
                listLinks.push_back(linkTmp);
                listImgs.push_back(imgTmp);
                listNames.push_back(nameTmp);
            }
            vector<string> nameTmp1;
            vector<string> imgTmp1;
            vector<string> linkTmp1;
            for (int i= num*3; i <size-1; i++) {
                
                string name_key = "appnames-"+to_string(i);
                
                nameTmp1.push_back (file->getValueStdString(name_key));
                
                string img_key = "appimgs-"+to_string(i);
                
                imgTmp1.push_back (file->getValueStdString(img_key));
                
                string link_key = "applinks-"+to_string(i);
                linkTmp1.push_back (file->getValueStdString(link_key));
            }
            
            listLinks.push_back(linkTmp1);
            listImgs.push_back(imgTmp1);
            listNames.push_back(nameTmp1);
            
            return;
        }
        else
        {
            //luu data
        
            
            CCDictionary * datas = new CCDictionary();
            int num = (int)(size-1)/3;
            for (int i = 0; i < num; i++)
            {
                vector<string> nameTmp;
                nameTmp.push_back (names[i*3]);
                nameTmp.push_back (names[i*3+1]);
                nameTmp.push_back (names[i*3+2]);
                
                //save names
                string name_key = "appnames-"+to_string(i*3);
                string name_key1 = "appnames-"+to_string(i*3+1);
                string name_key2 = "appnames-"+to_string(i*3+2);
                
                datas->setObject(CCString::createWithFormat("%s",names[i*3].c_str()), name_key);
                datas->setObject(CCString::createWithFormat("%s",names[i*3+1].c_str()), name_key1);
                datas->setObject(CCString::createWithFormat("%s",names[i*3+2].c_str()), name_key2);
                
                vector<string> imgTmp;
                imgTmp.push_back (imgs[i*3]);
                imgTmp.push_back (imgs[i*3+1]);
                imgTmp.push_back (imgs[i*3+2]);
                
                
                //save img
                string img_key = "appimgs-"+to_string(i*3);
                string img_key1 = "appimgs-"+to_string(i*3+1);
                string img_key2 = "appimgs-"+to_string(i*3+2);
                
                datas->setObject(CCString::createWithFormat("%s",imgs[i*3].c_str()), img_key);
                datas->setObject(CCString::createWithFormat("%s",imgs[i*3+1].c_str()), img_key1);
                datas->setObject(CCString::createWithFormat("%s",imgs[i*3+2].c_str()), img_key2);
                
                vector<string> linkTmp;
                linkTmp.push_back (links[i*3]);
                linkTmp.push_back (links[i*3+1]);
                linkTmp.push_back (links[i*3+2]);
                
                
                //save link
                string link_key = "applinks-"+to_string(i*3);
                string link_key1 = "applinks-"+to_string(i*3+1);
                string link_key2 = "applinks-"+to_string(i*3+2);
                
                datas->setObject(CCString::createWithFormat("%s",links[i*3].c_str()), link_key);
                datas->setObject(CCString::createWithFormat("%s",links[i*3+1].c_str()), link_key1);
                datas->setObject(CCString::createWithFormat("%s",links[i*3+2].c_str()), link_key2);
                
                listLinks.push_back(linkTmp);
                listImgs.push_back(imgTmp);
                listNames.push_back(nameTmp);
            }
            vector<string> nameTmp1;
            vector<string> imgTmp1;
            vector<string> linkTmp1;
            for (int i= num*3; i <size-1; i++) {
                
                nameTmp1.push_back (names[i]);
                
                string name_key = "appnames-"+to_string(i);
                datas->setObject(CCString::createWithFormat("%s",names[i].c_str()), name_key);

                imgTmp1.push_back (imgs[i]);
                
                //save img
                string img_key = "appimgs-"+to_string(i);
                datas->setObject(CCString::createWithFormat("%s",imgs[i].c_str()), img_key);
                
                linkTmp1.push_back (links[i]);
                //save img
                string link_key = "applinks-"+to_string(i);
                datas->setObject(CCString::createWithFormat("%s",links[i].c_str()), link_key);
            }
            
            std::string _path = CCFileUtils::sharedFileUtils()->getWritablePath();
            _path.append ("dataOther.plist");
            if( datas->writeToFile(_path.c_str()))
            {
                log("OK");
            }
            else
                log("KO!:D");
            listLinks.push_back(linkTmp1);
            listImgs.push_back(imgTmp1);
            listNames.push_back(nameTmp1);
        }
        tbv->reloadData();
    }
}

void Other::setHeight(int h1,int h2)
{
    headerHeight = h1;
    footerHeight = h2;
}