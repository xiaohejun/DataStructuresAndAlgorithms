/*************************************************************************
	> File Name: Joseph.cpp
	> Author:何军
       > Sub:运用单向循环链表解决
	> Created Time: 2017年11月02日 星期四 14时15分38秒
 ************************************************************************/

#include <iostream>
#include <cstdio>

using namespace std;

template <typename T>
class Link{ // 链表模板类
public:
    T data; // 数据域
    Link<T> * next; // 指向后继结点的指针

    Link(const T info,Link<T> * nextValue = NULL){ // 构造函数,结点数据域为传入的数据,指针域i默认值为空
        data = info;
        next = nextValue;
    }
    Link(Link<T> * nextValue = NULL){ // 为next指针赋值,默认是空
        next = nextValue;
    }
};

template <typename T>
class CircleLinkList: public Link<T>{ // 单向循环链表类继承链表模板类
private:
    Link<T> *head; // 头指针,不是头结点
    int cur; // 元素编号
    Link<T>* setPos(const int p); // 第p个元素指针
public:
    CircleLinkList(){}; //
    CircleLinkList(int s); // 构造函数
    ~CircleLinkList(){clear();}; // 析够函数

    bool isEmpty(); // 判断链表是否为空
    void clear(); // 将链表储存内容清空,成为空表
    int length(); // 返回当前链表的实际长度
    bool append(const T value); // 表尾添加一个元素
    bool insert(const int p, const T value); // 位置p上插入一个元素
    bool remove(const int p); // 删除位置p上的元素,表的长度减1
    bool getValue(const int p, T & value); // 返回位置p上的元素值
    bool getPos(int &p, const T value); // 查找值为value的元素
    void print(); // 打印链表值
};

// 打印链表
template <typename T>
void  CircleLinkList<T>::print(){
    if(isEmpty()) return;
    Link<T> *p = head->next;
    while(p){
        cout<< p->data << " ";
        p = p->next;
    }
    cout << endl;
}


template <typename T>  // 函数返回值是找到的结点指针
Link<T>* CircleLinkList<T>::setPos(const int i){
    int count = 0;
    if(i == -1) return head; // 头结点是-1的位置
    // 循环定位,若i的值是0则定位到第一个结点
    Link<T> *p = head->next;
    while(p != NULL && count < i){
        p = p->next; // 指针向下移动
        count++;
    }
    return p;
}

// 正向创建链表
template <typename T>
CircleLinkList<T>::CircleLinkList(int n){ // 构造函数,s为要输入的链表元素个数
    Link<T> *p,*q;
    T value;
    for(int i = 1; i <= n; i++){
        cur = i; // 记录序号
        cin >> value; // 输入数据
        p = new Link<T>(value);
        q = p;
        if(i == 1) head = p; // 记录第一个,因为一会儿要指回来
        q->next = p;
    }
    p->next = head; // 指回第一个
}

template <typename T>
bool CircleLinkList<T>::isEmpty(){ // 判断链表是否为空
    return head == NULL;
}

template <typename T>
void CircleLinkList<T>::clear(){ // 讲链表储存内容清空,成为空表
    if(isEmpty()) return;
    Link<T> *p,*q;
    p = head; // p记录head的下一个结点
    while(p != NULL){
        q = p; // 记录当前结点
        delete q; // 删除当前结点
        q = NULL;
        p = p->next; // 指针下移
    }
    head =  tail = NULL;
}

template <typename T>
int CircleLinkList<T>::length(){ // 返回链表的实际长度
    Link<T> *p = head->next; // 工作指针
    int len = 0;
    while(p != NULL){
        p = p->next; // 指针下移
        len++;
    }
    return len;
}

template <typename T>
bool CircleLinkList<T>::append(const T value){ // 在链表的表尾添加一个元素
    return (insert(length(), value)); // 在尾部插入
}


template <typename T>
bool CircleLinkList<T>::insert(const int i, const T value){ // 插入数据内容为value的新结点作为第i个结点(i从0开始),也就是说是往第i个结点的前面插入一个结点
    Link<T> *p,*q;

    if((p = setPos(i-1)) == NULL){ // p是第i个结点的前驱
        cout << "非法插入点" << endl;
        return false; // 插入失败
    }

    q = new Link<T>(value, p->next); // 创造一个结点对象,它的next域是p->next
    p->next = q; // 往p结点后面插入q
    if(p == tail) tail = q; // 插入点在链表尾部,插入结点成为新的链尾
    return true; // 插入成功
}


template <typename T>
bool CircleLinkList<T>::remove(const int i){ // 移走第i个元素
    Link<T> *p,*q;
    if((p = setPos(i-1)) == NULL || p == tail){ // 待删除结点不存在,给定的i的值大于当前中元素的个数
        cout << "非法删除点" << endl;
        return false;
    }
    q = p->next; // q就是要删除的结点
    if(q == tail){ // 要删除的结点是尾结点
        tail = p; // 尾结点变成q的前驱结点
        p->next = NULL; // 把尾指针的next域设置成空
    }
    else {
        p->next = q->next; // 前驱结点的next域指向要删除的结点的next域
    }
    delete q; // 释放结点q
    return true;
}


template <typename T>
bool CircleLinkList<T>::getValue(const int i, T & value){ // 查找第i个元素,并且把它的值给value
    Link<T> *p = head->next; // 工作指针
    int count= 0; // 记录个数
    if(i < 0 || p == NULL) return false; // i的值不合法,或者这是一个空链表
    while(p != NULL && count < i){ // 找到第i个元素
        p = p->next;
        count++;
    }
    value = p->data;
    return true;
}


template <typename T>
bool CircleLinkList<T>::getPos(int &i, const T value){ // 查找元素值是value的位置
    Link<T> *p = head->next; // 工作指针
    int count= 0; // 记录个数
    if(i < 0 || p == NULL) return false; // i的值不合法,或者这是一个空链表
    while(p != NULL && value != p->data){ // 一直向下找,直到找到或者链表遍历完成
        p = p->next;
        count++;
    }
    if(p->data == value) { // 成功找到
        i = count;
        return true;
    }
    return false;
}

// 主函数测试数据
int main(){ 
    freopen("in.txt", "r", stdin);
    int n; // 人数
    while(true){
        cout << "输入人数:" << endl;
        cout >> n;
        if(n<=0) break; // 控制退出条件
        cout << "依次输入 " << n << " 个人的密码值:" << endl;
        CircleLinkList<int> joseph(n); // 创建单向循环链表
        joseph.JosephVisit(n,m); // 进行模拟遍历 
    }

    fclose(stdin);
    return 0;
}

















