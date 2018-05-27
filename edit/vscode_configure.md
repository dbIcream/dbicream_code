<!-- TOC -->

- [主题](#主题)
- [markdown插件](#markdown插件)
    - [代码相关插件](#代码相关插件)
- [git配置环境](#git配置环境)
- [快捷键](#快捷键)
    - [代码相关](#代码相关)
        - [内容及文件查找](#内容及文件查找)
- [设置](#设置)
- [编译c代码](#编译c代码)
- [运行python代码](#运行python代码)
    - [安装环境](#安装环境)
    - [切换到调试](#切换到调试)

<!-- /TOC -->

查看vs code的官网说明，可以解决很多问题。官网的地址：https://code.visualstudio.com/docs/?dv=win。

# 主题
**文件（首选项） -> 设置 -> 颜色主题**
主题名称： one dark pro
其他主题： monokai

# markdown插件
表格格式化： table format 


## 代码相关插件
- 自动补全： include autocomplete
- 括号高亮匹配： Bracket Pair Colorizer
- 字符数统计： word count

# git配置环境
[参考链接] (https://www.cnblogs.com/geekfeier/p/7649695.html)
配置git环境其实就是将git的路径配置给vscode，文件 -> 首先项 -> 设置
"git.path": "D:/Env/Git/cmd/git.exe",


# 快捷键
F11 切换全屏
是否关闭资源管理器：ctrl + b
功能管理： Ctrl + Alt + P 
跳转到上一次编辑位置： alt + 左箭头
跳转到下一次编辑位置： alt + 右箭头
将当前行上下移动一行： alt + 上下箭头

## 代码相关
多行注释： ctrl + /

### 内容及文件查找
当前文件查找： ctrl + F
**查找文件**： ctrl + p
查找项目里面的内容： ctrl + shift + F
在查找结果里面跳转到上一个位置： F3
在查找结果里面跳转到下一个位置： shift + F3

# 设置
文件 -> 首选项 -> 设置，在出现的配置单上，将default里面的配置拷到user中再修改。
**下面这个是我使用的配置文件，会经常更新**
```
{
    // 以像素为单位控制字号。
    "editor.fontSize": 18,
    "workbench.colorTheme": "One Dark Pro",
    "workbench.iconTheme": "eq-material-theme-icons",
    "materialTheme.fixIconsRunning": false,
    "git.ignoreMissingGitWarning": true,
    "git.path": "D:/Env/Git/cmd/git.exe",

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
}
```
# 编译c代码
右键点击callback.c，选择在命令提示符中打开
编译： gcc -g -o main callback.c
运行： ./main

# 运行python代码
## 安装环境
python
python -m pip install --upgrade pip
pip install pylint

## 切换到调试
添加一个断点，然后按F5进入调试
F5：调试/继续，
F10：单步跳过，
F11：单步进入，
Shift+F11：跳出
F9：切换断点

