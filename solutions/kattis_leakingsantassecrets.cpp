#include <bits/stdc++.h>
using namespace std;
int n;
int ask(const vector<int>&q){
    for(int i=0;i<n;i++)printf("%d%c",q[i]+1,i+1<n?' ':'\n');
    fflush(stdout);
    int r; if(scanf("%d",&r)!=1) exit(0);
    if(r<=0) exit(0);
    return r;
}
int main(){
    scanf("%d",&n);
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    vector<int> Q(n); iota(Q.begin(),Q.end(),0);
    shuffle(Q.begin(),Q.end(),rng);
    // P(i)=H(Q(i)); swapping Q[a],Q[b] merges the cycles of a,b in P if different, splits if same.
    int c=ask(Q);
    vector<int> ord(n); iota(ord.begin(),ord.end(),0); shuffle(ord.begin(),ord.end(),rng);
    vector<int> reps; // vertices known to lie in pairwise distinct cycles of P
    for(int idx=0;idx<n;idx++){
        int a=ord[idx];
        if(c==n)break; // P is identity
        int k=reps.size();
        // outcomes 0..k-1 = same cycle as reps[j]; outcome k = new cycle
        int lo=0,hi=k; // candidate outcomes [lo,hi]
        // if every cycle already has a representative, "new" is impossible
        if(c==k)hi=k-1;
        while(lo<hi){
            int cnt=(hi-lo+1)/2; // test reps[lo..lo+cnt-1]
            vector<int> q=Q;
            for(int j=1;j<cnt;j++)swap(q[reps[lo]],q[reps[lo+j]]);
            swap(q[reps[lo]],q[a]);
            int r=ask(q);
            // merged cnt cycles -> c-(cnt-1); then a: split (+1) if inside, merge (-1) otherwise
            if(r==c-(cnt-1)+1)hi=lo+cnt-1; else lo=lo+cnt;
        }
        if(lo<k){ swap(Q[reps[lo]],Q[a]); c++; }
        reps.push_back(a);
    }
    vector<int> H(n);
    for(int i=0;i<n;i++)H[Q[i]]=i; // H(Q(i))=i
    ask(H);
    return 0;
}
