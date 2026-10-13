#include <bits/stdc++.h>
using namespace std;
const int CAP=45; // 45 lengths in [1,1e9] always contain a triangle (Fibonacci)
struct Pt{int x,y,h;};
int n,q;
vector<Pt> pts;
struct Node{int x1,y1,x2,y2;};
vector<Node> nd;
void build(int o,int l,int r,int dim){
    int x1=INT_MAX,y1=INT_MAX,x2=INT_MIN,y2=INT_MIN;
    for(int i=l;i<r;i++){x1=min(x1,pts[i].x);x2=max(x2,pts[i].x);y1=min(y1,pts[i].y);y2=max(y2,pts[i].y);}
    nd[o]={x1,y1,x2,y2};
    if(r-l<=8) return;
    int m=(l+r)/2;
    if(x2-x1>=y2-y1) nth_element(pts.begin()+l,pts.begin()+m,pts.begin()+r,[](const Pt&a,const Pt&b){return a.x<b.x;});
    else nth_element(pts.begin()+l,pts.begin()+m,pts.begin()+r,[](const Pt&a,const Pt&b){return a.y<b.y;});
    build(2*o,l,m,dim^1);build(2*o+1,m,r,dim^1);
}
int qx1,qy1,qx2,qy2; int got[CAP+5]; int cnt;
void query(int o,int l,int r){
    if(cnt>=CAP) return;
    const Node&a=nd[o];
    if(a.x1>qx2||a.x2<qx1||a.y1>qy2||a.y2<qy1) return;
    bool inside=a.x1>=qx1&&a.x2<=qx2&&a.y1>=qy1&&a.y2<=qy2;
    if(inside){
        if(cnt+(r-l)>=CAP){cnt=CAP;return;}
        for(int i=l;i<r;i++) got[cnt++]=pts[i].h;
        return;
    }
    if(r-l<=8){
        for(int i=l;i<r&&cnt<CAP;i++) if(pts[i].x>=qx1&&pts[i].x<=qx2&&pts[i].y>=qy1&&pts[i].y<=qy2) got[cnt++]=pts[i].h;
        return;
    }
    int m=(l+r)/2;
    query(2*o,l,m);query(2*o+1,m,r);
}
int main(){
    scanf("%d %d",&n,&q);
    pts.resize(n);
    for(auto&p:pts)scanf("%d %d %d",&p.x,&p.y,&p.h);
    nd.resize(4*n+8);
    build(1,0,n,0);
    while(q--){
        scanf("%d %d %d %d",&qx1,&qy1,&qx2,&qy2);
        cnt=0; query(1,0,n);
        int ans=0;
        if(cnt>=CAP) ans=1;
        else{
            sort(got,got+cnt);
            for(int i=0;i+2<cnt;i++) if((long long)got[i]+got[i+1]>got[i+2]){ans=1;break;}
        }
        printf("%d\n",ans);
    }
}
