#include <bits/stdc++.h>
using namespace std;
int main(){
    int n; scanf("%d",&n);
    struct P{int a,d,len;};
    vector<P> pos,neg; int tot=0;
    for(int i=0;i<n;i++){
        static char buf[400]; scanf("%s",buf); int len=strlen(buf);
        int bal=0,mn=0; for(int j=0;j<len;j++){bal+=buf[j]=='('?1:-1; mn=min(mn,bal);}
        P p{-mn,bal,len};
        if(bal>=0){pos.push_back(p);tot+=bal;} else neg.push_back(p);
    }
    sort(pos.begin(),pos.end(),[](const P&x,const P&y){return x.a<y.a;});
    // negative: need from the right side = a+d, larger first
    sort(neg.begin(),neg.end(),[](const P&x,const P&y){return x.a+x.d>y.a+y.d;});
    const int NEG=INT_MIN/2;
    vector<int> dp(tot+1,NEG); dp[0]=0;
    for(auto&p:pos){
        for(int b=tot-p.d;b>=p.a;b--) if(dp[b]>NEG) dp[b+p.d]=max(dp[b+p.d],dp[b]+p.len);
    }
    for(auto&p:neg){
        for(int b=max(p.a,-p.d);b<=tot;b++) if(dp[b]>NEG) dp[b+p.d]=max(dp[b+p.d],dp[b]+p.len);
    }
    printf("%d\n",dp[0]);
}
