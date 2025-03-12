#include <iostream>
#include "Tourism.h"

#include "fstream"
using namespace std;
void showMenu(){
    cout<<"======景区信息管理系统======"<<endl;
    cout<<"1.创建景区景点图"<<endl;
    cout<<"2.查询景点信息"<<endl;
    cout<<"3.旅游景点导航"<<endl;
    cout<<"4.搜索最短路径"<<endl;
    cout<<"5.铺设电路规划"<<endl;
    cout<<"0.退出系统"<<endl;
    cout<<"请输入操作编号：";
}


int main() {
    bool PRUnning = true;
    CTourism m_cTourism;
    while (PRUnning){
        showMenu();
        int choice;
        cin>>choice;
        switch (choice){
            case 1:
                m_cTourism.CreateGraph();
                break;
            case 2:
                m_cTourism.GetSpotInfo();
                break;
            case 3:
                m_cTourism.TravelPath();
                break;
            case 4:
                m_cTourism.FindShortPath();
                break;
            case 5:
                m_cTourism.DesignPath();
            case 0: PRUnning = false;
        }
    }
    cout<<"======谢谢使用======"<<endl;






    return 0;
}
