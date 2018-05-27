<!-- TOC -->

- [日志封装使用](#日志封装使用)
    - [日志级别](#日志级别)
    - [如何自定义日志类](#如何自定义日志类)
    - [调用实例](#调用实例)
    - [提供的接口](#提供的接口)

<!-- /TOC -->
****************************************************
# 日志封装使用
[参考链接](https://www.cnblogs.com/goodhacker/p/3355660.html)

## 日志级别
日志级别：NOTSET < DEBUG < INFO < WARNING < ERROR < CRITICAL

## 如何自定义日志类
基础的日志类： import logging

logging.getLogger(log_name)
**每个log_name对应一个唯一的一个日志文件**。封装自定义的日志文件，其实我们要自定义这个log的一些特性，比如：
- 输出的路径， FileHandler, StreamHandler
- 是否输出到终端，addHandler
- 输出的格式，setFormatter
- 输出的级别，setLevel

## 调用实例
cc_log下的cc_log.py
```
#调用示例
logger = cc_log.CC_Log(log_file).get_log()
    logger.debug('some data')
```
## 提供的接口
| 提供的接口 | 接口说明 | 备注 |
| ---------- | -------- | ---- |
| 无         | 无       | 无   |



