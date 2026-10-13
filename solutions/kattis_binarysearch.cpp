#include <bits/stdc++.h>
using namespace std;
// Rewrite a string as (first symbol) + sequence of S(ame)/C(hange) letters; edges get colour S or C.
// The shortest unwalkable string is alternating in S/C; an infinite alternating walk <=> "infinity".
// State (v,c): at v, next edge colour c. Longest path in that state graph (DAG unless infinite).
int main(){
    int n,m; scanf("%d %d",&n,&m);
    vector<int> a(n);
    for(auto&x:a) scanf("%d",&x);
    vector<int> eu(m),ev(m);
    vector<int> deg(2*n,0); // out-degree of state
    vector<int> cnt(2*n+1,0);
    for(int i=0;i<m;i++){scanf("%d %d",&eu[i],&ev[i]);eu[i]--;ev[i]--;}
    // edge u-v colour c: (u,c)->(v,1-c), (v,c)->(u,1-c). Build reverse adjacency (CSR).
    for(int i=0;i<m;i++){int c=(a[eu[i]]!=a[ev[i]]);
        deg[2*eu[i]+c]++;deg[2*ev[i]+c]++;
        cnt[2*ev[i]+(1-c)]++;cnt[2*eu[i]+(1-c)]++;}
    vector<int> start(2*n+1,0);
    for(int i=0;i<2*n;i++) start[i+1]=start[i]+cnt[i];
    vector<int> radj(2*m),pos(start.begin(),start.end()-1);
    for(int i=0;i<m;i++){int c=(a[eu[i]]!=a[ev[i]]);
        radj[pos[2*ev[i]+(1-c)]++]=2*eu[i]+c;
        radj[pos[2*eu[i]+(1-c)]++]=2*ev[i]+c;}
    vector<int> len(2*n,0),q; q.reserve(2*n);
    for(int s=0;s<2*n;s++) if(deg[s]==0) q.push_back(s);
    for(size_t i=0;i<q.size();i++){int s=q[i];
        for(int k=start[s];k<start[s+1];k++){int p=radj[k];
            len[p]=max(len[p],len[s]+1);
            if(--deg[p]==0) q.push_back(p);}}
    if((int)q.size()<2*n){puts("infinity");return 0;}
    int best=INT_MAX;
    for(int lab=0;lab<2;lab++){
        bool any=false; int mx[2]={0,0};
        for(int v=0;v<n;v++) if(a[v]==lab){any=true;for(int c=0;c<2;c++)mx[c]=max(mx[c],len[2*v+c]);}
        if(!any){best=1;continue;}
        best=min(best,min(mx[0],mx[1])+2);
    }
    printf("%d\n",best);
}
