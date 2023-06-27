#include "HelloWorldScene.h"
#include "GameScene.h"
#include "GameScene2.h"
#include "LoseScene.h"
#include "WinScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "audio/include/AudioEngine.h"
#include <map>

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
int stoneState[45];     //砖块状态，0-4，初始为0，为4时破碎消失

PhysicsJointFixed* pjf;   //小球与发射台的关节

Button* btnPause;   //暂停按钮
Button* btnQuit;    //退出按钮

//玩家血量
Label* lb_blood;
int blood = 5;

int bgmID_game;  //游戏背景音乐ID

//小球速度方向量
float speedx = 200;
float speedy = 346;
//float speedx = 0;
//float speedy = 346;

bool isShot = 0;  //小球是否发射

//用于判断左右方向键是否处于被按下的状态
std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;

//砖块破碎动画
Animation* anim_blue;
Animation* anim_green;
Animation* anim_orange;
Animation* anim_red;
Animation* anim_yellow;

//纹理上的动画帧
SpriteFrame* sf_blue0;
SpriteFrame* sf_blue1;
SpriteFrame* sf_blue2;
SpriteFrame* sf_blue3;
SpriteFrame* sf_blue4;
SpriteFrame* sf_green0;
SpriteFrame* sf_green1;
SpriteFrame* sf_green2;
SpriteFrame* sf_green3;
SpriteFrame* sf_green4;
SpriteFrame* sf_orange0;
SpriteFrame* sf_orange1;
SpriteFrame* sf_orange2;
SpriteFrame* sf_orange3;
SpriteFrame* sf_orange4;
SpriteFrame* sf_red0;
SpriteFrame* sf_red1;
SpriteFrame* sf_red2;
SpriteFrame* sf_red3;
SpriteFrame* sf_red4;
SpriteFrame* sf_yellow0;
SpriteFrame* sf_yellow1;
SpriteFrame* sf_yellow2;
SpriteFrame* sf_yellow3;
SpriteFrame* sf_yellow4;

SpriteFrame* sf_0;

//存储动画帧的第一帧
SpriteFrameCache* sfCache;

//动画数组
Vector<SpriteFrame*> sfs_blue;
Vector<SpriteFrame*> sfs_green;
Vector<SpriteFrame*> sfs_orange;
Vector<SpriteFrame*> sfs_red;
Vector<SpriteFrame*> sfs_yellow;


time_t gameTime;
time_t currentTime;

//蓝色小球变大buff持续时间
time_t startTime;
time_t endTime;

PhysicsBody* pb_bat_huge;

int toNext = 45;    //判断砖块是否打完

bool isPause = false;   //判断是否暂停

//暂停界面
Sprite* bg_Pause;   //暂停背景

Button* btn_P_back;
Button* btn_P_continue;

int cnt_balls = 1;  //判断场上小球数量


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
    if (!Scene::initWithPhysics())
    {
        return false;
    }

    pw = this->getPhysicsWorld();
    //pw->setAutoStep(false); //关闭物理世界同步
    pw->setGravity(Vec2(0, -980));  //重力
    //pw->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);  //物理物体边界打开

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


//材质初始化
    pm_bg = PhysicsMaterial(0, 1, 1000);
    pm_bat = PhysicsMaterial(1000, 1, 0);
    pm_ball = PhysicsMaterial(0, 1, 0);
    pm_stone = PhysicsMaterial(1000, 1, 0);

//绘制背景
    bgLv1 = Sprite::create("background_level1.png");    //第一关背景
    bgLv2 = Sprite::create("background_level2.jpg");    //第二关背景
    bgLv1->setPosition(visibleSize / 2);
    bgLv2->setPosition(visibleSize / 2);
    bgLv1->setTag(95);
    bgLv2->setTag(95);
    pb_bg = PhysicsBody::createEdgeBox(visibleSize, pm_bg);
    //设置背景掩码
    pb_bg->setCategoryBitmask(99);
    pb_bg->setCollisionBitmask(99);
    pb_bg->setContactTestBitmask(99);

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

    if (flagLv == 1)    //播放第一关背景音乐
        bgmID_game = AudioEngine::play2d("bgm_game1.mp3", true, 0.5f);
    else if (flagLv == 2)   //播放第二关背景音乐
        bgmID_game = AudioEngine::play2d("bgm_game2.mp3", true, 0.5f);


