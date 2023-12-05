#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define ElemType int

typedef struct
{
    ElemType *data; //
    int length;     //
    int maxSize;    //
} Sequential_List;
Sequential_List GetList(int maxSize);                         //
void DestoryList(Sequential_List *SqList);                    //
bool ListInsert(Sequential_List *SqList, int i, ElemType e);  //
bool ListAdd(Sequential_List *SqList, ElemType e);            //
int LocateElem(Sequential_List *sqList, ElemType e);          //
bool ListDelete(Sequential_List *sqlist, int i, ElemType *e); //
void traverseList(Sequential_List *sqlist);                   // 遍历
ElemType GetElem(Sequential_List *sqlist, int i);             // 获取第i位置的元素
int Length(Sequential_List *sqlist);
bool Empty(Sequential_List *sqlist);

//-------------------TEST---------------------------

int main(int argc, char const *argv[])
{
    //
    Sequential_List s = GetSqList(10);

    //-----------------
    for (size_t i = 0; i < 5; i++)
    {
        ListAdd(&s, i);
    }

    ListInsert(&s, 7, 2324);
    printf("%d\n", LocateElem(&s, 2324));

    traverseList(&s);
    int returnData;
    ListDelete(&s, 15, &returnData);
    traverseList(&s);

    //---------------
    DestorySqlList(&s);
    return 0;
}
//-------------------END----------------------------
bool Empty(Sequential_List *sqlist)
{
    if (sqlist->length == 0)
    {
        return true;
    }
    return false;
}

int Length(Sequential_List *sqlist)
{
    return sqlist->length;
}
void GetElem(Sequential_List *sqlist, int i, ElemType *e)
{
    if (i > sqlist->length || i <= 0)
    {
        e = NULL;
        return;
    }
    e = sqlist->data[i - 1];
}

void traverseList(Sequential_List *sqlist)
{
    printf("----------开始遍历-----------\n");
    for (size_t i = 0; i < sqlist->length; i++)
    {
        printf("第 %d 个元素: %d\n", i, sqlist->data[i]);
        /* code */
    }
    printf("----------结束遍历-----------\n");
}

bool ListDelete(Sequential_List *sqlist, int i, ElemType *e)
{
    int length = sqlist->length;
    ElemType *data = sqlist->data;
    int maxSize = sqlist->maxSize;
    if (i > length || i <= 0)
    {
        e = NULL;
        return true;
    }
    *e = data[i - 1];
    for (size_t i1 = i - 1; i1 < length; i1++)
    {
        if (i1 == length - 1)
        {
            break;
        }
        data[i1] = data[i1 + 1]; // i+1
    }

    sqlist->length = length - 1;
    return true;
}

int LocateElem(Sequential_List *SqList, ElemType e)
{
    int length = SqList->length;
    ElemType *data = SqList->data;
    int maxSize = SqList->maxSize;
    for (size_t i = 0; i < length; i++)
    {
        if (data[i] == e)
        {
            return i;
        }
    }
    return -1;
}
bool ListAdd(Sequential_List *SqList, ElemType e)
{
    if (SqList->data == NULL || (SqList->length) + 1 > SqList->maxSize) // ȷ���Ϸ�
    {
        return false;
        /* code */
    }
    int length = SqList->length;
    ElemType *data = SqList->data;
    int maxSize = SqList->maxSize;

    data[length] = e;

    SqList->length = SqList->length + 1;
    return true;
}

bool ListInsert(Sequential_List *SqList, int i, ElemType e)
{
    if (SqList->data == NULL || i > SqList->maxSize || (SqList->length) + 1 > SqList->maxSize) // ȷ���Ϸ�
    {
        return false;
        /* code */
    }

    if (i > SqList->length)
    {
        (SqList->data)[i - 1] = e;
        (SqList->length) = i;
        return true;
    }

    for (size_t i1 = (SqList->length) - 1; i1 >= i - 1; i1--)
    {
        (SqList->data)[i1 + 1] = (SqList->data)[i1];
        /* code */
    }
    (SqList->data)[i - 1] = e;
    SqList->length = SqList->length + 1;
    return true;
}
void DestoryList(Sequential_List *SqList)
{
    free(SqList->data);
    SqList->length = 0;
    SqList->maxSize = 0;
}

Sequential_List GetList(int maxSize)
{
    Sequential_List Sqlist;
    Sqlist.data = (ElemType *)malloc(sizeof(ElemType) * maxSize);
    if (Sqlist.data == NULL)
    {
        printf("内存不足!");
        exit(EXIT_FAILURE);
    }
    Sqlist.length = 0;
    Sqlist.maxSize = maxSize;
    return Sqlist;
}