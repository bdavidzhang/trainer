#include <bits/stdc++.h>
using namespace std;
int main(){
    int c,n; scanf("%d %d",&c,&n);
    vector<bitset<1001>> dp(c+1);
    bitset<1001> mask; for(int i=0;i<=c;i++) mask[i]=1;
    dp[0][0]=1;
    for(int i=0;i<n;i++){
        int w; scanf("%d",&w);
        if(w>c) continue;
        for(int a=c;a>=0;a--){
            bitset<1001> nw = dp[a] | ((dp[a]<<w)&mask);
            if(a>=w) nw |= dp[a-w];
            dp[a]=nw;
        }
    }
    int ba=0,bb=0;
    for(int a=0;a<=c;a++) for(int b=0;b<=a;b++) if(dp[a][b]){
        if(a+b>ba+bb || (a+b==ba+bb && a-b<ba-bb)){ba=a;bb=b;}
    }
    printf("%d %d\n",ba,bb);
}
