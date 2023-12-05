
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define _CDEBUG_
#define ElemType int

// 双链表实现,循环双链表
// 带头节点,不带尾节点

typedef struct CLNode
{
    ElemType data;
    struct CLNode *next, *prior;
} CircularLinkedNode, *CNodePointer;

void traverseList(CNodePointer header, char *(*DataToString)(ElemType e, char *buff), char *buff);        // v
void reverseTraverseList(CNodePointer header, char *(*DataToString)(ElemType e, char *buff), char *buff); // v

CNodePointer GetNode();                                        // v
CNodePointer GetHeader();                                      // v
CNodePointer List_HeadInsert(CNodePointer header, ElemType e); // v
void DestoryList(CNodePointer header);                         // v
bool ListInsert(CNodePointer header, int i, ElemType e);       // v
bool ListAdd(CNodePointer header, ElemType e);                 // v
int LocateElem(CNodePointer header, ElemType e);               // v
bool ListDelete(CNodePointer header, int i, ElemType *e);      // v
void reverseList(CNodePointer header);                         // v
ElemType GetElem(CNodePointer header, int i);                  // v 没有定义第i个数据如果没有该怎么办
int Length(CNodePointer header);                               // v
bool Empty(CNodePointer header);                               // v
CNodePointer GetTailNode(CNodePointer header);                 // v

#ifdef _CDEBUG_
char *MyToString(ElemType e, char *buff)
{
    return itoa(e, buff, 10);
}
int main()
{
    printf("开始测试\n");

    CNodePointer header = GetHeader();
    char buff[20];
    for (size_t i = 0; i < 5; i++)
    {
        List_HeadInsert(header, i + 10);
    }

    ListAdd(header, 99);
    ListAdd(header, 999);
    printf("99的索引:%d\n", LocateElem(header, 99));
    printf("正向遍历:\n");
    traverseList(header, &MyToString, buff);

    ListInsert(header, 10, 100);
    printf("99的索引:%d\n", LocateElem(header, 99));
    ListDelete(header, 5, NULL);
    printf("100的索引:%d\n", LocateElem(header, 100));

    printf("长度%d\n", Length(header));
    printf("尾巴节点数据:%d\n", GetTailNode(header)->data);
    for (size_t i = 0; i < 20; i++)
    {
        printf("第%d个数据:%d\n", i, GetElem(header, i));
    }
    reverseList(header);
    printf("反向遍历:\n");
    reverseTraverseList(header, &MyToString, buff);
    //-----
    DestoryList(header);
}
#endif

int Length(CNodePointer header)
{
    int length = 0;
    CNodePointer flag = header;
    while (1)
    {
        if (header->next == flag)
        {
            return length;
        }
        header = header->next;
        length++;
    }
}
bool Empty(CNodePointer header)
{
    if (header->next == header)
    {
        return true;
    }
    return false;
}

