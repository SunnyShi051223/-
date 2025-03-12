//
// Created by 32874 on 2025/3/4.
//
#include "iostream"
#include <string>
#include <cstdio>
#include "Graph.h"
#include "Tourism.h"
using namespace std;

#define VEX_FILE_NAME "vex.txt"
#define EDGE_FILE_NAME "edge.txt"

void CTourism::CreateGraph(void){
    cout<<"=====创建景区地图======"<<endl;
    m_cGraph.Init();
    FILE *pVex = fopen(VEX_FILE_NAME,"r");
    if(pVex == NULL){
        cout<<"景点文件不存在"<<endl;
        return;
    }
    int spotNum=0;
    fscanf(pVex,"%d",&spotNum);
    cout<<"景点数量："<<spotNum<<endl;
    Vex sVex;
    while(fscanf(pVex,"%d\n%s\n%s\n",&sVex.num,sVex.name,sVex.desc)!=-1){
        cout<<sVex.num<<" "<<sVex.name<<endl;
        if(m_cGraph.InsertVex(sVex)){
            cout<<"插入景点失败"<<endl;
            break;
        }
    }
    fclose(pVex);

    FILE *edge = fopen(EDGE_FILE_NAME,"r");
    if(edge == NULL){
        cout<<"边文件不存在"<<endl;
    }
    int edgeNum=0;
    Edge sEdge;
    cout<<"========边======="<<endl;
    while(fscanf(edge,"%d%d%d",&sEdge.vex1,&sEdge.vex2,&sEdge.weight)!=-1){
        Vex sVex1 = m_cGraph.GetVex(sEdge.vex1);
        Vex sVex2 = m_cGraph.GetVex(sEdge.vex2);
        cout<<sVex1.name<<" - "<<sVex2.name<<" "<<sEdge.weight<<"m"<<endl;
        if(m_cGraph.InsertEdge(sEdge)){
            cout<<"插入边失败"<<endl;
            break;
        }
    }
    fclose(edge);



}

void CTourism::GetSpotInfo(void){
    cout<<"=====获取景点信息======"<<endl;
    int flag=0;
    cout<<"景点编号\t景点名称\t景点描述"<<endl;
    for(int i=0;i<m_cGraph.GetVexnum();i++){
        cout<<m_cGraph.GetVex(i).num<<"\t\t"<<m_cGraph.GetVex(i).name<<"\t\t"<<m_cGraph.GetVex(i).desc<<endl;
        flag=1;
    }
    if(flag==0){
        cout<<"景点信息为空"<<endl;
        cout<<"请先创建景区地图！！！！！"<<endl;
        return;
    }

}

void CTourism::TravelPath(void){
    cout<<"=====旅游景点导航======"<<endl;
    int flag=0;
    int vexNum = m_cGraph.GetVexnum();
    for(int i=0;i<vexNum;i++){
        Vex sVex = m_cGraph.GetVex(i);
        cout<<sVex.num<<"-"<<sVex.name<<endl;
        flag=1;
    }
    if(flag==0){
        cout<<"景点信息为空"<<endl;
        cout<<"请先创建景区地图！！！！！"<<endl;
        return;
    }
    cout<<"请输入起始景点编号"<<endl;
    int start;
    cin>>start;
    PathList pList =(PathList)malloc(sizeof(Path));
    PathList pHead = pList;
    m_cGraph.DFSTraverse(start,pList);
    cout<<"导航路线为："<<endl;
    int i=1;
    pList=pHead;
    while(pList->next){
        Vex sVex = m_cGraph.GetVex(pList->vexs[0]);
        cout<<"路线："<<i++<<": "<<sVex.name;
        for(int j=1;j<vexNum;j++){
            sVex = m_cGraph.GetVex(pList->vexs[j]);
            cout<<"->"<<sVex.name;
        }
        cout<<endl;
        pList = pList->next;
    }
    free(pList);
    pList=NULL;
    pHead=NULL;
}

void CTourism::FindShortPath(void){
    cout<<"=====旅游景点导航======"<<endl;
    int nVexNum= m_cGraph.GetVexnum();
    for(int i=0;i<nVexNum;i++){
        Vex svex=m_cGraph.GetVex(i);
        cout<<svex.num<<"-"<<svex.name<<endl;
    }
    cout<<"请输入起点"<<endl;
    int start;
    cin>>start;
    cout<<"请输入终点"<<endl;
    int end;
    cin>>end;
    Edge *path = (Edge*)malloc(sizeof(Edge)*m_cGraph.GetVexnum());
    int PathNum= m_cGraph.FindShortPath(start,end,path);
    Vex Vex = m_cGraph.GetVex(path[0].vex1);
    int sum=0;
    cout<<"最短路径为："<<Vex.name;
    for(int i=0;i<PathNum;i++){
        sum+=path[i].weight;
        Vex = m_cGraph.GetVex(path[i].vex2);
        cout<<"->"<<Vex.name;
    }
    cout<<endl;
    cout<<"最短距离为："<<sum<<endl;
    free(path);
    path=NULL;
}

void CTourism::DesignPath(void) {
    cout<<"=====铺设电路规划======"<<endl;
    Edge *path = (Edge*)malloc(sizeof(Edge)*m_cGraph.GetVexnum());
    int PathNum= m_cGraph.FindMinTree(path);
    int sum=0;
    if(PathNum==-1){
        cout<<"景点之间没有通路"<<endl;
        return;
    }
    cout<<"在以下两个景点铺设道路"<<endl;
    for(int i=0;i<PathNum;i++){
        sum+=path[i].weight;
        cout<<m_cGraph.GetVex(path[i].vex1).name<<" - "<<m_cGraph.GetVex(path[i].vex2).name<<" "<<path[i].weight<<"m"<<endl;
    }
    cout<<"铺设电路总长度为："<<sum<<"m"<<endl;
    free(path);
    path=NULL;
}