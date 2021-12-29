#include <stdio.h>
#include <stdlib.h>
#include <sys/malloc.h> // 在mac 中使用 #include <sys/malloc.h>， Linux 中使用 #include <malloc.h>

// 定义节点数据类型
typedef struct Node
{
    // 节点数据域
    int data;
    // 节点指针域
    struct Node *pNext;
} NODE, *PNODE; // PNODE等价于 struct NODE *

typedef struct Stack
{
    // 栈顶指针
    PNODE pTop;
    // 栈底指针
    PNODE pBottom;
} STACK, *PSTACK; // PSTACK 等价于 struct STACK *