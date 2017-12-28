#include <bits/stdc++.h>

using namespace std;

//---------------------------------邻接表作为储存结构表示图------------------------------------------
#define MAX_VERTEX_NUM 40 // 最多结点数目定义
typedef int InfoType; // 结点的编号数据类型
typedef string VertexType; // 结点的信息数据类型

typedef struct ArcNode{ // 结点
	int adjvex; // 终点
	struct ArcNode *nextarc; // 下一个指向
	InfoType info; // 这条边的信息,存权值
	ArcNode(int adj, InfoType i):adjvex(adj), info(i){nextarc = NULL;} // 构造函数
	void print(){
        cout << adjvex << "  " << info << endl;
	}
}ArcNode;

typedef struct VNode{
	VertexType data; //
	ArcNode *firstarc; // 第一条边,相当于头节点
	ArcNode *lastarc; // 最后一条边,相当于尾结点
	VNode(){firstarc = NULL; lastarc = NULL;} // 无参构造函数,将两个指针设置成空
	void pusn_back(ArcNode *node){ // 在这个链表后面加一个结点
        if(firstarc == NULL) firstarc = node; // 如果头指针是空
        else lastarc->nextarc = node; // 头指针不是空
        lastarc = node; // 移动尾指针
	}
	void print(){
        cout << data;
	}
}VNode, AdjList[MAX_VERTEX_NUM];

typedef struct ALGraph{
	AdjList vertices; // 链表数组
	int vexnum, arcnum; // 结点数目,边的数目
	int kind; // 图的种类,0代表有向图,1代表无向图
}ALGraph;


/**
 * 创建以邻接表作为储存结构的图
 */
void CreateALGraph(ALGraph &G){
    int from,to; // 边的起点到终点的边号
    InfoType info;
	scanf("%d", &G.vexnum); // 输入结点数
	scanf("%d", &G.arcnum); // 输入边的数目
	scanf("%d", &G.kind); // 输入图的种类
	for(int i = 1; i <= G.vexnum; i++){ // 输入每一个结点的信息,这里输入城市的名称
		cin >> G.vertices[i].data;
	}
	ArcNode *node; // 一个链表结点
	// 输入边
	for(int i = 1; i <= G.arcnum; i++){
        scanf("%d%d%d", &from, &to, &info); // from->to花费cost
        node = new ArcNode(to, info); // 开辟一个链表结点
        G.vertices[from].pusn_back(node); // 在相应位置插入结点
        if(G.kind == 1) { // 如果是无向图
            node = new ArcNode(from, info); // 开辟一个链表结点
            G.vertices[to].pusn_back(node); // 在相应位置插入结点
        }
	}
}

bool visited[MAX_VERTEX_NUM]; // 是否访问过这个结点


void DFS(ALGraph G, int v){ // 深度优先搜索
	visited[v] = true; // 访问
	G.vertices[v].print();
	for(ArcNode *it = G.vertices[v].firstarc; it != NULL; it = it->nextarc){ // 深度优先
        int cur = it->adjvex;
        if(!visited[cur]) DFS(G, cur); // 如果没有访问过这个结点,就从这个结点开始访问
	}
}

/**
 * 建立深度优先生成树并打印
 */
void CreateDFSTree(ALGraph G){
	for(int i = 1; i <= G.vexnum; i++) visited[i] = false; // 所有结点的状态设置成没有访问过
	for(int v = 1; v <= G.vexnum; v++){ // 从每一个结点开始深度优先搜索
		if(!visited[v]) DFS(G, v);
	}
}

/**
 * 建立广度优先生成树并且打印
 */
void CreateBFSTree(ALGraph G){
	int curnum = 1, nextnum = 0; // 这一层的数目,下一层的数目
	for(int i = 1; i <= G.vexnum; i++) visited[i] = false; // 所有的点初始状态都是没有访问过
	queue<VNode> que; // 初始化队列
	VNode u;
	for(int v = 1; v <= G.vexnum; v++){ // 遍历所有结点
	    if(!visited[v]) { // 如果没有访问过
	        visited[v] = true; // 访问
	        que.push(G.vertices[v]); // 把这个结点入栈
	        while(!que.empty()){ // 直到队列不是空的
	            u = que.front(); que.pop(); // 取得队头
	            for(ArcNode *it = u.firstarc; it != NULL; it = it->nextarc){ // 遍历这个链表
                       int cur = it->adjvex; // 得到u为起点,it->adjvex作为终点的边号
	                if(!visited[cur]) { // 如果没有访问过,访问
	                    visited[cur] = true;
	                    que.push(G.vertices[cur]); nextnum++; // 下一层的数目加一
	                }
	            }
	        }
	    }
	}
}
//------------------------------------------------------------------------

int main()
{
	freopen("in.txt", "r", stdin);
	ALGraph G;
	CreateALGraph(G);
	CreateDFSTree(G);
	return 0;
}