#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;

int n, curRound;

#define forEach(S)     \
	for (Role & t : S) \
		if (!t.die)

class Role {
	int HP, hp;
	int MP, mp;
	int atk, datk;
	int def, ddef;
	vector<int> prefer;
	int target;
	int talent, tx, ty;
	int skill, sx, sy, sz;
	int deltaMpAfterRound;

public:
	bool die;
	void input() {
		die = false;
		cin >> HP >> MP >> atk >> def;
		hp = HP, mp = 0, datk = ddef = 0;
		prefer.resize(n);
		for (int i = 0; i < n; ++i)
			cin >> prefer[i], prefer[i]--;
		target = 0;
		cin >> talent >> tx >> ty;
		cin >> skill >> sx >> sy >> sz;
		deltaMpAfterRound = 1;
	}
	inline int getA() { return max(atk + datk, 1); }
	inline int getD() { return max(def + ddef, 0); }
	inline int getHp() { return hp; }
	inline int getHP() { return HP; }
	inline int getMp() { return mp; }
	inline Role &decHp(int delta) {
		hp -= delta;
		if (hp <= 0) hp = 0, die = true;
		return *this;
	}
	inline Role &incHp(int delta) {
		hp = min(HP, hp + delta);
		return *this;
	}
	inline Role &incMp(int delta) {
		mp = min(MP, mp + delta);
		return *this;
	}
	inline Role &decMp(int delta) {
		mp = max(0, mp - delta);
		return *this;
	}
	inline Role &updDatk(int delta) {
		datk += delta;
		return *this;
	}
	inline Role &updDdef(int delta) {
		ddef += delta;
		return *this;
	}
	inline void updDeltaMpAfterRound(int delta) { deltaMpAfterRound += delta; }
	inline Role &active() {
		atk *= 2, def *= 2;
		hp = max(HP / 2, hp);
		mp = max(MP / 2, mp);
		return *this;
	}
	inline Role &disableSkill(int x) {
		if (skill == x) skill = 0;
		return *this;
	}
	int getTarget(vector<Role> &e) {
		while (target < n && e[prefer[target]].die)
			++target;
		return prefer[target];
	}
	int getMinHp(vector<Role> &s) {
		int res = 0;
		while (res < n && s[res].die)
			++res;
		for (int i = res + 1; i < n; ++i)
			if ((!s[i].die) && s[i].getHp() < s[res].getHp()) res = i;
		return res;
	}
	bool alive(vector<Role> &e) {
		forEach(e) return true;
		return false;
	}
	int tryAttacked(int harm, int realHarm) {
		int res = max(harm - getD(), 0) + realHarm;
		if (talent == 1) res -= realHarm / 2;
		return res;
	}
	void _doAttacked(int deltaHp) {
		decHp(deltaHp);
		if (!die) incMp(1);
	}
	Role &doAttacked(int harm, int realHarm) {
		_doAttacked(tryAttacked(harm, realHarm));
		return *this;
	}
	pair<int, int> tryAttack(vector<Role> &e) {
		Role &t = e[getTarget(e)];
		int res = 0;
		if (talent == 4)
			res = t.tryAttacked(0, getA());
		else if (talent == 2)
			res = t.tryAttacked(getA(), tx);
		else
			res = t.tryAttacked(getA(), 0);
		return make_pair(t.getHp(), res);
	}
	void doAttack(vector<Role> &e) {
		e[getTarget(e)]._doAttacked(tryAttack(e).second);
		if (!alive(e)) throw(0);
		if (talent == 5) incHp(tx);
		incMp(1);
	}
	inline int trySkill() { return mp == MP ? skill : -1; }
	int doSkill(vector<Role> &e, vector<Role> &s);
	void revertSkill(vector<Role> &e, vector<Role> &s);
	void afterRound() {
		incMp(deltaMpAfterRound);
		if (talent == 3) incHp(tx), incMp(ty);
	}
	inline void report() {
		cout << (die ? "D" : "A") << " S: " << skill << " T: " << talent << " ";
		cout << "hp: [" << hp << "/" << HP << "] ";
		cout << "mp: [" << mp << "/" << MP << "] ";
		cout << "atk: [" << atk << "+" << datk << "] ";
		cout << "def: [" << def << "+" << ddef << "] ";
		cout << "deltaMp: " << deltaMpAfterRound;
	}
};

