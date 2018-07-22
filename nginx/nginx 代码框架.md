<!-- TOC -->

- [nginx代码框架](#nginx代码框架)
    - [初探nginx架构](#初探nginx架构)
    - [connection连接](#connection连接)
    - [request结构](#request结构)

<!-- /TOC -->

# nginx代码框架

## 初探nginx架构
参考链接： <http://tengine.taobao.org/book/chapter_02.html#id1>

- 进程模型：master -> worker
- 事件模型
- 包括网络事件
- 信号，定时器事件

## connection连接

<http://tengine.taobao.org/book/chapter_02.html#id1>

- 封装的结构体：ngx_connection_t socket
- 连接池：worker_connections
- 多进程互斥锁：accept_mutex
- 用来控制互斥锁的变量：ngx_accept_disabled

## request结构

<http://tengine.taobao.org/book/chapter_02.html#id1>

- 请求的结构体：gx_http_request_t
- 请求的开始：ngx_http_init_request()，并设置读事件
- **解析请求行**：ngx_http_process_request_line() ->ngx_http_parse_request_line()
- **解析请求头部**：ngx_http_process_request_headers() -> ngx_http_parse_header_line()

需要特殊处理的请求头放在hash表中：ngx_http_headers_in，使用时如果查找到就使用对应的处理函数，如：ngx_http_process_host()。
当nginx解析到两个回车换行符时，就表示请求头的结束。
解析完请求头处理请求：ngx_http_process_request()

- 请求头大小限制。通过client_header_buffer_size来设置，不够大时可以通过large_client_header_buffers来设置更大的buffer。
- 设置读写事件的处理函数

ngx_http_request_handler()  
read_event_handler()：ngx_http_block_reading()，先不读取请求实体  
write_event_handler() : ngx_http_core_run_phases()  

- 调用各种filter

ngx_http_header_filter()  
ngx_http_write_filter()  
最终产生的响应头会放在ngx_http_request_t的**headers_out**中  
