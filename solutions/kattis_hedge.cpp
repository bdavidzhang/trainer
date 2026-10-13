#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __int128 LL;
struct Fr{ll n,d;}; // n/d, d>0, n>=0
static inline bool lt(const Fr&a,const Fr&b){return (LL)a.n*b.d<(LL)b.n*a.d;}
static inline bool eq(const Fr&a,const Fr&b){return (LL)a.n*b.d==(LL)b.n*a.d;}
static inline Fr dv(const Fr&a,const Fr&b){return {a.n*b.d,a.d*b.n};} // a/b
struct Pt{ll x,y;};
static inline ll cross(Pt a,Pt b){return a.x*b.y-a.y*b.x;}
static inline ll dot(Pt a,Pt b){return a.x*b.x+a.y*b.y;}
static inline int half(Pt a){return (a.y>0||(a.y==0&&a.x>0))?0:1;}
static inline bool angLess(Pt a,Pt b){int ha=half(a),hb=half(b);if(ha!=hb)return ha<hb;return cross(a,b)>0;}
static inline bool sameDir(Pt a,Pt b){return cross(a,b)==0&&dot(a,b)>0;}
// radius (multiple of d) where line p-q meets ray d
static inline Fr rad(Pt p,Pt q,Pt d){ll nu=cross(q,p);Pt w={q.x-p.x,q.y-p.y};ll de=cross(w,d);if(de<0){de=-de;nu=-nu;}return {nu,de};}
struct Stripes{vector<Fr> loL,loR,hiL,hiR;};
struct List{int s;Fr rloL,rloR,rhiL,rhiR;int ptr;};
vector<Stripes> SS;vector<List> lists;
static inline Fr LO(const List&l,int k){const Stripes&s=SS[l.s];Fr a=dv(s.loL[k],l.rloL),b=dv(s.loR[k],l.rloR);return lt(b,a)?b:a;}
static inline Fr HI(const List&l,int k){const Stripes&s=SS[l.s];Fr a=dv(s.hiL[k],l.rhiL),b=dv(s.hiR[k],l.rhiR);return lt(a,b)?b:a;}
int main(){
    int n,m;scanf("%d",&n);vector<Pt> A(n);for(auto&p:A)scanf("%lld %lld",&p.x,&p.y);
    scanf("%d",&m);vector<Pt> B(m);for(auto&p:B)scanf("%lld %lld",&p.x,&p.y);
    vector<Pt> dirs;for(auto&p:A)dirs.push_back(p);for(auto&p:B)dirs.push_back(p);
    sort(dirs.begin(),dirs.end(),angLess);
    {vector<Pt> u;for(auto&p:dirs)if(u.empty()||!sameDir(u.back(),p))u.push_back(p);dirs=u;}
    int D=dirs.size();
    auto dirIdx=[&](Pt p){int i=lower_bound(dirs.begin(),dirs.end(),p,angLess)-dirs.begin();
        // lower_bound with angLess: first not less than p -> same direction
        return i;};
    // per slab: sorted A edges with rL,rR
    vector<vector<pair<Fr,Fr>>> slabE(D);
    SS.resize(D);
    for(int i=0;i<D;i++){
        Pt d1=dirs[i],d2=dirs[(i+1)%D];Pt mid={d1.x+d2.x,d1.y+d2.y};
        auto&v=slabE[i];
        for(int e=0;e<n;e++){Pt p=A[e],q=A[(e+1)%n];ll c=cross(p,q);if(c==0)continue;Pt u=c>0?p:q,w=c>0?q:p;
            if(cross(u,mid)>0&&cross(mid,w)>0)v.push_back({rad(p,q,d1),rad(p,q,d2)});}
        sort(v.begin(),v.end(),[](const pair<Fr,Fr>&a,const pair<Fr,Fr>&b){if(!eq(a.first,b.first))return lt(a.first,b.first);return lt(a.second,b.second);});
        Stripes&s=SS[i];int c=v.size();
        for(int k=0;2*k<c;k++){
            if(k==0){s.loL.push_back({0,1});s.loR.push_back({0,1});}
            else{s.loL.push_back(v[2*k-1].first);s.loR.push_back(v[2*k-1].second);}
            s.hiL.push_back(v[2*k].first);s.hiR.push_back(v[2*k].second);
        }
        for(int e=0;e<m;e++){Pt p=B[e],q=B[(e+1)%m];ll cc=cross(p,q);if(cc==0)continue;Pt u=cc>0?p:q,w=cc>0?q:p;
            if(cross(u,mid)>0&&cross(mid,w)>0){Fr a=rad(p,q,d1),b=rad(p,q,d2);lists.push_back({i,a,b,a,b,0});}}
    }
    // radial edges of B
    vector<int> pseudo(D,-1);
    for(int e=0;e<m;e++){Pt p=B[e],q=B[(e+1)%m];if(cross(p,q)!=0)continue;
        int i=dirIdx(p);Pt d=dirs[i];ll dd=dot(d,d);
        if(pseudo[i]<0){
            vector<Fr> bp;
            for(auto&x:slabE[i])bp.push_back(x.first);
            for(auto&x:slabE[(i+D-1)%D])bp.push_back(x.second);
            vector<pair<Fr,Fr>> radA;
            for(int a=0;a<n;a++){Pt u=A[a],w=A[(a+1)%n];if(cross(u,w)!=0||!sameDir(u,d))continue;
                Fr r1={dot(u,d),dd},r2={dot(w,d),dd};if(lt(r2,r1))swap(r1,r2);radA.push_back({r1,r2});bp.push_back(r1);bp.push_back(r2);}
            sort(bp.begin(),bp.end(),lt);
            Stripes s;Fr prev={0,1};
            for(auto&b:bp){if(!lt(prev,b))continue;
                int cnt=0;for(auto&x:slabE[i])if(!lt(prev,x.first))cnt++;
                bool in=(cnt%2==0);
                if(in)for(auto&x:radA)if(!lt(prev,x.first)&&!lt(x.second,b)){in=false;break;}
                if(in){s.loL.push_back(prev);s.loR.push_back(prev);s.hiL.push_back(b);s.hiR.push_back(b);}
                prev=b;}
            pseudo[i]=SS.size();SS.push_back(s);
        }
        Fr r1={dot(p,d),dd},r2={dot(q,d),dd};if(lt(r2,r1))swap(r1,r2);
        lists.push_back({pseudo[i],r2,r2,r1,r1,0});
    }
    // sweep
    Fr t={0,1};
    auto cmp=[](const pair<Fr,int>&a,const pair<Fr,int>&b){return lt(b.first,a.first);};
    priority_queue<pair<Fr,int>,vector<pair<Fr,int>>,decltype(cmp)> pq(cmp);
    for(int li=0;li<(int)lists.size();li++){List&l=lists[li];int sz=SS[l.s].loL.size();if(sz==0)continue;
        Fr h=HI(l,0);if(lt(t,h))t=h;l.ptr=1;if(sz>1)pq.push({LO(l,1),li});}
    while(true){
        Fr nt=t;
        while(!pq.empty()&&lt(pq.top().first,t)){int li=pq.top().second;pq.pop();List&l=lists[li];int sz=SS[l.s].loL.size();
            int k=l.ptr;while(k<sz&&lt(LO(l,k),t))k++;
            Fr h=HI(l,k-1);if(lt(nt,h))nt=h;
            l.ptr=k;if(k<sz)pq.push({LO(l,k),li});}
        if(eq(nt,t))break;
        t=nt;
    }
    printf("%.10f\n",(double)((long double)t.d/(long double)t.n));
}
