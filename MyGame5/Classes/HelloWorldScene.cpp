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
#include "MyGameScene.h"
#include "audio/include/AudioEngine.h"

USING_NS_CC;

Sprite* ws;

Vector<SpriteFrame*> sf;

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
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

//�����л�
    /*
    //��ӱ���
    Sprite* bg = Sprite::create("BackGround960x640.png");
    bg->setPosition(visibleSize / 2);
    addChild(bg);

    //��ӿ�ʼ��Ϸ��ť
    Sprite* gs1 = Sprite::create("img2n.png");
    Sprite* gs2 = Sprite::create("img2s.png");
    Sprite* gs3 = Sprite::create("img2d.png");
    

    MenuItemSprite* mis1 = MenuItemSprite::create(gs1, gs2, gs3,
        [=](Ref* pSend) 
        {   
            auto GameScene = MyGame::createScene();
            Director::getInstance()->purgeCachedData();
            Director::getInstance()->replaceScene(GameScene);
        });

    Menu* menu = Menu::create(mis1, NULL);
    menu->alignItemsVertically();
    addChild(menu);
    */


//ȱʡ�����ļ��С���������
    //����������
    Sprite* bg = Sprite::create("Temple.png");
    bg->setPosition(visibleSize / 2);
    addChild(bg);

    //�������֣�ʮ�����
    AudioEngine::play2d("AmbushOnAllSides.mp3");

    //������Ӧ�¼����ӿ�
    ws = Sprite::create("Cut22.png");
    ws->setPosition(visibleSize.width * 0.53, visibleSize.height * 0.33);
    addChild(ws);

    EventListenerKeyboard* elk = EventListenerKeyboard::create();
    elk->onKeyPressed = CC_CALLBACK_2(HelloWorld::pressed_cut, this);
    EventDispatcher* ed = Director::getInstance()->getEventDispatcher();
    ed->addEventListenerWithSceneGraphPriority(elk, ws);

    return true;
}

void HelloWorld::pressed_cut(EventKeyboard::KeyCode keycode, Event* event)
{
    Size VisibleSize = Director::getInstance()->getVisibleSize();

    if (EventKeyboard::KeyCode::KEY_SPACE == keycode)
    {
        if (true == ws->isVisible())
        {
            ws->setVisible(false);
        }
        
        sf.clear();
        
        for (int i = 22; i <= 28; i++)
        {
            char filename[10];
            sprintf_s(filename, "Cut%d.png", i);
            sf.pushBack(Sprite::create(filename)->getSpriteFrame());
        }

        Sprite* sp = Sprite::create();
        Animation* anim = Animation::createWithSpriteFrames(sf, 0.0875);
        sp->setPosition(VisibleSize.width * 0.53, VisibleSize.height * 0.33);
        Animate* am = Animate::create(anim);
        sp->runAction(Sequence::create(am, CallFunc::create([=]()
            {
                sp->removeFromParent();
                ws->setVisible(true);
            }
        ), NULL));
        addChild(sp, 1);

        AudioEngine::play2d("Knife001.mp3");
    }
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();
}
