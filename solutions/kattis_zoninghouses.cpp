#include <bits/stdc++.h>
using namespace std;
int n,q; vector<long long> X,Y;
// sparse tables storing indices: 0 minx,1 maxx,2 miny,3 maxy
vector<vector<int>> sp[4];
static inline bool better(int t,int a,int b){
    switch(t){ case 0: return X[a]<X[b]; case 1: return X[a]>X[b]; case 2: return Y[a]<Y[b]; default: return Y[a]>Y[b]; }
}
int lg[100005];
int query(int t,int l,int r){ // inclusive, l<=r
    int k=lg[r-l+1]; int a=sp[t][k][l],b=sp[t][k][r-(1<<k)+1]; return better(t,a,b)?a:b;
}
int main(){
    scanf("%d %d",&n,&q); X.resize(n);Y.resize(n);
    for(int i=0;i<n;i++) scanf("%lld %lld",&X[i],&Y[i]);
    lg[1]=0; for(int i=2;i<=n;i++) lg[i]=lg[i/2]+1;
    for(int t=0;t<4;t++){
        sp[t].assign(lg[n]+1,vector<int>(n));
        for(int i=0;i<n;i++) sp[t][0][i]=i;
        for(int k=1;k<=lg[n];k++) for(int i=0;i+(1<<k)<=n;i++){ int a=sp[t][k-1][i],b=sp[t][k-1][i+(1<<(k-1))]; sp[t][k][i]=better(t,a,b)?a:b; }
    }
    while(q--){
        int a,b; scanf("%d %d",&a,&b); a--;b--;
        long long best=LLONG_MAX;
        for(int t=0;t<4;t++){
            int rem=query(t,a,b);
            int e[4];
            for(int u=0;u<4;u++){
                int c=-1;
                if(rem>a) c=query(u,a,rem-1);
                if(rem<b){ int d=query(u,rem+1,b); if(c<0||better(u,d,c)) c=d; }
                e[u]=c;
            }
            long long side=max(X[e[1]]-X[e[0]],Y[e[3]]-Y[e[2]]);
            best=min(best,side);
        }
        printf("%lld\n",best);
    }
}
