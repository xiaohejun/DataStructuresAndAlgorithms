/**
 * 起泡排序、直接插入排序、简单选择排序、快速排序、希尔排序、堆排序
 * 6种排序算法的性能比较
 */

#include <bits/stdc++.h>
using namespace std;

#define MAXSIZE 1000 // 表的最大长度
#define SORTNUM 6 // 6种排序算法
typedef int KeyType; // 关键字的数据类型
typedef int InfoType; // 其他数据数据类型
//-----------排序算法的声明------------------------
void BubbleSort(int &c, int &s);
void InsertSort(int &c, int &s);
void SelectSort(int &c, int &s);
void QuickSort(int &c, int &s);
void ShellSort(int &c, int &s);
void HeapSort(int &c, int &s);
//--------------------------------------------------------
typedef void (*Func)(int &c, int &s);  // 函数指针
static Func Sorts[SORTNUM] = { // 6种排序算法的函数指针
	BubbleSort, InsertSort, SelectSort, QuickSort, ShellSort, HeapSort
};
static string SortNames[SORTNUM] = { // 6种排序算法的名称
	"起泡", "插入", "选择", "快排", "希尔", "堆排"
};

static int Mix[] = {0, 1, 4, 16, 64, 128, 256, 4096, 16384}; // 4的指数级打乱
//----------------------------------------数据表的定义------------------------------------------
typedef struct RedType // 记录的数据类型
{
	KeyType key; // 关键字
	InfoType otherinfo; // 其他信息
}RedType;

typedef struct SqList // 顺序表
{
	RedType r[MAXSIZE+1]; // r[0]闲置作为哨兵单位
	int len; // 表的长度
}SqList;

SqList ordata; // 原始数据
SqList data; // 进行操作的数据表
int compCount; // 比较次数
int shiftCount; // 移动次数
int len, groups; // 关键字表的长度和需要生成的测试数据组数
//---------------------------------------------------------------------------------------------------------

//--------------------------------------------数据的初始化和一些操作------------------------------

void printData(SqList data){ // 打印一下数据
	for(int i = 1; i <= data.len; i++) cout << data.r[i].key << " ";
	cout << endl;
}

bool Less(int i, int j){ // 关键字i的位置小于关键字j的位置的关键字
	compCount++; // 比较次数加1
	return data.r[i].key < data.r[j].key; // 返回比较结果
}

bool LessOrEqual(int i, int j){ // 关键字i小于等于j的位置的关键字
	compCount++; // 比较次数加1
	return i <= data.r[j].key; // 返回比较结果
}

bool BigOrEqual(int i, int j){ // 关键字i小于等于j的位置的关键字
	compCount++; // 比较次数加1
	return i >= data.r[j].key; // 返回比较结果
}

void Swap(int i, int j, SqList &data){ // 交换第i和第j位置的两个关键字位置
	RedType tmp; // 移动交换中间变量
	tmp = data.r[i]; data.r[i] = data.r[j]; data.r[j] = tmp; // 交换两个位置的元素
	shiftCount += 3; // 交换次数加3
}

void Shift(int i, int j){ // 将第j个位置的元素移动到第i个位置
	data.r[i] = data.r[j]; // 移动
	shiftCount++; // 移动次数加1
}

void InverseOrder(){ //  将原始数据数据逆序
	for(int i = 1; i <= ordata.len; i++) ordata.r[i].key = ordata.len-i+1;
}

void Copydata(SqList ordata, SqList &data){ // 将ordata中的数据复制到data中
	for(int i = 1; i <= ordata.len; ++i) data.r[i] = ordata.r[i];
	data.len = ordata.len;
}

void InitData(){ // 初始化长度是n的数据,生成关键字,生成一个正序序列
    for(int i = 1; i <= ordata.len; i++) ordata.r[i].key = i;
}

