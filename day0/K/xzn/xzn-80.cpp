//#define Test
#include<bits/stdc++.h>
using namespace std;
const int Nmax=1e6+7;
#define MOD 1000000000
#define BUFFER_SIZE 5000000
#define LL long long
#define __base_t vector <int>

namespace __BigInt_b
{
void convert_s(const __base_t &a, char *s)
{
    static char buffer[BUFFER_SIZE];
    char *ptr = buffer;
    ptr += sprintf(ptr, "%d", a[a.size() - 1]);

    for(int i = a.size() - 2; ~i; -- i)
        ptr += sprintf(ptr, "%09d", a[i]);

    strcpy(s, buffer);
}

__base_t convert_b(const char *s)
{
    int size = strlen(s);
    __base_t c;
    c.resize((size + 8) / 9);

    for(int i = size - 1, j = 1; ~i; -- i, j = (j * 10 == MOD ? 1 : j * 10))
        c[(size - i - 1) / 9] += (s[i] - '0') * j;

    return c;
}

LL convert_i(const __base_t &a)
{
    LL b = 1, c = 0;

    for(int i = 0; i < a.size(); ++ i)
        c += a[i] * b, b = b * MOD;

    return c;
}

__base_t convert_b(LL a)
{
    __base_t b;

    if(a == 0)
        b.push_back(0);

    while(a)
        b.push_back(a % MOD), a /= MOD;

    return b;
}

int __comp(const __base_t &a, const __base_t &b)
{
    if(a.size() != b.size())
        return a.size() < b.size() ? -1 : 1;

    for(int i = a.size() - 1; ~i; -- i)
        if(a[i] != b[i])
            return a[i] < b[i] ? -1 : 1;

    return 0;
}

__base_t addi(const __base_t &a, const __base_t &b)
{
    if(a.size() < b.size())
        return addi(b, a);

    __base_t c = a;
    c.push_back(0);

    for(int i = 0; i < b.size() || c[i] >= MOD; ++ i)
    {
        if(i < b.size())
            c[i] += b[i];

        if(c[i] >= MOD)
            c[i] -= MOD, c[i + 1] ++;
    }

    while(c.size() > 1 && !c[c.size() - 1])
        c.pop_back();

    return c;
}

__base_t subt(const __base_t &a, const __base_t &b)
{
    __base_t c = a;

    for(int i = 0; i < a.size() && (i < b.size() || c[i] < 0); ++ i)
    {
        if(i < b.size())
            c[i] -= b[i];

        if(c[i] < 0)
            c[i] += MOD, c[i + 1] --;
    }

    while(c.size() > 1 && !c[c.size() - 1])
        c.pop_back();

    return c;
}

__base_t mult(const __base_t &a, const __base_t &b)
{
    __base_t c;
    c.resize(a.size() + b.size() + 1);
    LL k = 0;

    for(int i = 0; i < a.size(); ++ i)
    {
        for(int j = 0; j < b.size(); ++ j)
        {
            k = k + 1ll * a[i] * b[j] + c[i + j];
            c[i + j] = k % MOD;
            k /= MOD;
        }

        c[i + b.size()] = k;
        k = 0;
    }

    while(c.size() > 1 && !c[c.size() - 1])
        c.pop_back();

    return c;
}

void trial_division(const __base_t &a, int b, __base_t &c, int &d)
{
    c.resize(a.size());
    LL k = 0;

    for(int i = a.size() - 1; ~i; -- i)
    {
        k = k * MOD + a[i];
        c[i] = k / b;
        k %= b;
    }

    while(c.size() > 1 && !c[c.size() - 1])
        c.pop_back();

    d = k;
}

__base_t divi(const __base_t &a, int b)
{
    __base_t c;
    int d;
    trial_division(a, b, c, d);
    return c;
}

int modu(const __base_t &a, int b)
{
    __base_t c;
    int d;
    trial_division(a, b, c, d);
    return d;
}

#define __trial_division_subt()\
{\
    LL k = 0;\
    for (int j = 0; j < b.size(); ++ j)\
    {\
        k = k - 1ll * p * b[j] + d[i + j];\
        d[i + j] = k % MOD;\
        k /= MOD;\
        if (d[i + j] < 0) d[i + j] += MOD, k --;\
    }\
    if (k) d[i + b.size()] += k;\
    c[i] += p;\
}
#define __get_val(x, y, z) (10ull * MOD * ((y) + 1 < (z)? x[(y) + 1]: 0) + 10ull * x[(y)] + ((y) - 1 >= 0? x[(y) - 1]: 0) / (MOD / 10))
void trial_division(const __base_t &a, const __base_t &b, __base_t &c, __base_t &d)
{
    if(a.size() < b.size())
    {
        c.resize(0);
        d = a;
        return;
    }

    c, d = a;
    c.clear();
    c.resize(a.size() - b.size() + 1);

    for(int i = a.size() - b.size(); ~i; -- i)
    {
        int p;

        while(p = __get_val(d, i + (int)b.size() - 1, d.size()) / (__get_val(b, (int)b.size() - 1, b.size()) + 1), p)
            __trial_division_subt();

        p = 1;

        for(int j = b.size() - 1; ~j; -- j)
            if(d[j + i] != b[j])
            {
                p = b[j] < d[j + i];
                break;
            }

        if(p)
            __trial_division_subt();
    }

    while(c.size() > 1 && !c[c.size() - 1])
        c.pop_back();

    while(d.size() > 1 && !d[d.size() - 1])
        d.pop_back();
}

__base_t divi(const __base_t &a, const __base_t &b)
{
    __base_t c, d;
    trial_division(a, b, c, d);
    return c;
}

__base_t modu(const __base_t &a, const __base_t &b)
{
    __base_t c, d;
    trial_division(a, b, c, d);
    return d;
}
}


