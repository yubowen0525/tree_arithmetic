
//
// Created by ybw on 2020/4/1.
//

#ifndef TREE_ARITHMETIC_HEAP_H
#define TREE_ARITHMETIC_HEAP_H

#include <iostream>
#include <vector>
#include <string.h>
using namespace std;
#define Maxsize 1005
//typedef int ElementType;

/**堆数据结构的三个元素
 *  ElementType* Elements;   //存放堆元素的数组，符合数组构造的完全二叉树特性
    int Size;       //堆大小
    int Capacity;   //堆容量
 */
template <class ElementType>
class heap{
public:
    //这个堆中设计了一个哨兵元素，哨兵是最大的元素值，元素从Element[1]开始存放
    heap()
        :Elements(new ElementType[Maxsize+1]),Size(0),Capacity(Maxsize)
    {
    }

    //判断是否是满
    bool Is_Full()
    {
        return Size == Capacity;
    }
    //判断是否是空
    bool Is_Empty()
    {
        return !Size;
    }


    //层次遍历堆
    friend std::ostream& operator<<(std::ostream& os,heap<ElementType>& res)
    {
        for (int i = 1; i <= res.Size; ++i) {
            os << res.Elements[i] << " ";
        }
        os << std::endl;
        return os;
    }


//     /**
//     * 将vector通过插入的方式转化为堆栈 时间复杂度O(NlogN)
//     * @param res  vector数组
//     * @param h 堆栈
//     */
//     static void Translate_heap(const vector<ElementType>& res,heap* h);

     virtual void Insert(ElementType X) = 0;
    ~heap()
    {
        delete[] Elements;
        Elements = nullptr;
    }

public:
    ElementType* Elements;
    int Size;       //堆大小
    int Capacity;   //堆容量
};

//
// /**
//  * 将vector通过插入的方式转化为堆栈 时间复杂度O(NlogN)
//  * @param res  vector数组
//  * @param h 堆栈
//  */
//void Translate_heap(const vector<ElementType>& res,heap& h);




/**
 * 最大堆
 */
template <class ElementType>
class Max_heap : public heap<ElementType>{
public:

    Max_heap()
    {
        this->Elements[0] = INT32_MAX;    //最大堆的哨兵，应该是最大值
    }
    //插入
    void Insert(ElementType X) override;
    //删除,取顶元素
    ElementType Delete();
    //将数组直接在转化为堆，或者说heap上的数组结构元素，不具备堆特性，一次性直接转化成真正的堆,时间复杂度O(n)
    void Translate_heap(const vector<ElementType>& res);
private:
    void sort(int root);
};

/**
 * 最小堆
 */
 template <class ElementType>
class Min_heap:public heap<ElementType>{
public:
    Min_heap()
    {
        this->Elements[0] = INT32_MIN;    //最小堆的哨兵应该是最小值
    }
    //插入
    void Insert(ElementType X) override;
    //删除,取顶元素
    ElementType Delete();
    //将数组直接在转化为堆，或者说heap上的数组结构元素，不具备堆特性，一次性直接转化成真正的堆,时间复杂度O(n)
    void Translate_heap(const vector<ElementType>& res);

    //给出索引i，从i开始打印根到根节点
    void print_i_to_root(int index)
    {
        for (;  index>0; index/=2) {
            cout<<this->Elements[index];

            if(index != 1)
                cout<<" ";

        }
        cout<<endl;
    }
private:
    void sort(int root);
};







/**
* 将vector通过插入的方式转化为堆栈 时间复杂度O(NlogN)
* @param res  vector数组
* @param h 堆栈
*/
template <class ElementType>
void Translate_heap(const vector<ElementType>& res,heap<ElementType>* h)
{
    for (int re : res) {
        h->Insert(re);
    }
}



#endif //TREE_ARITHMETIC_HEAP_H
