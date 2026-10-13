#include <bits/stdc++.h>
using namespace std;
static int cur;
static int ask(const char*s){ printf("? %s\n",s); fflush(stdout); if(scanf("%d",&cur)!=1) exit(0); return cur; }
static void answer(int n){ printf("! %d\n",n); fflush(stdout); exit(0); }
int main(){
    const int K=40,L=40;
    if(scanf("%d",&cur)!=1) return 0;
    // Phase 1: deterministic check for n<=K. Zero K+1 consecutive carriages.
    for(int i=0;i<K;i++){ if(cur) ask("flip"); ask("right"); }
    if(cur) ask("flip");
    for(int i=0;i<K;i++) ask("left");
    if(cur) ask("flip"); // should not happen
    ask("flip"); // marker = 1
    for(int i=1;i<=K;i++){ ask("right"); if(cur) answer(i); }
    // Phase 2: n>K>=L. Write a random pattern on L distinct carriages, walk until it reappears.
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count() ^ (uint64_t)random_device{}());
    vector<int> t;
    for(int i=0;i<L;i++){ int r=rng()&1; if(cur!=r) ask("flip"); t.push_back(r); ask("right"); }
    while(true){
        t.push_back(cur);
        int m=t.size();
        if(m>=2*L){
            bool eq=true; for(int i=0;i<L&&eq;i++) if(t[m-L+i]!=t[i]) eq=false;
            if(eq) answer(m-L);
        }
        ask("right");
    }
}
