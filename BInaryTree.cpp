/*************************************************************************
    > File Name: BInaryTree.cpp
    > Author: 何军
    > Sub: 二叉树的实现
    > Created Time: 2017年10月30日 星期一 11时04分31秒
 ************************************************************************/

#include <bits/stdc++.h>
using namespace std;

//----------------------------------------二叉树节点类------------------------------------------------------------------
template <typename T>
class BinaryTreeNode { // 二叉树节点类

private:
    T info; // 二叉树结点域
    BinaryTreeNode<T> *left; // 指向左子树
    BinaryTreeNode<T> *right; // 指向右子树
public:
    BinaryTreeNode(); // 缺省构造函数
    BinaryTreeNode(const T& ele); // 给定数据的构造
    BinaryTreeNode(const T& ele, BinaryTreeNode<T> *l, BinaryTreeNode<T> *r); // 子树构造结点
    T value() const; // 返回当前结点数据
    void visit(const BinaryTreeNode<T> *node); // 访问结点
    BinaryTreeNode<T> *leftchild() const; // 返回左子树,常量成员函数
    BinaryTreeNode<T> *rightchild() const; // 返回右子树
    void setLeftchild(BinaryTreeNode<T> *); // 设置左子树
    void setRightchild(BinaryTreeNode<T> *); // 设置右子树
    void setValue(const T& val); // 设置数据域
    bool isLeaf() const; // 判断是否为叶节点
    BinaryTreeNode<T> & operator=(const BinaryTreeNode<T> &Node); // 重载赋值运算符
};

//---------------------------------------------二叉树类-------------------------------------------------------------------------------
template <typename T>
class BinaryTree{ // 二叉树类
friend class BinaryTreeNode<T>; // 声明是二叉树类的友元类.可以操作二叉树中的数据
private:
    BinaryTreeNode<T> *root; // 二叉树根结点
public:
    BinaryTree(){root = NULL;}; // 构造函数,根结点置为空
    ~BinaryTree(){deleteBinaryTree(root);}; // 析构函数
    bool isEmpty() const; // 判断二叉树是不是空树
    BinaryTreeNode<T> * getRoot(){return root;}; // 返回根结点
    BinaryTreeNode<T> * parent(BinaryTreeNode<T> *rt,BinaryTreeNode<T> *current); // 返回父结点,递归查找
    BinaryTreeNode<T> * parent(BinaryTreeNode<T> *current); // 利用栈结构来查找
    BinaryTreeNode<T> * leftSibling(BinaryTreeNode<T> *current); // 左兄
    BinaryTreeNode<T> * rightSibling(BinaryTreeNode<T> *current); // 右兄
    void createTree(const T& info, BinaryTree<T> & leftTree, BinaryTree<T> & rightTree); // 构造新树
    void preOrder(BinaryTreeNode<T> *root); // 前序遍历二叉树或其子树
    void inOrder(BinaryTreeNode<T> *root); // 中序遍历二叉树或其子树
    void postOrder(BinaryTreeNode<T> *root); // 后序遍历二叉树或其子树
    void preOrderWithoutRecusion(BinaryTreeNode<T> *root); // 前序遍历二叉树或其子树用栈
    void inOrderWithoutRecusion(BinaryTreeNode<T> *root); // 中序遍历二叉树或其子树用栈
    void postOrderWithoutRecusion(BinaryTreeNode<T> *root); // 后序遍历二叉树或其子树用栈
    void levelOrder(BinaryTreeNode<T> *root); // 按层次遍历二叉树或其子树
    void deleteBinaryTree(BinaryTreeNode<T> *root); // 删除二叉树或其子树
};
//-----------------------------------------------------------------------------------------------------------------------




//------------------------------------------------二叉树结点类的相关实现-------------------------------------------
template <typename T>
BinaryTreeNode<T>::BinaryTreeNode(){ // 保留空的构造函数
    left = right = NULL; // 将指针置空操作
}

template <typename T>
BinaryTreeNode<T>::BinaryTreeNode(const T& ele){ // 给结点的数据域一个值
    info = ele; // 结点数据域赋值
}

template <typename T>
BinaryTreeNode<T>::BinaryTreeNode(const T& ele, BinaryTreeNode<T> *l, BinaryTreeNode<T> *r){ // 子树构造结点
    info = ele; // 结点数据域赋值
    left = l; // 设置左孩子
    right = r; // 设置右孩子
}

template <typename T>
T BinaryTreeNode<T>::value() const{ // 返回当前结点数据
    return info; // 返回结点数据
}

