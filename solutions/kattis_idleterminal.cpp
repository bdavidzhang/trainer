#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,k; scanf("%d %d",&n,&k);
    priority_queue<long long,vector<long long>,greater<long long>> pq;
    vector<long long> fin; fin.reserve(n);
    for(int i=0;i<n;i++){
        long long d; scanf("%lld",&d);
        long long st=0;
        if((int)pq.size()==k){ st=pq.top(); pq.pop(); }
        pq.push(st+d); fin.push_back(st+d);
    }
    sort(fin.begin(),fin.end());
    long long best=0, prev=0;
    for(long long f:fin){ best=max(best,f-prev); prev=f; }
    printf("%lld\n",best);
}
