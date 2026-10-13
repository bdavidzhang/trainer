#include <bits/stdc++.h>
using namespace std;
int n;
int ask(const vector<int>&d){
    for(int i=0;i<n;i++)printf("%d%c",d[i],i+1<n?' ':'\n');
    fflush(stdout);
    int r; if(scanf("%d",&r)!=1) exit(0);
    if(r<=0) exit(0);
    return r;
}
int main(){
    scanf("%d",&n);
    vector<int> h(n,0); // 0 = ambiguous in {N,N+1}
    for(int i=0;i<n;i++){
        vector<int> d(n,n); d[i]=1;
        int r=ask(d);
        if(r>n){h[i]=r+1;continue;}
        d.assign(n,n+1); d[i]=2*n;
        r=ask(d);
        if(r>n){h[i]=2*n-r;continue;}
    }
    // remaining dials are N or N+1 (n>=2 here, since n==1 would already have terminated)
    for(int i=0;i<n;i++) if(!h[i]){
        vector<int> d(n);
        for(int j=0;j<n;j++) d[j]=h[j]?h[j]:n;
        d[i]=n+2;
        int r=ask(d);
        h[i]=(r>=2)?n:n+1;
    }
    ask(h);
    return 0;
}
