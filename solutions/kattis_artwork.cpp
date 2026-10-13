#include <bits/stdc++.h>
using namespace std;
int n,m,q;
vector<int> p;
int find(int x){ while(p[x]!=x){p[x]=p[p[x]];x=p[x];} return x; }
int main(){
    scanf("%d %d %d",&n,&m,&q);
    vector<int> cnt(n*m,0);
    vector<array<int,4>> s(q);
    for(auto&a:s){ scanf("%d %d %d %d",&a[0],&a[1],&a[2],&a[3]); a[0]--;a[1]--;a[2]--;a[3]--;
        for(int x=a[0];x<=a[2];x++) for(int y=a[1];y<=a[3];y++) cnt[x*m+y]++; }
    p.resize(n*m); iota(p.begin(),p.end(),0);
    int comps=0;
    const int dx[4]={1,-1,0,0}, dy[4]={0,0,1,-1};
    auto add=[&](int x,int y){
        comps++;
        for(int d=0;d<4;d++){ int nx=x+dx[d], ny=y+dy[d];
            if(nx<0||ny<0||nx>=n||ny>=m||cnt[nx*m+ny]) continue;
            int a=find(x*m+y), b=find(nx*m+ny);
            if(a!=b){p[a]=b;comps--;}
        }
    };
    // initial: add white cells one at a time (neighbors only count if already "present")
    vector<char> present(n*m,0);
    for(int x=0;x<n;x++) for(int y=0;y<m;y++) if(!cnt[x*m+y]){
        comps++; present[x*m+y]=1;
        if(x>0&&present[(x-1)*m+y]){int a=find(x*m+y),b=find((x-1)*m+y); if(a!=b){p[a]=b;comps--;}}
        if(y>0&&present[x*m+y-1]){int a=find(x*m+y),b=find(x*m+y-1); if(a!=b){p[a]=b;comps--;}}
    }
    vector<int> ans(q);
    for(int i=q-1;i>=0;i--){
        ans[i]=comps;
        auto&a=s[i];
        for(int x=a[0];x<=a[2];x++) for(int y=a[1];y<=a[3];y++) if(--cnt[x*m+y]==0) add(x,y);
    }
    for(int i=0;i<q;i++) printf("%d\n",ans[i]);
}
