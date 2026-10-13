#include <bits/stdc++.h>
using namespace std;
int main(){
    int m;scanf("%d",&m);vector<int>c(m);for(auto&x:c)scanf("%d",&x);
    int n,e;scanf("%d %d",&n,&e);
    vector<vector<int>> ev(10002);
    for(int i=0;i<e;i++){int t,p;scanf("%d %d",&t,&p);ev[t].push_back(p);}
    int S=n+1;vector<int> belt(S,0);vector<long long> bill(n+1,0);
    int nxt=0;
    // seat s at time t holds slot (s - t) mod S
    for(int t=0;t<=10000;t++){
        int s0=((0-t)%S+S)%S;
        if(!belt[s0]){belt[s0]=c[nxt];nxt=(nxt+1)%m;}
        for(int p:ev[t]){int s=((p-t)%S+S)%S;bill[p]+=belt[s];belt[s]=0;}
    }
    for(int i=1;i<=n;i++)printf("%lld\n",bill[i]);
}
