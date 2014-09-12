//
//  DNKStoreData.h
//  Henshin
//
//  Created by Duong Minh Khoa on 9/6/14.
//  Copyright (c) 2014 DNK. All rights reserved.
//

#ifndef __Henshin__DNKStoreData__
#define __Henshin__DNKStoreData__

#include "cocos2d.h"
#include "DNKCharacterInfo.h"
using namespace std;

class StoreData
{
private:
    StoreData();
    static StoreData * _storeSingleton;
    map<int,DNKCharacterInfo*> _infoData;
    void loadData(int chara_id);
    
public:
    static StoreData * GetInstance();
    DNKCharacterInfo* GetData(int chara_id);
    string GetTalk(int chara_id, int talk_id,int option);
    string GetCharaNickName(int chara_id);
    
};

#endif /* defined(__Henshin__DNKStoreData__) */
