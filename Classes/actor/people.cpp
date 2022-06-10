#include "people.h"
USING_NS_CC;


People::People()
{
}

People::~People()
{
}

bool People::init()
{
	if (!Sprite::init())
		return false;

	return true;
}

People* People::create(const char* file)
{
	People* sprite = new People();
	if (sprite && sprite->initWithFile(file))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);

	return nullptr;
}

Animate* People::getAnimate(const char* status, const char* heroName, int cnt, int loop)
{
	auto path = StringUtils::format("animation/%s/%s/%s_%s.plist", heroName, status,heroName, status);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(path);

	Vector<SpriteFrame*> frame;
	auto cache = SpriteFrameCache::getInstance();
	for (int i = 1; i <= cnt; i++)
	{
		auto name = StringUtils::format("%s_%s_0%d.png", heroName, status, i);
		frame.pushBack(cache->getSpriteFrameByName(name));
	}
	auto _animation = Animation::createWithSpriteFrames(frame, 1.f / 6,loop);
	auto _animate = Animate::create(_animation);
	_animate->retain();         //避免生成的animate会被自动释放(找了好久bug)
	return _animate;
}

bool People::isAlive() const
{
	return _isAlive;
}

int People::getMaxHP()
{
	return MaxCurrentHP;
}



