#include <bits/stdc++.h>
using namespace std;


//---------------------------------邻接多重表储存---------------------
#define MAX_VERTEX_NUM 40 // 最多结点数目定义
typedef int InfoType; // 结点的编号数据类型
typedef string VertexType; // 结点的信息数据类型

typedef struct EBox{ // 边
	bool mark; // 访问标志
	int ivex, jvex; // 这条边依附的两个顶点的位置
	struct EBox *ilink, *jlink; // ·分别指向依附这两个结点的下一条边
	InfoType info; // 这条边的信息,存权值
	EBox(){ // 初始化一条边,from->to花费cost
		mark = false; // 标记边没有访问过
		ilink = NULL; jlink = NULL; // 两个指针赋值成空
	}
	void print(){
		cout << ivex << "   " << jvex << "   " << info << endl;
	}
}EBox;


typedef struct VexBox{ // 每一个结点
	VertexType data; // 结点的信息,结点名称
	EBox *firstedge; // 第一条边
	VexBox(){firstedge = NULL;} // 指针赋值成空
}VexBox;


typedef struct{ // 邻借多重表的定义
	VexBox adjmulist[MAX_VERTEX_NUM];
	int vexnum, edgenum; // Î结点数目,边的数目
}AMLGraph;




/**
 * 向图G中加入一条边e
 */
void InsertEdge(AMLGraph &G, EBox *e){ // 相当于在逆序创建链表
    e->ilink = G.adjmulist[e->ivex].firstedge; // e->ilink指向ivex的第一条边
    e->jlink = G.adjmulist[e->jvex].firstedge; // e->jlink指向jvex的第一条边
    G.adjmulist[e->ivex].firstedge = G.adjmulist[e->jvex].firstedge = e; // 这个两个的第一条边指向e
}

/**
 *	创建图
 */
void CreateAMLGraph(AMLGraph &G){
       //freopen("in.txt", "r", stdin);
	int from, to, cost;
	scanf("%d", &G.vexnum); // 输入结点数目
	scanf("%d", &G.edgenum); // 输入边的数目
	for(int i = 1; i <= G.vexnum; i++){ // 输入每一个结点的名称,也就是每一个城市的名称
		cin >> G.adjmulist[i].data;
		//cout << G.adjmulist[i].data << endl;
	}
	for (int i = 1; i <= G.edgenum; ++i) // 输入编号是from到to权值是cost的边,输入顺序是from < to.从编号最大的开始开始起点输入
	{					// 因为加入边的时候是相当于链表的逆序创建
		scanf("%d%d%d", &from, &to, &cost);
		EBox* e = new EBox; // 边
		e->ivex = from; e->jvex = to; e->info = cost;
		InsertEdge(G, e); // 将边加入图
	}
}

bool visited[MAX_VERTEX_NUM]; // 结点访问标志
string  DFSRES; // 深度优先搜索的序列
string  BFSRES; // 宽度优先搜索的序列

/**
 * 访问图G中的*e边,将状态设置成flag
 */
void Visit(AMLGraph G, EBox *e){
	int ivex = e->ivex; // 左端点
	int jvex = e->jvex; // 右端点
	cout << ivex << "(" << G.adjmulist[ivex].data << ") <----> " << jvex << "(" << G.adjmulist[jvex].data << ")" << endl;
	e->mark = true; // 标记这条边访问过
}

/**
 * 点vi的下一条边.
 */
void NextEdge(AMLGraph G, int vi, EBox *p, int &vj, EBox *&q){
	if(p->ivex == vi) { q = p->ilink; vj = p->jvex;} // 如果左端点是vi,那么向下
	else {q = p->jlink; vj = p->ivex;} // 不是,向右
}

/**
 * // 从编号是v的结点开始进行宽度优先遍历
 * @param G 图
 * @param v 结点编号,从1开始的
 */
void BFSTraverse(AMLGraph G, int v){
	BFSRES = ""; // 初始化答案字符串
	memset(visited, false, sizeof(visited)); // 将每一个结点的状态设置成没有访问过
	EBox *e = G.adjmulist[v].firstedge; // 先指向第一条边
 	if(e == NULL) {cout << "编号是: " << v << " 结点信息是: " << G.adjmulist[v].data << " 没有相关联的边!" << endl; return;} // 如果这个结点没有依附的边
 	cout << "从编号是: " << v << "(" << G.adjmulist[v].data << ") 开始进行宽度优先搜索!" << endl;
 	queue<int> que; // 工作队列,装结点编号
 	que.push(v); // v入队列
 	int vx;
 	visited[v] = true; BFSRES += '(' + G.adjmulist[v].data + ')' + "-->";
 	while(!que.empty()) { // 直到队列不是空的
        v = que.front(); que.pop(); // 得到队头的元素
        e = G.adjmulist[v].firstedge;
 	    while(e) { // 直到空
            vx = e->ivex == v ? e->jvex : e->ivex; // 得到另一个端点
 	        if(!visited[vx]) { // 如果这个结点没有访问过入队列
                Visit(G, e); // 访问边
                visited[vx] = true; // 标记这个结点访问过
                BFSRES += '(' + G.adjmulist[vx].data + ')' + "-->";
                que.push(vx);
            }
 	        NextEdge(G, v, e, vx, e); // 下一条边
 	    }
 	}
 	BFSRES += "Finished";
 	cout << BFSRES << endl; // 输出结果
}


