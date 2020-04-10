//
// Created by ybw on 2020/4/1.
//
#include <iostream>
#include "heap.h"

using namespace std;



//
// Created by ybw on 2020/4/1.
//


int main()
{
//    测试堆的最基本能力
//    Min_heap h;
//    for (int i = 0; i < 50; ++i) {
//        h.Insert(i);
//    }
//    for (int i = 0; i < 51; ++i) {
//        cout<<h;
//        cout<<h.Delete()<<endl;
//    }

    //测试建立堆算法1
//    heap h2;
//    Translate_heap(vector<int>{1,2,3,4,5,6,7},h2);
//    cout<<h2<<endl;

//    //测试建立堆算法2
//    Max_heap<int> h3;
//    vector<int> ans;
//    for (int i = 0; i < 10; ++i) {
//        ans.push_back(i);
//    }

    //算法1
//    heap<int>* h = new Max_heap<int>();
//    Translate_heap(ans,h);
//    cout<<*h<<endl;

    //算法2
//    h3.Translate_heap(ans);
//    cout<<h3<<endl;
//
//    for (int i = 0; i < 10; ++i) {
//        cout<<h3.Delete()<<endl;
//    }

    //浙江数据结构算法——堆中的路径
    int N,M;
    cin>>N>>M;
    vector<int> tmp;
    for (int i = N; i > 0; --i) {
        int x;
        cin>>x;
        tmp.push_back(x);
    }

    Min_heap<int> h;
    Translate_heap<int>(tmp,&h);
    while(M)
    {
        int index;
        cin>>index;
        h.print_i_to_root(index);
        --M;
    }

}