#include <cstdio>
#include <cmath>
#include <iostream>
#include <cstdio>
#include <ctime>
#include<algorithm>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#ifndef M_PI_2
#define M_PI_2 1.5707963267948966
#endif
using namespace std;

const int MAXN=20000005;
const double EPS = 1e-9;

// io improver
namespace io {
  const int IBUFSZ = 50000000;
  const int OBUFSZ = 10000000;
  char ibuf[IBUFSZ];
  char obuf[OBUFSZ];
  char *it = ibuf, *ot = obuf;
  char outbuf[21];
  char *outnow = outbuf;
  inline void getbuf();
  inline void putbuf();
  inline void get(int &x);
  inline void get(long long &x);
  inline void get(char &x);
  inline void put(int x);
  inline void put(long long x);
  inline void put(const char &x);
  inline void getbuf() { fread(ibuf, 1, IBUFSZ, stdin); }
  inline void putbuf() { fwrite(obuf, sizeof(char), ot - obuf, stdout); }
  inline void get(int &x) {
    x = 0;register int y=1;
    for (; *it < '0' || *it > '9'; ++it)
      y = (*it == '-')?-1:1;
    for (; *it >= '0' && *it <= '9'; x = (x << 1) + (x << 3) + (*(it++) ^ 48))
      ;
    x=x*y;
    return;
  }
  inline void get(long long &x) {
    x = 0;register int y=1;
    for (; *it < '0' || *it > '9'; ++it)
      y = (*it == '-')?-1:1;
    for (; *it >= '0' && *it <= '9'; x = (x << 1) + (x << 3) + (*(it++) ^ 48))
      ;
    x=x*y;
    return;
  }
  inline void get(char &x) { x = *(it++); }
  inline void put(int x) {
    int y;
    if(x < 0){
      x=-x;
      *(ot++) = '-';
    }
    if(x == 0)
      *(ot++) = '0';
    while (x) {
      y = x / 10;
      *(outnow++) = x - (y << 3) - (y << 1) + '0';
      x = y;
    }
    while (outnow > outbuf) *(ot++) = *(--outnow);
  }
  inline void put(const char &x) { *(ot++) = x; }
  inline void put(long long x) {
    long long y;
    if(x < 0){
      x=-x;
      *(ot++) = '-';
    }
    if(x == 0)
      *(ot++) = '0';
    while (x) {
      y = x / 10;
      *(outnow++) = x - (y << 3) - (y << 1) + '0';
      x = y;
    }
    while (outnow > outbuf) *(ot++) = *(--outnow);
  }
}  // namespace io
using namespace io;



typedef struct vec3{
  double x;double y;double z;
  inline double alpha(){
    return atan2(y,x);
  }
  inline double beta(){
    return acos(z/sqrt(x*x+y*y+z*z));
  }
  inline double mod(){
    return sqrt(x*x+y*y+z*z);
  }
  inline vec3 norm(){
    auto l = sqrt(x*x+y*y+z*z);
    return vec3({x/l,y/l,z/l});
  }
}vec3;

inline double operator*(const vec3& a,const vec3& b){
  return a.x*b.x+a.y*b.y+a.z*b.z;
}

inline vec3 operator+(const vec3& a,const vec3& b){
  return vec3({a.x+b.x,a.y+b.y,a.z+b.z});
}

inline vec3 operator*(const double& a,const vec3& b){
  return vec3({a*b.x,a*b.y,a*b.z});
}

inline vec3 cross(const vec3& a,const vec3& b){
  vec3 result;
  result.x = a.y*b.z-b.y*a.z;
  result.y = a.z*b.x-b.z*a.x;
  result.z = a.x*b.y-b.x*a.y;
  return result;
}

typedef struct Circle{
  vec3 center;
  double r;
} Circle;

typedef struct PlaneCircle{
  double x;
  double y;
  double r;
} PlaneCircle;


PlaneCircle result;
Circle resultR;
PlaneCircle CirclePool[MAXN];

Circle makeCircle(const double& a,const double& b,const double& r){
  vec3 center = {cos(a)*sin(b),sin(a)*sin(b),cos(b)};
  return Circle({center,r});
}

