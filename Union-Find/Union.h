//
// Created by ybw on 2020/4/3.
//

#ifndef TREE_ARITHMETIC_UNION_H
#define TREE_ARITHMETIC_UNION_H

typedef int ElementType;
#define Maxsize 100
typedef struct SetType SetTypeP;
struct SetType
{
    ElementType value;
    int parent;
};

class Union {
public:
    Union()
        :data(new SetType[Maxsize]),Size(0),Capacity(Maxsize)
    {
        for (int i = 0; i < Maxsize; ++i) {
            data[i].value = i+1;
            data[i].parent = -1;
            ++Size;
        }
    }

    //查找父节点的索引
    int Find(ElementType X);
    //将两个元素合并成一个集合
    int union_value(ElementType X1,ElementType X2);


    bool Is_full()
    {
        return Size == Capacity;
    }

    bool Is_empty()
    {
        return !Size;
    }

    int size(){
        return Size;
    }

    ~Union(){
        delete[] data;
        data = nullptr;
    }

public:
    SetTypeP* data;
    int Size;
    int Capacity;
};


#endif //TREE_ARITHMETIC_UNION_H
