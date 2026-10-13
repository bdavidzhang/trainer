#include <bits/stdc++.h>
using namespace std;
typedef unsigned int u32; typedef unsigned long long u64;
u32 P;
static inline void addv(u32&a,u32 b){a+=b; if(a>=P)a-=P;}
u64 pw(u64 b,u64 e){u64 r=1%P;b%=P;while(e){if(e&1)r=r*b%P;b=b*b%P;e>>=1;}return r;}
int main(){
    int n,m; scanf("%d %d %u",&n,&m,&P);
    if(n%2==1&&m%2==1){printf("%u\n",1%P);return 0;}
    if(n%2==1||m%2==1){ int a,b; if(n%2==0){a=n/2;b=m/2;}else{a=m/2;b=n/2;} printf("%llu\n",pw(a+1,b)); return 0;}
    int a=n/2,b=m/2; int F=1<<a;
    // dp[y][mask]: mask = set of row bands whose block in this column is 'R'; y = column threshold
    vector<vector<u32>> dp(a+1,vector<u32>(F,1)),nx(a+1,vector<u32>(F)),E(a+1,vector<u32>(F));
    vector<u32> T(F),R(F);
    auto freeop=[&](vector<u32>&f,int i){ int bit=1<<i; for(int mk=0;mk<F;mk++) if(mk&bit) addv(f[mk^bit],f[mk]); };
    for(int col=1;col<b;col++){
        // y' == y : unrestricted subset transition
        for(int y=0;y<=a;y++){ T=dp[y]; for(int i=0;i<a;i++)freeop(T,i); nx[y]=T; }
        // y' > y : ascending bits; restricted bits i in [y, y'-2]: keeping i needs old bit i+1
        fill(R.begin(),R.end(),0);
        for(int i=0;i<a;i++){
            T=dp[i]; for(int k=0;k<i;k++)freeop(T,k);
            for(int mk=0;mk<F;mk++)addv(R[mk],T[mk]);
            E[i+1]=R;
            if(i+1<a){ int bit=1<<i,b2=1<<(i+1);
                for(int mk=0;mk<F;mk++) if(mk&bit){ addv(R[mk^bit],R[mk]); if(!(mk&b2))R[mk]=0; } }
            for(int yp=1;yp<=i+1;yp++)freeop(E[yp],i);
        }
        for(int yp=1;yp<=a;yp++)for(int mk=0;mk<F;mk++)addv(nx[yp][mk],E[yp][mk]);
        // y' < y : descending bits; restricted bits k in [y'+1, y-1]: keeping k needs old bit k-1
        fill(R.begin(),R.end(),0);
        for(int k=a-1;k>=0;k--){
            T=dp[k+1]; for(int t=a-1;t>k;t--)freeop(T,t);
            for(int mk=0;mk<F;mk++)addv(R[mk],T[mk]);
            E[k]=R;
            if(k>=1){ int bit=1<<k,b2=1<<(k-1);
                for(int mk=0;mk<F;mk++) if(mk&bit){ addv(R[mk^bit],R[mk]); if(!(mk&b2))R[mk]=0; } }
            for(int yp=k;yp<a;yp++)freeop(E[yp],k);
        }
        for(int yp=0;yp<a;yp++)for(int mk=0;mk<F;mk++)addv(nx[yp][mk],E[yp][mk]);
        dp.swap(nx);
    }
    u32 ans=0; for(int y=0;y<=a;y++)for(int mk=0;mk<F;mk++)addv(ans,dp[y][mk]%P);
    printf("%u\n",ans);
}
