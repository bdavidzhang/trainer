#include <bits/stdc++.h>
using namespace std;
typedef long long ll; typedef __int128 LL;
struct P{ll x,y;};
static LL cr(const P&a,const P&b,const P&c){return (LL)(b.x-a.x)*(c.y-a.y)-(LL)(b.y-a.y)*(c.x-a.x);}
static LL cr0(const P&a,const P&b){return (LL)a.x*b.y-(LL)a.y*b.x;}
int m; vector<P> h;
static bool vis(int i,const P&p){ i%=m; return cr(h[i],h[(i+1)%m],p)<0; }
int main(){
    int n,k; scanf("%d %d",&n,&k);
    vector<P> a(n); for(auto&p:a) scanf("%lld %lld",&p.x,&p.y);
    vector<P> s(a.begin(),a.begin()+k);
    sort(s.begin(),s.end(),[](const P&u,const P&v){return u.x<v.x||(u.x==v.x&&u.y<v.y);});
    h.assign(2*k,P{0,0}); int t=0;
    for(int i=0;i<k;i++){while(t>=2&&cr(h[t-2],h[t-1],s[i])<=0)t--;h[t++]=s[i];}
    int r=t-1;
    for(int i=k-2,lo=t+1;i>=0;i--){while(t>=lo&&cr(h[t-2],h[t-1],s[i])<=0)t--;h[t++]=s[i];}
    t--; h.resize(t); m=t;
    vector<LL> pre(m+1,0);
    for(int i=0;i<m;i++) pre[i+1]=pre[i]+cr0(h[i],h[(i+1)%m]);
    LL tot=pre[m], best=tot;
    ll minx=h[0].x,maxx=h[r].x;
    for(int q=k;q<n;q++){
        const P&p=a[q]; int v=-1,u=-1;
        if(p.x>minx&&p.x<maxx){
            int lo=0,hi=r; // lower chain: h[lo].x<=p.x<h[hi].x
            while(hi-lo>1){int mid=(lo+hi)/2; if(h[mid].x<=p.x)lo=mid;else hi=mid;}
            int le=lo;
            lo=r;hi=m; // upper chain: x decreasing; h[lo].x>p.x>=h[hi].x
            while(hi-lo>1){int mid=(lo+hi)/2; if(h[mid%m].x>p.x)lo=mid;else hi=mid;}
            int ue=lo;
            bool vl=vis(le,p),vu=vis(ue,p);
            if(!vl&&!vu) continue;
            if(vl&&!vu){v=le;u=ue;} else if(vu&&!vl){v=ue;u=le;}
        } else if(p.x<=minx){
            if(vis(0,p))v=0; else if(vis(m-1,p))v=m-1;
            if(!vis(r,p))u=r; else if(!vis(r-1+m,p))u=(r-1+m)%m;
        } else {
            if(vis(r,p))v=r; else if(vis(r-1+m,p))v=(r-1+m)%m;
            if(!vis(0,p))u=0; else if(!vis(m-1,p))u=m-1;
        }
        if(v<0||u<0){ // fallback linear scan
            v=u=-1;
            for(int i=0;i<m;i++){ if(vis(i,p))v=i; else u=i; }
            if(v<0) continue;
        }
        int d=((u-v)%m+m)%m; int lo=0,hi=d;
        while(hi-lo>1){int mid=(lo+hi)/2; if(vis(v+mid,p))lo=mid;else hi=mid;}
        int b=(v+lo)%m;
        int e=((v-u)%m+m)%m; lo=0;hi=e;
        while(hi-lo>1){int mid=(lo+hi)/2; if(vis(u+mid,p))hi=mid;else lo=mid;}
        int f=(u+hi)%m;
        int st=(b+1)%m, en=f;
        LL sum = en>=st ? pre[en]-pre[st] : tot-(pre[st]-pre[en]);
        sum += cr0(h[en],p)+cr0(p,h[st]);
        if(sum>best)best=sum;
    }
    unsigned long long A=(unsigned long long)best;
    printf("%llu.%c\n",A/2,(A&1)?'5':'0');
}
