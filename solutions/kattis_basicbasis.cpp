#include <bits/stdc++.h>
using namespace std;
typedef bitset<160> V;
int n,m,k;
V rd(){ static char s[64]; scanf("%s",s); V v; for(int i=0;i<k;i++){int c=isdigit(s[i])?s[i]-'0':s[i]-'a'+10; for(int b=0;b<4;b++) if(c>>(3-b)&1) v[4*(k-1-i)+3-b]=1;} return v;}
int main(){
    scanf("%d %d %d",&n,&m,&k);
    vector<V> basis(160); vector<int> tm(160,0); int zeroT=-1;
    for(int i=1;i<=n;i++){
        V v=rd(); bool ins=false;
        for(int b=159;b>=0;b--) if(v[b]){ if(tm[b]) v^=basis[b]; else {basis[b]=v;tm[b]=i;ins=true;break;} }
        if(!ins && zeroT<0) zeroT=i;
    }
    for(int q=0;q<m;q++){
        V v=rd();
        if(v.none()){printf("%d\n",zeroT);continue;}
        int ans=0;
        for(int b=159;b>=0&&ans>=0;b--) if(v[b]){ if(tm[b]){v^=basis[b];ans=max(ans,tm[b]);} else ans=-1; }
        printf("%d\n",ans);
    }
}
