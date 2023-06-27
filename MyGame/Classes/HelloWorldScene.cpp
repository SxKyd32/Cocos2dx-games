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

USING_NS_CC;

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

//// 解决中文乱码
//char* HelloWorld::FontToUTF8(const char* font)
//    {
//        int len = MultiByteToWideChar(CP_ACP, 0, font, -1, NULL, 0);
//        wchar_t* wstr = new wchar_t[len + 1];
//        memset(wstr, 0, len + 1);
//        MultiByteToWideChar(CP_ACP, 0, font, -1, wstr, len);
//        len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
//        char* str = new char[len + 1];
//        memset(str, 0, len + 1);
//        WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
//        if (wstr)
//            delete[] wstr;
//        return str;
//    }


// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    // 设定背景颜色
    LayerColor* lc = LayerColor::create(Color4B::GRAY);
    addChild(lc);

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    //auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    //if (label == nullptr)
    //{
    //    problemLoading("'fonts/Marker Felt.ttf'");
    //}
    //else
    //{
    //    // position the label on the center of the screen
    //    label->setPosition(Vec2(origin.x + visibleSize.width/2,
    //                            origin.y + visibleSize.height - label->getContentSize().height));

    //    // add the label as a child to this layer
    //    this->addChild(label, 1);
    //}

    // add "HelloWorld" splash screen"
    //auto sprite = Sprite::create("HelloWorld.png");
    //if (sprite == nullptr)
    //{
    //    problemLoading("'HelloWorld.png'");
    //}
    //else
    //{
    //    // position the sprite on the center of the screen
    //    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    //    // add the sprite as a child to this layer
    //    this->addChild(sprite, 0);
    //}


// 锚点的设置
    /*Sprite* sp2 = Sprite::create("pomegranateA.png");
    sp2->setAnchorPoint(Point(0, 0));
    sp2->setPosition(0, 0);
    addChild(sp2);*/

// 使用Texture2D创建Sprite对象
    /*Texture2D* texture = (Sprite::create("pomegranateA.png"))->getTexture();
    Sprite* sp2 = Sprite::createWithTexture(texture);
    sp2->setPosition(visibleSize / 2);
    addChild(sp2);*/

// 批量渲染
    //for (int i = 0; i < 10000; i++)     // 不使用批量渲染
    //{
    //    Sprite* sp = Sprite::create("CloseNormal.png");
    //    sp->setPosition(rand() % (int)visibleSize.width, rand() % (int)visibleSize.height);
    //    addChild(sp);
    //}

    //SpriteBatchNode* sbn = SpriteBatchNode::create("CloseNormal.png", 10000);   //使用批量渲染
    //sbn->setPosition(0, 0);
    //addChild(sbn);
    //for (int i = 0; i < 10000; i++)
    //{
    //    Sprite* sp = Sprite::createWithTexture(sbn->getTexture());
    //    sp->setPosition(rand() % (int)visibleSize.width, rand() % (int)visibleSize.height);
    //    sbn->addChild(sp);
    //}


// 拼装摩托车
    /*Sprite* sp1 = Sprite::create("motorWheel.png");
    sp1->setAnchorPoint(Point(0, 0));
    sp1->setPosition(0, 0);
    addChild(sp1);

    Sprite* sp2 = Sprite::create("motorWheel.png");
    sp2->setAnchorPoint(Point(0, 0));
    sp2->setPosition(206, 0);
    sp1->addChild(sp2);

    Sprite* sp = Sprite::create("motorBody.png");
    sp->setAnchorPoint(Point(0, 0));
    sp->setPosition(0, 0);
    sp1->addChild(sp);*/



// 使用位图字体输出文字
    //Label* la3 = Label::createWithBMFont("fonts/myfont1.fnt", "LETS.FNT");
    //la3->setPosition(visibleSize / 2);
    //// la3->setColor(Color3B::RED);
    //addChild(la3);