void RandomSqList(int d, bool isInverse){ // 将data作d级打乱,是否逆序,一开始生成的数据是正序
       int low = 1, high = data.len;
	if(isInverse) InverseOrder(); // 逆序
	else InitData();
	for(int i = 1; i <= Mix[d]; i++){ // 做d级打乱
        int x = low+rand()%(high-low+1), y = low+rand()%(high-low+1);
		Swap(x, y, ordata); // 随机交换两个位置的数据
	}
}

void BeforeSort(){ // 排序之前需要做的操作
	compCount = 0; shiftCount = 0; // 两个计数器清零
}

//---------------------------------------------------------------------------------------------------------

//--------------------------------------------排序算法的实现-----------------------------------------
void BubbleSort(int &c, int &s){ // 起泡排序(移动c次,交换s次)
	//cout << "BubbleSort" << endl;
	BeforeSort();
	bool hasSwap = true; // 是否存在交换的记录
	for(int i = 1; hasSwap ; i++){
		hasSwap = false;
		for(int j = data.len; j > i; j--){ // 从无序表后面往前比
			if(Less(j , j-1)){ // 如果后面的小
				Swap(j, j-1, data); // 交换
				hasSwap = true;
			}
		}
	}
	c = compCount; s = shiftCount;
}

void InsertSort(int &c, int &s){ // 插入排序(移动c次,交换s次)
	//cout << "InsertSort" << endl;
	BeforeSort(); // 两个计数器清0
	int i,j;
	for(i = 2; i <= data.len; i++){
		if(Less(i, i-1)){ // 如果i比i-1小,那就需要把i位置的放到i-1的位置上去
			Shift(0, i);  // 哨兵位置放置当前操作的元素的关键字
			Shift(i, i-1); // i的位置要小,把i-1往后移动
			for(j = i-2; Less(0, j); --j){ // 如果前面的比他大,直到找到比他>=的位置元素出现
				Shift(j+1, j); // 把前面大的往后移动
			}
			Shift(j+1, 0); // 找到正确的位置插入
		}
	}
	c = compCount; s = shiftCount; // 得到比较次数和移动次数
}

void SelectSort(int &c, int &s){ // 选择排序(移动c次,交换s次)
	//cout << "SelectSort" << endl;
	BeforeSort();
	int i,j,mincur; // 最小的下标
	for(i = 1; i < data.len; i++){
		mincur = i;
		for(j = i+1; j <= data.len; j++){ // 在无序表中找到最小的元素
			if(Less(j , mincur)) mincur = j; // 更新小的值下标
		}
		if( i != mincur) Swap(i, mincur, data); // 交换
	}
	c = compCount; s = shiftCount; // 得到比较次数和移动次数
}


int Partition(int low, int high){ // 得到划分的点的位置.这个位置的前后 不大(小)于它
	Shift(0, low); // 将low的位置作为枢轴
	int pivotkey = data.r[low].key; // 记录这个位置键值
	while(low < high) { // 直到low==high退出
	    while(low < high && LessOrEqual(pivotkey, high)) high--; // 调整把后面小的移动到pivotkey的前面
	    Shift(low, high); //  小的向前
	    while(low < high && BigOrEqual(pivotkey, low)) low++; // 大的向后
	    Shift(high, low);
	}
	Shift(low, 0); // 找到合适的位置放置pivotkey关键字
	return low;
}

void QSort(int low, int high){ // 将[low, high]进行快速排序
	int pivotloc; // 枢轴的位置
	//cout << "low= " << low << " high=" << high << endl;
      if(low < high) { // 表的长度大于1
        pivotloc = Partition(low, high); // 得到位置
		QSort(low, pivotloc-1); // 前面进行相同的操作
		QSort(pivotloc+1, high);// 后面进行相同的操作
	}
}

void QuickSort(int &c, int &s){ // 快速排序(移动c次,交换s次)
	//cout << "QuickSort" << endl;
	BeforeSort();
	QSort(1, data.len); // 快速排序
	c = compCount; s = shiftCount; // 得到比较次数和移动次数
}

