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

PhysicsWorld* pw_2;

//�������
PhysicsMaterial pm_bg_2;       //����ǽ�ڲ���
PhysicsMaterial pm_ball_2;     //С�����
PhysicsMaterial pm_bat_2;      //����̨����
PhysicsMaterial pm_stone_2;    //ש�����

//��Ϸ����
Sprite* bgLv1_2;
Sprite* bgLv2_2;
PhysicsBody* pb_bg_2;   //������߽�ȷ��
int flagLv_2 = 2;     //ȷ���ؿ�����ʼ��Ϊ�ڶ���

//��������
    //����̨
Sprite* bat_2;
PhysicsBody* pb_bat_2;
    //С��
Sprite* ball_2[3];
PhysicsBody* pb_ball_2[3];
    //ש��
Sprite* stone_2[45];
PhysicsBody* pb_stone_2[45];
int stoneState_2[45];     //ש��״̬��0-4����ʼΪ0��Ϊ4ʱ������ʧ

PhysicsJointFixed* pjf_2;   //С���뷢��̨�Ĺؽ�

Button* btnPause_2;   //��ͣ��ť
Button* btnQuit_2;    //�˳���ť

//���Ѫ��
Label* lb_blood_2;
int blood_2 = 5;

int bgmID_game_2;  //��Ϸ��������ID

//С���ٶȷ�����
float speedx_2 = 200;
float speedy_2 = 346;
//float speedx_2 = 0;
//float speedy_2 = 346;

bool isShot_2 = 0;  //С���Ƿ���

//�����ж����ҷ�����Ƿ��ڱ����µ�״̬
std::map<cocos2d::EventKeyboard::KeyCode, bool> keys_2;

//ש�����鶯��
Animation* anim_blue_2;
Animation* anim_green_2;
Animation* anim_orange_2;
Animation* anim_red_2;
Animation* anim_yellow_2;

//�����ϵĶ���֡
SpriteFrame* sf_blue0_2;
SpriteFrame* sf_blue1_2;
SpriteFrame* sf_blue2_2;
SpriteFrame* sf_blue3_2;
SpriteFrame* sf_blue4_2;
SpriteFrame* sf_green0_2;
SpriteFrame* sf_green1_2;
SpriteFrame* sf_green2_2;
SpriteFrame* sf_green3_2;
SpriteFrame* sf_green4_2;
SpriteFrame* sf_orange0_2;
SpriteFrame* sf_orange1_2;
SpriteFrame* sf_orange2_2;
SpriteFrame* sf_orange3_2;
SpriteFrame* sf_orange4_2;
SpriteFrame* sf_red0_2;
SpriteFrame* sf_red1_2;
SpriteFrame* sf_red2_2;
SpriteFrame* sf_red3_2;
SpriteFrame* sf_red4_2;
SpriteFrame* sf_yellow0_2;
SpriteFrame* sf_yellow1_2;
SpriteFrame* sf_yellow2_2;
SpriteFrame* sf_yellow3_2;
SpriteFrame* sf_yellow4_2;

SpriteFrame* sf_0_2;

//�洢����֡�ĵ�һ֡
SpriteFrameCache* sfCache_2;

//��������
Vector<SpriteFrame*> sfs_blue_2;
Vector<SpriteFrame*> sfs_green_2;
Vector<SpriteFrame*> sfs_orange_2;
Vector<SpriteFrame*> sfs_red_2;
Vector<SpriteFrame*> sfs_yellow_2;


time_t gameTime_2;
time_t currentTime_2;

//��ɫС����buff����ʱ��
time_t startTime_2;
time_t endTime_2;

int toNext_2 = 45;    //�ж�ש���Ƿ����

bool isPause_2 = false;   //�ж��Ƿ���ͣ

Sprite* bg_Pause_2;   //��ͣ����

//�ж�С������
Button* btn_P_back_2;
Button* btn_P_continue_2;

int cnt_balls_2 = 1;  //�жϳ���С������

