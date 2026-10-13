#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long u64;
const int W=16; // 1024-bit two's complement
struct Big{ u64 d[W]; Big(){memset(d,0,sizeof d);} };
static void add(Big&a,const Big&b){ unsigned __int128 c=0; for(int i=0;i<W;i++){ c+=a.d[i]; c+=b.d[i]; a.d[i]=(u64)c; c>>=64; } }
static void neg(Big&a){ u64 c=1; for(int i=0;i<W;i++){ a.d[i]=~a.d[i]+c; c=(c&&a.d[i]==0)?1:0; } }
static Big mulsmall(const Big&a,u64 m){ Big r; unsigned __int128 c=0; for(int i=0;i<W;i++){ c+=(unsigned __int128)a.d[i]*m; r.d[i]=(u64)c; c>>=64; } return r; }
static double todouble(Big a){ bool s=a.d[W-1]>>63; if(s)neg(a); double r=0; for(int i=W-1;i>=0;i--) r=r*18446744073709551616.0+(double)a.d[i]; return s?-r:r; }
int main(){
    int n,m; scanf("%d %d",&n,&m);
    // col[x] = C(x,n) for x=0..m
    vector<Big> cur(m+1), nxt(m+1);
    for(int x=0;x<=m;x++){ cur[x].d[0]=1; } // C(x,0)=1
    for(int i=1;i<=n;i++){
        nxt[0]=Big();
        for(int x=1;x<=m;x++){ nxt[x]=nxt[x-1]; add(nxt[x],cur[x-1]); }
        swap(cur,nxt);
    }
    vector<Big> T(n+1);
    for(int j=1;j<=n;j++){
        for(long long x=m;x>=n;x-=j) add(T[j],cur[x]);
    }
    static u64 C[64][64];
    for(int i=0;i<64;i++){C[i][0]=1;for(int j=1;j<=i;j++)C[i][j]=C[i-1][j-1]+(j<=i-1?C[i-1][j]:0);}
    double den=todouble(cur[m]);
    double pre=0;
    for(int k=1;k<=n;k++){
        int r=n-k+1;
        Big s;
        for(int j=r;j<=n;j++){
            Big t=mulsmall(mulsmall(T[j],C[n][j]),C[j-1][r-1]);
            if((j-r)&1) neg(t);
            add(s,t);
        }
        pre+=todouble(s)/den;
        printf("%.9f\n",pre);
    }
}
