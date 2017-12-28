/*************************************************************************
  > File Name: Huffman.cpp
  > Author:何军
  > Sub: 哈夫曼树的构造
  > Created Time: 2017年11月27日 星期四 15时07分38秒
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
    T removeMin(); // 删除堆顶的最小元素
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
T MinHeap<T>::removeMin(){ // 删除堆顶的最小元素
    T tmp;
    removeNode(0, tmp); // 删除数组第一个
    return tmp;
}

template <typename T>
void MinHeap<T>::siftUp(int pos){ // 从pos向上开始调整,使序列成为堆
    int temppos = pos;
    T temp = heapArray[temppos]; // 得到当前需要调整的数值
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
        heapArray[i].element.print();
    }
}
//-------------------------------------------------------------------------------------------------------------------

//--------------------------------------字符和权值组成的集合------------------------------------------------
const int MAX_N = 30; // 最多的字符个数
typedef struct CH // 字符
{
  char c; // 编码的字符
  int weight; // 字符的权值
  int code; // 编码,是一个数字,后来用于转换成二进制数
  int n; // 编码长度
  string strcode; // 字符型编码
  void change(){ // 将code数字转换成对应的编码字符
      for (int i = n-1; i >= 0; --i)
      {
        printf("%d", (code >> i) & 1);
      }
  }
  string toString(){ // 变成字符串
    string info;
    string str;
    info += c;
    info += '\t';
    for (int i = n-1; i >= 0; --i)
    {
      int tmp = (code >> i) & 1;
      str += char(tmp+'0');
    }
    strcode = str; // 字符型编码
    info += str;
    info += '\n';
    return info;
  }
  bool operator <(const CH &ch){ // 重载小于运算符
    return weight < ch.weight;
  }
  bool operator >(const CH &ch){ // 重载大于运算符
    return weight > ch.weight;
  }
  void print(){ // 打印值
    if(c) cout << c << "--";
    cout  << weight << " ";
    //cout << " " << code << " " << n
  }
}CH;
//-------------------------------------------------------------------------------------------------------------------

//-------------------------------哈夫曼树结点的类----------------------------------------
template <typename T>
class HuffmanTreeNode
{
public:
  T element; // 元素
  HuffmanTreeNode<T> *left, *right; // 左,右孩子
  HuffmanTreeNode(){left = NULL; right = NULL;};
  bool operator >(const HuffmanTreeNode<T>& node); // 重载大于符号
  bool operator <(const HuffmanTreeNode<T>& node); // 重载小于符号
  ~HuffmanTreeNode(){}; // 删除指针
};
//--------------------------------------------------------------------------------------------------


//----------------------------------相关工具类(文件读取)-------------------------------------
void write(string path, string info){ // 将info写入path中,从文件末尾开始写
  ofstream in;
  in.open(path, ios::app);
  in << info;
  in.close();
}

string read(string path){ // 从path中读取字符串
  ifstream t(path);  
  stringstream buffer;  
  buffer << t.rdbuf();  
  string contents(buffer.str());  
  return contents;
}


int getHfmTree(CH *chs){
  string info = read("hfmTree.txt"); // 读取文件内容
  int pos = 0;
  for (int i = 0; i < info.length(); ++i)
  { 
    while((info[i] == '0' || info[i] == '1') && i < info.length()) { // 分解字符串
        chs[pos-1].strcode += info[i];
        i++;
    }
    if(info[i] == '\t' || info[i] == '\n') continue;
    else chs[pos++].c = info[i]; // 字符
  }
  return pos;
}

bool cmp(CH c1, CH c2){
  return c1.c < c2.c;
}

int binarySearch(CH *chs, int size, char key){ // 二分搜索
  int low = 0, high = size-1;
  while(low <= high) {
      int mid = (low+high)/2;
      if(chs[mid].c == key) return mid;
      if(chs[mid].c > key) high = mid-1;
      else low = mid+1;
  } 
  return -1;
}

char search(CH *chs, int size, string s){ // 查找
  for (int i = 0; i < size; ++i)
  {
    if(chs[i].strcode == s) return chs[i].c;
  }
  return ' ';
}
//---------------------------------------------------------------------------------------------------

//----------------------------------哈夫曼结点类的实现------------------------------------
template <typename T>
bool HuffmanTreeNode<T>::operator >(const HuffmanTreeNode<T>& node){ // 重载大于符号
  return element > node.element;
}

template <typename T>
bool HuffmanTreeNode<T>::operator <(const HuffmanTreeNode<T>& node){ // 重载大于符号
  return element < node.element;
}
//---------------------------------------------------------------------------------------------------------


//---------------------------------哈夫曼树的类------------------------------------------------
template <typename T>
class HuffmanTree
{
private:
  HuffmanTreeNode<T> *root; // 哈夫曼树的根
  void MergeTree(HuffmanTreeNode<T> &ht1, HuffmanTreeNode<T> &ht2,
  HuffmanTreeNode<T> *parent); // 把ht1和ht2合并成以parent作为根的树
public:
  HuffmanTree(){};
  HuffmanTree(T wetght[], int n); // weight[] 权值数组, n个字符
  HuffmanTreeNode<T>* getRoot(){return root;}
  void levelOrderAndEncoding(); // 层次遍历进行编码写入文件
  void print(HuffmanTreeNode<T> node); // 将已经在内存中的哈夫曼树以直观的方式（树或凹入表形式）显示在终端上
  void print();
  virtual ~HuffmanTree(){}; // 析构函数
};
//----------------------------------------------------------------------------------------------------

//------------------------------------哈夫曼树的定义实现----------------------------------
template<typename T>
HuffmanTree<T>::HuffmanTree(T weight[], int n){ // n个权值是weight的字符进行编码
  HuffmanTreeNode<T> *parent,firstChild,secondChild; // 父亲,第一个孩子,第二个孩子
  HuffmanTreeNode<T> *nodeList = new HuffmanTreeNode<T>[n]; // n个结点
  for (int i = 0; i < n; ++i) // 将n个结点插入最小堆
  {
    nodeList[i].element = weight[i];
  }
  MinHeap<HuffmanTreeNode<T> > heap(nodeList, n); // 定义最小堆
  for(int i = 0; i < n-1; i++){ // 构造哈夫曼树
      parent = new HuffmanTreeNode<T>; // 构造一颗树
      firstChild = heap.removeMin(); // 得到权值最小的两个结点
      secondChild = heap.removeMin();
      MergeTree(firstChild, secondChild, parent); // 归并两个子树
      heap.insertNode(*parent); // 将父亲结点插入堆中
      root = parent; // 根结点指向当前父亲结点
  }
  delete []nodeList; // 删除开辟的数组
}

template <typename T>
void HuffmanTree<T>::MergeTree(HuffmanTreeNode<T> &ht1, HuffmanTreeNode<T> &ht2, // 合并两个子树
  HuffmanTreeNode<T> *parent){
    parent->element.weight = ht1.element.weight + ht2.element.weight; // 父亲结点的值是两个孩子结点权值的和
    parent->left = new HuffmanTreeNode<T>; // 左孩子
    parent->right = new HuffmanTreeNode<T>; // 有孩子
    *(parent->left) = ht1; // 左孩子
    *(parent->right) = ht2; // 右孩子
}


/**
 * 层次遍历过程中可以知道当前结点是否有左右孩子
 * 每一层结点之间的距离不同.层数越低.结点之间的距离越宽.
 * 假设每一个需要打印的结点元素最多占m个空格
 * 第n层.第i个元素.
 */
