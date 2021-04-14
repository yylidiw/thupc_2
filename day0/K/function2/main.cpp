#include <bits/stdc++.h>

using namespace std;

#define POWER 4
#define _QUOTE(x) #x
#define QUOTE(x) _QUOTE(x)
static_assert(POWER <= 4);

using LL = long long;

constexpr int get_base() {
    int ret = 1;
    for (int i = 0; i < POWER; i++) ret *= 10;
    return ret;
}

struct Bigint {
    // 10^4
    int d[255];
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

    void read() {
        char s[1024];
        scanf("%s", s);
        int buf_len = strlen(s);
        len = (buf_len - 1) / POWER + 1;
        for (int i = 0; i < len; i++) {
            for (int j = max(buf_len - (i + 1) * POWER, 0); j < buf_len - i * POWER; j++) {
                d[i] = d[i] * 10 + s[j] - '0';
            }
        }
    }
    void print() {
        if (len == 0) {
            putchar('0');
        } else {
            printf("%d", d[len - 1]);
            for (int i = len - 2; i >= 0; i--) {
                printf(FORMAT, d[i]);
            }
        }
    }
    void println() {
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

    bool is1() const { return len == 1 && d[0] == 1; }
};

Bigint operator + (const Bigint& a, const Bigint& b) {
    Bigint c;
    c.len = max(a.len, b.len);
    for (int i = 0; i < c.len; i++) {
        c[i] += a[i] + b[i];
        if (c[i] >= Bigint::BASE) {
            c[i + 1] ++;
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
    for (int i = c.len - 1, cur = 0; i >= 0; i--) {
        c[i] = a[i] - b[i];
        if (c[i] < 0) {
            c[i] += Bigint::BASE;
            assert(c[i + 1] > 0);
            c[i + 1]--;
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

Bigint gcd(Bigint a, Bigint b) {
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

LL gcd(LL a, LL b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        Bigint a, b, c;
        a.read();
        b.read();
        c.read();
        if (!gcd(a, gcd(b, c)).is1()) {
            puts("-1");
            continue;
        }
        for (;;) {
            Bigint d = gcd(b, c);
            if (d.is1()) break;
        }
        c.println();
    }
    return 0;
}
