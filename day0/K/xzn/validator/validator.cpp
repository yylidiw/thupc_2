//#define Test
#include<bits/stdc++.h>
using namespace std;
const int Nmax=1e6+7;
int main()
{
    #ifdef Test
    #endif
    int T;
    cin>>T;

    assert(T <= 10);
    assert(T >= 1);
    while(T--)
    {
        string a ,b,c;
        cin>>a>>b>>c;
        int lena=a.length(),lenb=b.length(),lenc=c.length();
        assert(lena<=2000 && lena>=1);
        assert(lenb<=2000 && lenb>=1);
        assert(lenc<=2000 && lenc>=1);
        for(auto ch:a)
            assert(ch>='0' && ch<='9');
        for(auto ch:b)
            assert(ch>='0' && ch<='9');
        for(auto ch:c)
            assert(ch>='0' && ch<='9');
    }
    return 0;
}


