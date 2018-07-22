<!-- MarkdownTOC -->

- [参考链接](#参考链接)
- [插件列表](#插件列表)
- [主题](#主题)
- [插入目录](#插入目录)
    - [markdown editing配置文件](#markdown-editing配置文件)
    - [Markdown Preview配置](#markdown-preview配置)
    - [MarkdownTOC配置](#markdowntoc配置)

<!-- /MarkdownTOC -->

***
# 参考链接
[在 Sublime 中配置 Markdown 环境 - Blog of 太极儒](http://frank19900731.github.io/blog/2015/04/13/zai-sublime-zhong-pei-zhi-markdown-huan-jing/)

# 插件列表
- Markdown Editing ，md文件编写的插件
- Markdown Preview， md文件预览的插件
- Table Editor ，表格对齐的工具
- MarkdownTOC ，生成目录

# 主题
主题推荐：Monokai Extended & Markdown Extended
操作步骤：
- ctrl + alt + p
- 输入： Markdown Extended（点击Set Syntax: Markdown Extended）

# 插入目录
点击 Tools -> MarkdownTOC -> Insert TOC

## markdown editing配置文件
GMF的user配置
```
{
    "extensions":
    [
        "md",
        "md - Preview",
    ],
    "color_scheme": "Packages/Monokai Extended/Monokai Extended.tmTheme",
    "line_numbers": true, //显然这个是显示行号的。
    "expand_tabs_on_save": true,

    "line_padding_top": 4,
    "line_padding_bottom": 4,

    "tab_size": 4,                     //tab占用的字符数
    "translate_tabs_to_spaces": true,   //tabale替换为空格

    "draw_centered": false,//不居中显示

    "word_wrap": true,// 强制换行
    "wrap_width": 120, // 每行字符数上限
    "rulers": [],
    "line_numbers": true,
    "highlight_line": false,
    "word_wrap": true,
}
```

## Markdown Preview配置
```
{
    "parser": "github",
    //"build_action": "browser",    //编译后使用浏览器打开，配置时ctrl+b时要卡挺久的
    "enable_mathjax": true,
    "enable_uml": true,
    "enable_highlight": true,
    "enable_pygments": true,
    "enabled_extensions": "github",
    "enabled_parsers": ["github"],
    "github_mode": "markdown",
    "github_inject_header_ids": true,
    "enable_autoreload": false
}
```
**添加快捷键**
{ "keys": ["alt+m"], "command": "markdown_preview", "args": {"target": "browser", "parser":"markdown"}  }
{ "keys": ["alt+m"], "command": "markdown_preview", "args": {"target": "browser", "parser":"github"}  }

## MarkdownTOC配置

```conf
{
    "default_autoanchor": false,   //目录以链接形式呈现
    "default_autolink": true,    //生成链接
    "default_bracket": "round",  //括号包含标题的锚点
    "default_depth": 0,           //无限目录深度
    "default_indent": "\t",
    "default_remove_image": true,
    "default_link_prefix": "",
    "default_list_bullets": "-",
    "default_lowercase": true,
    "default_lowercase_only_ascii": true,
    // "default_style": "ordered", //顺序显示，修改id的显示
    "default_uri_encoding": false, //开启时中文标题可能支持异常
    "default_markdown_preview": false,
    "id_replacements": {
    "-": " ",
    "" : ["&lt;","&gt;","&amp;","&apos;","&quot;","&#60;","&#62;","&#38;","&#39;","&#34;","!","#","$","&","'","(",")","*","+",",","/",":",";","=","_","?","@","[","]","`","\"", ".","<",">","{","}","™","®","©"]
    },
    "logging": false
}
```