CNodePointer GetTailNode(CNodePointer header)
{
    return header->prior;
}
ElemType GetElem(CNodePointer header, int i)
{
    // 获得index为i的元素
    if (i < 0)
    {
        return NULL;
    }

    CNodePointer flag = header;
    for (size_t i1 = 0; i1 < i + 1; i1++)
    {
        if (header->next == flag)
        {
            return NULL;
        }
        header = header->next;
    }

    return header->data;
}
void reverseList(CNodePointer header)
{
    // 翻转双链表

    // 从头到尾巴的prior和next进行交换
    CNodePointer flag = header;
    CNodePointer temp;
    while (1)
    {

        if (header->next == flag)
        {
            // 完成当前节点交换
            temp = header->next;
            header->next = header->prior;
            header->prior = temp;
            // 退出
            break;
        }
        // 完成当前节点交换
        temp = header->next;
        header->next = header->prior;
        header->prior = temp;
        // 修改header的位置,由于已经完成了交换,所以下一个需要交换的节点是前一节点
        header = header->prior;
    }
}
// 删除索引为i的节点,如果需要则将数据放入e,不需要则将e设置为NULL
bool ListDelete(CNodePointer header, int i, ElemType *e)
{
    if (i < 0)
    {
        return false;
    }

    // 找到索引节点为i的节点
    CNodePointer flag = header;
    for (size_t i1 = 0; i1 < i + 1; i1++)
    {
        if ((header = header->next) == flag)
        {
            return false;
        }
    }
    if (e != NULL)
    {
        *e = header->data;
    }
    // 删除这个节点
    header->prior->next = header->next;
    header->next->prior = header->prior;

#ifdef _CDEBUG_
    printf("释放数据为:%d的节点\n", header->data);
#endif
    free(header);
    return true;
}
int LocateElem(CNodePointer header, ElemType e)
{
    // 找到某个节点的索引
    CNodePointer flag;
    int index = 0;
    while ((header = header->next) != flag)
    {
        if (header->data == e)
        {
            return index;
        }
        index++;
    }
    return -1;
}
bool ListAdd(CNodePointer header, ElemType e)
{
    // 在最后加入节点
    // 找到最后一个节点
    header = header->prior;
    List_HeadInsert(header, e);
    return true;
}
void addNodeAfterHeader(CNodePointer header, CNodePointer new)
{
    // 将某个节点放到对应节点之后
    new->next = header->next;
    new->prior = header;
    header->next->prior = new;
    header->next = new;
}
// 在第i个位置之前插入
bool ListInsert(CNodePointer header, int i, ElemType e)
{
    if (i <= 0)
    {
        return true;
    }
    CNodePointer flag = header;
    // 找到index为i-2的节点,在其后面插入节点
    for (size_t i1 = 0; i1 < i - 1; i1++)
    {
        if (header->next == flag)
        {
            addNodeAfterHeader(header, GetNode());
        }
        header = header->next;
    }
    List_HeadInsert(header, e);
    return true;
}
CNodePointer GetNode()
{
    CNodePointer new = (CNodePointer)malloc(sizeof(CircularLinkedNode));
    new->next = NULL;
    new->prior = NULL;
    return new;
}

CNodePointer GetHeader()
{
    CNodePointer header = GetNode();
    header->next = header;
    header->prior = header;
    return header;
}

CNodePointer List_HeadInsert(CNodePointer header, ElemType e)
{
    // 头插法
    CNodePointer new = GetNode();
    if (new == NULL)
        return NULL;
    new->data = e;

    new->prior = header;
    new->next = header->next;
    header->next->prior = new;
    header->next = new;
    return new;
}
void traverseList(CNodePointer header, char *(*DataToString)(ElemType e, char *buff), char *buff)
{
    CNodePointer flag = header;
    while (1)
    {
        header = header->next;
        if (header == flag)
        {
            // 等于标记位 也就是首节点==>退出循环
            break;
        }

        printf("节点数据:%s\n", (*DataToString)(header->data, buff));
    }
}
void reverseTraverseList(CNodePointer header, char *(*DataToString)(ElemType e, char *buff), char *buff)
{
    // 反向遍历
    CNodePointer flag = header;
    while (1)
    {
        header = header->prior;
        if (header == flag)
        {
            // 等于标记位 也就是首节点==>退出循环
            break;
        }

        printf("节点数据:%s\n", (*DataToString)(header->data, buff));
    }
}

void DestoryList(CNodePointer header)
{
    // 递归有点麻烦,递归出口需要额外参数

    // 记录首节点
    CNodePointer exitFlag = header;
    CNodePointer nextNode;
    while (1)
    {
        // 获取下一个节点
        nextNode = header->next;

#ifdef _CDEBUG_
        printf("释放节点数据:%d \n", header->data);
#endif
        // 释放当前节点
        free(header);
        // 指向下一个节点
        header = nextNode; // 下一个节点
        if (header == exitFlag)
        {
            break;
        }
    }
}