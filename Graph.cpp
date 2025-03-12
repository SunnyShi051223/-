//
// Created by 32874 on 2025/3/4.
//
#include "Graph.h"
#include <iostream>
#include <cstdio>
#include <iostream>
using namespace std;
#define MAX_WEIGHT 10000
#define MAX_VERTEX_NUM 20
#define MAX_NAME_LEN 20
#define MAX_DESC_LEN 1024

//初始化
void CGraph::Init(void){
    m_nVexNum= 0;
    for(int i=0;i<MAX_VERTEX_NUM;i++){
        for(int j=0;j<MAX_VERTEX_NUM;j++){
            m_aAdjMatrix[i][j] = 0;
        }
    }
}

//插入顶点
int CGraph::InsertVex(Vex sVex){
    if(m_nVexNum == MAX_VERTEX_NUM){
        cout<<"顶点数量已达到最大值"<<endl;
    }
    m_aVexs[m_nVexNum] = sVex;
    m_nVexNum++;
    return 0;
}

//插入边
int CGraph::InsertEdge(Edge sEdge){
    if(sEdge.vex1 < 0 || sEdge.vex1 >= m_nVexNum || sEdge.vex2 < 0 || sEdge.vex2 >= m_nVexNum){
        cout<<"顶点编号越界"<<endl;
        return -1;
    }
    m_aAdjMatrix[sEdge.vex1][sEdge.vex2] = sEdge.weight;
    m_aAdjMatrix[sEdge.vex2][sEdge.vex1] = sEdge.weight;
    return 0;
}

//查找点
Vex CGraph::GetVex(int v){
    return m_aVexs[v];
}

//查找边
int CGraph::FindEdge(int v,Edge aEdge[]){
    int count = 0;
    for(int i=0;i<m_nVexNum;i++){
        count++;
        if(aEdge[i].vex1 == v || aEdge[i].vex2 == v){
            return i;
        }
    }
    return count;
}

//获取顶点数量
int CGraph::GetVexnum(void){
    return m_nVexNum;
}

int CGraph::FindShortPath(int nVexStart, int nVexEnd, Edge apath[]) {
    int nShortDistance[MAX_VERTEX_NUM];
    int visited[MAX_VERTEX_NUM];
    int prev[MAX_VERTEX_NUM]; // 前驱节点数组

    // 初始化数组
    for (int i = 0; i < m_nVexNum; i++) {
        visited[i] = 0;
        nShortDistance[i] = INT_MAX;
        prev[i] = -1;
    }
    nShortDistance[nVexStart] = 0; // 起始点到自身距离为0

    // Dijkstra算法主循环
    for (int i = 0; i < m_nVexNum; i++) {
        // 找到未访问的最小距离顶点
        int minDist = INT_MAX;
        int u = -1;
        for (int j = 0; j < m_nVexNum; j++) {
            if (!visited[j] && nShortDistance[j] < minDist) {
                minDist = nShortDistance[j];
                u = j;
            }
        }

        if (u == -1) break; // 所有顶点已访问或不可达
        visited[u] = 1;

        // 更新相邻顶点
        for (int v = 0; v < m_nVexNum; v++) {
            if (!visited[v] && m_aAdjMatrix[u][v] != 0) { // 存在边
                int alt = nShortDistance[u] + m_aAdjMatrix[u][v];
                if (alt < nShortDistance[v]) {
                    nShortDistance[v] = alt;
                    prev[v] = u;
                }
            }
        }
    }

    // 检查终点是否可达
    if (nShortDistance[nVexEnd] == INT_MAX) {
        return -1; // 不可达
    }

    // 回溯路径
    int path[MAX_VERTEX_NUM];
    int current = nVexEnd;
    int pathLength = 0;
    while (current != -1) {
        path[pathLength++] = current;
        current = prev[current];
    }

    // 反转路径得到从起点到终点的顺序
    for (int i = 0; i < pathLength / 2; i++) {
        int temp = path[i];
        path[i] = path[pathLength - 1 - i];
        path[pathLength - 1 - i] = temp;
    }

    // 构建apath数组
    int nIndex = 0;
    for (int i = 0; i < pathLength - 1; i++) {
        apath[nIndex].vex1 = path[i];
        apath[nIndex].vex2 = path[i + 1];
        apath[nIndex].weight = m_aAdjMatrix[path[i]][path[i + 1]];
        nIndex++;
    }

    return nIndex; // 返回路径边的数量
}

void CGraph::DFS(int nVex,bool bVisited[],int &Index,PathList &pList){
    bVisited[nVex] = true;
    pList->vexs[Index++]=nVex;
    int nVexNum=0;
    for(int i=0;i<m_nVexNum;i++){
        if(bVisited[i]){
            nVexNum++;
        }
    }
    if(nVexNum == m_nVexNum){
        pList->next=(PathList)malloc(sizeof(Path));
        for(int i=0;i<m_nVexNum;i++){
            pList->next->vexs[i] = pList->vexs[i];
        }
        pList=pList->next;
        pList->next=NULL;
    }
    else{
        for(int i=0;i<m_nVexNum;i++){
            if(m_aAdjMatrix[nVex][i] != 0 && !bVisited[i]){
                DFS(i,bVisited,Index,pList);
                bVisited[i]= false;
                Index--;
            }
        }
    }

}

void CGraph::DFSTraverse(int nVex,PathList &pList){
    int nIndex=0;
    bool bVisited[MAX_VERTEX_NUM] = {false};
    DFS(nVex,bVisited,nIndex,pList);
}

int CGraph::FindMinTree(Edge apath[]) {
    int nMinTree[MAX_VERTEX_NUM];
    int parent[MAX_VERTEX_NUM];
    int visited[MAX_VERTEX_NUM];

    for (int i = 0; i < m_nVexNum; i++) {
        nMinTree[i] = INT_MAX;
        visited[i] = 0;
        parent[i] = -1;
    }
    nMinTree[0] = 0;

    for (int i = 0; i < m_nVexNum - 1; i++) {
        int min = INT_MAX;
        int minIndex = -1;
        for (int j = 0; j < m_nVexNum; j++) {
            if (!visited[j] && nMinTree[j] < min) {
                min = nMinTree[j];
                minIndex = j;
            }
        }
        if (minIndex == -1) {
            return -1;
        }
        visited[minIndex] = 1;
        for (int k = 0; k < m_nVexNum; k++) {
            if (m_aAdjMatrix[minIndex][k] != 0 && !visited[k] && m_aAdjMatrix[minIndex][k] < nMinTree[k]) {
                nMinTree[k] = m_aAdjMatrix[minIndex][k];
                parent[k] = minIndex;
            }
        }
    }
    int index=0;
    for (int i = 1; i < m_nVexNum; i++) {
        apath[index].vex1 = parent[i];
        apath[index].vex2 = i;
        apath[index].weight = m_aAdjMatrix[parent[i]][i];
        index++;
    }
    if(index!=m_nVexNum-1){
        return -1;
    }
    return index;
}
