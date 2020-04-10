//
// Created by ybw on 2020/4/3.
//

#include <iostream>
//#include "Union.h"

using namespace std;

//////////////////////////////////////////////////////05-树8 File Transfer (25分)算法题
//因为计算机是从1-N进行排序的，所以下标0-N-1可以是计算机序号的映射。
#define QMaxsize 100
class Q_Union{
public:
    Q_Union(int size)
        :data(new int[size]),Size(size)
    {
        for (int i = 0; i < Size; ++i) {
            data[i] = -1;
        }
    }

    int size(){return Size;}

    int& operator[](int index)
    {
        return data[index];
    }

    //查找跟节点
    int Find(int X){
        for(;data[X] >= 0; X = data[X]);
        return X;
    }

    //路径压缩的方式查找
    int Find_based_PathCompression(int X){
        if(data[X] < 0) //找到根节点
            return X;
        else
        //不是根节点，去上一层查找并更新上一层保存的根节点。
            return data[X] = Find(data[X]);
    }


    //合并
    void Union(int X1,int X2)
    {
        data[X1] = X2;  //更新X1的根为X2
    }
    //按秩合并1 树高 利用存储根节点的地方保存树高 -树高
    void Union_based_Height(int X1,int X2)
    {
        if(data[X1] < data[X2])  //X1的树比较高
            data[X2] = X1;  //更新X2的树根
        else{
            if (data[X1] == data[X2])
                --(data[X2]); //X2的高度增加1
            data[X1] = X2;  //更新X1的树根
        }
    }
    //按秩合并2 数量
    void Union_based_Number(int X1,int X2)
    {
        if(data[X1] < data[X2]) //X1集合的数量更多
        {
            data[X1] += data[X2];
            data[X2] = X1;
        } else
        {
            data[X2] += data[X1];
            data[X1] = X2;
        }
    }
    ~Q_Union()
    {
        delete [] data;
        data = nullptr;
    }

private:
    int* data;
    int Size;
};

void Input_connection(Q_Union& qUnion)
{
    int X1,X2;
    cin>>X1>>X2;
    int root1 = qUnion.Find_based_PathCompression(X1-1);
    int root2 = qUnion.Find_based_PathCompression(X2-1);
    if(root1 != root2)
//        qUnion.Union(root1,root2);
        qUnion.Union_based_Number(root1,root2);
}
void Check_connection(Q_Union& qUnion)
{
    int X1,X2;
    cin>>X1>>X2;
//    int root1 = qUnion.Find(X1-1);
//    int root2 = qUnion.Find(X2-1);
    int root1 = qUnion.Find_based_PathCompression(X1-1);
    int root2 = qUnion.Find_based_PathCompression(X2-1);
    if(root1 == root2)
        cout<<"yes"<<endl;
    else
        cout<<"no"<<endl;

}
void Check_network(Q_Union& qUnion)
{
    int N = 0;
    for (int i = 0; i < qUnion.size(); ++i) {
        if(qUnion[i] < 0)
            ++N;
    }

    if(N <= 1)
        printf("The network is connected.");
    else
        printf("There are %d components.",N);
}


void File_Transfer()
{
    int N;
    cin>>N;
    Q_Union qUnion(N);
    char flag;
    do{
        getchar();  // 接收每次多出来的回车
        cin>>flag;
        switch (flag){
            case 'I':
                Input_connection(qUnion);
                break;
            case 'C':
                Check_connection(qUnion);
                break;
            case 'S':
                Check_network(qUnion);
                break;
            default:
                break;
        }
    }
    while(flag != 'S');
}

//////////////////////////////////////////////////////


int main()
{
//    Union u;
////    for (int i = 0; i < u.size(); ++i) {
////        cout<<u.data[i].value<<" ";
////    }
////    cout<<endl;
//
//    u.union_value(4,5);
//    u.union_value(6,7);
//    u.union_value(8,9);
//    cout<<u.Find(9)<<endl;
//    u.union_value(4,8);
//    u.union_value(4,6);
//    cout<<u.Find(9)<<endl;
    File_Transfer();


    return 0;
}