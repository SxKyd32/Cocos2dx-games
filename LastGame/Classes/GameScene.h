#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

class MyGame : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    bool initPhysics();     //初始化物理世界
         
                            
    //发射小球
    void pressed_Shoot(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);

    //左右移动发射台
        //判断左右键按下还是松开
    void pressed_batMove(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);
    void released_batMove(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);
        //判断左右键是否处于被按下状态
    bool isKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode);
        //按下响应处理
    void keyPressedDuration(cocos2d::EventKeyboard::KeyCode code);
    
    //监听
    void gameUpdate(float dt);

    //碰撞响应
    bool isCld(cocos2d::PhysicsContact& contact);





    void update(float dt);

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(MyGame);

private:

};

#endif // __HELLOWORLD_SCENE_H__
