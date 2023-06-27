#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

class MyGame : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    bool initPhysics();     //��ʼ����������
         
                            
    //����С��
    void pressed_Shoot(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);

    //�����ƶ�����̨
        //�ж����Ҽ����»����ɿ�
    void pressed_batMove(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);
    void released_batMove(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);
        //�ж����Ҽ��Ƿ��ڱ�����״̬
    bool isKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode);
        //������Ӧ����
    void keyPressedDuration(cocos2d::EventKeyboard::KeyCode code);
    
    //����
    void gameUpdate(float dt);

    //��ײ��Ӧ
    bool isCld(cocos2d::PhysicsContact& contact);





    void update(float dt);

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(MyGame);

private:

};

#endif // __HELLOWORLD_SCENE_H__
