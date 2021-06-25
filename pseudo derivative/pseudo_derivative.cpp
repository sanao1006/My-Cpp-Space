#include <cstdio>
#include <bitset>
#include <cstdlib> 
#include <cmath>
#include<cstring>
int main(void){
  const double dt = 0.00000001;//sampling time
  double t = 0;
  double A=0;
  double B=0;
  double x=0;
  double y=0;
  double omegac = 100000000;
  FILE *file;
  char data[100];    
  strcpy(data,"pseudo_derivative.dat");
  file = fopen(data,"w"); 
  
  while(t < 0.00001){
    A=x-B;
    x = 0.0000001 * sin(1000000 * t);// as you like
    y = A * omegac;
    B += y * dt;
  
    fprintf(file,"%.8f %f\n",t,y);
    t += dt;
  }
  fclose(file);
  return 0;
  }
