#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll fdiv(ll a,ll b){ll q=a/b; if((a%b!=0)&&((a<0)!=(b<0)))q--; return q;}
ll cdiv(ll a,ll b){return -fdiv(-a,b);}
int main(){
    int n,m,w,h; scanf("%d %d %d %d",&n,&m,&w,&h);
    vector<ll> hi(w+1,LLONG_MAX/4),lo(w+1,LLONG_MIN/4); // max allowed int y, min allowed int y
    for(int t=0;t<2;t++){
        int c=t?m:n;
        vector<ll> px(c),py(c);
        for(int i=0;i<c;i++)scanf("%lld %lld",&px[i],&py[i]);
        for(int i=0;i<c;i++){
            int x=px[i];
            if(t==0)hi[x]=min(hi[x],py[i]-1); else lo[x]=max(lo[x],py[i]+1);
            if(i+1<c&&px[i+1]>px[i]){
                ll den=px[i+1]-px[i];
                for(ll xx=px[i]+1;xx<px[i+1];xx++){
                    ll num=py[i]*den+(py[i+1]-py[i])*(xx-px[i]);
                    if(t==0)hi[xx]=min(hi[xx],cdiv(num,den)-1);
                    else lo[xx]=max(lo[xx],fdiv(num,den)+1);
                }
            }
        }
    }
    ll a=0,b=0;
    if(lo[0]>0||hi[0]<0){puts("impossible");return 0;}
    for(int x=1;x<=w;x++){
        a--;b++;
        if(a<lo[x]){a=lo[x]; if(((a-x)%2+2)%2)a++;}
        if(b>hi[x]){b=hi[x]; if(((b-x)%2+2)%2)b--;}
        if(a>b){puts("impossible");return 0;}
    }
    printf("%lld %lld\n",a,b);
}
