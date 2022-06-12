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
1、人物移动：通过添加监听器来监听键盘事件，使用map存储键盘是否被按下的信息，实现人物连续移动；

2、障碍物检测：使用tile地图，根据障碍物图层的gid判断是否能够移动，完成障碍物检测；
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

6、实现了英雄对其他人物进行普通攻击积攒能量，能量满课释放技能。普通攻击引入子弹类，并对其绑定刚体组件，通过碰撞监测进行判断与反馈，实现积攒能量。

7、鼠标控制攻击。加入鼠标事件监听器，按下左键进行对光标方向的普通攻击，能量满后按下右键释放技能。

8、英雄属性实时显示：使用label标签，不断调用label->setString();

9、实现毒圈：每30秒从地图边缘产生一层毒圈，进入毒圈的人物持续降低生命值。

10、实现游戏胜利与失败的判断。当玩家为最终存活者即胜利，否则失败。

11、英雄属性实时显示：使用label标签，不断调用label->setString();

12、实现游戏的UI界面：开始游戏、音量设置、帮助、游戏运行时终止游戏、游戏胜利与失败界面。

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
