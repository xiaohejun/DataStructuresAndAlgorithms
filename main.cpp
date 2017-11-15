#include <iostream>

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

//-----------------------链表实现队列-------------------------------------------------------------------
template <typename T>
class LinkQueue// 链式栈类
{
private:
	int size; // 队列中当前元素个数
	Link<T>* front; // 队头指针
	Link<T>* rear; // 队尾指针
public:
    LinkQueue(){size=0; front = NULL; rear = NULL;}; // 空的构造函数
	LinkQueue(int size); // 创建队列实列
	~LinkQueue(){clear();}; // 清空队列	
	void clear(); // 清空队列
	bool enQueue(const T elem); // 将元素elem入队，成功返回true
	bool deQueue(T& elem); // 返回队头元素并且删除,成功返回true
	bool getFront(T& elem); // 得到队头元素，不删除，成功返回true
	bool isEmpty(); // 队列是不是空的
};


template <typename T>
LinkQueue<T>::LinkQueue(int s){ // 创建size大小的队列。也就是创建链表
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
		front = new Link<T>(elem,NULL); // 创建结点
        rear = front; // 头和尾是同一个
	} else { // 添加元素
		rear->next = new Link<T>(elem,NULL);
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
	delete tmp;
	if(front==NULL){ // 如果队列删除完了
		rear==NULL;
	}
	size--;
	return true;
}

template <typename T>
bool LinkQueue<T>::getFront(T& elem){ // 得到队头元素，不删除，成功返回true
	if(size == 0 ) { // 队列是空的
		cout << "队列为空！" << endl;
		return false;
	}
	elem = front->data; // 得到数据
	return true;
} 

template <typename T>
bool LinkQueue<T>::isEmpty(){ // 队列是不是空的
	return size == 0;
}


template <typename T>
void LinkQueue<T>::clear(){ // 清空队列
    if(size==0) return; // 本来就是空的
    int e;
    while(size){
        deQueue(e); // 依次出栈.就是删除了   
    }
}
//--------------------------------------------------------------------------------------

//-------------------------------顺序栈的实现------------------------------------------------
const int STACK_INIT_SIZE = 100; // 栈的初始大小
const int STACKINCREMENT = 10; // 储存空间分配增量 


template <typename T>
class ArrStack // 顺序栈
{
private:
	int size; // 栈的大小
	int top; // 栈顶位置，应该小于size
	T *elem; // 栈中元素
public:
	ArrStack(){ // 创建默认大小的栈
		size = 0; top = -1; elem = new T[STACK_INIT_SIZE];
	}
	~ArrStack(){delete []elem;} // 析构函数释放空间
	void clear() { top = -1; } // 清空栈
	int getSize(){return this.size;} // 栈的大小
	bool push(const T item); // 入栈，成功返回true,失败返回false
	bool pop(T& item); // 得到栈顶内容并且弹出
	bool getTop(T& item); // 得到栈顶内容但是不弹出
	bool isEmpty(); // 栈是不是空的
};

template <typename T>
bool ArrStack<T>::push(T item){ // 把元素压入栈
	if(top == size-1) { // 栈满了
		elem = (T*) realloc(elem, sizeof(T)*(STACK_INIT_SIZE+STACKINCREMENT));
	}
	elem[++top] = item; // 栈可以装,top指针上移动一个位置
	size++;
	return true;
}

template <typename T>
bool ArrStack<T>::pop(T& elem){ // 出栈弹出
	if(getTop(elem)) {top--; size--; return true;} // 出栈
	else return false;
}

template <typename T>
bool ArrStack<T>::getTop(T& item){ // 得到栈顶内容但是不弹出
	if(top == -1) { // 栈空
		cout << "栈空！" << endl;
		return false;
	} else {
		item = elem[top]; // 得到元素,顶部指针不动
		return true;
	}
} 

template <typename T>
bool ArrStack<T>::isEmpty(){ // 栈是不是空的
	return top==-1;
}

//--------------------------------------------------------------------------------------

int main(int argc, char const *argv[])
{	
	
	return 0;
}
