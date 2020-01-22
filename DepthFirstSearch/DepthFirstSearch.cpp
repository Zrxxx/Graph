// DepthFirstSearch.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include<vector>
using std::vector;
struct edge {
	int begin;
	int end;
	edge(int a, int b) { begin = a; end = b; }
};
const int msize = 6;
int adjmatrix[msize][msize];
vector<edge> edges;
int num[msize] = {0,0,0,0,0,0};
int t = 1;

int zeronumCheck() {
	for (int i = 0; i < msize; ++i) {
		if (num[i] == 0) {
			return i;				//存在顶点未访问时返回该顶点的下标索引
		}
	}
	return -1;						//所有顶点已访问返回-1
}

void DFS(int i) {
	num[i] = t++;
	for (int j = 0; j < msize; ++j) {
		if (adjmatrix[i][j] > 0 && num[j] == 0) {
			std::cout << j << "->";
			edges.push_back(edge(i, j));
			DFS(j);
		}
	}
}
void depthFirstSearch() {
	int first = zeronumCheck();	//返回第一个一个未访问过的顶点
	num[first] = t++;		//标记该点为已访问
	while (first != -1)
	{
		for (int i = 0; i < msize; ++i) {
			if (adjmatrix[first][i] > 0 && num[i] ==0) {   //邻接矩阵中存在该边，且边的另一个端点未访问
				edges.push_back(edge(first, i));
				DFS(i);
			}
		}
		first = zeronumCheck();
		if (first != -1) {
			first = t++;
		}
	}
}




int main()
{
	for (int i = 0; i < msize; ++i) {
		for (int j = 0; j < msize; ++j) {
			std::cin >> adjmatrix[i][j];			//输入是否有要求
		}
	}
	depthFirstSearch();
	std::cout << "深度遍历:" << std::endl;
	for (int i = 0; i < edges.size(); ++i) {
		std::cout << "(" << edges[i].begin << "," << edges[i].end << ")";
	}
	std::cout << std::endl;
	for (int i = 0; i < msize; ++i) {
		std::cout << num[i] << " ";
	}
}

/*
0 0 1 1 1 1
0 0 0 0 0 1
1 0 0 1 1 0
1 0 1 0 1 0
1 0 1 1 0 0
1 1 0 0 0 0
深度遍历:
(0,2)(2,3)(3,4)(0,5)(5,1)
1 6 2 3 4 5
*/

