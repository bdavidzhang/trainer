#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __int128 L;
int n; vector<ll> X,Y;
L area(int a,int b,int c){
    L v=(L)(X[b]-X[a])*(Y[c]-Y[a])-(L)(Y[b]-Y[a])*(X[c]-X[a]);
    return v<0?-v:v;
}
int main(){
    ll k; scanf("%d %lld",&n,&k);
    X.resize(n);Y.resize(n);
    for(int i=0;i<n;i++)scanf("%lld %lld",&X[i],&Y[i]);
    if(k==0){puts("0");return 0;}
    ll best=0; set<pair<int,int>> ps;
    auto cand=[&](int a,int b){
        if(a==b)return;
        ll dx=X[a]-X[b],dy=Y[a]-Y[b]; ll d=dx*dx+dy*dy;
        if(d>best){best=d;ps.clear();}
        if(d==best)ps.insert({min(a,b),max(a,b)});
    };
    int j=1;
    for(int i=0;i<n;i++){
        int i2=(i+1)%n;
        while(area(i,i2,(j+1)%n)>area(i,i2,j))j=(j+1)%n;
        for(int a:{i,i2})for(int b:{(j+n-1)%n,j,(j+1)%n})cand(a,b);
    }
    ll c=ps.size();
    // minimal m with 4 m^2 D2 >= k^2
    L kk=(L)k*k;
    ll lo=1,hi=1000000001LL;
    while(lo<hi){ll m=(lo+hi)/2; if((L)4*m*m*best>=kk)hi=m; else lo=m+1;}
    ll m1=lo;
    if(m1<=c){printf("%lld\n",m1);return 0;}
    ll m2=m1; if((L)4*m1*m1*best==kk)m2=m1+1;
    printf("%lld\n",m2);
}
