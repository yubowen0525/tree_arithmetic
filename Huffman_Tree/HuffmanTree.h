//
// Created by ybw on 2020/4/2.
//

#ifndef TREE_ARITHMETIC_HUFFMANTREE_H
#define TREE_ARITHMETIC_HUFFMANTREE_H
//#define DEBUG

#include "heap.h"
#include <memory>


typedef shared_ptr<struct Huffman_Node> Huffman_Tree;

struct Huffman_Node{
    int Weight;
    Huffman_Tree Left;
    Huffman_Tree Right;
};

//template <class ElementType>
class Min_heap_H : public heap<Huffman_Tree>
{
public:
    typedef Huffman_Tree ElementType;

    friend ostream& operator<<(ostream& os,Min_heap_H& res)
    {
        for (int i = 1; i <= res.Size; ++i) {
            os<<res.Elements[i]->Weight<<" ";
        }
        return os;
    }

    Min_heap_H()
    {
        Huffman_Tree head = make_shared<Huffman_Node>();
        this->Elements[0] = head;
        this->Elements[0]->Weight = INT32_MIN;    //最小堆的哨兵应该是最小值
    }
    //插入
    void Insert(ElementType X) override;
    //删除,取顶元素
    ElementType Delete();
    //将数组直接在转化为堆，或者说heap上的数组结构元素，不具备堆特性，一次性直接转化成真正的堆,时间复杂度O(n)
    void Translate_heap(const vector<int>& res);
private:
    void sort(int root);
};

extern void PreorderTraversal(const Huffman_Tree& T);

class HuffmanTree{
public:
     HuffmanTree(const vector<int>& res)
        :MinHeap(new Min_heap_H()),
         Huff(HuffmanTreeBuild(res))
    {

    }

    friend void PreorderTraversal(HuffmanTree& T)
    {
        PreorderTraversal(T.Huff);
    }


    /**哈夫曼树的建造
     * 1 建立堆栈，将堆栈中数组的每个指针 = Huffman节点, 每个节点赋值
     * 2 做Size - 1 次合并
     * 每次新建一个节点 从堆中取出两个最小元素，放在T的左右，再权值相加，重新放回堆栈中
     */
    Huffman_Tree HuffmanTreeBuild(const vector<int>& res)
    {
        //1.将数组赋值给Huff节点的权值，赋值给最小堆,然后初始化最小堆特性
        MinHeap->Translate_heap(res);
#ifdef DEBUG
        cout<<*MinHeap<<endl;
#endif
        //2
        Huffman_Tree T;
        int times = MinHeap->Size - 1; //合并次数是最小堆大小减1
        for (int i = 1; i <= times; ++i) {
            T = make_shared<Huffman_Node>();    //创建一个新节点
            T->Left = MinHeap->Delete();    //从堆中拿出2个最小权值节点
            T->Right = MinHeap->Delete();
#ifdef DEBUG
            cout<<*MinHeap<<endl;
#endif
            T->Weight = T->Left->Weight + T->Right->Weight; //赋值新节点的权值
            MinHeap->Insert(T); //把该节点扔回堆栈排序
#ifdef DEBUG
            cout<<*MinHeap<<endl;
#endif
        }
        T = MinHeap->Delete();  //取出堆中的最后一个节点，也就是头节点
        return T;
    }

    int WPL(Huffman_Tree Huff,int depth) {
        // 如果是叶结点，返回编码长度
        if (Huff->Left == NULL && Huff->Right == NULL)
            return depth * Huff->Weight;
        else  // 否则返回其左右子结点的编码长度
            return (WPL(Huff->Left, depth + 1) + WPL(Huff->Right, depth + 1));
    }



    ~HuffmanTree()
    {
        delete MinHeap;
        MinHeap = nullptr;
        Huff = nullptr;
    }

public:
    Min_heap_H* MinHeap;
    Huffman_Tree Huff;
};

void PreorderTraversal(const Huffman_Tree& T);


#endif //TREE_ARITHMETIC_HUFFMANTREE_H
