#include<iostream>
#include<stack>
#include<string>
#include<malloc.h>
#include <stdio.h>
#include <memory>

using namespace std;


template <class T>
struct TreeNode{
    T data;
    int flag = 0;
    shared_ptr<TreeNode<T>> left;   // 左子树
    shared_ptr<TreeNode<T>> right;  // 右子树
};

typedef  shared_ptr<TreeNode<string>> Tree;
typedef shared_ptr<TreeNode<int>> INT_Tree;
//typedef TreeNode<int>* INT_Tree;



// 初始化一个树结点
Tree create(){
    Tree T;
//    T = new TreeNode<string>();
    T = make_shared<TreeNode<string>>();
    T->left = nullptr;
    T->right = nullptr;
    return T;
}

// 根据中序遍历整理出这棵树
Tree restore(Tree T){
    int n;
    string str;
    stack<Tree> s;
    Tree node = T;
    bool flag = false;
    string value;
    cin>>n;
    cin.ignore();
//    scanf("%d",&n);
//    cin.seekg(0, ios_base::end);
    // 根节点赋值
    getline(cin,str);
//    cout<<str<<endl;
    value = str.substr(5);  // 从第五个开始截取
    node->data = value;
    // 根结点入栈
    s.push(node);
//    while(node || !s.empty())
    for(int i=1;i<2*n;i++)
    {
        getline(cin,str);
        if(str=="Pop"){// 如果是 pop 操作
            node = s.top();
            s.pop();
        }else{   // push
            value = str.substr(5);  // 从第五个开始截取
            Tree tmp = create();
            tmp->data = value;
            if(!node->left){// 如果左儿子空，新结点就是左儿子
                node->left = tmp;
                node = node->left;
            }else if(!node->right){  // 如果右儿子空，新结点就是右儿子
                node->right = tmp;
                node = node->right;
            }
            s.push(tmp);
        }
    }
    return T;
}



//递归后序遍历
//前序，中序只需要改变顺序
void PostorderTranversal(Tree T,bool& flag)
{
    if(!T)
        return;
    PostorderTranversal(T->left,flag);
    PostorderTranversal(T->right,flag);
    if(!flag)
        flag = true;
    else
        cout<<" ";
    cout<<T->data;
}

//非递归,前序
void StackPreorderTranversal(Tree T,bool& flag)
{
    Tree BT = T;
//    Tree Printp = nullptr; //保存上一个已经访问的节点
    if(!T)
        return;
    stack<Tree> s;
//    s.push(BT);
    while(BT || !s.empty())
    {
        while(BT)
        {

            cout<<BT->data<<" ";
            s.push(BT);
            BT = BT->left;
        }

        if(!s.empty())
        {
            BT = s.top();
            s.pop();

            BT = BT->right;


        }
    }
    cout<<endl;
}


//非递归,中序
void StackInorderTranversal(Tree T,bool& flag)
{
    Tree BT = T;
//    Tree Printp = nullptr; //保存上一个已经访问的节点
    if(!T)
        return;
    stack<Tree> s;
//    s.push(BT);
    while(BT || !s.empty())
    {
        while(BT)
        {
            s.push(BT);
            BT = BT->left;
        }

        if(!s.empty())
        {
            BT = s.top();
            s.pop();

            if(!flag)
                flag = true;
            else
                cout<<" ";
            cout<<BT->data;

            BT = BT->right;


        }
    }
    cout<<endl;
}

//非递归的后序遍历
void StackPostorderTranversal(Tree T,bool& flag)
{
    Tree BT = T;
    Tree Printp = nullptr; //保存上一个已经访问的节点
    if(!T)
        return;
    stack<Tree> s;
//    s.push(BT);
    while(BT || !s.empty())
    {
        while(BT)
        {
            s.push(BT);
            BT = BT->left;
        }

        if(!s.empty())
        {
            BT = s.top();
            s.pop();

            if(BT->right == Printp || BT->right == nullptr)    //如果右节点已经访问了或者说不存在就可以打印该节点
            {
                if(!flag)
                    flag = true;
                else
                    cout<<" ";
                cout<<BT->data;
                Printp = BT;
                BT = nullptr;
            }
            else{
                s.push(BT); /* 否则,不应该弹出结点, 结点再次入栈 */
                BT = BT->right;
            }

        }
    }
    cout<<endl;
}


//题目1
void Question1()
{
    Tree T;
    bool flag = false;
    string str;
    T = create();
    T = restore(T);
    StackPreorderTranversal(T,flag);
    StackInorderTranversal(T,flag);
    StackPostorderTranversal(T,flag);
}


////////////////////////题目2
//////////////////////////////////////////////////////////////////////////////////////////
void PreorderTranversal(const INT_Tree T,string& tempstr)
{
    if(!T)
        return;

    tempstr += (T->data + '0');
    PreorderTranversal(T->left,tempstr);
    PreorderTranversal(T->right,tempstr);
}


