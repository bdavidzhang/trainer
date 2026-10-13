#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){int n,m;ll k;scanf("%d %d %lld",&n,&m,&k);
    vector<ll> f(n+1),paid(n+1,0);for(int i=1;i<=n;i++)scanf("%lld",&f[i]);
    vector<int> st;ll sumf=0,sump=0,total=0;
    for(int r=1;r<=n+m-1;r++){
        if(r<=n){sumf+=f[r];st.push_back(r);}
        int out=r-m;if(out>=1){sumf-=f[out];sump-=paid[out];}
        ll need=min(k,sumf)-sump;
        while(need>0){int i=st.back();ll c=min(need,f[i]-paid[i]);paid[i]+=c;need-=c;sump+=c;total+=c;
            if(paid[i]==f[i])st.pop_back();}
    }
    printf("%lld\n",total);}
