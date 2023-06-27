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

PhysicsWorld* pw;
PhysicsBody* pWheel;
int t = 1;
PhysicsJointFixed* pjf;

Scene* HelloWorld::createScene()
{
    HelloWorld* sn = (HelloWorld*)HelloWorld::createWithPhysics(); //创建物理世界
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
bool HelloWorld::initPhysics()
{
    if ( !Scene::initWithPhysics() )
    {
        return false;
    }
    pw = this->getPhysicsWorld();
    pw->setGravity(Vec2(0, -980));
    pw->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    pw->setAutoStep(false);
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

  
//物理引擎：下落的小球（打开Gravity）
    /*Sprite* bg = Sprite::create("bg960X640.jpg");
    bg->setPosition(visibleSize / 2);
    addChild(bg);
    PhysicsMaterial pm2 = PhysicsMaterial(1, 1, 0);
    PhysicsBody* pbg = PhysicsBody::createEdgeBox(visibleSize, pm2, 5);
    bg->setPhysicsBody(pbg);

    Sprite* ball = Sprite::create("ball.png");
    ball->setPosition(visibleSize.width / 2, visibleSize.height * 4 / 5);
    addChild(ball);
    PhysicsMaterial pm = PhysicsMaterial(1, 0.9, 0);
    PhysicsBody* pb = PhysicsBody::createCircle(ball->getContentSize().width / 2, pm);
    ball->setPhysicsBody(pb);*/


//物理引擎：台球运动（关闭Gravity）
    /*Sprite* bg = Sprite::create("bg960X640.jpg");
    bg->setPosition(visibleSize / 2);
    addChild(bg);
    PhysicsMaterial pm2 = PhysicsMaterial(1, 1, 10000);
    PhysicsBody* pbg = PhysicsBody::createEdgeBox(visibleSize, pm2, 5);
    bg->setPhysicsBody(pbg);

    Sprite* ball = Sprite::create("ball.png");
    ball->setPosition(visibleSize / 2);
    addChild(ball);
    PhysicsMaterial pm = PhysicsMaterial(1, 1, 10000);
    PhysicsBody* pb = PhysicsBody::createCircle(ball->getContentSize().width / 2, pm);
    ball->setPhysicsBody(pb);
    pb->setVelocity(Vec2(500, 500));
    //pb->setAngularVelocity(-10);*/


//物理引擎：斜抛小球（打开Gravity）
    /*Sprite* bg = Sprite::create("bg960X640.jpg");
    bg->setPosition(visibleSize / 2);
    addChild(bg);
    PhysicsMaterial pm2 = PhysicsMaterial(1, 1, 100);
    PhysicsBody* pbg = PhysicsBody::createEdgeBox(visibleSize, pm2, 3);
    bg->setPhysicsBody(pbg);

    Sprite* ball = Sprite::create("ball.png");
    ball->setPosition(visibleSize.width * 9 / 10, visibleSize.height * 1 / 10);
    addChild(ball);
    PhysicsMaterial pm = PhysicsMaterial(1, 1, 100);
    PhysicsBody* pb = PhysicsBody::createCircle(ball->getContentSize().width / 2, pm);
    ball->setPhysicsBody(pb);
    pb->setVelocity(Vec2(-4000, 4000));
    pb->setVelocityLimit(1000); //限制最大速度，使小球不能冲出物理边框
    //pb->setAngularVelocity(10);*/
    

//物理引擎：风车
    /*Sprite* bg = Sprite::create("bg960X640.jpg");
    addChild(bg);
    bg->setPosition(visibleSize / 2);


    Sprite* wheel = Sprite::create("pinwheelA.png");
    wheel->setPosition(visibleSize / 2);
    wheel->setScale(0.5);
    addChild(wheel);
    PhysicsMaterial pm1 = PhysicsMaterial(0, 0, 10);
    pWheel = PhysicsBody::createCircle(wheel->getContentSize().width / 2, pm1);
    wheel->setPhysicsBody(pWheel);


    srand((unsigned)time(NULL));
    schedule(CC_SCHEDULE_SELECTOR(HelloWorld::rotateWindWheel), (rand() % 2 + 1));*/


//物理引擎：FlipBird
    /*Sprite* bg = Sprite::create("backgroud.png");
    bg->setPosition(bg->getContentSize() / 2);
    addChild(bg, 1);
    MoveTo* mt = MoveTo::create(16, Vec2(-bg->getContentSize().width / 2, bg->getContentSize().height / 2));
    bg->runAction(RepeatForever::create(Sequence::create(mt, CallFunc::create([=] {bg->setPosition(bg->getContentSize() / 2); }), NULL)));
    
    Sprite* bg1 = Sprite::create("backgroud.png");
    bg1->setPosition(bg->getContentSize().width * 3 / 2, bg->getContentSize().height / 2);
    MoveTo* mt1 = MoveTo::create(16, bg->getContentSize() / 2);
    bg1->runAction(RepeatForever::create(Sequence::create(mt1, CallFunc::create([=] {bg1->setPosition(bg->getContentSize().width * 3 / 2, bg->getContentSize().height / 2); }), NULL)));
    addChild(bg1, 1);
    
    Sprite* bird = Sprite::create("duck01A.png");

    EventListenerKeyboard* elk = EventListenerKeyboard::create();
    elk->onKeyPressed = CC_CALLBACK_2(HelloWorld::bird_pressed, this);
    elk->onKeyReleased = CC_CALLBACK_2(HelloWorld::bird_released, this);
    EventDispatcher* ed = Director::getInstance()->getEventDispatcher();
    ed->addEventListenerWithSceneGraphPriority(elk, bird);

    Animation* ba = Animation::create();
    ba->addSpriteFrame(Sprite::create("duck02A.png")->getSpriteFrame());
    ba->setDelayPerUnit(0.25f);
    bird->runAction(RepeatForever::create(Animate::create(ba)));

    PhysicsMaterial pm1 = PhysicsMaterial(1, 1, 100000);
    PhysicsBody* pb = PhysicsBody::createCircle(bird->getContentSize().width / 2, pm1);
    bird->setPhysicsBody(pb);
    bird->setPosition(visibleSize.width * 2 / 5, visibleSize.height / 2);
    addChild(bird, 1);

    schedule(([=](float dt) {
        t++;
        if (t == 30) {
            auto labe2l = Label::createWithTTF("GAME OVER!", "fonts/Marker Felt.ttf", 48);
            labe2l->setTextColor(Color4B::RED);
            labe2l->setPosition(visibleSize / 2);
            addChild(labe2l, 1);
            bg->stopAllActions();
            bg1->stopAllActions();
            bird->stopAllActions();
            bird->getPhysicsBody()->setDynamic(false);
            ed->removeEventListener(elk);
        }
        }), 1, "s");*/


//物理引擎：选择性碰撞
    /*PhysicsMaterial pm = PhysicsMaterial(1, 0.5, 0);

    Sprite* ball = Sprite::create("ball.png");
    ball->setPosition(visibleSize.width / 2, visibleSize.height * 3 / 4);
    addChild(ball);
    PhysicsBody* pball = PhysicsBody::createCircle(ball->getContentSize().width / 2, pm);
    ball->setPhysicsBody(pball);

    Sprite* bg = Sprite::create("BoxG.png");
    bg->setPosition(visibleSize.width / 2, visibleSize.height / 4);
    addChild(bg);
    PhysicsBody* pbg = PhysicsBody::createBox(bg->getContentSize(), pm);
    bg->setPhysicsBody(pbg);
    pbg->setDynamic(false);

    Sprite* br = Sprite::create("BoxR.png");
    br->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    addChild(br);
    PhysicsBody* pbr = PhysicsBody::createBox(br->getContentSize(), pm);
    br->setPhysicsBody(pbr);
    pbr->setDynamic(false);
    pbr->setCollisionBitmask(0);*/


//物理引擎：碰撞消息响应
    /*PhysicsMaterial pm = PhysicsMaterial(1, 0.5, 0);

    Sprite* ball = Sprite::create("ball.png");
    ball->setPosition(visibleSize.width / 2, visibleSize.height * 3 / 4);
    addChild(ball);
    ball->setTag(1);
    PhysicsBody* pball = PhysicsBody::createCircle(ball->getContentSize().width / 2, pm);
    ball->setPhysicsBody(pball);
    pball->setContactTestBitmask(1);

    Sprite* br = Sprite::create("BoxR.png");
    br->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    addChild(br);
    br->setTag(2);
    PhysicsBody* pbr = PhysicsBody::createBox(br->getContentSize(), pm);
    br->setPhysicsBody(pbr);
    pbr->setDynamic(false);
    //pbr->setCollisionBitmask(0);
    pbr->setContactTestBitmask(1);

    Sprite* bg = Sprite::create("BoxG.png");
    bg->setPosition(visibleSize.width / 2, visibleSize.height / 4);
    addChild(bg);
    bg->setTag(3);
    PhysicsBody* pbg = PhysicsBody::createBox(bg->getContentSize(), pm);
    bg->setPhysicsBody(pbg);
    pbg->setDynamic(false);
    pbg->setContactTestBitmask(1);

    EventListenerPhysicsContact* elpc = EventListenerPhysicsContact::create();
    elpc->onContactBegin = CC_CALLBACK_1(HelloWorld::physicsTest, this);
    EventDispatcher* ed = Director::getInstance()->getEventDispatcher();
    ed->addEventListenerWithSceneGraphPriority(elpc, this);*/



//物理引擎：距离关节
    /*PhysicsMaterial pm = PhysicsMaterial(0, 0.5, 0);

    Sprite* bg = Sprite::create("Space.png");
    bg->setPosition(visibleSize / 2);
    addChild(bg);

    Sprite* sun = Sprite::create("sunA.png");
    sun->setPosition(visibleSize / 2);
    addChild(sun);
    PhysicsBody* psun = PhysicsBody::createCircle(sun->getContentSize().width / 2, pm);
    sun->setPhysicsBody(psun);
    psun->setDynamic(false);

    Sprite* earth = Sprite::create("earthA.png");
    earth->setPosition(visibleSize.width / 2, visibleSize.height / 2 - sun->getContentSize().width / 2 - 50);
    addChild(earth);
    PhysicsBody* pearth = PhysicsBody::createCircle(earth->getContentSize().width / 2, pm);
    earth->setPhysicsBody(pearth);
    pearth->setGravityEnable(false);

    PhysicsJointDistance* pjd = PhysicsJointDistance::construct(psun, pearth, Vec2::ZERO, Vec2::ZERO);
    pw->addJoint(pjd);

    pearth->setAngularVelocity(5);
    pearth->applyForce(Vec2(10000, 0));*/


//物理引擎：别针关节
    PhysicsMaterial pm = PhysicsMaterial(0, 0.5, 0);
    Sprite* rope[10];
    PhysicsBody* pRope[10];
    
    for (int i = 0; i < 10; i++)
    {
        rope[i] = Sprite::create("rope05HA.png");
        rope[i]->setPosition(visibleSize.width / 2 + i * rope[i]->getContentSize().width, visibleSize.height * 4 / 5);
        addChild(rope[i]);
        pRope[i] = PhysicsBody::createBox(rope[i]->getContentSize(), pm);
        rope[i]->setPhysicsBody(pRope[i]);
    }
    pRope[0]->setDynamic(false);
    
    PhysicsJointPin* pjp[9];
    for (int i = 0; i < 9; i++)
    {
        pjp[i] = PhysicsJointPin::construct(pRope[i], pRope[i + 1],
            rope[i + 1]->getPosition() - rope[i]->getPosition(), Vec2::ZERO);
        pw->addJoint(pjp[i]);
    }


//物理引擎：固定关节
    /*PhysicsMaterial pm = PhysicsMaterial(1, 0.5, 0);

    //绘制小球
    Sprite* ball = Sprite::create("ball.png");
    ball->setPosition(visibleSize.width / 2, visibleSize.height * 4 / 5);
    addChild(ball);
    PhysicsBody* pball = PhysicsBody::createCircle(ball->getContentSize().width / 2, pm);
    ball->setPhysicsBody(pball);

    //绘制底座
    Sprite* baseL = Sprite::create("RectB.png");
    Sprite* baseR = Sprite::create("RectB.png");
    baseL->setPosition(visibleSize.width / 2 - 200 + 25, visibleSize.height / 4);
    baseL->setRotation(90);
    baseR->setPosition(visibleSize.width / 2 + 200 - 25, visibleSize.height / 4);
    baseR->setRotation(90);
    addChild(baseL);
    addChild(baseR);
    PhysicsBody* pbaseL = PhysicsBody::createBox(baseL->getContentSize(), pm);
    baseL->setPhysicsBody(pbaseL);
    pbaseL->setDynamic(false);
    PhysicsBody* pbaseR = PhysicsBody::createBox(baseR->getContentSize(), pm);
    baseR->setPhysicsBody(pbaseR);
    pbaseR->setDynamic(false);

    //绘制横杆
    Sprite* barL = Sprite::create("RectR.png");
    Sprite* barR = Sprite::create("RectG.png");
    barL->setPosition(visibleSize.width / 2 - 100, visibleSize.height / 2 - 30);
    barR->setPosition(visibleSize.width / 2 + 100, visibleSize.height / 2 - 30);
    addChild(barL);
    addChild(barR);
    PhysicsBody* pbarL = PhysicsBody::createBox(barL->getContentSize(), pm);
    barL->setPhysicsBody(pbarL);
    PhysicsBody* pbarR = PhysicsBody::createBox(barR->getContentSize(), pm);
    barR->setPhysicsBody(pbarR);

    //给横杆添加固定关节
    pjf = PhysicsJointFixed::construct(pbarL, pbarR,
        Vec2(visibleSize.width / 2, visibleSize.height / 2 - 30));
    pw->addJoint(pjf);

    //碰撞消息
    ball->setTag(1);
    baseL->setTag(2);
    baseR->setTag(2);
    barL->setTag(3);
    barR->setTag(3);
    EventListenerPhysicsContact* elpc = EventListenerPhysicsContact::create();
    elpc->onContactBegin = CC_CALLBACK_1(HelloWorld::physicsTest, this);
    EventDispatcher* ed = Director::getInstance()->getEventDispatcher();
    ed->addEventListenerWithSceneGraphPriority(elpc, this);*/



    scheduleUpdate();

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

void HelloWorld::update(float dt)
{
    pw->step(0.01f);
}

void HelloWorld::rotateWindWheel(float dt)
{
    srand((unsigned)time(NULL));
    pWheel->setAngularVelocity(-(rand() % 20 + 1));
}

void HelloWorld::bird_pressed(EventKeyboard::KeyCode keycode, Event* event) {
    if (keycode == EventKeyboard::KeyCode::KEY_SPACE) {
        Sprite* b = static_cast<Sprite*>(event->getCurrentTarget());
        b->stopAllActions();
        b->getPhysicsBody()->setVelocity(Vec2(0, 150));
        Animation* ba = Animation::create();
        ba->addSpriteFrame(Sprite::create("duck01A.png")->getSpriteFrame());
        ba->addSpriteFrame(Sprite::create("duck02A.png")->getSpriteFrame());
        ba->addSpriteFrame(Sprite::create("duck03A.png")->getSpriteFrame());
        ba->setDelayPerUnit(0.25f);
        b->runAction(RepeatForever::create(Animate::create(ba)));
    }
}

void HelloWorld::bird_released(EventKeyboard::KeyCode keycode, Event* event) {
    if (keycode == EventKeyboard::KeyCode::KEY_SPACE) {
        Sprite* b = static_cast<Sprite*>(event->getCurrentTarget());
        b->stopAllActions();
        Animation* ba = Animation::create();
        ba->addSpriteFrame(Sprite::create("duck02A.png")->getSpriteFrame());
        ba->setDelayPerUnit(0.25f);
        b->runAction(RepeatForever::create(Animate::create(ba)));
    }
}

bool HelloWorld::physicsTest(PhysicsContact& contact)
{
    /*Sprite* tempA = (Sprite*)contact.getShapeA()->getBody()->getNode();
    if (2 == tempA->getTag())
        tempA->removeFromParent();
    Sprite* tempB = (Sprite*)contact.getShapeB()->getBody()->getNode();
    if (2 == tempB->getTag())
        tempB->removeFromParent();*/

    Sprite* tempA = (Sprite*)contact.getShapeA()->getBody()->getNode();
    if (3 == tempA->getTag())
        pw->removeJoint(pjf);
    Sprite* tempB = (Sprite*)contact.getShapeB()->getBody()->getNode();
    if (3 == tempB->getTag())
        pw->removeJoint(pjf);


    return true;
}

