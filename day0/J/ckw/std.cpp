#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define Rep(i,v) rep(i,0,(int)v.size()-1)
#define lint long long
#define ull unsigned lint
#define db long double
#define pb push_back
#define mp make_pair
#define fir first
#define sec second
#define gc getchar()
using namespace std;
typedef pair<int,int> pii;
typedef set<int>::iterator sit;
inline int inn()
{
	int x,ch;while((ch=gc)<'0'||ch>'9');
	x=ch^'0';while((ch=gc)>='0'&&ch<='9')
		x=(x<<1)+(x<<3)+(ch^'0');return x;
}
namespace CONST_NUMBERS{
	const int
		XRPN=1,XHLLTS=2,XSYW=3,CFRS=4,KJZS=5,
		XTBL=0,GLZL=1,RSZY=2,TLBDJ=3,YCKS=4,TLSZ=5,
		DQLSSD=6,JGZF=7,LX=8,JLBH=9,QLCQK=10,
		LHZZM_TYPE=-1,ATK_TYPE=1,DEF_TYPE=2,MP_TYPE=3;
}using namespace CONST_NUMBERS;
int cur_term,n;const int MAX_TERM=300010;
struct Event{ int tp,id,x,y; }evt;vector<pair<int,pii> > evs[MAX_TERM];
inline int build_event(int id,int tp,int x,int y) { return evt.id=id,evt.tp=tp,evt.x=x,evt.y=y; }
struct Innate{ int tp,x,y; }; struct Skill{ int tp,x,y,z; };
const int MAX_CH=12;
struct Character{
	int HP,hp,MP,mp,atk,del_atk,def,del_def,p[MAX_CH],del_mp;
	Innate in;Skill sk;int id;inline int alive() { return hp>0; }
	inline int full_mp() { return mp==MP; }
	inline int A() { return max(atk+del_atk,1); }
	inline int D() { return max(def+del_def,0); }
	inline int calc_del_hp(int x,int y) { if(in.tp==XRPN) return max(x-D(),0)+y-y/2;return max(x-D(),0)+y; }
	inline int del_hp(int x,int y) { return mp=min(mp+1,MP),hp-=calc_del_hp(x,y); }
	inline int firtar(Character *B) { rep(i,1,n) if(B[p[i]].alive()) return p[i];return 0; }
	inline int usual_atk(Character *B)
	{
		Character &tar=B[firtar(B)];int x=A(),y=0;
		if(in.tp==XHLLTS) x=A(),y=in.x;
		else if(in.tp==CFRS) x=0,y=A();
		tar.del_hp(x,y),mp=min(mp+1,MP);
		if(in.tp==KJZS)
		{
			int k=0;rep(i,1,n) if(B[i].alive()) k=1;
			if(k) hp=min(hp+in.x,HP);
		}
		return 0;
	}
	inline int try_atk(Character *B)
	{
		Character &tar=B[firtar(B)];
		if(in.tp==XHLLTS) return tar.calc_del_hp(A(),in.x);
		if(in.tp==CFRS) return tar.calc_del_hp(0,A());
		return tar.calc_del_hp(A(),0);
	}
	inline int perform_skill(Character *B)
	{
		mp=0;Character &tar=B[firtar(B)];
		switch(sk.tp)
		{
			case XTBL:break;
			case GLZL:rep(i,1,n) if(B[i].alive()) B[i].del_hp(sk.x,0),B[i].mp-=B[i].mp/10;break;
			case RSZY:rep(i,1,n) if(B[i].alive()) B[i].del_hp(0,A());break;
			case TLBDJ:rep(i,1,n) if(B[i].alive()) B[i].del_hp(min(sk.x*A(),B[i].HP/10),0);break;
			case YCKS:build_event(0,MP_TYPE,sk.x,sk.y);break;
			case TLSZ:tar.del_def-=sk.x;tar.del_hp(0,A());break;
			case DQLSSD:tar.del_hp(0,A());build_event(1,ATK_TYPE,sk.x,-sk.y);break;
			case JGZF:build_event(0,ATK_TYPE,sk.x,sk.y);break;//
			case LX:rep(i,1,n) B[i].del_hp(A(),0);build_event(1,DEF_TYPE,sk.x,-sk.y);break;
			case JLBH:build_event(0,DEF_TYPE,sk.x,sk.y);break;//
			case QLCQK:build_event(0,LHZZM_TYPE,sk.x,0);return 0;//
			default:assert(0);
		}
		mp=min(mp+1,MP);
		if(in.tp==KJZS) mp=min(mp+in.y,MP);
		return 0;
	}
	inline int renew()
	{
		if(!alive()) return 0;mp=min(mp+del_mp+1,MP);
		if(in.tp==XSYW) hp=min(hp+in.x,HP),mp=min(mp+in.y,MP);
		return 0;
	}
};
inline int any_alive(Character *B) { rep(i,1,n) if(B[i].alive()) return 1;return 0; }
struct Player{
	int n,id;Character ch[MAX_CH];
	inline int all_dead() { rep(i,1,n) if(ch[i].alive()) return 0;return 1; }
	inline int act(Character *B)
	{
		if(all_dead()) return 0;
		pii dec=mp(0,0);
		rep(i,1,n)
			if(ch[i].alive()&&ch[i].full_mp()) dec=max(dec,mp(ch[i].sk.tp,i));
		if(dec!=mp(0,0))
		{
			evt.tp=0,ch[dec.sec].perform_skill(B);
			if(dec.fir==JGZF)
			{
				pii bst=mp(INT_MAX,0);
				rep(i,1,n) if(ch[i].alive()) bst=min(mp(ch[i].hp,i),bst);
				int k=bst.sec,w=ch[dec.sec].sk.z;
				ch[k].hp=min(ch[k].hp+w,ch[k].HP);
			}
			else if(dec.fir==JLBH)
			{
				rep(i,1,n) if(ch[i].alive())
					ch[i].hp=min(ch[i].hp+ch[dec.sec].sk.z,ch[i].HP);
			}
			if(evt.tp==LHZZM_TYPE)
			{
				rep(i,1,n) if(ch[i].alive())
					ch[i].atk*=2,ch[i].hp=max(ch[i].hp,ch[i].HP/2),
					ch[i].def*=2,ch[i].mp=max(ch[i].mp,ch[i].MP/2);
				int k=dec.sec;ch[k].mp=min(ch[k].mp+1,ch[k].MP);
				if(ch[k].in.tp==KJZS) ch[k].mp=min(ch[k].mp+ch[k].in.y,ch[k].MP);
				rep(i,1,n) ch[i].del_mp+=1;
				rep(i,1,n) if(ch[i].sk.tp==QLCQK) ch[i].sk.tp=0;
				rep(i,1,n) if(B[i].sk.tp==QLCQK) B[i].sk.tp=0;
				evs[cur_term+evt.x-1].pb(mp(evt.id^id,mp(evt.tp,evt.y)));
			}
			else if(evt.tp){
				Character *C=(evt.id?B:ch);
				rep(i,1,n) if(C[i].alive())
				{
					if(evt.tp==ATK_TYPE) C[i].del_atk+=evt.y;
					if(evt.tp==DEF_TYPE) C[i].del_def+=evt.y;
					if(evt.tp==MP_TYPE) C[i].del_mp+=evt.y;
				}
				evs[cur_term+evt.x-1].pb(mp(evt.id^id,mp(evt.tp,evt.y)));
			}
			if(any_alive(B)) rep(i,1,n) if(ch[i].alive()) ch[i].renew();
			return 0;
		}
		pair<pii,int> bst=mp(mp(0,0),0);
		rep(i,1,n) if(ch[i].alive())
		{
			Character &_tar=B[ch[i].firtar(B)];
			pair<pii,int> res=mp(mp(_tar.hp,ch[i].try_atk(B)),i);
			if(res>bst) bst=res;
		}
		int w=bst.sec;ch[w].usual_atk(B);
		if(any_alive(B)) rep(i,1,n) if(ch[i].alive()) ch[i].renew();
		return 0;
	}
	inline int input(int _id)
	{
		id=_id;
		rep(i,1,n)
		{
			ch[i].hp=ch[i].HP=inn(),ch[i].mp=0,ch[i].MP=inn(),
			ch[i].atk=inn(),ch[i].def=inn(),ch[i].del_atk=ch[i].del_def=0;
			ch[i].id=i;rep(j,1,n) ch[i].p[j]=inn();
			ch[i].in.tp=inn(),ch[i].in.x=inn(),ch[i].in.y=inn();
			ch[i].sk.tp=inn(),ch[i].sk.x=inn(),ch[i].sk.y=inn(),ch[i].sk.z=inn();
		}
		return 0;
	}
}p[2];
inline int end_cur_term()
{
	Rep(i,evs[cur_term])
	{
		pair<int,pii> e=evs[cur_term][i];
		if(e.sec.fir==LHZZM_TYPE) { rep(i,1,n) p[e.fir].ch[i].hp=0;return 0; }
		int tp=e.sec.fir,w=e.sec.sec;Character *ch=p[e.fir].ch;
		rep(i,1,n)
			if(tp==ATK_TYPE) ch[i].del_atk-=w;
			else if(tp==DEF_TYPE) ch[i].del_def-=w;
			else ch[i].del_mp-=w;
	}
	return 0;
}
int main()
{
	n=p[0].n=p[1].n=inn(),p[0].input(0),p[1].input(1);
	for(cur_term=1;!p[0].all_dead()&&!p[1].all_dead();cur_term++)
	{
		p[0].act(p[1].ch);if(p[1].all_dead()) break;
		p[1].act(p[0].ch);if(p[0].all_dead()) break;
		end_cur_term();if(p[0].all_dead()||p[1].all_dead()) break;
	}
	printf("%d\n",cur_term);
	int t=p[0].all_dead();printf("%s\n",t?"Bob":"Alice");
	rep(i,1,n) printf("%d ",p[t].ch[i].alive()*p[t].ch[i].hp);
	return !printf("\n");
}
