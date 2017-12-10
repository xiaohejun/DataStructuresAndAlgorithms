/*************************************************************************
	> File Name: LinkQueue.h
	> Author:何军
    > Sub:链式队列的创建
	> Created Time: 2017年11月13日 星期四 21时15分38秒
 ************************************************************************/

#include <LinkList.h> // 链表头文件

template <typename T>
class Queue // 队列的基础类，基础操作
{
public:
	void clear(); // 清空队列
	bool enQueue(const T elem); // 将元素elem入队，成功返回true
	bool deQueue(T& elem); // 返回队头元素并且删除,成功返回true
	bool getFront(T& elem); // 得到队头元素，不删除，成功返回true
	bool isEmpty(); // 队列是不是空的
};

template <typename T>
class LinkQueue:public Queue<T> // 链式栈类
{
private:
	int size; // 队列中当前元素个数
	Link<T>* front; // 队头指针
	Link<T>* rear; // 队尾指针
public:
	LinkQueue(){size=0; front=NULL; rear=NULL;}; // 空的构造函数
	LinkQueue(int size); // 创建队列实列
	~LinkQueue();	
};


template <typename T>
LinkQueue<T>::LinkQueue<T>(int s){ // 创建size大小的队列。也就是创建链表
	size = s;
    Link<T> *p=NULL,*q=NULL;
    T value;
    while(s--){
        cin >> value; // 输入数据
        q = p;
        p = new Link<T>(value); // 创建结点
        if(front == NULL) front = new Link<T>(value); // 创建第一个结点
        else q->next = p;
    }
    rear = p;
}


template <typename T>
bool LinkQueue<T>::enQueue(const T elem){ // elem入队 
	if(rear==NULL) { // 空队列
		front = new Link<T>*(elem,NULL); // 创建结点
	} else { // 添加元素
		rear->next = new Link<T>*(elem,NULL);
		rear = rear->next; // 队尾指针后移动
	}
	size++;
	return true;
}

template <typename T>
bool LinkQueue<T>::deQueue(T& elem){ // 返回队头元素并且删除
	Link<T>* tmp;
	if(size == 0 ) { // 队列是空的
		cout << "队列为空！" << endl;
		return false;
	}
	elem = front->data; // 得到数据
	tmp = front; // 开始删除队头
	front = front->next; // 队头指针下移
	delete emp;
	if(front==NULL){ // 如果队列删除完了
		rear==NULL;
	}
	size--;
	return true;
}

template <typename T>
bool getFront(T& elem){ // 得到队头元素，不删除，成功返回true
	if(size == 0 ) { // 队列是空的
		cout << "队列为空！" << endl;
		return false;
	}
	elem = front->data; // 得到数据
	return true;
} 

template <typename T>
bool isEmpty(){ // 队列是不是空的
	return size == 0;
}