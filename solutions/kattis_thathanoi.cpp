#include <bits/stdc++.h>
using namespace std;
int main(){
    vector<int> peg(64,-1);
    int n=0; bool ok=true;
    for(int p=0;p<3;p++){
        int m; scanf("%d",&m);
        int prev=INT_MAX;
        for(int i=0;i<m;i++){
            int d; scanf("%d",&d);
            if(d>prev) ok=false;
            prev=d;
            if(d>=1&&d<64) peg[d]=p;
            n=max(n,d);
        }
    }
    if(!ok){puts("No");return 0;}
    long long rem=0; int s=0,d=2;
    for(int k=n;k>=1;k--){
        int aux=3-s-d;
        if(peg[k]==s){ rem+=1LL<<(k-1); d=aux; }
        else if(peg[k]==d){ s=aux; }
        else { puts("No"); return 0; }
    }
    printf("%lld\n",rem);
}