template <typename T>
void HuffmanTree<T>::levelOrderAndEncoding(){ // 层次遍历进行编码
  CH chs[MAX_N]; // 编码数据储存,存当前的二进制数字和二进制数字的长度
  queue<HuffmanTreeNode<T> > que; // 使用队列
  HuffmanTreeNode<T> p; // 工作结点
  root->left->element.code = 0; // 左边是0
  root->right->element.code = 1; // 右边是1
  que.push(*root); // 第一个结点入队列
  int n = 1; // 当前层数
  int cur = 1, next = 0; // 这一层的结点数,下一层的结点数目
  int pos = 0; // 位置下
  while(!que.empty()) {
      p = que.front(); que.pop(); // 得到队头结点
      cur--;
      if(p.left == NULL && p.right == NULL) {chs[pos++] = p.element;} // 叶子结点
      if(p.left != NULL) {if(n != 1) {p.left->element.n = n; p.left->element.code = (p.element.code << 1);} que.push(*(p.left));   next++;} // 左结点入队
      if(p.right != NULL) {if(n != 1) {p.right->element.n = n; p.right->element.code = (p.element.code << 1)+1;} que.push(*(p.right));  next++;} // 右结点入队
      if(cur == 0) {
        n++; // 层数加1
        cur = next; // 进入下一层
        next = 0; // 下一层的数目这时候是0
      }
  }
  // 打印每一个字符的编码结果
  for (int i = 0; i < pos; ++i)
  {
    chs[i].print();
    cout << " code=" << chs[i].code << "  ";
    chs[i].change();
    cout << "  n="<< chs[i].n << endl;
    write("hfmTree.txt", chs[i].toString()); // 写入文件
  }
}

