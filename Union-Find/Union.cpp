//
// Created by ybw on 2020/4/3.
//

#include "Union.h"

int Union::Find(ElementType X)
{
    int i = 0;
    while (i < Size && X != data[i].value)
        ++i;
    //没有找到X元素
    if(i == Size)
        return -1;

    //若Parent不按照约定根节点是负数，可能造成死循环
    while(data[i].parent >= 0)
        i = data[i].parent;

    return i;
}

/**
 * 将元素X2挂在X1下面
 * @param X1
 * @param X2
 * @return
 */
int Union::union_value(ElementType X1,ElementType X2)
{
    int Parent1 = Find(X1);
    int Parent2 = Find(X2);

    if(Parent1 != Parent2) //说明并不是一个集合
     data[Parent2].parent = Parent1;

}