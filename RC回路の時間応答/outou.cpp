#include<iostream>
#include<fstream>
#include <cstdio> 
#include<cstring>
#include<cstdlib>
using namespace std;

int main(){
    const int R=10000, V=50;
    const double C=0.00001, dt=0.001;
    //各定数の設定//
    double t=0;
    double Vc=0;
    double i= V/R;
    //各変数の設定//
    fstream file;
    file.open("outou.dat");
    //出力するファイルの設定&オープン//
    while(t<1){
        i=(V-Vc)/R;
        Vc = Vc + (i/C)*dt;
        file<<t<<" "<<Vc<<" "<<i<<endl;
        t=t+dt;        
    }
    file.close();
    return 0;
}