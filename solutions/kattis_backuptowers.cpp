#include <bits/stdc++.h>
using namespace std;
int main(){int r,c,n;scanf("%d %d %d",&r,&c,&n);
    vector<array<int,2>> best(r*c,{0,0}); vector<char> cnt(r*c,0);
    // states (dist,id,cell) processed in lexicographic order; each cell keeps first 2 distinct ids
    typedef tuple<int,int,int> T;
    priority_queue<T,vector<T>,greater<T>> pq;
    for(int t=1;t<=n;t++){int i,j;scanf("%d %d",&i,&j);pq.push({0,t,(i-1)*c+j-1});}
    int di[4]={0,1,0,-1},dj[4]={1,0,-1,0};
    while(!pq.empty()){
        auto [d,t,v]=pq.top();pq.pop();
        if(cnt[v]>=2||(cnt[v]==1&&best[v][0]==t))continue;
        best[v][(int)cnt[v]++]=t;
        int i=v/c,j=v%c;
        for(int k=0;k<4;k++){int a=i+di[k],b=j+dj[k];if(a<0||a>=r||b<0||b>=c)continue;
            int u=a*c+b;if(cnt[u]>=2||(cnt[u]==1&&best[u][0]==t))continue;
            pq.push({d+1,t,u});}
    }
    string out;
    for(int k=0;k<2;k++)for(int i=0;i<r;i++){for(int j=0;j<c;j++){out+=to_string(best[i*c+j][k]);out+=(j+1<c?' ':'\n');}}
    fputs(out.c_str(),stdout);
}
