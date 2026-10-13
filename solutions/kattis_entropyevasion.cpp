#include <bits/stdc++.h>
using namespace std;
// Greedy: always re-randomise the subarray maximising (#zeros - #ones),
// i.e. the one with the largest expected gain (Kadane).
int main(){
    int n; if(scanf("%d",&n)!=1) return 0;
    vector<int> v(n,0);
    for(int step=0;step<125;step++){
        int best=INT_MIN,bl=0,br=0,cur=0,cl=0;
        for(int i=0;i<n;i++){
            int w=v[i]?-1:1;
            if(cur<=0){cur=w;cl=i;} else cur+=w;
            if(cur>best){best=cur;bl=cl;br=i;}
        }
        printf("%d %d\n",bl+1,br+1); fflush(stdout);
        for(int i=0;i<n;i++) if(scanf("%d",&v[i])!=1) return 0;
        int p; if(scanf("%d",&p)!=1) return 0;
        if(p>=70) break;
    }
    return 0;
}