//初始化场景内容
    //发射台
    bat = Sprite::create("bat.png");
    Sprite* bat_h = Sprite::create("bat_huge.png");
    bat->setPosition(visibleSize.width / 2, visibleSize.height / 8);
    addChild(bat);
    pb_bat = PhysicsBody::createBox(bat->getContentSize(), pm_bat);
    pb_bat->setGravityEnable(false);
    bat->setPhysicsBody(pb_bat);
    pb_bat_huge = PhysicsBody::createBox(bat_h->getContentSize(), pm_bat);
    pb_bat_huge->setGravityEnable(false);

    bat->setTag(99);     //Tag标记，发射台为99，普通小球和红色小球为98，蓝色小球为97
    //设置发射台掩码
    pb_bat->setCategoryBitmask(99);
    pb_bat->setCollisionBitmask(98);
    pb_bat->setContactTestBitmask(98);

    //小球
    ball[0] = Sprite::create("ball_pinball.png");
    ball[0]->setPosition(bat->getPosition().x, bat->getPosition().y + bat->getContentSize().height / 2);
    addChild(ball[0]);
    pb_ball[0] = PhysicsBody::createCircle(ball[0]->getContentSize().width / 2, pm_ball);
    pb_ball[0]->setGravityEnable(false);
    ball[0]->setPhysicsBody(pb_ball[0]);
        //设置小球标记
    ball[0]->setTag(98);
        //设置小球碰撞掩码
    pb_ball[0]->setCategoryBitmask(99);
    pb_ball[0]->setCollisionBitmask(97);
    pb_ball[0]->setContactTestBitmask(97);

    //散射小球1
    ball[1] = Sprite::create("ball_red.png");
    ball[1]->setTag(98);
    ball[1]->setPosition(-100, -100);
    addChild(ball[1]);
    pb_ball[1] = PhysicsBody::createCircle(ball[1]->getContentSize().width / 2, pm_ball);
    pb_ball[1]->setGravityEnable(false);
    ball[1]->setPhysicsBody(pb_ball[1]);
    pb_ball[1]->setCategoryBitmask(99);
    pb_ball[1]->setCollisionBitmask(97);
    pb_ball[1]->setContactTestBitmask(97);
    
    //散射小球2
    ball[2] = Sprite::create("ball_red.png");
    ball[2]->setTag(98);
    ball[2]->setPosition(-100, -200);
    addChild(ball[2]);
    pb_ball[2] = PhysicsBody::createCircle(ball[2]->getContentSize().width / 2, pm_ball);
    pb_ball[2]->setGravityEnable(false);
    ball[2]->setPhysicsBody(pb_ball[2]);
    pb_ball[2]->setCategoryBitmask(99);
    pb_ball[2]->setCollisionBitmask(97);
    pb_ball[2]->setContactTestBitmask(97);



    //小球与发射台连接
    pjf = PhysicsJointFixed::construct(pb_bat, pb_ball[0],
        bat->getPosition() + Vec2(0, bat->getContentSize().height / 2));
    pw->addJoint(pjf);

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
            stone[i]->setTag(i);    //砖块的标记为i，即其次序
            //设置砖块掩码
            pb_stone[i]->setCategoryBitmask(99);
            pb_stone[i]->setCollisionBitmask(1);
            pb_stone[i]->setContactTestBitmask(1);
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
            stone[i]->setTag(i);
            //设置砖块掩码
            pb_stone[i]->setCategoryBitmask(99);
            pb_stone[i]->setCollisionBitmask(0);
            pb_stone[i]->setContactTestBitmask(0);
        }
    }


//暂停按钮内部事件
    //添加暂停界面
    bg_Pause = Sprite::create("pauseboard.png");
    bg_Pause->setPosition(visibleSize / 2);
    addChild(bg_Pause);
    bg_Pause->setVisible(false);

    //添加按钮
    btn_P_back = Button::create("back_normal.png", "back_selected.png");
    btn_P_back->setPosition(Point(visibleSize.width / 2, visibleSize.height * 2 / 5));
    btn_P_back->addClickEventListener([=](Ref* pSend)
        {   //回主界面
            AudioEngine::play2d("click.mp3", false, 0.5f);  //单击音效

            blood = 5;
            isShot = 0;
            toNext = 45;
            auto MainScene = HelloWorld::createScene();
            Director::getInstance()->purgeCachedData();
            Director::getInstance()->replaceScene(MainScene);
            AudioEngine::stop(bgmID_game);
        });
    addChild(btn_P_back);
    btn_P_back->setVisible(false);
    btn_P_back->setEnabled(false);

    btn_P_continue = Button::create("continue_normal.png", "continue_selected.png");
    btn_P_continue->setPosition(Point(visibleSize.width / 2, visibleSize.height * 3 / 5));
    btn_P_continue->setEnabled(true);
    addChild(btn_P_continue);
    btn_P_continue->setVisible(false);
    btn_P_continue->setEnabled(false);