Scene* MyGame2::createScene()
{
    MyGame2* sn = (MyGame2*)MyGame2::createWithPhysics();
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
bool MyGame2::initPhysics()
{
    if (!Scene::initWithPhysics())
    {
        return false;
    }

    pw_2 = this->getPhysicsWorld();
    //pw2->setAutoStep(false); //�ر���������ͬ��
    pw_2->setGravity(Vec2(0, -980));  //����
    //pw_2->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);  //��������߽��

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


//���ʳ�ʼ��
    pm_bg_2 = PhysicsMaterial(0, 1, 1000);
    pm_bat_2 = PhysicsMaterial(1000, 1, 0);
    pm_ball_2 = PhysicsMaterial(0, 1, 0);
    pm_stone_2 = PhysicsMaterial(1000, 1, 0);

//���Ʊ���
    bgLv1_2 = Sprite::create("background_level1.png");    //��һ�ر���
    bgLv2_2 = Sprite::create("background_level2.jpg");    //�ڶ��ر���
    bgLv1_2->setPosition(visibleSize / 2);
    bgLv2_2->setPosition(visibleSize / 2);
    bgLv1_2->setTag(95);
    bgLv2_2->setTag(95);
    pb_bg_2 = PhysicsBody::createEdgeBox(visibleSize, pm_bg_2);
    //���ñ�������
    pb_bg_2->setCategoryBitmask(99);
    pb_bg_2->setCollisionBitmask(99);
    pb_bg_2->setContactTestBitmask(99);

    if (flagLv_2 == 1)
    {
        addChild(bgLv1_2);
        bgLv1_2->setPhysicsBody(pb_bg_2);
    }
    else if (flagLv_2 == 2)
    {
        addChild(bgLv2_2);
        bgLv2_2->setPhysicsBody(pb_bg_2);
    }


//������Ϸ�ڱ�������
    AudioEngine::preload("bgm_game1.mp3");
    AudioEngine::preload("bgm_game2.mp3");

    if (flagLv_2 == 1)    //���ŵ�һ�ر�������
        bgmID_game_2 = AudioEngine::play2d("bgm_game1.mp3", true, 0.5f);
    else if (flagLv_2 == 2)   //���ŵڶ��ر�������
        bgmID_game_2 = AudioEngine::play2d("bgm_game2.mp3", true, 0.5f);


//��ʼ����������
    //����̨
    bat_2 = Sprite::create("bat.png");
    bat_2->setPosition(visibleSize.width / 2, visibleSize.height / 8);
    addChild(bat_2);
    pb_bat_2 = PhysicsBody::createBox(bat_2->getContentSize(), pm_bat_2);
    pb_bat_2->setGravityEnable(false);
    bat_2->setPhysicsBody(pb_bat_2);
    bat_2->setTag(99);     //Tag��ǣ�����̨Ϊ99����ͨС��ͺ�ɫС��Ϊ98����ɫС��Ϊ97
    //���÷���̨����
    pb_bat_2->setCategoryBitmask(99);
    pb_bat_2->setCollisionBitmask(98);
    pb_bat_2->setContactTestBitmask(98);

    //С��
    ball_2[0] = Sprite::create("ball_pinball.png");
    ball_2[0]->setPosition(bat_2->getPosition().x, bat_2->getPosition().y + bat_2->getContentSize().height / 2);
    addChild(ball_2[0]);
    pb_ball_2[0] = PhysicsBody::createCircle(ball_2[0]->getContentSize().width / 2, pm_ball_2);
    pb_ball_2[0]->setGravityEnable(false);
    ball_2[0]->setPhysicsBody(pb_ball_2[0]);
        //����С����
    ball_2[0]->setTag(98);
        //����С����ײ����
    pb_ball_2[0]->setCategoryBitmask(99);
    pb_ball_2[0]->setCollisionBitmask(97);
    pb_ball_2[0]->setContactTestBitmask(97);

    //ɢ��С��1
    ball_2[1] = Sprite::create("ball_red.png");
    ball_2[1]->setTag(98);
    ball_2[1]->setPosition(-100, -100);
    addChild(ball_2[1]);
    pb_ball_2[1] = PhysicsBody::createCircle(ball_2[1]->getContentSize().width / 2, pm_ball_2);
    pb_ball_2[1]->setGravityEnable(false);
    ball_2[1]->setPhysicsBody(pb_ball_2[1]);
    pb_ball_2[1]->setCategoryBitmask(99);
    pb_ball_2[1]->setCollisionBitmask(97);
    pb_ball_2[1]->setContactTestBitmask(97);

    //ɢ��С��2
    ball_2[2] = Sprite::create("ball_red.png");
    ball_2[2]->setTag(98);
    ball_2[2]->setPosition(-100, -200);
    addChild(ball_2[2]);
    pb_ball_2[2] = PhysicsBody::createCircle(ball_2[2]->getContentSize().width / 2, pm_ball_2);
    pb_ball_2[2]->setGravityEnable(false);
    ball_2[2]->setPhysicsBody(pb_ball_2[2]);
    pb_ball_2[2]->setCategoryBitmask(99);
    pb_ball_2[2]->setCollisionBitmask(97);
    pb_ball_2[2]->setContactTestBitmask(97);


    //С���뷢��̨����
    pjf_2 = PhysicsJointFixed::construct(pb_bat_2, pb_ball_2[0],
        bat_2->getPosition() + Vec2(0, bat_2->getContentSize().height / 2));
    pw_2->addJoint(pjf_2);

    //ש��
        //��ʼ��ש��״̬
    for (int i = 0; i < 45; i++)
    {
        stoneState_2[i] = 0;  //ש���ʼ��Ϊ���״̬
    }

    if (flagLv_2 == 1)
    {       //�ؿ�1
        for (int i = 0; i < 45; i++)
        {
            switch (i % 5)
            {
            case 0:         //��ɫש��
                stone_2[i] = Sprite::create("stone_normal_blue.png");
                break;

            case 1:         //��ɫ
                stone_2[i] = Sprite::create("stone_normal_green.png");
                break;

            case 2:         //��ɫ
                stone_2[i] = Sprite::create("stone_normal_orange.png");
                break;

            case 3:         //��ɫ
                stone_2[i] = Sprite::create("stone_normal_red.png");
                break;

            case 4:         //��ɫ
                stone_2[i] = Sprite::create("stone_normal_yellow.png");
                break;

            default:
                break;
            }

            if (i < 15)   //��һ��
            {
                stone_2[i]->setPosition(visibleSize.width * ((i % 15) + 1) / 15,
                    visibleSize.height * 9 / 10);
            }
            else if (i >= 15 && i < 30) //�ڶ���
            {
                stone_2[i]->setPosition(visibleSize.width * ((i % 15) + 1) / 15,
                    visibleSize.height * 9 / 10 - stone_2[i]->getContentSize().height);
            }
            else if (i >= 30 && i < 45) //������
            {
                stone_2[i]->setPosition(visibleSize.width * ((i % 15) + 1) / 15,
                    visibleSize.height * 9 / 10 - stone_2[i]->getContentSize().height * 2);
            }
            addChild(stone_2[i]);
            pb_stone_2[i] = PhysicsBody::createBox(stone_2[i]->getContentSize(), pm_stone_2);
            pb_stone_2[i]->setGravityEnable(false);
            stone_2[i]->setPhysicsBody(pb_stone_2[i]);
            stone_2[i]->setTag(i);    //ש��ı��Ϊi���������
            //����ש������
            pb_stone_2[i]->setCategoryBitmask(99);
            pb_stone_2[i]->setCollisionBitmask(1);
            pb_stone_2[i]->setContactTestBitmask(1);
        }
    }
    else if (flagLv_2 == 2)
    {       //�ؿ�2
        for (int i = 0; i < 45; i++)
        {
            switch (i % 5)
            {
            case 0:         //��ɫש��
                stone_2[i] = Sprite::create("stone_normal_blue.png");
                break;

            case 1:         //��ɫ
                stone_2[i] = Sprite::create("stone_normal_green.png");
                break;

            case 2:         //��ɫ
                stone_2[i] = Sprite::create("stone_normal_orange.png");
                break;

            case 3:         //��ɫ
                stone_2[i] = Sprite::create("stone_normal_red.png");
                break;

            case 4:         //��ɫ
                stone_2[i] = Sprite::create("stone_normal_yellow.png");
                break;

            default:
                break;
            }

            if (i < 15)   //��һ��
            {
                stone_2[i]->setPosition(visibleSize.width * ((i % 15) + 1) / 15,
                    visibleSize.height * 9 / 10 - stone_2[i]->getContentSize().height * (i % 4));
            }
            else if (i >= 15 && i < 30) //�ڶ���
            {
                stone_2[i]->setPosition(visibleSize.width * ((i % 15) + 1) / 15,
                    visibleSize.height * 9 / 10 - stone_2[i]->getContentSize().height * ((i % 4) + 1));
            }
            else if (i >= 30 && i < 45) //������
            {
                stone_2[i]->setPosition(visibleSize.width * ((i % 15) + 1) / 15,
                    visibleSize.height * 9 / 10 - stone_2[i]->getContentSize().height * ((i % 4) + 1));
            }
            addChild(stone_2[i]);
            pb_stone_2[i] = PhysicsBody::createBox(stone_2[i]->getContentSize(), pm_stone_2);
            pb_stone_2[i]->setGravityEnable(false);
            stone_2[i]->setPhysicsBody(pb_stone_2[i]);
            stone_2[i]->setTag(i);
            //����ש������
            pb_stone_2[i]->setCategoryBitmask(99);
            pb_stone_2[i]->setCollisionBitmask(0);
            pb_stone_2[i]->setContactTestBitmask(0);
        }
    }


//��ͣ��ť�ڲ��¼�
    //�����ͣ����
    bg_Pause_2 = Sprite::create("pauseboard.png");
    bg_Pause_2->setPosition(visibleSize / 2);
    addChild(bg_Pause_2);
    bg_Pause_2->setVisible(false);

    //��Ӱ�ť
    btn_P_back_2 = Button::create("back_normal.png", "back_selected.png");
    btn_P_back_2->setPosition(Point(visibleSize.width / 2, visibleSize.height * 2 / 5));
    btn_P_back_2->addClickEventListener([=](Ref* pSend)
        {   //��������
            AudioEngine::play2d("click.mp3", false, 0.5f);  //������Ч

            blood_2 = 5;
            isShot_2 = 0;
            toNext_2 = 45;
            auto MainScene = HelloWorld::createScene();
            Director::getInstance()->purgeCachedData();
            Director::getInstance()->replaceScene(MainScene);
            AudioEngine::stop(bgmID_game_2);
        });
    addChild(btn_P_back_2);
    btn_P_back_2->setVisible(false);
    btn_P_back_2->setEnabled(false);

    btn_P_continue_2 = Button::create("continue_normal.png", "continue_selected.png");
    btn_P_continue_2->setPosition(Point(visibleSize.width / 2, visibleSize.height * 3 / 5));
    btn_P_continue_2->setEnabled(true);
    btn_P_continue_2->addClickEventListener([=](Ref* pSend)
        {
            Director::getInstance()->resume();  //����

            bg_Pause_2->setVisible(false);
            btn_P_back_2->setVisible(false);
            btn_P_back_2->setEnabled(false);
            btn_P_continue_2->setVisible(false);
            btn_P_continue_2->setEnabled(false);


        });
    addChild(btn_P_continue_2);
    btn_P_continue_2->setVisible(false);
    btn_P_continue_2->setEnabled(false);

//��ͣ��ť
    btnPause_2 = Button::create("pause_normal.png", "pause_selected.png");
    btnPause_2->setPosition(Point(btnPause_2->getContentSize().width * 3 / 2,
        visibleSize.height - btnPause_2->getContentSize().height / 2));
    btnPause_2->addClickEventListener([=](Ref* pSend)     //��ͣ�¼�
        {
            if (!isPause_2)
            {
                isPause_2 = true;
                AudioEngine::play2d("click.mp3", false, 0.5f);  //������Ч
                //Director::getInstance()->getScheduler()->setTimeScale(0);
                Director::getInstance()->pause();   //��ͣ
                //��ӱ���
                bg_Pause_2->setVisible(true);
                //��Ӱ�ť
                btn_P_back_2->setVisible(true);
                btn_P_back_2->setEnabled(true);
                btn_P_continue_2->setVisible(true);
                btn_P_continue_2->setEnabled(true);
            }
            else
            {
                isPause_2 = false;
                //ɾ������
                bg_Pause_2->setVisible(false);
                //ɾ����ť
                btn_P_back_2->setVisible(false);
                btn_P_back_2->setEnabled(false);
                btn_P_continue_2->setVisible(false);
                btn_P_continue_2->setEnabled(false);
            }
        });
    addChild(btnPause_2);


//�˳���ť
    btnQuit_2 = Button::create("exit_normal.png", "exit_selected.png");
    btnQuit_2->setPosition(Point(btnQuit_2->getContentSize().width / 2,
        visibleSize.height - btnQuit_2->getContentSize().height / 2));
    btnQuit_2->addClickEventListener([=](Ref* pSend)     //�˳��¼�
        {   //�ص�������
            AudioEngine::play2d("click.mp3", false, 0.5f);  //������Ч

            blood_2 = 5;
            isShot_2 = 0;
            toNext_2 = 45;
            auto MainScene = HelloWorld::createScene();
            Director::getInstance()->purgeCachedData();
            Director::getInstance()->replaceScene(MainScene);
            AudioEngine::stop(bgmID_game_2);     //�ر���Ϸ��������

            //Director::getInstance()->end();     //�˳���Ϸ

        });
    addChild(btnQuit_2);


//���Ѫ��
    lb_blood_2 = Label::Label::createWithTTF(std::to_string(blood_2), "fonts//Marker Felt.ttf", 32);
    lb_blood_2->setColor(Color3B::RED);
    lb_blood_2->setPosition(visibleSize.width * 19 / 20, visibleSize.height / 15);
    lb_blood_2->removeFromParent();
    addChild(lb_blood_2);




//������Ϣ��������Ӧ
    //����С��
    EventListenerKeyboard* shootListener = EventListenerKeyboard::create();
    shootListener->onKeyPressed = CC_CALLBACK_2(MyGame2::pressed_Shoot, this);
        
    //����̨�����ƶ�
    EventListenerKeyboard* moveListener = EventListenerKeyboard::create();
    moveListener->onKeyPressed = CC_CALLBACK_2(MyGame2::pressed_batMove, this);
    moveListener->onKeyReleased = CC_CALLBACK_2(MyGame2::released_batMove, this);

    EventDispatcher* dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addEventListenerWithSceneGraphPriority(shootListener, this);
    dispatcher->addEventListenerWithSceneGraphPriority(moveListener, this);

    schedule(CC_SCHEDULE_SELECTOR(MyGame2::gameUpdate), 0.01f);  //update����




//��ײ��Ӧ
    EventListenerPhysicsContact* elpc = EventListenerPhysicsContact::create();
    elpc->onContactBegin = CC_CALLBACK_1(MyGame2::isCld, this);
    EventDispatcher* ed = Director::getInstance()->getEventDispatcher();
    ed->addEventListenerWithSceneGraphPriority(elpc, this);



    



    //scheduleUpdate();
    //Director::getInstance()->getScheduler()->scheduleUpdate(this, 0, false);

    return true;
}

void MyGame2::pressed_Shoot(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();

    if (EventKeyboard::KeyCode::KEY_Z == keycode)   // ����z��������С��
    {
        if (!isShot_2)
        {
            pb_ball_2[0]->setVelocity(Vec2(speedx_2, speedy_2));  //������60�ȷ���С��
            //ɾ���ؽ�
            pw_2->removeJoint(pjf_2);
            isShot_2 = 1;
        }
    }
}

void MyGame2::pressed_batMove(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event)
{
    keys_2[keycode] = true;
    //log("1");
}

void MyGame2::released_batMove(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event)
{
    keys_2[keycode] = false;
    //log("2");
}

bool MyGame2::isKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode)
{
    if (keys_2[keyCode])
        return true;
    else
        return false;
}

