//#define Test
#include<bits/stdc++.h>
using namespace std;
const int Nmax=1e6+7;
typedef __int128 ll;
inline void read(ll &x)
{
    char ch;
    ch=getchar();

    while(ch==' ' || ch=='\n')
        ch=getchar();

    for(x = ch - '0'; (ch = getchar()) >= '0' && ch <= '9'; x = x * 10 + ch - '0');

}
inline void write(ll x)
{
    if(x>=10)
        write(x/10);

    putchar(x%10+'0');

}
int main()
{
#ifdef Test
#endif
    int T;
    cin>>T;

    while(T--)
    {
        ll a,b,c;
        read(a);
        read(b);
        read(c);

        if(__gcd(a,__gcd(b,c))!=1)
        {
            printf("-1\n");
            continue;
        }

        ll d=__gcd(b,c);

        while(1)
        {
            ll d2=__gcd(d*d,c);

            if(d==d2)
                break;

            d=d2;
        }

        c/=d;
        write(c);
        putchar('\n');
    }

    return 0;
}


