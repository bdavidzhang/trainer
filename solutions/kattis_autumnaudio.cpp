#include <bits/stdc++.h>
using namespace std;
int main(){
    int n;scanf("%d",&n);
    vector<long long> t(n);
    for(auto&x:t)scanf("%lld",&x);
    sort(t.begin(),t.end());
    vector<long long> res;
    vector<long long> q(n);
    for(int j=1;j<n;j++){
        long long d=t[j]-t[0];
        if(d<=0)continue;
        if(t[j]==t[j-1])continue;
        int qh=0,qt=0;bool ok=true;
        for(int i=0;i<n;i++){
            if(qh<qt){
                if(q[qh]==t[i]){qh++;continue;}
                if(q[qh]<t[i]){ok=false;break;}
            }
            if(qt-qh>=n-i){ok=false;break;}
            q[qt++]=t[i]+d;
        }
        if(ok&&qh==qt)res.push_back(d);
    }
    printf("%d\n",(int)res.size());
    for(long long d:res)printf("%lld\n",d);
}
