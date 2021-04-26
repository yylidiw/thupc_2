#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 998244353;
ll n, a[1230];
int f[21][1 << 10][3], g[21][1 << 10][3];
int m;

void addto(int &x, int y) {
	x += y; if (x >= mod) x -= mod;
}

int setbit(int v, int d, int w) {
	if ((v >> d & 1) == w) return v;
	return v ^ (1 << d);
}

void dpit(int d, int p) {
	memset(g, 0, sizeof g);
	for (int i = 0; i <= 20; ++i)
		for (int j = 0; j < 1 << m; ++j)
			for (int k = 0; k < 3; ++k)
				if (f[i][j][k]) {
					if (a[p] >> d & 1) {
						addto(g[i][setbit(j, p, 0)][k == 2 ? 2 : k], f[i][j][k]);
						addto(g[i + 1][j][k == 2 ? 2 : (k ^ 1)], f[i][j][k]);
					} else {
						addto(g[i][j][k == 2 ? 2 : k], f[i][j][k]);
						addto(g[i + 1][setbit(j, p, 1)][k == 2 ? 2 : (k ^ 1)], f[i][j][k]); 
					}
				}
	memcpy(f, g, sizeof g);
}

void solve(int d) {
	for (int i = 0; i < m; ++i)
		dpit(d, i);
	memset(g, 0, sizeof g);
	for (int i = 0; i <= 20; ++i)
		for (int j = 0; j < 1 << m; ++j)
			for (int k = 0; k < 3; ++k)
				if (f[i][j][k]) 
					if ((i & 1) == (n >> d & 1))
						addto(g[i >> 1][j][k ? 2 : 0], f[i][j][k]);
	memcpy(f, g, sizeof g);
}

int main() {
	scanf("%lld%d", &n, &m); 
	for (int i = 0; i < m; ++i)
		scanf("%lld", &a[i]);
	f[0][0][0] = 1;
	for (int i = 0; i < 61; ++i)
		solve(i);
	printf("%d\n", f[0][0][2]);
}
