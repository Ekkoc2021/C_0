#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define _DLDEBUG_
#define ElemType int
typedef struct DLNode
{
    ElemType data;
    struct DLNode *next, *prior;
} DoublyLinedListNode, *DNodePointer;

void traverseList(DNodePointer header, char *(*DataToString)(ElemType e, char *buff), char *buff); // v
void reverseTraverseList(DNodePointer header, char *(*DataToString)(ElemType e, char *buff), char *buff);
DNodePointer GetNode();                                        // v
DNodePointer List_HeadInsert(DNodePointer header, ElemType e); // v
void DestoryList(DNodePointer header);                         // v
bool ListInsert(DNodePointer header, int i, ElemType e);       // v
bool ListAdd(DNodePointer header, ElemType e);                 // v
int LocateElem(DNodePointer header, ElemType e);               // v
bool ListDelete(DNodePointer header, int i, ElemType *e);      // v

void reverseList(DNodePointer header);         // v
ElemType GetElem(DNodePointer header, int i);  // v
int Length(DNodePointer header);               // v
bool Empty(DNodePointer header);               // v
DNodePointer GetTailNode(DNodePointer header); // v

//-----------------TEST----------------------

#ifdef _DLDEBUG_
char *MyToString(ElemType e, char *buff)
{
    return itoa(e, buff, 10);
}
int main(int argc, char const *argv[])
{
    // 10 ^ 01 = 11
    // 11 ^ 10=01
    // 11 ^ 01=10
    int a = 3;
    int b = 5;
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;

    printf("开始测试,a=%d,b=%d\n", a, b);
    DNodePointer header = GetNode();
    printf("指针的长度:%d,long long的长度:%d\n", sizeof(header), sizeof(long long int));
    char buff[20];
    //---测试-----
    for (size_t i = 0; i < 10; i++)
    {

        List_HeadInsert(header, i + 10);
    }
    ListInsert(header, 2, 99);
    for (size_t i = 0; i < 5; i++)
    {
        ListAdd(header, i + 80);
    }
    ElemType temp;
    printf("%d\n", LocateElem(header, 99));
    ListDelete(header, 0, &temp);
    printf("删除的节点%d\n", temp);

    traverseList(header, &MyToString, buff);
    reverseList(header);
    reverseTraverseList(header, &MyToString, buff);
    //------
    DestoryList(header);

    return 0;
}
#endif

//---------------------TEST--------------------
DNodePointer GetNode()
{
    DNodePointer new = malloc(sizeof(DoublyLinedListNode));
    new->next = NULL;
    new->prior = NULL;
    return new;
}
DNodePointer List_HeadInsert(DNodePointer header, ElemType e)
{
    DNodePointer new = GetNode();
    new->data = e;
    if (header->next != NULL)
    {
        new->next = header->next;
        header->next->prior = new;
    }

    header->next = new;
    new->prior = header;
    return new;
}

void DestoryList(DNodePointer header)
{
    if (header->next != NULL)
    {
        DestoryList(header->next);
    }
#ifdef _DLDEBUG_
    printf("准备释放节点%d", header->data);
#endif
    free(header);
#ifdef _DLDEBUG_
    printf("=====>成功释放 \n");
#endif
}

void traverseList(DNodePointer header, char *(*DataToString)(ElemType e, char *buff), char *buff)
{
    // header 头节点
    // dataToString 遍历函数
    // 缓冲区==>由数据大小去决定缓冲大小,用户决定
    int index = 1;
    while ((header = header->next) != NULL)
    {
        printf("第%d个数据:%s\n", index, (*DataToString)(header->data, buff));
        index++;
    }
}

bool ListInsert(DNodePointer header, int i, ElemType e)
{

    // i<1
    if (i <= 0)
    {
        return true;
    }
    // 无论是双链表在操作定位的时候
    // 定位到前一个节点思路一定不会错,也会留有很多操作的余地
    // 定位到前一个节点
    for (size_t i1 = 0; i1 < i - 1; i1++)
    {
        // 找到第i个节点
        if (header->next == NULL)
        {
            header->next = GetNode();
            header->next->prior = header;
        }
        header = header->next;
    }
    DNodePointer new = GetNode();
    new->data = e;
    // 在第i个节点的前面添加一个节点,定位后的header节点后加一个节点
    if (header->next == NULL)
    {
        header->next = new;
        new->prior = header;
        return true;
    }

    // 这里从第i个节点去进行操作,所以获取到第i个节点
    header = header->next;

    header->prior->next = new;
    new->next = header;
    new->prior = header->prior;
    header->prior = new;
    return true;
}

