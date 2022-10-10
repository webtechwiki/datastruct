# 线性离散存储-链表

## 一、概述

在数据结构中，我们研究的对象就是数据，其次是研究操作数据的方法与步骤。

连续存储实际上就是连续的存储结构，我们可以理解数组就是连续存储的实现。接下来我们通过 C 语言的`struct`，定义连续存储这种数据结构体，这里我们把它叫做数组，并研究其基本的算法。

连续存储结构容易实现元素的追和读取线性表中的第 i 个元素的操作；但在实现插入、删除操作时，需要移动大量元素。所以，它适合存储相对稳定的线性表，如职工工资表、学生学籍表。

## 二、连续存储的数据结构与基本算法

### 2.1 定义数组

首先我们定义一个`src/02_sqlist/main.cpp`文件，需要引入基本的 c 语言头文件，如下代码

```c
# include <stdio.h> // 标准io头部，包含printf函数
# include <malloc.h> // 包含malloc函数，在mac OS上，改为sys/malloc.h
# include <stdlib.h> // 包含exit函数
```

接下来我们定义数组的结构体，该数据类型包含三个成员，pBase、len、cnt，如下代码

```c
struct Arr
{
    int *pBase; // 存储的是数组第一个元素的地址
    int len;    // 数组所能容纳的最大元素个数
    int cnt;    // 当前数组有效元素个数
};
```

### 2.2 初始化数组

接下来我们定义初始化数组的函数，根据数组长度动态分配内存，用于存储对应的数组元素，如下代码

```c
void init_arr(struct Arr *pArr, int length)
{
    // 根据数组的长度，分配的内存pBase
    pArr->pBase = (int *)malloc(sizeof(int) * length);
    if (NULL == pArr->pBase)
    {
        printf("动态分配内存失败");
        exit(-1);
    }
    // 内存分配成功
    pArr->len = length;
    pArr->cnt = 0;
    return;
}
```

### 2.3 判定数组是否为空或是否已满

我们可以根据当前数组的有效元素和数组总元素判定数组是否为空或者是否已满，定义以下两个函数

```c
// 判断数组是否为空
bool is_empty(struct Arr *pArr)
{
    // 数组的有效个数为0，即数组为空
    if (0 == pArr->cnt)
    {
        return true;
    }
    // 否则，数组不为空
    else
    {
        return false;
    }
}
// 判断数组是否已满
bool is_full(struct Arr *pArr)
{
    // 数组的有效个数为数组的长度，即数组已满
    if (pArr->cnt == pArr->len)
    {
        return true;
    }
    // 否则，数组未满
    else
    {
        return false;
    }
}
```

### 2.4 遍历数组元素

遍历数组的目的是把每一个有效的数组元素打印到终端。根据数组的当前有效个数，遍历并打印每个元素，我们定义如下代码

```c
void traverse_arr(struct Arr *pArr)
{
    for (int i = 0; i < pArr->cnt; i++)
    {
        printf("%d\t", pArr->pBase[i]);
    }
    printf("\n");
}
```

### 2.5 追加数组元素

追加即在未满的数组中，在末尾添加元素，如下代码

```c
bool append_arr(struct Arr *pArr, int val)
{
    // 数组已满则返回false
    if (is_full(pArr))
    {
        return false;
    }
    // 数组不满时进行追加
    pArr->pBase[pArr->cnt] = val;
    (pArr->cnt)++;
    return true;
}
```

### 2.6 插入元素

数组除了追加，还有数组插入操作，插入即在特定的位置添加数据，如下代码

```c
bool insert_arr(struct Arr *pArr, int pos, int val)
{
    // 如果数组元素已满，返回false
    if (is_full(pArr))
    {
        return false;
    }
    // 如果要插入的位置不对，返回false
    if (pos < 0 || pos > pArr->cnt)
    {
        return false;
    }
    // 从最后一个元素的位置开始，到要插入的位置，挨个将数组元素往后移一位
    for (int i = pArr->cnt - 1; i >= pos; --i)
    {
        pArr->pBase[i + 1] = pArr->pBase[i];
    }
    // 将插入的值，赋在指定的位置
    pArr->pBase[pos] = val;
    // 标记数组有效元素的字段加1
    (pArr->cnt)++;
    return true;
}
```

