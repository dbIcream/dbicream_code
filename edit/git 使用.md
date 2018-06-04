<!-- TOC -->

- [介绍文档](#介绍文档)
- [git的初始化](#git的初始化)
    - [初始仓库](#初始仓库)
    - [记住全局的用户名邮箱](#记住全局的用户名邮箱)
    - [记住密码](#记住密码)
    - [git修改密码后删除已经保存的密码](#git修改密码后删除已经保存的密码)
    - [查看global参数](#查看global参数)
- [git文件添加及提交](#git文件添加及提交)
    - [添加文件和添加全部](#添加文件和添加全部)
    - [删除文件](#删除文件)
    - [查看本地状态](#查看本地状态)
    - [提交修改](#提交修改)
    - [同步远程仓库到本地](#同步远程仓库到本地)
    - [将本地改动推送到远端仓库](#将本地改动推送到远端仓库)
- [其他场景](#其他场景)
    - [git放弃修改，强制覆盖本地文件](#git放弃修改强制覆盖本地文件)
    - [gitignore忽略文件](#gitignore忽略文件)
    - [Everything up-to-date问题解决](#everything-up-to-date问题解决)

<!-- /TOC -->


# 介绍文档
- [Git简介 - 廖雪峰](http://www.liaoxuefeng.com/wiki/0013739516305929606dd18361248578c67b8067c8c017b000/001373962845513aefd77a99f4145f0a2c7a7ca057e7570000)
- [GitHub从入门到精通常用命令](http://blog.csdn.net/piaopiaopiaopiaopiao/article/details/42239651)

# git的初始化
## 初始仓库
```
git init
git clone  https://github.com/dbIcream/dbicream_code.git
```

## 记住全局的用户名邮箱
git上使用的用户名是昵称，不是邮箱  
```
git config --global user.name "dbIcream"  
git config --global user.email "doubleicream@163.com"  
```

## 记住密码
```
git config --global credential.helper store  
```

## git修改密码后删除已经保存的密码
先查看是否保存了密码： git config --list  
编辑并删除密码（下次就会要求你重新输入）： git config --global --edit, 删除掉[credential]和store的值，即可  


## 查看global参数
```
git config --list | grep helper
```


# git文件添加及提交
## 添加文件和添加全部
```
添加单个文件： git add README  
添加全部文件： git add . 或者 git add *  
```

## 删除文件
```
git rm file
```

## 查看本地状态
文档增加、删除、修改的状态等，
```
显示具体信息（推荐）： git status  
简要显示信息： git status -s 
```

## 提交修改
提交说明是必须要有的操作
```
添加提交说明： git commit -m "this ia a change"  
提交一个文件更新： git commit file  
提交所有更新： git commit .  
```

## 同步远程仓库到本地
主要使用git pull这个命令  
```
拉取远程分支github的更新： git fetch github  
拉取远程master分支的更新： git fetch  
合并远程分支到本地： git merge github/master  
合并到本地的origin分支： git merge  
拉取+合并(确认本地没有修改时推荐使用): git pull origin master 
拉取+合并的缩写： git pull  
```

## 将本地改动推送到远端仓库
```
git push [alias] [branch]  
git push  origin master:master  
```

# 其他场景
## git放弃修改，强制覆盖本地文件
[参考链接](http://blog.csdn.net/tmtongming/article/details/73178997)  
放弃本地的修改，适合确定放弃本地修改的场景。  
```
git fetch --all  
git reset --hard origin/master   
git pull  
```

## gitignore忽略文件
[参考链接](https://blog.csdn.net/u014079773/article/details/51602344)  
首先生成一个忽略的列表的文件  
```
.gitignore  
```

在.gitignore中添加要忽略的文件名或者目录名  
```
file1
*.txt
/dir1/
```
## Everything up-to-date问题解决  
[参考链接](https://www.jianshu.com/p/899b9e66a3db)  
可能原因是太久没有更新，导致本地的仓库需要先做更新后才能push  
```
# 新建分支
git branch newbranch
# 验证分支是否创建成功
git branch
# 进入分支提交修改
git checkout newbranch
git commit . -m "更新说明"
# 切换到主分支，并merge上面新建的分支
git checkout master
git merge newbranch
# 有冲突时需要解决冲突
git diff
# 无冲突或者冲突解决之后，提交修改
git push -u origin master
# 删除临时的分支
git branch -D newbranch
# 如果想保留分支只是想删除已经合并的部分只要把大写的D改成小写的d就行了
git branch -d newbranch
```



