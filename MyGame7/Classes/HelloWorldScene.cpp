/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "ComMove.h"

USING_NS_CC;

float x, y;
Sprite* tw;
Sprite* mt;
Sprite* ms;
int cntMon = 0;
int cntMs = 10;
std::vector<Point> path;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


//绘制瓦片地图
    /*Sprite* bg = Sprite::create("background.png");
    bg->setPosition(visibleSize / 2);
    addChild(bg);

    TMXTiledMap* map = TMXTiledMap::create("map01.tmx");
    map->setPosition(Point::ZERO);
    addChild(map);*/


//怪物按指定路线行走
    /*Sprite* bg = Sprite::create("background.png");
    bg->setPosition(visibleSize / 2);
    addChild(bg);

    TMXTiledMap* map = TMXTiledMap::create("map01.tmx");
    map->setPosition(Point::ZERO);
    addChild(map);

    Sprite* mt = Sprite::create("Monster.png");
    mt->setPosition(visibleSize / 2);
    addChild(mt);

    TMXObjectGroup* tog = map->getObjectGroup("walk");
    ValueVector  vv = tog->getObjects();
    std::vector<Point > path;
    for (auto pos : vv)
        path.push_back(Point(pos.asValueMap()["x"].asInt(), pos.asValueMap()["y"].asInt()));
    mt->setPosition(path[0]);
    Vector<FiniteTimeAction*> fta;
    for (int i = 1; i < path.size(); i++)
        fta.pushBack(MoveTo::create(5, path[i]));
    Sequence* sp = Sequence::create(fta);
    mt->runAction(sp);*/


//设置武器站
    /*Sprite* bg = Sprite::create("background.png");
    bg->setPosition(visibleSize / 2);
    addChild(bg);

    TMXTiledMap* map = TMXTiledMap::create("map01.tmx");
    map->setPosition(Point::ZERO);
    addChild(map);

    TMXLayer* t1 = map->getLayer("weapon");
    int idTile = t1->getTileGIDAt(Vec2(x, y));
    if (idTile != 0)
    {
        Value p = map->getPropertiesForGID(idTile);
        if ("allow" == (p.asValueMap().find("build"))->second.asString())
        {
            tw = Sprite::create("Tower.png");
            tw->setPosition(Vec2(x, y));
            addChild(tw);
        }

        else
            log("　此处不能建站！　");
    }*/


//使用构造函数创建组件
    /*Sprite* bg = Sprite::create("background.png");
    bg->setPosition(visibleSize / 2);
    addChild(bg);

    TMXTiledMap* map = TMXTiledMap::create("map01.tmx");
    map->setPosition(Point::ZERO);
    addChild(map);

    Sprite* mt = Sprite::create("Monster.png");
    mt->setPosition(visibleSize / 2);
    addChild(mt);

    TMXObjectGroup* tog = map->getObjectGroup("walk");
    ValueVector  vv = tog->getObjects();
    std::vector<Point > path;
    for (auto pos : vv)
        path.push_back(Point(pos.asValueMap()["x"].asInt(), pos.asValueMap()["y"].asInt()));
    
    CMyCom* myCom = new CMyCom(path);
    mt->addComponent(myCom);
    myCom->startMove();*/


//实现组件的create方法
    Sprite* bg = Sprite::create("background.png");
    bg->setPosition(visibleSize / 2);
    addChild(bg);

    TMXTiledMap* map = TMXTiledMap::create("map01.tmx");
    map->setPosition(Point::ZERO);
    addChild(map);

    TMXObjectGroup* tog = map->getObjectGroup("walk");
    ValueVector  vv = tog->getObjects();
    
    for (auto pos : vv)
        path.push_back(Point(pos.asValueMap()["x"].asInt(), pos.asValueMap()["y"].asInt()));

    schedule(CC_SCHEDULE_SELECTOR(HelloWorld::wavePlay), 1);
    


//



    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

void HelloWorld::monMove(float dt)
{
    Size VisibleSize = Director::getInstance()->getVisibleSize();
    CMyCom* myCom = new CMyCom(path);
    if (cntMon % 20 < 10)
    {
        mt = Sprite::create("Monster.png");
        addChild(mt);
        mt->addComponent(myCom);
        myCom->startMove();
    }
    cntMon++;
    cntMs++;
}

void HelloWorld::msMove(float dt)
{
    Size VisibleSize = Director::getInstance()->getVisibleSize();
    CMyCom* myCom = new CMyCom(path);
    if (cntMs % 20 < 10)
    {
        ms = Sprite::create("Mushroom01A.png");
        addChild(ms);
        ms->addComponent(myCom);
        myCom->startMove();
    }
    cntMon++;
    cntMs++;
}

void HelloWorld::wavePlay(float dt)
{
    if (cntMon % 20 < 10)
        schedule(CC_SCHEDULE_SELECTOR(HelloWorld::monMove), 0.3f);
    if (cntMs % 20 < 10)
        schedule(CC_SCHEDULE_SELECTOR(HelloWorld::msMove), 0.3f);
}
