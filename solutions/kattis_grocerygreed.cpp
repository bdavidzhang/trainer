#include <bits/stdc++.h>
using namespace std;
int main(){
    int n; scanf("%d",&n);
    long long total=0; long long cnt[5]={0,0,0,0,0};
    for(int i=0;i<n;i++){
        char buf[64]; scanf("%63s",buf);
        long long v=0; for(char*p=buf;*p;p++) if(isdigit((unsigned char)*p)) v=v*10+(*p-'0');
        total+=v; cnt[v%5]++;
    }
    long long c3=cnt[3],c4=cnt[4],best=0;
    for(long long x=0;x<=min(c3,c4);x++) best=max(best,2*x+(c3-x)/2+2*((c4-x)/3));
    long long ans=total-cnt[1]-2*cnt[2]-best;
    printf("%lld.%02lld\n",ans/100,ans%100);
}
