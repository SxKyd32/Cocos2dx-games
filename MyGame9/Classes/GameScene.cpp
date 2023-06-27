#include "HelloWorldScene.h"
#include "GameScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "audio/include/AudioEngine.h"

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace cocostudio;
using namespace cocos2d::ui;

PhysicsWorld* pw;

//物理材质
PhysicsMaterial pm_bg;       //背景墙壁材质
PhysicsMaterial pm_ball;     //小球材质
PhysicsMaterial pm_bat;      //发射台材质
PhysicsMaterial pm_stone;    //砖块材质

//游戏背景
Sprite* bgLv1;
Sprite* bgLv2;
PhysicsBody* pb_bg;   //背景框边界确定
int flagLv = 1;     //确定关卡，初始化为第一关

//场景内容
    //发射台
Sprite* bat;        
PhysicsBody* pb_bat;
    //小球
Sprite* ball[3];    
PhysicsBody* pb_ball[3];
    //砖块
Sprite* stone[45];  
PhysicsBody* pb_stone[45];
int stoneState[45];     //砖块状态，0-5，初始为0，为5时破碎消失

Button* btnPause;   //暂停按钮
Button* btnQuit;    //退出按钮

int bgmID_game;  //游戏背景音乐ID


Scene* MyGame::createScene()
{
    MyGame* sn = (MyGame*)MyGame::createWithPhysics();
    sn->initPhysics();

    return sn;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MyGame::initPhysics()
{
    if ( !Scene::initWithPhysics() )
    {
        return false;
    }

    pw = this->getPhysicsWorld();
    //pw->setAutoStep(false); //关闭物理世界同步
    pw->setGravity(Vec2(0, -980));  //重力
    pw->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);  //物理物体边界打开

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    //材质初始化
    pm_bg = PhysicsMaterial(0, 1, 1000);
    pm_bat = PhysicsMaterial(0, 1, 0);
    pm_ball = PhysicsMaterial(0, 1, 0);
    pm_stone = PhysicsMaterial(0, 1, 0);
    
    //绘制背景
    bgLv1 = Sprite::create("background_level1.png");    //第一关背景
    bgLv2 = Sprite::create("background_level2.jpg");    //第二关背景
    bgLv1->setPosition(visibleSize / 2);
    bgLv2->setPosition(visibleSize / 2);

    pb_bg = PhysicsBody::createEdgeBox(visibleSize, pm_bg);

    if (flagLv == 1)
    {
        addChild(bgLv1);
        bgLv1->setPhysicsBody(pb_bg);
    } 
    else if (flagLv == 2)
    {
        addChild(bgLv2);
        bgLv2->setPhysicsBody(pb_bg);
    }
    

    //播放游戏内背景音乐
    AudioEngine::preload("bgm_game1.mp3");
    AudioEngine::preload("bgm_game2.mp3");

    if (flagLv == 1)
        bgmID_game = AudioEngine::play2d("bgm_game1.mp3", true, 0.5f);
    else if (flagLv == 2)
        bgmID_game = AudioEngine::play2d("bgm_game2.mp3", true, 0.5f);


    //初始化场景内容
        //发射台
    bat = Sprite::create("bat.png");
    bat->setPosition(visibleSize.width / 2, visibleSize.height / 8);
    addChild(bat);
    pb_bat = PhysicsBody::createBox(bat->getContentSize(), pm_bat);
    pb_bat->setGravityEnable(false);
    bat->setPhysicsBody(pb_bat);

        //小球
    ball[0] = Sprite::create("ball_pinball.png");
    ball[0]->setPosition(bat->getPosition().x, bat->getPosition().y + bat->getContentSize().height / 2);
    addChild(ball[0]);
    pb_ball[0] = PhysicsBody::createCircle(ball[0]->getContentSize().width / 2, pm_ball);
    pb_ball[0]->setGravityEnable(false);
    ball[0]->setPhysicsBody(pb_ball[0]);

        //砖块
            //初始化砖块状态
    for (int i = 0; i < 45; i++)
    {
        stoneState[i] = 0;  //砖块初始化为完好状态
    }

    if (flagLv == 1) 
    {       //关卡1
        for (int i = 0; i < 45; i++) 
        {
            switch (i%5)
            {
            case 0:         //蓝色砖块
                stone[i] = Sprite::create("stone_normal_blue.png");
                break;

            case 1:         //绿色
                stone[i] = Sprite::create("stone_normal_green.png");
                break;

            case 2:         //橙色
                stone[i] = Sprite::create("stone_normal_orange.png");
                break;

            case 3:         //红色
                stone[i] = Sprite::create("stone_normal_red.png");
                break;

            case 4:         //黄色
                stone[i] = Sprite::create("stone_normal_yellow.png");
                break;

            default:
                break;
            }

            if (i < 15)   //第一排
            {
                stone[i]->setPosition(visibleSize.width * ((i % 15) + 1) / 15,
                    visibleSize.height * 9 / 10);
            }
            else if (i >= 15 && i < 30) //第二排
            {
                stone[i]->setPosition(visibleSize.width * ((i % 15) + 1) / 15,
                    visibleSize.height * 9 / 10 - stone[i]->getContentSize().height);
            }
            else if (i >= 30 && i < 45) //第三排
            {
                stone[i]->setPosition(visibleSize.width * ((i % 15) + 1) / 15,
                    visibleSize.height * 9 / 10 - stone[i]->getContentSize().height * 2);
            }
            addChild(stone[i]);
            pb_stone[i] = PhysicsBody::createBox(stone[i]->getContentSize(), pm_stone);
            pb_stone[i]->setGravityEnable(false);
            stone[i]->setPhysicsBody(pb_stone[i]);
        }
    }
    else if (flagLv == 2) 
    {       //关卡2
        for (int i = 0; i < 45; i++)
        {
            switch (i % 5)
            {
            case 0:         //蓝色砖块
                stone[i] = Sprite::create("stone_normal_blue.png");
                break;

            case 1:         //绿色
                stone[i] = Sprite::create("stone_normal_green.png");
                break;

            case 2:         //橙色
                stone[i] = Sprite::create("stone_normal_orange.png");
                break;

            case 3:         //红色
                stone[i] = Sprite::create("stone_normal_red.png");
                break;

            case 4:         //黄色
                stone[i] = Sprite::create("stone_normal_yellow.png");
                break;

            default:
                break;
            }

            if (i < 15)   //第一排
            {
                stone[i]->setPosition(visibleSize.width * ((i % 15) + 1) / 15,
                    visibleSize.height * 9 / 10 - stone[i]->getContentSize().height * (i % 4));
            }
            else if (i >= 15 && i < 30) //第二排
            {
                stone[i]->setPosition(visibleSize.width * ((i % 15) + 1) / 15,
                    visibleSize.height * 9 / 10 - stone[i]->getContentSize().height * ((i % 4) + 1));
            }
            else if (i >= 30 && i < 45) //第三排
            {
                stone[i]->setPosition(visibleSize.width * ((i % 15) + 1) / 15,
                    visibleSize.height * 9 / 10 - stone[i]->getContentSize().height * ((i % 4) + 1));
            }
            addChild(stone[i]);
            pb_stone[i] = PhysicsBody::createBox(stone[i]->getContentSize(), pm_stone);
            pb_stone[i]->setGravityEnable(false);
            stone[i]->setPhysicsBody(pb_stone[i]);
        }
    }


    //暂停按钮
    btnPause = Button::create("pause_normal.png", "pause_selected.png");
    btnPause->setPosition(Point(btnPause->getContentSize().width * 3 / 2,
        visibleSize.height - btnPause->getContentSize().height / 2));
    btnPause->addClickEventListener([=](Ref* pSend)     //暂停事件
        {
            AudioEngine::play2d("click.mp3", false, 0.5f);  //单击音效

        });
    addChild(btnPause);


    //退出按钮
    btnQuit = Button::create("exit_normal.png", "exit_selected.png");
    btnQuit->setPosition(Point(btnQuit->getContentSize().width / 2,
        visibleSize.height - btnQuit->getContentSize().height / 2));
    btnQuit->addClickEventListener([=](Ref* pSend)     //退出事件
        {   //回到主界面
            AudioEngine::play2d("click.mp3", false, 0.5f);  //单击音效

            auto MainScene = HelloWorld::createScene();
            Director::getInstance()->purgeCachedData();
            Director::getInstance()->replaceScene(MainScene);
            AudioEngine::stop(bgmID_game);     //关闭游戏背景音乐

            //Director::getInstance()->end();     //退出游戏

        });
    addChild(btnQuit);



    //消息监听、响应

        















    //scheduleUpdate();
    
    return true;
}

void MyGame::update(float dt)
{
    //pw->step(0.01f);
}


void MyGame::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
