#include "ComMove.h"
using namespace cocos2d;

void CMyCom::startMove()
{
    Vector<FiniteTimeAction*> fta;
    for (int i = 1; i < m_path.size(); i++)
        fta.pushBack(MoveTo::create(5, m_path[i]));
    Sequence* sp = Sequence::create(fta);
    Sprite* host = (Sprite*)getOwner();
    host->setPosition(m_path[0]);
    host->runAction(sp);
}

CMyCom* CMyCom::create(std::vector<Point> path)
{
    CMyCom* ret = new CMyCom(path);
    if (ret != nullptr && ret->init())
        ret->autorelease();
    else
        CC_SAFE_DELETE(ret);
    return ret;
}

