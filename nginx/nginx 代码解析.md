<!-- TOC -->

- [nginx模块](#nginx模块)
    - [http模块](#http模块)
    - [ngx_request_t结构体](#ngx_request_t结构体)
    - [http头部](#http头部)
    - [http包体](#http包体)
    - [发送应答](#发送应答)

<!-- /TOC -->

# nginx模块

## http模块

- 模块处理函数：ngx_http_block
- ngx_http_init_phase_handlers
- ngx_http_core_content_phase
- ngx_http_finalize_request

## ngx_request_t结构体

- uri：uri_start，uri_end
- method方法：method_start，method_end
- 文件扩展名：extern，uri_ext
- 参数：args_start
- 协议版本：http_protocol，http_version
- 原始的用户请求行：request_start，request_end

## http头部

- http头部：header_in，headers_in

头部的数据保存在ngx_http_headers_in_t结构体中，每个头部对应一个ngx_table_elt_t中，NULL时表示为空

```conf
#举例判断Rpc-Desicription头部是否值为uploadFile
ngx_list_part_t *part = &r->headers_in.headers.part;
ngx_table_elt_t *header = part->elts; // 开始遍历链表

//开始遍历链表
for (i = 0; /* void */; i++) {
    if (i >= part->nelts) { // 判断是否到达链表中当前数组的结尾处
        if (part->next == NULL) {// 是否还有下一个链表数组元素
            break;
        }
    /* part设置为next来访问下一个链表数组；header也指向下一个链表数组的首地址；i设置为0时，表示从头开始遍历新的链表数组
    */
        part = part->next;
        header = part->elts;
        i = 0;
    }

    // hash为0时表示不是合法的头部
    if (header[i].hash == 0) {
        continue;
    }
    /*判断当前的头部是否是“Rpc-Description”。如果想要忽略大小写，则应该先用header[i].lowcase_key代替header[i].key.data，然后比较字符串*/
    if (0 == ngx_strncasecmp(header[i].key.data, (u_char*) "Rpc-Description", header[i].key.len))
    {
        // 判断这个HTTP头部的值是否是“uploadFile”
        if (0 == ngx_strncmp(header[i].value.data, "uploadFile",
        header[i].value.len))
        {
            // 找到了正确的头部，继续向下执行
        }
    }
}
```

## http包体

- 异步读body：ngx_http_read_client_request_body
- 通过回调post_handler来返回处理状态

```c
ngx_int_t rc = ngx_http_read_client_request_body(r, ngx_http_mytest_body_handler);
    if (rc >= NGX_HTTP_SPECIAL_RESPONSE){
        return rc;
    }
}
return NGX_DONE;
```

## 发送应答

ngx_http_send_header() 处理响应  
ngx_http_output_filter 身客户端发送HTTP响应包体  

ngx_pcalloc(pool, size)  
ngx_create_temp_buf  

ngx_http_output_filter 发送磁盘中的文件  