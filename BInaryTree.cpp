/*************************************************************************
	> File Name: BInaryTree.cpp
	> Author: 何军 
    > Sub: 二叉树的实现
	> Created Time: 2017年10月30日 星期一 11时04分31秒
 ************************************************************************/

#include<iostream>
#include<stack>
using namespace std;


template <typename T>
class BinaryTreeNode { // 二叉树节点类
    friend class BinaryTree<T>; // 声明二叉树类为友元类
private:
    T info; // 二叉树结点域
public:
    BinaryTreeNode(); // 缺省构造函数
    BinaryTreeNode(const T& ele); // 给定数据的构造
    BinaryTreeNode(const T& ele, BinaryTreeNode<T> *l, BinaryTreeNode<T> *r); // 子树构造结点
    T value() const; // 返回当前结点数据
    void Visit(const BinaryTreeNode<T> *node); // 访问结点 
    BinaryTreeNode<T> *leftchild() const; // 返回左子树
    BinaryTreeNode<T> *rightchild() const; // 返回右子树
    void setLeftchild(BinaryTreeNode<T> *); // 设置左子树
    void setRightchild(BinaryTreeNode<T> *); // 设置右子树
    void setValue(const T& val); // 设置数据域
    bool isLeaf() const; // 判断是否为叶节点
    BinaryTreeNode<T> & operator=(const BinaryTreeNode<T> &Node); // 重载赋值运算符
};

template <typename T>
class BinaryTree{ // 二叉树类
private:
    BinaryTreeNode<T> *root; // 二叉树根结点
public:
    BinaryTree(){root = NULL}; // 构造函数
    ~BinaryTree(){DeleteBinaryTree(root);}; // 析构函数
    bool isEmpty() const; // 判断二叉树是不是空树
    BinaryTreeNode<T> * Root(){return root;}; // 返回根结点
    BinaryTreeNode<T> * Parent(BinaryTreeNode<T> *current); // 返回父结点
    BinaryTreeNode<T> * LeftSibling(BinaryTreeNode<T> *current); // 左兄
    BinaryTreeNode<T> * RightSibling(BinaryTreeNode<T> *current); // 右兄
    void CreateTree(const T& info, BinaryTree<T> & leftTree, BinaryTree<T> & rightTree); // 构造新树
    void PreOrder(BinaryTreeNode<T> *root); // 前序遍历二叉树或其子树
    void InOrder(BinaryTreeNode<T> *root); // 中序遍历二叉树或其子树
    void PostOrder(BinaryTreeNode<T> *root); // 后序遍历二叉树或其子树
    void PreOrderWithoutRecusion(BinaryTreeNode<T> *root); // 前序遍历二叉树或其子树用栈        
    void InOrderWithoutRecusion(BinaryTreeNode<T> *root); // 中序遍历二叉树或其子树用栈
    void PostOrderWithoutRecusion(BinaryTreeNode<T> *root); // 后序遍历二叉树或其子树用栈
    void LevelOrder(BinaryTreeNode<T> *root); // 按层次遍历二叉树或其子树
    void DeleteBinaryTree(BinaryTreeNode<T> *root); // 删除二叉树或其子树
};

void BinaryTreeNode<T>::Visit(BinaryTreeNode<T> *node){ // 访问结点
    
}

//---------------------------递归遍历二叉树----------------------------
void BinaryTree<T>::PreOrder(BinaryTreeNode<T> *root){ // 先序遍历
    if(root != NULL){
        Visit(root); // 访问结点
        PreOrder(root->leftchild()); // 先序遍历左子树
        PreOrder(root->rightchild()); // 先序遍历右子树
    }
}

void BinaryTree<T>::InOrder(BinaryTreeNode<T> *root){ // 中序遍历
    if(root != NULL){
        InOrder(root->leftchild()); // 中序遍历左子树
        Visit(root); // 访问结点
        InOrder(root->rightchild()); // 中序遍历右子树
    }
}

void BinaryTree<T>::PostOrder(BinaryTreeNode<T> *root){ // 后序遍历
    if(root != NULL){
        PostOrder(root->leftchild()); // 后序遍历左子树
        PostOrder(root->rightchild()); // 后序遍历右子树
        Visit(root); // 访问结点
    }
}
//----------------------------------------------------------------------


//---------------------------运用栈遍历二叉树---------------------------
void BinaryTree<T>::PreOrderWithoutRecusion(BinaryTreeNode<T> *root){ // 先序遍历
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

void BinaryTree<T>::InOrderWithoutRecusion(BinaryTreeNode<T> *root){ // 中序遍历
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

void BinaryTree<T>::PostOrderWithoutRecusion(BinaryTreeNode<T> *root){ // 后序遍历
    stack<BinaryTreeNode<T> *> aStack; // 工作栈
    BinaryTreeNode<T> * pointer = root; // 因为不能改变root指针的指向,所以用一个工作指针代替
    
}
//------------------------------------------------------------------------


