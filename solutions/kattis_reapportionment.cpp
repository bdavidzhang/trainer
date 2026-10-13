#include <bits/stdc++.h>
using namespace std;
int R,C,n,W;long long T;int val[25];unsigned adj_[25];
vector<bool> failedM;
bool solve(unsigned freeM);
// every connected component of m must have population a positive multiple of T
bool compsOk(unsigned m){
    while(m){
        unsigned comp=m&(~m+1),fr=comp;long long s=0;
        while(fr){int v=__builtin_ctz(fr);fr&=fr-1;s+=val[v];unsigned nb=adj_[v]&m&~comp;comp|=nb;fr|=nb;}
        if(s==0||s%T)return false;
        m&=~comp;
    }
    return true;
}
unsigned FREE;
bool enumr(unsigned cur,long long sum,unsigned frontier,unsigned allowed){
    if(sum==T){
        unsigned rest=FREE&~cur;
        if(rest==0)return true;
        if(!failedM[rest]&&compsOk(rest)){
            unsigned saved=FREE;
            bool r=solve(rest);
            FREE=saved;
            if(r)return true;
        }
    }
    while(frontier){
        int v=__builtin_ctz(frontier);frontier&=frontier-1;
        allowed&=~(1u<<v);
        if(sum+val[v]<=T){
            if(enumr(cur|(1u<<v),sum+val[v],(frontier|adj_[v])&allowed,allowed))return true;
        }
    }
    return false;
}
bool solve(unsigned freeM){
    if(freeM==0)return true;
    if(failedM[freeM])return false;
    FREE=freeM;
    int r=__builtin_ctz(freeM);
    unsigned allowed=freeM&~(1u<<r);
    bool ok=false;
    if(val[r]<=T)ok=enumr(1u<<r,val[r],adj_[r]&allowed,allowed);
    if(!ok)failedM[freeM]=true;
    return ok;
}
int main(){
    scanf("%d %d %d",&R,&C,&W);n=R*C;long long S=0;
    for(int i=0;i<n;i++){scanf("%d",&val[i]);S+=val[i];}
    if(S%W){puts("No");return 0;}
    T=S/W;
    if(T==0){puts("Yes");return 0;} // all blocks empty: cut a snake path into W pieces
    for(int i=0;i<R;i++)for(int j=0;j<C;j++){unsigned a=0;int v=i*C+j;
        if(i)a|=1u<<(v-C);if(i+1<R)a|=1u<<(v+C);if(j)a|=1u<<(v-1);if(j+1<C)a|=1u<<(v+1);adj_[v]=a;}
    failedM.assign((size_t)1<<n,false);
    unsigned full=(n==32)?~0u:((1u<<n)-1);
    puts(solve(full)?"Yes":"No");
}
