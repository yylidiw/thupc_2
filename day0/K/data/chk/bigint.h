#include <bits/stdc++.h>

#define POWER 4
#define _QUOTE(x) #x
#define QUOTE(x) _QUOTE(x)
static_assert(POWER <= 4);
#define MAXL 2000

namespace NBigint {
    using LL = long long;
    using namespace std;

    constexpr int get_base() {
        int ret = 1;
        for (int i = 0; i < POWER; i++) ret *= 10;
        return ret;
    }

    struct Bigint {
        int d[2 * MAXL / POWER + 10];
        int len;

        constexpr static const int BASE = get_base();
        constexpr static const char* FORMAT = "%0" QUOTE(POWER) "d";

        Bigint(LL x = 0) {
            memset(d, 0, sizeof(d));
            len = 0;
            while (x) {
                d[len++] = x % BASE;
                x /= BASE;
            }
        }

        int &operator [] (const int i) { return d[i]; }
        const int &operator [] (const int i) const { return d[i]; }

        void update(const char* s, int buf_len) {
            len = (buf_len - 1) / POWER + 1;
            for (int i = 0; i < len; i++) {
                for (int j = max(buf_len - (i + 1) * POWER, 0); j < buf_len - i * POWER; j++) {
                    d[i] = d[i] * 10 + s[j] - '0';
                }
            }
            while (len > 0 && d[len - 1] == 0) len--;
        }

        void read(FILE *f = stdin) {
            char s[MAXL + 10];
            fscanf(f, "%s", s);
            update(s, strlen(s));
        }
        void print() const {
            if (len == 0) {
                putchar('0');
            } else {
                printf("%d", d[len - 1]);
                for (int i = len - 2; i >= 0; i--) {
                    printf(FORMAT, d[i]);
                }
            }
        }
        void println() const {
            print();
            putchar('\n');
        }

        void div2() {
            for (int i = len - 1, cur = 0; i >= 0; i--) {
                cur = cur * BASE + d[i];
                int q = cur >> 1, r = cur & 1;
                d[i] = q;
                cur = r;
            }
            if (len && d[len - 1] == 0) len--;
        }

        int mod2() const {
            if (len == 0 || (d[0] & 1) == 0) return 0;
            else return 1;
        }

        void mul2() {
            for (int i = 0; i < len; i++) d[i] *=2;
            for (int i = 0; i < len; i++) {
                if (d[i] >= Bigint::BASE) {
                    d[i] -= Bigint::BASE;
                    d[i + 1]++;
                }
            }
            if (d[len]) len++;
        }

        Bigint mul(int x) const {
            Bigint ret = *this;
            assert(x < BASE);
            for (int i = 0; i < len; i++) ret[i] *= x;
            for (int i = 0; i < len; i++) {
                ret[i + 1] += ret[i] / BASE;
                ret[i] %= BASE;
            }
            if (ret[len]) ret.len++;
            return ret;
        }

        void append(int x) {
            assert(x < BASE);
            if (len == 0 && x == 0) return;
            for (int i = len - 1; i >= 0; i--) d[i + 1] = d[i];
            d[0] = x;
            len++;
        }

        Bigint div(const Bigint& a) {
            Bigint r = 0;
            for (int i = len - 1; i >= 0; i--) {
                r.append(d[i]);
                if (r < a) {
                    d[i] = 0;
                    continue;
                }
                // int x = r.len == a.len ? r[r.len - 1] : r[r.len - 1] * BASE + r[r.len - 2], y = a[a.len - 1];
                // int lo = max(x / (y + 1), 1), hi = min((x + 1) / y, BASE - 1);
                int lo = 1, hi = BASE - 1;
                while (lo <= hi) {
                    int m = (lo + hi) >> 1;
                    Bigint b = a.mul(m);
                    if (b <= r) d[i] = m, lo = m + 1;
                    else hi = m - 1;
                }

                r = r - a.mul(d[i]);
            }
            len -= a.len;
            if (d[len]) len++;
            return r;
        }

        bool is1() const { return len == 1 && d[0] == 1; }

        friend Bigint operator + (const Bigint& a, const Bigint& b);
        friend Bigint operator - (const Bigint& a, const Bigint& b);
        friend bool operator < (const Bigint& a, const Bigint& b);
        friend bool operator == (const Bigint& a, const Bigint& b);
        friend bool operator <= (const Bigint& a, const Bigint& b);
    };

    Bigint operator + (const Bigint& a, const Bigint& b) {
        Bigint c;
        c.len = max(a.len, b.len);
        for (int i = 0; i < c.len; i++) {
            c[i] += a[i] + b[i];
            if (c[i] >= Bigint::BASE) {
                c[i + 1]++;
                c[i] -= Bigint::BASE;
            }
        }
        if (c[c.len]) c.len++;
        return c;
    }

    // a >= b must hold
    Bigint operator - (const Bigint& a, const Bigint& b) {
        Bigint c;
        c.len = max(a.len, b.len);
        for (int i = 0; i < c.len; i++) {
            c[i] += a[i] - b[i];
            if (c[i] < 0) {
                c[i] += Bigint::BASE;
                c[i + 1]--;
                assert(c[i] >= 0);
            }
        }
        while (c.len && c[c.len - 1] == 0) c.len--;
        return c;
    }

    bool operator < (const Bigint& a, const Bigint& b) {
        if (a.len != b.len) return a.len < b.len;
        for (int i = a.len - 1; i >= 0; i--) {
            if (a[i] != b[i]) return a[i] < b[i];
        }
        return false;
    }

    bool operator == (const Bigint& a, const Bigint& b) {
        if (a.len != b.len) return false;
        for (int i = 0; i < a.len; i++) {
            if (a[i] != b[i]) return false;
        }
        return true;
    }

    bool operator <= (const Bigint& a, const Bigint& b) {
        if (a.len != b.len) return a.len < b.len;
        for (int i = a.len - 1; i >= 0; i--) {
            if (a[i] != b[i]) return a[i] < b[i];
        }
        return true;
    }

    Bigint operator * (const Bigint& a, const Bigint& b) {
        Bigint c;
        for (int i = 0; i < a.len; i++) {
            for (int j = 0; j < b.len; j++) {
                c[i + j] += a[i] * b[j];
                c[i + j + 1] += c[i + j] / Bigint::BASE;
                c[i + j] %= Bigint::BASE;
            }
        }
        c.len = a.len + b.len;
        while (c.len > 0 && !c[c.len - 1]) c.len--;
        return c;
    }

    Bigint gcd(Bigint a, Bigint b) {
        if (a.len < b.len) swap(a, b);
        a = a.div(b);
        if (a.len == 0) return b;
        swap(a, b);
        int cnt = 0;
        for (;;) {
            if (a == b) {
                while (cnt--) a.mul2();
                return a;
            }
            int ra = a.mod2(), rb = b.mod2();
            while (ra == 0 && rb == 0) {
                a.div2();
                b.div2();
                cnt++;
                ra = a.mod2();
                rb = b.mod2();
            }
            if (ra == 1 && rb == 1) {
                if (a < b) swap(a, b);
                a = a - b;
            } else if (rb == 0) swap(a, b);
            for (;;) {
                a.div2();
                if (a.mod2() == 1) break;
            }
        }
    }
}