template <typename T>
void BinaryTreeNode<T>::visit(const BinaryTreeNode<T> *node){ // 访问结点
    cout << node->value() << " "; // 输出当前结点的数据
}

template <typename T>
BinaryTreeNode<T>* BinaryTreeNode<T>::leftchild() const{ // 返回左孩子,常量成员函数
    return left;
}

template <typename T>
BinaryTreeNode<T>* BinaryTreeNode<T>::rightchild() const{ // 返回右孩子
    return right;
}

template <typename T>
void BinaryTreeNode<T>::setLeftchild(BinaryTreeNode<T> *l){ // 设置左孩子
    left = l;
}

template <typename T>
void BinaryTreeNode<T>::setRightchild(BinaryTreeNode<T> *r){ // 设置右孩子
    right = r;
}

template <typename T>
void BinaryTreeNode<T>::setValue(const T& val){ // 设置数据域
    info = val; // 设置数据
}

template <typename T>
bool BinaryTreeNode<T>::isLeaf() const{
    // 判断是否为叶节点
    return (left==NULL && right==NULL); // 左右孩子都是空就是叶子结点
}

template <typename T>
BinaryTreeNode<T> & BinaryTreeNode<T>::operator=(const BinaryTreeNode<T> &Node){  // 重载赋值运算符
    return NULL;
}
//------------------------------------------------------------------------------------------------end

//---------------------------二叉树的实现------------------------------------------------------------
template <typename T>
bool BinaryTree<T>::isEmpty() const{ // 判断二叉树是不是空树
    return root == NULL; // 根节点是空就说明二叉树是空树
}


template <typename T>
BinaryTreeNode<T> * BinaryTree<T>::parent(BinaryTreeNode<T> *rt,BinaryTreeNode<T> *current){ // 递归查找父结点
    BinaryTreeNode<T>* tmp;
    if(rt == NULL) return NULL; // 如果是空树
    if(current == rt->leftchild() || current == rt->rightchild()) // 是根的左孩子或者是右孩子
        return rt;
    if((tmp=parent(rt->leftchild(), current)) != NULL) // 从左边找
        return tmp;
    if((tmp=parent(rt->rightchild(), current)) != NULL) // 从右边找
        return tmp;
    return NULL; // 都找不到
}

template <typename T>
BinaryTreeNode<T> * BinaryTree<T>::parent(BinaryTreeNode<T> *current){ // 利用栈结构来查找
    stack<BinaryTreeNode<T> *> aStack; // 工作栈
    BinaryTreeNode<T> *p = root; // 工作指针
    aStack.push(NULL); // 栈底监视哨
    while(p) { // 相当与先序遍历
        if(p->rightchild() == current || p->rightchild() == current)
            return p;
        if(p->rightchild() != NULL) // 非空右孩子入栈
            aStack.push(p->rightchild());
        if(p->leftchild() != NULL) // 左路下降
            p = p->leftchild();
        else{   // 左子树访问完闭.开始访问右子树
            p = aStack.top(); aStack.pop(); // 取得栈顶元素.
        }
    }
}

template <typename T>
BinaryTreeNode<T> * BinaryTree<T>::leftSibling(BinaryTreeNode<T> *current){ // 返回current节点的左兄弟
    if(current){ // 如果当前结点不是空的
        BinaryTreeNode<T> *p = parent(current); // 找到当前结点的父结点
        if(p == NULL || current == p->leftchild()) // 如果父结点是空的或者当前结点是父结点的左孩子.说明它没有左兄弟
            return NULL;
        else return p->leftchild(); // 当前结点有父结点.并且是父结点的右孩子
    }
    return NULL;
}

template <typename T>
BinaryTreeNode<T> * BinaryTree<T>::rightSibling(BinaryTreeNode<T> *current){ // // 返回current节点的右兄弟
    if(current){ // 如果当前结点不是空的
        BinaryTreeNode<T> *p = parent(current); // 找到当前结点的父结点
        if(p == NULL || current == p->rightchild()) // 如果父结点是空的或者当前结点是父结点的右孩子.说明它没有右兄弟
            return NULL;
        else return p->rightchild(); // 当前结点有父结点.并且是父结点的左孩子
    }
    return NULL;
}


