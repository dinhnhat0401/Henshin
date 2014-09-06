//
//  DNKStoreData.cpp
//  Henshin
//
//  Created by Duong Minh Khoa on 9/6/14.
//  Copyright (c) 2014 DNK. All rights reserved.
//

#include "DNKStoreData.h"
#include "FilePlists.h"

StoreData* StoreData::_storeSingleton = NULL;

StoreData::StoreData()
{
}
StoreData * StoreData::GetInstance()
{
   if(_storeSingleton == NULL)
   {
       _storeSingleton = new StoreData();
   }
    return _storeSingleton;
};

void StoreData::loadData(int chara_id)
{
    FilePlists* plist = new FilePlists();
    string fileName = "chara_talk/chara_talk_" + to_string (chara_id) + ".plist";
    plist->readFile(fileName);
    DNKCharacterInfo* info = plist->getValues();
    _infoData[chara_id] = info;
}

DNKCharacterInfo * StoreData::GetData(int chara_id)
{
    if(_infoData.find(chara_id) == _infoData.end())
    {
        loadData(chara_id);
    }
    
    DNKCharacterInfo * info = _infoData[chara_id];
    return info;
}

string StoreData::GetTalk(int chara_id, int talk_id, int option)
{
    DNKCharacterInfo * info = GetData(chara_id);
    string mesg = (option == 0) ? info->getTalk()->getItem(talk_id)->getQuestion() :
        info->getTalk()->getItem(talk_id)->getOptions()->getSelection(option).getAnswer();
    return mesg;
}

string StoreData::GetCharaNickName(int chara_id)
{
    DNKCharacterInfo * info = GetData(chara_id);
    if(info != NULL)
    {
        return info->getNickName();
    }
    else return "No Name";
    
}


