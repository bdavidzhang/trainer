#include <bits/stdc++.h>
using namespace std;
int main(){
    long long s; int n; scanf("%lld %d",&s,&n);
    vector<long long> Y,N;
    for(int i=0;i<n;i++){ long long d; char t; scanf("%lld %c",&d,&t); if(t=='y')Y.push_back(d); else N.push_back(d); }
    sort(Y.rbegin(),Y.rend()); sort(N.begin(),N.end());
    // assign paper users to latest possible distinct slots
    vector<long long> slots; long long prev=LLONG_MAX;
    for(long long d:Y){ long long t=min(d,prev-1); if(t<1){puts("No");return 0;} slots.push_back(t); prev=t; }
    reverse(slots.begin(),slots.end()); // ascending
    size_t p=0;
    for(size_t i=0;i<N.size();i++){
        long long d=N[i];
        while(p<slots.size()&&slots[p]<=d)p++;
        if(i+1<N.size()&&N[i+1]==d)continue;
        if((long long)(i+1)+(long long)p> s*d){puts("No");return 0;}
    }
    puts("Yes");
}
