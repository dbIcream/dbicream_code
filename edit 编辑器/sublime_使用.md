##安装sublime
- 下载安装
[官网下载地址](https://www.sublimetext.com/3)，安装时尽量使用较新的版本，推荐使用最新版本，通过注册码注册使用。旧版本可能找不到channel.json。

##安装插件
- [安装package control](http://www.cnblogs.com/luoshupeng/archive/2013/09/09/3310777.html)
命令建议是从官网上去加载最新的：https://packagecontrol.io/installation

- [设置主题](https://www.jianshu.com/p/13fedee165f1)
推荐使用主题：**material**，[绿色护眼主题](https://github.com/waer24/sublimeTheme)，[其他主题推荐](https://www.zhihu.com/question/46266742)

- [sublime text怎么同步更新主题](http://blog.csdn.net/zhangyu_h321/article/details/54709503)
- [no package available解决](http://www.jianshu.com/p/23d1ec6988e5)
由于墙的原因，可能安装之后仍然是经常找不到插件，这个可能是channel的配置问题。
- [更新侧边框图标](https://github.com/ihodev/a-file-icon)
- [Sublime Text 离线安装插件的方法](http://blog.csdn.net/juhaotian/article/details/50978707)

##自定义显示优化
首选项->设置
```
{
	"auto_complete": true,		//自动补全
	"auto_match_enabled": true,	//自动匹配
	"color_scheme": "Packages/Color Scheme - Legacy/IDLE.tmTheme",	//设置
	"font_size": 14,	//字体大小
	"word_wrap": true,	//自动超过显示长度后自动换行
	"wrap_width": 120,	//单行显示最大长度
	"tab_size": 4,		//设置tab长度
	"translate_tabs_to_spaces": true,	//设置自动用空格替换tab键
	//若要在保存时自动把tab 转换成空格，请把值设置成 true，如不需要: 设置成 false
	"expand_tabs_on_save": true,	
	//此行的主要作用是, 当某行为空格且无其它字符时, 保存时会去除空白  
	"trim_trailing_white_space_on_save": false,  
	"ignored_packages":
	[
		"Vintage"
	],
	"update_check": false  //设置不自动检测更新
}
```

##配置python环境
- Ctrl+shift+p 键入 install packages
- 稍等片刻后，键入 SublimeREPL 安装即可
- [设置编译快捷键](https://www.zhihu.com/question/22904994)


##配置C开发环境
[参考链接](http://blog.csdn.net/pjchigan/article/details/53889469)
绝对路径是：C:\Users\XXX\AppData\Roaming\Sublime Text 3\Packages\User
配置好gcc和g++环境，cmd窗口输入gcc -v可显示则gcc环境正常
```
{
    "cmd": ["g++", "${file}","-o", "${file_path}/${file_base_name}"],
    "file_regex":"^(..[^:]*):([0-9]+):?([0-9]+)?:? (.*)$",
    "working_dir":"${file_path}",
    "selector": "source.c,source.c++",
    "encoding":"cp936",
    "shell": true,

    "variants":
    [
        {
            "name": "Run",
            "cmd": ["CMD", "/U", "/C", "g++ ${file} -o${file_base_name} &&${file_base_name}"] 
        }
    ]
}
```
- [使用makefile编译多个文件](http://www.yalewoo.com/sublime_text_3_gcc.html)
- [c开发常用插件](http://www.jianshu.com/p/595975a2a5f3)







