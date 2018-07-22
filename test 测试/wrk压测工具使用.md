<!-- TOC -->

- [wrk工具使用](#wrk工具使用)
    - [wrk安装](#wrk安装)
    - [wrk的使用](#wrk的使用)
        - [使用示例](#使用示例)
        - [常用参数](#常用参数)
    - [结果展示](#结果展示)

<!-- /TOC -->

# wrk工具使用

## wrk安装

<https://www.cnblogs.com/savorboard/p/wrk.html>

下载，编译生成wrk的二进制文件  

```shell
# 从git下载源码
git clone https://github.com/wg/wrk.git

# 编译，自动在当前目录下生成一个wrk二进制文件
make
```

## wrk的使用

### 使用示例

```shell
./wrk -c 1 -t 1 -d 1 http://www.baidu.com
```

### 常用参数

- 并发请求数：-c
- 使用线程数：-t，2-4为宜
- 测试时间10秒：-d
- tcp超时时间：-T
- 添加头部：-H或者--header。 示例：-H "User-Agent: wrk"
- 添加lua脚本：-s。 调用lua的代码解析：luaL_loadfile() / luaL_loadfilex()
- 其他参数。如查看响应时间的分布情况可以加上--latency参数

```shell
./wrk -c 30 -t 2 -d 10 --latency http://www.baidu.com
```

## 结果展示

- Latency：响应时间
- Req/Sec：每个线程每秒钟的完成的请求数，重要的压力测试性能指标，可以看出应用程序的吞吐量
- Avg：平均
- Max：最大
- Stdev：标准差
  标准差如果太大说明样本本身离散程度比较高. 有可能系统性能波动很大
- +/- Stdev： 正负一个标准差占比
