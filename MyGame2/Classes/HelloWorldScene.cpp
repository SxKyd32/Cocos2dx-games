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

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
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


//MoveTo
    /*Sprite* plane = Sprite::create("BigEnemy1.png");
    plane->setPosition(Vec2(visibleSize.width / 5, visibleSize.height * 4 / 5));
    addChild(plane);
    MoveTo* mt = MoveTo::create(3, Vec2(visibleSize / 5));
    plane->runAction(mt);*/


//MoveBy
    /*Sprite* plane = Sprite::create("BigEnemy1.png");
    plane->setPosition(Vec2(visibleSize.width / 5, visibleSize.height / 2));
    addChild(plane);
    MoveBy* mb = MoveBy::create(3, Vec2(visibleSize.width * 3 / 5, 0));
    plane->runAction(RepeatForever::create(Sequence::create(mb, mb->reverse(), NULL)));*/
    

//RotateBy
    /*Sprite* hand = Sprite::create("hand02.png");
    hand->setPosition(visibleSize.width/2, visibleSize.height / 2 + 130 + 80);
    addChild(hand, 2);

    Sprite* watch = Sprite::create("watch02.png");
    watch->setAnchorPoint(Vec2(0.5, 1));
    watch->setPosition(visibleSize.width / 2 - 40, visibleSize.height / 2 + 150);
    watch->setRotation(-30);
    addChild(watch);
    RotateBy* rb = RotateBy::create(2, 60);
    watch->runAction(RepeatForever::create(Sequence::create(rb, rb->reverse(), NULL)));*/


//ScaleBy
    /*Sprite* heart = Sprite::create("heart001.png");
    heart->setPosition(visibleSize / 2);
    addChild(heart);
    ScaleBy* sb = ScaleBy::create(0.4, 0.8);
    heart->setScale(1);
    heart->runAction(RepeatForever::create(Sequence::create(sb, sb->reverse(), NULL)));*/


//JumpTo
    /*Sprite* jumper = Sprite::create("jumperS.png");
    jumper->setPosition(visibleSize.width / 5 - 20, visibleSize.height / 5 - 20);
    addChild(jumper);
    JumpBy* jb = JumpBy::create(5, Vec2(visibleSize.width * 3 / 5, visibleSize.height * 3 / 5), 20, 5);
    jumper->runAction(Sequence::create(jb, jb->reverse(), NULL));*/


//FadeIn
   /* Sprite* tl = Sprite::create("TL.png");
    tl->setPosition(visibleSize / 2);
    addChild(tl);
    Sprite* gl = Sprite::create("GL.png");
    gl->setPosition(visibleSize / 2);
    addChild(gl);
    FadeIn* fi = FadeIn::create(1);
    gl->setOpacity(0);
    gl->runAction(fi);*/

   
//Blink
    /*Sprite* tl = Sprite::create("TL.png");
    tl->setPosition(visibleSize / 2);
    addChild(tl);
    Sprite* gl = Sprite::create("GL.png");
    gl->setPosition(visibleSize / 2);
    addChild(gl);
    Blink* bk = Blink::create(10, 10);
    gl->runAction(bk);*/


//TintTo
    /*Sprite* girl = Sprite::create("girl.png");
    girl->setPosition(visibleSize / 2);
    addChild(girl);
    Sprite* face = Sprite::create("face.png");
    face->setPosition(visibleSize / 2);
    addChild(face);
    TintTo* tt = TintTo::create(1, Color3B(255, 150, 150));
    face->runAction(tt);*/

    
//课堂练习
    /*Sprite* space = Sprite::create("space.jpg");
    space->setPosition(visibleSize / 2);
    addChild(space);

    Sprite* plane = Sprite::create("Hero1.png");
    plane->setPosition(Vec2(visibleSize.width / 5, visibleSize.height / 2));
    addChild(plane);
    MoveBy* mb = MoveBy::create(3, Vec2(visibleSize.width * 3 / 5, 0));
    plane->runAction(RepeatForever::create(Sequence::create(mb, mb->reverse(), NULL)));*/



