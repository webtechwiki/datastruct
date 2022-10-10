#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

// 定义链表节点
typedef struct Node
{
    int data;           // 数据域
    struct Node *pNext; // 指针域
} NODE, *PNODE;         // NODE 等价于 struct Node, *PNODE 等价于* Node

// 创建一个非循环的单链表
PNODE create_list(void)
{
    int len; // 存放节点的有效个数
    int val; //存放用户输入的临时存入的节点的值

    // 分配一个不存在任何数据的头节点
    PNODE pHead = (PNODE)malloc(sizeof(NODE));
    if (NULL == pHead)
    {
        printf("内存分配失败!\n");
        exit(-1);
    }

    // 初始状态下，链表尾节点和头节点指向同一个内存（即头节点就是尾节点），而指针域为NULL
    PNODE pTail = pHead;
    pTail->pNext = NULL;

    printf("请输入您需要生成的链表节点的个数：len=");
    scanf("%d", &len);

    for (int i = 0; i < len; i++)
    {
        printf("请输入第%d个节点的值:", i + 1);
        scanf("%d", &val);

        PNODE pNew = (PNODE)malloc(sizeof(NODE));
        if (NULL == pNew)
        {
            printf("分配失败，程序终止！\n");
            exit(-1);
        }

        // 分配成功，给新节点赋值
        pNew->data = val;
        // 让链表尾节指针域点指向最新的节点，实现增加新节点
        pTail->pNext = pNew;
        // 新节点的指针域为NULL
        pNew->pNext = NULL;

        // 最后，再让尾节点指向新节点。
        pTail = pNew;
    }

    // 链表创建完成后，返回头节点
    return pHead;
}

// 遍历链表
void traverse_list(PNODE pHead)
{
    // 把第一个节点赋给变量p
    PNODE p = pHead->pNext;

    while (NULL != p)
    {
        // p 不为NULL,代表有数据，则输出p的数据于
        printf("%d  ", p->data);
        // 输出p的数据域之后，让p指向下一个节点
        p = p->pNext;
    }
    printf("\n");
    return;
}

// 判断链表是否为空
bool is_empty(PNODE pHead)
{
    if (NULL == pHead->pNext)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// 计算链表的长度
int length_list(PNODE pHead)
{
    PNODE p = pHead->pNext;
    int len = 0;
    while (NULL != p)
    {
        ++len;
        p = p->pNext;
    }
    return len;
}

// 链表排序
void sort_list(PNODE pHead)
{
    int i, j, t;
    int len = length_list(pHead);
    // 定义p和q两个节点变量，用于临时存放交换节点
    PNODE p, q;

    // 让p指向当前节点
    for (i = 0, p = pHead->pNext; i < len - 1; i++, p = p->pNext)
    {
        // 让q指向当前节点的下一个节点
        for (j = i + 1, q = p->pNext; j < len; j++, q = q->pNext)
        {
            // 用当前节点和下一个节点进行对比，如果当前节点的数据域大于下一个节点，就将数据进行交换
            if (p->data > q->data)
            {
                t = p->data;
                p->data = q->data;
                q->data = t;
            }
        }
    }
}

// 插入节点
bool insert_list(PNODE pHead, int position, int val)
{
    int len = length_list(pHead);
    if (len < 0 || position > len)
    {
        return false;
    }

    int i = 0;
    PNODE p = pHead;
    // 使用while循环，使p变量指向position节点的前一个节点
    while (NULL != p->pNext && i < position)
    {
        p = p->pNext;
        ++i;
    }

    // 程序执行到这里，p已经指向position节点的前一个节点，position节点是否为空无所谓

    // 插入过程1：分配新节点
    PNODE pNew = (PNODE)malloc(sizeof(NODE));
    if (NULL == pNew)
    {
        printf("动态分配内存失败失败");
        exit(-1);
    }
    // 插入过程2：将传入的值赋给新节点的数据域
    pNew->data = val;

    // 插入过程3：用变量q临时存储position节点
    PNODE q = p->pNext;
    // 插入过程4：将position节点的前一个节点指向新节点
    p->pNext = pNew;
    // 插入过程5：再将新节点指向posion节点
    pNew->pNext = q;

    return true;
}

// 删除节点
bool delete_list(PNODE pHead, int position, int *pVal)
{
    int len = length_list(pHead);
    if (len < 0 || position > len)
    {
        return false;
    }

    int i = 0;
    PNODE p = pHead;

    // 使用while循环，使p变量指向position节点的前一个节点
    while (NULL != p->pNext && i < position)
    {
        p = p->pNext;
        ++i;
    }

    // 如果position节点为NULL，返回false
    if (NULL == p->pNext)
    {
        return false;
    }

    // 程序执行到这里，p已经指向position节点的前一个节点，并且position节点是存在的
    // 删除过程1，让q变量指向position节点
    PNODE q = p->pNext;
    // 删除过程2，将position节点的数据赋给pVal
    *pVal = q->data;

    // 删除过程3，让position节点的前一个节点指向position节点的下一个
    p->pNext = p->pNext->pNext;

    // 删除过程4，释放position节点指向的内存，并让q变量指向NULL
    free(q);
    q = NULL;

    return true;
}

int main()
{
    // 创建链表，定义长度为6，输入1、5、6、4、3、2
    PNODE pHead = create_list();

    // 遍历元素：输出 1 5 6 4 3 2
    traverse_list(pHead);

    // 链表排序
    sort_list(pHead);
    // 遍历元素：输出 1 2 3 4 5 6
    traverse_list(pHead);

    // 在索引为0的位置添加元素7
    insert_list(pHead, 0, 7);
    // 遍历元素：输出 7 1 2 3 4 5 6
    traverse_list(pHead);

    // 在索引为5的位置删除元素，并输出删除的元素
    int val;
    delete_list(pHead, 5, &val);
    // 遍历元素，输出：
    traverse_list(pHead);
    // 打印删除的元素
    printf("被删除的元素数据域是%d\n", val);

    return 0;
}