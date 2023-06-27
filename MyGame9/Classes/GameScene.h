#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

class MyGame : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    bool initPhysics();
    
    virtual void update(float dt);

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(MyGame);
};

#endif // __HELLOWORLD_SCENE_H__
