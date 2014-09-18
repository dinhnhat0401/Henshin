//
//  AppTableViewCell.cpp
//  Henshin
//
//  Created by hoangdieu on 9/7/14.
//  Copyright (c) 2014 DNK. All rights reserved.
//

#include "AppTableViewCell.h"
using namespace cocos2d::network;
USING_NS_CC;

AppCell *AppCell::init(vector<string> names, vector<string> imgs, vector<string> link,int idx)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    //    this->autorelease();
    
    // セルの背景
    auto bg = Sprite::create();
    bg->setAnchorPoint(Vec2(0, 0));
    bg->setTextureRect(Rect(0, 0, visibleSize.width, visibleSize.height*0.15));
    heightCell = (int)(visibleSize.height*0.15);
    int cl = 204;
    if(idx %2 == 0)
        cl = 229;
    bg->setColor(Color3B(204,255,cl));
    this->addChild(bg);
    num = idx;
    int max = 3;
    if ( names.size() < 3)
    {
        max = names.size();;
    }
    Point origin = Director::getInstance()->getVisibleOrigin();
    auto fileUtils = FileUtils::getInstance();
    for(int i = 0; i < max; i++)
    {
        string filenameofImg = imgs[i].substr(imgs[i].find_last_of("/")+1,imgs[i].size());

        std::string filename = fileUtils->getWritablePath()+"images/" + filenameofImg;
        listName.push_back(names[i]);
        listLinks.push_back(link[i]);
        filenames.push_back(filenameofImg);
    }
    
    /// add to sprite
    
    if(Application::getInstance()->checkInternetConnected())
    {
        for (int i=0; i < max; i++) {
            getSpriteURL(imgs[i].c_str());
        }
    }
    else
    {
        for (int i=0; i < max; i++) {
            
            Size visibleSize = Director::getInstance()->getVisibleSize();
            Point origin = Director::getInstance()->getVisibleOrigin();
            float widthDefault = 2*visibleSize.width/3 ;
            
            auto fileUtils = FileUtils::getInstance();
            //
            std::string filename = fileUtils->getWritablePath()+ "images/" +filenames[i];
            
            // check file existed ?
            if (fileUtils->isFileExist(filename)) {
                log("File name:%s",filename.c_str());
                auto sprite = Sprite::create(filename.c_str());
                
                MenuItemImage *btnApps = MenuItemImage::create(filename, filename,CC_CALLBACK_1(AppCell::clickApp,this));
                
                //            btnApps->setAnchorPoint(Vec2(0.5,0.5));
                //            sprite->setContentSize(Size(widthDefault, widthDefault));
                //            btnApps->setPosition(Point(origin.x+(2*index+1)*visibleSize.width/6, widthDefault/2));
                
                
                float spt_height = sprite->getContentSize().height;
                float spt_width = sprite->getContentSize().width;
                
                yAxis = heightCell-spt_height/2-10;
                
                btnApps->setContentSize(Size(spt_width,spt_height));
                btnApps->setTag(num*3+i);
                std::string gameName = "";
//
                if(listName[i].length() > 30)
                    gameName= listName[i].substr(0,27)+"...";
                else
                    gameName = listName[i];
                CCLabelTTF* title = CCLabelTTF::create(gameName, "Helvetica-Bold", 12);
                title->setColor(Color3B::BLACK);
                title->setHorizontalAlignment(TextHAlignment::CENTER);
                title->setVerticalAlignment(TextVAlignment::TOP);
                title->setAnchorPoint(Vec2(0,0.5));
                title->setPosition(Point(-15 , -15));
                title->setDimensions(Size(Vec2(spt_height+30, 0)));
                
                btnApps->addChild(title,2);
                auto menu1 = Menu::create(btnApps, NULL);
                menu1->setPosition(Point(origin.x+(2*i+1)*visibleSize.width/6, yAxis));
                this->addChild(menu1,2);
            }
        }
    }
    
    
    return this;
}
void AppCell::getSpriteURL (const char*url)
{
    auto request = new HttpRequest();
    
    request->setUrl(url);
    
    request->setRequestType(HttpRequest::Type::GET);
    
    request->setResponseCallback(this, httpresponse_selector(AppCell::onHttpRequestCompleted));
    
    network::HttpClient::getInstance()->send(request);
    request->release();
}
void AppCell::onHttpRequestCompleted(HttpClient* sender, HttpResponse* response)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    float widthDefault = 2*visibleSize.width/3 ;
    
    auto fileUtils = FileUtils::getInstance();
    // file name la dng dan tuyet doi roi, co can cai / khong
    std::string filename = fileUtils->getWritablePath()+ "images/" +filenames[index];
    // check file existed ?
    if (fileUtils->isFileExist(filename)) {
        
        auto sprite = Sprite::create(filename.c_str());
//        log("%s",filename.c_str());
        MenuItemImage *btnApps = MenuItemImage::create(filename, filename,CC_CALLBACK_1(AppCell::clickApp,this));
        
        //            btnApps->setAnchorPoint(Vec2(0.5,0.5));
        //            sprite->setContentSize(Size(widthDefault, widthDefault));
        //            btnApps->setPosition(Point(origin.x+(2*index+1)*visibleSize.width/6, widthDefault/2));
        
        
        float spt_height = sprite->getContentSize().height;
        float spt_width = sprite->getContentSize().width;
        
        yAxis = heightCell-spt_height/2-10;
        
        btnApps->setContentSize(Size(spt_width,spt_height));
        btnApps->setTag(num*3+index);
        std::string gameName = "ALCCL";
        
        if(listName[index].length() > 30)
            gameName= listName[index].substr(0,27)+"...";
        else
            gameName = listName[index];
        CCLabelTTF* title = CCLabelTTF::create(gameName, "Helvetica-Bold", 12);
        title->setColor(Color3B::BLACK);
        title->setHorizontalAlignment(TextHAlignment::CENTER);
        title->setVerticalAlignment(TextVAlignment::TOP);
        title->setAnchorPoint(Vec2(0,0.5));
        title->setPosition(Point(-15 , -15));
        title->setDimensions(Size(Vec2(spt_height+30, 0)));
        
        btnApps->addChild(title,2);
        auto menu1 = Menu::create(btnApps, NULL);
        menu1->setPosition(Point(origin.x+(2*index+1)*visibleSize.width/6, yAxis));
        this->addChild(menu1,2);
    }
    else
    {
        if (response->isSucceed()) {
            
            std::vector<char>* buffer = response->getResponseData();
            
            auto* img = new Image();
            
            img->initWithImageData(reinterpret_cast<unsigned char*>(&(buffer->front())), buffer->size());
            
            img->saveToFile(filename.c_str(),false);
            imgPath.push_back(filename);
            
            auto* texture = new Texture2D();
            
            texture->initWithImage(img);
            
            
            auto sprite = Sprite::createWithTexture(texture);
            
            MenuItemImage *btnApps = MenuItemImage::create(filename, filename,CC_CALLBACK_1(AppCell::clickApp,this));
            
//            btnApps->setAnchorPoint(Vec2(0.5,0.5));
//            sprite->setContentSize(Size(widthDefault, widthDefault));
//            btnApps->setPosition(Point(origin.x+(2*index+1)*visibleSize.width/6, widthDefault/2));
            
            btnApps->setTag(num*3+index);
            
            float spt_height = sprite->getContentSize().height;
            float spt_width = sprite->getContentSize().width;
            
            yAxis = heightCell-spt_height/2-10;
            
            btnApps->setContentSize(Size(spt_width,spt_height));
            
            std::string gameName = "";

            if(listName[index].length() > 30)
                gameName= listName[index].substr(0,27)+"...";
            else
                gameName = listName[index];
            CCLabelTTF* title = CCLabelTTF::create(gameName, "Helvetica-Bold", 12);
            title->setColor(Color3B::BLACK);
            title->setHorizontalAlignment(TextHAlignment::CENTER);
            title->setVerticalAlignment(TextVAlignment::TOP);
            title->setAnchorPoint(Vec2(0,0.5));
            title->setPosition(Point(-15 , -15));
            title->setDimensions(Size(Vec2(spt_height+30, 0)));
            
            btnApps->addChild(title,2);
            auto menu1 = Menu::create(btnApps, NULL);
            menu1->setPosition(Point(origin.x+(2*index+1)*visibleSize.width/6, yAxis));
            this->addChild(menu1,2);
        }
    }

    index++;
}

void AppCell::clickApp(cocos2d::Ref *pSender)
{
    MenuItemImage *btn = (MenuItemImage*) pSender;
    int tag = btn->getTag();
    int elm = tag%3;
    log("Links:%s",listLinks[elm].c_str());
    Application::getInstance()->openURL(listLinks[elm].c_str());
}