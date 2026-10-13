#include <bits/stdc++.h>
using namespace std;
int N,M,K;
int segId[15][15][4]; // from (r,c) heading dir
int dr[4]={-1,0,1,0}, dc[4]={0,-1,0,1}; // N,W,S,E : left of dir i is (i+1)%4, right is (i+3)%4
struct Seg{int r0,c0,r1,c1,T,dir;int fn[3];}; // fn bitmask: 1=L,2=S,4=R
vector<Seg> segs;
int dirOf(int a,int b,int c,int d){for(int i=0;i<4;i++)if(a+dr[i]==c&&b+dc[i]==d)return i;return -1;}
int main(){
    scanf("%d %d %d",&N,&M,&K);
    int D;scanf("%d",&D);
    memset(segId,-1,sizeof segId);
    for(int i=0;i<D;i++){
        Seg s;scanf("%d %d %d %d %d",&s.r0,&s.c0,&s.r1,&s.c1,&s.T);
        s.dir=dirOf(s.r0,s.c0,s.r1,s.c1);
        for(int j=0;j<K;j++){char b[8];scanf("%s",b);int f=0;for(char*p=b;*p;p++){if(*p=='L')f|=1;if(*p=='S')f|=2;if(*p=='R')f|=4;}s.fn[j]=f;}
        segId[s.r0][s.c0][s.dir]=i;segs.push_back(s);
    }
    // transitions: for each seg, lane -> list of (target seg, target lane, isLeft)
    struct Tr{int e,l,left;};
    vector<vector<Tr>> tr(D*K);
    for(int e=0;e<D;e++){
        Seg&s=segs[e];
        for(int ty=0;ty<3;ty++){
            int nd= ty==0?(s.dir+1)%4: ty==1?s.dir:(s.dir+3)%4;
            int te=segId[s.r1][s.c1][nd];
            vector<int> ls;
            for(int j=0;j<K;j++)if(s.fn[j]>>ty&1)ls.push_back(j);
            if(ls.empty()||te<0)continue;
            int cnt=ls.size();
            if(ty<2){
                for(int i=0;i<cnt;i++){
                    if(i<cnt-1)tr[e*K+ls[i]].push_back({te,i,ty==0});
                    else for(int x=i;x<K;x++)tr[e*K+ls[i]].push_back({te,x,ty==0});
                }
            }else{
                // number from right
                for(int i=0;i<cnt;i++){
                    int lane=ls[cnt-1-i];
                    if(i<cnt-1)tr[e*K+lane].push_back({te,K-1-i,0});
                    else for(int x=i;x<K;x++)tr[e*K+lane].push_back({te,K-1-x,0});
                }
            }
        }
    }
    int P;scanf("%d",&P);
    while(P--){
        int a,b,c,d,e2,f,g,h,X,Y;scanf("%d %d %d %d %d %d %d %d %d %d",&a,&b,&c,&d,&e2,&f,&g,&h,&X,&Y);
        int s=segId[a][b][dirOf(a,b,c,d)], t=segId[e2][f][dirOf(e2,f,g,h)];
        int XS=X+1,YS=Y+1;
        auto id=[&](int e,int l,int x,int y){return ((e*K+l)*XS+x)*YS+y;};
        vector<int> dist(D*K*XS*YS,INT_MAX);
        priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
        dist[id(s,K-1,0,0)]=segs[s].T/2;pq.push({segs[s].T/2,id(s,K-1,0,0)});
        while(!pq.empty()){
            auto [dd,u]=pq.top();pq.pop();
            if(dd>dist[u])continue;
            int y=u%YS,x=u/YS%XS,l=u/YS/XS%K,e=u/YS/XS/K;
            auto relax=[&](int v,int nd){if(nd<dist[v]){dist[v]=nd;pq.push({nd,v});}};
            if(y<Y){ if(l>0)relax(id(e,l-1,x,y+1),dd); if(l<K-1)relax(id(e,l+1,x,y+1),dd);}
            for(auto&q:tr[e*K+l]){
                int nx=x+q.left; if(nx>X)continue;
                relax(id(q.e,q.l,nx,y),dd+segs[q.e].T);
            }
        }
        int best=INT_MAX;
        for(int x=0;x<=X;x++)for(int y=0;y<=Y;y++)best=min(best,dist[id(t,K-1,x,y)]);
        if(best==INT_MAX)puts("-1");else printf("%d\n",best-segs[t].T/2);
    }
}
