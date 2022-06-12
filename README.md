# Team-Work-in-2022
项目信息介绍：
===
项目名：
--
荒野乱斗

项目成员：
--
陈峥海 2152831、刘佳昊 2154063、刘启 2152047、杨瑞华 2152057

小组成员贡献比例：
--
陈峥海 0.333、刘佳昊 0.333、刘启 0.001、杨瑞华 0.333

项目github地址：
--
https://github.com/luxingzhi27/Team-Work-in-2022.git

项目进度时间线：
--
2022.5.23 创建项目

2022.5.28 完成开始界面

2022.6.1  增加人物行走功能以及行走动画和障碍物检测

2022.6.4  完成地图随主角移动

2022.6.6  添加血条

2022.6.7  增加了物品类，包括子弹和宝箱钻石，实现了子弹宝箱英雄之间的碰撞检测

2022.6.8  添加了进草隐身，随机出生点，宝箱刷新点

2022.6.9  添加了游戏ai

2022.6.10 修复了ai 的一些bug，优化了血条，更改背景音乐

2022.6.11 完成了选择英雄的界面，添加了选择ai数量的ui，添加了结束场景，降低了ai的强度，添加help界面，发布了可执行文件

项目开发文档：
==
游戏整体架构、小组分工：
--
陈峥海：整体ui设计，后期测试与调整

刘佳昊：物理引擎部分，物品类设计，完善人物类，后期测试与调整

杨瑞华：人物类构建，地图制作，设计游戏ai，后期测试与调整

实现功能点、实现思路：
--
1、人物移动：通过添加监听器来监听键盘事件，使用map存储键盘是否被按下的信息，	实现人物连续移动；

2、障碍物检测：使用tile地图，根据障碍物图层的gid判断是否能够移动，完成障碍物	检测；
```cpp
position = Vec2toTile(position + Vec2(aimx, aimy));
auto wallgrp = _map->getLayer("barrier");
int tilegid = wallgrp->getTileGIDAt(position);
if (tilegid)
  return;
```
3、添加游戏ai：由在人物类中添加数据成员isai来决定是否是ai，并由aiSearch函数索敌，aiMove函数完成ai移动以及射击；

4、选择英雄及ai数量：添加global类，存储需要的全局变量，来实现不同场景间传递信息；
```cpp
#pragma once
#ifndef _GLOABL_H_
#define _GLOBAL_H

extern int NumOfHero;
extern int NumOfAi;

#endif // !_GLOABL_H_
```
5、在地图中加入了能量宝箱与能量宝石：创建了宝箱类，继承自sprite并加入物理躯干组件，具有生命值，被击破后掉落宝石，人物与其接触后获得生命值上限与攻击力增加的buff。

6、实现了英雄对其他人物进行普通攻击积攒能量，能量满课释放技能。普通攻击引入子弹类，并对其绑定物理躯干组件，通过碰撞监测进行判断与反馈，实现积攒能量。

7、鼠标控制攻击。加入鼠标事件监听器，按下左键进行对光标方向的普通攻击，能量满后按下右键释放技能。

8、英雄属性实时显示：使用label标签，不断调用label->setString();

9、实现毒圈：每30秒从地图边缘产生一层毒圈，进入毒圈的人物持续降低生命值。

10、实现游戏胜利与失败的判断。当玩家为最终存活者即胜利，否则失败。

11、实现游戏的UI界面：开始游戏、音量设置、帮助、游戏运行时终止游戏、游戏胜利与失败界面。

项目技术难点、解决方案以及解决过程：
--
1、生成人物行走动画：生成人物行走动画采用的是people类中getAnimate函数，通过读取帧动画配置文件来播放行走动画，期间将动画初始化后在update函数中让英雄runAction会出现访问权限异常的问题，原因是生成的动画被autoRelease函数自动释放，故在getAnimate函数中将生成的动画retain一下解决了问题；
```cpp
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
```
2、人物ai 的构建：通过在人物类中加入isai数据成员判断是否是ai，然后通过aiSearch函数索敌，aiMove函数完成ai移动以及射击；期间ai有时会不停抽搐，通过判断与目标间的距离解决了问题，还有ai射击不准的问题，发现是没有加上map层的偏移量，加上之后最终实现了ai，但ai强度过高，又给ai添加了进行攻击的随机数，让进行攻击的概率降到10%，同时将攻击方位加上了微小的随机偏移量；

