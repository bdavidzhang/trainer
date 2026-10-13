#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,m; scanf("%d %d",&n,&m);
    vector<int> vx(n),vy(n);
    for(int i=0;i<n;i++) scanf("%d %d",&vx[i],&vy[i]);
    int sx,sy; scanf("%d %d",&sx,&sy);
    // boundary lattice points with odd x+y
    vector<int> px,py; vector<char> hor;
    for(int i=0;i<n;i++){
        int j=(i+1)%n;
        if(vy[i]==vy[j]){
            int lo=min(vx[i],vx[j]),hi=max(vx[i],vx[j]);
            for(int x=lo+1;x<hi;x+=2){ px.push_back(x);py.push_back(vy[i]);hor.push_back(1);}
        }else{
            int lo=min(vy[i],vy[j]),hi=max(vy[i],vy[j]);
            for(int y=lo+1;y<hi;y+=2){ px.push_back(vx[i]);py.push_back(y);hor.push_back(0);}
        }
    }
    int N=px.size();
    vector<int> o1(N),o2(N),p1(N),p2(N);
    iota(o1.begin(),o1.end(),0); iota(o2.begin(),o2.end(),0);
    sort(o1.begin(),o1.end(),[&](int a,int b){int da=px[a]-py[a],db=px[b]-py[b]; return da!=db?da<db:px[a]<px[b];});
    sort(o2.begin(),o2.end(),[&](int a,int b){int da=px[a]+py[a],db=px[b]+py[b]; return da!=db?da<db:px[a]<px[b];});
    for(int i=0;i<N;i++){p1[o1[i]]=i;p2[o2[i]]=i;}
    int cur=-1;
    for(int i=0;i<N;i++) if(px[i]==sx&&py[i]==sy){cur=i;break;}
    int dx=1,dy=1;
    string out; out.reserve((size_t)m*16);
    char buf[40];
    for(int s=0;s<m;s++){
        int nx;
        if(dx==dy) nx=o1[p1[cur]+dx];
        else nx=o2[p2[cur]+dx];
        cur=nx;
        if(hor[cur]) dy=-dy; else dx=-dx;
        int len=snprintf(buf,sizeof buf,"%d %d\n",px[cur],py[cur]);
        out.append(buf,len);
    }
    fputs(out.c_str(),stdout);
}
