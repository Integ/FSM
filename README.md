FSM
===

A four-axis aircraft looks like Flying Spaghetti Monster, RAmen.

Ongoing...

这是一个四轴飞行器开发项目，包括飞行器硬件设计，姿态控制算法，wifi/3G通信模块以及一套基于java和html5的web用户接口。

##Hardware 飞行器硬件设计

硬件选型：
- 机架：X525 V3
- 遥控器套件：冠丽4通道遥控器 + 6通道接收器
- 电机：新西达A2212 KV1000
- 电调：中特威 AL30A
- 桨：黑色 1045 两叶正反桨各两支
- 电池：狮子航模锂电 11.1V 2200mAh 30C，支持5C充电
- 充电器：花牌 ACE锂电平衡充电器+电源适配器套装
- 主控芯片：STM32F103C8
- 传感器：九轴模块，包括L3G4200D三轴陀螺仪+ADXL345三轴加速度计+HMC5883L三轴磁阻传感器（电子罗盘/指南针）+BMP085气压计

##姿态控制算法

1. 姿态估计——kalman滤波
2. 自动控制——PID

##wifi/3G通信模块

待定。

##Web User Interface 用户接口（/WebUI)

A friendly user interface.Frontend use html5 and jquery. It must be easy and elegant.

一个好用的飞行器监控系统，前端使用html5和three.js（3d动画），后端java。目标是使数据更加直观（汪星人能看懂），对飞行器的操控更加飘逸（喵星人也会使用）。