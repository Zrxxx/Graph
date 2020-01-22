残存网络：
对于流网络的一条边e，边e的流量是f(e),将其进行双向分解，原方向的边在残存网络的值slack是 c(e)-f(e),反向的边在残存网络的值slack是 f(e)。
1.残存网络中没有从s到t的路径时（其中某条边满载，在残存网络该边为0），最大流等于最小割容量。
2.残存网络中有从s到t的路径时，最大流不等于最小割容量
FordFulkerson算法流程：
	每条边e需要记录容量值 c(e) ,当前边流向的流量 f(e) , 残存量 c(e)-f(e),当前边的反向的流量 f'(e), f'(e) = f(e)  根据残存图的定义
	每个点u需要做标记：  如果该点作为前向边v->u的终点，其标记值为 min( c(vu)-f(vu), label(v))，
			 如果该点作为后向边 v->u的终点，其标记值为 min( f(vu), label(v))。    每次都是选最小值（最小割）标记，将标记值传递到汇点

	标记源点s为（null,ifinity），并将源点放入已检查集合，只要已检查的集合labeled[]不为空，将源点拿出，
	对该集合中一点的邻接点中未访问过的点设置标记、设置为已检查，并进行类似深度优先遍历，
	当遍历到汇点t时即表示找到一条增广路，从t的标记残留值开始将每条边的流量进行增加，并将labeled[]中重置为只有源点s,
	当遍历结果不能到t，则找到最大路最小割。
*/
#include "pch.h"
#include <iostream>
#include <vector>
#include <algorithm>
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
const int source = 0;
const int end = 5;

//记录结点的标记，前驱点和残存量
struct node {
	int pre;
	int slack;
	node(int a = -1, int b = 0) { pre = a; slack = b; } //源点初始化没有源点 pre = -1 ,残余量slack = 0
};

int adjmatrix[msize][msize] = { {0,16,13,0,0,0},		//存储边容量信息
				{0,0,0,12,0,0},
				{0,4,0,0,14,0},
				{0,0,9,0,0,20},
				{0,0,0,7,0,4},
				{0,0,0,0,0,0} };

int flow[msize][msize]{ {0,0,0,0,0,0},				//各边的起始流量
			{0,0,0,0,0,0},
			{0,0,0,0,0,0},
			{0,0,0,0,0,0},
			{0,0,0,0,0,0},
			{0,0,0,0,0,0}};					
node label[msize];			//存储结点的标记
bool labeledChecked[msize] = {0,0,0,0,0,0};//记录该顶点是否已经标记，书中已标记的顶点用栈结果push存入，但使用栈存入无法判断邻接顶点是否已经检查
vector<int> labeled[msize];		//便于检验
bool isempty() {
	for (int i = 0; i < msize; ++i) {
		if (labeledChecked[msize] != 0) {
			return 0;
		} }
	return 1;
}
bool isforwardedge(int pre, int post) {
	//前后向边的前提是原图中存在一条边关联pre ,post这俩个点，在残存网络中再进行双向分解
	if (labeledChecked[pre]==1&& labeledChecked[post] ==0) {
		/*if (adjmatrix[pre][post] > 0) {
			return 1;
		}
		else if (adjmatrix[pre][post] == 0) {
			return 0;
		}*/
		return 1;
	}
	else if (labeledChecked[pre] == 1 && labeledChecked[post] == 1) {
		return 0;
	}
	
}
int slack(int pre, int post) {
	if (isforwardedge(pre, post)) {
		return std::min((adjmatrix[pre][post] - flow[pre][post]), label[pre].slack);
	}
	else
	{
		return  std::min( flow[pre][post], label[pre].slack);
	}
}

