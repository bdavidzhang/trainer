#include <bits/stdc++.h>
using namespace std;

int main(){
    int n,k; scanf("%d %d",&n,&k);
    vector<int>a(n); for(auto&x:a)scanf("%d",&x);
    int h=0;
    while(!is_sorted(a.begin(),a.end())){
        h++;
        // one pass: position i gets the min of the carried k-1 elements plus a[i+k-1]
        priority_queue<int,vector<int>,greater<int>> pq;
        for(int i=0;i<k-1;i++)pq.push(a[i]);
        int w=0;
        for(int i=k-1;i<n;i++){ pq.push(a[i]); a[w++]=pq.top(); pq.pop(); }
        while(!pq.empty()){ a[w++]=pq.top(); pq.pop(); }
    }
    printf("%d\n",h);
}