### 2.7 删除元素

删除操作和插入操作类似，区别是：插入数据时，从插入位置开始，后面的数据往后移，并在插入的位置加入元素；删除数据时，我们需要在删除位置的后一位开始，后面的数据都往前移，删除位置的数据会被覆盖，如下代码

```c
bool delete_arr(struct Arr *pArr, int pos, int *pVal)
{
    // 如果数组元素已满，返回false
    if (is_full(pArr))
    {
        return false;
    }
    // 如果要插入的位置不对，返回false
    if (pos < 0 || pos > pArr->cnt)
    {
        return false;
    }
    // 将删除的元素的值赋给传进来的指针变量
    *pVal = pArr->pBase[pos];
    // 从到要删除的位置开始，一直到最后一个位置，将数组元素挨个往前移动
    for (int i = pos; i < pArr->cnt; ++i)
    {
        pArr->pBase[i] = pArr->pBase[i + 1];
    }
    pArr->cnt--;
    return true;
}
```

### 2.8 数组倒置

数组倒置的操作是将数组的第 1 位和最后 1 位元素进行替换，第 2 位和倒数第 2 位元素进行替换，依此类推。最终完成倒置，如下代码

```c
void inverse_arr(struct Arr *pArr)
{
    int i = 0;
    int j = pArr->cnt - 1;
    int t;
    while (i < j)
    {
        t = pArr->pBase[i];
        pArr->pBase[i] = pArr->pBase[j];
        pArr->pBase[j] = t;
        ++i;
        --j;
    }
    return;
}
```

### 2.9 数组排序

接下来是一个简单的排序过程，函数中有两层循环。第一层循环，选择当前位置的元素（从索引为 0 的位置开始，即未循环前，当前位置是第 1 个元素），在第二层循环中，从当前位置的元素的下一个元素开始，直到最后一个元素，挨个与当前位置的元素进行大小对比，每次对比都把小的元素替换到当前位置。

第 1 轮循环结束后，索引为 0 的位置将是最小的元素，第 2 轮循环结束后，索引为 1 的位置将是次小的元素，依此类推。最终，数组元素将按从小到大的顺序排列，如下代码

```c
void sort_arr(struct Arr *pArr)
{
    int i, j, t;
    for (i = 0; i < pArr->cnt; i++)
    {
        for (j = i + 1; j < pArr->cnt; j++)
        {
            if (pArr->pBase[i] > pArr->pBase[j])
            {
                t = pArr->pBase[i];
                pArr->pBase[i] = pArr->pBase[j];
                pArr->pBase[j] = t;
            }
        }
    }
}
```

## 三、测试与验证

最终所有测试代码如下

