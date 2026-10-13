#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
int main(){ int n,k; double pd; cin>>n>>k>>pd; ld p=pd;
    int S=1<<n; // mask of last n outcomes
    vector<vector<ld>> a(S,vector<ld>(S+1,0));
    for(int m=0;m<S;m++){
        a[m][m]=1;
        if(__builtin_popcount(m)>=k){ a[m][S]=0; continue; }
        a[m][S]=1;
        int m1=((m<<1)|1)&(S-1), m0=(m<<1)&(S-1);
        a[m][m1]-=p; a[m][m0]-=(1-p);
    }
    for(int c=0;c<S;c++){
        int pv=c; for(int r=c+1;r<S;r++) if(fabsl(a[r][c])>fabsl(a[pv][c])) pv=r;
        swap(a[c],a[pv]);
        for(int r=0;r<S;r++) if(r!=c && a[r][c]!=0){ ld f=a[r][c]/a[c][c]; for(int j=c;j<=S;j++) a[r][j]-=f*a[c][j]; }
    }
    printf("%.9Lf\n",a[0][S]/a[0][0]); }