void MyGame2::keyPressedDuration(cocos2d::EventKeyboard::KeyCode code)   //���������ƶ���Ϣ��Ӧ�¼�
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

    auto moveTo = MoveTo::create(0.3, Vec2(bat_2->getPositionX() + offsetX, bat_2->getPositionY() + offsetY));
    bat_2->runAction(moveTo);
}

void MyGame2::gameUpdate(float dt)
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

    lb_blood_2->setString(std::to_string(blood_2));     //����Ѫ��

    //endTime_2 = time(NULL);
    //if (endTime_2 - startTime_2 == 10)  //���Ч������10��
    //{
    //    Sprite* bat_normal = Sprite::create("bat.png");
    //    auto texture = Director::getInstance()->getTextureCache()->addImage("bat.png");
    //    bat_2->setContentSize(Size(bat_normal->getContentSize()));
    //    bat_2->setScale(bat_normal->getScale());
    //    bat_2->setTexture(texture);
    //    PhysicsBody* pb_bat_normal = PhysicsBody::createBox(bat_2->getContentSize(), pm_bat_2);
    //    pb_bat_normal->setGravityEnable(false);
    //    bat_2->setPhysicsBody(pb_bat_normal);
    //}

    if (toNext_2 == 0 && flagLv_2 == 1)     //��ת����һ��
    {
        flagLv_2 = 2;


        toNext_2 = 45;
    }
    else if (toNext_2 == 0 && flagLv_2 == 2)    //��ת����Ϸʤ������
    {
        blood_2 = 5;
        isShot_2 = 0;
        toNext_2 = 45;
        auto WinScene = GameWin::createScene();
        Director::getInstance()->purgeCachedData();
        Director::getInstance()->replaceScene(WinScene);
        AudioEngine::stop(bgmID_game_2);

        toNext_2 = 1;
    }

    if (blood_2 == 0)     //Ѫ��Ϊ0����Ϸʧ��
    {
        blood_2 = 5;
        isShot_2 = 0;
        toNext_2 = 45;
        auto LoseScene = GameLose::createScene();
        Director::getInstance()->purgeCachedData();
        Director::getInstance()->replaceScene(LoseScene);
        AudioEngine::stop(bgmID_game_2);
    }
}