void reset() {
	for (int i = 1; i < msize; ++i) {
		labeledChecked[i] = 0;
	}
	labeled->clear();
	labeled->push_back(0);
}
void augmentPath(int t) {
	int pre = label[t].pre;
	int post = t;
	while (pre!=-1)
	{
		if (isforwardedge(pre, t)) {
			flow[pre][post] += label[t].slack;
		}
		else
		{
			flow[pre][post] -= label[t].slack;
		}
		post = pre;
		pre = label[post].pre;
		
	}
	for (int i = 0; i < msize; i++)
	{
		for (int j = 0; j < msize; j++)
		{
			std::cout << flow[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void FordFulkersonAlgorithm() {
	label[0].pre = -1;			//源点没有父节点，设置为-1
	label[0].slack = infinity;		//源点的残余量为无穷大
	labeledChecked[0] = 1;			//源点设置为已检查
	labeled->push_back(0);
	while (!labeled->empty())	

	{
		std::cout << "开始遍历" << std::endl;			//测试
		int i = labeled->back();
		labeled->pop_back();
		for (int j = 1; j < msize ; ++j) {
			//若一条边在原图中存在，那么该边在残存网络中是双向的,只要存在adjmatrix[i][j] - flow[i][j] >0则该边可双向输入输出
			if(labeledChecked[j] == 0 && adjmatrix[i][j] - flow[i][j] > 0)
			{
				//访问顶点s的所有未访问邻接顶点
				std::cout << "进入未标记的临界点循环，正在处理结点： "<<j << std::endl;			//测试
				if (isforwardedge(i,j) && adjmatrix[i][j] - flow[i][j] > 0) { //当flow(i,j)=cap(i,j)时不进行标记
					label[j].pre = i;
					label[j].slack = slack(i, j);
					std::cout << "（正向边）更新结点 " << j << "  slack为：" << label[j].slack << std::endl;//测试
				}
				else if(!isforwardedge(i,j)){
					label[j].pre = i;
					label[j].slack = slack(i, j);
					std::cout << "（反向边）更新结点 " << j << "  slack为：" << label[j].slack << std::endl;//测试
				}
				if (end == j) {
						augmentPath(j);
						reset();
				}
				else {
					labeledChecked[j] = 1;
					labeled->push_back(j);

				}	
			}
		}
	}
}


int main() {
	for (int i = 0; i < msize; i++)
	{
		for (int j = 0; j < msize; j++)
		{
			std::cout << adjmatrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
	FordFulkersonAlgorithm();
	int sum = 0;
	for ( int i = 0; i < msize; i++)
	{
		for (int j = 0; j < msize; j++)
		{
			std::cout << flow[i][j] << " ";
			if (j == msize - 1) {
				sum += flow[i][j];
			}
		}
		std::cout << std::endl;
	}

	std::cout << "最大流为" << sum << std::endl;
}

/*
0 16 13 0 0 0
0 0 0 12 0 0
0 4 0 0 14 0
0 0 9 0 0 20
0 0 0 7 0 4
0 0 0 0 0 0
开始遍历
进入未标记的临界点循环，正在处理结点： 1
（正向边）更新结点 1  slack为：16
进入未标记的临界点循环，正在处理结点： 2
（正向边）更新结点 2  slack为：13
开始遍历
进入未标记的临界点循环，正在处理结点： 4
（正向边）更新结点 4  slack为：13
开始遍历
进入未标记的临界点循环，正在处理结点： 3
（正向边）更新结点 3  slack为：7
进入未标记的临界点循环，正在处理结点： 5
（正向边）更新结点 5  slack为：4
0 0 4 0 0 0
0 0 0 0 0 0
0 0 0 0 4 0
0 0 0 0 0 0
0 0 0 0 0 4
0 0 0 0 0 0
开始遍历
进入未标记的临界点循环，正在处理结点： 1
（正向边）更新结点 1  slack为：16
进入未标记的临界点循环，正在处理结点： 2
（正向边）更新结点 2  slack为：9
开始遍历
进入未标记的临界点循环，正在处理结点： 4
（正向边）更新结点 4  slack为：9
开始遍历
进入未标记的临界点循环，正在处理结点： 3
（正向边）更新结点 3  slack为：7
开始遍历
进入未标记的临界点循环，正在处理结点： 5
（正向边）更新结点 5  slack为：7
0 0 11 0 0 0
0 0 0 0 0 0
0 0 0 0 11 0
0 0 0 0 0 7
0 0 0 7 0 4
0 0 0 0 0 0
开始遍历
进入未标记的临界点循环，正在处理结点： 1
（正向边）更新结点 1  slack为：16
进入未标记的临界点循环，正在处理结点： 2
（正向边）更新结点 2  slack为：2
开始遍历
进入未标记的临界点循环，正在处理结点： 4
（正向边）更新结点 4  slack为：2				（4被删除，4已无其它路径可走）
开始遍历							(1已被访问，2被删除)
开始遍历							（vector中剩1）
进入未标记的临界点循环，正在处理结点： 3
（正向边）更新结点 3  slack为：12
开始遍历
进入未标记的临界点循环，正在处理结点： 5
（正向边）更新结点 5  slack为：12
0 12 11 0 0 0
0 0 0 12 0 0
0 0 0 0 11 0
0 0 0 0 0 19
0 0 0 7 0 4
0 0 0 0 0 0
开始遍历
进入未标记的临界点循环，正在处理结点： 1
（正向边）更新结点 1  slack为：4
进入未标记的临界点循环，正在处理结点： 2
（正向边）更新结点 2  slack为：2
开始遍历
进入未标记的临界点循环，正在处理结点： 4
（正向边）更新结点 4  slack为：2                  
开始遍历											
开始遍历											
0 12 11 0 0 0
0 0 0 12 0 0
0 0 0 0 11 0
0 0 0 0 0 19
0 0 0 7 0 4
0 0 0 0 0 0
最大流为23
*/