template <typename T>
void BinaryTree<T>::createTree(const T& info, BinaryTree<T> & leftTree, BinaryTree<T> & rightTree){ // 构造新树,前序构造二叉树
    // 以info作为根结点，leftTree作为树的左子树，rightTree作为树的右子树，构造一棵新的二叉树
    root = new BinaryTreeNode<T>(info,leftTree.root,rightTree.root);  //创建新树
    leftTree.root = rightTree.root = NULL;    //原来两棵子树的根结点指空，避免访问
}



template <typename T>
void BinaryTree<T>::preOrder(BinaryTreeNode<T> *root){ // 先序遍历
    if(root != NULL){
        visit(root); // 访问结点
        preOrder(root->leftchild()); // 先序遍历左子树
        preOrder(root->rightchild()); // 先序遍历右子树
    }
}

template <typename T>
void BinaryTree<T>::inOrder(BinaryTreeNode<T> *root){ // 中序遍历
    if(root != NULL){
        inOrder(root->leftchild()); // 中序遍历左子树
        visit(root); // 访问结点
        inOrder(root->rightchild()); // 中序遍历右子树
    }
}

template <typename T>
void BinaryTree<T>::postOrder(BinaryTreeNode<T> *root){ // 后序遍历
    if(root != NULL){
        postOrder(root->leftchild()); // 后序遍历左子树
        postOrder(root->rightchild()); // 后序遍历右子树
        visit(root); // 访问结点
    }
}

template <typename T>
void BinaryTree<T>::preOrderWithoutRecusion(BinaryTreeNode<T> *root){ // 先序遍历
    stack<BinaryTreeNode<T> *> aStack; // 工作栈
    BinaryTreeNode<T> * pointer = root; // 因为不能改变root指针的指向,所以用一个工作指针代替
    aStack.push(NULL); // 栈底监视哨
    while(pointer){
        Visit(pointer->value); // 访问当前结点
        if(pointer->rightchild() != NULL) // 右孩子入栈
            aStack.push(pointer->rightchild());
        if(pointer->leftchild() != NULL) // 左路下降
            pointer = pointer->leftchild();
        else { // 左子树访问完毕,访问右子树
            pointer = aStack.top(); // 得到栈顶元素
            aStack.pop(); // 栈顶元素退栈
        }
    }
}

template <typename T>
void BinaryTree<T>::inOrderWithoutRecusion(BinaryTreeNode<T> *root){ // 中序遍历
    stack<BinaryTreeNode<T> *> aStack; // 工作栈
    BinaryTreeNode<T> * pointer = root; // 因为不能改变root指针的指向,所以用一个工作指针代替
    while(!aStack.empty() || pointer){ // 一开始栈是空的,pointer一般不是空
        if(pointer){ // 如果当前结点不是空
            // Visit(pointer->value()); // 前序访问结点的情况
            aStack.push(pointer); // 当前节点入栈
            pointer = pointer->leftchild(); // 当前结点指向左孩子
        } else { // 左子树访问完毕,转向右子树
            pointer = aStack.top(); // 得到栈顶元素
            aStack.pop(); // 当前元素退栈
            Visit(pointer->value()); // 访问当前节点
            pointer = pointer->rightchild(); // 当前链接结构指向有孩子
        }
    }
}


template <typename T>
void BinaryTree<T>::postOrderWithoutRecusion(BinaryTreeNode<T> *root){ // 后序遍历二叉树或其子树用栈

}

template <typename T>
void BinaryTree<T>::levelOrder(BinaryTreeNode<T> *root){ // 按层次遍历二叉树或其子树,宽搜
    queue<BinaryTreeNode<T> *> aQueue; // 工作队列
    BinaryTreeNode<T> *p = root; // 工作指针先指向树根
    if(p) aQueue.push(p); // 把第一个结点加入队列
    while(!aQueue.empty()) {
        p = aQueue.front(); aQueue.pop(); // 得到队头元素
        visit(p); // 访问这个结点
        if(p->leftchild())
            aQueue.push(p->leftchild()); // 左孩子入队列
        if(p->rightchild())
            aQueue.push(p->rightchild()); // 右孩子入队列
    }
}

template <typename T>
void BinaryTree<T>::deleteBinaryTree(BinaryTreeNode<T> *root){ // 删除二叉树或其子树
    if(root){ // 如果不是空树
        deleteBinaryTree(root->leftchild()); // 删除左孩子
        deleteBinaryTree(root->rightchild()); // 删除右孩子
        delete root; // 删除根结点
    }
}
//------------------------------------------------------------------------------------------------------end


int main(){
    freopen("BinaryTreeIn.txt", "r", stdin);
    BinaryTree<char> chTree;

    fclose(stdin);
}