```c
#include <stdio.h>
#include <malloc.h> // mac OS中用 #include <sys/malloc.h>
#include <stdlib.h>

// 定义数组结构体
struct Arr
{
    int *pBase; // 存储的是数组第一个元素的地址
    int len;    // 数组所能容纳的最大元素个数
    int cnt;    // 当前数组有效元素个数
};

// 初始化数组
void init_arr(struct Arr *pArr, int length)
{
    // 将分配的内存赋给pBase
    pArr->pBase = (int *)malloc(sizeof(int) * length);
    if (NULL == pArr->pBase)
    {
        printf("动态分配内存失败");
        exit(-1);
    }
    // 内存分配成功
    pArr->len = length;
    pArr->cnt = 0;
    return;
}

// 判断数组是否为空
bool is_empty(struct Arr *pArr)
{
    // 数组的有效个数为0，即数组为空
    if (0 == pArr->cnt)
    {
        return true;
    }
    // 否则，数组不为空
    else
    {
        return false;
    }
}

// 判断数组元素是否已满
bool is_full(struct Arr *pArr)
{
    // 数组的有效个数为数组的长度，即数组已满
    if (pArr->cnt == pArr->len)
    {
        return true;
    }
    // 否则，数组未满
    else
    {
        return false;
    }
}

// 遍历数组
void traverse_arr(struct Arr *pArr)
{
    for (int i = 0; i < pArr->cnt; i++)
    {
        printf("%d\t", pArr->pBase[i]);
    }
    printf("\n");
}

// 追加数组（元素）
bool append_arr(struct Arr *pArr, int val)
{
    // 数组满是返回false
    if (is_full(pArr))
    {
        return false;
    }
    // 数组不满时追加
    pArr->pBase[pArr->cnt] = val;
    (pArr->cnt)++;
    return true;
}

// 插入数组（元素）
bool insert_arr(struct Arr *pArr, int pos, int val)
{
    // 如果数组元素已满，返回false
    if (is_full(pArr))
    {
        return false;
    }
    // 如果要插入的位置不对，返回false
    if (pos < 0 || pos > pArr->cnt)
    {
        return false;
    }
    // 从最后一个元素的位置开始，到要插入的位置，挨个将数组元素往后移一位
    for (int i = pArr->cnt - 1; i >= pos; --i)
    {
        pArr->pBase[i + 1] = pArr->pBase[i];
    }
    // 将插入的值，赋在指定的位置
    pArr->pBase[pos] = val;
    // 标记数组有效元素的字段加1
    (pArr->cnt)++;
    return true;
}

// 删除数组（元素）
bool delete_arr(struct Arr *pArr, int pos, int *pVal)
{
    // 如果数组元素已满，返回false
    if (is_full(pArr))
    {
        return false;
    }
    // 如果要插入的位置不对，返回false
    if (pos < 0 || pos > pArr->cnt)
    {
        return false;
    }
    // 将删除的元素的值赋给传进来的指针变量
    *pVal = pArr->pBase[pos];
    // 从到要删除的位置开始，一直到最后一个位置，将数组元素挨个往前移动
    for (int i = pos; i < pArr->cnt; ++i)
    {
        pArr->pBase[i] = pArr->pBase[i + 1];
    }
    pArr->cnt--;
    return true;
}

// 倒置数组（元素）
void inverse_arr(struct Arr *pArr)
{
    int i = 0;
    int j = pArr->cnt - 1;
    int t;
    while (i < j)
    {
        t = pArr->pBase[i];
        pArr->pBase[i] = pArr->pBase[j];
        pArr->pBase[j] = t;
        ++i;
        --j;
    }
    return;
}

// 数组排序
void sort_arr(struct Arr *pArr)
{
    int i, j, t;
    for (i = 0; i < pArr->cnt; i++)
    {
        for (j = i + 1; j < pArr->cnt; j++)
        {
            if (pArr->pBase[i] > pArr->pBase[j])
            {
                t = pArr->pBase[i];
                pArr->pBase[i] = pArr->pBase[j];
                pArr->pBase[j] = t;
            }
        }
    }
}

// 主函数测试
int main()
{
    struct Arr arr;
    // 初始化长度为6的数组
    init_arr(&arr, 6);

    // 追加元素
    append_arr(&arr, 1);
    append_arr(&arr, 2);
    append_arr(&arr, 3);
    append_arr(&arr, 4);

    traverse_arr(&arr); // 输出结果为 1 2 3 4

    // 在索引为0的位置插入6
    insert_arr(&arr, 0, 5);
    traverse_arr(&arr); // 输出结果为 5 1 2 3 4

    // 在索引为0的位置删除元素
    int delval; // 用于接收删除的元素
    delete_arr(&arr, 0, &delval);
    traverse_arr(&arr); // 输出结果为 1 2 3 4

    // 数组倒置
    inverse_arr(&arr);
    traverse_arr(&arr); // 输出结果为 4 3 2 1

    // 数组排序
    sort_arr(&arr);
    traverse_arr(&arr); // 输出结果为 1 2 3 4

    return 0;
}
```

> 本文原创首发自 wx 订阅号：**极客开发中**，禁止转载
