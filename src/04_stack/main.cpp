#include <stdio.h>
#include <stdlib.h>
#include <malloc.h> // 在mac 中使用 #include <sys/malloc.h>， Linux 中使用 #include <malloc.h>

// 定义节点数据类型
typedef struct Node
{
    // 节点数据域
    int data;
    // 节点指针域
    struct Node *pNext;
} NODE, *PNODE; // PNODE等价于 struct NODE *

// 定义栈数据类型
typedef struct Stack
{
    // 栈顶指针
    PNODE pTop;
    // 栈底指针
    PNODE pBottom;
} STACK, *PSTACK; // PSTACK 等价于 struct STACK *

// 栈的初始化
void init(PSTACK pS)
{
    pS->pTop = (PNODE)malloc(sizeof(NODE));
    if (NULL == pS->pTop)
    {
        printf("动态内存分配失败\n");
        exit(-1);
    }
    else
    {
        pS->pBottom = pS->pTop; // 顶部指针和底部指针指向同一个位置
        pS->pTop->pNext = NULL; // pS->pBottom->next = NULL;
    }
}

// 入栈
void push(PSTACK pS, int val)
{
    PNODE pNew = (PNODE)malloc(sizeof(NODE));
    pNew->data = val;
    pNew->pNext = pS->pTop; // 新指针指向栈原来的顶端
    pS->pTop = pNew;        // 顶端指针再往上移

    return;
}

// 判断是否为空
bool empty(PSTACK pS)
{
    if (pS->pTop == pS->pBottom)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// 出栈
bool pop(PSTACK pS, int *pVal)
{
    if (empty(pS))
    {
        return false;
    }
    else
    {
        PNODE r = pS->pTop;
        *pVal = r->data;
        pS->pTop = r->pNext;
        free(r);
        r = NULL;

        return true;
    }
}

// 遍历
void traverse(PSTACK pS)
{
    PNODE p = pS->pTop;
    while (p != pS->pBottom)
    {
        printf("%d \n", p->data);
        p = p->pNext;
    }
    printf("\n");
    return;
}

// 清空
void clear(PSTACK pS)
{
    if (empty(pS))
    {
        return;
    }
    else
    {
        PNODE p = pS->pTop;
        PNODE q = NULL;
        while (p != pS->pBottom)
        {
            q = p->pNext;
            free(p);
            p = q;
        }
        pS->pTop = pS->pBottom;
    }
}

int main(void)
{
    STACK S; // STACK 等价于 struct Stack
    int val;

    init(&S);    //目的是造出一个空栈
    push(&S, 1); //压栈
    push(&S, 2);
    push(&S, 3);
    push(&S, 4);
    push(&S, 5);
    push(&S, 6);
    printf("初始元素信息如下:\n");
    traverse(&S);

    if (pop(&S, &val))
    {
        printf("出栈成功，出栈的元素是%d\n", val);
    }
    else
    {
        printf("出栈失败!\n");
    }

    printf("出栈后元素信息如下:\n");
    traverse(&S);

    clear(&S);
    printf("清空后元素信息如下:\n");
    traverse(&S);

    return 0;
}