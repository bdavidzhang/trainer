#include <bits/stdc++.h>
using namespace std;
// Column sweep. Horizontal bricks sticking from column i into i+1 are "tokens".
// Each odd free run of a column emits exactly one token, pushed as high as possible
// (top of the run); canonical tokens drift down one row per column, so store row+column.
int main(){
    int w; long long h; scanf("%d %lld",&w,&h);
    vector<long long> a(w+1);
    bool bad=false;
    for(int i=1;i<=w;i++){ scanf("%lld",&a[i]); if(a[i]>h) bad=true; }
    if(bad){ puts("impossible"); return 0; }
    // linked list of tokens, ordered bottom -> top (= insertion order)
    vector<long long> key; vector<int> prv,nxt; vector<char> dead;
    int head=-1,tail=-1;
    vector<int> badlist; // tokens (with a predecessor) whose parity differs from predecessor
    vector<int> stamp;
    for(int i=1;i<=w;i++){
        bool addNew;
        vector<int> rem;
        if(head==-1){
            addNew=((h-a[i])&1);
        } else {
            long long q1=key[head]-i;
            if(q1<=a[i]){ puts("impossible"); return 0; }
            long long qm=key[tail]-i;
            addNew=((h-qm)&1);
            if(((q1-1-a[i])&1)==0) rem.push_back(head);
            for(int t:badlist) rem.push_back(t);
        }
        badlist.clear();
        vector<int> cand;
        for(int t:rem){
            dead[t]=1;
            int p=prv[t],n=nxt[t];
            if(p!=-1) nxt[p]=n; else head=n;
            if(n!=-1) prv[n]=p; else tail=p;
        }
        for(int t:rem){ int n=nxt[t]; if(n!=-1 && !dead[n]) cand.push_back(n); }
        for(int c:cand){
            if(stamp[c]==i) continue; stamp[c]=i;
            if(prv[c]!=-1 && ((key[c]^key[prv[c]])&1)) badlist.push_back(c);
        }
        if(addNew){
            int id=key.size();
            key.push_back(h+i+1); prv.push_back(tail); nxt.push_back(-1); dead.push_back(0); stamp.push_back(0);
            if(tail!=-1) nxt[tail]=id; else head=id;
            if(tail!=-1 && ((key[id]^key[tail])&1)) badlist.push_back(id);
            tail=id;
        }
    }
    puts(head==-1?"possible":"impossible");
}
