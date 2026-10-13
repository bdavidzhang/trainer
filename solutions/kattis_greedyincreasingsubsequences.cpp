#include <bits/stdc++.h>
using namespace std;
int main(){
    int n;scanf("%d",&n);vector<vector<int>>seq;vector<int>tail;
    for(int i=0;i<n;i++){int x;scanf("%d",&x);
        // tails non-increasing; find first tail < x
        int lo=0,hi=tail.size();
        while(lo<hi){int mid=(lo+hi)/2;if(tail[mid]<x)hi=mid;else lo=mid+1;}
        if(lo==(int)tail.size()){tail.push_back(x);seq.push_back({x});}
        else{tail[lo]=x;seq[lo].push_back(x);}
    }
    printf("%d\n",(int)seq.size());
    for(auto&v:seq){for(size_t i=0;i<v.size();i++)printf(i?" %d":"%d",v[i]);puts("");}
}
