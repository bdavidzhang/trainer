#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int h,w,n;
vector<int> pr,pd;
static int fnd(vector<int>&p,int x){int r=x;while(p[r]!=r)r=p[r];while(p[x]!=r){int y=p[x];p[x]=r;x=y;}return r;}
int main(){
    scanf("%d %d %d",&h,&w,&n);
    vector<string> g(h);
    {static char buf[1000005];for(int i=0;i<h;i++){scanf("%s",buf);g[i]=buf;}}
    vector<int> sr(n),sc(n),er(n),ec(n);vector<ll> stt(n);
    int r=h-1,c=0;ll t=1;
    for(int i=0;i<n;i++){
        char d[10];int x;scanf("%s %d",d,&x);
        sr[i]=r;sc[i]=c;stt[i]=t;
        if(d[0]=='u')r-=x;else if(d[0]=='d')r+=x;else if(d[0]=='l')c-=x;else c+=x;
        er[i]=r;ec[i]=c;t+=x;
    }
    ll total=t;
    pr.resize((size_t)h*(w+1));pd.resize((size_t)w*(h+1));
    for(size_t i=0;i<pr.size();i++)pr[i]=i;
    for(size_t i=0;i<pd.size();i++)pd[i]=i;
    vector<ll> L((size_t)h*w,0);
    auto paint=[&](int rr,int cc,ll tm){
        L[(size_t)rr*w+cc]=tm;
        pr[rr*(w+1)+cc]=rr*(w+1)+cc+1;
        pd[cc*(h+1)+rr]=cc*(h+1)+rr+1;
    };
    for(int i=n-1;i>=0;i--){
        if(sr[i]==er[i]){
            int rr=sr[i],lo=min(sc[i],ec[i]),hi=max(sc[i],ec[i]);
            int base=rr*(w+1);
            int x=fnd(pr,base+lo)-base;
            while(x<=hi){paint(rr,x,stt[i]+abs(x-sc[i]));x=fnd(pr,base+x+1)-base;}
        }else{
            int cc=sc[i],lo=min(sr[i],er[i]),hi=max(sr[i],er[i]);
            int base=cc*(h+1);
            int x=fnd(pd,base+lo)-base;
            while(x<=hi){paint(x,cc,stt[i]+abs(x-sr[i]));x=fnd(pd,base+x+1)-base;}
        }
    }
    ll lo=0,hi=total;bool bad=false;
    for(int i=0;i<h&&!bad;i++)for(int j=0;j<w;j++){
        ll v=L[(size_t)i*w+j];
        if(g[i][j]=='#'){if(!v){bad=true;break;}lo=max(lo,v);}
        else if(v)hi=min(hi,v-1);
    }
    if(bad||lo>hi)puts("-1 -1");else printf("%lld %lld\n",lo,hi);
}
