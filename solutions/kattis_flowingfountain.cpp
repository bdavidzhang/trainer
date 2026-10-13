#include <bits/stdc++.h>
using namespace std;
int par[300005];
int find(int v){ while(par[v]!=v){ par[v]=par[par[v]]; v=par[v]; } return v; }
int main(){
    int n,q; scanf("%d %d",&n,&q);
    vector<long long> c(n+1), f(n+1,0);
    for(int i=0;i<n;i++) scanf("%lld",&c[i]);
    vector<int> nx(n+1,n);
    vector<int> st;
    for(int i=n-1;i>=0;i--){
        while(!st.empty() && c[st.back()]<c[i]) st.pop_back();
        nx[i]=st.empty()?n:st.back();
        st.push_back(i);
    }
    for(int i=0;i<=n;i++) par[i]=i; // par points to self if not full, else to nx
    while(q--){
        char t; scanf(" %c",&t);
        if(t=='+'){
            int l; long long x; scanf("%d %lld",&l,&x); l--;
            int v=find(l);
            while(v<n && x>0){
                long long room=c[v]-f[v];
                if(x<room){ f[v]+=x; x=0; }
                else { x-=room; f[v]=c[v]; par[v]=nx[v]; v=find(v); }
            }
        } else {
            int l; scanf("%d",&l); l--;
            printf("%lld\n",f[l]);
        }
    }
}
