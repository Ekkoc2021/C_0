# ch7

## if语句

```
if (expression) statement
```

expression为1 则执行statement

带else的if语句

```
if (expression) statement1 else  statement2
```

多重选择 else if

```
if (expression1) statement1 else if (expression2) statement2 else statement3
```

在多重if else 语句中,如果statement不是复合语句(也就是没有花括号),else会自动与第一个if进行匹配,这种机制可能会导致程序行为与预期的不一致

最好是无论是否是多条语句都用花括号括起来

## getchar 和 putchar函数

两个函数都在stdio.h中定义

- getchar(): 获取来自设备输入的下一个字符
- putchar(char c): 打印传入一个char类型c

## ctype.h 头文件

包含一系列字符处理函数,如isalpha()...

## 逻辑运算符

- && 与
- || 或
- ! 非

只要包含了 iso646.h头文件就可以使用以下表示法表示逻辑运算符

- && = and
- || = or
- ! = not

&& 比 || 优先级高,二者都低于关系运算符,高于赋值运算符

而 ! 则和增量和减量运算符同级别

赋值运算符 : = , *= ...

逻辑运算符 : && ...

关系运算符 : \< , \<= ...

算术运算符 : + , - ....

增量和减量运算符 : ++ , --

混合使用多种运算符时,即使知道优先级,最好也要用括号来表明运算的优先级

## 条件运算符 ? :

```
expression1 ? expression2 : expression3
```

如果 expression1为真 则整个表达式值为expression2 否则为expression3

```
max=a>b ? a : b ;// 取a,b中最大值
```

## 循环辅助手段:continue,break

continue : 跳过本次循环,不执行continue之后的语句,直接进入下一轮循环

break : 跳出当前循环

## 多重选择 switch语句

```
switch (expression) {
    case constant1:
        // 代码块1
        break; // 如果丢弃 break 可能会出现穿透现象
    case constant2:
        // 代码块2
        break;
    // ...
    default:
        // 默认代码块
}

```

expression通常是一个变量,变量类型可以是整数类型（如int、char、short、long等）或枚举类型。这意味着只有整数类型和枚举类型的变量可以用作switch语句的表达式。(**没有包含浮点类型**)

constant 必须是编译时可确定的常量值，而不能是变量。这是因为switch语句在编译时进行静态分析，并生成相应的跳转表来实现快速的条件分支

一般而言，switch语句在某些情况下可能比if语句具有更好的性能，特别是当需要对同一个表达式进行多个常量值的比较时。这是因为switch语句可以通过生成跳转表（跳转表是一个包含每个case标签对应代码地址的表）来实现快速的条件分支，从而减少了比较的次数。

## goto 语句

```
#include <stdio.h>

int main() {
    int i = 1;

    start:
    printf("Iteration %d\n", i);
    i++;
    int j = 1;
    j++;
    printf("j: %d\n", j);

    if (i <= 5) {
        goto start; // 跳转到标签 "start" 处
    }

    printf("Program continues...\n");
    return 0;
}

```

一般goto能完成的场景,都能能用条件语句,循环语句.尽可能的避免goto,滥用goto,只会让代码可读性变得更差.用goto来跳出多层循环,相当好用,这种时候使用也是能够被接受的.
