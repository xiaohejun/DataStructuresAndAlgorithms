/*************************************************************************
    > File Name: SequenceLinkList.cpp
    > Author: 何军
    > Sub: 线性表的顺序表示和实现
    > Created Time: 2017年11月20日 星期一 09时06分41秒
 ************************************************************************/
#include <iostream>
#include<cstdio>
using namespace std;

const int LIST_INIT_SIZE = 100;// 线性表的初始分配量
const int LISTINCREMENT = 10; // 线性表的空间分配增量

template <typename T>
class SequenceLinkList{ // 顺序结构实现线性表
private:
    T* elem; // 元素
    int length; // 长度
    int listsize; // 当前分配的储存容量
public:
    SequenceLinkList(){elem = new T[LIST_INIT_SIZE]; listsize = LIST_INIT_SIZE; length = 0;} // 空的
    SequenceLinkList(int s); // 构造函数.构造指定大小的顺序结构
    ~SequenceLinkList(){delete []elem;} // 析够函数,释放指针
    bool isEmpty(); // 判断顺序表是否为空
    int getLength(); // 返回当前书寻表的长度
    bool append(const T value); // 表尾添加一个元素
    bool insert(const int p, const T value); // 位置p上插入一个元素
    bool remove(const int p); // 删除位置p上的元素,表的长度减1
    bool getValue(const int p, T & value); // 返回位置p上的元素值
    int getPos(const T value); // 查找值为value的元素在的位置
    void print(); // 打印顺序表值
    void josephVisit(int n,int m); // 进行约瑟夫遍历
};


// 打印顺序表
template <typename T>
void  SequenceLinkList<T>::print(){
    if(isEmpty()) return;
    for (int i = 0; i < length; ++i)
    {
        cout << elem[i] << " ";
    }
    cout << endl;
}

// 创建指定大小的顺序表
template <typename T>
SequenceLinkList<T>::SequenceLinkList(int n){ // 构造函数,s为指定大小
    elem = new T[n];
    listsize = n;
    for (int i = 0; i < n; ++i) // 输入数据
    {
        cin >> elem[i];
    }
    length = n;
}



template <typename T>
bool SequenceLinkList<T>::isEmpty(){ // 判断链表是否为空
    return length == 0;
}


template <typename T>
int SequenceLinkList<T>::getLength(){ // 返回链表的实际长度
    return length;
}

template <typename T>
bool SequenceLinkList<T>::append(const T value){ // 在链表的表尾添加一个元素
    return (insert(length()-1, value)); // 在尾部插入
}


template <typename T>
bool SequenceLinkList<T>::insert(const int i, const T value){ // 插入数据内容为value的新结点作为第i个结点(i从0开始),也就是说是往第i个结点的前面插入一个结点
    if(i < 0 || i > length) return false;
    if(length >= listsize){ // 空间不足
        elem = (T*)realloc(elem, (listsize+LISTINCREMENT)*sizeof(T));
    }
    for(int j = length-1; j >= i; j--){
        elem[j+1] = elem[j];
    }
    elem[i] = value;
    length++;
    return true;
}


template <typename T>
bool SequenceLinkList<T>::remove(const int i){ // 移走第i个元素
    if(i < 0 || i > length-1) return false;
    for(int j = i; j < length; j++){
        elem[j] = elem[j+1];
    }
    length--;
    return true;
}


template <typename T>
bool SequenceLinkList<T>::getValue(const int i, T & value){ // 查找第i个元素,并且把它的值给value
    if(i >= 0 && i < length){
        value = elem[i];
        return true;
    }
    return false;
}


template <typename T>
int SequenceLinkList<T>::getPos(const T value){ // 查找元素值是value的位置.前提是元素值不重复
    for (int i = 0; i < length; ++i)
    {
        if(elem[i]==value) return i;
    }
    return -1;
}

template <typename T>
void SequenceLinkList<T>::josephVisit(int n, int m){ // 进行约瑟夫遍历
    int len = length;
    print(); // 打印最初的状态
    int pos = 0;
    int i;
    while(len) { // 直到顺序表长度是0
        pos--;
        for (i = 0; i < m; ++i) // 开始报数字
        {
            pos++;
            if(pos==len) pos = 0; // 重头来
            cout << elem[pos] << " ";
        }
        cout << endl;
        cout << "cur=" << elem[pos].getCur() << " ";
        cout << endl;
        m = elem[pos].getData(); // m的值更新
        remove(pos);
        //print();
        len--; // 长度减一
     }
    cout << endl;
}

//-------------------------------约瑟夫相关类------------------------------------------------
class Node // 结点类
{
private:
    int cur; // 编号
    int data; // 数据密码
    static int num; // 静态变量.记录原来的编号
public:
    Node(){cur=++num;  data=0;}
    friend istream & operator >> (istream &in,Node &n);
    friend ostream & operator << (ostream &out,Node &n);
    int getCur(){return cur;}
    int getData(){return data;}
    static void setNum(int n){num=n;}
};
int Node::num = 0;
istream & operator >> (istream &in, Node &n){ // 重载输入运算符
    in >> n.data;
    return in;
}
ostream & operator << (ostream &out,Node &n){ // 重在输出运算符号
    out << n.data;
    return out;
}
//--------------------------------------------------------------------------------------

// 主函数测试数据
int main(){
    freopen("joseph.txt", "r", stdin);
    int n,m; // 人数
    while(cin >> n >> m && n>0 && (m<=20)){
        Node::setNum(0); // 设置初始编号
        SequenceLinkList<Node> joseph(n); // 创建顺序表
        joseph.josephVisit(n,m); // 进行模拟遍历
    }
    fclose(stdin);
    return 0;
}
