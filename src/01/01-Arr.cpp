#include <stdio.h>
#include <sys/malloc.h> // windows中用 #include <malloc.h>
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