//BezierTo
    /*Sprite* bg = Sprite::create("background.png");
    bg->setPosition(visibleSize / 2);
    addChild(bg);

    Sprite* soilder = Sprite::create("soilder1.png");
    soilder->setPosition(visibleSize.width / 5, visibleSize.height * 4 / 5);
    addChild(soilder);

    ccBezierConfig bc;
    bc.controlPoint_1 = Vec2(visibleSize.width / 5, visibleSize.height * 4 / 5);
    bc.controlPoint_2 = Vec2(visibleSize.width * 2 / 5, visibleSize.height * 3 / 5);
    bc.endPosition = Vec2(visibleSize / 5);
    BezierTo* bt = BezierTo::create(5, bc);
    soilder->runAction(bt);*/


//基数曲线动作(竖屏)
    /*Sprite* ball = Sprite::create("RedBall001AS.png");
    addChild(ball);
    PointArray* pa = PointArray::create(8);
    pa->addControlPoint(Vec2(visibleSize.width / 2, visibleSize.height * 4 / 5));
    pa->addControlPoint(Vec2(visibleSize.width / 2, visibleSize.height * 1 / 5));
    pa->addControlPoint(Vec2(visibleSize.width / 2, visibleSize.height * 3 / 5));
    pa->addControlPoint(Vec2(visibleSize.width / 2, visibleSize.height * 1 / 5));
    pa->addControlPoint(Vec2(visibleSize.width / 2, visibleSize.height * 2 / 5));
    pa->addControlPoint(Vec2(visibleSize.width / 2, visibleSize.height * 1 / 5));
    pa->addControlPoint(Vec2(visibleSize.width / 2, visibleSize.height * 2 / 6));
    pa->addControlPoint(Vec2(visibleSize.width / 2, visibleSize.height * 1 / 5));
    CardinalSplineTo* cst = CardinalSplineTo::create(6, pa, 0);
    ball->runAction(cst);*/


//变速运动特效EaseIn(竖屏)
    /*Sprite* rkt = Sprite::create("Rocket09A03.png");
    rkt->setPosition(visibleSize.width / 2, visibleSize.height / 5);
    addChild(rkt);
    EaseIn* ei = EaseIn::create(MoveBy::create(5, Vec2(0, visibleSize.height)), 2.5f);
    rkt->runAction(ei);*/


//网格特效(960x640)
    /*Sprite* pool = Sprite::create("pool.png");
    Sprite* water = Sprite::create("w03.jpg");
    pool->setPosition(visibleSize / 2);
    water->setPosition(visibleSize / 2);
    //addChild(water);

    NodeGrid* ng = NodeGrid::create();
    ng->addChild(water);
    addChild(ng);
    addChild(pool);
    Waves3D* w3 = Waves3D::create(10, Size(100, 100), 10, 10);
    ng->runAction(w3);*/


//卷动屏幕(960x640)
    /*Sprite* bg = Sprite::create("gameface.png");
    bg->setPosition(visibleSize / 2);
    addChild(bg);

    Sprite* soilder = Sprite::create("soilder1.png");
    soilder->setPosition(visibleSize / 2);
    addChild(soilder);

    MoveBy* mb = MoveBy::create(3, Vec2(0, visibleSize.height));
    bg->runAction(mb);
    this->runAction(Follow::create(bg, Rect(0, 0, visibleSize.width, visibleSize.height + 100)));*/



//动作序列Sequence
    /*Sprite* p = Sprite::create("pomegranateA.png");
    p->setPosition(visibleSize.width / 5, visibleSize.height / 2);
    addChild(p);
    MoveBy* mb = MoveBy::create(3, Vec2(visibleSize.width * 3 / 5, 0));
    p->runAction(Sequence::create(mb, mb->reverse(), NULL));*/


//动作组合Spawn
    /*Sprite* p = Sprite::create("pomegranateA.png");
    p->setPosition(visibleSize.width / 5, visibleSize.height / 2);
    addChild(p);
    MoveBy* mb = MoveBy::create(3, Vec2(visibleSize.width * 3 / 5, 0));
    RotateBy* rb = RotateBy::create(3, 1080);
    p->runAction(Sequence::create(Spawn::create(mb, rb, NULL), Spawn::create(mb->reverse(), rb->reverse(), NULL), NULL));*/


//回调函数动作
    /*Sprite* p = Sprite::create("pomegranateA.png");
    p->setPosition(visibleSize.width / 5, visibleSize.height / 2);
    addChild(p);
    MoveBy* mb = MoveBy::create(3, Vec2(visibleSize.width * 3 / 5, 0));
    p->runAction(Sequence::create(mb, CallFunc::create([=]() {log("Pomegranate is on the far right!"); }), NULL));*/


