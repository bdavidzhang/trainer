#include <bits/stdc++.h>
using namespace std;
int R,C;char g[55][55];
bool ok(int x1,int y1,int x2,int y2){ // x: column coord, y: row coord
    if(x1==x2||y1==y2)return true;
    if(x1>x2){swap(x1,x2);swap(y1,y2);}
    int dx=x2-x1,dy=y2-y1;
    for(int i=x1;i<x2;i++){int a=y1*dx+(i-x1)*dy,b=a+dy;int lo=min(a,b),hi=max(a,b);
        int j0=lo/dx,j1=(hi+dx-1)/dx-1;
        for(int j=j0;j<=j1;j++)if(g[j][i]=='#')return false;}
    return true;}
int main(){scanf("%d %d",&R,&C);for(int i=0;i<R;i++)scanf("%s",g[i]);
    int W=C+1,V=(R+1)*W;vector<double> dist(V,1e18);vector<char> done(V,0);dist[0]=0;
    for(int it=0;it<V;it++){int u=-1;for(int v=0;v<V;v++)if(!done[v]&&(u<0||dist[v]<dist[u]))u=v;
        if(dist[u]>1e17)break;done[u]=1;if(u==V-1)break;int ux=u%W,uy=u/W;
        for(int v=0;v<V;v++)if(!done[v]){int vx=v%W,vy=v/W;double d=dist[u]+hypot(ux-vx,uy-vy);if(d<dist[v]&&ok(ux,uy,vx,vy))dist[v]=d;}}
    printf("%.9f\n",dist[V-1]);
}
