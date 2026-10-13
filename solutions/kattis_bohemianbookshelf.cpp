#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,H,W; scanf("%d %d %d",&n,&H,&W);
    vector<int> h(n),t(n); int total=0;
    for(int i=0;i<n;i++){ scanf("%d %d",&h[i],&t[i]); total+=t[i]; }
    vector<int> ord(n); iota(ord.begin(),ord.end(),0);
    stable_sort(ord.begin(),ord.end(),[&](int a,int b){ return h[a]<h[b]; });
    // suf[pos]: all books at sorted positions >= pos can stand upright
    vector<char> suf(n+1,1);
    for(int p=n-1;p>=0;p--) suf[p]=suf[p+1]&&(h[ord[p]]<=H);
    for(int pos=0;pos<n;pos++){
        if(!suf[pos+1]) continue;
        int top=ord[pos];               // widest book of the stack
        int cap=H-t[top];
        if(cap<0) continue;
        // dp over ord[0..pos-1]; books taller than H are forced into the stack
        vector<vector<char>> dp(pos+1,vector<char>(cap+1,0));
        dp[0][0]=1;
        for(int j=0;j<pos;j++){
            int b=ord[j]; bool forced=h[b]>H;
            for(int s=0;s<=cap;s++) if(dp[j][s]){
                if(!forced) dp[j+1][s]=1;
                if(s+t[b]<=cap) dp[j+1][s+t[b]]=1;
            }
        }
        for(int s=cap;s>=0;s--){
            if(!dp[pos][s]) continue;
            int st=s+t[top];
            if(st>=total) continue;            // need at least one upright book
            if(total-st+h[top]>W) break;       // smaller s only gets worse
            vector<char> inStack(n,0); inStack[top]=1;
            int cur=s;
            for(int j=pos-1;j>=0;j--){
                int b=ord[j]; bool forced=h[b]>H;
                if(!forced&&dp[j][cur]) continue;
                inStack[b]=1; cur-=t[b];
            }
            printf("upright");
            for(int i=0;i<n;i++) if(!inStack[i]) printf(" %d",i+1);
            printf("\nstacked");
            for(int j=pos;j>=0;j--) if(inStack[ord[j]]) printf(" %d",ord[j]+1);
            printf("\n");
            return 0;
        }
    }
    puts("impossible");
}
