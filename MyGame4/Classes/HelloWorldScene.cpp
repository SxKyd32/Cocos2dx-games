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
#include <cocos\base\CCDirector.cpp>
#include "cocostudio/CocoStudio.h"
#include <cocos\renderer\CCTextureCache.cpp>

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

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

//粒子系统：蜡烛
    /*Sprite* candle = Sprite::create("CandleHolder.png");
    candle->setPosition(visibleSize.width / 2 + 30, visibleSize.height * 2 / 5);
    addChild(candle);

    ParticleFire* pf = ParticleFire::create();
    pf->setPosition(visibleSize.width / 2, visibleSize.height * 2 / 5 + candle->getContentSize().height / 2);
    pf->setPosVar(Vec2(0, 0));
    pf->setLife(0.4);
    pf->setLifeVar(0.2);
    pf->setStartSize(50);
    pf->setStartSizeVar(25);
    pf->setEndSize(50);
    pf->setEndSizeVar(25);
    pf->setTotalParticles(1000);
    pf->setGravity(Vec2(0, 1000));
    addChild(pf);*/


//粒子系统：下雨
    /*Sprite* bg = Sprite::create("Rain960x640.jpg");
    bg->setPosition(visibleSize / 2);
    addChild(bg);
    ParticleRain* pr = ParticleRain::createWithTotalParticles(5000);
    pr->setStartSize(2);
    pr->setSpeed(400);
    pr->setEmissionRate(1000);
    addChild(pr);*/


//粒子系统：发射火箭
    /*Sprite* rkt = Sprite::create("Rocket.png");
    rkt->setPosition(visibleSize.width / 2, visibleSize.height / 5);
    addChild(rkt);
    ParticleSystemQuad* psq = ParticleSystemQuad::create("myRocketFire.plist");
    psq->setPosition(visibleSize.width / 2, visibleSize.height / 5 - rkt->getContentSize().height / 2);
    psq->setScale(0.5);
    addChild(psq);

    MoveBy* mb1 = MoveBy::create(5, Vec2(0, visibleSize.height));
    MoveBy* mb2 = MoveBy::create(5, Vec2(0, visibleSize.height));
    rkt->runAction(mb1);
    psq->runAction(mb2);*/



//粒子系统：简单爆炸效果
    /*ParticleSystemQuad* psq = ParticleSystemQuad::create("myExplosion.plist");
    psq->setPosition(visibleSize / 2);
    psq->setScale(0.5);
    addChild(psq);*/


//粒子系统：实现爆炸效果
    ParticleExplosion* pex = ParticleExplosion::create();
    addChild(pex);
    pex->setTexture(Director::getInstance()->getTextureCache()->addImage("TtA.png"));
    pex->setTotalParticles(100);
    pex->setLife(1);
    pex->setLifeVar(0.1);
    pex->setStartSize(50);
    pex->setStartSizeVar(50);
    pex->setEmissionRate(1000);
    pex->setStartColor(Color4F(1, 0.9, 0.5, 1));
    pex->setStartColorVar(Color4F(0, 0, 0, 0));
    pex->setEndColor(Color4F(0.3, 0, 0, 1));
    pex->setEndColorVar(Color4F(0, 0, 0, 1));
    pex->setEndSize(50);
    pex->setEndSizeVar(50);
    pex->setStartSpin(0);
    pex->setStartSpinVar(10);
    pex->setEndSpin(0);
    pex->setEndSpinVar(10);


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
