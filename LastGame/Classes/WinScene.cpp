#include "HelloWorldScene.h"
#include "WinScene.h"
#include "GameScene2.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "audio/include/AudioEngine.h"
#include <time.h>

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace cocostudio;
using namespace cocos2d::ui;


Sprite* bg_win; //主界面背景

Button* btnBack_win; //回主菜单按钮


Scene* GameWin::createScene()
{
    return GameWin::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameWin::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //播放游戏失败音乐
    AudioEngine::play2d("win.mp3", false, 0.5f);


    //背景
    bg_win = Sprite::create("bg_win.jpg");
    bg_win->setPosition(visibleSize / 2);
    addChild(bg_win);


    //游戏胜利图片
    Sprite* winG = Sprite::create("win.png");
    winG->setPosition(visibleSize.width / 2, visibleSize.height * 3 / 5);
    addChild(winG);

    //回主菜单按钮
    btnBack_win = Button::create("back_normal.png", "back_selected.png");
    btnBack_win->setPosition(Point(visibleSize.width / 2, visibleSize.height / 4));
    btnBack_win->addClickEventListener([=](Ref* pSend)
        {   //回主菜单，跳转界面
            AudioEngine::play2d("click.mp3", false, 0.5f);  //单击音效

            auto MainScene = HelloWorld::createScene();
            Director::getInstance()->purgeCachedData();
            Director::getInstance()->replaceScene(MainScene);
        });
    addChild(btnBack_win);

    return true;
}


void GameWin::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