//暂停按钮
    btnPause = Button::create("pause_normal.png", "pause_selected.png");
    btnPause->setPosition(Point(btnPause->getContentSize().width * 3 / 2,
        visibleSize.height - btnPause->getContentSize().height / 2));
    btnPause->addClickEventListener([=](Ref* pSend)     //暂停事件
        {
            if (!isPause)
            {
                isPause = true;
                AudioEngine::play2d("click.mp3", false, 0.5f);  //单击音效
                //Director::getInstance()->getScheduler()->setTimeScale(0);
                Director::getInstance()->pause();   //暂停
                //添加背景
                bg_Pause->setVisible(true);
                //添加按钮
                btn_P_back->setVisible(true);
                btn_P_back->setEnabled(true);
                btn_P_continue->setVisible(true);
                btn_P_continue->setEnabled(true);
            }
            else
            {
                isPause = false;
                //删除背景
                bg_Pause->setVisible(false);
                //删除按钮
                btn_P_back->setVisible(false);
                btn_P_back->setEnabled(false);
                btn_P_continue->setVisible(false);
                btn_P_continue->setEnabled(false);
            }
        });
    addChild(btnPause);


//退出按钮
    btnQuit = Button::create("exit_normal.png", "exit_selected.png");
    btnQuit->setPosition(Point(btnQuit->getContentSize().width / 2,
        visibleSize.height - btnQuit->getContentSize().height / 2));
    btnQuit->addClickEventListener([=](Ref* pSend)     //退出事件
        {   //回到主界面
            AudioEngine::play2d("click.mp3", false, 0.5f);  //单击音效

            blood = 5;
            isShot = 0;
            toNext = 45;
            auto MainScene = HelloWorld::createScene();
            Director::getInstance()->purgeCachedData();
            Director::getInstance()->replaceScene(MainScene);
            AudioEngine::stop(bgmID_game);     //关闭游戏背景音乐

            //Director::getInstance()->end();     //退出游戏

        });
    addChild(btnQuit);


//玩家血量
    lb_blood = Label::Label::createWithTTF(std::to_string(blood), "fonts//Marker Felt.ttf", 32);
    lb_blood->setColor(Color3B::RED);
    lb_blood->setPosition(visibleSize.width * 19 / 20, visibleSize.height / 15);
    lb_blood->removeFromParent();
    addChild(lb_blood);




//键盘消息监听、响应
    //发射小球
    EventListenerKeyboard* shootListener = EventListenerKeyboard::create();
    shootListener->onKeyPressed = CC_CALLBACK_2(MyGame::pressed_Shoot, this);
        
    //发射台左右移动
    EventListenerKeyboard* moveListener = EventListenerKeyboard::create();
    moveListener->onKeyPressed = CC_CALLBACK_2(MyGame::pressed_batMove, this);
    moveListener->onKeyReleased = CC_CALLBACK_2(MyGame::released_batMove, this);

    EventDispatcher* dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addEventListenerWithSceneGraphPriority(shootListener, this);
    dispatcher->addEventListenerWithSceneGraphPriority(moveListener, this);

    schedule(CC_SCHEDULE_SELECTOR(MyGame::gameUpdate), 0.01f);  //update监听




//碰撞响应
    EventListenerPhysicsContact* elpc = EventListenerPhysicsContact::create();
    elpc->onContactBegin = CC_CALLBACK_1(MyGame::isCld, this);
    EventDispatcher* ed = Director::getInstance()->getEventDispatcher();
    ed->addEventListenerWithSceneGraphPriority(elpc, this);



    



    //scheduleUpdate();
    //Director::getInstance()->getScheduler()->scheduleUpdate(this, 0, false);

    return true;
}

void MyGame::pressed_Shoot(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();

    if (EventKeyboard::KeyCode::KEY_Z == keycode)   // 按“z”键发射小球
    {
        if (!isShot)
        {
            pb_ball[0]->setVelocity(Vec2(speedx, speedy));  //向右上60度发射小球
            //删除关节
            pw->removeJoint(pjf);
            isShot = 1;
        }
    }
}

void MyGame::pressed_batMove(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event)
{
    keys[keycode] = true;
    //log("1");
}

void MyGame::released_batMove(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event)
{
    keys[keycode] = false;
    //log("2");
}

bool MyGame::isKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode)
{
    if (keys[keyCode])
        return true;
    else
        return false;
}

void MyGame::keyPressedDuration(cocos2d::EventKeyboard::KeyCode code)   //处理左右移动消息响应事件
{
    int offsetX = 0, offsetY = 0;
    switch (code) {
    case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        offsetX = -5;
        break;
    case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        offsetX = 5;
        break;
    default:
        offsetY = offsetX = 0;
        break;
    }

    auto moveTo = MoveTo::create(0.3, Vec2(bat->getPositionX() + offsetX, bat->getPositionY() + offsetY));
    bat->runAction(moveTo);
}