3、子弹命中与补充能量：本项目中，子弹与其他物体的碰撞通过物理引擎采用碰撞监测来实现，而在物体碰撞时遇到只能得到node对象，不能直接实现Bullet类与其他类的直接关系。解决时采用设置tag，在碰撞处理中使用dynaminc_cast方法得到对应的继承类进行对应处理。（如图4）而在处理时，单独的Bullet对象只能与碰撞物体产生直接关系，为了实现补充能量，在Bullet类中添加了一个Hero指针的data member，在调用Attack函数时子弹创建并绑定发出者，在子弹命中其他人物时与其建立联系，实现积攒能量。
```cpp
///////////////////人物中弹
        if (nodeA->getTag() == BULLET_TAG&& nodeB->getTag()==HERO_TAG)
        {
            isConEve=true;
            ConEve = ContactEvents::HeroHurt;
            auto bullet = dynamic_cast<Bullet*>(nodeA);
            auto hero = dynamic_cast<Hero*>(nodeB);
            ConEve_Hero_Bullet(hero,bullet);
        }
        else if (nodeB->getTag() == BULLET_TAG && nodeA->getTag() == HERO_TAG)
        {
            isConEve = true;
            ConEve = ContactEvents::HeroHurt;
            auto bullet = dynamic_cast<Bullet*>(nodeB);
            auto hero = dynamic_cast<Hero*>(nodeA);
            ConEve_Hero_Bullet(hero, bullet);
        }
```

4、实现脱战回复生命值。脱战的判断标志与实现曾成为困扰。因为我们发现单一的bool型数据作为标志不能较好刻画这一机制。经过共同商议，我们决定采用一个int型变量实现。在人物发生攻击命中、受到伤害、在毒圈中毒等行为时，将其置为5，引入一个调度器，当该值大于0时，每秒减一，等于0时即判定为脱战，进行生命值回复。

5、背景音乐重复问题：创建开始界面时（是一个场景），添加了背景音乐，当游戏结束或返回主菜单时，因为会再次调用创建场景的函数，故音乐会重叠，选择了一种比较简单的方法来解决此问题----创建了一个缓冲的场景（只会在游戏开始时生成一次），该场景换延时调用开始界面的场景，并选择在该场景添加背景音乐。
```cpp
CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("start.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(1);
	this->scheduleOnce(CC_SCHEDULE_SELECTOR(Startinterface::PlayMusic), 4.0f);
	//回调函数的声明
	this->scheduleOnce(CC_SCHEDULE_SELECTOR(Startinterface::AlterToStartScene), 3.0f);//延迟切换场景
```
6、血条、蓝条无法改变问题：血条和蓝条虽然加到了英雄身上但是无法根据英雄血量实时更新（一直保持不变的状态），该开始使用的是进度条创建的蓝条和血条，由于调试时始终无法解决上述无法更新的问题，故采用另外一种方式添加（ProgressTimer），并加到英雄的初始化函数中，最终能实时更新英雄属性。

层屏蔽问题：游戏场景中有菜单界面，当点击该菜单时，会生成一个选择界面（层），当不断点击该菜单时，会一直生成选择界面造成重叠，有多种解决方法，第一种是设置禁用后在继续启用，还有就是在原位置生成同样的图片不添加函数，因为层级的问题，点击之后便不会再有选择界面的生成。

游戏亮点：
--
1、使用const.h，将常用宏定义放入其中

2、通过getAnimate函数在初始化中加载好英雄行走动画，提高运行效率

3、实时显示血量、蓝量、攻击力与子弹数目

4、实现了进草隐身效果（AI进草隐身，主角进草透明度降低并屏蔽AI监测）

5、发射的子弹未命中则直接消失，命中则产生类似烟花的粒子特效

6、实现脱战回血机制

7、可以通过滑动条选择ai数量与控制音量

项目运行截图：
--
![image](https://github.com/luxingzhi27/Team-Work-in-2022/blob/main/images/1.png)
![image](https://github.com/luxingzhi27/Team-Work-in-2022/blob/main/images/2.png)
![image](https://github.com/luxingzhi27/Team-Work-in-2022/blob/main/images/3.png)
![image](https://github.com/luxingzhi27/Team-Work-in-2022/blob/main/images/4.png)
