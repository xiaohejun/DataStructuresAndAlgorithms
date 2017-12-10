/*************************************************************************
	> File Name: Stack.cpp
	> Author:何军
    > Sub:顺序栈的实现
	> Created Time: 2017年11月13日 星期四 14时15分38秒
 ************************************************************************/


const int STACK_INIT_SIZE = 100; // 栈的初始大小
const int STACKINCREMENT = 10; // 储存空间分配增量 

template <typename T>
class Stack // 栈
{
public:
	Stack();
	~Stack();
	void clear(); // 清栈
	bool push(const T item); // 入栈，成功返回true,失败返回false
	bool pop(T& item); // 得到栈顶内容并且弹出
	bool top(T& item); // 得到栈顶内容但是不弹出
	bool isEmpty(); // 栈是不是空的
};

template <typename T>
class ArrStack: public Stack<T> // 顺序栈
{
private:
	int size; // 栈的大小
	int top; // 栈顶位置，应该小于size
	T *elem; // 栈中元素
public:
	ArrStack(){ // 创建默认大小的栈
		size = 0; top = -1; elem = new T[STACK_INIT_SIZE];
	}
	ArrStack(){ // 无参数构造函数
		top = -1;
	}
	~ArrStack(delete []elem); // 析构函数释放空间
	void clear() { top = -1; } // 清空栈
	int size(){return size;} // 栈的大小
};

template <typename T>
bool ArrStack<T>::push(T elem){ // 把元素压入栈
	if(top == size-1) { // 栈满了
		elem = (T*) realloc(elem, sizeof(T)*(STACK_INIT_SIZE+STACKINCREMENT));
	}
	elem[++top] = item; // 栈可以装,top指针上移动一个位置
	size++;
	return true;
}

template <typename T>
bool ArrStack<T>::pop(T& elem){ // 出栈弹出
	if(top(elem)) {top--; size--; return true;} // 出栈
	else return false;
}

template <typename T>
bool ArrStack<T>::top(T& item){ // 得到栈顶内容但是不弹出
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
