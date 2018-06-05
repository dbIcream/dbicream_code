# -*- coding:utf-8 -*-
#!/usr/local/bin/python3

__author__ = 'dbicream'

from _overlapped import NULL
import unittest

class TestCommonCase(unittest.TestCase):

    def setUp(self):
        # print('init by setUp...')
        pass

    def tearDown(self):
        # print('end by tearDown...')
        pass

    def test_upper(self):
        self.assertEqual('foo'.upper(), 'FOO')

    def test_isupper(self):
        self.assertTrue('FOO'.isupper())
        self.assertFalse('Foo'.isupper())
        self.assertTrue('Foo'.isupper())

    def test_split(self):
        s = 'hello world'
        self.assertEqual(s.split(), ['hello', 'world'])
        # check that s.split fails when the separator is not a string
        with self.assertRaises(TypeError):
            s.split(2)
    def test_null(self):
        self.assertTrue('', NULL)


if __name__ == '__main__':
    # unittest.main()
    
    # 装载测试用例
    test_cases = unittest.TestLoader().loadTestsFromTestCase(TestCommonCase)

    # 手动顺序加载
    test_cases = [TestCommonCase('test_isupper'), TestCommonCase('test_split')]
    
    # 使用测试套件并打包测试用例
    suite = unittest.TestSuite()
    suite.addTests(test_cases)
    suite.addTest(TestCommonCase('test_null'))
    
    # 运行测试套件，并返回测试结果
    runner = unittest.TextTestRunner(verbosity=2)
    result = runner.run(suite)
    
    #生成测试报告
    # print("testsRun:%s" % result.testsRun)
    # print("failures:%s" % len(result.failures))
    # print("errors:%s" % len(result.errors))
    # print("skipped:%s" % len(result.skipped))
    
    
    