<!-- TOC -->

- [vs的配置指导](#vs的配置指导)
    - [主题](#主题)
    - [markdown插件及使用](#markdown插件及使用)
        - [markdown插件](#markdown插件)
        - [markdown格式化表格](#markdown格式化表格)
        - [markdown预览](#markdown预览)
        - [markdown插入目录及目录更新](#markdown插入目录及目录更新)
    - [其他相关插件](#其他相关插件)
    - [git配置环境](#git配置环境)
    - [快捷键](#快捷键)
        - [代码相关](#代码相关)
        - [内容及文件查找](#内容及文件查找)
    - [Dash和zeal查看文档API](#dash和zeal查看文档api)
    - [设置](#设置)
    - [编译c代码](#编译c代码)
    - [运行python代码](#运行python代码)
        - [安装python环境](#安装python环境)
        - [切换到调试](#切换到调试)

<!-- /TOC -->

***********************************************
# vs的配置指导

查看vs code的官网说明，可以解决很多问题。官网的地址：<https://code.visualstudio.com/docs/?dv=win>
卸载重装：[参考链接](https://blog.csdn.net/qq_36279445/article/details/79650059)

## 主题

**文件（首选项） -> 设置 -> 颜色主题**
深色主题： one dark pro
其他主题： monokai
浅色主题： Solarized Light

## markdown插件及使用

### markdown插件

- 表格格式化： table format
- markdown的outline: code outline
- markdown的preview插件
- markdown TOC
- markdowninit: 检测markdown的语法规范  

### markdown格式化表格

表格插入+表格格式化  

- ctrl + shift + p
- 输入table，找到table insert，插入表格
- 输入table，找到format table，格式化表格

### markdown预览

右键markdown有预览功能

### markdown插入目录及目录更新

右键markdown有插入目录的功能，默认是保存时更新。**一个使用技巧是，打开预览功能，然后根据双击标题来跳转到指定位置。**。
另外，也可以通过outline来快捷标识，安装code outline插件之后，会在左边出现一个outline的框。  

- AL OUTLINE插件:  可以折叠三级标题的outline

## 其他相关插件

- 自动补全： include autocomplete
- 括号高亮匹配： Bracket Pair Colorizer
- 字符数统计： word count
- 行高亮插件： hightlight line
- 单词高亮: highlight-words

## git配置环境

[参考链接](https://www.cnblogs.com/geekfeier/p/7649695.html)  
配置git环境其实就是将git的路径配置给vscode，文件 -> 首先项 -> 设置
"git.path": "D:/Env/Git/cmd/git.exe"。

## 快捷键

F11 切换全屏
是否关闭资源管理器: Ctrl + b  
功能管理： Ctrl + Alt + P  
跳转到上一次编辑位置： alt + 左箭头  
跳转到下一次编辑位置： alt + 右箭头  
将当前行上下移动一行： alt + 上下箭头  

### 代码相关

多行注释： ctrl + /  
strstr

### 内容及文件查找

当前文件查找： ctrl + F  
**查找文件**： ctrl + p  
查找项目里面的内容： ctrl + shift + F  
在查找结果里面跳转到上一个位置： F3  
在查找结果里面跳转到下一个位置： shift + F3  
查找本文件的函数： ctrl + shift + p  

- 查找所有引用的插件: find all references, 快捷键 ctrl + t

## Dash和zeal查看文档API

- 安装Zeal文档库，官网下载安装即可
- vscode安装插件: Dash, 按下ctrl + H调出zeal文档

## 设置

文件 -> 首选项 -> 设置，在出现的配置单上，将default里面的配置拷到user中再修改。  
**下面这个是我使用的配置文件，会经常更新**  

```c
{
    // 以像素为单位控制字号。
    "editor.fontSize": 18,
    "workbench.colorTheme": "Solarized Light",
    "git.ignoreMissingGitWarning": true,
    "git.path": "D:/env/Git/cmd/git.exe",

    //markdown 相关
    // 控制 Markdown 预览中使用的字号(以像素为单位)。
    "markdown.preview.fontSize": 14,
    // 在 Markdown 预览中启用或禁用将类似 URL 的文本转换为链接。
    "markdown.preview.linkify": false,
    // 在一定数量的等宽字符后显示垂直标尺。输入多个值，显示多个标尺。若数组为空，则不绘制标尺。
    "editor.rulers": [80],

    // 在 "editor.wordWrap" 为 "wordWrapColumn" 或 "bounded" 时控制编辑器列的换行。
    "editor.wordWrap": "bounded",
    "editor.wordWrapColumn": 80,
    "gitlens.advanced.messages": {
        "suppressShowKeyBindingsNotice": true
    },
    "gitlens.historyExplorer.enabled": true,
    "workbench.startupEditor": "newUntitledFile",
    "workbench.iconTheme": "material-icon-theme",
}
```

## 编译c代码

右键点击callback.c，选择在命令提示符中打开  
编译： gcc -g -o main callback.c  
运行： ./main  

## 运行python代码

### 安装python环境

python
python -m pip install --upgrade pip
pip install pylint

### 切换到调试

添加一个断点，然后按F5进入调试  
F5：调试/继续，  
F10：单步跳过，  
F11：单步进入，  
Shift+F11：跳出  
F9：切换断点  
