#include <bits/stdc++.h>
using namespace std;
int main(){int n;scanf("%d",&n);vector<int>c(n);for(auto&x:c)scanf("%d",&x);
    int L=c[n-1]+c[n-2];
    vector<int> opt(L+1,INT_MAX),g(L+1,0);opt[0]=0;
    int p=0;
    for(int x=1;x<=L;x++){
        while(p+1<n&&c[p+1]<=x)p++;
        g[x]=g[x-c[p]]+1;
        int b=INT_MAX;
        for(int i=0;i<=p;i++){int v=opt[x-c[i]];if(v<b)b=v;}
        opt[x]=b+1;
        if(opt[x]<g[x]){puts("non-canonical");return 0;}
    }
    puts("canonical");}