// 使用LabelAtlas输入文字 
   /* LabelAtlas* la4 = LabelAtlas::create("2333323333", "fonts/Number05100A.png", 48, 100, '1');
    la4->setPosition(visibleSize.width / 2 - 250, visibleSize.height / 2 + 50);
    addChild(la4);*/
    
 // 课堂练习：恐龙
    //// 恐龙图片
    //Sprite* sp = Sprite::create("dragon.png");
    //sp->setPosition(visibleSize / 2);
    //addChild(sp);

    //// 底部字体
    //Label* la = Label::createWithBMFont("fonts/myfont2.fnt", "QQ Dragon Boom");
    //la->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 280);
    //// la->setColor(Color3B::RED);
    //addChild(la);

    //// 部件说明
    //Label* la1 = Label::createWithSystemFont("eyes", "宋体", 20);     // 眼睛
    //la1->setColor(Color3B::BLACK);
    //la1->setPosition(210, 440);
    //addChild(la1);

    //Label* la2 = Label::createWithSystemFont("head", "宋体", 20);     // 头
    //la2->setColor(Color3B::BLACK);
    //la2->setPosition(270, 470);
    //addChild(la2);

    //Label* la3 = Label::createWithSystemFont("beard1", "宋体", 20);     // 胡须1
    //la3->setColor(Color3B::BLACK);
    //la3->setPosition(205, 400);
    //addChild(la3);

    //Label* la4 = Label::createWithSystemFont("beard2", "宋体", 20);     // 胡须2
    //la4->setColor(Color3B::BLACK);
    //la4->setPosition(500, 400);
    //addChild(la4);

    //Label* la5 = Label::createWithSystemFont("jaw", "宋体", 20);     // 下巴
    //la5->setColor(Color3B::BLACK);
    //la5->setPosition(210, 360);
    //addChild(la5);

    //Label* la6 = Label::createWithSystemFont("neck", "宋体", 20);     // 颈部
    //la6->setColor(Color3B::BLACK);
    //la6->setPosition(380, 350);
    //addChild(la6);

    //Label* la7 = Label::createWithSystemFont("hair", "宋体", 20);     // 头发
    //la7->setColor(Color3B::BLACK);
    //la7->setPosition(500, 450);
    //addChild(la7);

    //Label* la8 = Label::createWithSystemFont("body", "宋体", 20);     // 身体
    //la8->setColor(Color3B::BLACK);
    //la8->setPosition(400, 320);
    //addChild(la8);

    //Label* la9 = Label::createWithSystemFont("claw1", "宋体", 20);     // 前爪1
    //la9->setColor(Color3B::BLACK);
    //la9->setPosition(170, 310);
    //addChild(la9);

    //Label* la10 = Label::createWithSystemFont("claw2", "宋体", 20);     // 前爪2
    //la10->setColor(Color3B::BLACK);
    //la10->setPosition(520, 305);
    //addChild(la10);

    //Label* la11 = Label::createWithSystemFont("forearm1", "宋体", 20);     // 前臂1
    //la11->setColor(Color3B::BLACK);
    //la11->setPosition(180, 270);
    //addChild(la11);

    //Label* la12 = Label::createWithSystemFont("forearm2", "宋体", 20);     // 前臂2
    //la12->setColor(Color3B::BLACK);
    //la12->setPosition(460, 270);
    //addChild(la12);

    //Label* la13 = Label::createWithSystemFont("backarm1", "宋体", 20);     // 后臂1
    //la13->setColor(Color3B::BLACK);
    //la13->setPosition(230, 290);
    //addChild(la13);

    //Label* la14 = Label::createWithSystemFont("backarm2", "宋体", 20);     // 后臂2
    //la14->setColor(Color3B::BLACK);
    //la14->setPosition(450, 300);
    //addChild(la14);

    //Label* la15 = Label::createWithSystemFont("leg1", "宋体", 20);     // 后爪1
    //la15->setColor(Color3B::BLACK);
    //la15->setPosition(220, 150);
    //addChild(la15);

    //Label* la16 = Label::createWithSystemFont("leg2", "宋体", 20);     // 后爪2
    //la16->setColor(Color3B::BLACK);
    //la16->setPosition(330, 140);
    //addChild(la16);

    //Label* la17 = Label::createWithSystemFont("tail", "宋体", 20);     // 尾巴
    //la17->setColor(Color3B::BLACK);
    //la17->setPosition(550, 160);
    //addChild(la17);

    //Label* la18 = Label::createWithSystemFont("fine", "宋体", 20);     // 尾巴毛
    //la18->setColor(Color3B::BLACK);
    //la18->setPosition(480, 240);
    //addChild(la18);

    //Label* la19 = Label::createWithSystemFont("end", "宋体", 20);     // 尾巴尖
    //la19->setColor(Color3B::BLACK);
    //la19->setPosition(640, 240);
    //addChild(la19);

    //Label* la20 = Label::createWithSystemFont("clothes", "宋体", 20);     // 衣服
    //la20->setColor(Color3B::BLACK);
    //la20->setPosition(610, 370);
    //addChild(la20);

// 直接使用图片序列实现动画
    /*Vector<SpriteFrame*> a;
    Sprite* sp1 = Sprite::create();
    for (int i = 1; i <= 8; i++)
    {
        char filename[30];
        sprintf_s(filename, "J20%d.png", i);
        a.pushBack(Sprite::create(filename)->getSpriteFrame());
    }
    Animation* anim = Animation::createWithSpriteFrames(a, 0, 125);
    sp1->setPosition(visibleSize.width / 5, visibleSize.height / 2);
    sp1->runAction(RepeatForever::create(Animate::create(anim)));
    addChild(sp1);*/
    
