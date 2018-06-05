<!-- TOC -->

- [unittest单元测试](#unittest单元测试)
    - [使用的库](#使用的库)
    - [使用步骤](#使用步骤)
    - [定义测试类](#定义测试类)
        - [setUp()准备工作](#setup准备工作)
        - [tearDown()清理工作](#teardown清理工作)
        - [setUpClass()/tearDownClass()](#setupclassteardownclass)
        - [test_func()测试用例](#test_func测试用例)
        - [路过某个case](#路过某个case)
            - [skip装饰器](#skip装饰器)
            - [TestCase.skipTest()](#testcaseskiptest)
    - [定义测试套件](#定义测试套件)
        - [使用TestLoader无序加入](#使用testloader无序加入)
        - [手动指定顺序加入](#手动指定顺序加入)
        - [将测试的用例加入套件](#将测试的用例加入套件)
    - [获取执行结果](#获取执行结果)
        - [设置报告的详细程度](#设置报告的详细程度)
        - [输入到文件中](#输入到文件中)
    - [生成漂亮的HTML报告](#生成漂亮的html报告)

<!-- /TOC -->


# unittest单元测试
[参考链接](https://blog.csdn.net/huilan_same/article/details/52944782)

## 使用的库
- unittest, 定义基础的测试类： unittest.TestCase。嵌套的TestSuite。  

## 使用步骤
- 定义自定义的的测试类，继承unittest.TestCase
- 实例化测试类， TestLoader()
- 定义测试套件， TestSuite(), 将实例化的类对象添加到测试套件
- 执行用例， TextTestRunner(), 执行测试类中的所有测试函数


## 定义测试类
### setUp()准备工作
非必须的函数，如果我们没有需要初始化的一些环境时，可以不需要重新定义setUp()  

### tearDown()清理工作
非必须的函数，如果我们初始化的一些环境时，可以使用teerDown()进行一些清理工作。如果不需要清理时可以不用重新定义  

### setUpClass()/tearDownClass()
在所有case执行之前准备一次环境，并在所有case执行结束之后再清理环境.  

### test_func()测试用例
通常直接用来测试方法的执行是否符合预期。每一次执行前后都会去调用setUp()和tearDown()  
```
def add(a, b):
    return a+b
def test_add(self):
    """Test method add(a, b)"""
    self.assertEqual(3, add(1, 2))
    self.assertNotEqual(3, add(2, 2))
```

### 路过某个case
#### skip装饰器
unittest.skip(reason). skip无条件跳过  
unittest.skipIf(condition, reason), 当condition为True时跳过  
unittest.skipUnless(condition, reason), skipUnless当condition为False时跳过  
```
@unittest.skip("I don't want to run this case.")
def test_divide(self):
    """Test method divide(a, b)"""
    print "divide"
    self.assertEqual(2, divide(6, 3))
    self.assertEqual(2.5, divide(5, 2))
```

#### TestCase.skipTest()
```
def test_divide(self):
    """Test method divide(a, b)"""
    self.skipTest('Do not run this.')
    self.assertEqual(2, divide(6, 3))
    self.assertEqual(2.5, divide(5, 2))
```

## 定义测试套件
我们定义的类里面的测试用例可能有**先后顺序**。  

### 使用TestLoader无序加入
这种方式会把所有的测试用例test_func()全部加入，而且没有指定顺序，到时候会无序执行。  
```
test_cases = unittest.TestLoader().loadTestsFromTestCase(TestCommonCase)
```
### 手动指定顺序加入
将TestCommonCase的类，手动加入，执行顺序与加入的顺序有关。**可以只加入部分用例**。  
```
test_cases = [TestCommonCase('test_isupper'), TestCommonCase('test_split'), TestCommonCase('test_null')]
```
### 将测试的用例加入套件
suite.addTest()  
suite.addTests()  
suite.countTestCases(), 返回当前加入的用例数。  
```
suite = unittest.TestSuite()
suite.addTests(test_cases)
```


## 获取执行结果
### 设置报告的详细程度
- 默认级别是1
- 设为0时，则不输出每个用例的执行结果；  
- 设置为2，则输出详细的执行结果。  
```
runner = unittest.TextTestRunner(verbosity=2)
result = runner.run(suite)
```

### 输入到文件中
```
with open('UnittestTextReport.txt', 'a') as fd:
    runner = unittest.TextTestRunner(stream=fd, verbosity=2)
    runner.run(suite)
```


## 生成漂亮的HTML报告
[参考链接](https://blog.csdn.net/huilan_same/article/details/52944782)