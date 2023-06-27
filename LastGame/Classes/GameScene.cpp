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

//�������
PhysicsMaterial pm_bg;       //����ǽ�ڲ���
PhysicsMaterial pm_ball;     //С�����
PhysicsMaterial pm_bat;      //����̨����
PhysicsMaterial pm_stone;    //ש�����

//��Ϸ����
Sprite* bgLv1;
Sprite* bgLv2;
PhysicsBody* pb_bg;   //������߽�ȷ��
int flagLv = 1;     //ȷ���ؿ�����ʼ��Ϊ��һ��

//��������
    //����̨
Sprite* bat;
PhysicsBody* pb_bat;
    //С��
Sprite* ball[3];
PhysicsBody* pb_ball[3];
    //ש��
Sprite* stone[45];
PhysicsBody* pb_stone[45];
int stoneState[45];     //ש��״̬��0-4����ʼΪ0��Ϊ4ʱ������ʧ

PhysicsJointFixed* pjf;   //С���뷢��̨�Ĺؽ�

Button* btnPause;   //��ͣ��ť
Button* btnQuit;    //�˳���ť

//���Ѫ��
Label* lb_blood;
int blood = 5;

int bgmID_game;  //��Ϸ��������ID

//С���ٶȷ�����
float speedx = 200;
float speedy = 346;
//float speedx = 0;
//float speedy = 346;

bool isShot = 0;  //С���Ƿ���

//�����ж����ҷ�����Ƿ��ڱ����µ�״̬
std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;

//ש�����鶯��
Animation* anim_blue;
Animation* anim_green;
Animation* anim_orange;
Animation* anim_red;
Animation* anim_yellow;

//�����ϵĶ���֡
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

//�洢����֡�ĵ�һ֡
SpriteFrameCache* sfCache;

//��������
Vector<SpriteFrame*> sfs_blue;
Vector<SpriteFrame*> sfs_green;
Vector<SpriteFrame*> sfs_orange;
Vector<SpriteFrame*> sfs_red;
Vector<SpriteFrame*> sfs_yellow;


time_t gameTime;
time_t currentTime;

//��ɫС����buff����ʱ��
time_t startTime;
time_t endTime;

PhysicsBody* pb_bat_huge;

int toNext = 45;    //�ж�ש���Ƿ����

bool isPause = false;   //�ж��Ƿ���ͣ

//��ͣ����
Sprite* bg_Pause;   //��ͣ����

Button* btn_P_back;
Button* btn_P_continue;

int cnt_balls = 1;  //�жϳ���С������


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
    //pw->setAutoStep(false); //�ر���������ͬ��
    pw->setGravity(Vec2(0, -980));  //����
    //pw->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);  //��������߽��

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


//���ʳ�ʼ��
    pm_bg = PhysicsMaterial(0, 1, 1000);
    pm_bat = PhysicsMaterial(1000, 1, 0);
    pm_ball = PhysicsMaterial(0, 1, 0);
    pm_stone = PhysicsMaterial(1000, 1, 0);

//���Ʊ���
    bgLv1 = Sprite::create("background_level1.png");    //��һ�ر���
    bgLv2 = Sprite::create("background_level2.jpg");    //�ڶ��ر���
    bgLv1->setPosition(visibleSize / 2);
    bgLv2->setPosition(visibleSize / 2);
    bgLv1->setTag(95);
    bgLv2->setTag(95);
    pb_bg = PhysicsBody::createEdgeBox(visibleSize, pm_bg);
    //���ñ�������
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


//������Ϸ�ڱ�������
    AudioEngine::preload("bgm_game1.mp3");
    AudioEngine::preload("bgm_game2.mp3");

    if (flagLv == 1)    //���ŵ�һ�ر�������
        bgmID_game = AudioEngine::play2d("bgm_game1.mp3", true, 0.5f);
    else if (flagLv == 2)   //���ŵڶ��ر�������
        bgmID_game = AudioEngine::play2d("bgm_game2.mp3", true, 0.5f);