//渐变ProgressTo/ProgressFromTo
    /*Sprite* p = Sprite::create("pomegranateA.png");
    ProgressTimer* pt = ProgressTimer::create(p);
    ProgressTo* progress = ProgressTo::create(3, 100);
    pt->setType(ProgressTimer::Type::BAR);
    pt->runAction(progress);
    addChild(pt);
    pt->setPosition(visibleSize / 2);*/


//目标动作TargetedAction
    /*Sprite* p = Sprite::create("pomegranateA.png");
    Sprite* h = Sprite::create("hummer1.png");
    p->setPosition(visibleSize.width / 5, visibleSize.height / 4);
    addChild(p);
    h->setPosition(visibleSize.width / 5 - h->getContentSize().width * 2, visibleSize.height / 4 + h->getContentSize().height * 2);
    h->setAnchorPoint(Vec2(0.5, 1));
    h->setRotation(45);
    addChild(h);
    RotateBy* rb = RotateBy::create(0.5f, -40);
    MoveBy* mb = MoveBy::create(1, Vec2(visibleSize.width * 3 / 5, 0));
    TargetedAction* ta = TargetedAction::create(p, mb);
    h->runAction(Sequence::create(rb, ta, NULL));*/


//定时器(640x480)，定时调用planeMove()
    /*Sprite* bg = Sprite::create("bg.jpg");
    bg->setPosition(visibleSize / 2);
    addChild(bg);
    schedule(CC_SCHEDULE_SELECTOR(HelloWorld::planeMove), 1);*/



//事件处理
//移动石榴(1024x768)
    /*Sprite* bg = Sprite::create("bground.jpg");
    bg->setPosition(visibleSize / 2);
    addChild(bg);

    Sprite* p = Sprite::create("pomegranateA.png");
    p->setPosition(visibleSize / 2);
    addChild(p);

    EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::testBegin, this);
    listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::testMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::testEnded, this);

    EventDispatcher* dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addEventListenerWithSceneGraphPriority(listener, p);*/


//移动色块
    /*Sprite* redB = Sprite::create("BoxR.png");
    redB->setPosition(visibleSize.width / 2 - 50, visibleSize.height / 2 + 50);
    addChild(redB);

    Sprite* greenB = Sprite::create("BoxG.png");
    greenB->setPosition(visibleSize / 2);
    addChild(greenB);

    Sprite* blueB = Sprite::create("BoxB.png");
    blueB->setPosition(visibleSize.width / 2 + 50, visibleSize.height / 2 + 50);
    addChild(blueB);

    EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::testBegin, this);
    listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::testMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::testEnded, this);

    EventDispatcher* dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addEventListenerWithSceneGraphPriority(listener, redB);
    dispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), greenB);
    dispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), blueB);*/


//鼠标事件
    /*Sprite* A = Sprite::create("cross100A.png");
    A->setPosition(visibleSize / 2);
    addChild(A);

    EventListenerMouse* listener = EventListenerMouse::create();
    listener->onMouseMove = [=](Event* event)
    {
        EventMouse* e = dynamic_cast<EventMouse*>(event);
        A->setPosition(e->getCursorX(), e->getCursorY());
    };
    EventDispatcher* dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    ::ShowCursor(false);*/


//键盘事件
    /*Sprite* bg = Sprite::create("bg960X640.jpg");
    bg->setPosition(visibleSize / 2);
    addChild(bg);

    Sprite* plane = Sprite::create("Hero1.png");
    plane->setPosition(visibleSize.width / 2, visibleSize.height / 5);
    addChild(plane);

    EventListenerKeyboard* listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(HelloWorld::testPressed_planeMove, this);
    EventDispatcher* dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addEventListenerWithSceneGraphPriority(listener, plane);*/




//简单弹孔    
    /*Sprite* ABCD = Sprite::create("ABCD.png");
    Sprite* hole = Sprite::create("Hole.png");
    Sprite* pt = Sprite::create("Point.png");
    ClippingNode* cn = ClippingNode::create();

    cn->addChild(ABCD);
    cn->addChild(hole);
    cn->setStencil(pt);
    addChild(cn);
    cn->setPosition(visibleSize/2);
    cn->setAlphaThreshold(0.5);
    cn->setInverted(true);*/
    

