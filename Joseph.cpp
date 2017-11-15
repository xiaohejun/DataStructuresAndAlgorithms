/*************************************************************************
	> File Name: Joseph.cpp
	> Author:何军
       > Sub:运用单向循环链表解决
	> Created Time: 2017年11月02日 星期四 14时15分38秒
 ************************************************************************/

#include <iostream>
#include <cstdio>

using namespace std;


// 主函数测试数据
int main(){ 
    freopen("in.txt", "r", stdin);
    int n,m; // 人数
    while(cin >> n >> m && n>0 && (m<=20)){
        CircleLinkList<int> joseph(n); // 创建单向循环链表
        joseph.josephVisit(n,m); // 进行模拟遍历 
    }
    fclose(stdin);
    return 0;
}

















