//
// Created by 32874 on 2025/3/4.
//

#ifndef GRAPHCPRO_GRAPH_H
#define GRAPHCPRO_GRAPH_H

typedef struct Path{
    int vexs[20];
    Path *next;
}*PathList;

//顶点结构体
struct Vex{
    int num;
    char name[20];
    char desc[1024];
};

//边结构体
struct Edge{
    int vex1;
    int vex2;
    int weight;
};

//图
class CGraph{
public:
    CGraph(void){

    }
    ~CGraph(void){

    }

private:
    Vex m_aVexs[20];//顶点数组
    int m_nVexNum;//顶点个数
    int m_aAdjMatrix[20][20];//邻接矩阵

public:
    void Init(void);//初始化
    int InsertVex(Vex sVex);//插入顶点
    int InsertEdge(Edge sEdge);//插入边
    Vex GetVex(int v);//获取顶点
    int FindEdge(int v,Edge aEdge[]);//查找边
    int GetVexnum(void);//获取顶点个数
    int FindShortPath(int nVexStart,int nVexEnd,Edge apath[]);
    void DFS(int nVex,bool bVisited[],int &Index,PathList &pList);//深度优先搜索
    void DFSTraverse(int nVex,PathList &pList);//深度优先遍历
    int FindMinTree(Edge apath[]);
};


#endif //GRAPHCPRO_GRAPH_H
