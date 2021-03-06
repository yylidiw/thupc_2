#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<queue>
#define gc getchar()
#define pc putchar
#define pii pair<int,int>
#define pip pair<int,pii >
#define pjp pair<juese*,pii >
#define fi first
#define se second
#define mkp make_pair
#define rep for(int i = 1;i <= n;++i)
#define repa(x) rep if(!(x)[i].dead)
#define repb(x) rep if(!(x)[i] -> dead)
using namespace std;
inline int read(){
	int x = 0,c = gc;
	while(c < '0' || c > '9') c = gc;
	while(c >= '0' && c <= '9') x = x * 10 + c - '0',c = gc;
	return x;
}
inline void print(int x){
	if(x >= 10) print(x / 10);
	pc(x % 10 + '0');
}
int n,cnt;
int endtime;
string name[2] = {"Alice","Bob"};
inline void gmover(bool);
struct tf{
	int id,x,y;
	inline tf(){id = x = y = 0;}
	inline void in(){
		id = read();x = read();y = read();
	}
};
struct jn{
	int id,x,y,z;
	inline jn(){id = x = y = z = 0;}
	inline void in(){
		id = read();x = read();y = read();z = read();
	}
};
struct node{
	int tim,id,x;	
	inline node(int _tim = 0,int _id = 0,int _x = 0){
		tim = _tim;id = _id;x = _x;
	}
};
inline bool operator < (node a,node b){
	return a.tim > b.tim;
}
struct juese{
	bool dead,bel;
	int n,id;
	int hp,hhp,mp,mmp,atk,aatk,def,ddef;
	int ehp,emp;
	priority_queue<node> que;
	tf tt;
	jn jj;
	juese *sx[12],*df[12],*jf[12];
	inline juese(){
		dead = 0;bel = 0;
		n = 0;id = 0;
		hp = hhp = mp = mmp = atk = aatk = def = ddef = 0;
		ehp = 0;emp = 1;
	}
	inline int at(){return max(atk + aatk,1);}
	inline int de(){return max(def + ddef,0);}
	inline void yichu(){hhp = min(hhp,hp);mmp = min(mmp,mp);}
	inline void in(int _n,int _id,bool _bel,juese *_jf,juese *_df){
		n = _n;id = _id;bel = _bel;dead = 0;
		hp = hhp = read();mp = read();atk = read();def = read();
		mmp = aatk = ddef = 0;ehp = 0;emp = 1;
		while(!que.empty()) que.pop();
		rep jf[i] = &_jf[i],df[i] = &_df[i]; 
		rep sx[i] = df[read()];
		tt.in();jj.in();
		if(tt.id == 3) ehp += tt.x,emp += tt.y;
	}
	inline juese* findgj(){
		repb(sx) return sx[i];
		return 0;
	}
	inline void mdfhp(int x){
		hhp += x;yichu();
		if(hhp <= 0){
			dead = 1;hhp = 0;
			repb(jf) return;
			gmover(!bel);
		}
	}
	inline void mdfmp(int x){
		mmp += x;yichu();
	}
	inline int jskc(int x,int y){
		x = max(x,0);y = max(y,0);
		if(tt.id == 1) return max(x - de(),0) + y - y / 2; 
		return max(x - de(),0) + y;
	} 
	inline void smzkc(int x,int y){
		mdfmp(1);mdfhp(-jskc(x,y));
	}
	inline void del(){
		while(!que.empty() && que.top().tim == cnt){
			node q = que.top();que.pop();
			switch(q.id){
				case 0:aatk += q.x;break;
				case 1:ddef += q.x;break;
				case 2:ehp += q.x;break;
				case 3:emp += q.x;break;
			}
		}
	}
	inline void up(){
		mdfhp(ehp);mdfmp(emp);
	}
	inline pjp chkgj(){
		juese *q = findgj();
		int x = 0,y = 0;
		if(tt.id == 2) x = at(),y = tt.x;
		else if(tt.id == 4) x = 0,y = at();
		else x = at(),y = 0;
		return mkp(q,mkp(x,y));
	} 
	inline pip testgj(){
		pjp q = chkgj();
		return mkp(q.fi -> hhp,mkp(q.fi -> jskc(q.se.fi,q.se.se),id)); 
	}
	inline void ysxg(int id,int x,int y){
		switch(id){
			case 0:aatk += y;break;
			case 1:ddef += y;break;
			case 2:ehp += y;break;
			case 3:emp += y;break;
		}
		que.push(node(cnt + x - 1,id,-y));
	}
	inline void gj(){
		pjp q = chkgj();
		q.fi -> smzkc(q.se.fi,q.se.se);
		mdfmp(1);
		if(tt.id == 5) mdfhp(tt.x);
	}
	inline void fdjn(){
		juese *q = 0;
		int mn = 0x3f3f3f3f;
		mdfmp(-mmp);
		switch(jj.id){
			case 0:break;
			case 1:
				repb(df) df[i] -> smzkc(jj.x,0);
				repb(df) df[i] -> mdfmp(-(df[i] -> mmp) / 10);
				break;
			case 2:
				repb(df) df[i] -> smzkc(0,at());
				break;
			case 3:
				repb(df) df[i] -> smzkc(min((df[i] -> hp) / 10,jj.x * at()),0);
				break;
			case 4:
				repb(jf) jf[i] -> ysxg(3,jj.x,jj.y);
				break;
			case 5:
				q = findgj();
				(q -> ddef) -= jj.x;
				q -> smzkc(0,at());
				break;
			case 6:
				q = findgj();
				q -> smzkc(0,at());
				repb(df) df[i] -> ysxg(0,jj.x,-jj.y);
				break;
			case 7:
				repb(jf) mn = min(mn,jf[i] -> hhp);
				rep if((jf[i] -> hhp) == mn){
					jf[i] -> mdfhp(jj.z);
					break;
				}
				repb(jf) jf[i] -> ysxg(0,jj.x,jj.y);
				break;
			case 8:
				repb(df) df[i] -> smzkc(at(),0);
				repb(df) df[i] -> ysxg(1,jj.x,-jj.y);
				break;
			case 9:
				repb(jf) jf[i] -> mdfhp(jj.z);
				repb(jf) jf[i] -> ysxg(1,jj.x,jj.y);
				break;
			case 10:
				endtime = (cnt + jj.x - 1) * (bel ? -1 : 1);
				repb(jf) if((jf[i] -> jj).id == 10) (jf[i] -> jj).id = 0;
				repb(df) if((df[i] -> jj).id == 10) (df[i] -> jj).id = 0;
				repb(jf){
					(jf[i] -> atk) *= 2;
					(jf[i] -> def) *= 2;
					(jf[i] -> hhp) = max(jf[i] -> hhp,(jf[i] -> hp) / 2);
					(jf[i] -> mmp) = max(jf[i] -> mmp,(jf[i] -> mp) / 2);
					jf[i] -> ysxg(3,jj.x,1);
				}
				break;
		}
		mdfmp(1 + (tt.id == 5) * tt.y);
	}
};
struct player{
	int n;
	bool id;
	player *df;
	juese a[12];
	juese& operator [](int x){return a[x];} 
	inline void in(){
		rep a[i].in(n,i,id,a,df -> a);
	}
	bool fdjn(){
		for(int i = 10;i >= 0;--i){
			for(int j = n;j;--j) if(!a[j].dead && a[j].jj.id == i && a[j].mmp == a[j].mp){
				a[j].fdjn();return 1;
			}
		}
		return 0;
	}
	void gj(){
		pip nw = mkp(0,mkp(0,0));
		repa(a) nw = max(nw,a[i].testgj());
		a[nw.se.se].gj();
	}
	inline void del(){
		repa(a) a[i].del();
	}
	inline void up(){
		repa(a) a[i].up();
	}
}p[2];
inline void gmover(bool win){
	print(cnt);pc('\n');
	cout<<name[win];pc('\n');
	rep print(max(0,p[win][i].hhp)),pc(' ');pc('\n');
	exit(0);
}
void run(bool nw){
	if(!p[nw].fdjn()) p[nw].gj();
	p[nw].up();
}
void play(){
	run(0);run(1);
	p[0].del();p[1].del();
	if(cnt == abs(endtime)) gmover(endtime > 0);
}
int main(){
	n = p[0].n = p[1].n = read();
	p[0].df = &p[1];p[1].df = &p[0];
	p[0].id = 0;p[1].id = 1;
	p[0].in();p[1].in();
	for(cnt = 1;;++cnt) play();
	return 0;
}
