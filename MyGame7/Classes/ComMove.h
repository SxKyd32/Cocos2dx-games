#include "cocos2d.h"

class CMyCom :public cocos2d::Component
{
public:
	CMyCom(std::vector<cocos2d::Point>path) { m_path = path; };
	void startMove();
	static CMyCom* create(std::vector<cocos2d::Point>path);
private:
	std::vector<cocos2d::Point>m_path;
};