struct BigInt
{
    bool is_neg;
    __base_t data;

    BigInt() {}
    BigInt(LL x) {
        is_neg = x < 0;
        data = __BigInt_b::convert_b(abs(x));
    }

    BigInt(const char *s) {
        if(s[0] == '-')
            is_neg = 1, data = __BigInt_b::convert_b(s + 1);
        else
            is_neg = 0, data = __BigInt_b::convert_b(s);
    }

    void to_string(char *s) const {
        if(data.size() == 1 && data[0] == 0)
            return strcpy(s, "0"), void();
        else {
            if(is_neg) {
                s[0] = '-';
                s++;
            }

            __BigInt_b::convert_s(data, s);
        }
    }

    LL to_int() const {
        return (is_neg ? -1 : 1) * __BigInt_b::convert_i(data);
    }

    BigInt operator + (const BigInt &b) const;
    BigInt operator - (const BigInt &b) const;
    template <typename T> BigInt &operator += (const T &b);
    template <typename T> BigInt &operator -= (const T &b);
    template <typename T> BigInt &operator *= (const T &b);
    template <typename T> BigInt &operator /= (const T &b);
    template <typename T> BigInt &operator %= (const T &b);

    BigInt &operator /= (int b);

};
void print(const BigInt &x)
{
    static char buf[2000010];
    x.to_string(buf);
    printf("%s", buf);
}
void println(const BigInt &x)
{
    static char buf[2000010];
    x.to_string(buf);
    printf("%s\n", buf);
}
void read(BigInt &x)
{
    static char buf[1000010];
    scanf("%s", buf);
    x = (BigInt)(buf);
}