void ShellInsert(int g){ // 相隔g距离的插入排序
	int i,j;
	for(i = g+1; i <= data.len; i++){
		if(Less(i, i-g)){ // 如果后面的小
			Shift(0, i); // 先将当前位置的移动到0
			Shift(i, i-g); // 把大的移动到后面
			for(j = i-g; j > 0 && Less(0, j); j-=g){
				Shift(j+g, j); // 大的往后移动
			}
			Shift(j+g, 0);
		}
	}
}

void ShellSort(int &c, int &s){ // 希尔排序(移动c次,交换s次)
	//cout << "ShellSort" << endl;
	BeforeSort();
	vector<int> G; // 生成增量序列 g(n+1) = 3g(n)+1; g(1) = 1;
	int g = 1;
	while(g < ordata.len) {
	    G.push_back(g);
	    g = (3*g+1);
	}
	for (int i = G.size()-1; i >= 0; --i)
	{
		ShellInsert(G[i]);
	}
	c = compCount; s = shiftCount; // 得到比较次数和移动次数
}

void ShiftDown(int s, int m){ // 从start开始向下筛选
	int j;
	Shift(0, s);
	for(j = 2*s; j <= m; j*=2){ // 向下筛选
		if(j < m && Less(j, j+1)) ++j; // 得到大的那个孩子
		if(!Less(0, j)) break; // 如果当前位置的大.退出
		Shift(s, j); s = j; // 小的话.向下找
	}
	Shift(s, 0);
}

void HeapSort(int &c, int &s){ // 起泡排序(移动c次,交换s次)
	//cout << "HeapSort" << endl;
	BeforeSort();
	for(int i = data.len/2; i > 0; --i){ // 建立最小堆
		ShiftDown(i, data.len); // 从最后一个根开始i向下筛选
	}
	for(int i = data.len; i >= 2; --i){
		Swap(1, i, data); // 和最后一个元素交换
		ShiftDown(1, i-1); // 调整
	}
	c = compCount; s = shiftCount; // 得到比较次数和移动次数
}



//-------------------------------------------主菜单的显示--------------------------------------------
void MainMenu(){ // 主菜单
	system("clear");
	cout << "\n关键字序列长度范围[2,1000]\t测试数据组数[2,18]\t输入 长度  组数\n";
	cin >> ordata.len >> groups;
	cout << "|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|\n";
	cout << "| 打乱 |\t\t\t比较次数\t\t\t\t\t|\t\t\t\t\t移动次数\t\t\t\t|\n| 程度 |";
	for(int i = 0; i < SORTNUM; i++) {
		if(i > 0) cout << "\t\t\t";
		else cout << "\t\t";
		cout << SortNames[i];
	}
	cout << "\t\t|\n|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|\n";
	int c,s;
	bool isInverse = false;
	int cur = 0;
	for(int i = 0; i < groups; i++){
		if(i >= 9) { isInverse = true; cur = groups-i-1; } else cur = i;
		if(i >= 9) printf("| -%d\t|", cur);
        	else printf("| +%d\t|", cur);
        	RandomSqList(cur%9, isInverse);
        	for(int j = 0; j < SORTNUM; j++){
        		Copydata(ordata, data); // 将生成的数据放到data中准备进行操作
        		(*Sorts[j])(c, s); // 排序
        		printf("\t%4d\t%4d\t|", c, s);
        	}
        	printf("\n");	
	}
}
//--------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------
/**
 * 主函数
 * @return [description]
 */
int main(){
	freopen("in.txt", "r", stdin);
	char cmd = 'c';
	//while(cmd == 'c') {
	    MainMenu();
	   // cout << "c(继续)  q(退出) ?" << endl; cin >> cmd;
	//}
	// int c,s; // 移动次数
	// len = 20; groups = 18;
	// srand((unsigned int)time(NULL));
	// for(int i = 0; i < groups; i++){
 //        RandomSqList(i, false);
 //        for(int i = 0; i < SORTNUM; i++) (*Sorts[i])(c, s);
	// }
	return 0;
}
