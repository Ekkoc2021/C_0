#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define _LISTDEBUG_
#define ElemType int

// 带头节点单链表==>头节点数据为空
typedef struct SinglyLinkedListNode
{
    ElemType data; // 0 为无效数据
    struct SinglyLinkedListNode *next;
} SinglyLinkedListNode, *NodePointer;

NodePointer GetNode();                                                                            // v
NodePointer List_HeadInsert(NodePointer header, ElemType e);                                      // v
void DestoryList(NodePointer header);                                                             // v
bool ListInsert(NodePointer header, int i, ElemType e);                                           // v 在第i个位置的前面添加节点
bool ListAdd(NodePointer header, ElemType e);                                                     // v 尾巴添加节点
int LocateElem(NodePointer header, ElemType e);                                                   // v 从左边寻找首个数据为e节点
bool ListDelete(NodePointer header, int i, ElemType *e);                                          // v 删除第i个节点
void traverseList(NodePointer header, char *(*DataToString)(ElemType e, char *buff), char *buff); // v 遍历
void reverseList(NodePointer header);                                                             // v 翻转链表
ElemType GetElem(NodePointer header, int i);                                                      // v 获取索引为i的元素
int Length(NodePointer header);                                                                   // v
bool Empty(NodePointer header);                                                                   // v
NodePointer GetTailNode(NodePointer header);                                                      // v 获取尾巴节点

#ifdef _LISTDEBUG_
//------------------TEST--------------------
// 自定义输出数据格式
char *MyToString(ElemType e, char *buff)
{
    return itoa(e, buff, 10);
}

int main(int argc, char const *argv[])
{
    printf("测试开始\n");
    char buff[] = "helloworld!";
    NodePointer header = GetNode();
    printf("是否等于空:%d \n", Empty(header));
    //---
    for (size_t i = 0; i < 10; i++)
    {
        List_HeadInsert(header, i + 10);
    }
    printf("长度:%d\n", Length(header));
    printf("是否等于空:%d \n", Empty(header));
    traverseList(header, &MyToString, buff);
    ListInsert(header, 10, 9090);

    for (size_t i = 0; i < 4; i++)
    {
        ListAdd(header, i + 100);
    }
    printf("长度:%d\n", Length(header));
    printf("数据%d的索引为:%d \n", 0, LocateElem(header, 0));
    printf("数据%d的索引为:%d \n", 103, LocateElem(header, 103));

    int delData;
    if (ListDelete(header, 10, &delData))
    {
        printf("删除节点的数据为:%d \n", delData);
    }
    printf("长度:%d\n", Length(header));
    traverseList(header, &MyToString, buff);
    printf("%d\n", GetElem(header, 9));
    reverseList(header);
    //---
    DestoryList(header);
    printf("%s", buff);
    return 0;
}
#endif
//------------------测试------------------------
int Length(NodePointer header)
{
    int index = 0;
    while (1)
    {
        if (header->next == NULL)
        {
            return index;
        }
        header = header->next;
        index++;
    }
}
bool Empty(NodePointer header)
{
    return header->next == NULL ? true : false;
}

ElemType GetElem(NodePointer header, int i)
{
    if (i < 0)
    {
        return 0;
    }
    // 下标为i的数据元素
    for (size_t i1 = 0; i1 < i + 1; i1++)
    {
        if (header->next == NULL)
        {
            return 0; // 数据不为0
        }
        header = header->next;
    }

    return header->data;
}

void traverseList(NodePointer header, char *(*DataToString)(ElemType e, char *buff), char *buff)
{
    header = header->next;
    int index = 1;
    while (header != NULL)
    {
        printf("第%d个节点数据为:%s \n", index, (*DataToString)(header->data, buff));
        header = header->next;
        index++;
    }
}

void reverseList(NodePointer header)
{
    SinglyLinkedListNode tempHeader;            // 感觉从堆去处理会好一点!
    tempHeader.next = NULL;                     // 必要操作,最后节点会指向这个节点下一个节点,这里是一个野指针,会导致释放的时候出现问题
    NodePointer pendingNode;                    // 正在处理的节点
    NodePointer nextPendingNode = header->next; // 下一个需要处理的节点
    while (1)
    {
        if (nextPendingNode == NULL)
        {
            break;
        }
        pendingNode = nextPendingNode;       // 初始化要处理的节点
        nextPendingNode = pendingNode->next; // 初始化下一个要处理的节点
        pendingNode->next = tempHeader.next; // 当前处理节点指向头节点下一个节点
        tempHeader.next = pendingNode;       // 头节点指向当前处理节点
    }

    header->next = tempHeader.next;
}
bool ListDelete(NodePointer header, int i, ElemType *e)
{
    if (i <= 0)
    {
        return false;
    }

    // 拿到 删除节点的前驱
    for (int index = 0; index < i - 1; index++) // 首节点不算所以直接找到第i个节点
    {
        if (header->next == NULL)
        {
            return false;
        }
        header = header->next;
    }

    if (header->next == NULL)
    {
        return false;
    }
    *e = header->next->data;
    NodePointer temp = header->next;
    header->next = header->next->next;
    free(temp);
    return true;
}

int LocateElem(NodePointer header, ElemType e)
{
    int index = 0;
    while (1)
    {
        if (header->next == NULL)
        {
            break;
        }
        header = header->next;
        if (header->data == e)
        {
            return index;
        }
        index++;
    }
    return -1;
}

bool ListAdd(NodePointer header, ElemType e)
{
    NodePointer tailNode = GetTailNode(header);
    NodePointer newNode = GetNode();
    newNode->data = e;
    tailNode->next = newNode;
    return true;
}

bool ListInsert(NodePointer header, int i, ElemType e)
{
    if (i <= 0)
    {
        return false;
    }

    // 在第i个位置插入节点
    // 获取第i-1个节点
    for (int index = 0; index < i - 1; index++) // 首节点不算所以直接找到第i个节点
    {
        if (header->next == NULL)
        {
            header->next = GetNode();
        }
        header = header->next;
    }
    NodePointer newNode = GetNode();
    newNode->data = e;
    // 在第i个节点插入数据
    if (header->next == NULL)
    {
        header->next = newNode;
        return true;
    }

    newNode->next = header->next;
    header->next = newNode;
    return true;
}

NodePointer GetTailNode(NodePointer header)
{

    while (header->next != NULL)
    {
        header = header->next;
    }
    return header;
}
NodePointer List_HeadInsert(NodePointer header, ElemType e)
{
    // 栈内存是固定:想要通过函数返回一个新内存,不要用栈存放
    // 栈存放的数据在函数结束后会被释放调用,重复调用分配得到newNode在栈上的内存一致
    // 导致后面出现了死循环
    // SinglyLinkedListNode newNode;

    // TODO newNode需要用堆内存去存放
    NodePointer newNode = GetNode();
    newNode->data = e;
    GetTailNode(header)->next = newNode;
#ifdef _LISTDEBUG_
    printf("成功添加节点,数据为:%d\n", newNode->data);
#endif
    return header;
}

NodePointer GetNode()
{
    NodePointer n = (NodePointer)malloc(sizeof(SinglyLinkedListNode));
    n->next = NULL;
    return n;
}

void DestoryList(NodePointer header)
{
    // 判断是否有下一个节点
    if (header->next != NULL)
    {

        // 递归入口
        DestoryList(header->next);
    }
#ifdef _LISTDEBUG_
    printf("成功释放节点,节点存放数据:%d\n", header->data);
#endif
    free(header->next); // 不用担心next指向野指针的问题!
}