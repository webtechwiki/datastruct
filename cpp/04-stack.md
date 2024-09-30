# 栈

## 一、概述

在数据结构中，我们把能实现先进后出（类似于箱子）的数据结构叫做栈。我们可以使用链表或者顺序表来实现栈，实际上栈也是线性表，是受操作限制的线性表，栈的操作是线性表操作的子集。因此，也可以将线性表的结构作为栈的结构。

> 本节，我们使用顺序表来实现栈，也叫做顺序栈。本节，我们暂且不讨论链栈。

## 二、栈的实现过程

### 2.1 栈的结构

我们可以使用一个顺序表表示栈，用一个 pBootom 指针代表栈底位置，用 pTop 指针代表栈顶的位置，初始状态下，栈底和栈顶指向同一个节点。栈的结构如下图所示

![03-01.png](../img/03-01.png)

栈的操作主要包括：压栈、出栈。

### 2.2 栈的定义

根据栈的结构，我们需要定义两种结构体来存储栈信息。首先我们定义一个`src/04_stack/main.cpp`文件，再定义两种结构体，如下代码

```cpp
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
```

### 2.3 栈的初始化

```cpp
void init(PSTACK pS)
{
    pS->pTop = (PNODE)malloc(sizeof(NODE));
    if (NULL == pS->pTop)
    {
        printf("动态内存分配失败\n");
        exit(-1);
    }else {
        pS->pBottom = pS->pTop;
        pS->pTop->pNext = NULL;
    }
}
```

### 2.4 入栈

```cpp
void push(PSTACK pS, int val)
{
    PNODE pNew = (PNODE)malloc(sizeof(NODE));
    pNew->data = val;
    pNew->pNext = pS->pTop; // 新指针指向栈原来的顶端
    pS->pTop = pNew;        // 顶端指针再往上移

    return;
}
```

### 2.5 判断栈是否为空

```cpp
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
```

### 2.6 出栈

```cpp
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
```

### 2.7 遍历

```cpp
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
```

### 2.8 清空

```cpp
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
```

## 三、测试

### 3.1 主函数

最后测试主函数如下

```cpp
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
```

### 3.2 执行结果

最终得出结果如下

```bash
初始元素信息如下:
6 
5 
4 
3 
2 
1 

出栈成功，出栈的元素是6
出栈后元素信息如下:
5 
4 
3 
2 
1 

清空后元素信息如下:
```
