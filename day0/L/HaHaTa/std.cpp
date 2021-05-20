#include<bits/stdc++.h>

using namespace std;

const double eps = 1e-8;
const double pi = acos(-1.0);
const int MAXN = 1000000;

#define lt(x, y) ((x) < (y) - eps)
#define gt(x, y) ((x) > (y) + eps)
#define le(x, y) ((x) <= (y) + eps)
#define ge(x, y) ((x) >= (y) - eps)
#define eq(x, y) (le(x, y) && ge(x, y))
#define sqr(x) ((x) * (x))

struct vec3 {
	double x, y, z;
	vec3(double x0 = 0, double y0 = 0, double z0 = 0) : x(x0), y(y0), z(z0) {}
	inline vec3 operator-() const {return vec3(-x, -y, -z);}
	inline vec3 operator+(const vec3 &V) const {return vec3(x + V.x, y + V.y, z + V.z);}
	inline vec3 operator-(const vec3 &V) const {return vec3(x - V.x, y - V.y, z - V.z);}
	inline vec3 operator*(double k) const {return vec3(x * k, y * k, z * k);}
	inline vec3 operator/(double k) const {return vec3(x / k, y / k, z / k);}
	inline bool operator<(const vec3 &V) const {return lt(x, V.x) || (eq(x, V.x) && lt(y, V.y)) || (eq(x, V.x) && eq(y, V.y) && lt(z, V.z));}
	inline bool operator>(const vec3 &V) const {return gt(x, V.x) || (eq(x, V.x) && gt(y, V.y)) || (eq(x, V.x) && eq(y, V.y) && gt(z, V.z));}
	inline bool operator<=(const vec3 &V) const {return le(x, V.x) || (eq(x, V.x) && le(y, V.y)) || (eq(x, V.x) && eq(y, V.y) && le(z, V.z));}
	inline bool operator>=(const vec3 &V) const {return ge(x, V.x) || (eq(x, V.x) && ge(y, V.y)) || (eq(x, V.x) && eq(y, V.y) && ge(z, V.z));}
	inline bool operator==(const vec3 &V) const {return eq(x, V.x) && eq(y, V.y) && eq(z, V.z);}
	inline double operator*(const vec3 &V) const {return x * V.x + y * V.y + z * V.z;}
	inline vec3 operator^(const vec3 &V) const {return vec3(y * V.z - z * V.y, z * V.x - x * V.z, x * V.y - y * V.x);}
	inline double len() const {return sqrt(x * x + y * y + z * z);}
	inline double len2() const {return x * x + y * y + z * z;}
	inline vec3 unit() const {return vec3(x / sqrt(x * x + y * y + z * z), y / sqrt(x * x + y * y + z * z), z / sqrt(x * x + y * y + z * z));}
};

typedef vec3 pt3;

double dis(const pt3 &A, const pt3 &B) { //dis on unit sphere
	return acos(A * B);
}

struct circle {
	pt3 ct;
	double r;
	circle(pt3 ct0 = pt3(0, 0, 0), double r0 = 0) : ct(ct0), r(r0) {}
}C[MAXN + 5], Res;

circle gen(const circle &A) {
	return A;
}

circle gen(const circle&A, const circle&B) {
	double d = dis(A.ct, B.ct), r = (d + A.r + B.r) / 2;
	vec3 n = ((A.ct ^ B.ct) ^ A.ct).unit();
	double theta = r - A.r;
	return circle(A.ct * cos(theta) + n * sin(theta), r);
}

circle gen(const circle&X, const circle&Y, const circle&Z) {
	double x = X.r, y = Y.r, z = Z.r;
	double a = dis(Y.ct, Z.ct), b = dis(X.ct, Z.ct), c = dis(X.ct, Y.ct);
	double A = a * a - (y - z) * (y - z), B = b * b - (z - x) * (z - x), C = c * c - (x - y) * (x - y);
	double S = sqrt((a + b + c) * (-a + b + c) * (a - b + c) * (a + b - c)) / 4;
	double r = ((A * B * C) + sqr((y - x) * B - (z - x) * C)) / ((z - x) * C * (A + B - C) + (y - x) * B * (A - B + C) + 4 * S * sqrt(A * B * C)) - x;
	return circle(pt3(0, 0, 0), r);
}

int main() {
	int N;
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		double x, y, z, r;
		scanf("%lf%lf%lf%lf", &x, &y, &z, &r);
		C[i].ct = pt3(x, y, z) / pt3(x, y, z).len();
		C[i].r = asin(r / pt3(x, y, z).len());
	}
	random_shuffle(C + 1, C + N + 1);
	//Res = gen(C[1]);
	Res = gen(C[1], C[2], C[3]);
	printf("%.6lf %.6lf %.6lf %.12lf\n", Res.ct.x, Res.ct.y, Res.ct.z, Res.r);
	printf("%d\n", int(Res.r / (pi / 2) * 1e5));
	return 0;
}
