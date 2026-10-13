#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;typedef __int128 L;
L pw(ull b,int e){L r=1;for(int i=0;i<e;i++){r*=b;if(r>(L)2e18)return r;}return r;}
int main(){ull x;cin>>x;
    if(x==1){puts("1");return 0;}
    ull best=0;
    for(int k=2;k<=60;k++){
        ull r=(ull)llround(pow((long double)x,1.0L/k));
        ull n=0;
        for(ull c=(r>2?r-2:1);c<=r+2;c++)if(pw(c,k)==(L)x){n=c;break;}
        if(!n)continue;
        // count divisors of n (n<=1e9)
        ull t=n;int d=1;
        for(ull p=2;p*p<=t;p++)if(t%p==0){int e=0;while(t%p==0){t/=p;e++;}d*=e+1;}
        if(t>1)d*=2;
        if(d==k&&(best==0||n<best))best=n;
    }
    if(best)cout<<best<<"\n";else puts("-1");}