// 使用SpriteFrameCache制作动画
    /*SpriteFrameCache* sfc = SpriteFrameCache::getInstance();
    for (int i = 1; i <= 12; i++)
    {
        char fname[30];
        char name[10];
        sprintf_s(fname, "ERA0%d.png", i);
        sprintf_s(name, "e%d", i);
        sfc->addSpriteFrame(Sprite::create(fname)->getSpriteFrame(), name);
    }
    Sprite* sp2 = Sprite::createWithSpriteFrame(sfc->getSpriteFrameByName("e1"));
    sp2->setPosition(visibleSize.width * 4 / 5, visibleSize.height / 2);
    addChild(sp2);
    Vector<SpriteFrame*> vector;
    for (int i = 1; i <= 12; i++)
    {
        char name[10];
        sprintf_s(name, "e%d", i);
        vector.pushBack(sfc->getSpriteFrameByName(name));
    }
    Animation* anim2 = Animation::createWithSpriteFrames(vector, 0.1f);
    sp2->runAction(RepeatForever::create(Animate::create(anim2)));*/


    /*auto frame1 = SpriteFrame::create("ERA01.png", Rect(0, 0, 240, 365));
    auto frame2 = SpriteFrame::create("ERA02.png", Rect(0, 0, 240, 365));
    auto frame3 = SpriteFrame::create("ERA03.png", Rect(0, 0, 240, 365));
    auto frame4 = SpriteFrame::create("ERA04.png", Rect(0, 0, 240, 365));
    auto frame5 = SpriteFrame::create("ERA05.png", Rect(0, 0, 240, 365));
    auto frame6 = SpriteFrame::create("ERA06.png", Rect(0, 0, 240, 365));
    auto frame7 = SpriteFrame::create("ERA07.png", Rect(0, 0, 240, 365));
    auto frame8 = SpriteFrame::create("ERA08.png", Rect(0, 0, 240, 365));
    auto frame9 = SpriteFrame::create("ERA09.png", Rect(0, 0, 240, 365));
    auto frame10 = SpriteFrame::create("ERA10.png", Rect(0, 0, 240, 365));
    auto frame11 = SpriteFrame::create("ERA11.png", Rect(0, 0, 240, 365));
    auto frame12 = SpriteFrame::create("ERA12.png", Rect(0, 0, 240, 365));

    Vector<SpriteFrame*> arr;
    arr.pushBack(frame1);
    arr.pushBack(frame2);
    arr.pushBack(frame3);
    arr.pushBack(frame4);
    arr.pushBack(frame5);
    arr.pushBack(frame6);
    arr.pushBack(frame7);
    arr.pushBack(frame8);
    arr.pushBack(frame9);
    arr.pushBack(frame10);
    arr.pushBack(frame11);
    arr.pushBack(frame12);

    Animation* amt = Animation::createWithSpriteFrames(arr, 0.1f);
    Animate* amt2 = Animate::create(amt);
    auto sprite2 = Sprite::createWithSpriteFrame(frame1);
    sprite2->setPosition(visibleSize / 2);
    addChild(sprite2);
    sprite2->runAction(RepeatForever::create(amt2));*/


// 课堂测验：逐帧动画
    /*Sprite* spbg = Sprite::create("bGround.png");
    spbg->setPosition(visibleSize / 2);
    addChild(spbg);


    SpriteFrameCache* sfc = SpriteFrameCache::getInstance();
    for (int i = 1; i <= 12; i++)
    {
        char fname[30];
        char name[10];
        sprintf_s(fname, "ERA0%d.png", i);
        sprintf_s(name, "e%d", i);
        sfc->addSpriteFrame(Sprite::create(fname)->getSpriteFrame(), name);
    }
    Sprite* sp2 = Sprite::createWithSpriteFrame(sfc->getSpriteFrameByName("e1"));
    sp2->setPosition(visibleSize.width * 4 / 5, visibleSize.height / 2);
    addChild(sp2);
    Vector<SpriteFrame*> vector;
    for (int i = 1; i <= 12; i++)
    {
        char name[10];
        sprintf_s(name, "e%d", i);
        vector.pushBack(sfc->getSpriteFrameByName(name));
    }
    Animation* anim2 = Animation::createWithSpriteFrames(vector, 0.1f);
    sp2->runAction(RepeatForever::create(Animate::create(anim2)));*/


// 大阅兵
    AudioEngine::play2d("PLA.mp3");

    Sprite* bk = Sprite::create("parad03B.jpg");
    bk->setPosition(visibleSize / 2);
    addChild(bk);

    Sprite* era = Sprite::create();
    era->setPosition(visibleSize / 2);
    addChild(era);

    Animation* anim = Animation::create();
    for (int i = 1; i <= 12; i++)
    {
        char fileName[30];
        sprintf_s(fileName, "ERA0%d.png", i);
        anim->addSpriteFrameWithFile(fileName);
    }
    anim->setDelayPerUnit(0.09f);
    anim->setRestoreOriginalFrame(true);
    Animate* an = Animate::create(anim);
    era->runAction(RepeatForever::create(an));

    schedule(([=](float dt) {
        if (2 == an->getCurrentFrameIndex() || 8 == an->getCurrentFrameIndex())
            AudioEngine::play2d("footArmy2.mp3");
        }), 0.09f, "step");



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
