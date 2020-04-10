//
// Created by ybw on 2020/4/2.
//

#include "HuffmanTree.h"
/**
 * 首先若在完全二叉树插入元素，一定是数组的后面一个位置。从下往上跟根节点进行比较，根节点小，则根节点赋值子节点。
 * @param X
 *
 */
void Min_heap_H::Insert(ElementType X)
{
    if(this->Is_Full()) {
        std::cout<<"堆空间已经满了"<<std::endl;
        return;
    }
    //添加新元素，当前数组的下一个元素，维护堆特性。
    int i = ++(this->Size);
    //结束条件，i/2 = 0 时，会跟哨兵元素进行比较，但是哨兵为int最小值，所以退出。
    for (; this->Elements[i/2]->Weight > X->Weight; i/=2) {
        this->Elements[i] = this->Elements[i/2];
    }
    this->Elements[i] = X;
}

/**
 *删除头节点，把数组最后一个元素来填充，自上而下维护堆特性。
 * @return
 */
Min_heap_H::ElementType Min_heap_H::Delete()
{
    if(this->Is_Empty()){
        std::cout<<"堆为空，无法删除!"<<std::endl;
        return nullptr;
    }
    //取出堆最小值
    ElementType Min = this->Elements[1];
    //取出最后一个元素，维护堆特性
    ElementType temp = this->Elements[this->Size--];
    //给temp在堆中找位子,考虑循环结束条件：父节点是否有左孩子
    int Parent,Child;
    for (Parent = 1; Parent*2 <= this->Size; Parent = Child) {
        Child = Parent*2; //此时为左孩子节点
        if(this->Elements[Child]->Weight > this->Elements[Child+1]->Weight)   //若右孩子小，那么更新Child到右孩子
            ++Child;
        if(temp->Weight <= this->Elements[Child]->Weight)    //若temp小于最小的子节点，证明可以填
            break;
        else{        //把最小Child移到Parent
            this->Elements[Parent] = this->Elements[Child];
        }
    }
    //此时Parent就是temp应该插入的位置
    this->Elements[Parent] = temp;
    return Min;
}


//将根节点维护成堆,自上而下。与删除逻辑类似
void Min_heap_H::sort(int root)
{
    ElementType temp = this->Elements[root];
    int Child;
    //结束条件：具有左节点
    for (; root*2 <= this->Size; root = Child) {
        Child = root*2; //左节点
        if(Child+1<=this->Size && this->Elements[Child]->Weight > this->Elements[Child+1]->Weight)
            ++Child;
        if(temp->Weight <= this->Elements[Child]->Weight) //根节点的权值小于儿子的最小权值,跳出
            break;
        else //根节点不是最小权值，下面的提上来
            this->Elements[root] = this->Elements[Child];
    }
    this->Elements[root] = temp;
}

/**
 *
 * 在vector基础上直接转化为最大堆 时间复杂度O(n)
 * 从最后一个有孩子结点的结点来说，其本身结点和孩子结点共同构成"子最小堆"，借助前面删除的想法，对每个"子最小堆"排序，当排序完成，整个最小堆也建立成功
 * 排序的算法跟删除一样
 *
 * @param res
 */
void Min_heap_H::Translate_heap(const vector<int>& res)
{
    int n = res.size();

    if(res.size() > this->Capacity)
    {
        cout<<"超出容量"<<endl;
        n = this->Capacity;
    }
    //O(n)
//    for (int i = 0; i < n; ++i) {
//        this->Elements[++(this->Size)] = res[i];
//    }

    for (int x : res) {
        Huffman_Tree  T = make_shared<Huffman_Node>();
        T->Weight = x;
        this->Elements[++(this->Size)] = T;
    }

    //最后一个有叶子节点的节点
    int lastroot = this->Size/2;
    for(int i = lastroot;i>0;--i)
    {
        sort(i);
    }

}
void PreorderTraversal(const Huffman_Tree& T)
{
    if(!T)
        return;
    cout<<T->Weight<<" ";
    PreorderTraversal(T->Left);
    PreorderTraversal(T->Right);
}

template class heap<Huffman_Tree>;