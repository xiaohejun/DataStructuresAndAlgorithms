/*************************************************************************
    > File Name: CircleLinkList.h
    > Author:何军
       > Sub:单向循环链表
    > Created Time: 2017年11月02日 星期四 14时15分38秒
 ************************************************************************/


template <typename T>
class Link{ // 链表模板类
public:
    T data; // 数据域
    int cur; // 下标
    Link<T> * next; // 指向后继结点的指针

    Link(const T info,const int i,Link<T> * nextValue = NULL){ // 构造函数,结点数据域为传入的数据,指针域i默认值为空
        data = info;
        cur = i;
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
  //  Link<T>* setPos(const int p); // 第p个元素指针
public:
    CircleLinkList(){}; //
    CircleLinkList(int s); // 构造函数
    ~CircleLinkList(){clear();}; // 析够函数
    Link<T>* setPos(const int p); // 第p个元素指针
    bool isEmpty(); // 判断链表是否为空
    void clear(); // 将链表储存内容清空,成为空表
    int length(); // 返回当前链表的实际长度
    bool append(const T value); // 表尾添加一个元素
    bool insert(const int p, const T value); // 位置p上插入一个元素
    bool remove(const int p); // 删除位置p上的元素,表的长度减1
    bool getValue(const int p, T & value); // 返回位置p上的元素值
    int getPos(const T value); // 查找值为value的元素
    void print(); // 打印链表值
    void josephVisit(int n,int m);
};

// 打印链表
template <typename T>
void  CircleLinkList<T>::print(){
    if(isEmpty()) return;
    Link<T> *p = head->next;
    while(p != head){
        cout<< p->cur << "=" << p->data << " ";
        p = p->next;
    }
    cout << endl;
}

// 正向创建链表
template <typename T>
CircleLinkList<T>::CircleLinkList(int n){ // 构造函数,s为要输入的链表元素个数
    head = new Link<T>();
    head->next = head; // 自己指向自己,形成循环
    Link<T> *p,*q;
    T value;
    for (int i = 1; i <= n; ++i)
    {
        cin >> value; // 输入数据
        q = p;
        p = new Link<T>(value,i); // 创建结点
        if(head->next == head) head->next = p;
        else q->next = p;
    }
    p->next = head;
}



template <typename T>
bool CircleLinkList<T>::isEmpty(){ // 判断链表是否为空
    return head->next == head;
}

template <typename T>
void CircleLinkList<T>::clear(){ // 讲链表储存内容清空,成为空表
    Link<T> *p,*q;
    p = head->next; // p记录head的下一个结点
    while(p != head){
        q = p; // 记录当前结点
        delete q; // 删除当前结点
        q = NULL;
        p = p->next; // 指针下移
    }
    delete head;
    head = NULL;
}

template <typename T>
int CircleLinkList<T>::length(){ // 返回链表的实际长度
    Link<T> *p = head->next; // 工作指针
    int len = 0;
    while(p != head){
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
    if((p = setPos(i-1)) == head){ // p是第i个结点的前驱
        cout << "非法插入点" << endl;
        return false; // 插入失败
    }
    q = new Link<T>(value, p->next); // 创造一个结点对象,它的next域是p->next
    p->next = q; // 往p结点后面插入q
    return true; // 插入成功
}


template <typename T>  // 函数返回值是找到的结点指针
Link<T>* CircleLinkList<T>::setPos(const int i){
    int count = 0;
    if(i == 0) return head; // 头结点是0的位置
    // 循环定位,若i的值是0则定位到第一个结点
    Link<T> *p = head->next;
    while(p != head && count < i-1){
        p = p->next; // 指针向下移动
        count++;
    }
    return p;
}


template <typename T>
bool CircleLinkList<T>::remove(const int i){ // 移走第i个元素
    if(isEmpty() || i<=0 || i>length()) {cout << "非法删除点" << endl; return false;} // 空的话不能删除
    Link<T> *p,*q;
    p = setPos(i-1); // 要删除的结点位置的前驱结点
    q = p->next; // q就是要删除的结点
    p->next = q->next; // 前驱结点的next域指向要删除的结点的next域
    delete q; // 释放结点q
    return true;
}


template <typename T>
bool CircleLinkList<T>::getValue(const int i, T & value){ // 查找第i个元素,并且把它的值给value
    Link<T> *p = head->next; // 工作指针
    int count= 0; // 记录个数
    if(i == 0 || p == head) return false; // i的值不合法,或者这是一个空链表
    while(p != head && count < i-1){ // 找到第i个元素
        p = p->next;
        count++;
    }
    value = p->data;
    return true;
}


template <typename T>
int CircleLinkList<T>::getPos(const T value){ // 查找元素值是value的位置.前提是元素值不重复
    Link<T> *p = head->next; // 工作指针
    int count= 1; // 记录个数
    if(p == head) {return 0;} // 这是一个空链表
    while(p != head && value != p->data){ // 一直向下找,直到找到或者链表遍历完成
        p = p->next;
        count++;
    }
    if(p->data == value) { // 成功找到
        return count;
    }
    return -1;
}

template <typename T>
void CircleLinkList<T>::josephVisit(int n, int m){ // 进行约瑟夫遍历
    bool update = false; // 判断pos有没有更新
    int len = length();
    Link<T> *p = head; // 定位到第0个结点.
    int pos = 1; // 要删除的位置
    print();
    while(len) { // 直到链表长度是0
        pos--;
        for (int i = 1; i <= m; ++i) // 开始报数字
        {   
            pos++;
            if((p=p->next)==head) {p = p->next; pos = 1;} // 跳过头结点
            cout << p->data << " "; // 输出报数字的顺序
        }
        cout << "\n" << endl;
        cout << "cur=" << p->cur << " " << endl;
        //cout << "p->data=" << m << endl;
       // cout << "m=" << m << " pos=" << pos << " cur=" << p->cur;
        m = p->data; // m的值更新
        remove(pos);
        //print();
        len--; // 长度减一
      //  cout << " len=" << len << endl;
     }
    cout << endl;
}