bool ListAdd(DNodePointer header, ElemType e)
{

    // 寻找到最后一个节点的
    while (1)
    {
        if (header->next == NULL)
        {
            break;
        }
        header = header->next;
    }

    // 添加节点
    DNodePointer new = GetNode();
    new->data = e;

    header->next = new;
    new->prior = header;
    return true;
}
void reverseTraverseList(DNodePointer header, char *(*DataToString)(ElemType e, char *buff), char *buff)
{
    DNodePointer tailPointer = GetTailNode(header);
    while (1)
    {
        if (tailPointer == header)
        {
            return;
        }
        printf("节点数值:%d\n", tailPointer->data);
        tailPointer = tailPointer->prior;
    }
}
DNodePointer GetTailNode(DNodePointer header)
{
    while (1)
    {
        if (header->next == NULL)
        {
            return header;
        }
        header = header->next;
    }
}

int LocateElem(DNodePointer header, ElemType e)
{

    int index = 0;
    while ((header = header->next) != NULL)
    {
        if (header->data == e)
        {
            return index;
        }
        index++;
    }
    return -1;
}

// 删除索引为i节点,将删除的节点的数据放入指定位置
bool ListDelete(DNodePointer header, int i, ElemType *e)
{
    for (size_t i1 = 0; i1 < i + 1; i1++)
    {
        header = header->next;
        if (header == NULL)
        {
            return false;
        }
    }
    *e = header->data;
    header->prior->next = header->next;
    if (header->next != NULL)
    {
        header->next->prior = header->prior;
    }
#ifdef _DLDEBUG_
    printf("释放数据为:%d的节点\n", header->data);
#endif
    free(header);
    return true;
}
void reverseList(DNodePointer header)
{
    // | h |==> | n |==>| n |
    // | h |<== | n |<==| n |

    // step 1
    // | h |==> | n |<==| n |
    // | h |<== | n |==>| n |

    // step 2
    // | n |<==| n |<==| h |
    // | n |==>| n |==>| h |
    DNodePointer tempHeader = header; // 记录header

    // todo 看起来好像没有什么毛病==>无法保证指针的长度为8字节
    // 用一个中间变量完成交换工作才是一劳永逸
    // DNodePointer temp;
    while (1)
    {
        // 交换两个指针的值==> 用^操作
        header->next = (DNodePointer)((long long int)(header->next) ^ (long long int)(header->prior));
        header->prior = (DNodePointer)((long long int)(header->next) ^ (long long int)(header->prior));
        header->next = (DNodePointer)((long long int)(header->next) ^ (long long int)(header->prior));
        if (header->prior == NULL)
        {
            break;
        }
        header = header->prior;
    }
    // 现在所有的指针指针位置都已经交换位置,断开原先的头节点和首节点
    tempHeader->prior->next = NULL;

    // 现在的header是原来的尾节点
    tempHeader->next = header;  // tempheader的下一个指向原来的尾巴节点
    header->prior = tempHeader; // 原来的未节点的前驱指向tempHeader
    tempHeader->prior = NULL;   // 将 tempHeader的前驱节点设置为NULL
}

ElemType GetElem(DNodePointer header, int i)
{
    for (size_t i1 = 0; i1 < i + 1; i1++)
    {
        header = header->next;
        if (header == NULL)
        {
            return -1111111;
        }
    }
    return header->data;
}
int Length(DNodePointer header)
{
    int length = 0;
    while (1)
    {
        if (header->next == NULL)
        {
            return length;
        }
        header = header->next;
        length++;
    }
}
bool Empty(DNodePointer header)
{
    if (header->next == NULL)
    {
        return true;
    }
    return false;
}