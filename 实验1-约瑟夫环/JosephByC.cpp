/****************************************
*
*	用C语言实现循环链表并且解决约瑟夫问题
*
******************************************/
#include <stdio.h>
#include <stdlib.h>

typedef struct people // 每一个人的结构体定义
{
	int pas; // 密码
	int cur; // 初始标号
}people;

#define OK 1
#define ERROR 0
typedef int Status;
typedef people Elemtype; // 数据类型

// 结点的定义
typedef struct Node
{
	Elemtype data; // 数据域
	struct Node *next; // 指针域
}Node,*DeList;



// 得到链表中的第i个元素
Node *getPos(DeList L, int i){
	Node *p = L; // 工作指针指向第一个元素
	int cur = 1;
	p = p->next;
	while(p != L) {
        cur++;
        if(cur == i) break;
	    p = p->next;
	}
	return p;
}

// 得到链表的长度
int getLen(DeList L){
	Node *p = L; // 工作指针指向第一个元素
	int len = 1;
	p = p->next;
	while(p != L) {
        len++;
	  p = p->next;
	}
	return len;
}

// 正向创建长度是n的循环链表
Status createDeList(DeList &L, int n){
      Node  *p, *q;
      L = p = (DeList)malloc(sizeof(Node)); // 第一个结点
      scanf("%d",&p->data.pas); // 输入第一个结点的值
      p->data.cur = 1;
      for(int i = 2; i <= n; i++) // 输入剩下的n-1个结点
      {
            q = p; // q指向下一个结点
            p = (DeList)malloc(sizeof(Node)); // 创建新的结点
            scanf("%d", &p->data.pas); // 输入结点的数据
            p->data.cur = i;
            q->next = p; // 上一个结点指向这个刚开辟的结点
      }
      p->next = L; // 指回第一个结点.构成单向循环链表
	return OK;
}

// 删除链表中的第i个结点
Status deleteNode(DeList &L,int i){
	int len = getLen(L);
	if(i < 1 || i > len) {printf("非法删除操作\n"); return ERROR;}
	Node *p,*q; // 两个工作结点
	if(i == 1) p = getPos(L, len); // 如果删除第一个结点,那么他的前驱结点是最后的一个结点
	else p = getPos(L, i-1); // 得到要删除结点的前驱结点
	q = p->next;
	p->next = q->next;
	delete q; // 删除结点
	if(i == 1) L = p->next;
	return OK;
}

// 遍历循环链表
Status visitDeList(DeList L){
    Node *p = L;
    printf("cur = %d  pas = %d\n", p->data.cur, p->data.pas); // 输出第一个
    p = p->next;
    while(p != L){
        printf("cur = %d  pas = %d\n", p->data.cur, p->data.pas);
        p = p->next;
    }
    return OK;
}

// 进行模拟约瑟夫遍历
void joseph(){
	//freopen("in.txt", "r", stdin);
	int n,m; // 输入n和m
	scanf("%d%d", &n,&m);
	DeList L;
	createDeList(L, n); // 创建循环链表
	int len = getLen(L);
	Node *p = L; // 工作指针
	int pos = 1; // 要删除的位置
	while(len) { // 直到链表长度是0
	    for (int i = 1; i < m; ++i) // 开始报数字
	    {   
	        if((p=p->next)==L) {pos = 1;} // 走了一遍
	        else pos++;
	    }
	    printf("cur = %d   ", p->data.cur); // 输出原来的位置
	    m = p->data.pas; // m的值更新
	    p = p->next;
	    deleteNode(L, pos);
	    len--; // 长度减一
	}
}


/*
输入数据:
	7 6
	3 1 7 2 4 8 4
运行结果
	cur = 6   cur = 1   cur = 4   cur = 7   cur = 2   cur = 3   cur = 5   
*/


int main(){
	joseph(); // 进行模拟约瑟夫遍历
	return 0;
}
