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


Sprite* bg_win; //�����汳��

Button* btnBack_win; //�����˵���ť


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

    //������Ϸʧ������
    AudioEngine::play2d("win.mp3", false, 0.5f);


    //����
    bg_win = Sprite::create("bg_win.jpg");
    bg_win->setPosition(visibleSize / 2);
    addChild(bg_win);


    //��Ϸʤ��ͼƬ
    Sprite* winG = Sprite::create("win.png");
    winG->setPosition(visibleSize.width / 2, visibleSize.height * 3 / 5);
    addChild(winG);

    //�����˵���ť
    btnBack_win = Button::create("back_normal.png", "back_selected.png");
    btnBack_win->setPosition(Point(visibleSize.width / 2, visibleSize.height / 4));
    btnBack_win->addClickEventListener([=](Ref* pSend)
        {   //�����˵�����ת����
            AudioEngine::play2d("click.mp3", false, 0.5f);  //������Ч

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
