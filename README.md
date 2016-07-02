是什么
---

一个分布式系统通常由client（SDK）、master、worker等角色组成。
在实践中，当要开始一个新项目时，总是得先花一段时间配好各种依赖，然后写个hello world验证环境等的正确性。
为了节约时间，把这些初始化工作整理一下，基础依赖、编译等已经“搞定”，可以快速开始实现项目自己的逻辑。

依赖sofa-pbrpc进行网络通信；
使用gflags解析配置选项。


怎么用
---

`./build.sh` 搞定依赖，依赖无变更时只用执行一次

`make master` 编译master

`make client` 编译client工具

运行 master： `./master --flagfile=./taocipian.flag`

运行 client：`./client --flagfile=./taocipian.flag`


正确的实现
---

目的在于为以后init一个项目节约时间。
感觉正确的办法应该是实现一个编程模型或框架，而不是像现在这样搞一些copy & paste的代码片段 ＝。＝