INT_Tree Insert(int x,INT_Tree BST)
{
    //这里与搜索不同的点，空就证明到了要插入的位置
    if(!BST)
    {
        //用动态指针解决什么时候释放的问题
        BST = make_shared<TreeNode<int>>();
        BST->data = x;
        BST->right = nullptr;
        BST->left = nullptr;
    }
    else{//不为空，根节点进行比较
        if(x < BST->data)
            BST->left = Insert(x,BST->left);
        else if(x > BST->data)
            BST->right = Insert(x,BST->right);
        //相等什么也不做？
    }
    return BST;
}

//检查该节点是否有问题
bool check(int x,INT_Tree BST)
{
    if(BST->flag)   //该节点原来访问过
    {
        if(x < BST->data) return check(x,BST->left);
        else if(x > BST->data) return check(x,BST->right);
        else return false;
    } else{ //该节点没有访问过
        if(x == BST->data)
        {
            BST->flag = 1;
            return true;
        } else  //若节点从没有被访问，且节点值不等就退出
            return false;
    }
}

void Reset(INT_Tree T)
{
    if(!T)
        return;

    T->flag = 0;
    Reset(T->left);
    Reset(T->right);
}

//判断后面的二叉树是否跟前面的一致
bool judge(INT_Tree InitBST,int N)
{
    int X = 0;
    bool flag = true;
    //先对根节点做处理
//    cin.ignore();
//    cin>>X;
////    scanf("%d",&X);
//    if(InitBST->data != X) return false;
//    else InitBST->flag = 1;

    for (int i = 0; i < N; ++i) {
//        scanf("%d",&X);
        cin.ignore();
        cin>>X;
        if(!check(X,InitBST))   //只要有一个check是错的，那么肯定就是不等
            flag = false;
    }

    return flag;
}


//根据输入构建二叉搜索树
void create_tree()
{
    int n,l;
    int tmp;
    cin>>n;
    while(n)
    {
        cin>>l;
        INT_Tree InitBST = nullptr;
        // 每次新输入 n l 的初始插入序列
        for (int i = 0; i < n; ++i) {
            cin>>tmp;
            InitBST = Insert(tmp,InitBST);
        }


        // 每行的插入序列产生一个树，用 str 记录先序遍历结果
        //插入是按先序进行插入的，所以
//        PreorderTranversal(InitBST,Initstr);
//        cout<<Initstr<<endl;


        //循环剩下的判别数组
        for (int j = 0; j < l; ++j) {
            if(judge(InitBST,n)) cout<<"Yes"<<endl;
            else cout<<"No"<<endl;
            //清除模板二叉树的标记
            Reset(InitBST);
        }


        cin>>n;
    }
}

//题目2
void Question2()
{
    //构建树
    create_tree();

    //

}



////////////////////////题目3
//////////////////////////////////////////////////////////////////////////////////////////
typedef struct AVLNode* AVLTree;
struct AVLNode{
    int data;     // 存值
    AVLTree left;  // 左子树
    AVLTree right;  // 右子树
    int height;  // 树高
};

// 返回树高，空树返回 -1
int getHeight(AVLTree A){
    return A== nullptr?-1:A->height;
}

// 返回最大值
int max(int a,int b){
    return a>b?a:b;
}

// LL单旋
// 把 B 的右子树腾出来挂给 A 的左子树，再将 A 挂到 B 的右子树上去
AVLTree LLRotation(AVLTree A)
{
    AVLTree B = A->left;    //B为A的左子树
    A->left = B->right;     //B的右子树（左边最大的值）挂在A的左子树上（右边最小的值）
    B->right = A;           //A挂在B的右子树
    //更新树高,树高就是比左右子树最高的树+1
    A->height = max(getHeight(A->left),getHeight(A->right)) + 1;

    B->height = max(getHeight(B->left),getHeight(B->right)) + 1;

    return B;
}


//RR单旋
AVLTree RRRotation(AVLTree A)
{
    AVLTree B = A->right;
    A->right = B->left;//B的左子树挂在A的右子树上
    B->left = A;    //A挂在B的左子树上
    //更新树高,树高就是比左右子树最高的树+1
    A->height = max(getHeight(A->left),getHeight(A->right)) + 1;
    B->height = max(getHeight(B->left),getHeight(B->right)) + 1;
    return B;
}

// LR双旋
AVLTree LRRotation(AVLTree A)
{
    //A的左子树进行RR

    A->left = RRRotation(A->left);
    //A进行LL
    return LLRotation(A);
}

// RL双旋
AVLTree RLRotation(AVLTree A)
{
    //A的左子树进行LL
    A->right = LLRotation(A->right);
    //A进行RR
    return RRRotation(A);
}

