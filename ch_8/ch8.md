# ch8

## 缓冲区

stdio.h头文件中的getchar属于携带缓冲的

conio.h头文件中的getche不带缓冲

## 文件/流/标准流

从概念来说c程序处理的是一个流而不是直接处理文件

标准IO包:键盘和显示设备作为每个c程序自动打开的文件来对待.
- 键盘输入 stdin
- 输出 stdout
getchar,putchar,printf,scanf都是标准IO包的成员

与处理文件相同的技术来处理键盘输入.

## 文件结尾

文件夹结尾的标志有很多
- Ctrl+Z表示结尾
- 根据os标注文件大小判断是否到达结尾

处理的函数会返回一个EOF的值标识文件到达末尾,如getchar
```
// stdio.h中定义的EOF
# define EOF(-1)
```

## 命令行:输入输出重定向

将标准输入输出重定向为其他的流,如文件

'''
#  echo为程序
echo<hello.txt # 输入为hello.txt
echo>hello.txt # 输出为hello.txt
echo>>hello.txt # 追加
echo>file1<file2 #  组合重定向
'''

## getchar

getchar 读取单个字符,回车也算单个字符,使用循环读取字符时

scanf读取字符串会跳过空格,制表符,换行符,读取字符时和getchar不会