//��ʼ����������
    //����̨
    bat = Sprite::create("bat.png");
    Sprite* bat_h = Sprite::create("bat_huge.png");
    bat->setPosition(visibleSize.width / 2, visibleSize.height / 8);
    addChild(bat);
    pb_bat = PhysicsBody::createBox(bat->getContentSize(), pm_bat);
    pb_bat->setGravityEnable(false);
    bat->setPhysicsBody(pb_bat);
    pb_bat_huge = PhysicsBody::createBox(bat_h->getContentSize(), pm_bat);
    pb_bat_huge->setGravityEnable(false);

    bat->setTag(99);     //Tag��ǣ�����̨Ϊ99����ͨС��ͺ�ɫС��Ϊ98����ɫС��Ϊ97
    //���÷���̨����
    pb_bat->setCategoryBitmask(99);
    pb_bat->setCollisionBitmask(98);
    pb_bat->setContactTestBitmask(98);

    //С��
    ball[0] = Sprite::create("ball_pinball.png");
    ball[0]->setPosition(bat->getPosition().x, bat->getPosition().y + bat->getContentSize().height / 2);
    addChild(ball[0]);
    pb_ball[0] = PhysicsBody::createCircle(ball[0]->getContentSize().width / 2, pm_ball);
    pb_ball[0]->setGravityEnable(false);
    ball[0]->setPhysicsBody(pb_ball[0]);
        //����С����
    ball[0]->setTag(98);
        //����С����ײ����
    pb_ball[0]->setCategoryBitmask(99);
    pb_ball[0]->setCollisionBitmask(97);
    pb_ball[0]->setContactTestBitmask(97);

    //ɢ��С��1
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
    
    //ɢ��С��2
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



    //С���뷢��̨����
    pjf = PhysicsJointFixed::construct(pb_bat, pb_ball[0],
        bat->getPosition() + Vec2(0, bat->getContentSize().height / 2));
    pw->addJoint(pjf);

    //ש��
        //��ʼ��ש��״̬
    for (int i = 0; i < 45; i++)
    {
        stoneState[i] = 0;  //ש���ʼ��Ϊ���״̬
    }

    if (flagLv == 1)
    {       //�ؿ�1
        for (int i = 0; i < 45; i++)
        {
            switch (i % 5)
            {
            case 0:         //��ɫש��
                stone[i] = Sprite::create("stone_normal_blue.png");
                break;

            case 1:         //��ɫ
                stone[i] = Sprite::create("stone_normal_green.png");
                break;

            case 2:         //��ɫ
                stone[i] = Sprite::create("stone_normal_orange.png");
                break;

            case 3:         //��ɫ
                stone[i] = Sprite::create("stone_normal_red.png");
                break;

            case 4:         //��ɫ
                stone[i] = Sprite::create("stone_normal_yellow.png");
                break;

            default:
                break;
            }

            if (i < 15)   //��һ��
            {
                stone[i]->setPosition(visibleSize.width * ((i % 15) + 1) / 15,
                    visibleSize.height * 9 / 10);
            }
            else if (i >= 15 && i < 30) //�ڶ���
            {
                stone[i]->setPosition(visibleSize.width * ((i % 15) + 1) / 15,
                    visibleSize.height * 9 / 10 - stone[i]->getContentSize().height);
            }
            else if (i >= 30 && i < 45) //������
            {
                stone[i]->setPosition(visibleSize.width * ((i % 15) + 1) / 15,
                    visibleSize.height * 9 / 10 - stone[i]->getContentSize().height * 2);
            }
            addChild(stone[i]);
            pb_stone[i] = PhysicsBody::createBox(stone[i]->getContentSize(), pm_stone);
            pb_stone[i]->setGravityEnable(false);
            stone[i]->setPhysicsBody(pb_stone[i]);
            stone[i]->setTag(i);    //ש��ı��Ϊi���������
            //����ש������
            pb_stone[i]->setCategoryBitmask(99);
            pb_stone[i]->setCollisionBitmask(1);
            pb_stone[i]->setContactTestBitmask(1);
        }
    }
    else if (flagLv == 2)
    {       //�ؿ�2
        for (int i = 0; i < 45; i++)
        {
            switch (i % 5)
            {
            case 0:         //��ɫש��
                stone[i] = Sprite::create("stone_normal_blue.png");
                break;

            case 1:         //��ɫ
                stone[i] = Sprite::create("stone_normal_green.png");
                break;

            case 2:         //��ɫ
                stone[i] = Sprite::create("stone_normal_orange.png");
                break;

            case 3:         //��ɫ
                stone[i] = Sprite::create("stone_normal_red.png");
                break;

            case 4:         //��ɫ
                stone[i] = Sprite::create("stone_normal_yellow.png");
                break;

            default:
                break;
            }

            if (i < 15)   //��һ��
            {
                stone[i]->setPosition(visibleSize.width * ((i % 15) + 1) / 15,
                    visibleSize.height * 9 / 10 - stone[i]->getContentSize().height * (i % 4));
            }
            else if (i >= 15 && i < 30) //�ڶ���
            {
                stone[i]->setPosition(visibleSize.width * ((i % 15) + 1) / 15,
                    visibleSize.height * 9 / 10 - stone[i]->getContentSize().height * ((i % 4) + 1));
            }
            else if (i >= 30 && i < 45) //������
            {
                stone[i]->setPosition(visibleSize.width * ((i % 15) + 1) / 15,
                    visibleSize.height * 9 / 10 - stone[i]->getContentSize().height * ((i % 4) + 1));
            }
            addChild(stone[i]);
            pb_stone[i] = PhysicsBody::createBox(stone[i]->getContentSize(), pm_stone);
            pb_stone[i]->setGravityEnable(false);
            stone[i]->setPhysicsBody(pb_stone[i]);
            stone[i]->setTag(i);
            //����ש������
            pb_stone[i]->setCategoryBitmask(99);
            pb_stone[i]->setCollisionBitmask(0);
            pb_stone[i]->setContactTestBitmask(0);
        }
    }


