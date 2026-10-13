#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n; vector<int> P, Q; // P[i]=j, Q[j]=i (1-indexed)
// Mo-style snake order: blocks of size B along one axis, sorted by the other axis, alternating direction
static vector<int> build(int axis,int B,int dir){
    // returns list of old-page indices i
    const vector<int>& other = axis==0 ? P : Q; // key -> other coordinate
    vector<int> ord; ord.reserve(n);
    vector<int> blk;
    int d=dir;
    for(int s=1;s<=n;s+=B){
        blk.clear();
        for(int k=s;k<s+B && k<=n;k++) blk.push_back(k);
        if(d==0) sort(blk.begin(),blk.end(),[&](int x,int y){return other[x]<other[y];});
        else sort(blk.begin(),blk.end(),[&](int x,int y){return other[x]>other[y];});
        for(int k:blk) ord.push_back(axis==0 ? k : Q[k]);
        d^=1;
    }
    return ord;
}
static ll cost(const vector<int>& ord){
    ll c=0; int ci=1,cj=1;
    for(int i:ord){ c+=abs(i-ci)+abs(P[i]-cj); ci=i; cj=P[i]; }
    return c;
}
int main(){
    scanf("%d",&n);
    P.assign(n+1,0); Q.assign(n+1,0);
    for(int i=1;i<=n;i++){ scanf("%d",&P[i]); Q[P[i]]=i; }
    int r=max(1,(int)llround(sqrt((double)n)));
    set<int> Bs;
    for(int B=max(1,r/2);B<=min(n,2*r+2);B++) Bs.insert(B);
    Bs.insert(1); Bs.insert(n);
    vector<int> bestOrd; ll bc=LLONG_MAX;
    for(int B:Bs) for(int axis=0;axis<2;axis++) for(int dir=0;dir<2;dir++){
        vector<int> o=build(axis,B,dir); ll c=cost(o);
        if(c<bc){ bc=c; bestOrd.swap(o); }
    }
    string out;
    for(int i:bestOrd){ out+=to_string(i); out+=' '; out+=to_string(P[i]); out+='\n'; }
    fputs(out.c_str(),stdout);
}
