#include <bits/stdc++.h>
using namespace std;
// residues 1,2 are bought alone (save 1,2); residue 0 is free.
// residues 3 (a items) and 4 (b items): small exact DP after peeling provably-optimal groups.
static const int T=16;
int f[T+1][T+1];
int sv(int x,int y){ int r=(3*x+4*y)%5; static const int s[5]={0,1,2,-2,-1}; return s[r]; }
int main(){
    int n; scanf("%d",&n);
    long long c[5]={0,0,0,0,0};
    for(int i=0;i<n;i++){int p;scanf("%d",&p);c[p%5]++;}
    for(int a=0;a<=T;a++)for(int b=0;b<=T;b++){
        if(a==0&&b==0){f[a][b]=0;continue;}
        int best=INT_MIN;
        for(int x=0;x<=a;x++)for(int y=0;y<=b;y++){
            if(x+y==0)continue;
            best=max(best,f[a-x][b-y]+sv(x,y));
        }
        f[a][b]=best;
    }
    long long a=c[3],b=c[4],ans=c[1]+2*c[2];
    long long k=max(0LL,min(a,b)-8);
    a-=k;b-=k;ans+=2*k;
    if(a>T){ long long g=(a-T+1)/2; a-=2*g; ans+=g; }
    if(b>T){ long long g=(b-T+2)/3; b-=3*g; ans+=2*g; }
    ans+=f[a][b];
    printf("%lld\n",ans);
}
