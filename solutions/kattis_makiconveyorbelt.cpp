#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int N,M,K;ll pA,pB;
vector<ll> a,b;
vector<ll> tA,tB,X,C;vector<int> ty;
bool feas(ll T){
    vector<ll> sa(M,0),sb(M,0),sab(M,0);
    for(int i=0;i<K;i++){
        bool A=tA[i]<=T,B=tB[i]<=T;
        if(A&&B)sab[ty[i]]+=X[i];else if(A)sa[ty[i]]+=X[i];else if(B)sb[ty[i]]+=X[i];
    }
    for(int m=0;m<M;m++){
        if(sa[m]+sab[m]<a[m])return false;
        if(sb[m]+sab[m]<b[m])return false;
        if(sa[m]+sb[m]+sab[m]<a[m]+b[m])return false;
    }
    return true;
}
int main(){
    scanf("%d %d %d %lld %lld",&N,&M,&K,&pA,&pB);
    a.resize(M);b.resize(M);
    for(auto&x:a)scanf("%lld",&x);
    for(auto&x:b)scanf("%lld",&x);
    tA.resize(K);tB.resize(K);X.resize(K);C.resize(K);ty.resize(K);
    vector<ll> cand;cand.push_back(0);
    for(int i=0;i<K;i++){
        ll s;scanf("%lld %d %lld %lld",&s,&ty[i],&X[i],&C[i]);ty[i]--;
        tA[i]=((pA-s)%N+N)%N;tB[i]=((pB-s)%N+N)%N;
        cand.push_back(tA[i]);cand.push_back(tB[i]);
    }
    sort(cand.begin(),cand.end());cand.erase(unique(cand.begin(),cand.end()),cand.end());
    if(!feas(cand.back())){puts("impossible");return 0;}
    int lo=0,hi=cand.size()-1;
    while(lo<hi){int mid=(lo+hi)/2;if(feas(cand[mid]))hi=mid;else lo=mid+1;}
    ll T=cand[lo];
    // min cost
    vector<int> ord(K);iota(ord.begin(),ord.end(),0);
    sort(ord.begin(),ord.end(),[&](int x,int y){if(ty[x]!=ty[y])return ty[x]<ty[y];return C[x]<C[y];});
    ll total=0;
    int i=0;
    while(i<K){
        int j=i;int m=ty[ord[i]];
        while(j<K&&ty[ord[j]]==m)j++;
        // plates ord[i..j) sorted by cost
        ll capA=a[m],capB=b[m],need=a[m]+b[m];
        for(int q=i;q<j&&need>0;q++){
            int p=ord[q];bool A=tA[p]<=T,B=tB[p]<=T;
            ll take=0;
            if(A&&B)take=min(X[p],need);
            else if(A){take=min(X[p],min(capA,need));capA-=take;}
            else if(B){take=min(X[p],min(capB,need));capB-=take;}
            need-=take;total+=take*C[p];
        }
        i=j;
    }
    printf("%lld %lld\n",T,total);
}
