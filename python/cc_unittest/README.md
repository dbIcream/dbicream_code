<!-- TOC -->

- [单元测试](#单元测试)
    - [单元测试介绍](#单元测试介绍)
        - [测试步骤](#测试步骤)
    - [接口说明](#接口说明)

<!-- /TOC -->


# 单元测试
[参考链接](参考链接：http://www.cnblogs.com/beer/p/5418471.html)
## 单元测试介绍
导入的库： import unittest
1、自定义的类要继承于基础类： unittest.TestCase， 如class MyUnitTest(unittest.TestCase)
2、一个类可以同时测试多个用例，每个测试用例以test_开始，如test_url()
3、测试前的准备工作，都会调用setUp(self)函数
4、测试结束的清理工作，可以放在tearDown(self)中处理

### 测试步骤
1、装载测试用例
2、加载测试套件
3、运行测试用例
4、分析测试结果

## 接口说明
无