//��ͣ��ť�ڲ��¼�
    //�����ͣ����
    bg_Pause = Sprite::create("pauseboard.png");
    bg_Pause->setPosition(visibleSize / 2);
    addChild(bg_Pause);
    bg_Pause->setVisible(false);

    //��Ӱ�ť
    btn_P_back = Button::create("back_normal.png", "back_selected.png");
    btn_P_back->setPosition(Point(visibleSize.width / 2, visibleSize.height * 2 / 5));
    btn_P_back->addClickEventListener([=](Ref* pSend)
        {   //��������
            AudioEngine::play2d("click.mp3", false, 0.5f);  //������Ч

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


//��ͣ��ť
    btnPause = Button::create("pause_normal.png", "pause_selected.png");
    btnPause->setPosition(Point(btnPause->getContentSize().width * 3 / 2,
        visibleSize.height - btnPause->getContentSize().height / 2));
    btnPause->addClickEventListener([=](Ref* pSend)     //��ͣ�¼�
        {
            if (!isPause)
            {
                isPause = true;
                AudioEngine::play2d("click.mp3", false, 0.5f);  //������Ч
                //Director::getInstance()->getScheduler()->setTimeScale(0);
                Director::getInstance()->pause();   //��ͣ
                //��ӱ���
                bg_Pause->setVisible(true);
                //��Ӱ�ť
                btn_P_back->setVisible(true);
                btn_P_back->setEnabled(true);
                btn_P_continue->setVisible(true);
                btn_P_continue->setEnabled(true);
            }
            else
            {
                isPause = false;
                //ɾ������
                bg_Pause->setVisible(false);
                //ɾ����ť
                btn_P_back->setVisible(false);
                btn_P_back->setEnabled(false);
                btn_P_continue->setVisible(false);
                btn_P_continue->setEnabled(false);
            }
        });
    addChild(btnPause);


//�˳���ť
    btnQuit = Button::create("exit_normal.png", "exit_selected.png");
    btnQuit->setPosition(Point(btnQuit->getContentSize().width / 2,
        visibleSize.height - btnQuit->getContentSize().height / 2));
    btnQuit->addClickEventListener([=](Ref* pSend)     //�˳��¼�
        {   //�ص�������
            AudioEngine::play2d("click.mp3", false, 0.5f);  //������Ч

            blood = 5;
            isShot = 0;
            toNext = 45;
            auto MainScene = HelloWorld::createScene();
            Director::getInstance()->purgeCachedData();
            Director::getInstance()->replaceScene(MainScene);
            AudioEngine::stop(bgmID_game);     //�ر���Ϸ��������

            //Director::getInstance()->end();     //�˳���Ϸ

        });
    addChild(btnQuit);


//���Ѫ��
    lb_blood = Label::Label::createWithTTF(std::to_string(blood), "fonts//Marker Felt.ttf", 32);
    lb_blood->setColor(Color3B::RED);
    lb_blood->setPosition(visibleSize.width * 19 / 20, visibleSize.height / 15);
    lb_blood->removeFromParent();
    addChild(lb_blood);




//������Ϣ��������Ӧ
    //����С��
    EventListenerKeyboard* shootListener = EventListenerKeyboard::create();
    shootListener->onKeyPressed = CC_CALLBACK_2(MyGame::pressed_Shoot, this);
        
    //����̨�����ƶ�
    EventListenerKeyboard* moveListener = EventListenerKeyboard::create();
    moveListener->onKeyPressed = CC_CALLBACK_2(MyGame::pressed_batMove, this);
    moveListener->onKeyReleased = CC_CALLBACK_2(MyGame::released_batMove, this);

    EventDispatcher* dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addEventListenerWithSceneGraphPriority(shootListener, this);
    dispatcher->addEventListenerWithSceneGraphPriority(moveListener, this);

    schedule(CC_SCHEDULE_SELECTOR(MyGame::gameUpdate), 0.01f);  //update����




//��ײ��Ӧ
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

    if (EventKeyboard::KeyCode::KEY_Z == keycode)   // ����z��������С��
    {
        if (!isShot)
        {
            pb_ball[0]->setVelocity(Vec2(speedx, speedy));  //������60�ȷ���С��
            //ɾ���ؽ�
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

void MyGame::keyPressedDuration(cocos2d::EventKeyboard::KeyCode code)   //���������ƶ���Ϣ��Ӧ�¼�
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

    lb_blood->setString(std::to_string(blood));     //����Ѫ��

    //endTime = time(NULL);
    //if (endTime - startTime == 10)  //���Ч������10��
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

    if (toNext == 0 && flagLv == 1)     //��ת����һ��
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
    else if (toNext == 0 && flagLv == 2)    //��ת����Ϸʤ������
    {

        toNext = 1;
    }

    if (blood == 0)     //Ѫ��Ϊ0����Ϸʧ��
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

bool MyGame::isCld(cocos2d::PhysicsContact& contact)    //��ײ��Ӧ
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
            stoneState[i]++;    //ש������̶�����

            switch (i % 5)
            {
            case 0:         //��ɫש��
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
                //ש�����鶯��
                    //���������������
                    sfs_blue.clear();
                    //͸������
                    auto texture_0 = Director::getInstance()->getTextureCache()->addImage("0.png");
                    sf_0 = SpriteFrame::createWithTexture(texture_0, Rect(0, 0, 5, 5));
                    //����ȷ������֡�ߴ�
                    Sprite* brk_blue = Sprite::create("stone_breaking_blue.png");
                    //����
                    auto texture_blue = Director::getInstance()->getTextureCache()->addImage("stone_breaking_blue.png");
                    //�����ϵĶ���֡
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
                    //���붯��֡����������
                    sfs_blue.pushBack(sf_blue0);
                    sfs_blue.pushBack(sf_blue1);
                    sfs_blue.pushBack(sf_blue2);
                    sfs_blue.pushBack(sf_blue3);
                    sfs_blue.pushBack(sf_blue4);
                    sfs_blue.pushBack(sf_0);
                    //����������Ϣ
                    anim_blue = Animation::createWithSpriteFrames(sfs_blue, 0.1f);
                    //����ש�����鶯��
                    Sprite* sp = Sprite::createWithSpriteFrame(sf_blue0);
                    sp->setPosition(stone[i]->getPosition());
                    addChild(sp);
                    sp->runAction(Animate::create(anim_blue));
                    //�Ƴ�ש��
                    stone[i]->setVisible(false);
                    pb_stone[i]->setEnabled(false);

                    //С���Ϊ��ɫ
                    auto texture = Director::getInstance()->getTextureCache()->addImage("ball_blue.png");
                    targetA->setTexture(texture);
                    targetA->setTag(97);
                }
                break;

            case 1:         //��ɫ
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
                    //���������������
                    sfs_green.clear();
                    //͸������
                    auto texture_0 = Director::getInstance()->getTextureCache()->addImage("0.png");
                    sf_0 = SpriteFrame::createWithTexture(texture_0, Rect(0, 0, 5, 5));
                    //����ȷ������֡�ߴ�
                    Sprite* brk_green = Sprite::create("stone_breaking_green.png");
                    //����
                    auto texture_green = Director::getInstance()->getTextureCache()->addImage("stone_breaking_green.png");
                    //�����ϵĶ���֡
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
                    //���붯��֡����������
                    sfs_green.pushBack(sf_green0);
                    sfs_green.pushBack(sf_green1);
                    sfs_green.pushBack(sf_green2);
                    sfs_green.pushBack(sf_green3);
                    sfs_green.pushBack(sf_green4);
                    sfs_green.pushBack(sf_0);
                    //����������Ϣ
                    anim_green = Animation::createWithSpriteFrames(sfs_green, 0.1f);
                    //����ש�����鶯��
                    Sprite* sp_green = Sprite::createWithSpriteFrame(sf_green0);
                    sp_green->setPosition(stone[i]->getPosition());
                    addChild(sp_green);
                    sp_green->runAction(Animate::create(anim_green));
                    //�Ƴ�ש��
                    stone[i]->setVisible(false);   
                    pb_stone[i]->setEnabled(false);
                }
                break;

            case 2:         //��ɫ
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
                    //���������������
                    sfs_orange.clear();
                    //͸������
                    auto texture_0 = Director::getInstance()->getTextureCache()->addImage("0.png");
                    sf_0 = SpriteFrame::createWithTexture(texture_0, Rect(0, 0, 5, 5));
                    //����ȷ������֡�ߴ�
                    Sprite* brk_orange = Sprite::create("stone_breaking_orange.png");
                    //����
                    auto texture_orange = Director::getInstance()->getTextureCache()->addImage("stone_breaking_orange.png");
                    //�����ϵĶ���֡
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
                    //���붯��֡����������
                    sfs_orange.pushBack(sf_orange0);
                    sfs_orange.pushBack(sf_orange1);
                    sfs_orange.pushBack(sf_orange2);
                    sfs_orange.pushBack(sf_orange3);
                    sfs_orange.pushBack(sf_orange4);
                    sfs_orange.pushBack(sf_0);
                    //����������Ϣ
                    anim_orange = Animation::createWithSpriteFrames(sfs_orange, 0.1f);
                    //����ש�����鶯��
                    Sprite* sp_orange = Sprite::createWithSpriteFrame(sf_orange0);
                    sp_orange->setPosition(stone[i]->getPosition());
                    addChild(sp_orange);
                    sp_orange->runAction(Animate::create(anim_orange));
                    //�Ƴ�ש��
                    stone[i]->setVisible(false);
                    pb_stone[i]->setEnabled(false);
                }
                break;

            case 3:         //��ɫ
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
                    //���������������
                    sfs_red.clear();
                    //͸������
                    auto texture_0 = Director::getInstance()->getTextureCache()->addImage("0.png");
                    sf_0 = SpriteFrame::createWithTexture(texture_0, Rect(0, 0, 5, 5));
                    //����ȷ������֡�ߴ�
                    Sprite* brk_red = Sprite::create("stone_breaking_red.png");
                    //����
                    auto texture_red = Director::getInstance()->getTextureCache()->addImage("stone_breaking_red.png");
                    //�����ϵĶ���֡
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
                    //���붯��֡����������
                    sfs_red.pushBack(sf_red0);
                    sfs_red.pushBack(sf_red1);
                    sfs_red.pushBack(sf_red2);
                    sfs_red.pushBack(sf_red3);
                    sfs_red.pushBack(sf_red4);
                    sfs_red.pushBack(sf_0);
                    //����������Ϣ
                    anim_red = Animation::createWithSpriteFrames(sfs_red, 0.1f);
                    //����ש�����鶯��
                    Sprite* sp_red = Sprite::Sprite::createWithSpriteFrame(sf_red0);
                    sp_red->setPosition(stone[i]->getPosition());
                    addChild(sp_red);
                    sp_red->runAction(Animate::create(anim_red));
                    //�Ƴ�ש��
                    stone[i]->setVisible(false);
                    pb_stone[i]->setEnabled(false);

                    //С���Ϊ������ɫС��ɢ��
                    auto texture = Director::getInstance()->getTextureCache()->addImage("ball_red.png");
                    targetA->setTexture(texture);
                    //targetA->setTag(98);
                        //ɢ��С��1
                    ball[1]->runAction(Place::create(Vec2(targetA->getPosition().x - targetA->getContentSize().width, targetA->getPosition().y)));
                    pb_ball[1]->setVelocity(Vec2(-200, -346));
                        //ɢ��С��2
                    ball[2]->setPosition((targetA->getPosition().x + targetA->getContentSize().width), targetA->getPosition().y);
                    pb_ball[2]->setVelocity(Vec2(200, -346));

                    cnt_balls += 2;
                }
                break;

            case 4:         //��ɫ
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
                    //���������������
                    sfs_yellow.clear();
                    //͸������
                    auto texture_0 = Director::getInstance()->getTextureCache()->addImage("0.png");
                    sf_0 = SpriteFrame::createWithTexture(texture_0, Rect(0, 0, 5, 5));
                    //����ȷ������֡�ߴ�
                    Sprite* brk_yellow = Sprite::create("stone_breaking_yellow.png");
                    //����
                    auto texture_yellow = Director::getInstance()->getTextureCache()->addImage("stone_breaking_yellow.png");
                    //�����ϵĶ���֡
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
                    //���붯��֡����������
                    sfs_yellow.pushBack(sf_yellow0);
                    sfs_yellow.pushBack(sf_yellow1);
                    sfs_yellow.pushBack(sf_yellow2);
                    sfs_yellow.pushBack(sf_yellow3);
                    sfs_yellow.pushBack(sf_yellow4);
                    sfs_yellow.pushBack(sf_0);
                    //����������Ϣ
                    anim_yellow = Animation::createWithSpriteFrames(sfs_yellow, 0.1f);
                    //����ש�����鶯��
                    Sprite* sp_yellow = Sprite::createWithSpriteFrame(sf_yellow0);
                    sp_yellow->setPosition(stone[i]->getPosition());
                    addChild(sp_yellow);
                    sp_yellow->runAction(Animate::create(anim_yellow));
                    //�Ƴ�ש��
                    stone[i]->setVisible(false);
                    pb_stone[i]->setEnabled(false);
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
        //�ı䷢��̨�ߴ�
        Sprite* bat_huge = Sprite::create("bat_huge.png");
        auto texture = Director::getInstance()->getTextureCache()->addImage("bat_huge.png");
        bat->setContentSize(Size(bat_huge->getContentSize()));
        bat->setTexture(texture);
        
        //bat->setPhysicsBody(pb_bat_huge);

        //startTime = time(NULL); //�����ײʱ��

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
                if (blood == 0) //Ѫ��Ϊ0����Ϸʧ��
                {
                    //����update�д���
                }
                else
                {
                    isShot = 0;     //��Ϊ�ɷ���
                    //����С��λ�ã���ɫ
                    cnt_balls = 1;
                    ball[0]->runAction(Place::create(Vec2(bat->getPosition().x, bat->getPosition().y + bat->getContentSize().height / 2)));
                    auto texture = Director::getInstance()->getTextureCache()->addImage("ball_pinball.png");
                    ball[0]->setTexture(texture);
                    pb_ball[0]->setVelocity(Vec2(0, 0));

                    ball[1]->runAction(Place::create(Vec2(-100, -100)));
                    pb_ball[1]->setVelocity(Vec2(0, 0));

                    ball[2]->runAction(Place::create(Vec2(-100, -200)));
                    pb_ball[2]->setVelocity(Vec2(0, 0));

                    //��ӹؽ�
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
