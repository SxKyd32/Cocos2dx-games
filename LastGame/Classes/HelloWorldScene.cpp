#include "HelloWorldScene.h"
#include "GameScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "audio/include/AudioEngine.h"
#include <time.h>

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace cocostudio;
using namespace cocos2d::ui;


Sprite* bg; //�����汳��

Button* btnStart; //��ʼ��Ϸ��ť

int bgmID;  //��������ID

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
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //Ԥ���ر�������
    AudioEngine::preload("bgm_main1.mp3");
    AudioEngine::preload("bgm_main2.mp3");

    //�������ּ����ɱ���
    srand(time(NULL));
    float rd = rand() / (RAND_MAX + 1.0);   //�����
    if ((int)(RAND_MAX * rd) % 2)
    {
        bg = Sprite::create("background_main1.png");    //����1
        bgmID = AudioEngine::play2d("bgm_main1.mp3", true, 0.5f);     //���������汳������1
    }

    else
    {
        bg = Sprite::create("background_main2.png");    //����2
        bgmID = AudioEngine::play2d("bgm_main2.mp3", true, 0.5f);  //���������汳������2
    }

    bg->setPosition(visibleSize / 2);
    addChild(bg);

    //��Ϸ������ש�飨Break the Bricks��
    Label* lb_title = Label::createWithTTF("Break the Bricks", "fonts//Marker Felt.ttf", 50);
    lb_title->setColor(Color3B::WHITE);
    lb_title->setPosition(visibleSize.width / 2, visibleSize.height * 3 / 5);
    addChild(lb_title);


    //��ʼ��Ϸ��ť
    btnStart = Button::create("start_normal.png", "start_selected.png");
    btnStart->setPosition(Point(visibleSize.width / 2, visibleSize.height / 4));
    btnStart->addClickEventListener([=](Ref* pSend)
        {   //��ʼ��Ϸ����ת����
            AudioEngine::play2d("click.mp3", false, 0.5f);  //������Ч

            auto GameScene = MyGame::createScene();
            Director::getInstance()->purgeCachedData();
            Director::getInstance()->replaceScene(GameScene);
            AudioEngine::stop(bgmID);     //�ر������汳������
        });
    addChild(btnStart);

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