template <typename T>
void HuffmanTree<T>::print(HuffmanTreeNode<T> node){ // 使用凹入表形式将已经在内存中的哈夫曼树以直观的方式显示在终端上,中序遍历
    printf("("); // 打印左括号
    node.element.print(); // 打印中间
    if(node.left == NULL) printf("NULL");
    else print(*(node.left)); // 打印左边
    printf(","); // 逗号隔开
    if(node.right == NULL) printf("NULL");
    else print(*(node.right)); // 打印左边
    printf(")"); // 打印右括号
}

template <typename T>
void HuffmanTree<T>::print(){ // 使用凹入表形式将已经在内存中的哈夫曼树以直观的方式显示在终端上
  queue<HuffmanTreeNode<T> > que; // 使用队列
  HuffmanTreeNode<T> p;
  que.push(*root); // 第一个结点入队列
  int n = 1; // 当前层数
  int cur = 1, next = 0; // 这一层的结点数,下一层的结点数目
  while(!que.empty()) {
      p = que.front(); que.pop(); // 得到队头元素
      p.element.print(); cur--;
      if(p.left != NULL) {que.push(*(p.left)); next++;}
      if(p.right != NULL) {que.push(*(p.right)); next++;}
      if(cur == 0) {
        cout << endl;
        n++; // 层数加1
        cur = next; // 进入下一层
        next = 0; // 下一层的数目这时候是0
      }
  }
}


//-------------------------------------------------------------------------------------------------------

//----------------------------------------------------整个哈夫曼程序的初始化----------------------------------
HuffmanTree<CH> Initialization(){ // 初始化
    freopen("data.txt", "r", stdin);
    CH chs[MAX_N];
    int n;
    cin >> n; // 输入n
    for (int i = 0; i < n; ++i)  // 输入权值
    {
        chs[i].c = cin.get(); // 输入字符
    }
    for (int i = 0; i < n; ++i)  // 输入权值
    {
        cin >> chs[i].weight;
    }
    HuffmanTreeNode<CH> a,b;
    HuffmanTree<CH> hfm(chs, n);
    hfm.levelOrderAndEncoding();
    return hfm;
}

void Encoding(){ // 用以建好的哈夫曼树（如不在内存，则从文件hfmTree中读入），对文件ToBeTran中的正文进行编码，然后将结果存入文件CodeFile中。
  CH chs[MAX_N];
  int pos = getHfmTree(chs); // 得到数组信息
  sort(chs, chs+pos, cmp); // 排序
  string info = read("ToBeTran.txt");
  string code; // 编码结果
  int cur;
  for (int i = 0; i < info.length(); ++i)
  { 
    cur = binarySearch(chs, pos, info[i]);
    code += chs[cur].strcode;
    code += ' ';
  }
  write("CodeFile.txt", code);
}

void Decoding(){ // 利用已经建好的哈夫曼树将文件CodeFile中的代码进行译码，结果存入文件TextFile中
  CH chs[MAX_N];
  int pos = getHfmTree(chs); // 得到数组信息
  string code = read("CodeFile.txt");
  string dstr; // 译码结果
  string tmp;
  for (int i = 0; i < code.length(); ++i)
  { 
    tmp = "";
    while(code[i] != ' ' && i < code.length()) {
        tmp += code[i];
        i++;
    }
    dstr += search(chs, pos, tmp);
  }
  write("TextFile.txt", dstr);
}


void Print(){ // 将文件CodeFile以紧凑格式显示在终端上，每行50个代码，同时将此字符形式的编码写入文件CodePrint中。
  string code = read("CodeFile.txt");
  int pos = 0;
  string codeprint;
  for (int i = 0; i < code.length(); ++i)
  {
    if(code[i] != ' ') {printf("%c", code[i]); codeprint += code[i]; pos++;}
    if(!(pos%50)) {printf("\n"); codeprint += '\n';} // 每行打印50个字符
  }
  write("CodePrint.txt", codeprint);
}

template <typename T>
void Treeprinting(HuffmanTree<T> hfm){ // 将已经在内存中的哈夫曼树以直观的方式（树或凹入表形式）显示在终端上，同时将此字符形式的哈夫曼树写入文件TreePrint中。
  hfm.print(); // 打印哈夫曼树(层次表)
  hfm.print(*(hfm.getRoot())); // 打印哈夫曼树(凹入表)
}



int main(){
  HuffmanTree<CH> hfm;
  hfm = Initialization(); // 得到初始化后的哈夫曼树
  Treeprinting(hfm);
  Encoding(); // 编码
  Decoding();
  Print();
  return 0;
}
