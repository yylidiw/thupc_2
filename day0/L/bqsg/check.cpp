#include<bits/stdc++.h>
using namespace std;
int main(int argc,char *argv[]){
  FILE* in0 = fopen(argv[1],"r");
  FILE* in1 = fopen(argv[2],"r");

  double a,b;
  fscanf(in0,"%lf",&a);
  fscanf(in1,"%lf",&b);

  printf("%.6f\n",a-b);
  fclose(in0);
  fclose(in1);
  if(fabs(a-b)>20){

    system((string("cp ./data.tmp ./lgw/") + to_string(a-b) + string(".tmp")).c_str());
  }
  return 0;
}