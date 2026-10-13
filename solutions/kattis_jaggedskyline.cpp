#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
static bool ask(int x, ll y){
    printf("? %d %lld\n",x,y); fflush(stdout);
    char buf[32]; if(scanf("%31s",buf)!=1) exit(0);
    return buf[0]=='b';
}
int main(){
    int w; ll h;
    if(scanf("%d %lld",&w,&h)!=2) return 0;
    vector<int> ord(w); iota(ord.begin(),ord.end(),1);
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count()^0x9e3779b97f4a7c15ULL);
    shuffle(ord.begin(),ord.end(),rng);
    ll best=0; int bx=1;
    for(int x:ord){
        if(best>=h) break;
        if(!ask(x,best+1)) continue;
        // height of x is in [best+1, h]
        ll lo=best+1, hi=h;
        while(lo<hi){
            ll mid=lo+(hi-lo+1)/2;
            if(ask(x,mid)) lo=mid; else hi=mid-1;
        }
        best=lo; bx=x;
    }
    printf("! %d %lld\n",bx,best); fflush(stdout);
}
