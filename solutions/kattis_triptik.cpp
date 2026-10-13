#include <bits/stdc++.h>
using namespace std;
int n,k,N;
struct T{int a[4];};
static T tb[18][100005];
T mrg(const T&x,const T&y){
    T r; int i=0,j=0;
    for(int c=0;c<4;c++){
        if(c>=k){r.a[c]=0;continue;}
        int xv=i<k?x.a[i]:0, yv=j<k?y.a[j]:0;
        if(xv==yv){r.a[c]=xv; i++; j++;}
        else if(xv>yv){r.a[c]=xv;i++;}
        else {r.a[c]=yv;j++;}
    }
    return r;
}
int main(){
    scanf("%d %d",&n,&k);
    vector<pair<long long,int>> p; p.push_back({0,0});
    for(int i=1;i<=n;i++){long long x;scanf("%lld",&x);p.push_back({2*x,i});}
    sort(p.begin(),p.end()); N=n+1;
    vector<int> pos(N); vector<long long> xs(N);
    for(int i=0;i<N;i++){pos[p[i].second]=i;xs[i]=p[i].first; tb[0][i]=T{{p[i].second,0,0,0}};}
    vector<int> lg(N+2,0); for(int i=2;i<=N+1;i++)lg[i]=lg[i/2]+1;
    for(int j=1;(1<<j)<=N;j++)for(int i=0;i+(1<<j)<=N;i++)tb[j][i]=mrg(tb[j-1][i],tb[j-1][i+(1<<(j-1))]);
    const int LV=30;
    vector<int> dist((size_t)LV*N,-1), ans(N,-1);
    vector<int> q; q.reserve((size_t)LV*N);
    int st=1*N+pos[0]; dist[st]=0; q.push_back(st);
    for(size_t h=0;h<q.size();h++){
        int s=q[h], lv=s/N, i=s%N, d=dist[s];
        long long hw=1LL<<lv;
        int l=lower_bound(xs.begin(),xs.end(),xs[i]-hw)-xs.begin();
        int r=upper_bound(xs.begin(),xs.end(),xs[i]+hw)-xs.begin()-1;
        int j=lg[r-l+1];
        T t=mrg(tb[j][l],tb[j][r-(1<<j)+1]);
        int me=p[i].second;
        for(int c=0;c<k;c++){
            int w=t.a[c]; if(w<=0)continue;
            if(w==me){ if(ans[me]<0)ans[me]=d; continue;}
            int ns=lv*N+pos[w]; if(dist[ns]<0){dist[ns]=d+1;q.push_back(ns);}
        }
        if(lv+1<LV){int ns=s+N; if(dist[ns]<0){dist[ns]=d+1;q.push_back(ns);}}
        if(lv>0){int ns=s-N; if(dist[ns]<0){dist[ns]=d+1;q.push_back(ns);}}
    }
    for(int i=1;i<=n;i++)printf("%d\n",ans[i]);
}
