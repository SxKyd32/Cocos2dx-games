#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "audio/include/AudioEngine.h"
USING_NS_CC;

using namespace cocostudio::timeline;
using namespace cocostudio;
using namespace cocos2d::ui;

time_t startTime;
time_t currentTime;

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
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    LayerColor* lc = LayerColor::create(Color4B::BLUE);
    addChild(lc);

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    

//播放音频
    //直接加载音频
    /*AudioEngine::play2d("mother.mp3");*/


    //行走的小玩偶
    /*Sprite* bg = Sprite::create("BoxB.jpg");
    bg->setPosition(visibleSize / 2);
    addChild(bg);
    AudioEngine::play2d("bground.wav");

    Vector<SpriteFrame*> sf;
    for (int i = 0; i <= 6; i++)
    {
        char filename[10];
        sprintf_s(filename, "b%d.png", i);
        sf.pushBack(Sprite::create(filename)->getSpriteFrame());
    }

    Sprite* sp = Sprite::create();
    Animation* anim = Animation::createWithSpriteFrames(sf, 0.25);
    sp->setPosition(visibleSize / 2);
    sp->runAction(RepeatForever::create(Animate::create(anim)));
    addChild(sp);
    AudioEngine::play2d("foot.wav", true);*/
    


//课堂练习：鬼子进村
    /*Sprite* bg = Sprite::create("bg001.jpg");
    bg->setPosition(visibleSize / 2);
    addChild(bg);

    Vector<SpriteFrame*> sf;
    for (int i = 1; i <= 8; i++)
    {
        char filename[10];
        sprintf_s(filename, "J20%d.png", i);
        sf.pushBack(Sprite::create(filename)->getSpriteFrame());
    }

    Sprite* sp = Sprite::create();
    Animation* anim = Animation::createWithSpriteFrames(sf, 0.125);
    sp->setPosition(visibleSize / 2);
    sp->runAction(RepeatForever::create(Animate::create(anim)));
    addChild(sp);

    AudioEngine::play2d("japanIn.mp3");
    AudioEngine::play2d("footArmy2.mp3", true);*/


//课堂练习：大阅兵进阶版
    Sprite* bg = Sprite::create("parad.jpg");
    bg->setPosition(visibleSize / 2);
    addChild(bg);

    Vector<SpriteFrame*> sf;
    for (int i = 1; i <= 12; i++)
    {
        char filename[20];
        sprintf_s(filename, "ERA0%d.png", i);
        sf.pushBack(Sprite::create(filename)->getSpriteFrame());
    }

    Sprite* sp = Sprite::create();
    Animation* anim = Animation::createWithSpriteFrames(sf, 0.104);
    sp->setPosition(visibleSize.width * 4 / 5, visibleSize.height * 3 / 5);
    sp->runAction(RepeatForever::create(Animate::create(anim)));

    addChild(sp);

    AudioEngine::play2d("PLA.mp3");

    //文件读取，存入数组
    FILE* f = fopen("pla.txt", "rb");



//文本菜单
    /*MenuItemFont::setFontName("黑体");
    MenuItemFont::setFontSize(86);
    MenuItemFont* item1 = MenuItemFont::create("Start", [=](Ref* pSend) {log("Start"); });
    item1->setColor(Color3B::WHITE);
    MenuItemFont* item2 = MenuItemFont::create("Quit", [=](Ref* pSend) {log("Quit"); });
    item2->setColor(Color3B::WHITE);
    Menu* menu = Menu::create(item1, item2, NULL);
    menu->alignItemsVertically();
    addChild(menu);*/


//图片菜单
    /*MenuItemImage* mii1 = MenuItemImage::create("img1n.png", "img1s.png", "img1d.png",
        [=](Ref* pSend) {log("img1 OK"); });
    MenuItemImage* mii2 = MenuItemImage::create("img2n.png", "img2s.png", "img2d.png",
        [=](Ref* pSend) {log("img2 OK"); });
    Menu* menu = Menu::create(mii1, mii2, NULL);
    menu->alignItemsVertically();
    addChild(menu);*/


//Sprite菜单
    /*Sprite* p1n = Sprite::create("planen1.png");
    Sprite* p1s = Sprite::create("planes1.png");
    Sprite* p1d = Sprite::create("planed1.png");
    Sprite* p2n = Sprite::create("planen2.png");
    Sprite* p2s = Sprite::create("planes2.png");
    Sprite* p2d = Sprite::create("planed2.png");

    MenuItemSprite* item1 = MenuItemSprite::create(p1n, p1s, p1d, [=](Ref* pSend) {log("sp ok"); });
    MenuItemSprite* item2 = MenuItemSprite::create(p2n, p2s, p2d, [=](Ref* pSend) {log("sp ok"); });
    Menu* menu = Menu::create(item1, item2, NULL);
    menu->alignItemsVertically();
    addChild(menu);*/


//开关菜单
    /*Sprite* sp = Sprite::create("signalLight.png");
    sp->setPosition(visibleSize / 2);
    addChild(sp);

    MenuItemImage* mii1 = MenuItemImage::create("OnA.png", "OnA.png");
    MenuItemImage* mii2 = MenuItemImage::create("signalLight.png", "signalLight.png");
    MenuItemToggle* mit = MenuItemToggle::createWithCallback([=](Ref* pSend) {}, mii1, mii2, NULL);
    Menu* menu = Menu::create(mit, NULL);
    menu->alignItemsVertically();
    addChild(menu);*/



    return true;
}

void HelloWorld::parRun(float dt)
{
    currentTime = time(NULL);
    float cut = currentTime - startTime;

    if (cut > )
    {

    }

}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
