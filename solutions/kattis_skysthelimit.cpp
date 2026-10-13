#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
int main(){
    int n; char buf[256];
    if(scanf("%d %255s",&n,buf)!=2) return 0;
    ld k=strtold(buf,nullptr);
    vector<ld> h(n+2,0),p(n+2,0),f(n+2,0);
    for(int i=1;i<=n;i++){scanf("%255s",buf);h[i]=strtold(buf,nullptr);}
    for(int i=1;i<=n;i++){p[i]=k*(ld)i*(ld)(n+1-i);f[i]=h[i]-p[i];}
    // upper hull of (i,f[i]), i=0..n+1
    vector<int> st;
    for(int i=0;i<=n+1;i++){
        while(st.size()>=2){
            int a=st[st.size()-2],b=st.back();
            // b is below or on segment a-i -> pop
            if((f[b]-f[a])*(ld)(i-a) <= (f[i]-f[a])*(ld)(b-a)) st.pop_back(); else break;
        }
        st.push_back(i);
    }
    ld best=0;
    for(size_t t=0;t+1<st.size();t++){
        int a=st[t],b=st[t+1];
        for(int i=a;i<=b;i++){
            ld v=f[a]+(f[b]-f[a])*(ld)(i-a)/(ld)(b-a)+p[i];
            if(i==a) v=h[a]; if(i==b) v=h[b];
            best=max(best,v);
        }
    }
    printf("%.9Lf\n",best);
}