//命中枪靶
    /*Sprite* ABCD = Sprite::create("ABCD.png");
    Sprite* peo = Sprite::create("Target006.jpg");
    Sprite* hole = Sprite::create("Hole.png");
    Sprite* pt = Sprite::create("Point.png");
    ClippingNode* cn = ClippingNode::create();

    peo->setPosition(visibleSize / 2);
    addChild(peo);

    cn->addChild(hole);
    cn->setStencil(pt);
    cn->setAlphaThreshold(0.5);
    cn->setInverted(true);
    addChild(cn);

    EventListenerMouse* elm = EventListenerMouse::create();
    elm->onMouseDown = [=](Event* event)
    {
        EventMouse* e = dynamic_cast<EventMouse*>(event);
        cn->setPosition(e->getCursorX(), e->getCursorY());
    };
    EventDispatcher* dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addEventListenerWithSceneGraphPriority(elm, this);*/


//放大镜
    Sprite* sm = Sprite::create("J11B.jpg");
    Sprite* bg = Sprite::create("J11B_conew1.jpg");
    Sprite* st = Sprite::create("Hero1_conew1.png");

    sm->setPosition(visibleSize / 2);
    addChild(sm);

    ClippingNode* cn = ClippingNode::create();
    cn->addChild(bg);
    cn->setStencil(st);
    addChild(cn);

    EventListenerMouse* elm = EventListenerMouse::create();
    elm->onMouseMove = [=](Event* event)
    {
        EventMouse* e = dynamic_cast<EventMouse*>(event);
        bg->setTextureRect(Rect(e->getCursorX() - 5, e->getCursorY() + 5, e->getCursorX() + 5, e->getCursorY() - 5));
        cn->setPosition(e->getCursorX(), e->getCursorY());
    };
    EventDispatcher* dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addEventListenerWithSceneGraphPriority(elm, this);


    return true;
}

void HelloWorld::planeMove(float dt)
{
    Size VisibleSize = Director::getInstance()->getVisibleSize();
    Sprite* plane = Sprite::create("SmallEnemy1.png");
    plane->setPosition(VisibleSize.width / 10, VisibleSize.height * 9 / 10);
    addChild(plane);
    MoveBy* mb1 = MoveBy::create(1.5, Vec2(VisibleSize.width * 8 / 10, 0));
    MoveBy* mb2 = MoveBy::create(1, Vec2(0, -VisibleSize.height));
    TargetedAction* ta = TargetedAction::create(plane, mb2);
    plane->runAction(Sequence::create(mb1, ta, NULL));
}

bool HelloWorld::testBegin(Touch* touch, Event* event)
{
    Sprite* temp = static_cast<Sprite*>(event->getCurrentTarget());
    Vec2 cp = touch->getLocation();
    Size size = temp->getContentSize();
    Rect rect = Rect(0, 0, size.width, size.height);
    Point pt = temp->convertToNodeSpace(cp);
    if (rect.containsPoint(pt))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void HelloWorld::testMoved(Touch* touch, Event* event)
{
    Sprite* temp = static_cast<Sprite*>(event->getCurrentTarget());
    temp->setPosition(temp->getPosition() + touch->getDelta());
}

void HelloWorld::testEnded(Touch* touch, Event* event)
{

}

void HelloWorld::testPressed_planeMove(EventKeyboard::KeyCode keycode, Event* event)
{
    Size VisibleSize = Director::getInstance()->getVisibleSize();

    Sprite* temp = static_cast<Sprite*>(event->getCurrentTarget());

    Sprite* atk = Sprite::create("HeroBullet.png");

    MoveBy* mb_blt = MoveBy::create(3, Vec2(0, VisibleSize.height));

    MoveBy* mb_l = MoveBy::create(0.5, Vec2(-50, 0));
    MoveBy* mb_r = MoveBy::create(0.5, Vec2(50, 0));

    if (EventKeyboard::KeyCode::KEY_SPACE == keycode)
    {
        atk->setPosition(temp->getPosition().x, temp->getContentSize().height / 2 + temp->getPosition().y);
        atk->runAction(mb_blt);
        addChild(atk);
    }
    if (EventKeyboard::KeyCode::KEY_LEFT_ARROW == keycode)
    {
        Vec2 pos = temp->getPosition();
        if (pos.x <= 150)
        {

        }
        else
        {
            temp->runAction(mb_l);
        }
    }
    if (EventKeyboard::KeyCode::KEY_RIGHT_ARROW == keycode)
    {
        Vec2 pos = temp->getPosition();
        if (pos.x >= 800)
        {

        }
        else
        {
            temp->runAction(mb_r);
        }
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
