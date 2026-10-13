#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){int n,k;scanf("%d %d",&n,&k);vector<ll> T(n);ll t=0;
for(int i=0;i<n;i++){ll a;scanf("%lld",&a);t=max(0LL,t-a);T[i]=t;}
sort(T.begin(),T.end());
for(int j=0;j<k;j++){ll b;scanf("%lld",&b);int c=T.end()-lower_bound(T.begin(),T.end(),5*b);printf("%d%c",c,j+1<k?' ':'\n');}
}
