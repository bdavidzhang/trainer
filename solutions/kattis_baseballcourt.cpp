#include <bits/stdc++.h>
using namespace std;
typedef unsigned int u32;
const u32 MOD=1000000007;
int main(){
    int N,a,b; scanf("%d %d %d",&N,&a,&b);
    // compositions g_1..g_r (r>=2) with e2(g)=N, D-g_r<=a, D-g_1<=b.
    // middle: f[M][E] = #compositions of M (>=1 part) with e2=E; need 2M+1+E<=N.
    int Mmax=(N-1)/2;
    vector<vector<u32>> f(Mmax+1);
    for(int M=1;M<=Mmax;M++){ f[M].assign(N-2*M,0); f[M][0]=1; } // E in [0, N-2M-1]
    for(int p=1;p<=Mmax;p++){
        const vector<u32>& src=f[p];
        for(int g=1;p+g<=Mmax;g++){
            int q=p+g; long long sh=(long long)p*g;
            int lim=N-2*q-1; // max E at q
            if(sh>lim) break;
            vector<u32>& dst=f[q];
            int top=min((long long)lim-sh,(long long)src.size()-1);
            const u32* s=src.data(); u32* d=dst.data()+sh;
            for(int e=0;e<=top;e++){ u32 v=d[e]+s[e]; d[e]= v>=MOD? v-MOD: v; }
        }
    }
    unsigned long long ans=0;
    // M=0
    for(int x=1;x<=N;x++) if(N%x==0){ int z=N/x; if(x<=a&&z<=b) ans++; }
    for(int M=1;M<=Mmax;M++){
        const vector<u32>& fm=f[M];
        for(int x=1;x+M<=a;x++){
            long long r=N-(long long)x*M; // need xz+zM<=r
            if(r<x+M) break;
            for(int z=1;z+M<=b;z++){
                long long E=r-(long long)z*(x+M);
                if(E<0) break;
                ans+=fm[E];
            }
        }
        ans%=MOD;
    }
    printf("%llu\n",ans%MOD);
}