void MyGame::gameUpdate(float dt)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();

    //log("update");

    auto leftArrow = EventKeyboard::KeyCode::KEY_LEFT_ARROW;
    auto rightArrow = EventKeyboard::KeyCode::KEY_RIGHT_ARROW;
    if (isKeyPressed(leftArrow))
    {
        keyPressedDuration(leftArrow);
        //log("left");
    }
    else if (isKeyPressed(rightArrow))
    {
        keyPressedDuration(rightArrow);
        //log("right");
    }

    lb_blood->setString(std::to_string(blood));     //更新血量

    //endTime = time(NULL);
    //if (endTime - startTime == 10)  //变大效果持续10秒
    //{
    //    Sprite* bat_normal = Sprite::create("bat.png");
    //    auto texture = Director::getInstance()->getTextureCache()->addImage("bat.png");
    //    bat->setContentSize(Size(bat_normal->getContentSize()));
    //    bat->setScale(bat_normal->getScale());
    //    bat->setTexture(texture);
    //    PhysicsBody* pb_bat_normal = PhysicsBody::createBox(bat->getContentSize(), pm_bat);
    //    pb_bat_normal->setGravityEnable(false);
    //    bat->setPhysicsBody(pb_bat_normal);
    //}

    if (toNext == 0 && flagLv == 1)     //跳转至下一关
    {
        //flagLv = 2;
        blood = 5;
        isShot = 0;
        toNext = 45;
        auto GameScene2 = MyGame2::createScene();
        Director::getInstance()->purgeCachedData();
        Director::getInstance()->replaceScene(GameScene2);
        AudioEngine::stop(bgmID_game);
    }
    else if (toNext == 0 && flagLv == 2)    //跳转至游戏胜利画面
    {

        toNext = 1;
    }

    if (blood == 0)     //血量为0，游戏失败
    {
        blood = 5;
        isShot = 0;
        toNext = 45;
        auto LoseScene = GameLose::createScene();
        Director::getInstance()->purgeCachedData();
        Director::getInstance()->replaceScene(LoseScene);
        AudioEngine::stop(bgmID_game);
    }
}

