#include <bits/stdc++.h>
using namespace std;
int a[10],b[10],third; bool seen[2000];
static unsigned char vis[1024][11][11][41]; // bitset of scores (up to 320)
void go(int mask,int n1,int n2,int sc){
    if(vis[mask][n1][n2][sc>>3]>>(sc&7)&1) return;
    vis[mask][n1][n2][sc>>3]|=1<<(sc&7);
    if(mask==1023){ seen[sc]=true; return; }
    for(int i=0;i<10;i++) if(!(mask>>i&1)){
        if(a[i]==10){ if(b[i]!=0) continue; go(mask|1<<i,10,n1,sc+10+n1+n2); }
        else if(a[i]+b[i]==10) go(mask|1<<i,a[i],b[i],sc+10+n1);
        else go(mask|1<<i,a[i],b[i],sc+a[i]+b[i]);
    }
}
int main(){
    int total; cin>>total>>third; for(int i=0;i<10;i++) cin>>a[i]>>b[i];
    for(int i=0;i<10;i++){
        bool strike=a[i]==10, spare=!strike&&a[i]+b[i]==10;
        if(!strike&&!spare&&third!=0) continue;
        go(1<<i,min(a[i],10),min(b[i],10),a[i]+b[i]+third);
    }
    if(total>=0&&total<2000&&seen[total]){ printf("%d Yes\n",total); return 0; }
    int lo=-1,hi=-1;
    for(int v=0;v<2000;v++) if(seen[v]){ if(v<total) lo=v; else if(v>total&&hi<0) hi=v; }
    printf("%d",total); if(lo>=0) printf(" %d",lo); if(hi>=0) printf(" %d",hi); puts("");
}
