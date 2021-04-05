#include<bits/stdc++.h>
#define gc getchar()
#define pc putchar
#define li long long
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define pii pair<int,int>
#define md int mid = l + r >> 1
#define ls q << 1
#define rs q << 1 | 1
#define ln ls,l,mid
#define rn rs,mid + 1,r
using namespace std;
const int mo = 998244353;
inline li read(){
	li x = 0;
	int y = 0,c = gc;
	while(c < '0' || c > '9') y = c,c = gc;
	while(c >= '0' && c <= '9') x = x * 10 + c - '0',c = gc;
	return y == '-' ? -x : x;
}
inline void prt(li x){
	if(x >= 10) prt(x / 10);
	pc(x % 10 + '0');
}
inline void print(li x){
	if(x < 0) pc('-'),x = -x;
	prt(x);
}
li n,m,a[12],f[62][1030][12],p,c[15][15],wei[1030],ni[15],nj[15];
inline li zh(li q,li w){
	if(w > q || w < 0) return 0;
	q %= mo; 
	li ans = 1;
	for(li i = q;i > q - w;--i) (ans *= i % mo) %= mo;
	return ans * nj[w] % mo;
}
inline li wk(){
	li ans = 0;
	for(int i = 0;i < p;++i){
		li w = n;
		for(int j = 1;j <= m;++j) if(i & (1 << j - 1)) w -= a[j] + 1;
		li q = zh(w + m - 1,m - 1);
		if(wei[i] & 1) ans = (ans - q + mo) % mo;
		else (ans += q) %= mo; 
	}
	return ans;
}
int main(){
	int i,j,k,l,g,h;
	n = read();m = read();p = 1 << m;
	ni[1] = 1;for(i = 2;i <= m;++i) ni[i] = (mo - mo / i * ni[mo % i] % mo) % mo;
	nj[0] = 1;for(i = 1;i <= m;++i) nj[i] = nj[i - 1] * ni[i] % mo;
	for(i = 1;i < p;++i) wei[i] = wei[i >> 1] + (i & 1);
	for(i = 1;i <= m;++i) a[i] = min(n,read());
	c[0][0] = 1;
	for(i = 1;i <= m;++i){
		c[i][0] = 1;
		for(j = 1;j <= i;++j) c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
	}
	f[60][p - 1][0] = 1;
	for(i = 60;i;--i){
		for(j = 0;j < p;++j){
			int q = 0,r = m - wei[j];
			for(k = 1;k <= m;++k) if((j & (1 << k - 1))){
				if((a[k] >> i - 1) & 1) q |= (1 << k - 1);
			}
			for(k = 0;k < m;++k) if(f[i][j][k]){
				f[i][j][k] %= mo;
				for(g = q;;g = (g - 1) & q){
					l = k * 2 + ((n >> i - 1) & 1) - wei[g];
					for(h = wei[g] & 1;h <= r && h <= l;h += 2){
						if(l - h >= m) continue;
						(f[i - 1][j ^ q ^ g][l - h] += f[i][j][k] * c[r][h]) %= mo;
					}
					if(!g) break;
				}
			}
		}
	}
	li ans = 0;
	for(i = 0;i < p;++i) (ans += f[0][i][0]) %= mo;
	print((wk() - ans + mo) % mo);
	return 0;
}
