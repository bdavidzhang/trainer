#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
typedef unsigned long long ull;
struct Edge{ld ax,ay,bx,by;int obj;};
struct Trans{int type;int target;ld dt;int child;};
struct Node{ld x,y,vx,vy,T;int cmask=-1;Trans ct;int smask=-1;Trans sk;vector<pair<int,int>> kids;}; // type 0 exit,1 bounce(wall/obj), target: obj index or -1
int W,H,n,m;
vector<Edge> E;vector<Node> nodes;
vector<int> cnt;int mask;
Trans compute(int id){
    if(nodes[id].cmask==mask)return nodes[id].ct; // mask only shrinks, so the latest entry suffices
    const Node nd=nodes[id];
    ld best=1e30L;int be=-100; // -1 left,-2 right,-3 top,-4 bottom
    if(nd.vx<0){ld t=max((ld)0,(0-nd.x)/nd.vx);if(t<best){best=t;be=-1;}}
    if(nd.vx>0){ld t=max((ld)0,(W-nd.x)/nd.vx);if(t<best){best=t;be=-2;}}
    if(nd.vy>0){ld t=max((ld)0,(H-nd.y)/nd.vy);if(t<best){best=t;be=-3;}}
    if(nd.vy<0){ld t=max((ld)0,(0-nd.y)/nd.vy);if(t<best){best=t;be=-4;}}
    for(int i=0;i<(int)E.size();i++){
        const Edge&e=E[i];if(!(mask>>e.obj&1))continue;
        ld ex=e.bx-e.ax,ey=e.by-e.ay;
        ld den=nd.vx*ey-nd.vy*ex;if(fabsl(den)<1e-15L)continue;
        ld wx=e.ax-nd.x,wy=e.ay-nd.y;
        ld t=(wx*ey-wy*ex)/den, u=(wx*nd.vy-wy*nd.vx)/den;
        if(t>1e-9L&&u>=-1e-12L&&u<=1+1e-12L&&t<best){best=t;be=i;}
    }
    Trans tr;tr.dt=best;
    if(be==-4){tr.type=0;tr.target=-1;tr.child=-1;}
    else{
        tr.type=1;tr.target=be>=0?E[be].obj:-1;
        int found=-1;for(auto&kv:nd.kids)if(kv.first==be)found=kv.second;
        if(found>=0)tr.child=found;
        else{
            Node c;c.x=nd.x+nd.vx*best;c.y=nd.y+nd.vy*best;c.T=nd.T+best;c.vx=nd.vx;c.vy=nd.vy;
            if(be==-1){c.x=0;c.vx=-c.vx;}
            else if(be==-2){c.x=W;c.vx=-c.vx;}
            else if(be==-3){c.y=H;c.vy=-c.vy;}
            else{const Edge&e=E[be];ld ex=e.bx-e.ax,ey=e.by-e.ay;ld L=sqrtl(ex*ex+ey*ey);ex/=L;ey/=L;
                ld d=nd.vx*ex+nd.vy*ey;c.vx=2*d*ex-nd.vx;c.vy=2*d*ey-nd.vy;}
            ld L=sqrtl(c.vx*c.vx+c.vy*c.vy);c.vx/=L;c.vy/=L;
            nodes.push_back(c);tr.child=nodes.size()-1;nodes[id].kids.push_back({be,tr.child});
        }
    }
    nodes[id].cmask=mask;nodes[id].ct=tr;return tr;
}
// Next object hit / exit from node id under the current mask, skipping over wall bounces.
// Returned dt is the absolute path time of that event. Memoised on every wall node passed.
vector<int> pathBuf;
Trans skipWalls(int id){
    pathBuf.clear();int cur=id;Trans res;
    while(true){
        if(nodes[cur].smask==mask){res=nodes[cur].sk;break;}
        Trans tr=compute(cur);
        if(tr.type==1&&tr.target<0){pathBuf.push_back(cur);cur=tr.child;continue;}
        res=tr;res.dt=nodes[cur].T+tr.dt;nodes[cur].smask=mask;nodes[cur].sk=res;break;
    }
    for(int v:pathBuf){nodes[v].smask=mask;nodes[v].sk=res;}
    return res;
}
int main(){
    double l,r,s;
    if(scanf("%d %d %d %d %lf %lf %lf",&W,&H,&n,&m,&l,&r,&s)!=7)return 0;
    cnt.resize(m);
    for(int i=0;i<m;i++){int p;scanf("%d",&p);vector<double>xs(p),ys(p);for(int j=0;j<p;j++)scanf("%lf %lf",&xs[j],&ys[j]);
        scanf("%d",&cnt[i]);
        for(int j=0;j<p;j++){int k=(j+1)%p;E.push_back({xs[j],ys[j],xs[k],ys[k],i});}}
    mask=(1<<m)-1;
    {Node a;a.x=l;a.y=0;ld L=sqrtl((ld)r*r+(ld)s*s);a.vx=r/L;a.vy=s/L;a.T=0;nodes.push_back(a);}
    // each ball: current node, launch time, pending transition
    vector<int> bn(n,0);vector<Trans> bt(n);
    typedef pair<ld,int> PI;
    priority_queue<PI,vector<PI>,greater<PI>> pq;
    auto schedule=[&](int b){bt[b]=skipWalls(bn[b]);pq.push({(ld)b+bt[b].dt,b});};
    for(int b=0;b<n;b++)schedule(b);
    const ld EPS=1.01e-7L;
    vector<vector<int>> grp(m);
    vector<int> batch,used,resched;
    while(!pq.empty()){
        ld t0=pq.top().first;int b0=pq.top().second;pq.pop();
        if(pq.empty()||pq.top().first>t0+EPS){
            // fast path: a lone wall bounce / exit / stale event
            Trans&tr=bt[b0];
            if(tr.type==0)continue;
            if(tr.target<0){bn[b0]=tr.child;schedule(b0);continue;}
            if(!(mask>>tr.target&1)){schedule(b0);continue;}
        }
        batch.clear();used.clear();resched.clear();batch.push_back(b0);
        while(!pq.empty()&&pq.top().first<=t0+EPS){batch.push_back(pq.top().second);pq.pop();}
        for(int b:batch){
            Trans&tr=bt[b];
            if(tr.type==0)continue; // left the screen
            if(tr.target<0){bn[b]=tr.child;schedule(b);continue;}
            if(!(mask>>tr.target&1)){schedule(b);continue;} // stale: object already gone
            if(grp[tr.target].empty())used.push_back(tr.target);
            grp[tr.target].push_back(b);
        }
        // all balls striking one object at the same instant: either they finish it off
        // (then every one of them flies through) or they all bounce
        for(int o:used){
            cnt[o]-=(int)grp[o].size();
            if(cnt[o]<=0){mask&=~(1<<o);}
            else for(int b:grp[o])bn[b]=bt[b].child;
            for(int b:grp[o])resched.push_back(b);
            grp[o].clear();
        }
        for(int b:resched)schedule(b);
    }
    for(int i=0;i<m;i++)printf("%d%c",max(0,cnt[i]),i+1<m?' ':'\n');
}
