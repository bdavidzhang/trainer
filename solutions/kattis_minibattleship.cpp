#include <bits/stdc++.h>
using namespace std;
int n,k; unsigned X=0,O=0; vector<unsigned> pl[6]; int sz[6]; long long cnt=0;
void rec(int i,unsigned m){
    if(i==k){ if((m&O)==O)cnt++; return;}
    for(unsigned p:pl[i]) if(!(p&m)) rec(i+1,m|p);
}
int main(){
    cin>>n>>k;
    for(int i=0;i<n;i++){string s;cin>>s;for(int j=0;j<n;j++){if(s[j]=='X')X|=1u<<(i*n+j); if(s[j]=='O')O|=1u<<(i*n+j);}}
    for(int i=0;i<k;i++){cin>>sz[i]; int x=sz[i];
        for(int r=0;r<n;r++)for(int c=0;c+x<=n;c++){unsigned m=0;for(int t=0;t<x;t++)m|=1u<<(r*n+c+t); if(!(m&X))pl[i].push_back(m);}
        if(x>1)for(int c=0;c<n;c++)for(int r=0;r+x<=n;r++){unsigned m=0;for(int t=0;t<x;t++)m|=1u<<((r+t)*n+c); if(!(m&X))pl[i].push_back(m);}
    }
    rec(0,0);
    printf("%lld\n",cnt);
}
