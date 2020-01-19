// TopologicalSort.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include<cstring>
#include<string>
using namespace std;

const int maxs = 4;
int adjmatrix[maxs][maxs];
int indegree[maxs];
string ver = "abcdefgh";

void topologicalSort(int adjmatrix[maxs][maxs],int indegree[maxs]) {
	for (int i = 0; i < maxs; ++i) {
		//对所有顶点，每次找出入度为0的点
		for (int j = 0; j < maxs; ++j)
		{	//遍历所有顶点找出入度为0的顶点
			if (indegree[j] == 0) {
				cout << ver[j] << " ";
				--indegree[j];
				for (int k = 0; k < maxs; ++k) {
					if (adjmatrix[j][k] > 0) {
						--indegree[k];
					}
				}
			}
		}
	}

}
int main() {
	for (int i = 0; i < maxs; ++i) {
		for (int j = 0; j < maxs; ++j) {
			cin >> adjmatrix[i][j];
		}
	}
	for (int i = 0; i < maxs; ++i) {
		for (int j = 0; j < maxs; ++j) {
			if (adjmatrix[j][i] > 0) {
				++indegree[i];
			}
		}
	}
	topologicalSort(adjmatrix, indegree);
	
}