int Role::doSkill(vector<Role> &e, vector<Role> &s) {
	mp = 0;
	int res = (skill == 4 || skill >= 6) ? sx : 0;
	if (skill == 1) forEach(e) t.doAttacked(sx, 0), t.decMp(t.getMp() / 10);
	if (skill == 2) forEach(e) t.doAttacked(0, getA());
	if (skill == 3) forEach(e) t.doAttacked(min(t.getHP() / 10, sx * getA()), 0);
	if (skill == 4) forEach(s) t.updDeltaMpAfterRound(sy);
	if (skill == 5) e[getTarget(e)].updDdef(-sx), e[getTarget(e)].doAttacked(0, getA());
	if (skill == 6) {
		e[getTarget(e)].doAttacked(0, getA());
		forEach(e) t.updDatk(-sy);
	}
	if (skill == 7) {
		s[getMinHp(s)].incHp(sz);
		forEach(s) t.updDatk(sy);
	}
	if (skill == 8) {
		forEach(e) t.doAttacked(getA(), 0);
		forEach(e) t.updDdef(-sy);
	}
	if (skill == 9) forEach(s) t.incHp(sz), t.updDdef(sy);
	if (skill == 10) {
		forEach(s) t.active().disableSkill(10).updDeltaMpAfterRound(1);
		forEach(e) t.disableSkill(10);
	}
	if (!alive(e)) throw(0);
	incMp(1 + (talent == 5 ? ty : 0));
	return res;
}

void Role::revertSkill(vector<Role> &e, vector<Role> &s) {
	if (skill == 4) forEach(s) t.updDeltaMpAfterRound(-sy);
	if (skill == 6) forEach(e) t.updDatk(sy);
	if (skill == 7) forEach(s) t.updDatk(-sy);
	if (skill == 8) forEach(e) t.updDdef(sy);
	if (skill == 9) forEach(s) t.updDdef(-sy);
	if (skill == 0) {
		forEach(s) t.decHp(t.getHp());
		throw(0);
	}
}

struct Record {
	int rt, id;
	Record(int t, int i) : rt(t), id(i){};
	inline bool operator<(const Record &x) const {
		return rt > x.rt;
	}
};

class Roles {
	priority_queue<Record> pq;

public:
	vector<Role> r;
	void input() {
		r.resize(n);
		for (Role &t : r)
			t.input();
	}
	bool alive() {
		forEach(r) return true;
		return false;
	}
	void action(Roles &E) {
		int id = -1, ret, bst = -1;
		for (int i = 0; i < n; ++i) {
			if (r[i].die) continue;
			ret = r[i].trySkill();
			if (ret >= bst) bst = ret, id = i;
		}
		if (bst != -1) {
			ret = r[id].doSkill(E.r, r);
			if (ret)
				pq.push(Record(curRound + ret - 1, id));
		} else {
			pair<int, int> pbst = make_pair(0, 0), pret;
			for (int i = 0; i < n; ++i) {
				if (r[i].die) continue;
				pret = r[i].tryAttack(E.r);
				if (pret >= pbst) pbst = pret, id = i;
			}
			r[id].doAttack(E.r);
		}
		forEach(r) t.afterRound();
	}
	void revert(Roles &E) {
		while ((!pq.empty()) && pq.top().rt == curRound) {
			Record rec = pq.top();
			pq.pop();
			r[rec.id].revertSkill(E.r, r);
		}
	}
} A, B;

int main() {
	cin >> n;
	A.input(), B.input();
	try {
		while (1) {
			++curRound;
			A.action(B), B.action(A);
			A.revert(B), B.revert(A);
		}
	} catch (int ret) {
		cout << curRound << endl;
		if (A.alive()) {
			cout << "Alice" << endl;
			for (int i = 0; i < n; ++i)
				cout << A.r[i].getHp() << " ";
			cout << endl;
		} else {
			cout << "Bob" << endl;
			for (int i = 0; i < n; ++i)
				cout << B.r[i].getHp() << " ";
			cout << endl;
		}
	}
	return 0;
}