//插入所有，返回根节点
AVLTree Insert(AVLTree T,int x)
{
    if(!T){  // 如果该结点为空，初始化结点
        T = (AVLTree)malloc(sizeof(struct AVLNode));
        T->data = x;
        T->left = NULL;
        T->right = NULL;
        T->height = 0;
    }else{  // 否则不为空，
        if(x < T->data){  // 左子树
            T->left = Insert(T->left,x);
            if(getHeight(T->left)-getHeight(T->right)==2){  // 如果左子树和右子树高度差为 2
                if(x < T->left->data)  // LL 单旋
                    T = LLRotation(T);
                else if(T->left->data < x)  // LR双旋
                    T = LRRotation(T);
            }
        }else if(T->data < x){
            T->right = Insert(T->right,x);
            if(getHeight(T->right)-getHeight(T->left)==2){
                if(x < T->right->data)  // RL 双旋
                    T = RLRotation(T);
                else if(T->right->data < x)  // RR单旋
                    T = RRRotation(T);
            }
        }
    }
    //更新树高
    T->height = max(getHeight(T->left),getHeight(T->right)) + 1;
    return T;
        //相等什么也不做
}

//非递归,前序
void StackPreorderTranversal(AVLTree T,bool& flag)
{
    AVLTree BT = T;
//    Tree Printp = nullptr; //保存上一个已经访问的节点
    if(!T)
        return;
    stack<AVLTree> s;
//    s.push(BT);
    while(BT || !s.empty())
    {
        while(BT)
        {

            cout<<BT->data<<" ";
            s.push(BT);
            BT = BT->left;
        }

        if(!s.empty())
        {
            BT = s.top();
            s.pop();

            BT = BT->right;


        }
    }
    cout<<endl;
}

//非递归,中序
void StackInorderTranversal(AVLTree T,bool& flag)
{
    AVLTree BT = T;
//    Tree Printp = nullptr; //保存上一个已经访问的节点
    if(!T)
        return;
    stack<AVLTree> s;
//    s.push(BT);
    while(BT || !s.empty())
    {
        while(BT)
        {
            s.push(BT);
            BT = BT->left;
        }

        if(!s.empty())
        {
            BT = s.top();
            s.pop();

            if(!flag)
                flag = true;
            else
                cout<<" ";
            cout<<BT->data;

            BT = BT->right;
        }
    }
    cout<<endl;
}

void Question3()
{
    AVLTree T= nullptr;
    int n;
    cin>>n;
    for(int i=0;i<n;i++)
    {
        int tmp;
        cin>>tmp;
        T = Insert(T,tmp);
    }
    cout<<T->data;
    
}
//题目4
///////////////////////////////////////////////////////////////////////////////////
    #define MaxSize 200
    #include <algorithm>
    int value[MaxSize];
    int BST[MaxSize];

    //计算n个节点的树其左树节点的个数
    int getLeftTreeSize(int n)
    {
        //计算出树的高度
        int h = 0;
        int temp = n+1;
        while(temp!=1)
        {
            temp /= 2;
            ++h;
        }
        int x = n - int(pow(2,h) - 1); //计算出叶节点的个数
        x  = x < pow(2,h-1) ? x : int(pow(2,h-1));  //维护左叶子节点的最大值
        int L = (int(pow(2,h-1))-1) + x; // 除叶子节点外，根节点的左子树个数+左叶子节点 = 左边叶子节点的个数
        return L;
    }

    /**
     * 这是按照层次遍历顺序填充到BST中
     * @param left 这里是对于value数组来说，用来查找其中的root
     * @param right 这里是对于value数组来说
     * @param root 这里是对于BST数组来说的
     */
    void fill(int left,int right,int root)
    {
        int n = right - left + 1;  //确定范围内数值个数
        if(!n)
            return;
        int L = getLeftTreeSize(n); //找到偏移量
        BST[root] = value[left+L];   //根节点的值应该是 左边界 + 偏移量
        int leftRoot = 2 * root + 1;    //根据完全二叉树的概念，若从0开始，根的左节点 = 2*i+1;根的右节点 = 2*i+2
        int rightRoot = leftRoot + 1;
        fill(left,left+L-1,leftRoot);   //左子树递归
        fill(left+L+1,right,rightRoot);     // 右子树递归
    }


    void Question4()
    {
        int n;
        cin>>n;
        for(int i=0;i<n;i++){
            cin>>value[i];
        }
        sort(value,value+n);
        fill(0,n-1,0);
        for(int i=0;i<n;i++){
            if(i)
                cout<<" ";
            cout<<BST[i];
        }
    }



    int main() {
    //    Question1();
    //    Question2();
    //    Question3();
        Question4();
        return 0;
    }