bool MyGame::isCld(cocos2d::PhysicsContact& contact)    //碰撞响应
{
    Size visibleSize = Director::getInstance()->getVisibleSize();

    Sprite* targetA = (Sprite*)contact.getShapeA()->getBody()->getNode();
    Sprite* targetB = (Sprite*)contact.getShapeB()->getBody()->getNode();


    //小球与砖块碰撞
    for (int i = 0; i < 45; i++)
    {
        if ((98 == targetA->getTag() && i == targetB->getTag()) || (97 == targetA->getTag() && i == targetB->getTag()))
        {
            //撞击音效
            AudioEngine::play2d("cld.mp3", false, 0.5f);  //单击音效
        

            //测试
            /*Sprite* sp = Sprite::createWithSpriteFrame(sf_blue0);
            sp->setPosition(VisibleSize / 2);
            addChild(sp);
            
            //gameTime = time(NULL);

            //sp->runAction(Animate::create(animCache->getAnimation("anim_b")));
            sp->runAction(Animate::create(anim_blue));

            currentTime = time(NULL);
            if (currentTime - gameTime == 0.5f)
                sp->removeFromParent();*/
            
            //log("hit");
            stoneState[i]++;    //砖块破碎程度增加

            switch (i % 5)
            {
            case 0:         //蓝色砖块
                if (stoneState[i] == 1)
                {
                    auto texture = Director::getInstance()->getTextureCache()->addImage("stone_damaged1_blue.png");
                    stone[i]->setTexture(texture);
                }
                else if (stoneState[i] == 2)
                {
                    auto texture = Director::getInstance()->getTextureCache()->addImage("stone_damaged2_blue.png");
                    stone[i]->setTexture(texture);
                }
                else if (stoneState[i] == 3)
                {
                    auto texture = Director::getInstance()->getTextureCache()->addImage("stone_damaged3_blue.png");
                    stone[i]->setTexture(texture);
                }
                else if (stoneState[i] == 4)
                {
                    toNext--;
                //砖块破碎动画
                    //清除动画数组内容
                    sfs_blue.clear();
                    //透明纹理
                    auto texture_0 = Director::getInstance()->getTextureCache()->addImage("0.png");
                    sf_0 = SpriteFrame::createWithTexture(texture_0, Rect(0, 0, 5, 5));
                    //用于确定动画帧尺寸
                    Sprite* brk_blue = Sprite::create("stone_breaking_blue.png");
                    //纹理
                    auto texture_blue = Director::getInstance()->getTextureCache()->addImage("stone_breaking_blue.png");
                    //纹理上的动画帧
                    sf_blue0 = SpriteFrame::createWithTexture(texture_blue,
                        Rect(0 * brk_blue->getContentSize().width / 5, 0,
                            brk_blue->getContentSize().width / 5, brk_blue->getContentSize().height));
                    sf_blue1 = SpriteFrame::createWithTexture(texture_blue,
                        Rect(1 * brk_blue->getContentSize().width / 5, 0,
                            brk_blue->getContentSize().width / 5, brk_blue->getContentSize().height));
                    sf_blue2 = SpriteFrame::createWithTexture(texture_blue,
                        Rect(2 * brk_blue->getContentSize().width / 5, 0,
                            brk_blue->getContentSize().width / 5, brk_blue->getContentSize().height));
                    sf_blue3 = SpriteFrame::createWithTexture(texture_blue,
                        Rect(3 * brk_blue->getContentSize().width / 5, 0,
                            brk_blue->getContentSize().width / 5, brk_blue->getContentSize().height));
                    sf_blue4 = SpriteFrame::createWithTexture(texture_blue,
                        Rect(4 * brk_blue->getContentSize().width / 5, 0,
                            brk_blue->getContentSize().width / 5, brk_blue->getContentSize().height));
                    //放入动画帧到动画数组
                    sfs_blue.pushBack(sf_blue0);
                    sfs_blue.pushBack(sf_blue1);
                    sfs_blue.pushBack(sf_blue2);
                    sfs_blue.pushBack(sf_blue3);
                    sfs_blue.pushBack(sf_blue4);
                    sfs_blue.pushBack(sf_0);
                    //创建动画信息
                    anim_blue = Animation::createWithSpriteFrames(sfs_blue, 0.1f);
                    //播放砖块破碎动画
                    Sprite* sp = Sprite::createWithSpriteFrame(sf_blue0);
                    sp->setPosition(stone[i]->getPosition());
                    addChild(sp);
                    sp->runAction(Animate::create(anim_blue));
                    //移除砖块
                    stone[i]->setVisible(false);
                    pb_stone[i]->setEnabled(false);

                    //小球变为蓝色
                    auto texture = Director::getInstance()->getTextureCache()->addImage("ball_blue.png");
                    targetA->setTexture(texture);
                    targetA->setTag(97);
                }
                break;

            case 1:         //绿色
                if (stoneState[i] == 1)
                {
                    auto texture = Director::getInstance()->getTextureCache()->addImage("stone_damaged1_green.png");
                    stone[i]->setTexture(texture);
                }
                else if (stoneState[i] == 2)
                {
                    auto texture = Director::getInstance()->getTextureCache()->addImage("stone_damaged2_green.png");
                    stone[i]->setTexture(texture);
                }
                else if (stoneState[i] == 3)
                {
                    auto texture = Director::getInstance()->getTextureCache()->addImage("stone_damaged3_green.png");
                    stone[i]->setTexture(texture);
                }
                else if (stoneState[i] == 4)
                {
                    toNext--;
                    //清除动画数组内容
                    sfs_green.clear();
                    //透明纹理
                    auto texture_0 = Director::getInstance()->getTextureCache()->addImage("0.png");
                    sf_0 = SpriteFrame::createWithTexture(texture_0, Rect(0, 0, 5, 5));
                    //用于确定动画帧尺寸
                    Sprite* brk_green = Sprite::create("stone_breaking_green.png");
                    //纹理
                    auto texture_green = Director::getInstance()->getTextureCache()->addImage("stone_breaking_green.png");
                    //纹理上的动画帧
                    sf_green0 = SpriteFrame::createWithTexture(texture_green,
                        Rect(0 * brk_green->getContentSize().width / 5, 0,
                            brk_green->getContentSize().width / 5, brk_green->getContentSize().height));
                    sf_green1 = SpriteFrame::createWithTexture(texture_green,
                        Rect(1 * brk_green->getContentSize().width / 5, 0,
                            brk_green->getContentSize().width / 5, brk_green->getContentSize().height));
                    sf_green2 = SpriteFrame::createWithTexture(texture_green,
                        Rect(2 * brk_green->getContentSize().width / 5, 0,
                            brk_green->getContentSize().width / 5, brk_green->getContentSize().height));
                    sf_green3 = SpriteFrame::createWithTexture(texture_green,
                        Rect(3 * brk_green->getContentSize().width / 5, 0,
                            brk_green->getContentSize().width / 5, brk_green->getContentSize().height));
                    sf_green4 = SpriteFrame::createWithTexture(texture_green,
                        Rect(4 * brk_green->getContentSize().width / 5, 0,
                            brk_green->getContentSize().width / 5, brk_green->getContentSize().height));
                    //放入动画帧到动画数组
                    sfs_green.pushBack(sf_green0);
                    sfs_green.pushBack(sf_green1);
                    sfs_green.pushBack(sf_green2);
                    sfs_green.pushBack(sf_green3);
                    sfs_green.pushBack(sf_green4);
                    sfs_green.pushBack(sf_0);
                    //创建动画信息
                    anim_green = Animation::createWithSpriteFrames(sfs_green, 0.1f);
                    //播放砖块破碎动画
                    Sprite* sp_green = Sprite::createWithSpriteFrame(sf_green0);
                    sp_green->setPosition(stone[i]->getPosition());
                    addChild(sp_green);
                    sp_green->runAction(Animate::create(anim_green));
                    //移除砖块
                    stone[i]->setVisible(false);   
                    pb_stone[i]->setEnabled(false);
                }
                break;

            case 2:         //橙色
                if (stoneState[i] == 1)
                {
                    auto texture = Director::getInstance()->getTextureCache()->addImage("stone_damaged1_orange.png");
                    stone[i]->setTexture(texture);
                }
                else if (stoneState[i] == 2)
                {
                    auto texture = Director::getInstance()->getTextureCache()->addImage("stone_damaged2_orange.png");
                    stone[i]->setTexture(texture);
                }
                else if (stoneState[i] == 3)
                {
                    auto texture = Director::getInstance()->getTextureCache()->addImage("stone_damaged3_orange.png");
                    stone[i]->setTexture(texture);
                }
                else if (stoneState[i] == 4)
                {
                    toNext--;
                    //清除动画数组内容
                    sfs_orange.clear();
                    //透明纹理
                    auto texture_0 = Director::getInstance()->getTextureCache()->addImage("0.png");
                    sf_0 = SpriteFrame::createWithTexture(texture_0, Rect(0, 0, 5, 5));
                    //用于确定动画帧尺寸
                    Sprite* brk_orange = Sprite::create("stone_breaking_orange.png");
                    //纹理
                    auto texture_orange = Director::getInstance()->getTextureCache()->addImage("stone_breaking_orange.png");
                    //纹理上的动画帧
                    sf_orange0 = SpriteFrame::createWithTexture(texture_orange,
                        Rect(0 * brk_orange->getContentSize().width / 5, 0,
                            brk_orange->getContentSize().width / 5, brk_orange->getContentSize().height));
                    sf_orange1 = SpriteFrame::createWithTexture(texture_orange,
                        Rect(1 * brk_orange->getContentSize().width / 5, 0,
                            brk_orange->getContentSize().width / 5, brk_orange->getContentSize().height));
                    sf_orange2 = SpriteFrame::createWithTexture(texture_orange,
                        Rect(2 * brk_orange->getContentSize().width / 5, 0,
                            brk_orange->getContentSize().width / 5, brk_orange->getContentSize().height));
                    sf_orange3 = SpriteFrame::createWithTexture(texture_orange,
                        Rect(3 * brk_orange->getContentSize().width / 5, 0,
                            brk_orange->getContentSize().width / 5, brk_orange->getContentSize().height));
                    sf_orange4 = SpriteFrame::createWithTexture(texture_orange,
                        Rect(4 * brk_orange->getContentSize().width / 5, 0,
                            brk_orange->getContentSize().width / 5, brk_orange->getContentSize().height));
                    //放入动画帧到动画数组
                    sfs_orange.pushBack(sf_orange0);
                    sfs_orange.pushBack(sf_orange1);
                    sfs_orange.pushBack(sf_orange2);
                    sfs_orange.pushBack(sf_orange3);
                    sfs_orange.pushBack(sf_orange4);
                    sfs_orange.pushBack(sf_0);
                    //创建动画信息
                    anim_orange = Animation::createWithSpriteFrames(sfs_orange, 0.1f);
                    //播放砖块破碎动画
                    Sprite* sp_orange = Sprite::createWithSpriteFrame(sf_orange0);
                    sp_orange->setPosition(stone[i]->getPosition());
                    addChild(sp_orange);
                    sp_orange->runAction(Animate::create(anim_orange));
                    //移除砖块
                    stone[i]->setVisible(false);
                    pb_stone[i]->setEnabled(false);
                }
                break;

            case 3:         //红色
                if (stoneState[i] == 1)
                {
                    auto texture = Director::getInstance()->getTextureCache()->addImage("stone_damaged1_red.png");
                    stone[i]->setTexture(texture);
                }
                else if (stoneState[i] == 2)
                {
                    auto texture = Director::getInstance()->getTextureCache()->addImage("stone_damaged2_red.png");
                    stone[i]->setTexture(texture);
                }
                else if (stoneState[i] == 3)
                {
                    auto texture = Director::getInstance()->getTextureCache()->addImage("stone_damaged3_red.png");
                    stone[i]->setTexture(texture);
                }
                else if (stoneState[i] == 4)
                {
                    toNext--;
                    //清除动画数组内容
                    sfs_red.clear();
                    //透明纹理
                    auto texture_0 = Director::getInstance()->getTextureCache()->addImage("0.png");
                    sf_0 = SpriteFrame::createWithTexture(texture_0, Rect(0, 0, 5, 5));
                    //用于确定动画帧尺寸
                    Sprite* brk_red = Sprite::create("stone_breaking_red.png");
                    //纹理
                    auto texture_red = Director::getInstance()->getTextureCache()->addImage("stone_breaking_red.png");
                    //纹理上的动画帧
                    sf_red0 = SpriteFrame::createWithTexture(texture_red,
                        Rect(0 * brk_red->getContentSize().width / 5, 0,
                            brk_red->getContentSize().width / 5, brk_red->getContentSize().height));
                    sf_red1 = SpriteFrame::createWithTexture(texture_red,
                        Rect(1 * brk_red->getContentSize().width / 5, 0,
                            brk_red->getContentSize().width / 5, brk_red->getContentSize().height));
                    sf_red2 = SpriteFrame::createWithTexture(texture_red,
                        Rect(2 * brk_red->getContentSize().width / 5, 0,
                            brk_red->getContentSize().width / 5, brk_red->getContentSize().height));
                    sf_red3 = SpriteFrame::createWithTexture(texture_red,
                        Rect(3 * brk_red->getContentSize().width / 5, 0,
                            brk_red->getContentSize().width / 5, brk_red->getContentSize().height));
                    sf_red4 = SpriteFrame::createWithTexture(texture_red,
                        Rect(4 * brk_red->getContentSize().width / 5, 0,
                            brk_red->getContentSize().width / 5, brk_red->getContentSize().height));
                    //放入动画帧到动画数组
                    sfs_red.pushBack(sf_red0);
                    sfs_red.pushBack(sf_red1);
                    sfs_red.pushBack(sf_red2);
                    sfs_red.pushBack(sf_red3);
                    sfs_red.pushBack(sf_red4);
                    sfs_red.pushBack(sf_0);
                    //创建动画信息
                    anim_red = Animation::createWithSpriteFrames(sfs_red, 0.1f);
                    //播放砖块破碎动画
                    Sprite* sp_red = Sprite::Sprite::createWithSpriteFrame(sf_red0);
                    sp_red->setPosition(stone[i]->getPosition());
                    addChild(sp_red);
                    sp_red->runAction(Animate::create(anim_red));
                    //移除砖块
                    stone[i]->setVisible(false);
                    pb_stone[i]->setEnabled(false);

                    //小球变为三个红色小球，散射
                    auto texture = Director::getInstance()->getTextureCache()->addImage("ball_red.png");
                    targetA->setTexture(texture);
                    //targetA->setTag(98);
                        //散射小球1
                    ball[1]->runAction(Place::create(Vec2(targetA->getPosition().x - targetA->getContentSize().width, targetA->getPosition().y)));
                    pb_ball[1]->setVelocity(Vec2(-200, -346));
                        //散射小球2
                    ball[2]->setPosition((targetA->getPosition().x + targetA->getContentSize().width), targetA->getPosition().y);
                    pb_ball[2]->setVelocity(Vec2(200, -346));

                    cnt_balls += 2;
                }
                break;

            case 4:         //黄色
                if (stoneState[i] == 1)
                {
                    auto texture = Director::getInstance()->getTextureCache()->addImage("stone_damaged1_yellow.png");
                    stone[i]->setTexture(texture);
                }
                else if (stoneState[i] == 2)
                {
                    auto texture = Director::getInstance()->getTextureCache()->addImage("stone_damaged2_yellow.png");
                    stone[i]->setTexture(texture);
                }
                else if (stoneState[i] == 3)
                {
                    auto texture = Director::getInstance()->getTextureCache()->addImage("stone_damaged3_yellow.png");
                    stone[i]->setTexture(texture);
                }
                else if (stoneState[i] == 4)
                {
                    toNext--;
                    //清除动画数组内容
                    sfs_yellow.clear();
                    //透明纹理
                    auto texture_0 = Director::getInstance()->getTextureCache()->addImage("0.png");
                    sf_0 = SpriteFrame::createWithTexture(texture_0, Rect(0, 0, 5, 5));
                    //用于确定动画帧尺寸
                    Sprite* brk_yellow = Sprite::create("stone_breaking_yellow.png");
                    //纹理
                    auto texture_yellow = Director::getInstance()->getTextureCache()->addImage("stone_breaking_yellow.png");
                    //纹理上的动画帧
                    sf_yellow0 = SpriteFrame::createWithTexture(texture_yellow,
                        Rect(0 * brk_yellow->getContentSize().width / 5, 0,
                            brk_yellow->getContentSize().width / 5, brk_yellow->getContentSize().height));
                    sf_yellow1 = SpriteFrame::createWithTexture(texture_yellow,
                        Rect(1 * brk_yellow->getContentSize().width / 5, 0,
                            brk_yellow->getContentSize().width / 5, brk_yellow->getContentSize().height));
                    sf_yellow2 = SpriteFrame::createWithTexture(texture_yellow,
                        Rect(2 * brk_yellow->getContentSize().width / 5, 0,
                            brk_yellow->getContentSize().width / 5, brk_yellow->getContentSize().height));
                    sf_yellow3 = SpriteFrame::createWithTexture(texture_yellow,
                        Rect(3 * brk_yellow->getContentSize().width / 5, 0,
                            brk_yellow->getContentSize().width / 5, brk_yellow->getContentSize().height));
                    sf_yellow4 = SpriteFrame::createWithTexture(texture_yellow,
                        Rect(4 * brk_yellow->getContentSize().width / 5, 0,
                            brk_yellow->getContentSize().width / 5, brk_yellow->getContentSize().height));
                    //放入动画帧到动画数组
                    sfs_yellow.pushBack(sf_yellow0);
                    sfs_yellow.pushBack(sf_yellow1);
                    sfs_yellow.pushBack(sf_yellow2);
                    sfs_yellow.pushBack(sf_yellow3);
                    sfs_yellow.pushBack(sf_yellow4);
                    sfs_yellow.pushBack(sf_0);
                    //创建动画信息
                    anim_yellow = Animation::createWithSpriteFrames(sfs_yellow, 0.1f);
                    //播放砖块破碎动画
                    Sprite* sp_yellow = Sprite::createWithSpriteFrame(sf_yellow0);
                    sp_yellow->setPosition(stone[i]->getPosition());
                    addChild(sp_yellow);
                    sp_yellow->runAction(Animate::create(anim_yellow));
                    //移除砖块
                    stone[i]->setVisible(false);
                    pb_stone[i]->setEnabled(false);
                }
                break;

            default:
                break;
            }
        }
    }
    

    //普通或红色小球与发射台碰撞
    if (98 == targetA->getTag() && 99 == targetB->getTag())
    {
        Vec2 pos_bat, pos_ball;
        pos_ball = targetA->getPosition();
        pos_bat = targetB->getPosition();
        
        if (pos_ball.x < pos_bat.x - targetB->getContentSize().width / 4)
            targetA->getPhysicsBody()->setVelocity(Vec2(-200, 346));
        else if ((pos_ball.x >= pos_bat.x - targetB->getContentSize().width / 4) && pos_ball.x < pos_bat.x)
            targetA->getPhysicsBody()->setVelocity(Vec2(-100, 346));
        else if ((pos_ball.x <= pos_bat.x + targetB->getContentSize().width / 4) && pos_ball.x > pos_bat.x)
            targetA->getPhysicsBody()->setVelocity(Vec2(-100, 346));
        else if (pos_ball.x > pos_bat.x + targetB->getContentSize().width / 4)
            targetA->getPhysicsBody()->setVelocity(Vec2(200, 346));
    }


    //蓝色小球与发射台碰撞
    if (97 == targetA->getTag() && 99 == targetB->getTag())
    {
        //改变发射台尺寸
        Sprite* bat_huge = Sprite::create("bat_huge.png");
        auto texture = Director::getInstance()->getTextureCache()->addImage("bat_huge.png");
        bat->setContentSize(Size(bat_huge->getContentSize()));
        bat->setTexture(texture);
        
        //bat->setPhysicsBody(pb_bat_huge);

        //startTime = time(NULL); //标记碰撞时间

        Vec2 pos_bat, pos_ball;
        pos_ball = targetA->getPosition();
        pos_bat = targetB->getPosition();

        if (pos_ball.x < pos_bat.x - targetB->getContentSize().width / 4)
            targetA->getPhysicsBody()->setVelocity(Vec2(-200, 346));
        else if ((pos_ball.x >= pos_bat.x - targetB->getContentSize().width / 4) && pos_ball.x < pos_bat.x)
            targetA->getPhysicsBody()->setVelocity(Vec2(-100, 346));
        else if ((pos_ball.x <= pos_bat.x + targetB->getContentSize().width / 4) && pos_ball.x > pos_bat.x)
            targetA->getPhysicsBody()->setVelocity(Vec2(-100, 346));
        else if (pos_ball.x > pos_bat.x + targetB->getContentSize().width / 4)
            targetA->getPhysicsBody()->setVelocity(Vec2(200, 346));
    }


    //小球与边界碰撞
    if ((98 == targetA->getTag() && 95 == targetB->getTag()) || (97 == targetA->getTag() && 95 == targetB->getTag()))
    {
        if (ball[0]->getPosition().y < bat->getPosition().y)
        {
            cnt_balls--;
            if (cnt_balls != 0)
            {
                targetA->runAction(Place::create(Vec2(-100, -100)));
                
            }
            else if (cnt_balls == 0)
            {
                blood--;
                if (blood == 0) //血量为0，游戏失败
                {
                    //已在update中处理
                }
                else
                {
                    isShot = 0;     //设为可发射
                    //重置小球位置，颜色
                    cnt_balls = 1;
                    ball[0]->runAction(Place::create(Vec2(bat->getPosition().x, bat->getPosition().y + bat->getContentSize().height / 2)));
                    auto texture = Director::getInstance()->getTextureCache()->addImage("ball_pinball.png");
                    ball[0]->setTexture(texture);
                    pb_ball[0]->setVelocity(Vec2(0, 0));

                    ball[1]->runAction(Place::create(Vec2(-100, -100)));
                    pb_ball[1]->setVelocity(Vec2(0, 0));

                    ball[2]->runAction(Place::create(Vec2(-100, -200)));
                    pb_ball[2]->setVelocity(Vec2(0, 0));

                    //添加关节
                    pjf = PhysicsJointFixed::construct(pb_bat, pb_ball[0],
                        bat->getPosition() + Vec2(0, bat->getContentSize().height / 2));
                    pw->addJoint(pjf);
                }
            }
        }
    }

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
