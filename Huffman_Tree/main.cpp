//
// Created by ybw on 2020/4/2.
//

//#include "HuffmanTree.h"


//////////////////////////////////////////////////Huffman_Code
#include <queue>
#include <map>
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

priority_queue<int,vector<int>,greater<int>> q;
map<char,int> Huffman_Base;
struct Huffman_base
{
    int weight;         //频率
    char character;     //字符
};

struct Huffman_code
{
    char character;     //字符
    string str;         //编码
};



int FirstWeight(int n)
{
    int WPL = 0;
    //频率全部压入队列
    auto iter = Huffman_Base.begin();
    for (;iter != Huffman_Base.end();++iter) {
        q.push(iter->second);
    }
    int L1,L2;
    for (int i = 0; i < n-1; ++i) {
        L1 = q.top();
        q.pop();
        L2 = q.top();
        q.pop();
        q.push(L1+L2);
        WPL += L1 + L2;
    }
    q.pop();
    return WPL;
}

//比较器
bool cmp(const Huffman_code& X1,const Huffman_code& X2)
{
    return X1.str.size() < X2.str.size();
}

//判断是否有前缀
bool have_pre(int n,Huffman_code code[])
{
    sort(code,code+n,cmp);
    for (int i = 0; i < n; ++i) {
        string str = code[i].str;
        for (int j = i+1; j < n; ++j) {
            if(str == code[j].str.substr(0,str.size()))
                return true;
        }
    }
    return false;
}



bool judge(int n,int WPL)
{
    char character;
    string str;
    Huffman_code code[n];
    int code_WPL = 0;
    for (int i = 0; i < n; ++i) {
        cin>>character>>str;
        code[i].character = character;
        code[i].str = str;

        //首先计算编码长度。
        if(Huffman_Base.find(character) != Huffman_Base.end())
            code_WPL += Huffman_Base.find(character)->second * static_cast<int>(str.size());
        else
            cout<<"没有找到该字符，出现错误"<<endl;
    }
    if(WPL != code_WPL || have_pre(n,code))
        return false;
    else
        return true;
}



//1.输入数据
//2. WPL的比较
    // a. 对基本的数据计算WPL，利用优先队列，出队的权值相加
    // b. 对输入的编码计算WPL，字符长度*出现频率
//3. 对于WPL最优的计算是否拥有前缀
void Huffman_Code(){
    int N,M;
    cin>>N;
    char character;
    int frequence;
    for (int i = 0; i < N; ++i) {
        cin>>character>>frequence;
        Huffman_Base[character] = frequence;
    }
    //计算基本数据的WPL
    int WPL = FirstWeight(N);
    cin>>M;
    for (int i = 0; i < M; ++i) {
        if(judge(N,WPL))
            cout<<"Yes"<<endl;
        else
            cout<<"No"<<endl;
    }


}
//////////////////////////////////////////////////



int main()
{
//    vector<int> a = {1,2,3,4,5,6,7};
//    HuffmanTree H({4,5,6});
//    PreorderTraversal(H);
//    int test = H.WPL(H.Huff,0);
//    cout<<test<<endl;
    Huffman_Code();
    return 0;
}