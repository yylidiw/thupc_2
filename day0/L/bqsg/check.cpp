#include<bits/stdc++.h>

int main(int argc,char *argv[]){
  FILE* in0 = fopen(argv[1],"r");
  FILE* in1 = fopen(argv[2],"r");

  double a,b;
  fscanf(in0,"%lf",&a);
  fscanf(in1,"%lf",&b);

  printf("%.6f, %.6f, %.6f\n",a,b,fabs(a-b));
  fclose(in0);
  fclose(in1);
  return 0;
}