# ch7

## if���

```
if (expression) statement
```

expressionΪ1 ��ִ��statement

��else��if���

```
if (expression) statement1 else  statement2
```

����ѡ�� else if

```
if (expression1) statement1 else if (expression2) statement2 else statement3
```

�ڶ���if else �����,���statement���Ǹ������(Ҳ����û�л�����),else���Զ����һ��if����ƥ��,���ֻ��ƿ��ܻᵼ�³�����Ϊ��Ԥ�ڵĲ�һ��

����������Ƿ��Ƕ�����䶼�û�����������

## getchar �� putchar����

������������stdio.h�ж���

- getchar(): ��ȡ�����豸�������һ���ַ�
- putchar(char c): ��ӡ����һ��char����c

## ctype.h ͷ�ļ�

����һϵ���ַ�������,��isalpha()...

## �߼������

- && ��
- || ��
- ! ��

ֻҪ������ iso646.hͷ�ļ��Ϳ���ʹ�����±�ʾ����ʾ�߼������

- && = and
- || = or
- ! = not

&& �� || ���ȼ���,���߶����ڹ�ϵ�����,���ڸ�ֵ�����

�� ! ��������ͼ��������ͬ����

��ֵ����� : = , *= ...

�߼������ : && ...

��ϵ����� : \< , \<= ...

��������� : + , - ....

�����ͼ�������� : ++ , --

���ʹ�ö��������ʱ,��ʹ֪�����ȼ�,���ҲҪ��������������������ȼ�

## ��������� ? :

```
expression1 ? expression2 : expression3
```

��� expression1Ϊ�� ���������ʽֵΪexpression2 ����Ϊexpression3

```
max=a>b ? a : b ;// ȡa,b�����ֵ
```

## ѭ�������ֶ�:continue,break

continue : ��������ѭ��,��ִ��continue֮������,ֱ�ӽ�����һ��ѭ��

break : ������ǰѭ��

## ����ѡ�� switch���

```
switch (expression) {
    case constant1:
        // �����1
        break; // ������� break ���ܻ���ִ�͸����
    case constant2:
        // �����2
        break;
    // ...
    default:
        // Ĭ�ϴ����
}

```

expressionͨ����һ������,�������Ϳ������������ͣ���int��char��short��long�ȣ���ö�����͡�����ζ��ֻ���������ͺ�ö�����͵ı�����������switch���ı��ʽ��(**û�а�����������**)

constant �����Ǳ���ʱ��ȷ���ĳ���ֵ���������Ǳ�����������Ϊswitch����ڱ���ʱ���о�̬��������������Ӧ����ת����ʵ�ֿ��ٵ�������֧

һ����ԣ�switch�����ĳЩ����¿��ܱ�if�����и��õ����ܣ��ر��ǵ���Ҫ��ͬһ�����ʽ���ж������ֵ�ıȽ�ʱ��������Ϊswitch������ͨ��������ת����ת����һ������ÿ��case��ǩ��Ӧ�����ַ�ı���ʵ�ֿ��ٵ�������֧���Ӷ������˱ȽϵĴ�����

## goto ���

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
        goto start; // ��ת����ǩ "start" ��
    }

    printf("Program continues...\n");
    return 0;
}

```

һ��goto����ɵĳ���,���������������,ѭ�����.�����ܵı���goto,����goto,ֻ���ô���ɶ��Ա�ø���.��goto���������ѭ��,�൱����,����ʱ��ʹ��Ҳ���ܹ������ܵ�.
