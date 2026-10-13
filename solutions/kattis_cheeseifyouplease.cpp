#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
int main(){
    int n,m; scanf("%d %d",&n,&m);
    vector<ld> w(n);
    for(auto&x:w){double t;scanf("%lf",&t);x=t;}
    // tableau: n rows, m + n columns + rhs
    int C=m+n;
    vector<vector<ld>> T(n+1, vector<ld>(C+1,0));
    for(int j=0;j<m;j++){
        for(int i=0;i<n;i++){double p;scanf("%lf",&p);T[i][j]=p/100.0;}
        double t;scanf("%lf",&t);T[n][j]=-t;
    }
    vector<int> basis(n);
    for(int i=0;i<n;i++){T[i][m+i]=1;T[i][C]=w[i];basis[i]=m+i;}
    const ld EPS=1e-12L;
    while(true){
        // Bland's rule
        int pc=-1;
        for(int j=0;j<C;j++) if(T[n][j]<-EPS){pc=j;break;}
        if(pc<0)break;
        int pr=-1; ld best=0;
        for(int i=0;i<n;i++) if(T[i][pc]>EPS){
            ld r=T[i][C]/T[i][pc];
            if(pr<0||r<best-EPS||(fabsl(r-best)<=EPS&&basis[i]<basis[pr])){pr=i;best=r;}
        }
        if(pr<0)break; // unbounded (should not happen)
        ld pv=T[pr][pc];
        for(int j=0;j<=C;j++)T[pr][j]/=pv;
        for(int i=0;i<=n;i++) if(i!=pr){
            ld f=T[i][pc]; if(fabsl(f)<1e-18L)continue;
            for(int j=0;j<=C;j++)T[i][j]-=f*T[pr][j];
        }
        basis[pr]=pc;
    }
    printf("%.2f\n",(double)(T[n][C]+1e-9L));
}
