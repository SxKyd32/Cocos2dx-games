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
#include "ui/CocosGUI.h"
#include "AudioEngine.h"

using namespace cocos2d::ui;
USING_NS_CC;

int health = 100;
int sound = 100;
CheckBox* btn[2];
CheckBox* ckb[3];

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


//UI控件
//课前作业1
    /*Sprite* bk = Sprite::create("Dark.jpg");
    bk->setPosition(visibleSize / 2);
    addChild(bk);

    //姓名
    Layout* layout_name = Layout::create();
    layout_name->setLayoutType(Layout::Type::HORIZONTAL);
    Text* text_name = Text::create("　姓名　", "　黑体　", 24);
    TextField* tf_name = TextField::create("　请输入姓名　", "　黑体　", 18);
    tf_name->setCursorEnabled(true);
    layout_name->setContentSize(Size(80, 40));
    layout_name->addChild(text_name);
    layout_name->addChild(tf_name);
    layout_name->setPosition(Point(visibleSize.width * 0.2, visibleSize.height * 0.8));
    addChild(layout_name);

    //密码
    Layout* layout_password = Layout::create();
    layout_password->setLayoutType(Layout::Type::HORIZONTAL);
    Text* text_password = Text::create("　密码　", "　黑体　", 24);
    TextField* tf_password = TextField::create("　请输入密码　", "　黑体　", 18);
    tf_password->setCursorEnabled(true);
    tf_password->setPasswordEnabled(true);
    layout_password->setContentSize(Size(80, 40));
    layout_password->addChild(text_password);
    layout_password->addChild(tf_password);
    layout_password->setPosition(Point(visibleSize.width * 0.2, visibleSize.height * 0.7));
    addChild(layout_password);

    //性别
    Layout* layout_sex = Layout::create();
    layout_sex->setLayoutType(Layout::Type::HORIZONTAL);
    Text* text_sex = Text::create("　性别　", "　黑体　", 24);
    text_sex->setPosition(Point(visibleSize.width * 0.2, visibleSize.height * 0.5 + 40));
    addChild(text_sex);
    Text* tx_sex[2];
    tx_sex[0] = Text::create("　男　", "　黑体　", 24);
    tx_sex[1] = Text::create("　女　", "　黑体　", 24);
    for (int i = 0; i < 2; i++)
    {
        btn[i] = CheckBox::create("R1A.png", "R2A.png");
        layout_sex->addChild(btn[i]);
        layout_sex->addChild(tx_sex[i]);
    }

    btn[0]->addEventListener([=](Ref* pSend, CheckBox::EventType type)
        {
            if (!btn[0]->isSelected())
            {
                btn[0]->setSelected(true);
                btn[1]->setSelected(false);
            }
            if (btn[0]->isSelected())
            {
                btn[1]->setSelected(false);
            }
        });
    btn[1]->addEventListener([=](Ref* pSend, CheckBox::EventType type)
        {
            if (!btn[1]->isSelected())
            {
                btn[0]->setSelected(false);
                btn[1]->setSelected(true);
            }
            if (btn[1]->isSelected())
            {
                btn[0]->setSelected(false);
            }
        });
    layout_sex->setPosition(Point(visibleSize.width * 0.3, visibleSize.height * 0.5 + 40));
    addChild(layout_sex);

    //爱好
    Layout* layout_ckb = Layout::create();
    layout_ckb->setLayoutType(Layout::Type::HORIZONTAL);
    Text* text[3];
    text[0] = Text::create("RPG", "　黑体　", 24);
    text[1] = Text::create("AVG", "　黑体　", 24);
    text[2] = Text::create("FPS", "　黑体　", 24);
    Text* title_ckb = Text::create("　爱好　", "　黑体　", 24);
    title_ckb->setPosition(Point(visibleSize.width * 0.2, visibleSize.height * 0.3 + 50));
    addChild(title_ckb);
    for (int i = 0; i < 3; i++)
    {
        ckb[i] = CheckBox::create("CheckBox_Normal.png", "CheckBoxNode_Normal.png");
        layout_ckb->addChild(ckb[i]);
        layout_ckb->addChild(text[i]);
    }
    layout_ckb->setPosition(Point(visibleSize.width * 0.3, visibleSize.height * 0.3 + 50));
    addChild(layout_ckb);

    Text* output = Text::create("　　", "　黑体　", 24);
    output->setPosition(Point(visibleSize.width * 0.8, visibleSize.height * 0.3));
    addChild(output);
    Button* CheckBt = Button::create("R1A.png", "R2A.png");
    CheckBt->setPosition(Point(visibleSize.width * 0.8, visibleSize.height * 0.4));
    CheckBt->addClickEventListener([=](Ref* pSend)
        {
            std::string str = "";
            str += tf_name->getString() + ";" + " ";
            if (btn[0]->isSelected())
                str += "man;";
            else
                str += "woman;";
            for (int i = 0; i < 3; i++)
            {
                if (ckb[i]->isSelected())
                    str += text[i]->getString() + "," + "";
            }
            output->setString(str);

        });
    addChild(CheckBt);*/



//课前作业2
    AudioEngine::preload("bground.wav");
    int bkAudioID = AudioEngine::play2d("bground.wav", false);

    Sprite* bk = Sprite::create("bg960X640.jpg");
    bk->setPosition(visibleSize / 2);
    addChild(bk);

    Sprite* plane = Sprite::create("Hero1.png");
    plane->setPosition(visibleSize / 2);
    addChild(plane);

    LoadingBar* lb_health = LoadingBar::create("myHelth.jpg");
    lb_health->setPosition(Point(visibleSize.width * 0.2, visibleSize.height * 0.8));
    lb_health->setPercent(health);
    addChild(lb_health);

    Label* healthnum = Label::createWithSystemFont(std::to_string(health), "　黑体　", 24);
    healthnum->setColor(Color3B::RED);
    healthnum->setPosition(visibleSize.width * 0.2 + 400, visibleSize.height * 0.8);
    addChild(healthnum);

    Slider* sld = Slider::create("Slider_Back.png", "SliderNode_Press.png");
    sld->setPosition(Point(visibleSize.width * 0.2, visibleSize.height * 0.2));
    sld->setPercent(100);
    addChild(sld);

    Label* soundnum = Label::createWithSystemFont(std::to_string(sound), "　黑体　", 24);
    soundnum->setColor(Color3B::RED);
    soundnum->setPosition(visibleSize.width * 0.2 + 400, visibleSize.height * 0.1);
    addChild(soundnum);

    schedule(([=](float dt)
        {
            if (health > 0)
                health--;
            sound = sld->getPercent();
            AudioEngine::setVolume(bkAudioID, 0.01f * sound);
            lb_health->setPercent(health);
            healthnum->setString(std::to_string(health));
            soundnum->setString(std::to_string(sound));
        }), 0.33f, "HealthDown"
    );



   
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