inline double norm2 (const double& x1,const double& x2,const double& y1,const double& y2){
  return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

inline double distance(const PlaneCircle& A,const PlaneCircle& B){
  return norm2(A.x,B.x,A.y,B.y);
}

PlaneCircle calcCircle(PlaneCircle A,PlaneCircle B){
  double r1 = A.r, r2 = B.r;
  double x1 = A.x, x2 = B.x;
  double y1 = A.y, y2 = B.y;

  double l = distance(A, B);

  double r = (l + r1 + r2) / 2;
  double v = r - r2;
  double cx = v / l * (x1 - x2) + x2;
  double cy = v / l * (y1 - y2) + y2;
  
  return PlaneCircle({cx, cy, r});
}
ostream & operator<<(ostream &out,const vec3 &A){
    out << "(" << A.x<<", "<<A.y<<", "<<A.z<<")";
    return out;
}

ostream & operator<<(ostream &out,const Circle &A){
    out << "[" << A.center<<", "<<A.r<<"]";
    return out;
}

PlaneCircle calcCircle(PlaneCircle A,PlaneCircle B,PlaneCircle C){
  double r1 = A.r, r2 = B.r, r3 = C.r;
  double x1 = A.x, x2 = B.x, x3 = C.x;
  double y1 = A.y, y2 = B.y, y3 = C.y;
  double v11 = 2 * x2 - 2 * x1;
  double v12 = 2*y2 - 2*y1;
  double v13 = x1*x1 - x2*x2 + y1*y1 - y2*y2 - r1*r1 + r2*r2;
  double v14 = 2*r2 - 2*r1;
  
  double v21 = 2*x3 - 2*x2;
  double v22 = 2*y3 - 2*y2;
  double v23 = x2*x2 - x3*x3 + y2*y2 - y3*y3 - r2*r2 + r3*r3;
  double v24 = 2*r3 - 2*r2;

  double w12 = v12/v11;
  double w13 = v13/v11;
  double w14 = v14/v11;
  
  double w22 = v22/v21-w12;
  double w23 = v23/v21-w13;
  double w24 = v24/v21-w14;
  
  double P = -w23/w22;
  double Q = w24/w22;
  double M = -w12*P-w13;
  double N = w14 - w12*Q;
  
  double a = N*N + Q*Q - 1;
  double b = M*N - N*x1 + P*Q - Q*y1 + r1;
  double c = x1*x1 + M*M - 2*M*x1 + P*P + y1*y1 - 2*P*y1 - r1*r1;
  double r = (- b - sqrt(b*b - a * c)) / (a);
  
  
  double x = M+N*r;
  double y = P+Q*r;
  
  if(isnan(x)||isnan(y)||isnan(r)){
    return PlaneCircle({0,0,0});
  }

  return PlaneCircle({x,y,r});
}


PlaneCircle makeCircleFromStar(int x,int y,int z,int r){
  vec3 far = vec3({(double)x,(double)y,(double)z});
  vec3 center = far.norm();
  double a = atan2(center.y,center.x);
  double b = acos(center.z);
  double c = asin(r / far.mod());

  double rb1 = (b-c)/2;
  double rb2 = (b+c)/2;

  double l1 = 2*tan(rb1);
  double l2 = 2*tan(rb2);

  double pt1x = l1 * cos(a);
  double pt1y = l1 * sin(a);
  double pt2x = l2 * cos(a);
  double pt2y = l2 * sin(a);

  double rr =  norm2(pt1x, pt2x, pt1y, pt2y)/2;


  return PlaneCircle({(pt2x + pt1x) / 2 ,(pt2y + pt1y) / 2 , rr});
}
Circle inverseCircleFromCircle(const PlaneCircle &c){
  double x = c.x;
  double y = c.y;
  double r = c.r;
  double l = x * x + y * y;
  double l1 = sqrt(l) + r;
  double l2 = sqrt(l) - r;

  double a = atan2(y, x);

  double b1 = 2*atan2(l1, 2);
  double b2 = 2*atan2(l2, 2);
  
  double b = (b1+b2)/2;
  double rr = (b1-b2)/2;

  if(b < 0){
    a +=  M_PI;
    if(a>M_2_PI) a-=M_2_PI;
    b = -b;
  }
  return makeCircle(a,b,rr);
}

int main() {
  srand(time(0));
  getbuf();
  int N;
  get(N);
  // scanf("%d",&N);
  int x, y, z, r;
  for(int i=1;i<=N;i++){
    get(x);
    get(y);
    get(z); 
    get(r);
    // scanf("%d%d%d%d",&x,&y,&z,&r);
    CirclePool[i]=makeCircleFromStar(x, y, z, r);
    //cout<<CirclePool[i].x<<" "<<CirclePool[i].y<<" "<<CirclePool[i].r<<endl;
    //getchar();
  }
  //cerr<<CirclePool[1]<<endl;
  random_shuffle(CirclePool+1,CirclePool+N+1);

  //cerr<<CirclePool[1]<<endl;
  result=CirclePool[1];

  for(int i=2;i<=N;i++){
    if(
      distance(result,CirclePool[i]) -
      result.r + CirclePool[i].r > -EPS
    ){
      
      result = CirclePool[i];
      for(int j=1;j<=i-1;j++){
        if(
          distance(result,CirclePool[j]) -
          result.r + CirclePool[j].r > -EPS
        ){
          
          result = calcCircle(CirclePool[i],CirclePool[j]);
          for(int k=1;k<=j-1;k++){
            if(
              distance(result,CirclePool[k]) - 
              result.r + CirclePool[k].r > -EPS
            ){

              result = calcCircle(CirclePool[i],CirclePool[j],CirclePool[k]);
              
            }
          }
        }
      }
    }

  }

  

  resultR = inverseCircleFromCircle(result);

  //cout<<result.x<<" "<<result.y<<" "<<result.r<<endl;
  //printf("%d",int(result.r/M_PI_2 * 100000));
 
  fprintf(stderr,"%.6f",resultR.r/M_PI_2 * 100000);
  int results = int(resultR.r / M_PI_2 * 100000);

  if(results > 99999)
  results = 99999;
  put(results);
  putbuf();
  return 0;
}
