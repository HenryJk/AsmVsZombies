# AsmVsZombies

High-precision PvZ scripting framework

## Introduction

AvZ (Assembly vs. Zombies) is a precise scripting framework for 
Plants vs. Zombies written in C++. The underlying mechanism was
discovered by yuchenxi0_0，then further developed by vector-wlc.

This project uses MinGW+cmake as Toolchain.

## 原理

在游戏主循环函数前面注入键控代码，使得键控脚本在每一帧都被调用，从而实现真正意义上100%精确的键控。

## 对比

从原理可以明显看出此套框架在理论实现上与传统框架截然不同，传统框架使用一个程序向 PvZ 窗口发送点击消息，而此套框架使用代码注入，直接入侵到程序内部，让游戏程序运行我们编写的脚本！其优缺点大致如下：

> 缺点 
>
> * 编写不慎可能会导致游戏崩溃

> 优点
>
> * 精度极高
> * 脚本出现错误时提示更加人性化
> * 对硬件配置 (CPU) 的要求低
> * 对操作时间顺序不做严格要求

## 使用

#### MinGW Visual Studio Code
在 [https://wwe.lanzous.com/b015az7nc](https://wwe.lanzous.com/b015az7nc) (a0a3) 下载压缩包，
解压并使用 [VSCode](https://code.visualstudio.com/) 打开，无需任何配置，便可直接使用。<br>
在 [https://wwe.lanzous.com/b015az8yj](https://wwe.lanzous.com/b015az8yj) (37zu) 下载相应版本包，
进行更新或退回，注意在 2020_07_10 之后的版本包将只支持新的 [VSCode](https://code.visualstudio.com/) 环境包

## 致谢
[yuchenxi2000/AssemblyVsZombies](https://github.com/yuchenxi2000/AssemblyVsZombies)<br>
[lmintlcx/pvzscript](https://github.com/lmintlcx/pvzscripts)<br>
[失控的指令(bilibili)](https://space.bilibili.com/147204150/)<br>
[Power_tile(bilibili)](https://space.bilibili.com/367385512)
