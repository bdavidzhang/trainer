#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
// Minimum Manhattan network of 5 points: an optimum lives on the Hanan grid (<=5x5, <=40 edges).
// Branch and bound: for the next pair not yet joined by a monotone path, try each of its <=70 staircase paths.
int X,Y; vector<int> xs,ys;
int wgt[64]; int ne;
int hid(int i,int j){return i*Y+j;}              // (i,j)-(i+1,j)
int vid(int i,int j){return (X-1)*Y+i*(Y-1)+j;}  // (i,j)-(i,j+1)
vector<ull> paths[10]; int np=0;
int best=INT_MAX;
void gen(int i,int j,int ti,int tj,ull m,vector<ull>&out){
    if(i==ti&&j==tj){out.push_back(m);return;}
    if(i<ti) gen(i+1,j,ti,tj,m|(1ULL<<hid(i,j)),out);
    if(j<tj) gen(i,j+1,ti,tj,m|(1ULL<<vid(i,j)),out);
    if(j>tj) gen(i,j-1,ti,tj,m|(1ULL<<vid(i,j-1)),out);
}
void dfs(int k,ull cur,int cost){
    if(cost>=best) return;
    while(k<np){ bool ok=false; for(ull p:paths[k]) if((p&~cur)==0){ok=true;break;} if(!ok)break; k++; }
    if(k==np){best=cost;return;}
    // order candidates by added cost
    int n=paths[k].size(); pair<int,ull> cand[70];
    for(int t=0;t<n;t++){ ull add=paths[k][t]&~cur; int c=0; ull a=add; while(a){c+=wgt[__builtin_ctzll(a)];a&=a-1;} cand[t]={c,add}; }
    sort(cand,cand+n);
    for(int t=0;t<n;t++){ if(cost+cand[t].first>=best) break; dfs(k+1,cur|cand[t].second,cost+cand[t].first); }
}
int main(int argc,char**argv){
    int px[5],py[5];
    for(int i=0;i<5;i++) scanf("%d %d",&px[i],&py[i]);
    if(argc>1){ // testing mode: full integer grid instead of the Hanan grid
        int mx=0; for(int i=0;i<5;i++) mx=max(mx,max(px[i],py[i]));
        for(int i=0;i<=mx;i++){xs.push_back(i);ys.push_back(i);}
    } else {
        for(int i=0;i<5;i++){xs.push_back(px[i]);ys.push_back(py[i]);}
        sort(xs.begin(),xs.end());xs.erase(unique(xs.begin(),xs.end()),xs.end());
        sort(ys.begin(),ys.end());ys.erase(unique(ys.begin(),ys.end()),ys.end());
    }
    X=xs.size();Y=ys.size(); ne=(X-1)*Y+X*(Y-1);
    for(int i=0;i+1<X;i++)for(int j=0;j<Y;j++)wgt[hid(i,j)]=xs[i+1]-xs[i];
    for(int i=0;i<X;i++)for(int j=0;j+1<Y;j++)wgt[vid(i,j)]=ys[j+1]-ys[j];
    int cx[5],cy[5];
    for(int i=0;i<5;i++){cx[i]=lower_bound(xs.begin(),xs.end(),px[i])-xs.begin();cy[i]=lower_bound(ys.begin(),ys.end(),py[i])-ys.begin();}
    vector<vector<ull>> all;
    for(int a=0;a<5;a++)for(int b=a+1;b<5;b++){
        int s=a,t=b; if(cx[s]>cx[t]) swap(s,t);
        vector<ull> out; gen(cx[s],cy[s],cx[t],cy[t],0,out); all.push_back(out);
    }
    sort(all.begin(),all.end(),[](const vector<ull>&a,const vector<ull>&b){return a.size()>b.size();});
    for(auto&v:all) paths[np++]=v;
    dfs(0,0,0);
    printf("%d\n",best);
}
