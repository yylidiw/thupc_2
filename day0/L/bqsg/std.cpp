#include <cstdio>
#include <cmath>
#include <iostream>
#include<algorithm>
using namespace std;

const int MAXN=20000005;
const double EPS = 1e-9;
// io improver
namespace io {
  const int IBUFSZ = 30000000;
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
    x = 0;
    for (; *it < '0' || *it > '9'; ++it)
      ;
    for (; *it >= '0' && *it <= '9'; x = (x << 1) + (x << 3) + (*(it++) ^ 48))
      ;
    return;
  }
  inline void get(long long &x) {
    x = 0;
    for (; *it < '0' || *it > '9'; ++it)
      ;
    for (; *it >= '0' && *it <= '9'; x = (x << 1) + (x << 3) + (*(it++) ^ 48))
      ;
    return;
  }
  inline void get(char &x) { x = *(it++); }
  inline void put(int x) {
    int y;
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
  double radius;
} Circle;

Circle makeCircle(const double& a,const double& b,const double& r){
  vec3 center = {cos(a)*sin(b),sin(a)*sin(b),cos(b)};
  return Circle({center,r});
}

inline double distance(const Circle& A,const Circle& B){
  return acos(A.center * B.center);
}

Circle calcCircle(Circle A,Circle B){
  auto r = (distance(A,B) + A.radius + B.radius)/2;
  auto n = cross(A.center,B.center).norm();
  auto q = cross(n,A.center).norm();
  auto centerDist = r - A.radius;
  auto center = cos(centerDist) * A.center+ sin(centerDist) * q;
  return Circle({center,r});
}
ostream & operator<<(ostream &out,const vec3 &A){
    out << "(" << A.x<<", "<<A.y<<", "<<A.z<<")";
    return out;
}

ostream & operator<<(ostream &out,const Circle &A){
    out << "[" << A.center<<", "<<A.radius<<"]";
    return out;
}

Circle calcCircle(Circle A,Circle B,Circle C){
  vec3 MX = {A.center.x, B.center.x, C.center.x},
       MY = {A.center.y, B.center.y, C.center.y}, 
       MZ = {A.center.z, B.center.z, C.center.z};
      // matrix M with col vector
  vec3 AMX = cross(MY, MZ), AMY = cross(MZ, MX), AMZ = cross(MX, MY);
  double det = MX * AMX;

  if(abs(det)<EPS){
    cout<<"Matrix inversement error. DET == 0";
  }

  double d1 = 1 / det;

  vec3 IM1 = d1* AMX, IM2 = d1 * AMY,IM3 = d1 * AMZ;
  
  vec3 N1 = {cos(A.radius), cos(B.radius), cos(C.radius)},
       N2 = {sin(A.radius), sin(B.radius), sin(C.radius)};  
  double A11 = N1*IM1, A12 = N2*IM1,
         A21 = N1*IM2, A22 = N2*IM2,
         A31 = N1*IM3, A32 = N2*IM3;
        
  auto u = A11 * A11 + A21 * A21 + A31 * A31;
  auto v = A12 * A11 + A22 * A21 + A32 * A31;
  auto w = A12 * A12 + A22 * A22 + A32 * A32;
  
  double tg = (- v - sqrt(v * v - (u - 1) * (w - 1))) / (w - 1 - 1e-14);
  double r = atan(tg);
  double cr = cos(r),sr = sin(r);
  vec3 center = {
    cr * A11 + sr * A12,
    cr * A21 + sr * A22,
    cr * A31 + sr * A32,
  }; 
  return Circle({center,r});
}


Circle CirclePool[MAXN];

Circle makeCircleFromStar(int x,int y,int z,int r){
  vec3 far = vec3({(double)x,(double)y,(double)z});
  vec3 center = far.norm();
  double radius = asin(r / far.mod());
  return Circle({center,radius});
}


int main() {
  int N;
  cin>>N;
  int x, y, z, r;
  for(int i=1;i<=N;i++){
    cin>>x>>y>>z>>r;
    CirclePool[i]=makeCircleFromStar(x, y, z, r);
  }
  random_shuffle(CirclePool+1,CirclePool+N);

  Circle result=CirclePool[1];

  for(int i=2;i<=N;i++){
    if(
      distance(result,CirclePool[i]) > 
      result.radius - CirclePool[i].radius
    ){
      
      result = CirclePool[i];
      for(int j=1;j<=i-1;j++){
        if(
          distance(result,CirclePool[j]) > 
          result.radius - CirclePool[j].radius
        ){
          
          result = calcCircle(CirclePool[i],CirclePool[j]);
          for(int k=1;k<=j-1;k++){
            if(
              distance(result,CirclePool[k]) > 
              result.radius - CirclePool[k].radius
            ){

              result = calcCircle(CirclePool[i],CirclePool[j],CirclePool[k]);
            
            }
          }
        }
      }
    }

  }

  //cout<<result<<endl;
  cout<<int(result.radius/M_PI_2 * 100000)<<endl;

  return 0;
}
