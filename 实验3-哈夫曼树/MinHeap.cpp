/*************************************************************************
    > File Name: MinHeap.cpp
    > Author:何军
        > Sub: 最小堆的定义
    > Created Time: 2017年11月27日 星期四 19时07分38秒
    n个元素序列{k1, k2... ki...kn},当且仅当满足下列关系时称之为堆：
(ki <= k2i+2, ki <= k2i+1)或者(ki >= k2i+2, ki >= k2i+1), (i = 1, 2, 3, 4... n/2)
 ************************************************************************/
#include <bits/stdc++.h>
using namespace std;

//-------------------------------最小堆类的定义---------------------------------------------------------
// const int MINHEAP_INIT_SIZE = 100;// 最小堆的初始分配量
// const int MINHEAPINCREMENT = 10; // 最小堆的空间分配增量
template <typename T>
class MinHeap // 最小堆的定义
{
private:
    T* heapArray; // 存放堆数据的数组
    int currentSize; // 当前堆中元素的数目
    int maxSize; // 堆能容纳的最大元素数目
    void buildHeap(); // 建立堆
public:
    MinHeap(T *a, const int n); // n是最大的元素数目
    virtual ~MinHeap(){delete []heapArray;}; // 析构函数把数组指针删除
    bool isLeaf(int pos) const; // 判断当前位置元素是不是叶子结点
    int leftChild(int pos) const; // 返回左孩子的位置
    int rightChild(int pos) const; // 返回右孩子的位置
    int parent(int pos) const; // 当前位置的父结点的位置
    bool removeNode(int pos, T& node); // 删除给定下标的元素
    bool insertNode(const T& newnode); // 向堆中加入元素newnode
    T & removeMin(); // 删除堆顶的最小元素
    void siftUp(int pos); // 从pos向上开始调整,使序列成为堆
    void siftDown(int pos); // 筛选法函数,参数pos表示开始处理的数组下标
    void printHeap(); // 打印
};
//-------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------最小堆的实现-----------------------------------------------
template <typename T>
void MinHeap<T>::buildHeap(){ // 建立堆,从第一个分支结点heapArray[currentSize/2-1]
                              // 开始，自底向下逐步把子树调整成堆
                              // 效率是O(n),堆有log(n)深
    // 从最后一个父亲结点开始.反复掉用筛选函数
    for (int i = currentSize/2-1; i >= 0; --i)
    {
        siftDown(i);
    }
}

template <typename T>
MinHeap<T>::MinHeap(T *a, const int n){ // n是最大的元素数目
    heapArray = new T[n]; // 开辟连续内存
    maxSize = n; // 最大容纳数量
    currentSize = n; // 当前长度是0
    for(int i = 0; i < n; i++) heapArray[i] = a[i];
    buildHeap(); // 建立最小堆
}

template <typename T>
bool MinHeap<T>::isLeaf(int pos) const{ // 判断当前位置元素是不是叶子结点
    return leftChild(pos)==-1 && rightChild(pos)==-1; // 左右孩子都没有
}

template <typename T>
int MinHeap<T>::leftChild(int pos) const{ // 返回左孩子的位置
    return (2*pos+1 < currentSize) ? 2*pos+1 : -1; // 左孩子下标,没有的话就返回-1
}

template <typename T>
int MinHeap<T>::rightChild(int pos) const{ // 返回右孩子的位置
    return (2*pos+2 < currentSize) ? 2*pos+2 : -1; // 左孩子下标,没有的话就返回-1
}

template <typename T>
int MinHeap<T>::parent(int pos) const{ // 当前位置的父结点的位置
    return (pos-1)/2;
}

template <typename T>
bool MinHeap<T>::removeNode(int pos, T& node){ // 删除给定下标的元素，并且得到删除位置的元素，O(logn)
    if (pos < 0 || pos >= currentSize) // 删除位置不合法
        return false;
    T temp = heapArray[pos]; // 得到这个位置的元素
    heapArray[pos] = heapArray[--currentSize]; // 把最后一个元素放在这个位置，同时把堆当前的大小减去1
    if (parent(pos) != -1 && heapArray[parent(pos)] > heapArray[pos]) // 父亲结点比当前结点大
    {
        siftUp(pos); // 把当前位置的元素向上筛选到合适位置
    } else siftDown(pos); // 父亲结点比当前位置的元素小，向下筛选
    node = temp; // 得到删除的元素的值
}

template <typename T>
bool MinHeap<T>::insertNode(const T& newnode){ // 向堆中加入元素newnode，O(logn)
    if (currentSize == maxSize) // 堆已经满了
        return false;
    heapArray[currentSize] = newnode; // 把新的元素放入堆中
    siftUp(currentSize); // 调整当前元素在合适的位置
    currentSize++; // 添加之后当前堆的大小加1
}

template <typename T>
T & MinHeap<T>::removeMin(){ // 删除堆顶的最小元素
    T tmp;
    removeNode(0, tmp); // 删除数组第一个
    return tmp;
}

template <typename T>
void MinHeap<T>::siftUp(int pos){ // 从pos向上开始调整,使序列成为堆
    int temppos = pos;
    int temp = heapArray[temppos]; // 得到当前需要调整的数值
    while((temppos > 0) && (heapArray[parent(temppos)] > temp)) { // 如果父亲结点比当前结点大
        heapArray[temppos] = heapArray[parent(temppos)]; // 父亲结点赋值成小的
        temppos = parent(temppos); // 向上继续进行调整
    }
    heapArray[temppos] = temp;
}

template <typename T>
void MinHeap<T>::siftDown(int pos){ // 筛选法函数,参数porays表示开始处理的数组下标
   int i = pos; // 父亲结点.需要下沉的元素下标
   int j = 2*i+1; // j指向左孩子
   T temp = heapArray[pos]; // 保存当前需要处理的元素
   while(j < currentSize) {
       if ((j < currentSize-1) && (heapArray[j] > heapArray[j+1])) j++; // 始终指向值最小的那个孩子
       if (temp > heapArray[j]) // 如果当前的结点值比他的孩子值要大
       {
       	heapArray[i] = heapArray[j]; // 孩子向上
       	i = j; // 重新开始从孩子的位置当作父亲进行调整
       	j = 2*i+1;
       }
       else break; // 不需要调整
   }
   heapArray[i] = temp; // 把数字放在了合适的位置
}

template <typename T>
void MinHeap<T>::printHeap(){
    for (int i = 0; i < currentSize; ++i)
    {
        cout << heapArray[i] << " ";
    }
    cout << endl;
}
//-------------------------------------------------------------------------------------------------------------------


int main(int argc, char const *argv[])
{
    int arr[] = {3, 5, 3, 0, 8, 6, 1, 5, 8, 6, 2, 4, 9, 4, 7, 0, 1, 8, 9, 7, 3, 1, 2, 5, 9, 7, 4, 0, 2, 6};
    int len = (int) sizeof(arr) / sizeof(*arr);
    cout << "len=" << len << endl;
    MinHeap<int> heap(arr, len);
    heap.printHeap();
    return 0;
}

