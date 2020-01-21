/*
部分概念：
残存网络：
对于流网络的一条边e，边e的流量是f(e),将其进行双向分解，原方向的边在残存网络的值slack是 c(e)-f(e),反向的边在残存网络的值slack是 f(e)。

FordFulkerson算法流程：
	每条边e需要记录容量值 c(e) ,当前边流向的流量 f(e) , 残存量 c(e)-f(e),当前边的反向的流量 f'(e), f'(e) = f(e)  根据残存图的定义
	每个点u需要做标记：  如果该点作为前向边v->u的终点，其标记值为 min( c(vu)-f(vu), label(v))，
						 如果该点作为后向边 v->u的终点，其标记值为 min( f(vu), label(v))。

	标记源点s为（null,ifinity），并将源点放入已检查集合，只要已检查的集合labeled[]不为空，对该集合中一点的邻接点中未访问过的点设置标记
	并进行类似深度优先遍历，当遍历到汇点t时即表示找到一条增广路，从t的标记残留值开始将每条边的流量进行增加，并将labeled[]中重置为只有源点s,
	当遍历结果不能到t，则找到最大路最小割。
*/
#include "pch.h"
#include <iostream>
#include <vector>
using std::vector;
/* 示例：  输出最大流23
	0	1	2	3	4	5	
0	0	16	13	0	0	0	
1	0	0	0	12	0	0	
2	0	4	0	0	14	0	
3	0	0	9	0	0	20	
4	0	0	0	7	0	4
5	0	0	0	0	0	0
*/
const int msize = 6;
const int infinity = 10000;


//记录结点的标记，前驱点和残存量
struct node {
	int pre;
	int slack;
	node(int a = -1, int b = 0) { pre = a; slack = b; }
};

int adjmatrix[msize][msize] = { {0,16,13,0,0,0},		//存储边容量信息
								{0,0,0,12,0,0},
								{0,4,0,0,14,0},
								{0,0,9,0,0,20},
								{0,0,0,7,0,4},
								{0,0,0,0,0,0} };

int flow[msize][msize];					//各边的流量
node label[msize];						//存储结点的标记
vector<int> labeled;					//记录该顶点是否已经标记


bool isforwardedge(int pre, int post) {
	if (adjmatrix[pre][post] > 0) {
		return  1;
	}
	else if (adjmatrix[post][pre] > 0) {
		return 0;
	}
}
int slack(int pre, int post) {

}
void FordFulkersonAlgorithm() {
	label[0].pre = -1;
	label[0].slack = infinity;
	labeled.push_back(0);
	while (!labeled.empty())
	{
		node temp = labeled.back();
		int i = temp.

		for (int i = 0; i < msize; i++) {
			if (adjmatrix[0][i] > 0 &&label[i].slack>0) {		//访问顶点s的所有未标记邻接顶点
				if (isforwardedge(0, i)) {
					label[i].pre = 0;
					label[i].slack = slack(0, i);
				}
				else {
					label[i].
				}
			}
		}
	}
}
