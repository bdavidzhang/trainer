#include <bits/stdc++.h>
using namespace std;
// Target equals the maximum possible (sum of top n scores per topic), so every duo must
// contain exactly one "high" (score > n) student in every topic: partners have complementary
// high/low bit vectors. Check multiset of vectors is closed under complement with equal counts.
int main(){
    int n,r; scanf("%d %d",&n,&r);
    int N=2*n;
    vector<array<unsigned long long,2>> v(N,array<unsigned long long,2>{0,0});
    for(int i=0;i<r;i++)for(int j=0;j<N;j++){
        int x; scanf("%d",&x);
        if(x>n) v[j][i>>6]|=1ULL<<(i&63);
    }
    array<unsigned long long,2> mask{0,0};
    for(int i=0;i<r;i++) mask[i>>6]|=1ULL<<(i&63);
    map<array<unsigned long long,2>,int> cnt;
    for(auto&a:v) cnt[a]++;
    for(auto&[a,c]:cnt){
        array<unsigned long long,2> b{a[0]^mask[0],a[1]^mask[1]};
        auto it=cnt.find(b);
        if(it==cnt.end()||it->second!=c){ puts("impossible"); return 0; }
    }
    puts("possible");
}