/**
 * 深度搜索,将搜索过的状态设置成flag
 */
void DFS(AMLGraph G, int v){
    int vx;
    EBox *e = G.adjmulist[v].firstedge; // 得到当前的第一条边
    DFSRES +=  '(' + G.adjmulist[v].data + ')' + "-->"; // 访问序列
    visited[v] = true; // 标记这个结点访问过
    while(e) { // 直到空
        vx = e->ivex == v ? e->jvex : e->ivex; // 得到另一个端点
        if(!visited[vx]) {Visit(G, e); DFS(G,vx);}// 如果没有访问过,访问这个结点
        NextEdge(G, v, e, vx, e); // 下一条边
    }
}

/**
 * 进行深度优先搜索
 */
void DFSTraverse(AMLGraph G, int v){ // 从编号是v的结点开始进行深度优先遍历
	DFSRES = "深度优先搜索访问顺序是:  ";
	EBox *e = G.adjmulist[v].firstedge; // 得到第一条边
	if(e == NULL) {cout << "编号是: " << v << " 结点信息是: " << G.adjmulist[v].data << " 没有相关联的边!" << endl; return;} // 如果这个结点没有依附的边
	cout << "从编号是: " << v << "(" << G.adjmulist[v].data << ") 开始进行深度优先搜索!" << endl;
	memset(visited, false, sizeof(visited)); // 设置结点全部没有访问过
	visited[0] = true; // 0号没有存,所以设置成true
	int i = v;
	while(true){
		if(!visited[i]) DFS(G, i);
		if(++i%G.vexnum == v) break;
	}
	cout << (DFSRES += "Finished") << endl; // 输出序列
}

/**
 * 运用栈进行深度优先搜索
 * 算法描述：
 *      1.栈初始化
 *      2.输出起始顶点v；起始顶点v设置成已经访问过。起始点v入栈
 *      3.重复下列操作直到栈空
 *          3.1取栈顶元素v（不出栈）
 *          3.2栈顶元素v存在邻接点
 *              3.2.1输出顶点vx  
 *              3.2.2访问vx
 *              3.2.3vx入栈
 *          3.3不存在邻接点，出栈一个元素
 */ 
void DFSTraverseWtihStack(AMLGraph G, int v){
	DFSRES = "深度优先搜索访问顺序是(运用栈):  ";
	EBox *e = G.adjmulist[v].firstedge; // 得到第一条边
	if(e == NULL) {cout << "编号是: " << v << " 结点信息是: " << G.adjmulist[v].data << " 没有相关联的边!" << endl; return;} // 如果这个结点没有依附的边
	cout << "从编号是: " << v << "(" << G.adjmulist[v].data << ") 开始进行深度优先搜索!" << endl;
	memset(visited, false, sizeof(visited)); // 设置结点全部没有访问过
	stack<int> st; // 工作栈
	st.push(v); // 结点入栈
	visited[v] = true; // 标记这个结点访问过
	DFSRES += '(' + G.adjmulist[v].data + ')' + "-->";
	int vx;
	while(!st.empty()){ // 直到栈空
		v = st.top(); // 得到栈顶元素
		e = G.adjmulist[v].firstedge;
		while(e){ // 知道得到的边是空的
            vx = e->ivex == v ? e->jvex : e->ivex; // 得到另外一个端点
            if(!visited[vx]) { // 如果这个点没有访问过
                Visit(G, e); // 访问这条边
                visited[vx] = true; // 标记这个点访问过
                DFSRES += '(' + G.adjmulist[vx].data + ')' + "-->";
                st.push(vx); // 把这个点入栈
                break;
            }
            NextEdge(G, v, e, vx, e); // 得到下一条边
		}
		if(e == NULL) st.pop(); // 出栈
	}
	cout << (DFSRES += "Finished") << endl; // 输出序列
}



//-----------------------------------------------------------------------------------------------------------

int main()
{
	freopen("in.txt", "r", stdin);
	AMLGraph G;
	CreateAMLGraph(G);
	int s = 1; // 起点
	BFSTraverse(G, s);
	DFSTraverse(G, s);
	DFSTraverseWtihStack(G, s);
	return 0;
}