bool operator == (const BigInt &a, const BigInt &b)
{
    if(a.is_neg != b.is_neg)
        return 0;

    return __BigInt_b::__comp(a.data, b.data) == 0;
}
bool operator != (const BigInt &a, const BigInt &b)
{
    if(a.is_neg != b.is_neg)
        return 1;

    return __BigInt_b::__comp(a.data, b.data) != 0;
}
bool operator < (const BigInt &a, const BigInt &b)
{
    if(a.is_neg != b.is_neg)
        return a.is_neg;

    return __BigInt_b::__comp(a.data, b.data) * (a.is_neg ? -1 : 1) < 0;
}
bool operator > (const BigInt &a, const BigInt &b)
{
    if(a.is_neg != b.is_neg)
        return !a.is_neg;

    return __BigInt_b::__comp(a.data, b.data) * (a.is_neg ? -1 : 1) > 0;
}
bool operator <= (const BigInt &a, const BigInt &b)
{
    if(a.is_neg != b.is_neg)
        return a.is_neg;

    return __BigInt_b::__comp(a.data, b.data) * (a.is_neg ? -1 : 1) <= 0;
}
bool operator >= (const BigInt &a, const BigInt &b)
{
    if(a.is_neg != b.is_neg)
        return !a.is_neg;

    return __BigInt_b::__comp(a.data, b.data) * (a.is_neg ? -1 : 1) >= 0;
}

BigInt link(bool _is_neg, const __base_t &_data)
{
    BigInt c;
    c.is_neg = _is_neg;
    c.data = _data;

    if(_data.size() == 1 && _data[0] == 0)
        c.is_neg = 0;

    return c;
}

BigInt BigInt::operator + (const BigInt &b) const
{
    if(is_neg ^ b.is_neg)
    {
        if(__BigInt_b::__comp(data, b.data) >= 0)
            return link(is_neg, __BigInt_b::subt(data, b.data));
        else
            return link(b.is_neg, __BigInt_b::subt(b.data, data));
    }
    else
        return link(is_neg, __BigInt_b::addi(b.data, data));
}

BigInt BigInt::operator - (const BigInt &b) const
{
    if(is_neg ^ b.is_neg)
        return link(is_neg, __BigInt_b::addi(b.data, data));
    else
    {
        if(__BigInt_b::__comp(data, b.data) >= 0)
            return link(is_neg, __BigInt_b::subt(data, b.data));
        else
            return link(!is_neg, __BigInt_b::subt(b.data, data));
    }
}

BigInt operator * (const BigInt &a, const BigInt &b)
{
    return link(a.is_neg ^ b.is_neg, __BigInt_b::mult(a.data, b.data));
}
BigInt operator / (const BigInt &a, int b)
{
    return link(a.is_neg ^ (b < 0 ? 1 : 0), __BigInt_b::divi(a.data, abs(b)));
}
int operator % (const BigInt &a, int b)
{
    return (a.is_neg ? -1 : 1) * __BigInt_b::modu(a.data, abs(b));
}
BigInt operator / (const BigInt &a, const BigInt &b)
{
    return link(a.is_neg ^ b.is_neg, __BigInt_b::divi(a.data, b.data));
}
BigInt operator % (const BigInt &a, const BigInt &b)
{
    return link(a.is_neg, __BigInt_b::modu(a.data, b.data));
}

#define __ext_opt(opt, __opt)\
template <typename T> BigInt operator opt (const T &a, const BigInt &b) { return (BigInt)(a) opt b;}\
template <typename T> BigInt operator opt (const BigInt &a, const T &b) { return a opt (BigInt)(b);}\
template <typename T> BigInt & BigInt::operator __opt (const T &b) {*this = *this opt (BigInt)b; return *this;}

__ext_opt(+, +=)
__ext_opt(-, -=)
__ext_opt(*, *=)
__ext_opt(/, /=)
__ext_opt(%, %=)

BigInt & BigInt::operator /= (int b)
{
    *this = *this / b;
    return *this;
}

BigInt gcd(BigInt a,BigInt b)
{
    if(a==0LL)
        return b;

    return gcd(b%a,a);
}
#undef LL
#undef MOD
#undef __base_t
#undef __ext_opt

int main()
{
#ifdef Test
#endif
    int T;
    cin>>T;

    while(T--)
    {
        BigInt a,b,c;
        read(a);
        read(b);
        read(c);

        if(gcd(a,gcd(b,c))==1)
        {
            while(1)
            {
                BigInt d=gcd(b,c);

                if(d==1)
                    break;

                c/=d;
            }

            println(c);
        }
        else
            printf("-1\n");

    }

    return 0;
}