bool MyGame2::isCld(cocos2d::PhysicsContact& contact)    //��ײ��Ӧ
{
    Size visibleSize = Director::getInstance()->getVisibleSize();

    Sprite* targetA = (Sprite*)contact.getShapeA()->getBody()->getNode();
    Sprite* targetB = (Sprite*)contact.getShapeB()->getBody()->getNode();


    //С����ש����ײ
    for (int i = 0; i < 45; i++)
    {
        if ((98 == targetA->getTag() && i == targetB->getTag()) || (97 == targetA->getTag() && i == targetB->getTag()))
        {
            //ײ����Ч
            AudioEngine::play2d("cld.mp3", false, 0.5f);  //������Ч
        

            //����
            /*Sprite* sp = Sprite::createWithSpriteFrame(sf_blue0_2);
            sp->setPosition(VisibleSize / 2);
            addChild(sp);
            
            //gameTime_2 = time(NULL);

            //sp->runAction(Animate::create(animCache->getAnimation("anim_b")));
            sp->runAction(Animate::create(anim_blue_2));

            currentTime_2 = time(NULL);
            if (currentTime_2 - gameTime_2 == 0.5f)
                sp->removeFromParent();*/
            
            //log("hit");
            stoneState_2[i]++;    //ש������̶�����

            switch (i % 5)
            {
            case 0:         //��ɫש��
                if (stoneState_2[i] == 1)
                {
                    auto texture = Director::getInstance()->getTextureCache()->addImage("stone_damaged1_blue.png");
                    stone_2[i]->setTexture(texture);
                }
                else if (stoneState_2[i] == 2)
                {
                    auto texture = Director::getInstance()->getTextureCache()->addImage("stone_damaged2_blue.png");
                    stone_2[i]->setTexture(texture);
                }
                else if (stoneState_2[i] == 3)
                {
                    auto texture = Director::getInstance()->getTextureCache()->addImage("stone_damaged3_blue.png");
                    stone_2[i]->setTexture(texture);
                }
                else if (stoneState_2[i] == 4)
                {
                    toNext_2--;
                //ש�����鶯��
                    //���������������
                    sfs_blue_2.clear();
                    //͸������
                    auto texture_0 = Director::getInstance()->getTextureCache()->addImage("0.png");
                    sf_0_2 = SpriteFrame::createWithTexture(texture_0, Rect(0, 0, 5, 5));
                    //����ȷ������֡�ߴ�
                    Sprite* brk_blue = Sprite::create("stone_breaking_blue.png");
                    //����
                    auto texture_blue = Director::getInstance()->getTextureCache()->addImage("stone_breaking_blue.png");
                    //�����ϵĶ���֡
                    sf_blue0_2 = SpriteFrame::createWithTexture(texture_blue,
                        Rect(0 * brk_blue->getContentSize().width / 5, 0,
                            brk_blue->getContentSize().width / 5, brk_blue->getContentSize().height));
                    sf_blue1_2 = SpriteFrame::createWithTexture(texture_blue,
                        Rect(1 * brk_blue->getContentSize().width / 5, 0,
                            brk_blue->getContentSize().width / 5, brk_blue->getContentSize().height));
                    sf_blue2_2 = SpriteFrame::createWithTexture(texture_blue,
                        Rect(2 * brk_blue->getContentSize().width / 5, 0,
                            brk_blue->getContentSize().width / 5, brk_blue->getContentSize().height));
                    sf_blue3_2 = SpriteFrame::createWithTexture(texture_blue,
                        Rect(3 * brk_blue->getContentSize().width / 5, 0,
                            brk_blue->getContentSize().width / 5, brk_blue->getContentSize().height));
                    sf_blue4_2 = SpriteFrame::createWithTexture(texture_blue,
                        Rect(4 * brk_blue->getContentSize().width / 5, 0,
                            brk_blue->getContentSize().width / 5, brk_blue->getContentSize().height));
                    //���붯��֡����������
                    sfs_blue_2.pushBack(sf_blue0_2);
                    sfs_blue_2.pushBack(sf_blue1_2);
                    sfs_blue_2.pushBack(sf_blue2_2);
                    sfs_blue_2.pushBack(sf_blue3_2);
                    sfs_blue_2.pushBack(sf_blue4_2);
                    sfs_blue_2.pushBack(sf_0_2);
                    //����������Ϣ
                    anim_blue_2 = Animation::createWithSpriteFrames(sfs_blue_2, 0.1f);
                    //����ש�����鶯��
                    Sprite* sp = Sprite::createWithSpriteFrame(sf_blue0_2);
                    sp->setPosition(stone_2[i]->getPosition());
                    addChild(sp);
                    sp->runAction(Animate::create(anim_blue_2));
                    //�Ƴ�ש��
                    stone_2[i]->setVisible(false);
                    pb_stone_2[i]->setEnabled(false);

                    //С���Ϊ��ɫ
                    auto texture = Director::getInstance()->getTextureCache()->addImage("ball_blue.png");
                    targetA->setTexture(texture);
                    targetA->setTag(97);
                }
                break;

            case 1:         //��ɫ
                if (stoneState_2[i] == 1)
                {
                    auto texture = Director::getInstance()->getTextureCache()->addImage("stone_damaged1_green.png");
                    stone_2[i]->setTexture(texture);
                }
                else if (stoneState_2[i] == 2)
                {
                    auto texture = Director::getInstance()->getTextureCache()->addImage("stone_damaged2_green.png");
                    stone_2[i]->setTexture(texture);
                }
                else if (stoneState_2[i] == 3)
                {
                    auto texture = Director::getInstance()->getTextureCache()->addImage("stone_damaged3_green.png");
                    stone_2[i]->setTexture(texture);
                }
                else if (stoneState_2[i] == 4)
                {
                    toNext_2--;
                    //���������������
                    sfs_green_2.clear();
                    //͸������
                    auto texture_0 = Director::getInstance()->getTextureCache()->addImage("0.png");
                    sf_0_2 = SpriteFrame::createWithTexture(texture_0, Rect(0, 0, 5, 5));
                    //����ȷ������֡�ߴ�
                    Sprite* brk_green = Sprite::create("stone_breaking_green.png");
                    //����
                    auto texture_green = Director::getInstance()->getTextureCache()->addImage("stone_breaking_green.png");
                    //�����ϵĶ���֡
                    sf_green0_2 = SpriteFrame::createWithTexture(texture_green,
                        Rect(0 * brk_green->getContentSize().width / 5, 0,
                            brk_green->getContentSize().width / 5, brk_green->getContentSize().height));
                    sf_green1_2 = SpriteFrame::createWithTexture(texture_green,
                        Rect(1 * brk_green->getContentSize().width / 5, 0,
                            brk_green->getContentSize().width / 5, brk_green->getContentSize().height));
                    sf_green2_2 = SpriteFrame::createWithTexture(texture_green,
                        Rect(2 * brk_green->getContentSize().width / 5, 0,
                            brk_green->getContentSize().width / 5, brk_green->getContentSize().height));
                    sf_green3_2 = SpriteFrame::createWithTexture(texture_green,
                        Rect(3 * brk_green->getContentSize().width / 5, 0,
                            brk_green->getContentSize().width / 5, brk_green->getContentSize().height));
                    sf_green4_2 = SpriteFrame::createWithTexture(texture_green,
                        Rect(4 * brk_green->getContentSize().width / 5, 0,
                            brk_green->getContentSize().width / 5, brk_green->getContentSize().height));
                    //���붯��֡����������
                    sfs_green_2.pushBack(sf_green0_2);
                    sfs_green_2.pushBack(sf_green1_2);
                    sfs_green_2.pushBack(sf_green2_2);
                    sfs_green_2.pushBack(sf_green3_2);
                    sfs_green_2.pushBack(sf_green4_2);
                    sfs_green_2.pushBack(sf_0_2);
                    //����������Ϣ
                    anim_green_2 = Animation::createWithSpriteFrames(sfs_green_2, 0.1f);
                    //����ש�����鶯��
                    Sprite* sp_green = Sprite::createWithSpriteFrame(sf_green0_2);
                    sp_green->setPosition(stone_2[i]->getPosition());
                    addChild(sp_green);
                    sp_green->runAction(Animate::create(anim_green_2));
                    //�Ƴ�ש��
                    stone_2[i]->setVisible(false);   
                    pb_stone_2[i]->setEnabled(false);
                }
                break;

            case 2:         //��ɫ
                if (stoneState_2[i] == 1)
                {
                    auto texture = Director::getInstance()->getTextureCache()->addImage("stone_damaged1_orange.png");
                    stone_2[i]->setTexture(texture);
                }
                else if (stoneState_2[i] == 2)
                {
                    auto texture = Director::getInstance()->getTextureCache()->addImage("stone_damaged2_orange.png");
                    stone_2[i]->setTexture(texture);
                }
                else if (stoneState_2[i] == 3)
                {
                    auto texture = Director::getInstance()->getTextureCache()->addImage("stone_damaged3_orange.png");
                    stone_2[i]->setTexture(texture);
                }
                else if (stoneState_2[i] == 4)
                {
                    toNext_2--;
                    //���������������
                    sfs_orange_2.clear();
                    //͸������
                    auto texture_0 = Director::getInstance()->getTextureCache()->addImage("0.png");
                    sf_0_2 = SpriteFrame::createWithTexture(texture_0, Rect(0, 0, 5, 5));
                    //����ȷ������֡�ߴ�
                    Sprite* brk_orange = Sprite::create("stone_breaking_orange.png");
                    //����
                    auto texture_orange = Director::getInstance()->getTextureCache()->addImage("stone_breaking_orange.png");
                    //�����ϵĶ���֡
                    sf_orange0_2 = SpriteFrame::createWithTexture(texture_orange,
                        Rect(0 * brk_orange->getContentSize().width / 5, 0,
                            brk_orange->getContentSize().width / 5, brk_orange->getContentSize().height));
                    sf_orange1_2 = SpriteFrame::createWithTexture(texture_orange,
                        Rect(1 * brk_orange->getContentSize().width / 5, 0,
                            brk_orange->getContentSize().width / 5, brk_orange->getContentSize().height));
                    sf_orange2_2 = SpriteFrame::createWithTexture(texture_orange,
                        Rect(2 * brk_orange->getContentSize().width / 5, 0,
                            brk_orange->getContentSize().width / 5, brk_orange->getContentSize().height));
                    sf_orange3_2 = SpriteFrame::createWithTexture(texture_orange,
                        Rect(3 * brk_orange->getContentSize().width / 5, 0,
                            brk_orange->getContentSize().width / 5, brk_orange->getContentSize().height));
                    sf_orange4_2 = SpriteFrame::createWithTexture(texture_orange,
                        Rect(4 * brk_orange->getContentSize().width / 5, 0,
                            brk_orange->getContentSize().width / 5, brk_orange->getContentSize().height));
                    //���붯��֡����������
                    sfs_orange_2.pushBack(sf_orange0_2);
                    sfs_orange_2.pushBack(sf_orange1_2);
                    sfs_orange_2.pushBack(sf_orange2_2);
                    sfs_orange_2.pushBack(sf_orange3_2);
                    sfs_orange_2.pushBack(sf_orange4_2);
                    sfs_orange_2.pushBack(sf_0_2);
                    //����������Ϣ
                    anim_orange_2 = Animation::createWithSpriteFrames(sfs_orange_2, 0.1f);
                    //����ש�����鶯��
                    Sprite* sp_orange = Sprite::createWithSpriteFrame(sf_orange0_2);
                    sp_orange->setPosition(stone_2[i]->getPosition());
                    addChild(sp_orange);
                    sp_orange->runAction(Animate::create(anim_orange_2));
                    //�Ƴ�ש��
                    stone_2[i]->setVisible(false);
                    pb_stone_2[i]->setEnabled(false);
                }
                break;

            case 3:         //��ɫ
                if (stoneState_2[i] == 1)
                {
                    auto texture = Director::getInstance()->getTextureCache()->addImage("stone_damaged1_red.png");
                    stone_2[i]->setTexture(texture);
                }
                else if (stoneState_2[i] == 2)
                {
                    auto texture = Director::getInstance()->getTextureCache()->addImage("stone_damaged2_red.png");
                    stone_2[i]->setTexture(texture);
                }
                else if (stoneState_2[i] == 3)
                {
                    auto texture = Director::getInstance()->getTextureCache()->addImage("stone_damaged3_red.png");
                    stone_2[i]->setTexture(texture);
                }
                else if (stoneState_2[i] == 4)
                {
                    toNext_2--;
                    //���������������
                    sfs_red_2.clear();
                    //͸������
                    auto texture_0 = Director::getInstance()->getTextureCache()->addImage("0.png");
                    sf_0_2 = SpriteFrame::createWithTexture(texture_0, Rect(0, 0, 5, 5));
                    //����ȷ������֡�ߴ�
                    Sprite* brk_red = Sprite::create("stone_breaking_red.png");
                    //����
                    auto texture_red = Director::getInstance()->getTextureCache()->addImage("stone_breaking_red.png");
                    //�����ϵĶ���֡
                    sf_red0_2 = SpriteFrame::createWithTexture(texture_red,
                        Rect(0 * brk_red->getContentSize().width / 5, 0,
                            brk_red->getContentSize().width / 5, brk_red->getContentSize().height));
                    sf_red1_2 = SpriteFrame::createWithTexture(texture_red,
                        Rect(1 * brk_red->getContentSize().width / 5, 0,
                            brk_red->getContentSize().width / 5, brk_red->getContentSize().height));
                    sf_red2_2 = SpriteFrame::createWithTexture(texture_red,
                        Rect(2 * brk_red->getContentSize().width / 5, 0,
                            brk_red->getContentSize().width / 5, brk_red->getContentSize().height));
                    sf_red3_2 = SpriteFrame::createWithTexture(texture_red,
                        Rect(3 * brk_red->getContentSize().width / 5, 0,
                            brk_red->getContentSize().width / 5, brk_red->getContentSize().height));
                    sf_red4_2 = SpriteFrame::createWithTexture(texture_red,
                        Rect(4 * brk_red->getContentSize().width / 5, 0,
                            brk_red->getContentSize().width / 5, brk_red->getContentSize().height));
                    //���붯��֡����������
                    sfs_red_2.pushBack(sf_red0_2);
                    sfs_red_2.pushBack(sf_red1_2);
                    sfs_red_2.pushBack(sf_red2_2);
                    sfs_red_2.pushBack(sf_red3_2);
                    sfs_red_2.pushBack(sf_red4_2);
                    sfs_red_2.pushBack(sf_0_2);
                    //����������Ϣ
                    anim_red_2 = Animation::createWithSpriteFrames(sfs_red_2, 0.1f);
                    //����ש�����鶯��
                    Sprite* sp_red = Sprite::Sprite::createWithSpriteFrame(sf_red0_2);
                    sp_red->setPosition(stone_2[i]->getPosition());
                    addChild(sp_red);
                    sp_red->runAction(Animate::create(anim_red_2));
                    //�Ƴ�ש��
                    stone_2[i]->setVisible(false);
                    pb_stone_2[i]->setEnabled(false);

                    //С���Ϊ������ɫС��ɢ��
                    auto texture = Director::getInstance()->getTextureCache()->addImage("ball_red.png");
                    targetA->setTexture(texture);
                    //targetA->setTag(98);
                    //ɢ��С��1
                    ball_2[1]->runAction(Place::create(Vec2(targetA->getPosition().x - targetA->getContentSize().width, targetA->getPosition().y)));
                    pb_ball_2[1]->setVelocity(Vec2(-200, -346));
                    //ɢ��С��2
                    ball_2[2]->setPosition((targetA->getPosition().x + targetA->getContentSize().width), targetA->getPosition().y);
                    pb_ball_2[2]->setVelocity(Vec2(200, -346));

                    cnt_balls_2 += 2;
                }
                break;

            case 4:         //��ɫ
                if (stoneState_2[i] == 1)
                {
                    auto texture = Director::getInstance()->getTextureCache()->addImage("stone_damaged1_yellow.png");
                    stone_2[i]->setTexture(texture);
                }
                else if (stoneState_2[i] == 2)
                {
                    auto texture = Director::getInstance()->getTextureCache()->addImage("stone_damaged2_yellow.png");
                    stone_2[i]->setTexture(texture);
                }
                else if (stoneState_2[i] == 3)
                {
                    auto texture = Director::getInstance()->getTextureCache()->addImage("stone_damaged3_yellow.png");
                    stone_2[i]->setTexture(texture);
                }
                else if (stoneState_2[i] == 4)
                {
                    toNext_2--;
                    //���������������
                    sfs_yellow_2.clear();
                    //͸������
                    auto texture_0 = Director::getInstance()->getTextureCache()->addImage("0.png");
                    sf_0_2 = SpriteFrame::createWithTexture(texture_0, Rect(0, 0, 5, 5));
                    //����ȷ������֡�ߴ�
                    Sprite* brk_yellow = Sprite::create("stone_breaking_yellow.png");
                    //����
                    auto texture_yellow = Director::getInstance()->getTextureCache()->addImage("stone_breaking_yellow.png");
                    //�����ϵĶ���֡
                    sf_yellow0_2 = SpriteFrame::createWithTexture(texture_yellow,
                        Rect(0 * brk_yellow->getContentSize().width / 5, 0,
                            brk_yellow->getContentSize().width / 5, brk_yellow->getContentSize().height));
                    sf_yellow1_2 = SpriteFrame::createWithTexture(texture_yellow,
                        Rect(1 * brk_yellow->getContentSize().width / 5, 0,
                            brk_yellow->getContentSize().width / 5, brk_yellow->getContentSize().height));
                    sf_yellow2_2 = SpriteFrame::createWithTexture(texture_yellow,
                        Rect(2 * brk_yellow->getContentSize().width / 5, 0,
                            brk_yellow->getContentSize().width / 5, brk_yellow->getContentSize().height));
                    sf_yellow3_2 = SpriteFrame::createWithTexture(texture_yellow,
                        Rect(3 * brk_yellow->getContentSize().width / 5, 0,
                            brk_yellow->getContentSize().width / 5, brk_yellow->getContentSize().height));
                    sf_yellow4_2 = SpriteFrame::createWithTexture(texture_yellow,
                        Rect(4 * brk_yellow->getContentSize().width / 5, 0,
                            brk_yellow->getContentSize().width / 5, brk_yellow->getContentSize().height));
                    //���붯��֡����������
                    sfs_yellow_2.pushBack(sf_yellow0_2);
                    sfs_yellow_2.pushBack(sf_yellow1_2);
                    sfs_yellow_2.pushBack(sf_yellow2_2);
                    sfs_yellow_2.pushBack(sf_yellow3_2);
                    sfs_yellow_2.pushBack(sf_yellow4_2);
                    sfs_yellow_2.pushBack(sf_0_2);
                    //����������Ϣ
                    anim_yellow_2 = Animation::createWithSpriteFrames(sfs_yellow_2, 0.1f);
                    //����ש�����鶯��
                    Sprite* sp_yellow = Sprite::createWithSpriteFrame(sf_yellow0_2);
                    sp_yellow->setPosition(stone_2[i]->getPosition());
                    addChild(sp_yellow);
                    sp_yellow->runAction(Animate::create(anim_yellow_2));
                    //�Ƴ�ש��
                    stone_2[i]->setVisible(false);
                    pb_stone_2[i]->setEnabled(false);
                }
                break;

            default:
                break;
            }
        }
    }
    

    //��ͨ���ɫС���뷢��̨��ײ
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


    //��ɫС���뷢��̨��ײ
    if (97 == targetA->getTag() && 99 == targetB->getTag())
    {
        Sprite* bat_huge = Sprite::create("bat_huge.png");
        auto texture = Director::getInstance()->getTextureCache()->addImage("bat_huge.png");
        targetB->setContentSize(Size(bat_huge->getContentSize()));
        targetB->setScale(bat_huge->getScale());
        targetB->setTexture(texture);
        /*PhysicsBody* pb_bat_huge = PhysicsBody::createBox(targetB->getContentSize(), pm_bat_2);
        pb_bat_huge->setGravityEnable(false);
        targetB->setPhysicsBody(pb_bat_huge);*/

        //startTime_2 = time(NULL); //�����ײʱ��

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


    //С����߽���ײ
    if ((98 == targetA->getTag() && 95 == targetB->getTag()) || (97 == targetA->getTag() && 95 == targetB->getTag()))
    {
        if (ball_2[0]->getPosition().y < bat_2->getPosition().y)
        {
            cnt_balls_2--;
            if (cnt_balls_2 != 0)
            {
                targetA->runAction(Place::create(Vec2(-100, -100)));
            }
            else if (cnt_balls_2 == 0)
            {
                blood_2--;
                if (blood_2 == 0) //Ѫ��Ϊ0����Ϸʧ��
                {
                    //�Ѵ���
                }
                else
                {
                    cnt_balls_2 = 1;
                    isShot_2 = 0;     //��Ϊ�ɷ���
                    //����С��λ�ã���ɫ
                    ball_2[0]->runAction(Place::create(Vec2(bat_2->getPosition().x, bat_2->getPosition().y + bat_2->getContentSize().height / 2)));
                    auto texture = Director::getInstance()->getTextureCache()->addImage("ball_pinball.png");
                    ball_2[0]->setTexture(texture);
                    pb_ball_2[0]->setVelocity(Vec2(0, 0));
                    
                    ball_2[1]->runAction(Place::create(Vec2(-100, -100)));
                    pb_ball_2[1]->setVelocity(Vec2(0, 0));

                    ball_2[2]->runAction(Place::create(Vec2(-100, -200)));
                    pb_ball_2[2]->setVelocity(Vec2(0, 0));

                    //��ӹؽ�
                    pjf_2 = PhysicsJointFixed::construct(pb_bat_2, pb_ball_2[0],
                        bat_2->getPosition() + Vec2(0, bat_2->getContentSize().height / 2));
                    pw_2->addJoint(pjf_2);
                }
            }
        }
    }

    return true;
}

void MyGame2::update(float dt)
{
    //pw2->step(0.01f);

}


void MyGame2::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
